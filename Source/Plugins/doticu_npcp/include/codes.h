/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace CODES {

    using namespace Papyrus;

    enum : Int_t {

        SUCCESS,
        FAILURE,
        IS,
        ISNT,
        HAS,
        HASNT,
        CAN,
        CANT,
        ALIVE,
        DEAD,
        
        ACTOR,
        CHILD,
        CLONE,
        DISPLAY,
        FOLLOWER,
        FOLLOWERS,
        HORSE,
        HORSES,
        INTERIOR,
        MANNEQUIN,
        MARKER,
        MEMBER,
        MEMBERS,
        MOVEE,
        VAMPIRE,

    };

    namespace ACTION {
        enum : Int_t {

            WEAPON_SWING = 0,
            SPELL_CAST = 1,
            SPELL_FIRE = 2,
            VOICE_CAST = 3,
            VOICE_FIRE = 4,
            BOW_DRAW = 5,
            BOW_RELEASE = 6,
            DRAW_BEGIN = 7,
            DRAW_END = 8,
            SHEATHE_BEGIN = 9,
            SHEATHE_END = 10,

        };
    }

    namespace COMBAT {
        enum : Int_t {

            NO = 0,
            YES = 1,
            SEARCHING = 2,

        };
    }

    namespace CRITICAL {
        enum : Int_t {

            NONE = 0,
            GOO_BEGIN = 1,
            GOO_END = 2,
            DISINTEGRATE_BEGIN = 3,
            DISINTEGRATE_END = 4,

        };
    }

    namespace MOTION {
        enum : Int_t {

            DYNAMIC = 1,
            SPHERE_INERTIA = 2,
            BOX_INERTIA = 3,
            KEY_FRAMED = 4,
            FIXED = 5,
            THIN_BOX_INERTIA = 6,
            CHARACTER = 7,

        };
    }

    namespace OUTFIT {
        enum : Int_t {

            BASE = -100,
            REFERENCE = -200,

        };
    }

    namespace OUTFIT2 {
        enum : Int_t {

            CURRENT = -100,
            MEMBER = -1000,
            SETTLER = -2000,
            THRALL = -3000,
            FOLLOWER = -4000,
            IMMOBILE = -5000,
            VANILLA = -7000,
            DEFAULT = -8000,

            DELETED = 0xDEAD,

        };
    }

    namespace SEX {
        enum : Int_t {

            MALE = 0,
            FEMALE = 1,
            NONE = -1,

        };
    }

    // update these before going out of beta
    namespace STYLE {
        enum : Int_t {

            DEFAULT = -380, // 0
            WARRIOR = -381, // 1
            MAGE = -382, // 2
            ARCHER = -383, // 3
            COWARD = -384, // 4

        };
    }

    namespace VIEW {
        enum : Int_t {

            MEMBERS = -1000,
            FOLLOWERS = -1100,
            MEMBERS_MEMBER = -1200,
            FOLLOWERS_MEMBER = -1300,
            FILTER = -2000,
            FILTER_MEMBERS = -2010,
            FILTER_MEMBERS_MEMBER = -2020,
            MANNEQUINS = -3000,
            MANNEQUINS_CELL = -3001,
            MANNEQUINS_MEMBER = -3002

        };
    }

    // update these before going out of beta
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
