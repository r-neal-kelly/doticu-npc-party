/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"

#include "actor_base2.h"
#include "actor2.h"
#include "form.h"
#include "object_ref.h"
#include "outfit.h"
#include "utils.h"
#include "xentry.h"
#include "xlist.h"

namespace doticu_npcp { namespace Actor2 {

    const char *Get_Base_Name(Actor *actor) {
        return Object_Ref::Get_Base_Name(actor);
    }

    const char *Get_Ref_Name(Actor *actor) {
        return Object_Ref::Get_Ref_Name(actor);
    }

    const char *Get_Name(Actor *actor) {
        return Object_Ref::Get_Name(actor);
    }

    BGSOutfit *Get_Outfit(Actor *actor, bool get_sleep_outfit) {
        if (!actor) {
            return NULL;
        }

        TESNPC *base = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
        if (!base) {
            return NULL;
        }

        if (get_sleep_outfit) {
            return base->sleepOutfit;
        } else {
            return base->defaultOutfit;
        }
    }

    void Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit) {
        if (!ref_actor || !outfit) {
            return;
        }

        // this is the leveled/real base which carries the outfits.
        // Thank you to Ian Patterson of SKSE for how to save the outfit!
        TESNPC *base_actor = DYNAMIC_CAST(ref_actor->baseForm, TESForm, TESNPC);
        if (is_sleep_outfit) {
            base_actor->sleepOutfit = outfit;
            base_actor->MarkChanged(0x2000);
        } else {
            base_actor->defaultOutfit = outfit;
            base_actor->MarkChanged(0x1000);
        }

        // passing true keeps items that were previously in inventory.
        // passing false makes actors become unaliased!
        // using this does indeed avoid the horrible outfit bug.
        ref_actor->ResetInventory(true);

        tArray<TESForm *> *arr_outfit_items = &outfit->armorOrLeveledItemArray;
        if (!arr_outfit_items) {
            return;
        }

        // we make sure everything in outfit is equipped, because the actor may have better equipment
        UInt64 idx = 0;
        TESForm *form_outfit_item;
        while (idx < arr_outfit_items->count) {
            arr_outfit_items->GetNthItem(idx, form_outfit_item);
            if (form_outfit_item) {
                papyrusActor::EquipItemEx(ref_actor, form_outfit_item, 0, false, false);
            }
            idx += 1;
        }

        // we need to unequip anything that doesn't come with outfit
        ExtraContainerChanges *container_extra = Object_Ref::Get_XContainer(ref_actor);
        if (container_extra) {
            for (tList<InventoryEntryData>::Iterator it_entry = container_extra->data->objList->Begin(); !it_entry.End(); ++it_entry) {
                InventoryEntryData *entry = it_entry.Get();
                if (entry && entry->type && entry->extendDataList) {
                    for (tList<BaseExtraList>::Iterator it_xlist = entry->extendDataList->Begin(); !it_xlist.End(); ++it_xlist) {
                        BaseExtraList *xlist = it_xlist.Get();
                        if (xlist && !xlist->HasType(kExtraData_OutfitItem) && xlist->HasType(kExtraData_Worn)) {
                            papyrusActor::UnequipItemEx(ref_actor, entry->type, 0, true);
                        }
                    }
                }
            }
        }

        return;
    }

