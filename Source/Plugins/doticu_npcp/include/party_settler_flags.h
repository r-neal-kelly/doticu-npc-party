/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Flags_e :
        public Enum_t<u64>
    {
    public:
        enum enum_type : value_type
        {
        };

    public:
        using Enum_t::Enum_t;
    };

}}
