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
            IS_THRALL,

            HAS_CIVILIZED_SUIT,
            HAS_COMBATANT_SUIT,
            HAS_DANGEROUS_SUIT,
            HAS_EATER_SUIT,
            HAS_EXTERIOR_SUIT,
            HAS_FOLLOWER_SUIT,
            HAS_GUARD_SUIT,
            HAS_HOME_SUIT,
            HAS_IMMOBILE_SUIT,
            HAS_INN_SUIT,
            HAS_INTERIOR_SUIT,
            HAS_MANNEQUIN_SUIT,
            HAS_MEMBER_SUIT,
            HAS_SANDBOXER_SUIT,
            HAS_SETTLEMENT_SUIT,
            HAS_SITTER_SUIT,
            HAS_SLEEPER_SUIT,
            HAS_THRALL_SUIT,

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
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, IS_THRALL),

            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_CIVILIZED_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_COMBATANT_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_DANGEROUS_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_EATER_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_EXTERIOR_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_FOLLOWER_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_GUARD_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_HOME_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_IMMOBILE_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_INN_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_INTERIOR_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_MANNEQUIN_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_MEMBER_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_SANDBOXER_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_SETTLEMENT_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_SITTER_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_SLEEPER_SUIT),
            SKYLIB_DEFINE_FLAG(Member_Flags_e_data, HAS_THRALL_SUIT),

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
