/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_npcp.h"

namespace doticu_npcp {

    void Outfit_Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
        // changes are lost when the outfit is requipped, but not on load save game
        if (!outfit || !form_item) {
            return;
        }

        tArray<TESForm *> *arr_items = &outfit->armorOrLeveledItemArray;
        if (!arr_items) {
            return;
        }

        SInt64 idx_item = arr_items->GetItemIndex(form_item);
        if (idx_item < 0) {
            arr_items->Push(form_item);
        }
    }

    void Outfit_Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
        // changes are lost when the outfit is requipped, but not on load save game
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

    void ActorBase_Set_Outfit(TESNPC *base_actor, BGSOutfit *outfit, bool is_sleep_outfit) {
        if (!base_actor || !outfit) {
            return;
        }
        
        if (is_sleep_outfit) {
            base_actor->sleepOutfit = outfit;
        } else {
            base_actor->defaultOutfit = outfit;
        }
    }

    void Actor_Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit) {
        if (!ref_actor || !outfit) {
            return;
        }

        // this is the leveled/real base which carries the outfits
        TESNPC *base_actor = (TESNPC *)ref_actor->baseForm;
        if (is_sleep_outfit) {
            base_actor->sleepOutfit = outfit;
        } else {
            base_actor->defaultOutfit = outfit;
        }

        // passing true keeps items that were previously in inventory.
        // using this does indeed fix the horrible outfit bug but it
        // sometimes keeps items that are equipped over the default
        ref_actor->ResetInventory(true);

        // you can use GetNumForms and GetNthForm to traverse ref_actor inventory
        // you can get the ExtraContainerChanges, see either of the above's implementation
        // use the ExtraContainerChanges to get the InventoryEntryData and see if 'isItemWorn'
        // and you can check if the item is in outfit by finding it in array

        // now how to remove it? it might be way more efficient to just try and go through it all myself.
        // I'm really surprise how complicated the inventory system is

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
            new NativeFunction2 <TESNPC, void, BGSOutfit *, bool>("SetOutfit",
                                                                  "ActorBase",
                                                                  doticu_npcp::ActorBase_Set_Outfit,
                                                                  registry));
        registry->RegisterFunction(
            new NativeFunction2 <Actor, void, BGSOutfit *, bool>("SetOutfit",
                                                                 "Actor",
                                                                 doticu_npcp::Actor_Set_Outfit,
                                                                 registry));

        return true;
    }

}
