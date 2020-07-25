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
        STARTED,
        STOPPED,
        SYNC,
        ASYNC,
        OUT_OF_BOUNDS,
        
        IS_ACTOR,
        ISNT_ACTOR,
        IS_LOADED,
        ISNT_LOADED,
        IS_UNLOADED,
        ISNT_UNLOADED,
        IS_UNIQUE,
        ISNT_UNIQUE,
        IS_GENERIC,
        ISNT_GENERIC,
        IS_ORIGINAL,
        ISNT_ORIGINAL,
        IS_CLONE,
        ISNT_CLONE,
        IS_ALIVE,
        ISNT_ALIVE,
        IS_DEAD,
        ISNT_DEAD,
        IS_MEMBER,
        ISNT_MEMBER,
        IS_NON_MEMBER,
        ISNT_NON_MEMBER,
        IS_MOBILE,
        ISNT_MOBILE,
        IS_IMMOBILE,
        ISNT_IMMOBILE,
        IS_SETTLER,
        ISNT_SETTLER,
        IS_NON_SETTLER,
        ISNT_NON_SETTLER,
        IS_THRALL,
        ISNT_THRALL,
        IS_NON_THRALL,
        ISNT_NON_THRALL,
        IS_PARALYZED,
        ISNT_PARALYZED,
        IS_NON_PARALYZED,
        ISNT_NON_PARALYZED,
        IS_MANNEQUIN,
        ISNT_MANNEQUIN,
        IS_NON_MANNEQUIN,
        ISNT_NON_MANNEQUIN,
        IS_DISPLAY,
        ISNT_DISPLAY,
        IS_NON_DISPLAY,
        ISNT_NON_DISPLAY,
        IS_REANIMATED,
        ISNT_REANIMATED,
        IS_NON_REANIMATED,
        ISNT_NON_REANIMATED,
        IS_FOLLOWER,
        ISNT_FOLLOWER,
        IS_NON_FOLLOWER,
        ISNT_NON_FOLLOWER,
        IS_SNEAK,
        ISNT_SNEAK,
        IS_NON_SNEAK,
        ISNT_NON_SNEAK,
        IS_SADDLER,
        ISNT_SADDLER,
        IS_NON_SADDLER,
        ISNT_NON_SADDLER,
        IS_RETREATER,
        ISNT_RETREATER,
        IS_NON_RETREATER,
        ISNT_NON_RETREATER,

        IS_STYLE,
        ISNT_STYLE,
        IS_DEFAULT,
        IS_WARRIOR,
        IS_MAGE,
        IS_ARCHER,
        IS_COWARD,

        IS_VITALITY,
        ISNT_VITALITY,
        IS_MORTAL,
        IS_PROTECTED,
        IS_ESSENTIAL,
        IS_INVULNERABLE,

        HAS_ACTOR,
        HASNT_ACTOR,
        HAS_LOADED,
        HASNT_LOADED,
        HAS_UNLOADED,
        HASNT_UNLOADED,
        HAS_UNIQUE,
        HASNT_UNIQUE,
        HAS_GENERIC,
        HASNT_GENERIC,
        HAS_ORIGINAL,
        HASNT_ORIGINAL,
        HAS_CLONE,
        HASNT_CLONE,
        HAS_ALIVE,
        HASNT_ALIVE,
        HAS_DEAD,
        HASNT_DEAD,
        HAS_MEMBER,
        HASNT_MEMBER,
        HAS_NON_MEMBER,
        HASNT_NON_MEMBER,
        HAS_MOBILE,
        HASNT_MOBILE,
        HAS_IMMOBILE,
        HASNT_IMMOBILE,
        HAS_SETTLER,
        HASNT_SETTLER,
        HAS_NON_SETTLER,
        HASNT_NON_SETTLER,
        HAS_THRALL,
        HASNT_THRALL,
        HAS_NON_THRALL,
        HASNT_NON_THRALL,
        HAS_PARALYZED,
        HASNT_PARALYZED,
        HAS_NON_PARALYZED,
        HASNT_NON_PARALYZED,
        HAS_MANNEQUIN,
        HASNT_MANNEQUIN,
        HAS_NON_MANNEQUIN,
        HASNT_NON_MANNEQUIN,
        HAS_DISPLAY,
        HASNT_DISPLAY,
        HAS_NON_DISPLAY,
        HASNT_NON_DISPLAY,
        HAS_REANIMATED,
        HASNT_REANIMATED,
        HAS_NON_REANIMATED,
        HASNT_NON_REANIMATED,
        HAS_FOLLOWER,
        HASNT_FOLLOWER,
        HAS_NON_FOLLOWER,
        HASNT_NON_FOLLOWER,
        HAS_SNEAK,
        HASNT_SNEAK,
        HAS_NON_SNEAK,
        HASNT_NON_SNEAK,
        HAS_SADDLER,
        HASNT_SADDLER,
        HAS_NON_SADDLER,
        HASNT_NON_SADDLER,
        HAS_RETREATER,
        HASNT_RETREATER,
        HAS_NON_RETREATER,
        HASNT_NON_RETREATER,
        HAS_MARKER,
        HASNT_MARKER,

        CHILD,
        ADULT,
        INTERIOR,
        EXTERIOR,
        RATING,
        NON_RATING,
        VAMPIRE,
        NON_VAMPIRE,

        CAN_RESURRECT,
        CANT_RESURRECT,
        CAN_CLONE,
        CANT_CLONE,

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