    void Set_Outfit2(Actor *actor, TESForm *linchpin, TESObjectREFR *vanilla, TESObjectREFR *custom, TESObjectREFR *transfer) {
        if (!actor || !linchpin || !transfer) {
            _ERROR("Actor2::Set_Outfit2: Invalid args.");
            return;
        }

        XContainer_t *xcontainer_actor = Object_Ref::Get_XContainer(actor);
        if (!xcontainer_actor) {
            _ERROR("Actor2::Set_Outfit2: Unable to get actor XContainer.");
            return;
        }

        XEntry::Set_Count(Object_Ref::Get_XEntry(actor, linchpin), 1);

        std::vector<XEntry_t *> vec_xentries_destroy;
        vec_xentries_destroy.reserve(4);

        for (XEntries_t::Iterator it_xentry_actor = xcontainer_actor->data->objList->Begin(); !it_xentry_actor.End(); ++it_xentry_actor) {
            XEntry_t *xentry_actor = it_xentry_actor.Get();
            if (!xentry_actor || !xentry_actor->type || xentry_actor->type == linchpin) {
                continue;
            }

            TESForm *form_actor = xentry_actor->type;
            if (!form_actor->IsPlayable() && !form_actor->IsArmor() && !form_actor->IsWeapon() && !form_actor->IsAmmo()) {
                continue;
            }

            u64 count_in_xlists_kept = 0;
            if (xentry_actor->extendDataList) {
                std::vector<XList_t *> vec_xlists_trash;
                std::vector<XList_t *> vec_xlists_transfer;
                vec_xlists_trash.reserve(4);
                vec_xlists_transfer.reserve(4);

                for (XLists_t::Iterator it_xlist_actor = xentry_actor->extendDataList->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                    XList_t *xlist_actor = it_xlist_actor.Get();
                    if (!xlist_actor) {
                        continue;
                    }

                    if (static_cast<s32>(XList::Get_Count(xlist_actor)) < 0) {
                        _MESSAGE("Actor2::Set_Outfit2: Encountered xlist that could overflow xentry. Setting count to 1!:");
                        _MESSAGE("Actor: %s, Custom: %s, Form: %s", Get_Name(actor), Object_Ref::Get_Name(custom), Form::Get_Name(form_actor));
                        XList::Log(xlist_actor, "");
                        XList::Set_Count(xlist_actor, 1);
                    }

                    if (XList::Is_Quest_Item(xlist_actor)) {
                        count_in_xlists_kept += XList::Get_Count(xlist_actor);
                    } else if (!form_actor->IsPlayable() ||
                               XList::Is_Outfit_Item(xlist_actor) ||
                               XList::Is_Leveled_Item(xlist_actor) ||
                               XList::Has_Outfit2_Flag(xlist_actor)) {
                        vec_xlists_trash.push_back(xlist_actor);
                    } else {
                        vec_xlists_transfer.push_back(xlist_actor);
                    }
                }
                for (u64 idx = 0, size = vec_xlists_trash.size(); idx < size; idx += 1) {
                    XList_t *xlist_trash = vec_xlists_trash[idx];
                    XEntry::Remove_XList(xentry_actor, xlist_trash);
                    XList::Destroy(xlist_trash);
                }
                if (vec_xlists_transfer.size() > 0) {
                    XEntry_t *xentry_transfer = Object_Ref::Get_XEntry(transfer, form_actor, true);
                    for (u64 idx = 0, size = vec_xlists_transfer.size(); idx < size; idx += 1) {
                        XList_t *xlist_transfer = vec_xlists_transfer[idx];
                        XEntry::Move_XList(xentry_actor, xentry_transfer, xlist_transfer, transfer);
                    }
                }
            }

            s64 count_bentry = Object_Ref::Get_BEntry_Count(actor, form_actor);
            s64 count_xentry = Object_Ref::Get_XEntry_Count(actor, form_actor);
            s64 count_remaining = count_bentry + count_xentry - count_in_xlists_kept;
            if (count_remaining > 0) {
                if (form_actor->IsPlayable()) {
                    XEntry_t *xentry_transfer = Object_Ref::Get_XEntry(transfer, form_actor, true);
                    XEntry::Inc_Count(xentry_transfer, count_remaining);
                }
            }

            if (count_in_xlists_kept == 0 && count_bentry == 0) {
                vec_xentries_destroy.push_back(xentry_actor);
            } else {
                XEntry::Set_Count(xentry_actor, count_in_xlists_kept - count_bentry);
            }
        }
        for (u64 idx = 0, size = vec_xentries_destroy.size(); idx < size; idx += 1) {
            XEntry_t *xentry_destroy = vec_xentries_destroy[idx];
            Object_Ref::Remove_XEntry(actor, xentry_destroy);
            XEntry::Destroy(xentry_destroy);
        }

        BContainer_t *bcontainer_actor = Object_Ref::Get_BContainer(actor);
        if (bcontainer_actor) {
            for (u64 idx = 0; idx < bcontainer_actor->numEntries; idx += 1) {
                BEntry_t *bentry = bcontainer_actor->entries[idx];
                if (!bentry || !bentry->form || bentry->form->formType == kFormType_LeveledItem || bentry->count < 1) {
                    continue;
                }

                if (!Object_Ref::Has_XEntry(actor, bentry->form)) {
                    XEntry_t *xentry = Object_Ref::Get_XEntry(actor, bentry->form, true);
                    XEntry::Dec_Count(xentry, bentry->count);
                }
            }
        }

        Copy_Outfit2_Partition(actor, linchpin, vanilla);
        Copy_Outfit2_Partition(actor, linchpin, custom);
    }

