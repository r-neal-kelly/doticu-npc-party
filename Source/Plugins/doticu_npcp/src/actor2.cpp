/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"

namespace doticu_npcp { namespace Actor2 {

    bool Is_Worn(Actor *ref_actor, TESForm *ref_form) {
        if (!ref_actor || !ref_form) {
            return false;
        }

        ExtraContainerChanges *container_extra = Object_Ref::Get_Ref_Container(DYNAMIC_CAST(ref_actor, Actor, TESObjectREFR));
        if (container_extra) {
            for (tList<InventoryEntryData>::Iterator it_entry = container_extra->data->objList->Begin(); !it_entry.End(); ++it_entry) {
                InventoryEntryData *entry = it_entry.Get();
                if (entry && entry->type == ref_form && entry->extendDataList) {
                    for (tList<BaseExtraList>::Iterator it_xlist = entry->extendDataList->Begin(); !it_xlist.End(); ++it_xlist) {
                        BaseExtraList *xlist = it_xlist.Get();
                        if (xlist && xlist->HasType(kExtraData_Worn)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    void Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit) {
        if (!ref_actor || !outfit) {
            return;
        }

        // this is the leveled/real base which carries the outfits.
        // Thank you to Ian Patterson of SKSE for how to save the outfit!
        // Also, we're doing a dynamic cast, rather than static for TESNPC, because the library does
        TESNPC *base_actor = DYNAMIC_CAST(ref_actor->baseForm, TESForm, TESNPC);
        if (is_sleep_outfit) {
            base_actor->sleepOutfit = outfit;
            base_actor->MarkChanged(0x2000);
        } else {
            base_actor->defaultOutfit = outfit;
            base_actor->MarkChanged(0x1000);
        }

        // passing true keeps items that were previously in inventory.
        // it also stops aliased actors from becoming unaliased!
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
        ExtraContainerChanges *container_extra = Object_Ref::Get_Ref_Container(DYNAMIC_CAST(ref_actor, Actor, TESObjectREFR));
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

    bool Has_Changed_Outfit(StaticFunctionTag *, Actor *ref_actor, TESObjectREFR *ref_outfit, TESObjectREFR *ref_outfit2, TESForm *ref_linchpin) {
        // there are two outfits, one of them is a cache of vanilla outfit items, with pre-generated leveled items,
        // and the other is a super class of the vanilla outfit, which has items in addition to the BGSOutfit items
        // the linchpin is a form in the BGSOutfit, which must never be removed, to stop the engine from altering the inventory

        if (!ref_actor || !ref_outfit || !ref_outfit2 || !ref_linchpin) {
            _ERROR("Has_Outfit_Changed: invalid args");
            return false;
        }

        Object_Ref::Items items_actor = Object_Ref::Get_Items(DYNAMIC_CAST(ref_actor, Actor, TESObjectREFR));
        Object_Ref::Items items_outfit = Object_Ref::Get_Items(ref_outfit);
        Object_Ref::Items items_outfit2 = Object_Ref::Get_Items(ref_outfit2);

        // ref_actor may have items that aren't in the outfit
        for (u64 idx = 0, size = items_actor.forms.size(); idx < size; idx += 1) {
            TESForm *form = items_actor.forms[idx];
            if (form && form->formType != kFormType_Reference && form != ref_linchpin) {
                // we completely avoid any references and leave them alone
                // we need to keep the linchpin to avoid the engine refreshing outfit
                if (form->IsPlayable() || Is_Worn(ref_actor, form)) {
                    // any playable item is fair game, but only equipped unplayables are accounted for
                    if (!items_outfit.Has(form) && !items_outfit2.Has(form)) {
                        return true;
                    }
                }
            }
        }

        // ref_actor may be missing items that are in outfit
        for (u64 idx = 0, size = items_outfit.forms.size(); idx < size; idx += 1) {
            TESForm *form = items_outfit.forms[idx];
            if (form && items_actor.Count(form) != items_outfit.Count(form) + items_outfit2.Count(form)) {
                return true;
            }
        }

        // ref_actor may be missing items that are in outfit2
        for (u64 idx = 0, size = items_outfit2.forms.size(); idx < size; idx += 1) {
            TESForm *form = items_outfit2.forms[idx];
            if (form && items_actor.Count(form) != items_outfit.Count(form) + items_outfit2.Count(form)) {
                return true;
            }
        }

        return false;
    }

    void Refresh_Outfit(StaticFunctionTag *, Actor *ref_actor, TESObjectREFR *ref_outfit, TESObjectREFR *ref_outfit2, TESForm *ref_linchpin) {
        if (!ref_actor || !ref_outfit || !ref_outfit2 || !ref_linchpin) {
            _ERROR("Refresh_Outfit: invalid args");
            return;
        }

        TESObjectREFR *ref_actor_obj = DYNAMIC_CAST(ref_actor, Actor, TESObjectREFR);
        Object_Ref::Items items_actor = Object_Ref::Get_Items(ref_actor_obj);
        Object_Ref::Items items_outfit = Object_Ref::Get_Items(ref_outfit);
        Object_Ref::Items items_outfit2 = Object_Ref::Get_Items(ref_outfit2);

        // we wipe the inventory of everything but token (usually unplayable) items
        for (u64 idx = 0, size = items_actor.forms.size(); idx < size; idx += 1) {
            TESForm *form = items_actor.forms[idx];
            if (form && form->formType != kFormType_Reference && form != ref_linchpin) {
                // we completely avoid any references and leave them alone
                // we need to keep the linchpin to avoid the engine refreshing outfit
                if (form->IsPlayable() || form->IsArmor() || form->IsWeapon() || form->IsAmmo()) {
                    // any playable item is fair game, but any armor, weapons, and ammo have got to go
                    Object_Ref::Remove_Item(ref_actor_obj, form, items_actor.counts[idx]);
                }
            }
        }

        // and now we can cleanly add outfit items.
        for (u64 idx = 0, size = items_outfit.forms.size(); idx < size; idx += 1) {
            Object_Ref::Add_Item(ref_actor_obj, items_outfit.forms[idx], items_outfit.counts[idx]);
        }

        for (u64 idx = 0, size = items_outfit2.forms.size(); idx < size; idx += 1) {
            Object_Ref::Add_Item(ref_actor_obj, items_outfit2.forms[idx], items_outfit2.counts[idx]);
        }
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <Actor, void, BGSOutfit *, bool>(
                "SetOutfit",
                "Actor",
                Set_Outfit,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction4 <StaticFunctionTag, bool, Actor *, TESObjectREFR *, TESObjectREFR *, TESForm *>(
                "Actor_Has_Changed_Outfit",
                "doticu_npcp",
                Has_Changed_Outfit,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction4 <StaticFunctionTag, void, Actor *, TESObjectREFR *, TESObjectREFR *, TESForm *>(
                "Actor_Refresh_Outfit",
                "doticu_npcp",
                Refresh_Outfit,
                registry)
        );

        return true;
    }

}}}
