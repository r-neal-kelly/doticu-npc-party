/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_value_index.h"

namespace doticu_npcp { namespace Party {

    class Settler_Value_Index_Sitter_e :
        public Settler_Value_Index_e
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            LOCATION,               // Location
            SEARCH_CRITERIA,        // Target
            CHAIR_LIST,             // List
            WAIT_TIME,              // Float
            STOP_MOVEMENT,          // Bool
            ONLY_PREFERRED_PATH,    // Bool
            FALSE_BOOL,             // Bool

            _TOTAL_,
        };

    public:
        using Settler_Value_Index_e::Settler_Value_Index_e;
    };

}}
