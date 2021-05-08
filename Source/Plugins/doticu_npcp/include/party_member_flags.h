/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Member_Flags_e_data :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            IS_BANISHED,
            IS_CLONE,
            IS_IMMOBILE,
            IS_MANNEQUIN,
            IS_REANIMATED,
            IS_SNEAK,
            IS_THRALL,

            _TOTAL_,
        };
    };

    class Member_Flags_e :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = 0,

            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_BANISHED),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_CLONE),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_IMMOBILE),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_MANNEQUIN),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_REANIMATED),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_SNEAK),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_THRALL),

            _TOTAL_ = Member_Flags_e_data::_TOTAL_,
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
