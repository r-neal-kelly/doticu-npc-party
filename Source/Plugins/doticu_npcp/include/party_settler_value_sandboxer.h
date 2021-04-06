/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_value.h"

namespace doticu_npcp { namespace Party {

    class Settler_Value_Sandboxer_e :
        public Settler_Value_e
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            LOCATION,                   // Location
            DO_UNLOCK_ON_ARRIVAL,       // Bool
            ALLOW_EATING,               // Bool
            ALLOW_SLEEPING,             // Bool
            ALLOW_CONVERSATION,         // Bool
            ALLOW_IDLE_MARKERS,         // Bool
            ALLOW_SITTING,              // Bool
            ALLOW_SPECIAL_FURNITURE,    // Bool
            ALLOW_WANDERING,            // Bool
            DO_PREFERRED_PATH_ONLY,     // Bool
            ALLOW_HORSE_RIDING,         // Bool
            ATTENTION,                  // Float
            MIN_WANDER_DISTANCE,        // Float

            _TOTAL_,
        };

    public:
        using Settler_Value_e::Settler_Value_e;
    };

}}
