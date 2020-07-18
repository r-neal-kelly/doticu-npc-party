/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64_common/Relocation.h"

// credit goes to meh321 of 'Address Library for SKSE Plugins' for the offsets
// and also Ryan-rsm-McKenzie of CommonLibSSE for the ids

// this is for version 1.5.97.0 only. use the ids in comments for other versions
namespace doticu_npcp { namespace Offsets {

    namespace Actor {

        constexpr uintptr_t EVALUATE_PACKAGE            = 0x005DB310; // 36407
        constexpr uintptr_t UPDATE_3D_MODEL             = 0x00650DF0; // 38404

    }

    namespace Reference {

        constexpr uintptr_t PLAY_ANIMATION              = 0x00189E30; // 14189

    }

    namespace Extra {

        constexpr uintptr_t CAN_TALK_TO_PLAYER_V_TABLE  = 0x0152C740; // 229596
        constexpr uintptr_t FACTION_CHANGES_V_TABLE     = 0x0152C800; // 229602
        constexpr uintptr_t FLAGS_V_TABLE               = 0x0152CBC0; // 229632
        constexpr uintptr_t GHOST_V_TABLE               = 0x0152F2A0; // 229888
        constexpr uintptr_t TEXT_DISPLAY_V_TABLE        = 0x0152CAE0; // 229625

    }

}}
