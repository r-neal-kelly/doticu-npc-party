/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_flags.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Flags_Guard_e :
        public Settler_Flags_e
    {
    public:
        enum enum_type : value_type
        {
            _TOTAL_ = 16,
        };

    public:
        using Settler_Flags_e::Settler_Flags_e;
    };

}}
