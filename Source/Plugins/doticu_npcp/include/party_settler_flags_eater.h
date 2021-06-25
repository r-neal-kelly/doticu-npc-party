/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_flags.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Flags_Eater_e :
        public Settler_Flags_e
    {
    public:
        enum enum_type : value_type
        {
            ALLOW_ALREADY_HELD_FOOD = static_cast<value_type>(1 << 16),
            ALLOW_CONVERSATION      = static_cast<value_type>(1 << 17),
            ALLOW_EATING            = static_cast<value_type>(1 << 18),
            ALLOW_FAKE_FOOD         = static_cast<value_type>(1 << 19),
            ALLOW_HORSE_RIDING      = static_cast<value_type>(1 << 20),
            ALLOW_IDLE_MARKERS      = static_cast<value_type>(1 << 21),
            ALLOW_SITTING           = static_cast<value_type>(1 << 22),
            ALLOW_SLEEPING          = static_cast<value_type>(1 << 23),
            ALLOW_SPECIAL_FURNITURE = static_cast<value_type>(1 << 24),
            ALLOW_WANDERING         = static_cast<value_type>(1 << 25),
            ONLY_PREFERRED_PATH     = static_cast<value_type>(1 << 26),
            UNLOCK_ON_ARRIVAL       = static_cast<value_type>(1 << 27),

            _TOTAL_                 = 28,
        };

    public:
        using Settler_Flags_e::Settler_Flags_e;
    };

}}