    void Copy_Outfit2_Partition(Actor *actor, TESForm *linchpin, TESObjectREFR *outfit2_partition) {
        if (!actor || !linchpin) {
            return;
        }

        XContainer_t *xcontainer_outfit = Object_Ref::Get_XContainer(outfit2_partition);
        if (!xcontainer_outfit) {
            return;
        }

        for (XEntries_t::Iterator it_xentry_outfit = xcontainer_outfit->data->objList->Begin(); !it_xentry_outfit.End(); ++it_xentry_outfit) {
            XEntry_t *xentry_outfit = it_xentry_outfit.Get();
            if (!xentry_outfit || !xentry_outfit->type || xentry_outfit->type == linchpin) {
                continue;
            }
            TESForm *form_outfit = xentry_outfit->type;

            XEntry_t *xentry_actor = Object_Ref::Get_XEntry(actor, form_outfit, true);
            if (!xentry_actor) {
                continue;
            }

            u64 count_xlists_outfit = 0;
            if (xentry_outfit->extendDataList) {
                for (XLists_t::Iterator it_xlist_outfit = xentry_outfit->extendDataList->Begin(); !it_xlist_outfit.End(); ++it_xlist_outfit) {
                    XList_t *xlist_outfit = it_xlist_outfit.Get();
                    if (!xlist_outfit) {
                        continue;
                    }

                    XList_t *xlist_actor = XEntry::Get_XList(xentry_actor, xlist_outfit, true);
                    if (xlist_actor) {
                        u64 count_xlist_outfit = XList::Get_Count(xlist_outfit);
                        XList::Inc_Count(xlist_actor, count_xlist_outfit);
                        XEntry::Inc_Count(xentry_actor, count_xlist_outfit);
                        count_xlists_outfit += count_xlist_outfit;
                    } else {
                        xlist_actor = XList::Copy(xlist_outfit);
                        if (!xlist_actor) {
                            continue;
                        }

                        XList::Add_Outfit2_Flag(xlist_actor);
                        XEntry::Add_XList(xentry_actor, xlist_actor);
                        count_xlists_outfit += XList::Get_Count(xlist_outfit);
                    }
                }
            }

            s64 count_entry_outfit = Object_Ref::Get_Entry_Count(outfit2_partition, form_outfit);
            if (count_entry_outfit > count_xlists_outfit) {
                XList_t *xlist_remainder = XList::Create();
                XList::Set_Count(xlist_remainder, count_entry_outfit - count_xlists_outfit);
                XList::Add_Outfit2_Flag(xlist_remainder);
                XEntry::Add_XList(xentry_actor, xlist_remainder);
            }
        }
    }

