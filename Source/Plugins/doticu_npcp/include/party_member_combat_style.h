/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_Combat_Style_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            ARCHER,
            COWARD,
            MAGE,
            WARRIOR,

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
                SKYLIB_ENUM_TO_STRING(ARCHER),
                SKYLIB_ENUM_TO_STRING(COWARD),
                SKYLIB_ENUM_TO_STRING(MAGE),
                SKYLIB_ENUM_TO_STRING(WARRIOR),
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

        static inline maybe<Combat_Style_t*> To_Combat_Style(value_type value)
        {
            if (value == ARCHER)        return Consts_t::NPCP::Combat_Style::Archer()();
            else if (value == COWARD)   return Consts_t::NPCP::Combat_Style::Coward()();
            else if (value == MAGE)     return Consts_t::NPCP::Combat_Style::Mage()();
            else if (value == WARRIOR)  return Consts_t::NPCP::Combat_Style::Warrior()();
            else                        return none<Combat_Style_t*>();
        }

        static inline value_type From_Combat_Style(maybe<Combat_Style_t*> combat_style)
        {
            if (combat_style == Consts_t::NPCP::Combat_Style::Archer())         return ARCHER;
            else if (combat_style == Consts_t::NPCP::Combat_Style::Coward())    return COWARD;
            else if (combat_style == Consts_t::NPCP::Combat_Style::Mage())      return MAGE;
            else if (combat_style == Consts_t::NPCP::Combat_Style::Warrior())   return WARRIOR;
            else                                                                return _NONE_;
        }
    };

    class Member_Combat_Style_e :
        public Enum_Type_t<Member_Combat_Style_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;

    public:
        inline maybe<Combat_Style_t*> As_Combat_Style() const
        {
            return To_Combat_Style(*this);
        }

    public:
        inline operator maybe<Combat_Style_t*>() const
        {
            return As_Combat_Style();
        }
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Member_Combat_Style_e> :
        public none_enum<doticu_npcp::Member_Combat_Style_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<doticu_npcp::Member_Combat_Style_e> :
        public maybe_enum<doticu_npcp::Member_Combat_Style_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<doticu_npcp::Member_Combat_Style_e> :
        public some_enum<doticu_npcp::Member_Combat_Style_e>
    {
    public:
        using some_enum::some_enum;
    };

}
