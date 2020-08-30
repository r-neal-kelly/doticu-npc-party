/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

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

        XList::Validate(xlist);
        xlists->Insert(xlist);
        Increment(XList::Get_Count(xlist));
    }

    void XEntry_t::Remove_XList(XList_t* xlist)
    {
        NPCP_ASSERT(xlist);

        XList::Validate(xlist);

        if (xlists) {
            struct Functor {
                XList_t* to_remove;
                Functor(XList_t* to_remove) :
                    to_remove(to_remove)
                {
                }
                Bool_t Accept(XList_t* xlist)
                {
                    return xlist == to_remove;
                }
            } functor(xlist);
            xlists->RemoveIf(functor);

            Decrement(XList::Get_Count(xlist));
        }
    }

    void XEntry_t::Move_XList(XEntry_t* to_xentry, Reference_t* to_reference, XList_t* xlist)
    {
        if (to_xentry && to_reference && xlist) {
            Remove_XList(xlist);
            size_t xdata_count = XList::Clean_For_Move(xlist, to_reference);
            if (xdata_count == 0) {
                to_xentry->Increment(1);
                XList::Destroy(xlist);
            } else if (xdata_count == 1 && xlist->m_data->GetType() == kExtraData_Count) {
                to_xentry->Increment(XList::Get_Count(xlist));
                XList::Destroy(xlist);
            } else {
                to_xentry->Add_XList(xlist);
            }
        }
    }

    void XEntry_t::Clean_XLists(Reference_t* to_reference)
    {
        if (xlists && to_reference) {
            std::vector<XList_t*> buffer;
            for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (xlist) {
                    XList::Validate(xlist);
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
                    Increment(XList::Get_Count(xlist));
                    XList::Destroy(xlist);
                }
            }
        }
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

    void XEntry_t::Validate(Reference_t* owner)
    {
        if (xlists) {
            NPCP_ASSERT(owner);

            Int_t aggregate_xlist_count = 0;
            for (XLists_t::Iterator it = xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (xlist) {
                    XList::Validate(xlist);
                    aggregate_xlist_count += XList::Get_Count(xlist);
                }
            }
            if (aggregate_xlist_count < 0) {
                aggregate_xlist_count = 0;
            }

            Int_t bentry_count = Object_Ref::Get_BEntry_Count(owner, form);
            if (Delta_Count() < (aggregate_xlist_count - bentry_count)) {
                if (aggregate_xlist_count > 0) {
                    Delta_Count(aggregate_xlist_count);
                } else {
                    Delta_Count(1);
                }
            }
        }
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
