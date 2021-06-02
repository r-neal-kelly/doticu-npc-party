/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_Flags_Has_Suit_e_data :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            ARCHER,
            CIVILIZED,
            COMBATANT,
            COWARD,
            DANGEROUS,
            EATER,
            EXTERIOR,
            FOLLOWER,
            GUARD,
            HOME,
            IMMOBILE,
            INN,
            INTERIOR,
            MAGE,
            MANNEQUIN,
            MEMBER,
            SANDBOXER,
            SETTLEMENT,
            SITTER,
            SLEEPER,
            THRALL,
            WARRIOR,

            _TOTAL_,
        };
    };

    class Member_Flags_Has_Suit_e :
        public Enum_t<Word_t>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = 0,

            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, ARCHER),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, CIVILIZED),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, COMBATANT),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, COWARD),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, DANGEROUS),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, EATER),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, EXTERIOR),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, FOLLOWER),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, GUARD),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, HOME),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, IMMOBILE),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, INN),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, INTERIOR),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, MAGE),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, MANNEQUIN),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, MEMBER),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, SANDBOXER),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, SETTLEMENT),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, SITTER),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, SLEEPER),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, THRALL),
            SKYLIB_DEFINE_FLAG(Member_Flags_Has_Suit_e_data, WARRIOR),

            _TOTAL_ = Member_Flags_Has_Suit_e_data::_TOTAL_,
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
