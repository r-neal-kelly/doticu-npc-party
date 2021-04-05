/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party_settler_time_am_pm.h"

namespace doticu_npcp { namespace Party {

    Bool_t Settler_Time_AM_PM_e_data::Is_Valid(value_type value)
    {
        return value > _NONE_ && value < _TOTAL_;
    }

    some<const char* const*> Settler_Time_AM_PM_e_data::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(AM),
            SKYLIB_ENUM_TO_STRING(PM),
        };

        return strings;
    }

    some<const char*> Settler_Time_AM_PM_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Settler_Time_AM_PM_e_data::value_type Settler_Time_AM_PM_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

}}
