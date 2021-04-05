/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Settler_Time_AM_PM_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            AM,
            PM,

            _TOTAL_,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
    };

    class Settler_Time_AM_PM_e :
        public Enum_Type_t<Settler_Time_AM_PM_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Party::Settler_Time_AM_PM_e> :
        public none_enum<doticu_npcp::Party::Settler_Time_AM_PM_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<doticu_npcp::Party::Settler_Time_AM_PM_e> :
        public maybe_enum<doticu_npcp::Party::Settler_Time_AM_PM_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<doticu_npcp::Party::Settler_Time_AM_PM_e> :
        public some_enum<doticu_npcp::Party::Settler_Time_AM_PM_e>
    {
    public:
        using some_enum::some_enum;
    };

}
