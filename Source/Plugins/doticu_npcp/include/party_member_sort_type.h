/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Member_Sort_Type_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            NAME,
            NAME_CASELESS,
            RATING__NAME,
            RATING__NAME_CASELESS,
        };

    public:
        using Enum_t::Enum_t;
    };

}}
