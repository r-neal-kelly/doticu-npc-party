/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64_common/Relocation.h"

#include "object_ref.h"
#include "utils.h"
#include "xcontainer.h"
#include "xlist.h"

namespace doticu_npcp { namespace Papyrus {

    void Container_Changes_t::Add_XEntry(XEntry_t* to_add, Reference_t* owner)
    {
        NPCP_ASSERT(this->owner == owner);

        if (to_add) {
            Form_t* form = to_add->form;
            NPCP_ASSERT(form);

            if (!xentries) {
                xentries = XEntries_t::Create();
                xentries->Insert(to_add);
            } else {
                XEntry_t* existing_xentry = XEntry(form, false);
                if (existing_xentry) {
                    NPCP_ASSERT(to_add->Delta_Count() > 0);

                    if (to_add->xlists) {
                        std::vector<XList_t*> xlists_to_add;
                        xlists_to_add.reserve(to_add->xlists->Count());

                        for (XLists_t::Iterator it = to_add->xlists->Begin(); !it.End(); ++it) {
                            XList_t* xlist_to_add = it.Get();
                            if (xlist_to_add) {
                                XList::Validate(xlist_to_add);
                                xlists_to_add.push_back(xlist_to_add);
                            }
                        }

                        for (size_t idx = 0, count = xlists_to_add.size(); idx < count; idx += 1) {
                            XList_t* xlist_to_add = xlists_to_add[idx];
                            to_add->Remove_XList(xlist_to_add);
                            existing_xentry->Add_XList(xlist_to_add);
                        }
                    }

                    existing_xentry->Increment(to_add->Delta_Count());
                    XEntry_t::Destroy(to_add);
                } else {
                    xentries->Insert(to_add);
                }
            }
        }
    }

    void Container_Changes_t::Remove_XEntry(XEntry_t* xentry)
    {
        if (xentry) {
            if (xentries) {
                struct Functor {
                    XEntry_t* to_remove;
                    Functor(XEntry_t* to_remove) :
                        to_remove(to_remove)
                    {
                    }
                    Bool_t Accept(XEntry_t* xentry)
                    {
                        return xentry == to_remove;
                    }
                } functor(xentry);
                xentries->RemoveIf(functor);
            }
        }
    }

    XEntry_t* Container_Changes_t::XEntry(Form_t* form, Bool_t allow_creation)
    {
        if (form) {
            for (XEntries_t::Iterator it = xentries->Begin(); !it.End(); ++it) {
                XEntry_t* xentry = it.Get();
                if (xentry && xentry->form == form) {
                    return xentry;
                }
            }

            if (allow_creation) {
                XEntry_t* new_xentry = XEntry_t::Create(form, 0);
                xentries->Insert(new_xentry);
                return new_xentry;
            }

            return nullptr;
        } else {
            return nullptr;
        }
    }

    void Container_Changes_t::Validate()
    {
        if (xentries) {
            for (XEntries_t::Iterator it = xentries->Begin(); !it.End(); ++it) {
                XEntry_t* xentry = it.Get();
                if (xentry) {
                    xentry->Validate(owner);
                }
            }
        }
    }

    void XContainer_t::Add_XEntry(XEntry_t* xentry, Reference_t* owner)
    {
        NPCP_ASSERT(changes);
        changes->Add_XEntry(xentry, owner);
    }

    void XContainer_t::Remove_XEntry(XEntry_t* xentry)
    {
        NPCP_ASSERT(changes);
        changes->Remove_XEntry(xentry);
    }

    XEntry_t* XContainer_t::XEntry(Form_t* form, Bool_t allow_creation)
    {
        NPCP_ASSERT(changes);
        return changes->XEntry(form, allow_creation);
    }

    void XContainer_t::Validate()
    {
        NPCP_ASSERT(changes);
        changes->Validate();
    }

}}
