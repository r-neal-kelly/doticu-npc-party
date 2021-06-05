/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Value_Index_e :
        public Enum_t<s64>
    {
    public:
        enum enum_type : value_type
        {
        };

    public:
        using Enum_t::Enum_t;
    };

}}
