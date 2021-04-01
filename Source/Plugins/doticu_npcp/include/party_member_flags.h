/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Member_Flags_e :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            IS_BANISHED,
            IS_CLONE,
            IS_IMMOBILE,
            IS_MANNEQUIN,
            IS_PARALYZED,
            IS_REANIMATED,
            IS_THRALL,

            _TOTAL_,
        };

    public:
        using Enum_t::Enum_t;
    };

}}