    void Cache_Worn(Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out) {
        if (!actor || !linchpin || !cache_out) {
            _ERROR("Actor2::Cache_Worn: Invalid args.");
            return;
        }

        XContainer_t *xcontainer_actor = Object_Ref::Get_XContainer(actor);
        if (!xcontainer_actor) {
            return;
        }

        for (XEntries_t::Iterator it_xentry_actor = xcontainer_actor->data->objList->Begin(); !it_xentry_actor.End(); ++it_xentry_actor) {
            XEntry_t *xentry_actor = it_xentry_actor.Get();
            if (!xentry_actor || !xentry_actor->type || xentry_actor->type == linchpin || !xentry_actor->extendDataList) {
                continue;
            }

            std::vector<XList_t *> vec_xlists_worn;
            vec_xlists_worn.reserve(2);

            for (XLists_t::Iterator it_xlist_actor = xentry_actor->extendDataList->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                XList_t *xlist_actor = it_xlist_actor.Get();
                if (!xlist_actor) {
                    continue;
                }

                if (static_cast<s32>(XList::Get_Count(xlist_actor)) < 0) {
                    _MESSAGE("Actor2::Cache_Worn: Encountered xlist that could overflow xentry. Setting count to 1!:");
                    _MESSAGE("Actor: %s, Form: %s", Get_Name(actor), Form::Get_Name(xentry_actor->type));
                    XList::Log(xlist_actor, "");
                    XList::Set_Count(xlist_actor, 1);
                }

                if (XList::Is_Worn(xlist_actor)) {
                    vec_xlists_worn.push_back(xlist_actor);
                }
            }

            if (vec_xlists_worn.size() > 0) {
                XEntry_t *xentry_cache = Object_Ref::Get_XEntry(cache_out, xentry_actor->type, true);
                if (!xentry_cache) {
                    continue;
                }

                for (u64 idx = 0, size = vec_xlists_worn.size(); idx < size; idx += 1) {
                    XList_t *xlist_worn = vec_xlists_worn[idx];
                    XList_t *xlist_cache = XList::Copy(xlist_worn);
                    if (xlist_cache) {
                        XEntry::Add_XList(xentry_cache, xlist_cache);
                    } else {
                        XEntry::Inc_Count(xentry_cache, XList::Get_Count(xlist_worn));
                    }
                }
            }
        }
    }

