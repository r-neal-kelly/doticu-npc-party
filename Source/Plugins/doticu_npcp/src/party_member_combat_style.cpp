/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "party_member_combat_style.h"

namespace doticu_npcp { namespace Party {

    Bool_t Member_Combat_Style_e_data::Is_Valid(value_type value)
    {
        return value > _NONE_ && value < _TOTAL_;
    }

    some<const char* const*> Member_Combat_Style_e_data::Strings()
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

    some<const char*> Member_Combat_Style_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Member_Combat_Style_e_data::value_type Member_Combat_Style_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

    maybe<Combat_Style_t*> Member_Combat_Style_e::To_Combat_Style(value_type value)
    {
        if (value == ARCHER)        return Consts_t::NPCP::Combat_Style::Archer()();
        else if (value == COWARD)   return Consts_t::NPCP::Combat_Style::Coward()();
        else if (value == MAGE)     return Consts_t::NPCP::Combat_Style::Mage()();
        else if (value == WARRIOR)  return Consts_t::NPCP::Combat_Style::Warrior()();
        else                        return none<Combat_Style_t*>();
    }

    Member_Combat_Style_e::value_type Member_Combat_Style_e::From_Combat_Style(maybe<Combat_Style_t*> combat_style)
    {
        if (combat_style == Consts_t::NPCP::Combat_Style::Archer())         return ARCHER;
        else if (combat_style == Consts_t::NPCP::Combat_Style::Coward())    return COWARD;
        else if (combat_style == Consts_t::NPCP::Combat_Style::Mage())      return MAGE;
        else if (combat_style == Consts_t::NPCP::Combat_Style::Warrior())   return WARRIOR;
        else                                                                return _NONE_;
    }

    maybe<Combat_Style_t*> Member_Combat_Style_e::As_Combat_Style() const
    {
        return To_Combat_Style(*this);
    }

    Member_Combat_Style_e::operator maybe<Combat_Style_t*>() const
    {
        return As_Combat_Style();
    }

}}
