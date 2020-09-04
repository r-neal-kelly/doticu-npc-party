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

        constexpr uintptr_t ADD_SPELL                   = 0x0062F560; // 37771
        constexpr uintptr_t EVALUATE_PACKAGE            = 0x005DB310; // 36407
        constexpr uintptr_t QUEUE_NI_NODE_UPDATE        = 0x00693110; // 39181
        constexpr uintptr_t UPDATE_3D_MODEL             = 0x00650DF0; // 38404

    }

    namespace Actor_Equipper {

        constexpr uintptr_t SELF                        = 0x02EC4838; // 514494
        constexpr uintptr_t EQUIP_ITEM                  = 0x00637A80; // 37938
        constexpr uintptr_t UNEQUIP_ITEM                = 0x00638190; // 37945
        constexpr uintptr_t RIGHT_HAND_SLOT             = 0x00331620; // 23151
        constexpr uintptr_t LEFT_HAND_SLOT              = 0x003315F0; // 23150
        constexpr uintptr_t EITHER_HAND_SLOT            = 0x00331650; // 23152

    }

    namespace Virtual_Arguments {

        constexpr uintptr_t RESIZE                      = 0x00920360; // 53105

    }

    namespace Array {

        constexpr uintptr_t DESTROY                     = 0x01241E40; // 97723

    }

    namespace Container_Changes {

        constexpr uintptr_t CTOR                        = 0x001D9200; // 15812
        constexpr uintptr_t DTOR                        = 0x001D92F0; // 15813

    }

    namespace CRC32 {

        constexpr uintptr_t BY_SIZE                     = 0x00C06490; // 66962
        constexpr uintptr_t BY_32                       = 0x00C064F0; // 66963
        constexpr uintptr_t BY_64                       = 0x00C06570; // 66964

    }

    namespace Dialogue_Info {

        constexpr uintptr_t CTOR                        = 0x0056C9D0; // 34413

    }

    namespace Extra {

        constexpr uintptr_t CAN_TALK_TO_PLAYER_V_TABLE  = 0x0152C740; // 229596
        constexpr uintptr_t CONTAINER_CHANGES_V_TABLE   = 0x0152F260; // 229886
        constexpr uintptr_t FACTION_CHANGES_V_TABLE     = 0x0152C800; // 229602
        constexpr uintptr_t FLAGS_V_TABLE               = 0x0152CBC0; // 229632
        constexpr uintptr_t GHOST_V_TABLE               = 0x0152F2A0; // 229888
        constexpr uintptr_t TEXT_DISPLAY_V_TABLE        = 0x0152CAE0; // 229625
        constexpr uintptr_t OUTFIT_ITEM_V_TABLE         = 0x0152c1e0; // 229553

    }

    namespace Magic_Target {

        constexpr uintptr_t HAS_MAGIC_EFFECT            = 0x005530D0; // 33733

    }

    namespace Object {

        constexpr uintptr_t INCREMENT_LOCK              = 0x01234360; // 97468
        constexpr uintptr_t DECREMENT_LOCK              = 0x01234410; // 97469
        constexpr uintptr_t DESTROY                     = 0x01233670; // 97462

    }

    namespace Object_Policy {

        constexpr uintptr_t BIND_OBJECT                 = 0x0122DAD0; // 97379

    }

    namespace Process_Lists {

        constexpr uintptr_t SELF                        = 0x01EBEAD0; // 514167
        constexpr uintptr_t STOP_COMBAT_ALARM           = 0x006D9490; // 40330

    }

    namespace Quest {

        //constexpr uintptr_t CLEAR_ALL_ALIASES         = 0x003745D0; // 24520
        //constexpr uintptr_t RESET_ALIAS_HASHMAP       = 0x00374880; // 24521
        constexpr uintptr_t FORCE_REFERENCE_TO          = 0x00375050; // 24523

        constexpr uintptr_t START                       = 0x00370910; // 24481

    }

    namespace Reference {

        constexpr uintptr_t ADD_ITEM                    = 0x00993100; // 55616
        constexpr uintptr_t LOOKUP_REFERENCE_BY_HANDLE1 = 0x001328A0; // 12203
        constexpr uintptr_t LOOKUP_REFERENCE_BY_HANDLE2 = 0x001329D0; // 12204
        constexpr uintptr_t PLACE_AT_ME                 = 0x009951F0; // 55672
        constexpr uintptr_t PLAY_ANIMATION              = 0x00189E30; // 14189

    }

    namespace Relationships {

        constexpr uintptr_t SELF                        = 0x01DD3EF8; // 502260
        constexpr uintptr_t GET_RELATIONSHIP_RANK       = 0x00345ED0; // 23624
        constexpr uintptr_t SET_RELATIONSHIP_RANK       = 0x00345B80; // 23623

    }

    namespace String {

        constexpr uintptr_t SET                         = 0x00C28D60; // 67823

    }

    namespace Variable {

        constexpr uintptr_t COPY                        = 0x01236E50; // 97509
        constexpr uintptr_t DESTROY                     = 0x01236D10; // 97508

    }

}}
