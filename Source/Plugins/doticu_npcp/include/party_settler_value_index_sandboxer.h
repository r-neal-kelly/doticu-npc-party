/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_value_index.h"

namespace doticu_npcp { namespace Party {

    class Settler_Value_Index_Sandboxer_e :
        public Settler_Value_Index_e
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            LOCATION,                   // Location
            UNLOCK_ON_ARRIVAL,          // Bool
            ALLOW_EATING,               // Bool
            ALLOW_SLEEPING,             // Bool
            ALLOW_CONVERSATION,         // Bool
            ALLOW_IDLE_MARKERS,         // Bool
            ALLOW_SITTING,              // Bool
            ALLOW_SPECIAL_FURNITURE,    // Bool
            ALLOW_WANDERING,            // Bool
            ONLY_PREFERRED_PATH,        // Bool
            ALLOW_HORSE_RIDING,         // Bool
            ATTENTION,                  // Float
            WANDER_DISTANCE,            // Float

            _TOTAL_,
        };

    public:
        using Settler_Value_Index_e::Settler_Value_Index_e;
    };

}}
