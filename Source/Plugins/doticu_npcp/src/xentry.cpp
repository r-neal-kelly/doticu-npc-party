/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "form.h"
#include "utils.h"
#include "xentry.h"
#include "xlist.h"

namespace doticu_npcp { namespace XEntry {

    XEntry_t *Create(TESForm *form, SInt32 count) {
        if (!form) {
            _ERROR("XEntry::Create: Invalid args.");
            return NULL;
        }

        XEntry_t *entry = (XEntry_t *)Heap_Allocate(sizeof(XEntry_t));
        NPCP_ASSERT(entry);

        entry->type = form;
        entry->countDelta = count;
        entry->extendDataList = NULL;

        return entry;
    }

    void Destroy(XEntry_t *xentry) {
        if (!xentry) {
            return;
        }

        if (xentry->extendDataList) {
            for (XLists_t::Iterator it_xlist = xentry->extendDataList->Begin(); !it_xlist.End(); ++it_xlist) {
                XList::Destroy(it_xlist.Get());
            }
            xentry->extendDataList->Delete();
        }

        xentry->extendDataList = NULL;
        xentry->countDelta = 0;
        xentry->type = NULL;

        Heap_Free(xentry);
    }

    s32 Get_Count(XEntry_t *xentry) {
        if (!xentry) {
            return 0;
        }

        return xentry->countDelta;
    }

    void Set_Count(XEntry_t *xentry, s32 count) {
        if (!xentry) {
            return;
        }

        xentry->countDelta = count;
    }

    void Inc_Count(XEntry_t *xentry, s32 inc) {
        if (!xentry) {
            return;
        }

        xentry->countDelta += inc;
    }

    void Dec_Count(XEntry_t *xentry, s32 dec) {
        if (!xentry) {
            return;
        }

        xentry->countDelta -= dec;
    }

    void Add_XList(XEntry_t *xentry, XList_t *xlist) {
        if (!xentry || !xlist) {
            _ERROR("XEntry::Add_XList: Invalid args.");
            return;
        }

        if (!xentry->extendDataList) {
            xentry->extendDataList = XLists_t::Create();
        }

        XList::Validate(xlist);
        xentry->extendDataList->Insert(xlist);
        xentry->countDelta += XList::Get_Count(xlist);
    }

    void Remove_XList(XEntry_t *xentry, XList_t *xlist) {
        if (!xentry || !xlist) {
            _ERROR("XEntry::Remove_XList: Invalid args.");
            return;
        }

        XLists_t *xlists = xentry->extendDataList;
        if (!xlists) {
            return;
        }

        class Functor {
        private:
            XList_t *p_xlist;
        public:
            Functor(XList_t *xlist) {
                p_xlist = xlist;
            }
            bool Accept(XList_t *xlist) {
                return xlist == p_xlist;
            }
        } functor(xlist);
        xlists->RemoveIf(functor);

        XList::Validate(xlist);
        xentry->countDelta -= XList::Get_Count(xlist);
    }

    XList_t *Get_XList(XEntry_t *xentry, XList_t *xlist_similar, bool with_outfit2_flag) {
        if (!xentry || !xlist_similar) {
            return NULL;
        }
        if (!xentry->extendDataList) {
            return NULL;
        }

        if (with_outfit2_flag) {
            for (XLists_t::Iterator it = xentry->extendDataList->Begin(); !it.End(); ++it) {
                XList_t *xlist = it.Get();
                if (XList::Has_Outfit2_Flag(xlist) && XList::Is_Similar(xlist, xlist_similar)) {
                    return xlist;
                }
            }
        } else {
            for (XLists_t::Iterator it = xentry->extendDataList->Begin(); !it.End(); ++it) {
                XList_t *xlist = it.Get();
                if (XList::Is_Similar(xlist, xlist_similar)) {
                    return xlist;
                }
            }
        }

        return NULL;
    }

    bool Has_XList(XEntry_t *xentry, XList_t *xlist_similar, bool with_outfit2_flag) {
        return Get_XList(xentry, xlist_similar, with_outfit2_flag) != NULL;
    }

    void Move_XList(XEntry_t *from, XEntry_t *to, XList_t *xlist, TESObjectREFR *ref_to) {
        if (!from || !to || !xlist || !ref_to) {
            return;
        }

        Remove_XList(from, xlist);

        u64 count_xdata = XList::Clean_For_Move(xlist, ref_to);
        if (count_xdata == 0) {
            Inc_Count(to, 1);
            XList::Destroy(xlist);
        } else if (count_xdata == 1 && xlist->m_data->GetType() == kExtraData_Count) {
            Inc_Count(to, XList::Get_Count(xlist));
            XList::Destroy(xlist);
        } else {
            Add_XList(to, xlist);
        }
    }

    void Clean_XLists(XEntry_t *xentry, TESObjectREFR *ref_container) {
        if (!xentry || !xentry->extendDataList || !ref_container) {
            return;
        }

        std::vector<XList_t *> vec_xlists;
        for (XLists_t::Iterator it_xlist = xentry->extendDataList->Begin(); !it_xlist.End(); ++it_xlist) {
            XList_t *xlist = it_xlist.Get();
            if (!xlist) {
                continue;
            }
            XList::Validate(xlist);
            vec_xlists.push_back(xlist);
        }

        for (u64 idx = 0, size = vec_xlists.size(); idx < size; idx += 1) {
            XList_t *xlist = vec_xlists[idx];
            u64 count_xdata = XList::Clean_For_Move(xlist, ref_container);
            if (count_xdata == 0) {
                Remove_XList(xentry, xlist);
                Inc_Count(xentry, 1);
                XList::Destroy(xlist);
            } else if (count_xdata == 1 && xlist->m_data->GetType() == kExtraData_Count) {
                Remove_XList(xentry, xlist);
                Inc_Count(xentry, XList::Get_Count(xlist));
                XList::Destroy(xlist);
            }
        }
    }

    bool Has_An_XList(XEntry_t *xentry) {
        if (xentry) {
            return false;
        }

        return xentry->extendDataList->Count() > 0;
    }

    bool Is_Worn(XEntry_t *xentry) {
        if (!xentry || !xentry->extendDataList) {
            return false;
        }

        for (XLists_t::Iterator it_xlists = xentry->extendDataList->Begin(); !it_xlists.End(); ++it_xlists) {
            XList_t *xlist = it_xlists.Get();
            if (XList::Is_Worn(xlist)) {
                return true;
            }
        }

        return false;
    }

    void Log(XEntry_t *xentry, const std::string str_indent) {
        if (!xentry || !xentry->type) {
            return;
        }

        _MESSAGE("%s'%s', count: %i, type: %s",
                 str_indent.c_str(),
                 Form::Get_Name(xentry->type),
                 xentry->countDelta,
                 Form::Get_Type_String(xentry->type));

        if (xentry->extendDataList) {
            u64 idx_xlist = 0;
            for (XLists_t::Iterator it_xlist = xentry->extendDataList->Begin(); !it_xlist.End(); ++it_xlist, idx_xlist += 1) {
                XList_t *xlist = it_xlist.Get();
                if (xlist) {
                    _MESSAGE("%s%sxlist idx: %i",
                             str_indent.c_str(),
                             "    ",
                             idx_xlist);
                    XList::Log(xlist, str_indent + "        ");
                }
            }
        }
    }

}}
