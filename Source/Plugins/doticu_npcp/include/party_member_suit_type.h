/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "consts.h"
#include "intrinsic.h"
#include "party_member_flags_has_suit.h"
#include "party_member_flags_only_playables.h"
#include "party_member_suit_template.h"

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
            WARRIOR,
            MAGE,
            ARCHER,
            COWARD,
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
                SKYLIB_ENUM_TO_STRING(WARRIOR),
                SKYLIB_ENUM_TO_STRING(MAGE),
                SKYLIB_ENUM_TO_STRING(ARCHER),
                SKYLIB_ENUM_TO_STRING(COWARD),
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
            else if (value == ARCHER)       return Consts_t::NPCP::Faction::Suit_Archer();
            else if (value == CIVILIZED)    return Consts_t::NPCP::Faction::Suit_Civilized();
            else if (value == COMBATANT)    return Consts_t::NPCP::Faction::Suit_Combatant();
            else if (value == COWARD)       return Consts_t::NPCP::Faction::Suit_Coward();
            else if (value == DANGEROUS)    return Consts_t::NPCP::Faction::Suit_Dangerous();
            else if (value == EATER)        return Consts_t::NPCP::Faction::Suit_Eater();
            else if (value == EXTERIOR)     return Consts_t::NPCP::Faction::Suit_Exterior();
            else if (value == FOLLOWER)     return Consts_t::NPCP::Faction::Suit_Follower();
            else if (value == GUARD)        return Consts_t::NPCP::Faction::Suit_Guard();
            else if (value == HOME)         return Consts_t::NPCP::Faction::Suit_Home();
            else if (value == IMMOBILE)     return Consts_t::NPCP::Faction::Suit_Immobile();
            else if (value == INN)          return Consts_t::NPCP::Faction::Suit_Inn();
            else if (value == INTERIOR)     return Consts_t::NPCP::Faction::Suit_Interior();
            else if (value == MAGE)         return Consts_t::NPCP::Faction::Suit_Mage();
            else if (value == MANNEQUIN)    return Consts_t::NPCP::Faction::Suit_Mannequin();
            else if (value == MEMBER)       return Consts_t::NPCP::Faction::Suit_Member();
            else if (value == SANDBOXER)    return Consts_t::NPCP::Faction::Suit_Sandboxer();
            else if (value == SETTLEMENT)   return Consts_t::NPCP::Faction::Suit_Settlement();
            else if (value == SITTER)       return Consts_t::NPCP::Faction::Suit_Sitter();
            else if (value == SLEEPER)      return Consts_t::NPCP::Faction::Suit_Sleeper();
            else if (value == THRALL)       return Consts_t::NPCP::Faction::Suit_Thrall();
            else if (value == WARRIOR)      return Consts_t::NPCP::Faction::Suit_Warrior();
            else                            return none<Faction_t*>();
        }

        static inline value_type From_Faction(maybe<Faction_t*> faction)
        {
            if (faction == Consts_t::NPCP::Faction::Suit_Active())          return ACTIVE;
            else if (faction == Consts_t::NPCP::Faction::Suit_Archer())     return ARCHER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Civilized())  return CIVILIZED;
            else if (faction == Consts_t::NPCP::Faction::Suit_Combatant())  return COMBATANT;
            else if (faction == Consts_t::NPCP::Faction::Suit_Coward())     return COWARD;
            else if (faction == Consts_t::NPCP::Faction::Suit_Dangerous())  return DANGEROUS;
            else if (faction == Consts_t::NPCP::Faction::Suit_Eater())      return EATER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Exterior())   return EXTERIOR;
            else if (faction == Consts_t::NPCP::Faction::Suit_Follower())   return FOLLOWER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Guard())      return GUARD;
            else if (faction == Consts_t::NPCP::Faction::Suit_Home())       return HOME;
            else if (faction == Consts_t::NPCP::Faction::Suit_Immobile())   return IMMOBILE;
            else if (faction == Consts_t::NPCP::Faction::Suit_Inn())        return INN;
            else if (faction == Consts_t::NPCP::Faction::Suit_Interior())   return INTERIOR;
            else if (faction == Consts_t::NPCP::Faction::Suit_Mage())       return MAGE;
            else if (faction == Consts_t::NPCP::Faction::Suit_Mannequin())  return MANNEQUIN;
            else if (faction == Consts_t::NPCP::Faction::Suit_Member())     return MEMBER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Sandboxer())  return SANDBOXER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Settlement()) return SETTLEMENT;
            else if (faction == Consts_t::NPCP::Faction::Suit_Sitter())     return SITTER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Sleeper())    return SLEEPER;
            else if (faction == Consts_t::NPCP::Faction::Suit_Thrall())     return THRALL;
            else if (faction == Consts_t::NPCP::Faction::Suit_Warrior())    return WARRIOR;
            else                                                            return _NONE_;
        }

        static inline Member_Flags_Has_Suit_e To_Member_Flag_Has_Suit(value_type value)
        {
            if (value == ARCHER)            return Member_Flags_Has_Suit_e::ARCHER;
            else if (value == CIVILIZED)    return Member_Flags_Has_Suit_e::CIVILIZED;
            else if (value == COMBATANT)    return Member_Flags_Has_Suit_e::COMBATANT;
            else if (value == COWARD)       return Member_Flags_Has_Suit_e::COWARD;
            else if (value == DANGEROUS)    return Member_Flags_Has_Suit_e::DANGEROUS;
            else if (value == EATER)        return Member_Flags_Has_Suit_e::EATER;
            else if (value == EXTERIOR)     return Member_Flags_Has_Suit_e::EXTERIOR;
            else if (value == FOLLOWER)     return Member_Flags_Has_Suit_e::FOLLOWER;
            else if (value == GUARD)        return Member_Flags_Has_Suit_e::GUARD;
            else if (value == HOME)         return Member_Flags_Has_Suit_e::HOME;
            else if (value == IMMOBILE)     return Member_Flags_Has_Suit_e::IMMOBILE;
            else if (value == INN)          return Member_Flags_Has_Suit_e::INN;
            else if (value == INTERIOR)     return Member_Flags_Has_Suit_e::INTERIOR;
            else if (value == MAGE)         return Member_Flags_Has_Suit_e::MAGE;
            else if (value == MANNEQUIN)    return Member_Flags_Has_Suit_e::MANNEQUIN;
            else if (value == MEMBER)       return Member_Flags_Has_Suit_e::MEMBER;
            else if (value == SANDBOXER)    return Member_Flags_Has_Suit_e::SANDBOXER;
            else if (value == SETTLEMENT)   return Member_Flags_Has_Suit_e::SETTLEMENT;
            else if (value == SITTER)       return Member_Flags_Has_Suit_e::SITTER;
            else if (value == SLEEPER)      return Member_Flags_Has_Suit_e::SLEEPER;
            else if (value == THRALL)       return Member_Flags_Has_Suit_e::THRALL;
            else if (value == WARRIOR)      return Member_Flags_Has_Suit_e::WARRIOR;
            else                            return Member_Flags_Has_Suit_e::_NONE_;
        }

        static inline value_type From_Member_Has_Suit_Flag(Member_Flags_Has_Suit_e flag)
        {
            if (flag == Member_Flags_Has_Suit_e::ARCHER)            return ARCHER;
            else if (flag == Member_Flags_Has_Suit_e::CIVILIZED)    return CIVILIZED;
            else if (flag == Member_Flags_Has_Suit_e::COMBATANT)    return COMBATANT;
            else if (flag == Member_Flags_Has_Suit_e::COWARD)       return COWARD;
            else if (flag == Member_Flags_Has_Suit_e::DANGEROUS)    return DANGEROUS;
            else if (flag == Member_Flags_Has_Suit_e::EATER)        return EATER;
            else if (flag == Member_Flags_Has_Suit_e::EXTERIOR)     return EXTERIOR;
            else if (flag == Member_Flags_Has_Suit_e::FOLLOWER)     return FOLLOWER;
            else if (flag == Member_Flags_Has_Suit_e::GUARD)        return GUARD;
            else if (flag == Member_Flags_Has_Suit_e::HOME)         return HOME;
            else if (flag == Member_Flags_Has_Suit_e::IMMOBILE)     return IMMOBILE;
            else if (flag == Member_Flags_Has_Suit_e::INN)          return INN;
            else if (flag == Member_Flags_Has_Suit_e::INTERIOR)     return INTERIOR;
            else if (flag == Member_Flags_Has_Suit_e::MAGE)         return MAGE;
            else if (flag == Member_Flags_Has_Suit_e::MANNEQUIN)    return MANNEQUIN;
            else if (flag == Member_Flags_Has_Suit_e::MEMBER)       return MEMBER;
            else if (flag == Member_Flags_Has_Suit_e::SANDBOXER)    return SANDBOXER;
            else if (flag == Member_Flags_Has_Suit_e::SETTLEMENT)   return SETTLEMENT;
            else if (flag == Member_Flags_Has_Suit_e::SITTER)       return SITTER;
            else if (flag == Member_Flags_Has_Suit_e::SLEEPER)      return SLEEPER;
            else if (flag == Member_Flags_Has_Suit_e::THRALL)       return THRALL;
            else if (flag == Member_Flags_Has_Suit_e::WARRIOR)      return WARRIOR;
            else                                                    return _NONE_;
        }

        static inline Member_Flags_Only_Playables_e To_Member_Flag_Only_Playables(value_type value)
        {
            if (value == ARCHER)            return Member_Flags_Only_Playables_e::ARCHER;
            else if (value == CIVILIZED)    return Member_Flags_Only_Playables_e::CIVILIZED;
            else if (value == COMBATANT)    return Member_Flags_Only_Playables_e::COMBATANT;
            else if (value == COWARD)       return Member_Flags_Only_Playables_e::COWARD;
            else if (value == DANGEROUS)    return Member_Flags_Only_Playables_e::DANGEROUS;
            else if (value == EATER)        return Member_Flags_Only_Playables_e::EATER;
            else if (value == EXTERIOR)     return Member_Flags_Only_Playables_e::EXTERIOR;
            else if (value == FOLLOWER)     return Member_Flags_Only_Playables_e::FOLLOWER;
            else if (value == GUARD)        return Member_Flags_Only_Playables_e::GUARD;
            else if (value == HOME)         return Member_Flags_Only_Playables_e::HOME;
            else if (value == IMMOBILE)     return Member_Flags_Only_Playables_e::IMMOBILE;
            else if (value == INN)          return Member_Flags_Only_Playables_e::INN;
            else if (value == INTERIOR)     return Member_Flags_Only_Playables_e::INTERIOR;
            else if (value == MAGE)         return Member_Flags_Only_Playables_e::MAGE;
            else if (value == MANNEQUIN)    return Member_Flags_Only_Playables_e::MANNEQUIN;
            else if (value == MEMBER)       return Member_Flags_Only_Playables_e::MEMBER;
            else if (value == SANDBOXER)    return Member_Flags_Only_Playables_e::SANDBOXER;
            else if (value == SETTLEMENT)   return Member_Flags_Only_Playables_e::SETTLEMENT;
            else if (value == SITTER)       return Member_Flags_Only_Playables_e::SITTER;
            else if (value == SLEEPER)      return Member_Flags_Only_Playables_e::SLEEPER;
            else if (value == THRALL)       return Member_Flags_Only_Playables_e::THRALL;
            else if (value == WARRIOR)      return Member_Flags_Only_Playables_e::WARRIOR;
            else                            return Member_Flags_Only_Playables_e::_NONE_;
        }

        static inline value_type From_Member_Flag_Only_Playables(Member_Flags_Only_Playables_e flag)
        {
            if (flag == Member_Flags_Only_Playables_e::ARCHER)          return ARCHER;
            else if (flag == Member_Flags_Only_Playables_e::CIVILIZED)  return CIVILIZED;
            else if (flag == Member_Flags_Only_Playables_e::COMBATANT)  return COMBATANT;
            else if (flag == Member_Flags_Only_Playables_e::COWARD)     return COWARD;
            else if (flag == Member_Flags_Only_Playables_e::DANGEROUS)  return DANGEROUS;
            else if (flag == Member_Flags_Only_Playables_e::EATER)      return EATER;
            else if (flag == Member_Flags_Only_Playables_e::EXTERIOR)   return EXTERIOR;
            else if (flag == Member_Flags_Only_Playables_e::FOLLOWER)   return FOLLOWER;
            else if (flag == Member_Flags_Only_Playables_e::GUARD)      return GUARD;
            else if (flag == Member_Flags_Only_Playables_e::HOME)       return HOME;
            else if (flag == Member_Flags_Only_Playables_e::IMMOBILE)   return IMMOBILE;
            else if (flag == Member_Flags_Only_Playables_e::INN)        return INN;
            else if (flag == Member_Flags_Only_Playables_e::INTERIOR)   return INTERIOR;
            else if (flag == Member_Flags_Only_Playables_e::MAGE)       return MAGE;
            else if (flag == Member_Flags_Only_Playables_e::MANNEQUIN)  return MANNEQUIN;
            else if (flag == Member_Flags_Only_Playables_e::MEMBER)     return MEMBER;
            else if (flag == Member_Flags_Only_Playables_e::SANDBOXER)  return SANDBOXER;
            else if (flag == Member_Flags_Only_Playables_e::SETTLEMENT) return SETTLEMENT;
            else if (flag == Member_Flags_Only_Playables_e::SITTER)     return SITTER;
            else if (flag == Member_Flags_Only_Playables_e::SLEEPER)    return SLEEPER;
            else if (flag == Member_Flags_Only_Playables_e::THRALL)     return THRALL;
            else if (flag == Member_Flags_Only_Playables_e::WARRIOR)    return WARRIOR;
            else                                                        return _NONE_;
        }

        static inline Member_Suit_Template_t To_Member_Suit_Template(value_type value)
        {
            if (value == ARCHER)            return Member_Suit_Template_t::Archer();
            else if (value == CIVILIZED)    return Member_Suit_Template_t::Civilized();
            else if (value == COMBATANT)    return Member_Suit_Template_t::Combatant();
            else if (value == COWARD)       return Member_Suit_Template_t::Coward();
            else if (value == DANGEROUS)    return Member_Suit_Template_t::Dangerous();
            else if (value == EATER)        return Member_Suit_Template_t::Eater();
            else if (value == EXTERIOR)     return Member_Suit_Template_t::Exterior();
            else if (value == FOLLOWER)     return Member_Suit_Template_t::Follower();
            else if (value == GUARD)        return Member_Suit_Template_t::Guard();
            else if (value == HOME)         return Member_Suit_Template_t::Home();
            else if (value == IMMOBILE)     return Member_Suit_Template_t::Immobile();
            else if (value == INN)          return Member_Suit_Template_t::Inn();
            else if (value == INTERIOR)     return Member_Suit_Template_t::Interior();
            else if (value == MAGE)         return Member_Suit_Template_t::Mage();
            else if (value == MANNEQUIN)    return Member_Suit_Template_t::Mannequin();
            else if (value == MEMBER)       return Member_Suit_Template_t::Member();
            else if (value == SANDBOXER)    return Member_Suit_Template_t::Sandboxer();
            else if (value == SETTLEMENT)   return Member_Suit_Template_t::Settlement();
            else if (value == SITTER)       return Member_Suit_Template_t::Sitter();
            else if (value == SLEEPER)      return Member_Suit_Template_t::Sleeper();
            else if (value == THRALL)       return Member_Suit_Template_t::Thrall();
            else if (value == WARRIOR)      return Member_Suit_Template_t::Warrior();
            else                            return Member_Suit_Template_t();
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

        Member_Flags_Has_Suit_e As_Member_Flag_Has_Suit() const
        {
            return To_Member_Flag_Has_Suit(*this);
        }

        Member_Flags_Only_Playables_e As_Member_Flag_Only_Playables() const
        {
            return To_Member_Flag_Only_Playables(*this);
        }

        Member_Suit_Template_t As_Template() const
        {
            return To_Member_Suit_Template(*this);
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
