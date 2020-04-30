/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <cctype>
#include "doticu_npcp.h"

namespace doticu_npcp {

    int Aliases_Sort_Compare_Name(const void *ptr_item_a, const void *ptr_item_b);
    int Aliases_Sort_Compare_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b);
    int Aliases_Sort_Compare_Rating_Name(const void *ptr_item_a, const void *ptr_item_b);
    int Aliases_Sort_Compare_Rating_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b);

    int Aliases_Get_Race_Names_Compare(const void *ptr_item_a, const void *ptr_item_b);

    int Aliases_Get_Initial_Letters_Compare(const void *ptr_item_a, const void *ptr_item_b);

    enum Aliases_Filter_Flags {
        IS_ALIVE, IS_DEAD,
        IS_ORIGINAL, IS_CLONE,
        IS_UNIQUE, IS_GENERIC,
        IS_FOLLOWER, ISNT_FOLLOWER,
        IS_SETTLER, ISNT_SETTLER,
        IS_IMMOBILE, ISNT_IMMOBILE,
        IS_THRALL, ISNT_THRALL,
        IS_SNEAK, ISNT_SNEAK,
        IS_PARALYZED, ISNT_PARALYZED,
        IS_MANNEQUIN, ISNT_MANNEQUIN,
        IS_REANIMATED, ISNT_REANIMATED
    };

    bool String_Starts_With_Caseless(const char *str_a, const char *str_b);
    bool String_Contains_Caseless(const char *str_a, const char *str_b);
}
