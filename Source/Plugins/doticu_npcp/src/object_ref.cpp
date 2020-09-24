/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/
#undef max

#include <numeric>

#include "skse64/GameRTTI.h"
#include "skse64/PapyrusWornObject.h"

#include "cell.h"
#include "consts.h"
#include "form.h"
#include "funcs.h"
#include "game.h"
#include "object_ref.h"
#include "offsets.h"
#include "papyrus.h"
#include "papyrus.inl"
#include "quest.h"
#include "utils.h"
#include "vector.h"
#include "xcontainer.h"
#include "xdata.h"
#include "xentry.h"
#include "xlist.h"

namespace doticu_npcp { namespace Object_Ref {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("ObjectReference");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    BContainer_t *Get_BContainer(TESObjectREFR *obj) {
        if (!obj || !obj->baseForm) {
            return NULL;
        } else {
            return DYNAMIC_CAST(obj->baseForm, TESForm, TESContainer);
        }
    }

    XContainer_t *Get_XContainer(TESObjectREFR *obj, bool do_create) {
        if (obj) {
            if (do_create) {
                Init_Container_If_Needed(obj);
            }
            XContainer_t* xcontainer = static_cast<XContainer_t*>
                (obj->extraData.GetByType(kExtraData_ContainerChanges));
            if (xcontainer && !xcontainer->changes) {
                Init_Container_If_Needed(obj);
                xcontainer = static_cast<XContainer_t*>
                    (obj->extraData.GetByType(kExtraData_ContainerChanges));
            }
            return xcontainer;
        } else {
            return nullptr;
        }
    }

    void Validate_XContainer(Reference_t* ref)
    {
        if (ref) {
            XContainer_t* xcontainer = Get_XContainer(ref, false);
            if (xcontainer) {
                xcontainer->changes->Validate();
            }
        }
    }

    Worldspace_t* Worldspace(Reference_t* ref)
    {
        static auto worldspace = reinterpret_cast
            <Worldspace_t* (*)(Reference_t*)>
            (RelocationManager::s_baseAddr + Offsets::Reference::WORLDSPACE);

        if (ref) {
            return worldspace(ref);
        } else {
            return nullptr;
        }
    }

