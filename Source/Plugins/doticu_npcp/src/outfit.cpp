/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "outfit.h"
#include "utils.h"

namespace doticu_npcp { namespace Outfit {

    void Add_Item(Outfit_t* outfit, Form_t* form)
    {
        NPCP_ASSERT(outfit && form);
        tArray<Form_t*>& items = outfit->armorOrLeveledItemArray;
        if (items.GetItemIndex(form) < 0) {
            items.Push(form);
        }
    }

    void Remove_Item(Outfit_t* outfit, Form_t* form)
    {
        NPCP_ASSERT(outfit && form);
        tArray<Form_t*>& items = outfit->armorOrLeveledItemArray;
        SInt64 item_idx = items.GetItemIndex(form);
        if (item_idx > -1) {
            items.Remove(static_cast<UInt32>(item_idx));
        }
    }

}}
