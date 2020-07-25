/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace CODES {

    using namespace Papyrus;

    enum : Int_t {

        SUCCESS = 0,
        FAILURE,

        OUT_OF_BOUNDS,

        IS,
        ISNT,
        HAS,
        HASNT,
        
        IS_ACTOR,
        ISNT_ACTOR,
        IS_MEMBER,
        ISNT_MEMBER,
        IS_DISPLAY,
        ISNT_DISPLAY,

        IS_STYLE,
        ISNT_STYLE,
        IS_DEFAULT,
        IS_WARRIOR,
        IS_MAGE,
        IS_ARCHER,
        IS_COWARD,

        IS_VITALITY,
        ISNT_VITALITY,

        HAS_MEMBER,
        HASNT_MEMBER,
        HAS_MEMBER_SPACE,
        HASNT_MEMBER_SPACE,
        HAS_DISPLAY,
        HASNT_DISPLAY,

        HAS_FOLLOWER_SPACE,
        HASNT_FOLLOWER_SPACE,

        CAN_RESURRECT,
        CANT_RESURRECT,

    };

    // I want to update these before going out of beta
    namespace STYLE {
        enum : Int_t {

            DEFAULT = -380, // 0
            WARRIOR = -381, // 1
            MAGE = -382, // 2
            ARCHER = -383, // 3
            COWARD = -384, // 4

        };
    }

    namespace VITALITY {
        enum : Int_t {

            MORTAL = -303, // 0
            PROTECTED = -304, // 1
            ESSENTIAL = -305, // 2
            INVULNERABLE = -306 // 3

        };
    }

}}

namespace doticu_npcp { namespace CODES { namespace Exports {

    bool Register(Registry_t* registry);

}}}
