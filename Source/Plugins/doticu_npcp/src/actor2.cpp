/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "outfit.h"

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

    bool Has_Outfit2(Actor *actor,
                     TESForm *linchpin,
                     TESObjectREFR *vanilla,
                     TESObjectREFR *custom
    ) {
        if (!actor || !linchpin) {
            _ERROR("Actor2::Has_Outfit2: Invalid args.");
            return false;
        }

        if (!Object_Ref::Is_Worn(actor, linchpin)) {
            return false;
        }

        XContainer_t *xcontainer_actor = Object_Ref::Get_XContainer(actor);
        if (!xcontainer_actor) {
            _ERROR("Actor2::Has_Outfit2: Unable to get XContainer.");
            return false;
        }

        for (XEntries_t::Iterator it_xentry_actor = xcontainer_actor->data->objList->Begin(); !it_xentry_actor.End(); ++it_xentry_actor) {
            XEntry_t *xentry_actor = it_xentry_actor.Get();
            if (!xentry_actor || !xentry_actor->type || xentry_actor->type == linchpin) {
                continue;
            }

            TESForm *form_actor = xentry_actor->type;
            if (!form_actor->IsPlayable() && !form_actor->IsArmor() && !form_actor->IsWeapon() && !form_actor->IsAmmo()) {
                continue;
            }

            XEntry_t *xentry_vanilla = Object_Ref::Get_XEntry(vanilla, form_actor);
            XEntry_t *xentry_custom = Object_Ref::Get_XEntry(custom, form_actor);
            if (XEntry::Get_Count(xentry_actor) > 0 && !xentry_vanilla && !xentry_custom) {
                return false;
            }

            u64 count_xlists_tagged = 0;
            u64 count_xlists_untagged = 0;
            if (xentry_actor->extendDataList) {
                for (XLists_t::Iterator it_xlist_actor = xentry_actor->extendDataList->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                    XList_t *xlist_actor = it_xlist_actor.Get();
                    if (!xlist_actor) {
                        continue;
                    }

                    if (XList::Is_Quest_Item(xlist_actor)) {
                        count_xlists_untagged += XList::Get_Count(xlist_actor);
                    } else if (XList::Has_Outfit2_Flag(xlist_actor)) {
                        if (XList::Can_Copy(xlist_actor) &&
                            !XEntry::Get_XList(xentry_vanilla, xlist_actor, false) &&
                            !XEntry::Get_XList(xentry_custom, xlist_actor, false)
                            ) {
                            return false;
                        }
                        count_xlists_tagged += XList::Get_Count(xlist_actor);
                    } else {
                        return false;
                    }
                }
            }

            if (Object_Ref::Get_Entry_Count(actor, form_actor) != count_xlists_tagged + count_xlists_untagged) {
                return false;
            } else if (Object_Ref::Get_Entry_Count(vanilla, form_actor) + Object_Ref::Get_Entry_Count(custom, form_actor) != count_xlists_tagged) {
                return false;
            }

        }

        return Has_Outfit2_Partition(actor, linchpin, vanilla) && Has_Outfit2_Partition(actor, linchpin, custom);
    }

    bool Has_Outfit2_Partition(Actor *actor,
                               TESForm *linchpin,
                               TESObjectREFR *outfit2_partition
    ) {
        if (!actor || !linchpin) {
            _ERROR("Actor2::Has_Outfit2_Partition: Invalid args.");
            return false;
        }

        XContainer_t *xcontainer_outfit = Object_Ref::Get_XContainer(outfit2_partition);
        if (!xcontainer_outfit) {
            return true;
        }

        for (XEntries_t::Iterator it_xentry_outfit = xcontainer_outfit->data->objList->Begin(); !it_xentry_outfit.End(); ++it_xentry_outfit) {
            XEntry_t *xentry_outfit = it_xentry_outfit.Get();
            if (!xentry_outfit || !xentry_outfit->type || xentry_outfit->type == linchpin) {
                continue;
            }
            TESForm *form_outfit = xentry_outfit->type;

            XEntry_t *xentry_actor = Object_Ref::Get_XEntry(actor, form_outfit, false);
            if (!xentry_actor) {
                return false;
            }

            if (xentry_outfit->extendDataList) {
                for (XLists_t::Iterator it_xlist_outfit = xentry_outfit->extendDataList->Begin(); !it_xlist_outfit.End(); ++it_xlist_outfit) {
                    XList_t *xlist_outfit = it_xlist_outfit.Get();
                    if (!xlist_outfit) {
                        continue;
                    }

                    XList_t *xlist_actor = XEntry::Get_XList(xentry_actor, xlist_outfit, true);
                    if (!xlist_actor || XList::Get_Count(xlist_outfit) != XList::Get_Count(xlist_actor)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    void Set_Outfit2(Actor *actor,
                     TESForm *linchpin, // an item that when present, stops the engine from adding unwanted items to actor
                     TESObjectREFR *vanilla, // a cache of pre-calculated vanilla outfit items (can be null)
                     TESObjectREFR *custom, // custom items which are additional to vanilla
                     TESObjectREFR *trash, // where non-matching items are put specifically for deletion, i.e. previous outfit items
                     TESObjectREFR *transfer // where non-matching items are put for transfer elsewhere, i.e. items from the world
    ) {
        if (!actor || !linchpin || !transfer || !trash) {
            _ERROR("Actor2::Set_Outfit2: Invalid args.");
            return;
        }

        // this creates xcontainer_actor if necessary.
        if (!Object_Ref::Is_Worn(actor, linchpin)) {
            _MESSAGE("equipping linchpin");
            papyrusActor::EquipItemEx(actor, linchpin, 0, false, false);
        }
        XEntry::Set_Count(Object_Ref::Get_XEntry(actor, linchpin), 1);

        XContainer_t *xcontainer_actor = Object_Ref::Get_XContainer(actor);
        if (!xcontainer_actor) {
            return;
        }

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

            u64 count_xlists_kept = 0;
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

                    if (XList::Is_Quest_Item(xlist_actor)) {
                        count_xlists_kept += XList::Get_Count(xlist_actor);
                    } else if (!form_actor->IsPlayable() ||
                               XList::Has_Outfit2_Flag(xlist_actor) ||
                               XList::Is_Outfit_Item(xlist_actor) ||
                               XList::Is_Leveled_Item(xlist_actor)
                               ) {
                        vec_xlists_trash.push_back(xlist_actor);
                    } else {
                        vec_xlists_transfer.push_back(xlist_actor);
                    }
                }
                if (vec_xlists_trash.size() > 0) {
                    XEntry_t *xentry_trash = Object_Ref::Get_XEntry(trash, form_actor, true);
                    for (u64 idx = 0, size = vec_xlists_trash.size(); idx < size; idx += 1) {
                        XList_t *xlist_trash = vec_xlists_trash[idx];
                        XEntry::Remove_XList(xentry_actor, xlist_trash);
                        XEntry::Add_XList(xentry_trash, xlist_trash);
                    }
                }
                if (vec_xlists_transfer.size() > 0) {
                    XEntry_t *xentry_transfer = Object_Ref::Get_XEntry(transfer, form_actor, true);
                    for (u64 idx = 0, size = vec_xlists_transfer.size(); idx < size; idx += 1) {
                        XList_t *xlist_transfer = vec_xlists_transfer[idx];
                        XEntry::Remove_XList(xentry_actor, xlist_transfer);
                        XEntry::Add_XList(xentry_transfer, xlist_transfer);
                    }
                }
            }

            s64 count_bentry = Object_Ref::Get_BEntry_Count(actor, form_actor);
            s64 count_xentry = Object_Ref::Get_XEntry_Count(actor, form_actor);
            s64 count_remaining = count_bentry + count_xentry - count_xlists_kept;
            if (count_remaining > 0) {
                if (form_actor->IsPlayable()) {
                    XEntry_t *xentry_transfer = Object_Ref::Get_XEntry(transfer, form_actor, true);
                    XEntry::Inc_Count(xentry_transfer, count_remaining);
                }
            }

            if (count_xlists_kept == 0 && count_bentry == 0) {
                vec_xentries_destroy.push_back(xentry_actor);
            } else {
                XEntry::Set_Count(xentry_actor, count_xlists_kept - count_bentry);
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

    void Copy_Outfit2_Partition(Actor *actor,
                                TESForm *linchpin,
                                TESObjectREFR *outfit2_partition
    ) {
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

    void Set_Outfit2_Dead(Actor *actor,
                          TESForm *linchpin,
                          TESObjectREFR *vanilla,
                          TESObjectREFR *custom,
                          TESObjectREFR *trash,
                          TESObjectREFR *transfer
    ) {
        if (!actor || !linchpin || !transfer || !trash) {
            _ERROR("Actor2::Set_Outfit2: Invalid args.");
            return;
        }

        XContainer_t *xcontainer_actor = Object_Ref::Get_XContainer(actor);
        if (!xcontainer_actor) {
            return;
        }

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

            u64 count_xlists_kept = 0;
            if (xentry_actor->extendDataList) {
                std::vector<XList_t *> vec_xlists_trash;
                std::vector<XList_t *> vec_xlists_transfer;
                vec_xlists_trash.reserve(4);
                vec_xlists_transfer.reserve(4);

                XEntry_t *xentry_vanilla = Object_Ref::Get_XEntry(vanilla, form_actor, false);
                XEntry_t *xentry_custom = Object_Ref::Get_XEntry(custom, form_actor, false);

                for (XLists_t::Iterator it_xlist_actor = xentry_actor->extendDataList->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                    XList_t *xlist_actor = it_xlist_actor.Get();
                    if (!xlist_actor) {
                        continue;
                    }

                    if (XList::Is_Quest_Item(xlist_actor)) {
                        count_xlists_kept += XList::Get_Count(xlist_actor);
                    } else if (XList::Has_Outfit2_Flag(xlist_actor)) {
                        if (XList::Can_Copy(xlist_actor)) {
                            XList_t *xlist_vanilla = XEntry::Get_XList(xentry_vanilla, xlist_actor, false);
                            XList_t *xlist_custom = XEntry::Get_XList(xentry_custom, xlist_actor, false);
                            if (xlist_vanilla || xlist_custom) {
                                u64 count_xlist_outfit = XList::Get_Count(xlist_vanilla) + XList::Get_Count(xlist_custom);
                                XEntry::Set_XList_Count(xentry_actor, xlist_actor, count_xlist_outfit);
                                count_xlists_kept += count_xlist_outfit;
                            } else {
                                vec_xlists_trash.push_back(xlist_actor);
                            }
                        } else {
                            u64 count_nolist_outfit =
                                Object_Ref::Get_Entry_Count(vanilla, form_actor) -
                                XEntry::Get_XLists_Count(xentry_vanilla) +
                                Object_Ref::Get_Entry_Count(custom, form_actor) -
                                XEntry::Get_XLists_Count(xentry_custom);
                            if (count_nolist_outfit > 0) {
                                XEntry::Set_XList_Count(xentry_actor, xlist_actor, count_nolist_outfit);
                                count_xlists_kept += count_nolist_outfit;
                            } else {
                                vec_xlists_trash.push_back(xlist_actor);
                            }
                        }
                    } else if (!form_actor->IsPlayable() || XList::Is_Outfit_Item(xlist_actor) || XList::Is_Leveled_Item(xlist_actor)) {
                        vec_xlists_trash.push_back(xlist_actor);
                    } else {
                        vec_xlists_transfer.push_back(xlist_actor);
                    }
                }
                if (vec_xlists_trash.size() > 0) {
                    XEntry_t *xentry_trash = Object_Ref::Get_XEntry(trash, form_actor, true);
                    for (u64 idx = 0, size = vec_xlists_trash.size(); idx < size; idx += 1) {
                        XList_t *xlist_trash = vec_xlists_trash[idx];
                        XEntry::Remove_XList(xentry_actor, xlist_trash);
                        XEntry::Add_XList(xentry_trash, xlist_trash);
                    }
                }
                if (vec_xlists_transfer.size() > 0) {
                    XEntry_t *xentry_transfer = Object_Ref::Get_XEntry(transfer, form_actor, true);
                    for (u64 idx = 0, size = vec_xlists_transfer.size(); idx < size; idx += 1) {
                        XList_t *xlist_transfer = vec_xlists_transfer[idx];
                        XEntry::Remove_XList(xentry_actor, xlist_transfer);
                        XEntry::Add_XList(xentry_transfer, xlist_transfer);
                    }
                }
            }

            s64 count_bentry = Object_Ref::Get_BEntry_Count(actor, form_actor);
            s64 count_xentry = Object_Ref::Get_XEntry_Count(actor, form_actor);
            s64 count_remaining = count_bentry + count_xentry - count_xlists_kept;
            if (count_remaining > 0) {
                if (form_actor->IsPlayable()) {
                    XEntry_t *xentry_transfer = Object_Ref::Get_XEntry(transfer, form_actor, true);
                    XEntry::Inc_Count(xentry_transfer, count_remaining);
                }
            }

            if (count_xlists_kept == 0 && count_bentry == 0) {
                vec_xentries_destroy.push_back(xentry_actor);
            } else {
                XEntry::Set_Count(xentry_actor, count_xlists_kept - count_bentry);
            }
        }
        for (u64 idx = 0, size = vec_xentries_destroy.size(); idx < size; idx += 1) {
            XEntry_t *xentry_destroy = vec_xentries_destroy[idx];
            Object_Ref::Remove_XEntry(actor, xentry_destroy);
            XEntry::Destroy(xentry_destroy);
        }
    }

    void Cache_Worn(Actor *actor,
                    TESForm *linchpin,
                    TESObjectREFR *cache_out
    ) {
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

            // Because we don't know if we'll need xentry_cache, we cache xlists before ever calling Get_XEntry.
            std::vector<XList_t *> vec_xlists_worn;
            vec_xlists_worn.reserve(2);

            for (XLists_t::Iterator it_xlist_actor = xentry_actor->extendDataList->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                XList_t *xlist_actor = it_xlist_actor.Get();
                if (!xlist_actor) {
                    continue;
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

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    bool Has_Outfit2(StaticFunctionTag *,
                     Actor *actor,
                     TESForm *linchpin,
                     TESObjectREFR *vanilla,
                     TESObjectREFR *custom
    ) {
        return Actor2::Has_Outfit2(actor, linchpin, vanilla, custom);
    }

    void Set_Outfit2(StaticFunctionTag *,
                     Actor *actor,
                     TESForm *linchpin,
                     TESObjectREFR *vanilla,
                     TESObjectREFR *custom,
                     TESObjectREFR *trash,
                     TESObjectREFR *transfer
    ) {
        return Actor2::Set_Outfit2(actor, linchpin, vanilla, custom, trash, transfer);

        _MESSAGE("\nVanilla Partition:");
        Object_Ref::Log_XContainer(vanilla);

        _MESSAGE("\nCustom Partition:");
        Object_Ref::Log_XContainer(custom);

        _MESSAGE("\nActor Before:");
        Object_Ref::Log_XContainer(actor);

        Actor2::Set_Outfit2(actor, linchpin, vanilla, custom, trash, transfer);

        _MESSAGE("\nActor After:");
        Object_Ref::Log_XContainer(actor);

        _MESSAGE("\nTrash:");
        Object_Ref::Log_XContainer(trash);

        _MESSAGE("\nTransfer:");
        Object_Ref::Log_XContainer(transfer);
    }
    void Set_Outfit2_Dead(StaticFunctionTag *,
                          Actor *actor,
                          TESForm *linchpin,
                          TESObjectREFR *vanilla,
                          TESObjectREFR *custom,
                          TESObjectREFR *trash,
                          TESObjectREFR *transfer
    ) {
        return Actor2::Set_Outfit2_Dead(actor, linchpin, vanilla, custom, trash, transfer);
    }

    void Cache_Worn(StaticFunctionTag *,
                    Actor *actor,
                    TESForm *linchpin,
                    TESObjectREFR *cache_out
    ) {
        return Actor2::Cache_Worn(actor, linchpin, cache_out);
    }

    void Test(VMClassRegistry* registry, UInt32 stack_id, StaticFunctionTag*) {
        _MESSAGE("stack_id: %i", stack_id);
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
            new NativeFunction4 <StaticFunctionTag, bool, Actor *, TESForm *, TESObjectREFR *, TESObjectREFR *>(
                "Actor_Has_Outfit2",
                "doticu_npcp",
                Actor2::Exports::Has_Outfit2,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction6 <StaticFunctionTag, void, Actor *, TESForm *, TESObjectREFR *, TESObjectREFR *, TESObjectREFR *, TESObjectREFR *>(
                "Actor_Set_Outfit2",
                "doticu_npcp",
                Actor2::Exports::Set_Outfit2,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction6 <StaticFunctionTag, void, Actor *, TESForm *, TESObjectREFR *, TESObjectREFR *, TESObjectREFR *, TESObjectREFR *>(
                "Actor_Set_Outfit2_Dead",
                "doticu_npcp",
                Actor2::Exports::Set_Outfit2_Dead,
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
            new NativeFunction0 <StaticFunctionTag, void>(
                "Actor_Test",
                "doticu_npcp",
                Actor2::Exports::Test,
                registry)
        );

        return true;
    }

}}}
