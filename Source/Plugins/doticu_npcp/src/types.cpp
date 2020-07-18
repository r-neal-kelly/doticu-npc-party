/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "types.h"
#include "utils.h"
#include "string2.h"

namespace doticu_npcp {

    Bool_t Actor_Base_Data_t::Is_Unique()
    {
        return Utils::Is_Bit_On(flags, IS_UNIQUE);
    }

    Bool_t Actor_Base_Data_t::Is_Ghost()
    {
        return Utils::Is_Bit_On(flags, IS_GHOST);
    }

    void ExtraTextDisplay::Force_Rename(String_t new_name)
    {
        name = new_name;
        message = nullptr;
        owner = nullptr;
        flag = ExtraTextDisplay::CUSTOM;
        extra_health = 1.0f;
        custom_length = String2::Length(new_name);
        _MESSAGE("%u", custom_length);
    }

}
