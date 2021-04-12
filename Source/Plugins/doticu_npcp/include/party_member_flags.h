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
            IS_BANISHED     = static_cast<value_type>(1 << 0),
            IS_CLONE        = static_cast<value_type>(1 << 1),
            IS_IMMOBILE     = static_cast<value_type>(1 << 2),
            IS_MANNEQUIN    = static_cast<value_type>(1 << 3),
            IS_REANIMATED   = static_cast<value_type>(1 << 4),
            IS_THRALL       = static_cast<value_type>(1 << 5),

            _TOTAL_         = 7,
        };

    public:
        using Enum_t::Enum_t;
    };

}}
