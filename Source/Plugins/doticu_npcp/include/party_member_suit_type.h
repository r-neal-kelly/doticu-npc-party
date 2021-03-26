/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Member_Suit_Type_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = static_cast<value_type>(-1),

            MEMBER      = static_cast<value_type>(0),
            IMMOBILE,
            SETTLER,
            THRALL,
            FOLLOWER,
            VANILLA,
            DEFAULT,

            _TOTAL_,
        };

    public:
        using Enum_t::Enum_t;
    };

}}
