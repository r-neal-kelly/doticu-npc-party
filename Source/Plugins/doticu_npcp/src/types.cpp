/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "types.h"
#include "utils.h"

namespace doticu_npcp {

    Bool_t Actor_Base_Data_t::Is_Unique()
    {
        return Utils::Is_Bit_On(flags, IS_UNIQUE);
    }

    Bool_t Actor_Base_Data_t::Is_Ghost()
    {
        return Utils::Is_Bit_On(flags, IS_GHOST);
    }

}
