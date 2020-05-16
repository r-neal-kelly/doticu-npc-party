/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "xentry.h"
#include "form.h"

namespace doticu_npcp { namespace XEntry {

    XEntry_t *Create(TESForm *form, SInt32 count) {
        if (!form) {
            _ERROR("XEntry::Create: Invalid args.");
            return NULL;
        }

        XEntry_t *entry = (XEntry_t *)Heap_Allocate(sizeof(XEntry_t));
        ASSERT(entry);

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
            if (xentry->extendDataList->Count() > 0) {
                // we currently don't support destroying xlists, because we can't destroy their xdata
                return;
            } else {
                xentry->extendDataList->Delete();
            }
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

    u64 Get_XLists_Count(XEntry_t *xentry) {
        if (!xentry || !xentry->extendDataList) {
            return 0;
        }

        u64 count_xlists = 0;
        for (XLists_t::Iterator it_xlist = xentry->extendDataList->Begin(); !it_xlist.End(); ++it_xlist) {
            XList_t *xlist = it_xlist.Get();
            count_xlists += XList::Get_Count(xlist);
        }

        return count_xlists;
    }

    void Set_XList_Count(XEntry_t *xentry, XList_t *xlist, u64 count) {
        if (!xentry || !xlist || count < 1) {
            // if the count < 1, then the xlist should be deleted.
            return;
        }

        xentry->countDelta += count - XList::Get_Count(xlist);
        XList::Set_Count(xlist, count);
    }

    void Add_XList(XEntry_t *xentry, XList_t *xlist) {
        if (!xentry || !xlist) {
            _ERROR("XEntry::Add_XList: Invalid args.");
            return;
        }

        if (!xentry->extendDataList) {
            xentry->extendDataList = XLists_t::Create();
        }

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
                if (XList::Has_Outfit2_Flag(xlist) && XList::Is_Same(xlist, xlist_similar)) {
                    return xlist;
                }
            }
        } else {
            for (XLists_t::Iterator it = xentry->extendDataList->Begin(); !it.End(); ++it) {
                XList_t *xlist = it.Get();
                if (XList::Is_Same(xlist, xlist_similar)) {
                    return xlist;
                }
            }
        }

        return NULL;
    }

    bool Has_XList(XEntry_t *xentry, XList_t *xlist_similar, bool with_outfit2_flag) {
        return Get_XList(xentry, xlist_similar, with_outfit2_flag) != NULL;
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
