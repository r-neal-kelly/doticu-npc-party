/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Follower_Flags_e_data :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            IS_RETREATER,
            IS_SADDLER,
            IS_SOJOURNER,

            _TOTAL_,
        };
    };

    class Follower_Flags_e :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = 0,

            SKYLIB_DEFINE_FLAG(Follower_Flags_e_data, IS_RETREATER),
            SKYLIB_DEFINE_FLAG(Follower_Flags_e_data, IS_SADDLER),
            SKYLIB_DEFINE_FLAG(Follower_Flags_e_data, IS_SOJOURNER),

            _TOTAL_ = Follower_Flags_e_data::_TOTAL_,
        };

    public:
        using Enum_t::Enum_t;

    public:
        explicit operator Bool_t() const
        {
            return this->value != _NONE_;
        }
    };

}}
