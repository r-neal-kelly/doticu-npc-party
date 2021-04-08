/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_value_index.h"

namespace doticu_npcp { namespace Party {

    class Settler_Value_Index_Sleeper_e :
        public Settler_Value_Index_e
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            LOCATION,                   // Location
            SEARCH_CRITERIA,            // Target
            LOCK_DOORS,                 // Bool
            WARN_BEFORE_LOCKING,        // Bool
            ALLOW_HORSE_RIDING,         // Bool
            BED_LIST,                   // List
            FALSE_BOOL,                 // Bool
            ALLOW_EATING,               // Bool
            ALLOW_SLEEPING,             // Bool
            ALLOW_CONVERSATION,         // Bool
            ALLOW_IDLE_MARKERS,         // Bool
            ALLOW_SITTING,              // Bool
            ALLOW_SPECIAL_FURNITURE,    // Bool
            ALLOW_WANDERING,            // Bool
            WANDER_DISTANCE,            // Float
            ONLY_PREFERRED_PATH,        // Bool
            ATTENTION,                  // Float

            _TOTAL_,
        };

    public:
        using Settler_Value_Index_e::Settler_Value_Index_e;
    };

}}