    Location_t* Location(Reference_t* ref)
    {
        if (ref) {
            Cell_t* cell = Cell(ref);
            if (cell) {
                ExtraLocation* xlocation = static_cast<ExtraLocation*>
                    (reinterpret_cast<XList_t*>(&cell->unk048)->GetByType(kExtraData_Location));
                return xlocation ? xlocation->location : nullptr;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Cell_t* Cell(Reference_t* ref)
    {
        if (ref) {
            return ref->parentCell;
        } else {
            return nullptr;
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

        XContainer_t *xcontainer = Get_XContainer(obj, do_create);
        if (do_create) {
            NPCP_ASSERT(xcontainer);
        }

        if (xcontainer) {
            for (XEntries_t::Iterator it = xcontainer->changes->xentries->Begin(); !it.End(); ++it) {
                XEntry_t *entry = it.Get();
                if (entry && entry->form == form) {
                    return entry;
                }
            }
            if (do_create) {
                XEntry_t *entry_new = XEntry_t::Create(form, 0);
                xcontainer->Add_XEntry(entry_new, obj);
                return entry_new;
            }
        }

        return NULL;
    }

    void Add_XEntry(Reference_t* ref, XEntry_t* to_add) {
        if (ref && to_add) {
            XContainer_t* xcontainer_obj = Get_XContainer(ref, true);
            NPCP_ASSERT(xcontainer_obj);
            xcontainer_obj->Add_XEntry(to_add, ref);
        }
    }

    void Remove_XEntry(Reference_t* ref, XEntry_t* to_remove) {
        if (ref && to_remove) {
            XContainer_t* xcontainer = Get_XContainer(ref, false);
            if (xcontainer) {
                xcontainer->Remove_XEntry(to_remove);
            }
        }
    }

    bool Has_XEntry(TESObjectREFR *obj, TESForm *form) {
        return Get_XEntry(obj, form, false) != NULL;
    }

    Bool_t Has_Similar_XList(Reference_t* ref, Form_t* form, XList_t* xlist_to_compare)
    {
        if (ref) {
            XContainer_t* xcontainer = Get_XContainer(ref, false);
            if (xcontainer) {
                XEntry_t* xentry = xcontainer->XEntry(form, false);
                if (xentry) {
                    return xentry->Has_Similar_XList(xlist_to_compare);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Int_t Get_BEntry_Count(Reference_t* ref, Form_t* form)
    {
        if (ref && form) {
            BContainer_t* bcontainer = Get_BContainer(ref);
            Int_t count = 0;
            if (bcontainer) {
                for (size_t idx = 0, count = bcontainer->numEntries; idx < count; idx += 1) {
                    BEntry_t* bentry = bcontainer->entries[idx];
                    if (bentry && bentry->form == form) {
                        count += bentry->count;
                    }
                }
            }
            return count < 0 ? 1 : count;
        } else {
            return 0;
        }
    }

    Int_t Get_XEntry_Count(Reference_t* obj, Form_t* form)
    {
        if (obj && form) {
            XEntry_t* xentry = Get_XEntry(obj, form, false);
            if (xentry) {
                return xentry->Delta_Count();
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    Int_t Get_Entry_Count(Reference_t* obj, Form_t* form)
    {
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
                if (Utils::Is_Bit_On(info->alias->flags, 2)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool Is_Worn(TESObjectREFR *obj, TESForm *form) {
        if (obj && form) {
            XEntry_t* xentry = Get_XEntry(obj, form);
            return xentry && xentry->Has_Worn_XList();
        } else {
            return false;
        }
    }

    void Remove_If(Reference_t* from,
                   Reference_t* to,
                   Bool_t(*should_remove_xform)(Form_t*),
                   Bool_t(*should_remove_xlist)(XList_t*, Form_t*),
                   Bool_t(*should_remove_bform)(Form_t*))
    {
        NPCP_ASSERT(from);

        Bool_t do_delete_to;
        if (to) {
            Init_Container_If_Needed(to);
            do_delete_to = false;
        } else {
            to = Create_Container();
            do_delete_to = true;
        }

        if (!should_remove_xform) {
            should_remove_xform = [](Form_t*) -> Bool_t
            {
                return true;
            };
        }

        if (!should_remove_xlist) {
            should_remove_xlist = [](XList_t* xlist, Form_t*) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        if (!should_remove_bform) {
            should_remove_bform = should_remove_xform;
        }

        XContainer_t* xcontainer = Object_Ref::Get_XContainer(from, false);
        if (xcontainer) {
            std::vector<XEntry_t*> xentries_to_destroy;
            xentries_to_destroy.reserve(4);

            for (XEntries_t::Iterator xentries = xcontainer->changes->xentries->Begin(); !xentries.End(); ++xentries) {
                XEntry_t* xentry = xentries.Get();
                if (xentry) {
                    Form_t* form = xentry->form;
                    if (form) {
                        if (should_remove_xform(form)) {
                            std::vector<XList_t*> xlists_to_remove;
                            xlists_to_remove.reserve(2);

                            for (XLists_t::Iterator xlists = xentry->xlists->Begin(); !xlists.End(); ++xlists) {
                                XList_t* xlist = xlists.Get();
                                if (xlist) {
                                    XList::Validate(xlist, xentry->delta_count, Get_BEntry_Count(from, xentry->form));
                                    if (should_remove_xlist(xlist, form)) {
                                        xlists_to_remove.push_back(xlist);
                                    }
                                }
                            }

                            if (xlists_to_remove.size() > 0) {
                                XEntry_t* to_xentry = Object_Ref::Get_XEntry(to, form, true);
                                for (size_t idx = 0, count = xlists_to_remove.size(); idx < count; idx += 1) {
                                    XList_t* xlist = xlists_to_remove[idx];
                                    xentry->Move_XList(to_xentry, to, xlist);
                                }
                            }
                        }

                        if (xentry->Delta_Count() == 0) {
                            xentries_to_destroy.push_back(xentry);
                        }
                    } else {
                        xentries_to_destroy.push_back(xentry);
                    }
                }
            }

            for (size_t idx = 0, count = xentries_to_destroy.size(); idx < count; idx += 1) {
                XEntry_t* xentry = xentries_to_destroy[idx];
                Object_Ref::Remove_XEntry(from, xentry);
                XEntry_t::Destroy(xentry);
            }
        }

        BContainer_t* bcontainer = Object_Ref::Get_BContainer(from);
        if (bcontainer) {
            std::vector<BEntry_t*> bentries_to_move;
            bentries_to_move.reserve(4);

            for (size_t idx = 0, count = bcontainer->numEntries; idx < count; idx += 1) {
                BEntry_t* bentry = bcontainer->entries[idx];
                if (bentry && bentry->form && bentry->count > 0) {
                    Form_t* form = bentry->form;
                    if (form->formType != kFormType_LeveledItem && should_remove_bform(form)) {
                        bentries_to_move.push_back(bentry);
                    }
                }
            }

            if (bentries_to_move.size() > 0) {
                for (size_t idx = 0, count = bentries_to_move.size(); idx < count; idx += 1) {
                    BEntry_t* bentry = bentries_to_move[idx];
                    XEntry_t* xentry = Get_XEntry(from, bentry->form, true);
                    Int_t entry_count = bentry->count + xentry->Delta_Count();
                    if (entry_count > 0) {
                        XEntry_t* to_xentry = Get_XEntry(to, bentry->form, true);

                        to_xentry->Increment(entry_count);
                        xentry->Delta_Count(0 - bentry->count);
                    }
                }
            }
        }

        if (do_delete_to) {
            Delete_Safe(to);
        }
    }

    void Remove_Wearables(Reference_t* obj, Reference_t* other, Bool_t remove_quest_items)
    {
        auto should_remove_xform = [](Form_t* form) -> Bool_t
        {
            return form->IsArmor() || form->IsWeapon() || form->IsAmmo();
        };

        Bool_t (*should_remove_xlist)(XList_t*, Form_t*);
        if (remove_quest_items) {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        Remove_If(obj, other, should_remove_xform, should_remove_xlist);
    }

    void Remove_Unwearables(Reference_t* obj, Reference_t* other, Bool_t remove_quest_items)
    {
        auto should_remove_xform = [](Form_t* form) -> Bool_t
        {
            return !form->IsArmor() && !form->IsWeapon() && !form->IsAmmo();
        };

        Bool_t(*should_remove_xlist)(XList_t*, Form_t*);
        if (remove_quest_items) {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        Remove_If(obj, other, should_remove_xform, should_remove_xlist);
    }

    void Remove_Non_Outfit_Worn(Reference_t* obj, Reference_t* other, Bool_t remove_quest_items)
    {
        auto should_remove_xform = [](Form_t* form) -> Bool_t
        {
            return true;
        };

        Bool_t(*should_remove_xlist)(XList_t*, Form_t*);
        if (remove_quest_items) {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        auto should_remove_bform = [](Form_t* form) -> Bool_t
        {
            return false;
        };

        Remove_If(obj, other, should_remove_xform, should_remove_xlist, should_remove_bform);
    }

    void Remove_All_Items(Reference_t* ref, Reference_t* transfer, Bool_t remove_quest_items, Bool_t remove_unplayable_items)
    {
        Bool_t(*should_remove_xform)(Form_t*);
        if (remove_unplayable_items) {
            should_remove_xform = [](Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xform = [](Form_t* form) -> Bool_t
            {
                return form->IsPlayable();
            };
        }

        Bool_t(*should_remove_xlist)(XList_t*, Form_t*);
        if (remove_quest_items) {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        Remove_If(ref, transfer, should_remove_xform, should_remove_xlist);
    }

    Bool_t Contains_Form(Reference_t* ref, Form_t* form)
    {
        if (ref && form) {
            BContainer_t* bcontainer = Object_Ref::Get_BContainer(ref);
            if (bcontainer) {
                for (size_t idx = 0, count = bcontainer->numEntries; idx < count; idx += 1) {
                    BEntry_t* bentry = bcontainer->entries[idx];
                    if (bentry && bentry->form == form && bentry->count > 0) {
                        XEntry_t* xentry = Get_XEntry(ref, form, false);
                        if (!xentry || xentry->Delta_Count() > 0 - bentry->count) {
                            return true;
                        }
                    }
                }
            }
            XContainer_t* xcontainer = Object_Ref::Get_XContainer(ref, false);
            if (xcontainer) {
                for (XEntries_t::Iterator it = xcontainer->changes->xentries->Begin(); !it.End(); ++it) {
                    XEntry_t* xentry = it.Get();
                    if (xentry && xentry->form == form && xentry->Delta_Count() > 0) {
                        return true;
                    }
                }
            }
            return false;
        } else {
            return false;
        }
    }

    void Categorize(Reference_t *ref, Bool_t only_custom_categories) {
        if (ref) {
            Vector_t<XEntry_t*> xentries_to_destroy;
            xentries_to_destroy.reserve(2);

            XContainer_t* xcontainer = Get_XContainer(ref, false);
            if (xcontainer) {
                Init_Container_If_Needed(ref);
                for (XEntries_t::Iterator it = xcontainer->changes->xentries->Begin(); !it.End(); ++it) {
                    XEntry_t* xentry = it.Get();
                    if (xentry && xentry->form && xentry->form->IsPlayable()) {
                        Reference_t* category = only_custom_categories ?
                            Game::Get_NPCP_Custom_Category(xentry->form) :
                            Game::Get_NPCP_Category(xentry->form);
                        if (category && category != ref) {
                            Int_t bentry_count = Get_BEntry_Count(ref, xentry->form);
                            xentry->Validate(bentry_count);

                            XEntry_t* category_xentry = nullptr;

                            Vector_t<XList_t*> xlists_to_move;
                            xlists_to_move.reserve(2);
                            for (XLists_t::Iterator it = xentry->xlists->Begin(); !it.End(); ++it) {
                                XList_t* xlist = it.Get();
                                if (xlist) {
                                    xlists_to_move.push_back(xlist);
                                }
                            }

                            size_t xlists_to_move_count = xlists_to_move.size();
                            if (xlists_to_move_count > 0) {
                                category_xentry = Get_XEntry(category, xentry->form, true);
                                NPCP_ASSERT(category_xentry);
                                for (size_t idx = 0; idx < xlists_to_move_count; idx += 1) {
                                    XList_t* xlist = xlists_to_move[idx];
                                    xentry->Move_XList(category_xentry, category, xlist);
                                }
                            }
                            
                            Int_t bentry_negation = 0 - bentry_count;
                            if (xentry->Delta_Count() < bentry_negation) {
                                xentry->Delta_Count(bentry_negation);
                            }

                            if (xentry->Delta_Count() > bentry_negation) {
                                if (!category_xentry) {
                                    category_xentry = Get_XEntry(category, xentry->form, true);
                                    NPCP_ASSERT(category_xentry);
                                }
                                category_xentry->Increment(xentry->Delta_Count() - bentry_negation);
                                xentry->Delta_Count(bentry_negation);
                            }

                            if (xentry->Delta_Count() == 0) {
                                xentries_to_destroy.push_back(xentry);
                            }
                        }
                    }
                }
            }

            for (size_t idx = 0, count = xentries_to_destroy.size(); idx < count; idx += 1) {
                XEntry_t* xentry = xentries_to_destroy[idx];
                Remove_XEntry(ref, xentry);
                XEntry_t::Destroy(xentry);
            }

            BContainer_t* bcontainer = Object_Ref::Get_BContainer(ref);
            if (bcontainer) {
                for (size_t idx = 0; idx < bcontainer->numEntries; idx += 1) {
                    BEntry_t* bentry = bcontainer->entries[idx];
                    if (bentry && bentry->form && bentry->count > 0) {
                        if (bentry->form->IsPlayable() && bentry->form->formType != kFormType_LeveledItem) {
                            if (Get_XEntry(ref, bentry->form, false) == nullptr) {
                                Reference_t* category = only_custom_categories ?
                                    Game::Get_NPCP_Custom_Category(bentry->form) :
                                    Game::Get_NPCP_Category(bentry->form);
                                if (category && category != ref) {
                                    XEntry_t* category_xentry = Get_XEntry(category, bentry->form, true);
                                    NPCP_ASSERT(category_xentry);
                                    category_xentry->Increment(bentry->count);
                                    XEntry_t* xentry = Get_XEntry(ref, bentry->form, true);
                                    NPCP_ASSERT(xentry);
                                    xentry->Delta_Count(0 - bentry->count);
                                }
                            }
                        }
                    }
                }
            }
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

        XContainer_t *xcontainer = Object_Ref::Get_XContainer(ref_object, false);
        if (xcontainer) {
            for (XEntries_t::Iterator it_xentry = xcontainer->changes->xentries->Begin(); !it_xentry.End(); ++it_xentry) {
                XEntry_t *xentry = it_xentry.Get();
                if (xentry) {
                    xentry->Log("    ");
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

        float angle_radians = target->rot.z - (angle_degree * DOTICU_NPCP_PI / 180.0f);
        NiPoint3 obj_pos(
            target->pos.x + radius * sin(angle_radians),
            target->pos.y + radius * cos(angle_radians),
            target->pos.z
        );
        NiPoint3 obj_rot(
            0.0,
            0.0,
            target->rot.z + ((180.0f - angle_degree) * DOTICU_NPCP_PI / 180.0f)
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
                    XEntry_t::Destroy(xentry);
                }
            } else {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, true);
                if (xentry) {
                    if (xentry->Delta_Count() + bentry_count != count) {
                        xentry->Delta_Count(count - bentry_count);
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
                    XEntry_t::Destroy(xentry);
                }
            } else {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, true);
                if (xentry) {
                    if (xentry->Delta_Count() + bentry_count != 0) {
                        xentry->Delta_Count(0 - bentry_count);
                    }
                } else {
                    _MESSAGE("unable to get xentry for removing token.");
                }
            }
        }
    }

    void Block_Activation(Reference_t* ref)
    {
        if (ref) {
            ExtraFlags* xflags = static_cast<ExtraFlags*>(ref->extraData.GetByType(kExtraData_Flags));
            if (xflags) {
                xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_ACTIVATION);
            } else {
                xflags = XData::Create_Flags();
                if (xflags) {
                    ref->extraData.Add(kExtraData_Flags, xflags);
                    xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_ACTIVATION);
                }
            }
        }
    }

    void Unblock_Activation(Reference_t* ref)
    {
        if (ref) {
            ExtraFlags* xflags = static_cast<ExtraFlags*>(ref->extraData.GetByType(kExtraData_Flags));
            if (xflags) {
                xflags->flags = Utils::Bit_Off(xflags->flags, ExtraFlags::BLOCKS_ACTIVATION);
            }
        }
    }

    void Block_Player_Activation(Reference_t* ref)
    {
        if (ref) {
            ExtraFlags* xflags = static_cast<ExtraFlags*>(ref->extraData.GetByType(kExtraData_Flags));
            if (xflags) {
                xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_PLAYER_ACTIVATION);
            } else {
                xflags = XData::Create_Flags();
                if (xflags) {
                    ref->extraData.Add(kExtraData_Flags, xflags);
                    xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_PLAYER_ACTIVATION);
                }
            }
        }
    }

    void Unblock_Player_Activation(Reference_t* ref)
    {
        if (ref) {
            ExtraFlags* xflags = static_cast<ExtraFlags*>(ref->extraData.GetByType(kExtraData_Flags));
            if (xflags) {
                xflags->flags = Utils::Bit_Off(xflags->flags, ExtraFlags::BLOCKS_PLAYER_ACTIVATION);
            }
        }
    }

    void Block_All_Activation(Reference_t* ref)
    {
        if (ref) {
            ExtraFlags* xflags = static_cast<ExtraFlags*>(ref->extraData.GetByType(kExtraData_Flags));
            if (xflags) {
                xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_ACTIVATION);
                xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_PLAYER_ACTIVATION);
            } else {
                xflags = XData::Create_Flags();
                if (xflags) {
                    ref->extraData.Add(kExtraData_Flags, xflags);
                    xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_ACTIVATION);
                    xflags->flags = Utils::Bit_On(xflags->flags, ExtraFlags::BLOCKS_PLAYER_ACTIVATION);
                }
            }
        }
    }

    void Unblock_All_Activation(Reference_t* ref)
    {
        if (ref) {
            ExtraFlags* xflags = static_cast<ExtraFlags*>(ref->extraData.GetByType(kExtraData_Flags));
            if (xflags) {
                xflags->flags = Utils::Bit_Off(xflags->flags, ExtraFlags::BLOCKS_ACTIVATION);
                xflags->flags = Utils::Bit_Off(xflags->flags, ExtraFlags::BLOCKS_PLAYER_ACTIVATION);
            }
        }
    }

    void Block_Activation(Reference_t* ref, Bool_t do_block, Virtual_Callback_i* vcallback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Bool_t do_block;
            Arguments(Bool_t do_block) :
                do_block(do_block)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Bool(do_block);
                return true;
            }
        } arguments(do_block);
        Virtual_Machine_t::Self()->Call_Method(
            ref,
            "ObjectReference",
            "BlockActivation",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    void Play_Animation(Reference_t* ref, void* nicontroller, void* nisequence_from, void* nisequence_to)
    {
        using func_type = void(*)(Reference_t*, void*, void*, void*);
        static func_type func = reinterpret_cast<func_type>
            (RelocationManager::s_baseAddr + Offsets::Reference::PLAY_ANIMATION);

        if (ref && nicontroller && nisequence_from && nisequence_to) {
            return func(ref, nicontroller, nisequence_to, nisequence_from); // these are backwards I guess.
        }
    }

    void Rename(Reference_t* ref, String_t new_name)
    {
        if (ref && new_name.data) {
            XList::Validate_No_Count(&ref->extraData);
            referenceUtils::SetDisplayName(&ref->extraData, new_name, true);
        }

        /*if (ref) {
            XList::Validate(&ref->extraData);
            ExtraTextDisplay* xtext = static_cast<ExtraTextDisplay*>(ref->extraData.GetByType(kExtraData_TextDisplayData));
            if (xtext) {
                xtext->Force_Rename(new_name);
            } else {
                xtext = XData::Create_Text_Display(new_name);
                if (xtext) {
                    ref->extraData.Add(kExtraData_TextDisplayData, xtext);
                }
            }
        }*/
    }

    void Init_Container_If_Needed(Reference_t* ref)
    {
        if (ref) {
            XContainer_t* xcontainer = static_cast<XContainer_t*>
                (ref->extraData.GetByType(kExtraData_ContainerChanges));
            if (!xcontainer || !xcontainer->changes) {
                Weapon_t* blank_weapon = Consts::Blank_Weapon();
                ref->Equip_Weapon(blank_weapon, 0, false, 0, 0);
                XEntry_t* xentry = Get_XEntry(ref, blank_weapon, false);
                if (xentry) {
                    Remove_XEntry(ref, xentry);
                    XEntry_t::Destroy(xentry);
                }
            }
        }
    }

    void Open_Container(Reference_t* ref, Papyrus::Virtual_Callback_i** callback)
    {
        using namespace Papyrus;

        NPCP_ASSERT(ref && ref->baseForm && ref->baseForm->formType == kFormType_Container);

        class Arguments : public Virtual_Arguments_t {
        public:
            Reference_t* ref;
            Arguments(Reference_t* ref) :
                ref(ref)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Pack(ref);
                return true;
            }
        } arguments(ref);

        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(), "doticu_npcp_funcs", "Open_Container", &arguments, callback);
    }

    void Activate(Reference_t* ref,
                  Reference_t* activator,
                  Bool_t do_default_processing_only,
                  Papyrus::Virtual_Callback_i** callback)
    {
        using namespace Papyrus;

        class Arguments : public Virtual_Arguments_t {
        public:
            Reference_t* activator;
            Bool_t do_default_processing_only;
            Arguments(Reference_t* activator, Bool_t do_default_processing_only) :
                activator(activator), do_default_processing_only(do_default_processing_only)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(2);
                arguments->At(0)->Pack(activator);
                arguments->At(1)->Bool(do_default_processing_only);
                return true;
            }
        } arguments(activator, do_default_processing_only);

        Virtual_Machine_t::Self()->Call_Method(ref, "ObjectReference", "Activate", &arguments, callback);
    }

    Reference_t* Place_At_Me(Reference_t* me,
                             Form_t* to_place,
                             Int_t count,
                             Bool_t force_persist,
                             Bool_t initially_disabled)
    {
        using namespace Papyrus;
        static auto place_at_me = reinterpret_cast
            <Reference_t * (*)(Virtual_Machine_t*, Stack_ID_t, Reference_t*, Form_t*, Int_t, Bool_t, Bool_t)>
            (RelocationManager::s_baseAddr + Offsets::Reference::PLACE_AT_ME);

        Reference_t* reference = place_at_me(Virtual_Machine_t::Self(), 0, me, to_place, count, force_persist, initially_disabled);
        NPCP_ASSERT(reference);
        XList::Validate_No_Count(&reference->extraData);
        return reference;
    }

    void Add_Item(Reference_t* ref, Form_t* form, Int_t count, Bool_t do_silently)
    {
        using namespace Papyrus;
        static auto add_item = reinterpret_cast
            <void (*)(Virtual_Machine_t*, Stack_ID_t, Reference_t*, Form_t*, Int_t, Bool_t)>
            (RelocationManager::s_baseAddr + Offsets::Reference::ADD_ITEM);
        static Variable_t none;
        Virtual_Machine_t* virtual_machine = Virtual_Machine_t::Self();
        add_item(virtual_machine, 0, ref, form, count, do_silently);
        virtual_machine->Return_Latent_Function(0, &none);
    }

    Reference_t* From_Handle(Reference_Handle_t handle)
    {
        static auto lookup_reference_handle = reinterpret_cast
            <Reference_t* (*)(Reference_Handle_t&, NiPointer<Reference_t>&)>
            (RelocationManager::s_baseAddr + Offsets::Reference::LOOKUP_REFERENCE_BY_HANDLE1);

        NiPointer<Reference_t> ptr;
        lookup_reference_handle(handle, ptr);
        return ptr.get();
    }

    Reference_t* Create_Marker_At(Reference_t* ref)
    {
        if (ref) {
            Reference_t* marker = Place_At_Me(ref, Consts::X_Marker_Static(), 1, true, false);
            if (marker) {
                marker->pos.x = ref->pos.x;
                marker->pos.y = ref->pos.y;
                marker->pos.z = ref->pos.z;
                marker->rot.x = ref->rot.x;
                marker->rot.y = ref->rot.y;
                marker->rot.z = ref->rot.z;
                marker->Update_3D_Position();
                return marker;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Reference_t* Create_Container()
    {
        Reference_t* container = Place_At_Me(Consts::Storage_Marker(), Consts::Empty_Container(), 1, true, false);
        NPCP_ASSERT(container);
        Init_Container_If_Needed(container);
        return container;
    }

    void Delete_Safe(Reference_t* ref)
    {
        using namespace Papyrus;

        if (ref) {
            ref->Disable();
            Enable(ref);
            Virtual_Machine_t::Self()->Call_Method(ref, "ObjectReference", "Delete");
        }
    }

    void Enable(Reference_t* ref, Bool_t do_fade_in, Virtual_Callback_i** callback)
    {
        NPCP_ASSERT(ref);

        class Arguments : public Virtual_Arguments_t {
        public:
            Bool_t do_fade_in;
            Arguments(Bool_t do_fade_in) :
                do_fade_in(do_fade_in)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Bool(do_fade_in);
                return true;
            }
        } arguments(do_fade_in);

        Virtual_Machine_t::Self()->Call_Method(ref, "ObjectReference", "Enable", &arguments, callback);
    }

    void Disable(Reference_t* ref, Bool_t do_fade_out, Virtual_Callback_i** callback)
    {
        NPCP_ASSERT(ref);

        class Arguments : public Virtual_Arguments_t {
        public:
            Bool_t do_fade_out;
            Arguments(Bool_t do_fade_out) :
                do_fade_out(do_fade_out)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Bool(do_fade_out);
                return true;
            }
        } arguments(do_fade_out);

        Virtual_Machine_t::Self()->Call_Method(ref, "ObjectReference", "Disable", &arguments, callback);
    }

    bool Is_In_Interior_Cell(Reference_t* ref)
    {
        if (ref) {
            return ref->parentCell && Cell::Is_Interior(ref->parentCell);
        } else {
            return false;
        }
    }

    bool Is_In_Exterior_Cell(Reference_t* ref)
    {
        if (ref) {
            return ref->parentCell && Cell::Is_Exterior(ref->parentCell);
        } else {
            return false;
        }
    }

    UInt32 Ref_Count(Reference_t* ref)
    {
        NPCP_ASSERT(ref);
        return ref->handleRefObject.m_uiRefCount & 0x3FF;
    }

    void Add_Item_And_Callback(Reference_t* ref,
                               Form_t* form,
                               Int_t count,
                               Bool_t do_sounds,
                               Papyrus::Virtual_Callback_i** callback)
    {
        using namespace Papyrus;

        static String_t class_name = "ObjectReference";
        static String_t function_name = "AddItem";

        struct Args : public Virtual_Arguments_i {
            Form_t* form;
            Int_t count;
            Bool_t do_sounds;

            Args(Form_t* form, Int_t count, Bool_t do_sounds) :
                form(form), count(count), do_sounds(do_sounds)
            {
            }

            virtual Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(3);
                arguments->At(0)->Pack(form);
                arguments->At(1)->Int(count);
                arguments->At(2)->Bool(do_sounds);
                return true;
            }
        } args(form, count, do_sounds);

        Virtual_Machine_t::Self()->Call_Method(ref, class_name, function_name, &args, callback);
    }

    void Remove_Item_And_Callback(Reference_t* ref,
                                  Form_t* form,
                                  Int_t count,
                                  Bool_t do_sounds,
                                  Reference_t* destination,
                                  Papyrus::Virtual_Callback_i** callback)
    {
        using namespace Papyrus;

        static String_t class_name = "ObjectReference";
        static String_t function_name = "RemoveItem";

        struct Args : public Virtual_Arguments_i {
            Form_t* form;
            Int_t count;
            Bool_t do_sounds;
            Reference_t* destination;

            Args(Form_t* form, Int_t count, Bool_t do_sounds, Reference_t* destination) :
                form(form), count(count), do_sounds(do_sounds), destination(destination)
            {
            }

            virtual Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(4);
                arguments->At(0)->Pack(form);
                arguments->At(1)->Int(count);
                arguments->At(2)->Bool(do_sounds);
                arguments->At(3)->Pack(destination);
                return true;
            }
        } args(form, count, do_sounds, destination);

        Virtual_Machine_t::Self()->Call_Method(ref, class_name, function_name, &args, callback);
    }

    void Find_Closest_Actor_From(Reference_t* ref, Float_t radius, Virtual_Callback_i** callback)
    {
        class Arguments : public Virtual_Arguments_t {
        public:
            Reference_t* ref;
            Float_t radius;
            Arguments(Reference_t* ref, Float_t radius) :
                ref(ref), radius(radius)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(2);
                arguments->At(0)->Pack(ref);
                arguments->At(1)->Float(radius);
                return true;
            }
        } arguments(ref, radius);

        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(),
                                               "doticu_npcp_funcs",
                                               "Find_Closest_Actor_From",
                                               &arguments,
                                               callback);
    }

    void Translate_To(Reference_t* ref,
                      Float_t pos_degree_x,
                      Float_t pos_degree_y,
                      Float_t pos_degree_z,
                      Float_t rot_degree_x,
                      Float_t rot_degree_y,
                      Float_t rot_degree_z,
                      Float_t pos_speed,
                      Float_t rot_speed,
                      Virtual_Callback_i** callback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Float_t pos_degree_x;
            Float_t pos_degree_y;
            Float_t pos_degree_z;
            Float_t rot_degree_x;
            Float_t rot_degree_y;
            Float_t rot_degree_z;
            Float_t pos_speed;
            Float_t rot_speed;
            Arguments(Float_t pos_degree_x,
                      Float_t pos_degree_y,
                      Float_t pos_degree_z,
                      Float_t rot_degree_x,
                      Float_t rot_degree_y,
                      Float_t rot_degree_z,
                      Float_t pos_speed,
                      Float_t rot_speed) :
                pos_degree_x(pos_degree_x),
                pos_degree_y(pos_degree_y),
                pos_degree_z(pos_degree_z),
                rot_degree_x(rot_degree_x),
                rot_degree_y(rot_degree_y),
                rot_degree_z(rot_degree_z),
                pos_speed(pos_speed),
                rot_speed(rot_speed)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(8);
                arguments->At(0)->Float(pos_degree_x);
                arguments->At(1)->Float(pos_degree_y);
                arguments->At(2)->Float(pos_degree_z);
                arguments->At(3)->Float(rot_degree_x);
                arguments->At(4)->Float(rot_degree_y);
                arguments->At(5)->Float(rot_degree_z);
                arguments->At(6)->Float(pos_speed);
                arguments->At(7)->Float(rot_speed);
                return true;
            }
        } arguments(
            pos_degree_x,
            pos_degree_y,
            pos_degree_z,
            rot_degree_x,
            rot_degree_y,
            rot_degree_z,
            pos_speed,
            rot_speed
        );

        Virtual_Machine_t::Self()->Call_Method(
            ref,
            "ObjectReference",
            "TranslateTo",
            &arguments,
            callback
        );
    }

    void Stop_Translation(Reference_t* ref, Virtual_Callback_i** callback)
    {
        Virtual_Machine_t::Self()->Call_Method(
            ref,
            "ObjectReference",
            "StopTranslation",
            nullptr,
            callback
        );
    }

    void Push_Actor_Away(Reference_t* ref, Actor_t* actor, Float_t knockback_force, Virtual_Callback_i** vcallback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Actor_t* actor;
            Float_t knockback_force;
            Arguments(Actor_t* actor, Float_t knockback_force) :
                actor(actor), knockback_force(knockback_force)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(2);
                arguments->At(0)->Pack(actor);
                arguments->At(1)->Float(knockback_force);
                return true;
            }
        } arguments(actor, knockback_force);
        Virtual_Machine_t::Self()->Call_Method(
            ref,
            "ObjectReference",
            "PushActorAway",
            &arguments,
            vcallback
        );
    }

    void Apply_Havok_Impulse(Reference_t* ref, Float_t x, Float_t y, Float_t z, Float_t magnitude, Virtual_Callback_i** vcallback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Float_t x;
            Float_t y;
            Float_t z;
            Float_t magnitude;
            Arguments(Float_t x, Float_t y, Float_t z, Float_t magnitude) :
                x(x), y(y), z(z), magnitude(magnitude)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(4);
                arguments->At(0)->Float(x);
                arguments->At(1)->Float(y);
                arguments->At(2)->Float(z);
                arguments->At(3)->Float(magnitude);
                return true;
            }
        } arguments(x, y, z, magnitude);
        Virtual_Machine_t::Self()->Call_Method(
            ref,
            "ObjectReference",
            "ApplyHavokImpulse",
            &arguments,
            vcallback
        );
    }

    void Set_Open(Reference_t* ref, Bool_t is_open, Virtual_Callback_i* vcallback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Bool_t is_open;
            Arguments(Bool_t is_open) :
                is_open(is_open)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Bool(is_open);
                return true;
            }
        } arguments(is_open);
        Virtual_Machine_t::Self()->Call_Method(
            ref,
            "ObjectReference",
            "SetOpen",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    Inventory_t::Inventory_t(Reference_t* reference)
        : reference(reference)
    {
        if (reference) {
            Init_Container_If_Needed(reference);
            xcontainer = static_cast<XContainer_t*>
                (reference->extraData.GetByType(kExtraData_ContainerChanges));
            NPCP_ASSERT(xcontainer);

            bcontainer = reference->baseForm ?
                DYNAMIC_CAST(reference->baseForm, TESForm, TESContainer) : nullptr;
            if (bcontainer) {
                for (size_t idx = 0; idx < bcontainer->numEntries; idx += 1) {
                    BEntry_t* bentry = bcontainer->entries[idx];
                    if (bentry && bentry->form && bentry->count > 0) {
                        Int_t bentry_count = bentry->count;
                        if (bentry_count < 0) {
                            bentry_count = 1;
                        }
                        Entry_t* entry = Entry(bentry->form);
                        if (entry) {
                            entry->bentry_count += bentry_count;
                            if (entry->bentry_count < 0) {
                                entry->bentry_count = std::numeric_limits<Int_t>::max();
                            }
                        } else {
                            Entry_t entry;
                            entry.form = bentry->form;
                            entry.bentry_count = bentry_count;
                            entry.xentry = nullptr;
                            entry.xlist_count = 0;
                            entries.push_back(entry);
                        }
                    }
                }
            }

            Vector_t<XEntry_t*> xentries_to_destroy;
            xentries_to_destroy.reserve(4);
            for (XEntries_t::Iterator it = xcontainer->changes->xentries->Begin(); !it.End(); ++it) {
                XEntry_t* xentry = it.Get();
                if (xentry && xentry->form) {
                    Entry_t* entry = Entry(xentry->form);
                    if (entry) {
                        Int_t xlist_count = xentry->Validate(entry->bentry_count);
                        if (entry->xentry) {
                            if (xentry->xlists) {
                                Vector_t<XList_t*> xlists_to_move;
                                xlists_to_move.reserve(2);
                                for (XLists_t::Iterator it = xentry->xlists->Begin(); !it.End(); ++it) {
                                    XList_t* xlist = it.Get();
                                    if (xlist) {
                                        xlists_to_move.push_back(xlist);
                                    }
                                }
                                for (size_t idx = 0, count = xlists_to_move.size(); idx < count; idx += 1) {
                                    XList_t* xlist = xlists_to_move[idx];
                                    xentry->Move_XList(entry->xentry, reference, xlist);
                                }
                                entry->xlist_count += xlist_count;
                                if (entry->xlist_count < 0) {
                                    entry->xlist_count = std::numeric_limits<Int_t>::max();
                                }
                            }
                            if (xentry->delta_count + entry->bentry_count > 0) {
                                entry->xentry->delta_count += xentry->delta_count + entry->bentry_count;
                            }
                            if (entry->xentry->delta_count + entry->bentry_count < 0) {
                                entry->xentry->delta_count = std::numeric_limits<Int_t>::max() - entry->bentry_count;
                            }
                            xentries_to_destroy.push_back(xentry);
                        } else {
                            entry->xentry = xentry;
                            entry->xlist_count = xlist_count;
                        }
                    } else {
                        Int_t xlist_count = xentry->Validate(0);
                        Entry_t entry;
                        entry.form = xentry->form;
                        entry.bentry_count = 0;
                        entry.xentry = xentry;
                        entry.xlist_count = xlist_count;
                        entries.push_back(entry);
                    }
                }
            }
            for (size_t idx = 0, count = xentries_to_destroy.size(); idx < count; idx += 1) {
                XEntry_t* xentry = xentries_to_destroy[idx];
                xcontainer->changes->Remove_XEntry(xentry);
                XEntry_t::Destroy(xentry);
            }
        }
    }

    Entry_t* Inventory_t::Entry(Form_t* form)
    {
        if (reference && form) {
            for (size_t idx = 0, count = entries.size(); idx < count; idx += 1) {
                Entry_t* entry = &entries[idx];
                if (entry->form == form) {
                    return entry;
                }
            }
            return nullptr;
        } else {
            return nullptr;
        }
    }

    Entry_t* Inventory_t::Add_Entry(Form_t* form)
    {
        if (reference && form) {
            Entry_t* entry = Entry(form);
            if (entry) {
                return entry;
            } else {
                Entry_t entry;
                entry.form = form;
                entry.bentry_count = 0;
                entry.xentry = nullptr;
                entry.xlist_count = 0;
                entries.push_back(entry);
                return &entries.back();
            }
        } else {
            return nullptr;
        }
    }

    Int_t Inventory_t::Find(Entry_t* entry)
    {
        if (reference && entry) {
            for (size_t idx = 0, count = entries.size(); idx < count; idx += 1) {
                if (&entries[idx] == entry) {
                    return idx;
                }
            }
            return -1;
        } else {
            return -1;
        }
    }

    void Inventory_t::Validate(Entry_t* entry)
    {
        if (reference && entry) {
            NPCP_ASSERT(entry->form);

            //entry->bentry_count = Get_BEntry_Count(reference, entry->form);
            //entry->xentry = Get_XEntry(reference, entry->form, false);
            if (entry->xentry) {
                entry->xlist_count = entry->xentry->Validate(entry->bentry_count);
            } else {
                entry->xlist_count = 0;
            }
        }
    }

    Int_t Inventory_t::Count(Entry_t* entry)
    {
        if (reference && entry) {
            Int_t count = 0;
            if (entry->xentry) {
                count += entry->xentry->delta_count;
            }
            count += entry->bentry_count;
            if (count < 0) {
                count = std::numeric_limits<Int_t>::max();
            }
            return count;
        } else {
            return 0;
        }
    }

    Int_t Inventory_t::Count_Base(Entry_t* entry)
    {
        if (reference && entry) {
            return entry->bentry_count;
        } else {
            return 0;
        }
    }

    Int_t Inventory_t::Count_Extra(Entry_t* entry)
    {
        if (reference && entry && entry->xentry) {
            return entry->xentry->delta_count;
        } else {
            return 0;
        }
    }

    Int_t Inventory_t::Count_Loose(Entry_t* entry)
    {
        if (reference && entry) {
            if (entry->xentry) {
                Int_t count = Count(entry) - entry->xlist_count;
                if (count < 0) {
                    Validate(entry);
                    Int_t count = Count(entry) - entry->xlist_count;
                    if (count < 0) {
                        return 0;
                    } else {
                        return count;
                    }
                } else {
                    return count;
                }
            } else {
                return entry->bentry_count;
            }
        } else {
            return 0;
        }
    }

    Int_t Inventory_t::Count_XLists(Entry_t* entry)
    {
        if (reference && entry) {
            if (entry->xentry) {
                return entry->xlist_count;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    void Inventory_t::Add_Loose(Entry_t* entry, Int_t count)
    {
        if (reference && entry) {
            if (entry->xentry) {
                entry->xentry->delta_count += count;
                if (entry->xentry->delta_count + entry->bentry_count < 0) {
                    entry->xentry->delta_count = std::numeric_limits<Int_t>::max() - entry->bentry_count;
                }
            } else {
                entry->xentry = XEntry_t::Create(entry->form, count);
                xcontainer->changes->Add_XEntry(entry->xentry, reference);
                entry->xlist_count = 0;
            }
        }
    }

    void Inventory_t::Remove_Loose(Entry_t* entry, Int_t count)
    {
        if (reference && entry && count > 0) {
            if (entry->xentry) {
                Int_t entry_count = Count(entry);
                if (entry_count - count > entry->xlist_count) {
                    entry->xentry->delta_count -= count;
                } else {
                    entry->xentry->delta_count = entry->xlist_count - entry->bentry_count;
                }
                Try_To_Destroy_Entry(entry);
            } else if (entry->bentry_count > 0) {
                Int_t negative_count = 0 - count;
                Int_t negative_bentry_count = 0 - entry->bentry_count;
                if (negative_count < negative_bentry_count) {
                    entry->xentry = XEntry_t::Create(entry->form, negative_bentry_count);
                } else {
                    entry->xentry = XEntry_t::Create(entry->form, negative_count);
                }
                xcontainer->changes->Add_XEntry(entry->xentry, reference);
            }
        }
    }

    void Inventory_t::Add_XList(Entry_t* entry, XList_t* xlist)
    {
        if (reference && entry && xlist) {
            if (!entry->xentry) {
                entry->xentry = XEntry_t::Create(entry->form, 0);
                xcontainer->changes->Add_XEntry(entry->xentry, reference);
            }
            entry->xentry->Add_Clean_XList(xlist, reference);
            entry->xlist_count += XList::Count(xlist);
        }
    }

    void Inventory_t::Remove_XList(Entry_t* entry, XList_t* xlist)
    {
        if (reference && entry && xlist) {
            if (entry->xentry) {
                entry->xentry->Remove_XList(xlist);
                entry->xlist_count -= XList::Count(xlist);
                Try_To_Destroy_Entry(entry);
            }
        }
    }

    void Inventory_t::Increment_XList(Entry_t* entry, XList_t* xlist, Int_t count)
    {
        if (reference && entry && xlist && count > 0) {
            XList::Increment(xlist, count);
            entry->xlist_count += count;
        }
    }

    void Inventory_t::Decrement_XList(Entry_t* entry, XList_t* xlist, Int_t count)
    {
        if (reference && entry && xlist && count > 0) {
            Int_t xlist_count = XList::Count(xlist);
            if (xlist_count > count) {
                entry->xlist_count -= count;
            } else {
                entry->xlist_count -= xlist_count - 1;
            }
            XList::Decrement(xlist, count);
        }
    }

    void Inventory_t::Try_To_Destroy_Entry(Entry_t* entry)
    {
        if (reference && entry) {
            Int_t entry_index = Find(entry);
            if (entry_index > -1) {
                Validate(entry);
                if (entry->xentry && entry->xlist_count == 0 && entry->xentry->delta_count == 0) {
                    xcontainer->changes->Remove_XEntry(entry->xentry);
                    XEntry_t::Destroy(entry->xentry);
                    entry->xentry = nullptr;
                }
                /*if (!entry->xentry && entry->bentry_count == 0) {
                    entries.erase(entries.begin() + entry_index);
                }*/
            }
        }
    }

    void Inventory_t::Log(std::string indent)
    {
        if (reference) {
            _MESSAGE((indent + "Log_Inventory: %s").c_str(), Get_Name(reference));

            for (size_t idx = 0, end = entries.size(); idx < end; idx += 1) {
                Entry_t& entry = entries[idx];
                const char* name = Form::Name(entry.form);
                if (!name || !name[0]) {
                    name = "*";
                }
                _MESSAGE((indent + "    %-36s: total: %6i, base: %6i, extra: %6i, loose: %6i, xlists: %6i, form_type: %s").c_str(),
                         name,
                         Count(&entry),
                         Count_Base(&entry),
                         Count_Extra(&entry),
                         Count_Loose(&entry),
                         Count_XLists(&entry),
                         Form::Get_Type_String(entry.form));
                if (entry.xentry) {
                    Merged_XLists_t mxlists(&entry, true);
                    for (size_t idx = 0, end = mxlists.size(); idx < end; idx += 1) {
                        Merged_XList_t& mxlist = mxlists[idx];
                        _MESSAGE((indent + "        mxlist: %zu").c_str(), idx);
                        for (size_t idx = 0, end = mxlist.size(); idx < end; idx += 1) {
                            XList_t* xlist = mxlist[idx];
                            _MESSAGE((indent + "            xlist: %zu").c_str(), idx);
                            XList::Log(xlist, (indent + "                ").c_str());
                        }
                    }
                }
            }

            _MESSAGE("");
        }
    }

    Merged_XLists_t::Merged_XLists_t()
    {
    }

    Merged_XLists_t::Merged_XLists_t(Entry_t* entry, Bool_t(*do_exclude)(XList_t*))
    {
        if (entry && entry->xentry && entry->xentry->xlists && do_exclude) {
            reserve(4);
            for (XLists_t::Iterator it = entry->xentry->xlists->Begin(); !it.End(); ++it) {
                XList_t* xlist = it.Get();
                if (xlist && !do_exclude(xlist)) {
                    Merged_XList_t* merged_xlist = Merged_XList(xlist);
                    if (merged_xlist) {
                        merged_xlist->push_back(xlist);
                    } else {
                        Merged_XList_t merged_xlist;
                        merged_xlist.push_back(xlist);
                        push_back(merged_xlist);
                    }
                }
            }
        }
    }

    Merged_XLists_t::Merged_XLists_t(Entry_t* entry, Bool_t allow_quest_items)
    {
        if (allow_quest_items) {
            auto Do_Exclude = [](XList_t* xlist)->Bool_t
            {
                return false;
            };

            *this = Merged_XLists_t(entry, Do_Exclude);
        } else {
            auto Do_Exclude = [](XList_t* xlist)->Bool_t
            {
                return XList::Is_Quest_Item(xlist);
            };

            *this = Merged_XLists_t(entry, XList::Is_Quest_Item);
        }
    }

    Merged_XList_t* Merged_XLists_t::Merged_XList(XList_t* similar_xlist)
    {
        if (similar_xlist) {
            for (size_t idx = 0, count = size(); idx < count; idx += 1) {
                Merged_XList_t* merged_xlist = &at(idx);
                if (XList::Is_Similar(merged_xlist->at(0), similar_xlist)) {
                    return merged_xlist;
                }
            }
            return nullptr;
        } else {
            return nullptr;
        }
    }

    Int_t Merged_XLists_t::Count(Merged_XList_t* merged_xlist)
    {
        if (merged_xlist) {
            Int_t xlist_count = 0;
            for (size_t idx = 0, count = merged_xlist->size(); idx < count; idx += 1) {
                XList_t* xlist = merged_xlist->at(idx);
                xlist_count += XList::Count(xlist);
            }
            if (xlist_count < 0) {
                xlist_count = std::numeric_limits<Int_t>::max();
            }
            return xlist_count;
        } else {
            return 0;
        }
    }

    Bool_t Merged_XLists_t::Is_Worn(Merged_XList_t* merged_xlist)
    {
        if (merged_xlist) {
            for (size_t idx = 0, count = merged_xlist->size(); idx < count; idx += 1) {
                XList_t* xlist = merged_xlist->at(idx);
                if (XList::Is_Worn(xlist)) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }



    void Current_Crosshair_Reference(Virtual_Callback_i** callback)
    {
        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(),
                                               "doticu_npcp_funcs",
                                               "Current_Crosshair_Reference",
                                               nullptr,
                                               callback);
    }

    void Can_Use_Keys(Virtual_Callback_i** callback)
    {
        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(),
                                               "doticu_npcp_funcs",
                                               "Can_Use_Keys",
                                               nullptr,
                                               callback);
    }

    void Mapped_Control(Int_t key_code, Virtual_Callback_i* vcallback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Int_t key_code;
            Arguments(Int_t key_code) :
                key_code(key_code)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Int(key_code);
                return true;
            }
        } arguments(key_code);
        Virtual_Machine_t::Self()->Call_Global(
            "Input",
            "GetMappedControl",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
