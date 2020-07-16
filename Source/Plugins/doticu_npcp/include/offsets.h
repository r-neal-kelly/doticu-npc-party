/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64_common/Relocation.h"

// credit goes to meh321 of 'Address Library for SKSE Plugins' for the offsets
// and also Ryan-rsm-McKenzie of CommonLibSSE for the ids

// this is for version 1.5.97.0 only
namespace doticu_npcp { namespace Offsets {

    namespace Actor {

        constexpr size_t EVALUATE_PACKAGE           = 0x005DB310; // 36407

    }

    namespace Extra {

        constexpr size_t FACTION_CHANGES_V_TABLE    = 0x0152C800; // 229602
        constexpr size_t CAN_TALK_TO_PLAYER_V_TABLE = 0x0152C740; // 229596

    }

}}
