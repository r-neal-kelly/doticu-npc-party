/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_value.h"

namespace doticu_npcp { namespace Party {

    class Settler_Value_Eater_e :
        public Settler_Value_e
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            LOCATION,                   // Location
            DO_UNLOCK_ON_ARRIVAL,       // Bool
            FOOD_CRITERIA,              // Target
            FOOD_LIST,                  // List
            CHAIR_CRITERIA,             // Target
            CHAIR_LIST,                 // List
            FOOD_ITEM_COUNT,            // Int
            ALLOW_ALREADY_HELD,         // Bool
            ALLOW_HORSE_RIDING,         // Bool
            FALSE_BOOL,                 // Bool
            ALLOW_FAKE_FOOD,            // Bool
            ALLOW_EATING,               // Bool
            ALLOW_SLEEPING,             // Bool
            ALLOW_CONVERSATION,         // Bool
            ALLOW_IDLE_MARKERS,         // Bool
            ALLOW_SPECIAL_FURNITURE,    // Bool
            ALLOW_SITTING,              // Bool
            ALLOW_WANDERING,            // Bool
            MIN_WANDER_DISTANCE,        // Float
            DO_PREFERRED_PATH_ONLY,     // Bool
            ATTENTION,                  // Float

            _TOTAL_,
        };

    public:
        using Settler_Value_e::Settler_Value_e;
    };

}}
