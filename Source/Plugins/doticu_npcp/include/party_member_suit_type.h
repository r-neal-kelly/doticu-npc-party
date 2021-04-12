/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "consts.h"
#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Member_Suit_Type_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            MEMBER,
            THRALL,
            EXTERIOR,
            INTERIOR,
            CIVILIZED,
            DANGEROUS,
            SANDBOXER,
            SLEEPER,
            SITTER,
            EATER,
            GUARD,
            FOLLOWER,
            SETTLEMENT,
            HOME,
            INN,
            COMBATANT,
            IMMOBILE,
            MANNEQUIN,
            ACTIVE,

            _TOTAL_,
        };

        /*
            for each suit, I would like to give the option of filling it manually, either with or without unplayable items (like the default suit.)
            and we can clear it too, by sending to chests of course. Unplayable items can't be kept obviously.

            it's probably a bad idea to have each of these stored in their own references. what we can do is add markers to them
            and store them in one reference per member. we would have to change the ownership and use a faction as a flag.
            and when we outfit the member, we just copy over that item, and add x_outfit and change the flag to active faction.

            if there are no items to copy over, we add a blank x_outfit item to the actor.

            we also need an option to turn off strict outfitting, and just let foreign playable outfittable items stay.
            unplayable items always stay.

            we'll also set a blank outfit on each custom base, an actual form mind you. Then I think we should be able to fix up their
            inventories a little easier? or should we just stick with whatever is on the original base, in case there is any load
            confusion? (if we can change to custom base before the game sets the default outfit on ref). maybe what we should
            do is just set nullptr outfits to a blank and save it on the original base, but only if it's missing. no items in outfit!
        */

    public:
        static inline Bool_t Is_Valid(value_type value)
        {
            return value > _NONE_ && value < _TOTAL_;
        }

        static inline some<const char* const*> Strings()
        {
            static const char* const strings[_TOTAL_] =
            {
                SKYLIB_ENUM_TO_STRING(MEMBER),
                SKYLIB_ENUM_TO_STRING(THRALL),
                SKYLIB_ENUM_TO_STRING(EXTERIOR),
                SKYLIB_ENUM_TO_STRING(INTERIOR),
                SKYLIB_ENUM_TO_STRING(CIVILIZED),
                SKYLIB_ENUM_TO_STRING(DANGEROUS),
                SKYLIB_ENUM_TO_STRING(SANDBOXER),
                SKYLIB_ENUM_TO_STRING(SLEEPER),
                SKYLIB_ENUM_TO_STRING(SITTER),
                SKYLIB_ENUM_TO_STRING(EATER),
                SKYLIB_ENUM_TO_STRING(GUARD),
                SKYLIB_ENUM_TO_STRING(FOLLOWER),
                SKYLIB_ENUM_TO_STRING(SETTLEMENT),
                SKYLIB_ENUM_TO_STRING(HOME),
                SKYLIB_ENUM_TO_STRING(INN),
                SKYLIB_ENUM_TO_STRING(COMBATANT),
                SKYLIB_ENUM_TO_STRING(IMMOBILE),
                SKYLIB_ENUM_TO_STRING(MANNEQUIN),
                SKYLIB_ENUM_TO_STRING(ACTIVE),
            };

            return strings;
        }

        static inline some<const char*> To_String(value_type value)
        {
            return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
        }

        static inline value_type From_String(maybe<const char*> string)
        {
            return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
        }

        static inline maybe<Faction_t*> To_Faction(value_type value)
        {
            if (value == ACTIVE)            return Consts_t::NPCP::Faction::Suit_Active();
            else if (value == CIVILIZED)    return Consts_t::NPCP::Faction::Suit_Civilized();
            else if (value == COMBATANT)    return Consts_t::NPCP::Faction::Suit_Combatant();
            else if (value == DANGEROUS)    return Consts_t::NPCP::Faction::Suit_Dangerous();
            else if (value == EATER)        return Consts_t::NPCP::Faction::Suit_Eater();
            else if (value == EXTERIOR)     return Consts_t::NPCP::Faction::Suit_Exterior();
            else if (value == FOLLOWER)     return Consts_t::NPCP::Faction::Suit_Follower();
            else if (value == GUARD)        return Consts_t::NPCP::Faction::Suit_Guard();
            else if (value == HOME)         return Consts_t::NPCP::Faction::Suit_Home();
            else if (value == IMMOBILE)     return Consts_t::NPCP::Faction::Suit_Immobile();
            else if (value == INN)          return Consts_t::NPCP::Faction::Suit_Inn();
            else if (value == INTERIOR)     return Consts_t::NPCP::Faction::Suit_Interior();
            else if (value == MANNEQUIN)    return Consts_t::NPCP::Faction::Suit_Mannequin();
            else if (value == MEMBER)       return Consts_t::NPCP::Faction::Suit_Member();
            else if (value == SANDBOXER)    return Consts_t::NPCP::Faction::Suit_Sandboxer();
            else if (value == SETTLEMENT)   return Consts_t::NPCP::Faction::Suit_Settlement();
            else if (value == SITTER)       return Consts_t::NPCP::Faction::Suit_Sitter();
            else if (value == SLEEPER)      return Consts_t::NPCP::Faction::Suit_Sleeper();
            else if (value == THRALL)       return Consts_t::NPCP::Faction::Suit_Thrall();
            else                            return none<Faction_t*>();
        }

        static inline value_type From_Faction(maybe<Faction_t*> faction)
        {
            if (faction == Consts_t::NPCP::Faction::Suit_Active())          return ACTIVE;
            else if (faction == Consts_t::NPCP::Faction::Suit_Civilized())  return CIVILIZED;
            else if (faction == Consts_t::NPCP::Faction::Suit_Combatant())  return COMBATANT;
            else if (faction == Consts_t::NPCP::Faction::Suit_Dangerous())  return DANGEROUS;
            else if (faction == Consts_t::NPCP::Faction::Suit_Eater())      return EATER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Exterior())   return EXTERIOR;
            else if (faction == Consts_t::NPCP::Faction::Suit_Follower())   return FOLLOWER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Guard())      return GUARD;
            else if (faction == Consts_t::NPCP::Faction::Suit_Home())       return HOME;
            else if (faction == Consts_t::NPCP::Faction::Suit_Immobile())   return IMMOBILE;
            else if (faction == Consts_t::NPCP::Faction::Suit_Inn())        return INN;
            else if (faction == Consts_t::NPCP::Faction::Suit_Interior())   return INTERIOR;
            else if (faction == Consts_t::NPCP::Faction::Suit_Mannequin())  return MANNEQUIN;
            else if (faction == Consts_t::NPCP::Faction::Suit_Member())     return MEMBER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Sandboxer())  return SANDBOXER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Settlement()) return SETTLEMENT;
            else if (faction == Consts_t::NPCP::Faction::Suit_Sitter())     return SITTER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Sleeper())    return SLEEPER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Thrall())     return THRALL;
            else                                                            return _NONE_;
        }
    };

    class Member_Suit_Type_e :
        public Enum_Type_t<Member_Suit_Type_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;

    public:
        maybe<Faction_t*> As_Faction() const
        {
            return To_Faction(*this);
        }
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Party::Member_Suit_Type_e> :
        public none_enum<doticu_npcp::Party::Member_Suit_Type_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<doticu_npcp::Party::Member_Suit_Type_e> :
        public maybe_enum<doticu_npcp::Party::Member_Suit_Type_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<doticu_npcp::Party::Member_Suit_Type_e> :
        public some_enum<doticu_npcp::Party::Member_Suit_Type_e>
    {
    public:
        using some_enum::some_enum;
    };

}
