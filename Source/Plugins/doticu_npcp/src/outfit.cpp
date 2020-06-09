/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "outfit.h"

namespace doticu_npcp { namespace Outfit {



}}

namespace doticu_npcp { namespace Outfit { namespace Exports {

    void Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
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

    void Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item) {
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

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>(
                "Outfit_Add_Item",
                "doticu_npcp",
                Add_Item,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>(
                "Outfit_Remove_Item",
                "doticu_npcp",
                Remove_Item,
                registry)
        );

        _MESSAGE("Added Outfit functions.");

        return true;
    }

}}}
