/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_npcp { namespace Offsets {

    namespace Actor {

        constexpr uintptr_t ADD_SPELL                   = 0x0062F560; // 37771
        constexpr uintptr_t EVALUATE_PACKAGE            = 0x005DB310; // 36407
        constexpr uintptr_t QUEUE_NI_NODE_UPDATE        = 0x00693110; // 39181
        constexpr uintptr_t UPDATE_3D_MODEL             = 0x00650DF0; // 38404

    }

    namespace Container_Changes {

        constexpr uintptr_t CTOR                        = 0x001D9200; // 15812
        constexpr uintptr_t DTOR                        = 0x001D92F0; // 15813

    }

    namespace Process_Lists {

        constexpr uintptr_t SELF                        = 0x01EBEAD0; // 514167
        constexpr uintptr_t STOP_COMBAT_ALARM           = 0x006D9490; // 40330

    }

    namespace Quest {

        constexpr uintptr_t START                       = 0x00370910; // 24481

    }

    namespace Reference {

        constexpr uintptr_t ADD_ITEM                    = 0x00993100; // 55616
        constexpr uintptr_t LOOKUP_REFERENCE_BY_HANDLE2 = 0x001329D0; // 12204
        constexpr uintptr_t PLAY_ANIMATION              = 0x00189E30; // 14189

    }

}}
