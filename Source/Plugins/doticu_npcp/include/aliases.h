/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Aliases {

    enum Filter_Flags {
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

    int Compare_Name(const void *ptr_item_a, const void *ptr_item_b);
    int Compare_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b);
    int Compare_Rating_Name(const void *ptr_item_a, const void *ptr_item_b);
    int Compare_Rating_Name_Caseless(const void *ptr_item_a, const void *ptr_item_b);

    int Compare_Race_Names(const void *ptr_item_a, const void *ptr_item_b);

    bool Has_Head(VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head);
    SInt32 Count_Heads(VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head, bool do_print = false);

}}

namespace doticu_npcp { namespace Aliases { namespace Exports {

    VMResultArray<BGSBaseAlias *> Slice(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr, UInt32 idx_from, UInt32 idx_to_ex);
    VMResultArray<BGSBaseAlias *> Sort(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases, BSFixedString str_algorithm);
    VMResultArray<BGSBaseAlias *> Filter(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases, VMArray<BSFixedString> arr_strings, VMArray<SInt32> arr_ints);
    UInt32 Filter_Flag(StaticFunctionTag *, UInt32 int_flags, BSFixedString str_command, BSFixedString str_flag);
    VMResultArray<BSFixedString> Get_Race_Names(StaticFunctionTag *, VMArray<BGSBaseAlias *> arr_aliases);

    bool Has_Head(StaticFunctionTag *, VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head);
    SInt32 Count_Heads(StaticFunctionTag *, VMArray<BGSBaseAlias *> aliases, TESNPC *base_with_head, bool do_print = false);

    bool Register(VMClassRegistry *registry);

}}}
