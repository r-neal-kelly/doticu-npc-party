/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_Update_AI_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            EVALUATE_PACKAGE,
            RESET_AI,

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
                SKYLIB_ENUM_TO_STRING(EVALUATE_PACKAGE),
                SKYLIB_ENUM_TO_STRING(RESET_AI),
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
    };

    class Member_Update_AI_e :
        public Enum_Type_t<Member_Update_AI_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Member_Update_AI_e> :
        public none_enum<doticu_npcp::Member_Update_AI_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<doticu_npcp::Member_Update_AI_e> :
        public maybe_enum<doticu_npcp::Member_Update_AI_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<doticu_npcp::Member_Update_AI_e> :
        public some_enum<doticu_npcp::Member_Update_AI_e>
    {
    public:
        using some_enum::some_enum;
    };

}