    // this copies and splits playable items into two containers, one for equipment and the other for everything else
    void Cache_Inventory(Actor *actor, TESForm *linchpin, TESObjectREFR *worn_out, TESObjectREFR *pack_out) {
        if (!actor || !linchpin || !worn_out || !pack_out) {
            _ERROR("Actor2::Cache_Inventory: Invalid args.");
            return;
        }

        XContainer_t *xcontainer_worn = Object_Ref::Get_XContainer(worn_out);
        if (!xcontainer_worn) {
            _ERROR("Actor2::Cache_Inventory: Could not get worn xcontainer.");
            return;
        }

        XContainer_t *xcontainer_pack = Object_Ref::Get_XContainer(pack_out);
        if (!xcontainer_pack) {
            _ERROR("Actor2::Cache_Inventory: Could not get pack xcontainer.");
            return;
        }

        XContainer_t *xcontainer_actor = Object_Ref::Get_XContainer(actor);
        if (xcontainer_actor) {
            for (XEntries_t::Iterator it_xentry_actor = xcontainer_actor->data->objList->Begin(); !it_xentry_actor.End(); ++it_xentry_actor) {
                XEntry_t *xentry_actor = it_xentry_actor.Get();
                if (!xentry_actor || !xentry_actor->type || xentry_actor->type == linchpin) {
                    continue;
                }

                TESForm *form_actor = xentry_actor->type;
                if (!form_actor->IsPlayable()) {
                    continue;
                }

                u64 count_xlists_actor = 0;
                if (xentry_actor->extendDataList) {
                    std::vector<XList_t *> vec_xlists_worn;
                    std::vector<XList_t *> vec_xlists_pack;
                    vec_xlists_worn.reserve(2);
                    vec_xlists_pack.reserve(2);

                    for (XLists_t::Iterator it_xlist_actor = xentry_actor->extendDataList->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                        XList_t *xlist_actor = it_xlist_actor.Get();
                        if (!xlist_actor) {
                            continue;
                        }

                        if (static_cast<s32>(XList::Get_Count(xlist_actor)) < 0) {
                            _MESSAGE("Actor2::Cache_Inventory: Encountered xlist that could overflow xentry. Setting count to 1!:");
                            _MESSAGE("Actor: %s, Form: %s", Get_Name(actor), Form::Get_Name(xentry_actor->type));
                            XList::Log(xlist_actor, "");
                            XList::Set_Count(xlist_actor, 1);
                        }

                        count_xlists_actor += XList::Get_Count(xlist_actor);

                        if (XList::Is_Worn(xlist_actor)) {
                            vec_xlists_worn.push_back(xlist_actor);
                        } else {
                            vec_xlists_pack.push_back(xlist_actor);
                        }
                    }

                    if (vec_xlists_worn.size() > 0) {
                        XEntry_t *xentry_worn = Object_Ref::Get_XEntry(worn_out, form_actor, true);
                        if (!xentry_worn) {
                            continue;
                        }

                        for (u64 idx = 0, size = vec_xlists_worn.size(); idx < size; idx += 1) {
                            XList_t *xlist_worn = vec_xlists_worn[idx];
                            XList_t *xlist_copy = XList::Copy(xlist_worn);
                            if (xlist_copy) {
                                XEntry::Add_XList(xentry_worn, xlist_copy);
                            } else {
                                XEntry::Inc_Count(xentry_worn, XList::Get_Count(xlist_worn));
                            }
                        }
                    }

                    if (vec_xlists_pack.size() > 0) {
                        XEntry_t *xentry_pack = Object_Ref::Get_XEntry(pack_out, form_actor, true);
                        if (!xentry_pack) {
                            continue;
                        }

                        for (u64 idx = 0, size = vec_xlists_pack.size(); idx < size; idx += 1) {
                            XList_t *xlist_pack = vec_xlists_pack[idx];
                            XList_t *xlist_copy = XList::Copy(xlist_pack);
                            if (xlist_copy) {
                                XEntry::Add_XList(xentry_pack, xlist_copy);
                            } else {
                                XEntry::Inc_Count(xentry_pack, XList::Get_Count(xlist_pack));
                            }
                        }
                    }
                }

                u64 count_remaining = Object_Ref::Get_BEntry_Count(actor, form_actor) + XEntry::Get_Count(xentry_actor) - count_xlists_actor;
                if (count_remaining > 0) {
                    XEntry_t *xentry_pack = Object_Ref::Get_XEntry(pack_out, form_actor, true);
                    if (xentry_pack) {
                        XEntry::Inc_Count(xentry_pack, count_remaining);
                    }
                }
            }
        }

        BContainer_t *bcontainer_actor = Object_Ref::Get_BContainer(actor);
        if (bcontainer_actor) {
            for (u64 idx = 0; idx < bcontainer_actor->numEntries; idx += 1) {
                BEntry_t *bentry_actor = bcontainer_actor->entries[idx];
                if (!bentry_actor || !bentry_actor->form || bentry_actor->count < 1) {
                    continue;
                }

                TESForm *form_actor = bentry_actor->form;
                if (form_actor == linchpin || form_actor->formType == kFormType_LeveledItem || !form_actor->IsPlayable()) {
                    continue;
                }

                if (!Object_Ref::Has_XEntry(actor, form_actor)) {
                    XEntry_t *xentry_pack = Object_Ref::Get_XEntry(pack_out, form_actor, true);
                    XEntry::Inc_Count(xentry_pack, bentry_actor->count);
                }
            }
        }
    }

    // copies over BContainer equipment, except for linchpin.
    // we use AddItem_Native because we haven't implement leveled item expansion.
    // we cannot see what AddItem_Native adds, as it fulfills only after returning,
    // and because some items are leveled items, we can't filter forms in this func
    void Cache_Static_Inventory(VMClassRegistry* registry, UInt32 id_stack, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out) {
        if (!actor || !linchpin || !cache_out) {
            _ERROR("Actor2::Cache_Static_Inventory: Invalid args.");
            return;
        }

        BContainer_t *bcontainer_actor = Object_Ref::Get_BContainer(actor);
        if (bcontainer_actor) {
            for (u64 idx = 0; idx < bcontainer_actor->numEntries; idx += 1) {
                BEntry_t *bentry_actor = bcontainer_actor->entries[idx];
                if (!bentry_actor || !bentry_actor->form || bentry_actor->count < 1) {
                    continue;
                }

                TESForm *form_actor = bentry_actor->form;
                if (form_actor == linchpin) {
                    continue;
                }

                // this causes a latent error in papyrus log, not sure how to use it properly, but it's working?
                AddItem_Native(registry, id_stack, cache_out, form_actor, bentry_actor->count, true);
            }
        }

        //registry->ResumeStack(id_stack, NULL);
    }

