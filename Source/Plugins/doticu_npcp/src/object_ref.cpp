/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameRTTI.h"

#include "cell.h"
#include "form.h"
#include "game.h"
#include "object_ref.h"
#include "quest.h"
#include "utils.h"
#include "vector.h"
#include "xcontainer.h"
#include "xdata.h"
#include "xentry.h"
#include "xlist.h"

namespace doticu_npcp { namespace Object_Ref {

    BContainer_t *Get_BContainer(TESObjectREFR *obj) {
        if (!obj || !obj->baseForm) {
            return NULL;
        } else {
            return DYNAMIC_CAST(obj->baseForm, TESForm, TESContainer);
        }
    }

    XContainer_t *Get_XContainer(TESObjectREFR *obj, bool do_create) {
        if (!obj) {
            return NULL;
        }

        XContainer_t *xcontainer = (XContainer_t *)obj->extraData.GetByType(kExtraData_ContainerChanges);
        if (xcontainer && xcontainer->data && xcontainer->data->objList) {
            return xcontainer;
        } else if (do_create) {
            if (!xcontainer) {
                xcontainer = XContainer::Create(obj);
                obj->extraData.Add(kExtraData_ContainerChanges, xcontainer);
            } else if (!xcontainer->data) {
                xcontainer->data = XContainer::Create_Data(obj);
            } else {
                xcontainer->data->objList = XContainer::Create_Data_Entries();
            }
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

    void Add_XEntry(TESObjectREFR *obj, XEntry_t *xentry_add) {
        if (!obj || !xentry_add) {
            return;
        }

        XContainer_t *xcontainer_obj = Get_XContainer(obj);
        if (!xcontainer_obj) {
            _ERROR("Object_Ref::Add_XEntry: Cannot get obj xcontainer.");
            return;
        }

        TESForm *form = xentry_add->type;
        if (!form) {
            return;
        }

        XEntry_t *xentry_obj = Get_XEntry(obj, form, false);
        if (xentry_obj) {
            if (xentry_add->countDelta < 1) {
                _ERROR("Object_Ref::Add_XEntry: Cannot merge a negative or empty xentry.");
                return;
            }

            if (xentry_add->extendDataList) {
                std::vector<XList_t *>vec_xlists_add;
                vec_xlists_add.reserve(xentry_add->extendDataList->Count());

                for (XLists_t::Iterator it_xlist_add = xentry_add->extendDataList->Begin(); !it_xlist_add.End(); ++it_xlist_add) {
                    XList_t *xlist_add = it_xlist_add.Get();
                    if (xlist_add) {
                        vec_xlists_add.push_back(xlist_add);
                    }
                }

                for (u64 idx = 0, size = vec_xlists_add.size(); idx < size; idx += 1) {
                    XList_t *xlist_add = vec_xlists_add[idx];
                    XEntry::Remove_XList(xentry_add, xlist_add);
                    XEntry::Add_XList(xentry_obj, xlist_add);
                }
            }

            XEntry::Inc_Count(xentry_obj, XEntry::Get_Count(xentry_add));

            XEntry::Destroy(xentry_add);
        } else {
            if (xentry_add->countDelta < 1 && Get_BEntry_Count(obj, form) < 1) {
                _ERROR("Object_Ref::Add_XEntry: Cannot add a useless negative or empty xentry.");
                return;
            }

            xcontainer_obj->data->objList->Insert(xentry_add);
        }
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

    void Move_Entry(TESObjectREFR *from, TESObjectREFR *to, TESForm *form) {
        if (!from || !to || !form) {
            return;
        }

        XContainer_t *xcontainer_from = Get_XContainer(from);
        if (!xcontainer_from) {
            _ERROR("Object_Ref::Move_XEntry: Could not get xcontainer_from.");
            return;
        }

        XContainer_t *xcontainer_to = Get_XContainer(to);
        if (!xcontainer_to) {
            _ERROR("Object_Ref::Move_XEntry: Could not get xcontainer_to.");
            return;
        }

        XEntry_t *xentry_from = Get_XEntry(from, form);
        u64 count_bentry_from = Get_BEntry_Count(from, form);
        if (xentry_from) {
            u64 count_xentry_from = XEntry::Get_Count(xentry_from);
            if (count_xentry_from == 0 && count_bentry_from == 0) {
                Object_Ref::Remove_XEntry(from, xentry_from);
                XEntry::Destroy(xentry_from);
                return;
            }

            if (count_xentry_from <= 0 - count_bentry_from) {
                return;
            }

            Object_Ref::Remove_XEntry(from, xentry_from);
            XEntry::Clean_XLists(xentry_from, to);

            if (count_bentry_from > 0) {
                XEntry::Inc_Count(xentry_from, count_bentry_from);
                Object_Ref::Add_XEntry(from, XEntry::Create(form, 0 - count_bentry_from));
            }

            Object_Ref::Add_XEntry(to, xentry_from);
        } else if (count_bentry_from > 0) {
            Object_Ref::Add_XEntry(from, XEntry::Create(form, 0 - count_bentry_from));
            Object_Ref::Add_XEntry(to, XEntry::Create(form, count_bentry_from));
        }
    }

    void Move_XList(TESObjectREFR *from, TESObjectREFR *to, TESForm *form, XList_t *xlist) {
        return XEntry::Move_XList(Get_XEntry(from, form), Get_XEntry(to, form), xlist, to);
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

        const char *name = CALL_MEMBER_FN(ref_object, GetReferenceName)();
        if (!name) {
            return "";
        }

        return name;
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
                if (Utils::Is_Bit_On(info->alias->flags, 2)) {
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

    void Remove_Unwearable(TESObjectREFR *obj, TESObjectREFR *other) {
        if (!obj || !other) {
            _ERROR("Object_Ref::Remove_Unwearable: Invalid args.");
            return;
        }

        XContainer_t *xcontainer_other = Object_Ref::Get_XContainer(other);
        if (!xcontainer_other) {
            _ERROR("Object_Ref::Remove_Unwearable: Could not get other xcontainer.");
            return;
        }

        std::vector<TESForm *> vec_forms_remove;
        vec_forms_remove.reserve(4);

        XContainer_t *xcontainer_obj = Object_Ref::Get_XContainer(obj);
        if (xcontainer_obj) {
            for (XEntries_t::Iterator it_xentry_obj = xcontainer_obj->data->objList->Begin(); !it_xentry_obj.End(); ++it_xentry_obj) {
                XEntry_t *xentry_obj = it_xentry_obj.Get();
                if (!xentry_obj || !xentry_obj->type) {
                    continue;
                }

                TESForm *form_obj = xentry_obj->type;
                if (form_obj->IsArmor() || form_obj->IsWeapon() || form_obj->IsAmmo()) {
                    continue;
                }

                vec_forms_remove.push_back(form_obj);
            }
        }

        BContainer_t *bcontainer_obj = Object_Ref::Get_BContainer(obj);
        if (bcontainer_obj) {
            for (u64 idx = 0; idx < bcontainer_obj->numEntries; idx += 1) {
                BEntry_t *bentry_obj = bcontainer_obj->entries[idx];
                if (!bentry_obj || !bentry_obj->form || bentry_obj->count < 1) {
                    continue;
                }

                TESForm *form_obj = bentry_obj->form;
                if (form_obj->formType == kFormType_LeveledItem || form_obj->IsArmor() || form_obj->IsWeapon() || form_obj->IsAmmo()) {
                    continue;
                }

                if (!Vector::Has<TESForm *>(vec_forms_remove, form_obj)) {
                    vec_forms_remove.push_back(form_obj);
                }
            }
        }

        if (vec_forms_remove.size() > 0) {
            for (u64 idx = 0, size = vec_forms_remove.size(); idx < size; idx += 1) {
                TESForm *form_remove = vec_forms_remove[idx];
                Object_Ref::Move_Entry(obj, other, form_remove);
            }
        }
    }

    void Categorize(TESObjectREFR *obj) {
        if (!obj) {
            _MESSAGE("Object_Ref::Categorize: Missing ref_object.");
            return;
        }

        std::vector<TESForm *> vec_forms_move;

        XContainer_t *xcontainer_obj = Object_Ref::Get_XContainer(obj);
        if (xcontainer_obj) {
            for (XEntries_t::Iterator it_xentry_obj = xcontainer_obj->data->objList->Begin(); !it_xentry_obj.End(); ++it_xentry_obj) {
                XEntry_t *xentry_obj = it_xentry_obj.Get();
                if (!xentry_obj || !xentry_obj->type) {
                    continue;
                }

                TESForm *form_obj = xentry_obj->type;
                if (!form_obj->IsPlayable()) {
                    continue;
                }

                vec_forms_move.push_back(form_obj);
            }
        }

        BContainer_t *bcontainer_obj = Object_Ref::Get_BContainer(obj);
        if (bcontainer_obj) {
            for (u64 idx = 0; idx < bcontainer_obj->numEntries; idx += 1) {
                BEntry_t *bentry_obj = bcontainer_obj->entries[idx];
                if (!bentry_obj || !bentry_obj->form || bentry_obj->count < 1) {
                    continue;
                }

                TESForm *form_obj = bentry_obj->form;
                if (form_obj->formType == kFormType_LeveledItem || !form_obj->IsPlayable()) {
                    continue;
                }

                if (!Vector::Has<TESForm *>(vec_forms_move, form_obj)) {
                    vec_forms_move.push_back(form_obj);
                }
            }
        }

        for (u64 idx = 0, size = vec_forms_move.size(); idx < size; idx += 1) {
            TESForm *form_move = vec_forms_move[idx];

            TESObjectREFR *category = Game::Get_NPCP_Category(form_move);
            if (!category) {
                continue;
            }

            Object_Ref::Move_Entry(obj, category, form_move);
        }
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

    void Log_XList(TESObjectREFR *obj) {
        if (!obj) {
            _MESSAGE("Log_XList: Not an object.");
            return;
        }

        const char *name = Get_Name(obj);
        if (name && name[0]) {
            _MESSAGE("Logging XList: %s", name);
        } else {
            _MESSAGE("Logging XList: (no name)");
        }

        XList_t *xlist = &obj->extraData;
        XList::Log(xlist, "    ");

        _MESSAGE("End of XList.");
    }

    void Move_To_Orbit(TESObjectREFR *obj, TESObjectREFR *target, float radius, float angle_degree) {
        if (!obj || !target) {
            return;
        }

        UInt32 target_handle = target->CreateRefHandle();
        if (target_handle == *g_invalidRefHandle) {
            return;
        }

        TESObjectCELL *target_cell = target->parentCell;
        if (!target_cell) {
            return;
        }

        TESWorldSpace *target_world = CALL_MEMBER_FN(target, GetWorldspace)();

        float angle_radians = target->rot.z - (angle_degree * DOTICU_NPCP_PI / 180);
        NiPoint3 obj_pos(
            target->pos.x + radius * sin(angle_radians),
            target->pos.y + radius * cos(angle_radians),
            target->pos.z
        );
        NiPoint3 obj_rot(
            0.0,
            0.0,
            target->rot.z + ((180 - angle_degree) * DOTICU_NPCP_PI / 180)
        );

        MoveRefrToPosition(obj, &target_handle, target_cell, target_world, &obj_pos, &obj_rot);
    }

    float Get_Distance(TESObjectREFR *obj, TESObjectREFR *target) {
        if (!obj || !target) {
            return -1.0;
        }

        float dist_x;
        if (obj->pos.x > target->pos.x) {
            dist_x = obj->pos.x - target->pos.x;
        } else {
            dist_x = target->pos.x - obj->pos.x;
        }

        float dist_y;
        if (obj->pos.y > target->pos.y) {
            dist_y = obj->pos.y - target->pos.y;
        } else {
            dist_y = target->pos.y - obj->pos.y;
        }

        return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
    }

    bool Is_Near_Player(TESObjectREFR *obj, float max_radius) {
        Actor *actor_player = *g_thePlayer;
        TESObjectCELL *cell_player = actor_player->parentCell;
        TESObjectCELL *cell_obj = obj->parentCell;

        if (Cell::Is_Interior(cell_player) && cell_player != cell_obj) {
            return false;
        }

        float distance = Get_Distance(actor_player, obj);
        return distance > 0 && distance <= max_radius;
    }

    Reference_t* From_Handle(Reference_Handle_t handle)
    {
        NiPointer<Reference_t> reference = nullptr;
        LookupREFRByHandle(handle, reference);
        return static_cast<Reference_t*>(reference);
    }

    bool Has_Token(Reference_t* ref, Form_t* token, Int_t count)
    {
        if (ref && token && count > 0) {
            return Get_Entry_Count(ref, token) == count;
        } else {
            return false;
        }
    }

    void Token(Reference_t* ref, Form_t* token, Int_t count)
    {
        if (ref && token && count > 0) {
            Int_t bentry_count = Object_Ref::Get_BEntry_Count(ref, token);
            if (bentry_count == count) {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, false);
                if (xentry) {
                    Object_Ref::Remove_XEntry(ref, xentry);
                }
            } else {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, true);
                if (xentry) {
                    if (xentry->countDelta + bentry_count != count) {
                        xentry->countDelta = count - bentry_count;
                    }
                } else {
                    _MESSAGE("unable to get xentry for adding token.");
                }
            }
        }
    }

    void Untoken(Reference_t* ref, Form_t* token)
    {
        if (ref && token) {
            Int_t bentry_count = Object_Ref::Get_BEntry_Count(ref, token);
            if (bentry_count == 0) {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, false);
                if (xentry) {
                    Object_Ref::Remove_XEntry(ref, xentry);
                }
            } else {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, true);
                if (xentry) {
                    if (xentry->countDelta + bentry_count != 0) {
                        xentry->countDelta = 0 - bentry_count;
                    }
                } else {
                    _MESSAGE("unable to get xentry for removing token.");
                }
            }
        }
    }

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    void Remove_Unwearable(Selfless_t *, TESObjectREFR *obj, TESObjectREFR *other) {
        return Object_Ref::Remove_Unwearable(obj, other);
    }

    void Categorize(Selfless_t *, TESObjectREFR *obj) {
        return Object_Ref::Categorize(obj);
    }

    void Log_XContainer(Selfless_t *, TESObjectREFR *ref_object) {
        return Object_Ref::Log_XContainer(ref_object);
    }

    void Log_XList(Selfless_t *, TESObjectREFR *obj) {
        return Object_Ref::Log_XList(obj);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <Selfless_t, void, TESObjectREFR *, TESObjectREFR *>(
                "Object_Ref_Remove_Unwearable",
                "doticu_npcp",
                Exports::Remove_Unwearable,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Selfless_t, void, TESObjectREFR *>(
                "Object_Ref_Categorize",
                "doticu_npcp",
                Exports::Categorize,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Selfless_t, void, TESObjectREFR *>(
                "Object_Ref_Log_XContainer",
                "doticu_npcp",
                Exports::Log_XContainer,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <Selfless_t, void, TESObjectREFR *>(
                "Object_Ref_Log_XList",
                "doticu_npcp",
                Exports::Log_XList,
                registry)
        );

        return true;
    }

}}}
