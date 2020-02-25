/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameExtraData.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"
#include "doticu_npcp.h"

namespace doticu_npcp {

    void Outfit_Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
        // changes are NOT lost on load game, but they are lost after changing outfits.
        if (!outfit || !form_item) {
            _MESSAGE("    Outfit_Add_Item: missing param");
            return;
        }

        tArray<TESForm *> *arr_items = &outfit->armorOrLeveledItemArray;
        if (!arr_items) {
            _MESSAGE("    Outfit_Add_Item: outfit is missing armorOrLeveledItemArray");
            return;
        }

        SInt64 idx_item = arr_items->GetItemIndex(form_item);
        if (idx_item < 0) {
            arr_items->Push(form_item);
        }
    }

    void Outfit_Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
        // changes are NOT lost on load game, but they are lost after changing outfits.
        if (!outfit || !form_item) {
            return;
        }

        tArray<TESForm *> *arr_items = &outfit->armorOrLeveledItemArray;
        if (!arr_items) {
            return;
        }

        SInt64 idx_item = arr_items->GetItemIndex(form_item);
        if (idx_item > -1) {
            // as long as it's greater than -1, it should be fine to cast to unsigned
            arr_items->Remove((UInt64)idx_item);
        }
    }

    void Actor_Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit) {
        if (!ref_actor || !outfit) {
            return;
        }

        // this is the leveled/real base which carries the outfits.
        // this will not save the base oufit after a full game-load.
        // quick tests have shown that allowing the original ActorBase.SetOutfit()
        // does not cause the outfit bug. It's something in the original ObjectReference.SetOutfit()
        TESNPC *base_actor = (TESNPC *)ref_actor->baseForm;
        if (is_sleep_outfit) {
            base_actor->sleepOutfit = outfit;
        } else {
            base_actor->defaultOutfit = outfit;
        }

        // passing true keeps items that were previously in inventory.
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

        // it would be nice to unequip everything that doesn't belong in outfit as well.
        // but that requires looping over actor inventory, out of my knowledge right noe

        return;



        // I'm really surprised how complicated the inventory system is. I'm leaving this here to learn more later.
        // extraData appears to be a list of of BSExtraData, which is a base-class of ExtraContainerChanges.
        // if I understand correctly, this object is used to add stuff in addition to the base container of ref.
        // GetByType finds the BSExtraData in the list that we are looking for in particular.
        ExtraContainerChanges *container_changes = (ExtraContainerChanges *)(ref_actor->extraData.GetByType(kExtraData_ContainerChanges));
        if (!container_changes) {
            return;
        }

        // this is a list of all the different items that are in the extra container, as far as I understand
        tList<InventoryEntryData> *list_entries = container_changes->data->objList;
        if (!list_entries) {
            return;
        }

        // it's interesting that the print out shows some of the forms multiple times.
        // I understand there is some kind of split between items in the inventory, but
        // it is not at all clear to me how that works.
        tList<InventoryEntryData>::Iterator it = list_entries->Begin();
        while (!it.End()) {
            InventoryEntryData *entry = it.Get();
            TESForm *form = entry->type;
            TESFullName *full_name = DYNAMIC_CAST(form, TESForm, TESFullName);

            _MESSAGE("    %s, is_playable: %d", full_name->name.data, form->IsPlayable());

            ++it;
        }

        //InventoryEntryData *entry_data = container_changes->data->FindItemEntry();

        return;
    }

    bool Register_Functions(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>("Outfit_Add_Item",
                                                                                  "doticu_npcp",
                                                                                  doticu_npcp::Outfit_Add_Item,
                                                                                  registry));
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>("Outfit_Remove_Item",
                                                                                  "doticu_npcp",
                                                                                  doticu_npcp::Outfit_Remove_Item,
                                                                                  registry));
        registry->RegisterFunction(
            new NativeFunction2 <Actor, void, BGSOutfit *, bool>("SetOutfit",
                                                                 "Actor",
                                                                 doticu_npcp::Actor_Set_Outfit,
                                                                 registry));

        return true;
    }

}