    bool Has_Same_Head(Actor *actor_a, Actor *actor_b) {
        if (!actor_a || !actor_b) {
            return false;
        }

        TESNPC *actor_base_a = DYNAMIC_CAST(actor_a->baseForm, TESForm, TESNPC);
        TESNPC *actor_base_b = DYNAMIC_CAST(actor_b->baseForm, TESForm, TESNPC);
        
        return Actor_Base2::Has_Same_Head(actor_base_a, actor_base_b);
    }

    bool Is_Alive(Actor *actor) {
        if (!actor) {
            return false;
        }

        return !actor->IsDead(1);
    }

    bool Is_Dead(Actor *actor) {
        if (!actor) {
            return false;
        }

        return actor->IsDead(1);
    }

    bool Is_Loaded(Actor *actor) {
        if (!actor) {
            return false;
        }

        return actor->loadedState != nullptr;
    }

    bool Is_AI_Enabled(Actor *actor) {
        if (!actor) {
            return false;
        }

        return (actor->flags1 & Actor::kFlags_AIEnabled) == Actor::kFlags_AIEnabled;
    }

    bool Is_Aliased_In_Quest(Actor *actor, TESQuest *quest)
    {
        if (actor && quest)
        {
            ExtraAliasInstanceArray *xaliases = (ExtraAliasInstanceArray *)actor->extraData.GetByType(kExtraData_AliasInstanceArray);
            if (xaliases)
            {
                for (u64 idx = 0, size = xaliases->aliases.count; idx < size; idx += 1)
                {
                    ExtraAliasInstanceArray::AliasInfo *info = xaliases->aliases[idx];
                    if (info && info->quest == quest)
                    {
                        return true;
                    }
                }

                return false;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    void Move_To_Orbit(Actor *actor, TESObjectREFR *target, float radius, float angle_degree) {
        if (!actor || !target) {
            return;
        }

        Object_Ref::Move_To_Orbit(actor, target, radius, angle_degree);

        /*if (!Is_AI_Enabled(actor)) {
            // need to be careful, if they are on a horse. their extradata may have kExtraData_Horse as an indicator
            // make sure to test once we have followers riding horses.
            CALL_MEMBER_FN(actor, QueueNiNodeUpdate)(false);
        }*/

        CALL_MEMBER_FN(actor, QueueNiNodeUpdate)(false);
    }

    float Get_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor->actorValueOwner.GetCurrent(id_value);
    }

    float Get_Base_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor->actorValueOwner.GetBase(id_value);
    }

    float Get_Max_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor->actorValueOwner.GetMaximum(id_value);
    }

    void Set_Actor_Value(Actor *actor, const char *name, float value) {
        if (!actor || !name || !name[0]) {
            return;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return;
        }

        actor->actorValueOwner.SetCurrent(id_value, value);
    }

