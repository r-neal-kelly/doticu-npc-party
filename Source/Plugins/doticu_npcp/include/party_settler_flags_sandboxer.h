/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Settler_Flags_Sandboxer_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            IS_ENABLED                  = static_cast<value_type>(1 << 0),

            ALLOW_SWIMMING              = static_cast<value_type>(1 << 1),
            ALWAYS_SNEAK                = static_cast<value_type>(1 << 2),
            IGNORE_COMBAT               = static_cast<value_type>(1 << 3),
            KEEP_WEAPONS_DRAWN          = static_cast<value_type>(1 << 4),
            HIDE_WEAPONS                = static_cast<value_type>(1 << 5),
            SKIP_COMBAT_ALERT           = static_cast<value_type>(1 << 6),

            ALLOW_HELLOS_TO_PLAYER      = static_cast<value_type>(1 << 7),
            ALLOW_HELLOS_TO_NPCS        = static_cast<value_type>(1 << 8),
            ALLOW_IDLE_CHATTER          = static_cast<value_type>(1 << 9),
            ALLOW_AGGRO_RADIUS_BEHAVIOR = static_cast<value_type>(1 << 10),
            ALLOW_WORLD_INTERACTIONS    = static_cast<value_type>(1 << 11),
            COMMENT_ON_FRIENDLY_FIRE    = static_cast<value_type>(1 << 12),
            INSPECT_CORPSE_BEHAVIOR     = static_cast<value_type>(1 << 13),
            OBSERVE_COMBAT_BEHAVIOR     = static_cast<value_type>(1 << 14),
            REACT_TO_PLAYER_ACTIONS     = static_cast<value_type>(1 << 15),

            ALLOW_CONVERSATION          = static_cast<value_type>(1 << 16),
            ALLOW_EATING                = static_cast<value_type>(1 << 17),
            ALLOW_HORSE_RIDING          = static_cast<value_type>(1 << 18),
            ALLOW_IDLE_MARKERS          = static_cast<value_type>(1 << 19),
            ALLOW_SITTING               = static_cast<value_type>(1 << 20),
            ALLOW_SLEEPING              = static_cast<value_type>(1 << 21),
            ALLOW_SPECIAL_FURNITURE     = static_cast<value_type>(1 << 22),
            ALLOW_WANDERING             = static_cast<value_type>(1 << 23),

            PREFERRED_PATH_ONLY         = static_cast<value_type>(1 << 24),
            UNLOCK_ON_ARRIVAL           = static_cast<value_type>(1 << 25),

            _TOTAL_                     = 26,
        };

    public:
        using Enum_t::Enum_t;
    };

}}
