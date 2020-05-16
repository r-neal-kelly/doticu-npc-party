/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "object_ref.h"
#include "quest.h"

namespace doticu_npcp { namespace Object_Ref {

    BContainer_t *Get_BContainer(TESObjectREFR *obj) {
        if (!obj || !obj->baseForm) {
            return NULL;
        } else {
            return DYNAMIC_CAST(obj->baseForm, TESForm, TESContainer);
        }
    }

    XContainer_t *Get_XContainer(TESObjectREFR *obj) {
        if (!obj) {
            return NULL;
        }

        XContainer_t *xcontainer = (XContainer_t *)obj->extraData.GetByType(kExtraData_ContainerChanges);
        if (xcontainer && xcontainer->data && xcontainer->data->objList) {
            return xcontainer;
        } else {
            return NULL;
        }
    }

    BEntry_t *Get_BEntry(TESObjectREFR *obj, TESForm *form) {
        if (!obj || !form) {
            return NULL;
        }

        BContainer_t *bcontainer = Get_BContainer(obj);
        if (bcontainer) {
            for (u64 idx = 0; idx < bcontainer->numEntries; idx += 1) {
                BEntry_t *bentry = bcontainer->entries[idx];
                if (bentry && bentry->form == form) {
                    return bentry;
                }
            }
        }

        return NULL;
    }

    XEntry_t *Get_XEntry(TESObjectREFR *obj, TESForm *form, bool do_create) {
        if (!obj || !form) {
            return NULL;
        }

        XContainer_t *xcontainer = Get_XContainer(obj);
        if (xcontainer) {
            for (XEntries_t::Iterator it = xcontainer->data->objList->Begin(); !it.End(); ++it) {
                XEntry_t *entry = it.Get();
                if (entry && entry->type == form) {
                    return entry;
                }
            }
            if (do_create) {
                XEntry_t *entry_new = XEntry::Create(form, 0);
                if (entry_new) {
                    xcontainer->data->objList->Insert(entry_new);
                    return entry_new;
                }
            }
        }

        return NULL;
    }

    void Remove_XEntry(TESObjectREFR *obj, XEntry_t *xentry) {
        if (!obj || !xentry) {
            return;
        }

        XContainer_t *xcontainer = Get_XContainer(obj);
        if (!xcontainer) {
            return;
        }

        class Functor {
        private:
            XEntry_t *p_xentry;
        public:
            Functor(XEntry_t *xentry) {
                p_xentry = xentry;
            }
            bool Accept(XEntry_t *xentry) {
                return xentry == p_xentry;
            }
        } functor(xentry);
        xcontainer->data->objList->RemoveIf(functor);
    }

    bool Has_XEntry(TESObjectREFR *obj, TESForm *form) {
        return Get_XEntry(obj, form, false) != NULL;
    }

    // need to study if a BContainer can have multiple entries of the same form or not. confer with editor.
    SInt32 Get_BEntry_Count(TESObjectREFR *obj, TESForm *form) {
        if (!obj || !form) {
            return 0;
        }

        BContainer_t *bcontainer = Get_BContainer(obj);
        SInt32 count = 0;
        if (bcontainer) {
            for (u64 idx = 0; idx < bcontainer->numEntries; idx += 1) {
                BEntry_t *bentry = bcontainer->entries[idx];
                if (bentry && bentry->form == form) {
                    count += bentry->count;
                }
            }
        }

        return count;
    }

    SInt32 Get_XEntry_Count(TESObjectREFR *obj, TESForm *form) {
        if (!obj || !form) {
            return 0;
        }

        return XEntry::Get_Count(Get_XEntry(obj, form, false));
    }

    SInt32 Get_Entry_Count(TESObjectREFR *obj, TESForm *form) {
        return Get_BEntry_Count(obj, form) + Get_XEntry_Count(obj, form);
    }

    const char *Get_Base_Name(TESObjectREFR *ref_object) {
        if (!ref_object || !ref_object->baseForm) {
            return "";
        }

        return Form::Get_Name(ref_object->baseForm);
    }

    const char *Get_Ref_Name(TESObjectREFR *ref_object) {
        if (!ref_object) {
            return "";
        }

        return CALL_MEMBER_FN(ref_object, GetReferenceName)();
    }

    const char *Get_Name(TESObjectREFR *ref_object) {
        const char *str_name = Get_Ref_Name(ref_object);
        if (str_name[0] != NULL) {
            return str_name;
        } else {
            return Get_Base_Name(ref_object);
        }
    }

    // this appears to indicate if the object is stolen/stealable
    bool Is_Off_Limits(TESObjectREFR *ref_object) {
        if (!ref_object) {
            return false;
        }

        return CALL_MEMBER_FN(ref_object, IsOffLimits)();
    }

    bool Is_Quest_Item(TESObjectREFR *obj) {
        if (!obj || !obj->extraData.HasType(kExtraData_AliasInstanceArray)) {
            return false;
        }

        ExtraAliasInstanceArray *xaliases = (ExtraAliasInstanceArray *)obj->extraData.GetByType(kExtraData_AliasInstanceArray);
        if (!xaliases) {
            return false;
        }

        // just the fact that it has this extra data does not make it a quest item.
        // it appears to be a list of all this reference's aliases and their respective quests
        for (u64 idx = 0, count = xaliases->aliases.count; idx < count; idx += 1) {
            ExtraAliasInstanceArray::AliasInfo *info = xaliases->aliases[idx];
            if (info && info->alias) {
                //_MESSAGE("quest: %s, flags: %x", Quest::Get_Name(info->quest), info->alias->flags);
                if (Bit_Is_Set(info->alias->flags, 2)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool Is_Worn(TESObjectREFR *obj, TESForm *form) {
        if (!obj || !form) {
            return false;
        }

        return XEntry::Is_Worn(Get_XEntry(obj, form));
    }

    void Log_XContainer(TESObjectREFR *ref_object) {
        if (!ref_object) {
            _MESSAGE("Log_XContainer: Not an object.");
            return;
        }

        const char *str_object = Get_Name(ref_object);
        if (str_object && str_object[0]) {
            _MESSAGE("Log_XContainer: %s", str_object);
        } else {
            _MESSAGE("Log_XContainer: (no name)");
        }

        XContainer_t *xcontainer = Object_Ref::Get_XContainer(ref_object);
        if (xcontainer) {
            for (XEntries_t::Iterator it_xentry = xcontainer->data->objList->Begin(); !it_xentry.End(); ++it_xentry) {
                XEntry_t *xentry = it_xentry.Get();
                if (xentry) {
                    XEntry::Log(xentry, "    ");
                }
            }
        }

        _MESSAGE("End of Log_XContainer.");
    }

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    void Log_XContainer(StaticFunctionTag *, TESObjectREFR *ref_object) {
        return doticu_npcp::Object_Ref::Log_XContainer(ref_object);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, TESObjectREFR *>(
                "Object_Ref_Log_XContainer",
                "doticu_npcp",
                Log_XContainer,
                registry)
        );

        return true;
    }

}}}