    void Reset_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return;
        }

        TESNPC *actor_base = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
        if (!actor_base) {
            return;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return;
        }

        Set_Actor_Value(actor, name, Actor_Base2::Get_Base_Actor_Value(actor_base, name));
    }

    void Log_Actor_Values(Actor *actor) {
        if (!actor) {
            return;
        }

        _MESSAGE("Logging Actor Values: %s", Get_Name(actor));

        #define LOG_ACTOR_VALUE(NAME)                                   \
        M                                                               \
            _MESSAGE("    " NAME ": curr %10f, base %10f, max %10f",    \
                     Get_Actor_Value(actor, NAME),                      \
                     Get_Base_Actor_Value(actor, NAME),                 \
                     Get_Max_Actor_Value(actor, NAME));                 \
        W

        LOG_ACTOR_VALUE("Health");
        LOG_ACTOR_VALUE("Magicka");
        LOG_ACTOR_VALUE("Stamina");

        LOG_ACTOR_VALUE("OneHanded");
        LOG_ACTOR_VALUE("TwoHanded");
        LOG_ACTOR_VALUE("Block");
        LOG_ACTOR_VALUE("HeavyArmor");
        LOG_ACTOR_VALUE("LightArmor");
        LOG_ACTOR_VALUE("Smithing");

        LOG_ACTOR_VALUE("Destruction");
        LOG_ACTOR_VALUE("Restoration");
        LOG_ACTOR_VALUE("Conjuration");
        LOG_ACTOR_VALUE("Alteration");
        LOG_ACTOR_VALUE("Illusion");
        LOG_ACTOR_VALUE("Enchanting");

        LOG_ACTOR_VALUE("Marksman");
        LOG_ACTOR_VALUE("Sneak");
        LOG_ACTOR_VALUE("Alchemy");
        LOG_ACTOR_VALUE("Lockpicking");
        LOG_ACTOR_VALUE("Pickpocket");
        LOG_ACTOR_VALUE("Speechcraft");

        #undef LOG_ACTOR_VALUE
    }

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    void Set_Outfit2(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *vanilla, TESObjectREFR *custom, TESObjectREFR *transfer) {
        return Actor2::Set_Outfit2(actor, linchpin, vanilla, custom, transfer);

        _MESSAGE("\nVanilla Partition:");
        Object_Ref::Log_XContainer(vanilla);

        _MESSAGE("\nCustom Partition:");
        Object_Ref::Log_XContainer(custom);

        _MESSAGE("\nActor Before Set:");
        Object_Ref::Log_XContainer(actor);

        Actor2::Set_Outfit2(actor, linchpin, vanilla, custom, transfer);

        _MESSAGE("\nActor After Set:");
        Object_Ref::Log_XContainer(actor);

        _MESSAGE("\nTransfer:");
        Object_Ref::Log_XContainer(transfer);
    }

    void Cache_Worn(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out) {
        return Actor2::Cache_Worn(actor, linchpin, cache_out);
    }

    void Cache_Inventory(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *worn_out, TESObjectREFR *pack_out) {
        return Actor2::Cache_Inventory(actor, linchpin, worn_out, pack_out);

        _MESSAGE("\nWorn Before:");
        Object_Ref::Log_XContainer(worn_out);

        _MESSAGE("\nPack Before:");
        Object_Ref::Log_XContainer(pack_out);

        Actor2::Cache_Inventory(actor, linchpin, worn_out, pack_out);

        _MESSAGE("\nWorn After:");
        Object_Ref::Log_XContainer(worn_out);

        _MESSAGE("\nPack After:");
        Object_Ref::Log_XContainer(pack_out);
    }

    void Cache_Static_Inventory(VMClassRegistry* registry, UInt32 id_stack, StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out) {
        return Actor2::Cache_Static_Inventory(registry, id_stack, actor, linchpin, cache_out);
    }

    void Reset_Actor_Value(Selfless_t *, Actor *actor, BSFixedString name) {
        return Actor2::Reset_Actor_Value(actor, name.data);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <Actor, void, BGSOutfit *, bool>(
                "SetOutfit",
                "Actor",
                Actor2::Set_Outfit,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction5 <StaticFunctionTag, void, Actor *, TESForm *, TESObjectREFR *, TESObjectREFR *, TESObjectREFR *>(
                "Actor_Set_Outfit2",
                "doticu_npcp",
                Actor2::Exports::Set_Outfit2,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, void, Actor *, TESForm *, TESObjectREFR *>(
                "Actor_Cache_Worn",
                "doticu_npcp",
                Actor2::Exports::Cache_Worn,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction4 <StaticFunctionTag, void, Actor *, TESForm *, TESObjectREFR *, TESObjectREFR *>(
                "Actor_Cache_Inventory",
                "doticu_npcp",
                Actor2::Exports::Cache_Inventory,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, void, Actor *, TESForm *, TESObjectREFR *>(
                "Actor_Cache_Static_Inventory",
                "doticu_npcp",
                Actor2::Exports::Cache_Static_Inventory,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, Actor *, BSFixedString>(
                "Actor_Reset_Actor_Value",
                "doticu_npcp",
                Actor2::Exports::Reset_Actor_Value,
                registry)
        );

        return true;
    }

}}}
