/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#undef max

#include "form.h"
#include "object_ref.h"
#include "utils.h"
#include "xentry.h"
#include "xlist.h"

namespace doticu_npcp { namespace Papyrus {

    XEntry_t* XEntry_t::Create(Form_t* form, Int_t delta_count)
    {
        NPCP_ASSERT(form);

        XEntry_t* xentry = static_cast<XEntry_t*>(Heap_Allocate(sizeof(XEntry_t)));
        NPCP_ASSERT(xentry);

        xentry->form = form;
        xentry->delta_count = delta_count;
        xentry->xlists = nullptr;

        return xentry;
    }

    void XEntry_t::Destroy(XEntry_t* xentry)
    {
        if (xentry) {
            if (xentry->xlists) {
                for (XLists_t::Iterator it = xentry->xlists->Begin(); !it.End(); ++it) {
                    XList::Destroy(it.Get());
                }
                xentry->xlists->Delete();
            }

            xentry->form = nullptr;
            xentry->delta_count = 0;
            xentry->xlists = nullptr;

            Heap_Free(xentry);
        }
    }

    Int_t XEntry_t::Delta_Count()
    {
        // we could pass in the reference owner, or the bentry to validate
        return delta_count;
    }

    void XEntry_t::Delta_Count(Int_t new_delta_count)
    {
        // we could pass in the reference owner, or the bentry to validate
        delta_count = new_delta_count;
    }

    void XEntry_t::Increment(Int_t by)
    {
        // we could pass in the reference owner, or the bentry to validate
        delta_count += by;
    }

    void XEntry_t::Decrement(Int_t by)
    {
        // we could pass in the reference owner, or the bentry to validate
        delta_count -= by;
    }

    void XEntry_t::Add_XList(XList_t* xlist)
    {
        NPCP_ASSERT(xlist);

        if (!xlists) {
            xlists = XLists_t::Create();
        }

        xlists->Insert(xlist);
        Increment(XList::Count(xlist));
    }

    void XEntry_t::Add_Clean_XList(XList_t* xlist, Reference_t* owner)
    {
        size_t xdata_count = XList::Clean_For_Move(xlist, owner);
        if (xdata_count == 0) {
            Increment(1);
            XList::Destroy(xlist);
        } else if (xdata_count == 1 && xlist->m_data->GetType() == kExtraData_Count) {
            Increment(XList::Count(xlist));
            XList::Destroy(xlist);
        } else {
            Add_XList(xlist);
        }
    }

    void XEntry_t::Remove_XList(XList_t* xlist)
    {
        NPCP_ASSERT(xlist);

        if (xlists) {
            struct Functor {
                XEntry_t* xentry;
                XList_t* xlist_to_remove;
                Functor(XEntry_t* xentry, XList_t* xlist_to_remove) :
                    xentry(xentry), xlist_to_remove(xlist_to_remove)
                {
                }
                Bool_t Accept(XList_t* xlist)
                {
                    if (xlist == xlist_to_remove) {
                        xentry->Decrement(XList::Count(xlist));
                        return true;
                    } else {
                        return false;
                    }
                }
            } functor(this, xlist);
            xlists->RemoveIf(functor);
        }
    }

    void XEntry_t::Move_XList(XEntry_t* to_xentry, Reference_t* to_reference, XList_t* xlist)
    {
        if (to_xentry && to_reference && xlist) {
            Remove_XList(xlist);
            to_xentry->Add_Clean_XList(xlist, to_reference);
        }
    }

    void XEntry_t::Clean_XLists(Int_t from_bentry_count, Reference_t* to_reference)
    {
        if (xlists && to_reference) {
            std::vector<XList_t*> buffer;
            for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (xlist) {
                    XList::Validate(xlist, delta_count, from_bentry_count);
                    buffer.push_back(xlist);
                }
            }
            for (size_t idx = 0, count = buffer.size(); idx < count; idx += 1) {
                XList_t* xlist = buffer[idx];
                size_t xdata_count = XList::Clean_For_Move(xlist, to_reference);
                if (xdata_count == 0) {
                    Remove_XList(xlist);
                    Increment(1);
                    XList::Destroy(xlist);
                } else if (xdata_count == 1 && xlist->m_data->GetType() == kExtraData_Count) {
                    Remove_XList(xlist);
                    Increment(XList::Count(xlist));
                    XList::Destroy(xlist);
                }
            }
        }
    }

    void XEntry_t::Increment_XList(XList_t* xlist, Int_t increment)
    {
        if (xlist && increment > 0) {
            XList::Increment(xlist, increment);
            delta_count += increment;
        }
    }

    Int_t XEntry_t::Decrement_XList(XList_t* xlist, Int_t decrement)
    {
        Int_t amount_decreased = 0;

        if (xlist && decrement > 0) {
            amount_decreased = XList::Decrement(xlist, decrement);
            delta_count -= amount_decreased;
        }

        return amount_decreased;
    }

    XList_t* XEntry_t::Similar_XList(XList_t* xlist_to_compare)
    {
        if (xlist_to_compare && xlists) {
            for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (xlist && XList::Is_Similar(xlist, xlist_to_compare)) {
                    return xlist;
                }
            }
            return nullptr;
        } else {
            return nullptr;
        }
    }

    Bool_t XEntry_t::Has_Similar_XList(XList_t* similar)
    {
        return Similar_XList(similar) != nullptr;
    }

    Bool_t XEntry_t::Has_Worn_XList()
    {
        if (xlists) {
            for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (XList::Is_Worn(xlist)) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    Int_t XEntry_t::Validate(Int_t bentry_count)
    {
        Int_t xlist_count = 0;
        if (xlists) {
            for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (xlist) {
                    XList::Validate(xlist, delta_count, bentry_count);
                    xlist_count += XList::Count(xlist);
                }
            }
            if (xlist_count < 0) {
                xlist_count = std::numeric_limits<Int_t>::max();
            }
        }
        if (delta_count < xlist_count - bentry_count) {
            delta_count = xlist_count - bentry_count;
        }
        return xlist_count;
    }

    void XEntry_t::Log(const std::string indent)
    {
        if (form) {
            _MESSAGE("%s'%s', count: %i, type: %s",
                     indent.c_str(),
                     Form::Get_Name(form),
                     delta_count,
                     Form::Get_Type_String(form));

            if (xlists) {
                size_t idx = 0;
                for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it, idx += 1) {
                    XList_t* xlist = it.Get();
                    if (xlist) {
                        _MESSAGE("%s%sxlist idx: %i",
                                 indent.c_str(),
                                 "    ",
                                 idx);
                        XList::Log(xlist, indent + "        ");
                    }
                }
            }
        }
    }

}}
