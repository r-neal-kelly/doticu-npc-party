/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "intrinsic.h"
#include "party_settler_flags.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Flags_Sitter_e :
        public Settler_Flags_e
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
            ALLOW_AGGRO_RADIUS          = static_cast<value_type>(1 << 10),
            ALLOW_WORLD_INTERACTIONS    = static_cast<value_type>(1 << 11),
            COMMENT_ON_FRIENDLY_FIRE    = static_cast<value_type>(1 << 12),
            INSPECT_CORPSES             = static_cast<value_type>(1 << 13),
            OBSERVE_COMBAT              = static_cast<value_type>(1 << 14),
            REACT_TO_PLAYER_ACTIONS     = static_cast<value_type>(1 << 15),

            ONLY_PREFERRED_PATH         = static_cast<value_type>(1 << 16),
            STOP_MOVEMENT               = static_cast<value_type>(1 << 17),

            _TOTAL_                     = 18,
        };

    public:
        using Settler_Flags_e::Settler_Flags_e;
    };

}}
