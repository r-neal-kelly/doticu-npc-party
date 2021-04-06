/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_value.h"

namespace doticu_npcp { namespace Party {

    class Settler_Value_Sitter_e :
        public Settler_Value_e
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            LOCATION,               // Location
            SEARCH_CRITERIA,        // Target
            CHAIR_LIST,             // List
            WAIT_TIME,              // Float
            DO_STOP_MOVEMENT,       // Bool
            DO_PREFERRED_PATH_ONLY, // Bool
            FALSE_BOOL,             // Bool

            _TOTAL_,
        };

    public:
        using Settler_Value_e::Settler_Value_e;
    };

}}
