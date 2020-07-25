/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "codes.h"
#include "utils.h"

namespace doticu_npcp { namespace CODES {



}}

namespace doticu_npcp { namespace CODES { namespace Exports {

    Int_t SUCCESS(Selfless_t*)                  { return CODES::SUCCESS; }
    Int_t FAILURE(Selfless_t*)                  { return CODES::FAILURE; }

    Int_t OUT_OF_BOUNDS(Selfless_t*)            { return CODES::OUT_OF_BOUNDS; }

    Int_t IS_ACTOR(Selfless_t*)                 { return CODES::IS_ACTOR; }
    Int_t ISNT_ACTOR(Selfless_t*)               { return CODES::ISNT_ACTOR; }
    Int_t IS_MEMBER(Selfless_t*)                { return CODES::IS_MEMBER; }
    Int_t ISNT_MEMBER(Selfless_t*)              { return CODES::ISNT_MEMBER; }
    Int_t IS_DISPLAY(Selfless_t*)               { return CODES::IS_DISPLAY; }
    Int_t ISNT_DISPLAY(Selfless_t*)             { return CODES::ISNT_DISPLAY; }

    Int_t IS_STYLE(Selfless_t*)                 { return CODES::IS_STYLE; }
    Int_t ISNT_STYLE(Selfless_t*)               { return CODES::ISNT_STYLE; }
    Int_t IS_DEFAULT(Selfless_t*)               { return CODES::IS_DEFAULT; }
    Int_t IS_WARRIOR(Selfless_t*)               { return CODES::IS_WARRIOR; }
    Int_t IS_MAGE(Selfless_t*)                  { return CODES::IS_MAGE; }
    Int_t IS_ARCHER(Selfless_t*)                { return CODES::IS_ARCHER; }
    Int_t IS_COWARD(Selfless_t*)                { return CODES::IS_COWARD; }

    Int_t HAS_MEMBER(Selfless_t*)               { return CODES::HAS_MEMBER; }
    Int_t HASNT_MEMBER(Selfless_t*)             { return CODES::HASNT_MEMBER; }
    Int_t HAS_MEMBER_SPACE(Selfless_t*)         { return CODES::HAS_MEMBER_SPACE; }
    Int_t HASNT_MEMBER_SPACE(Selfless_t*)       { return CODES::HASNT_MEMBER_SPACE; }
    Int_t HAS_DISPLAY(Selfless_t*)              { return CODES::HAS_DISPLAY; }
    Int_t HASNT_DISPLAY(Selfless_t*)            { return CODES::HASNT_DISPLAY; }

    Int_t HAS_FOLLOWER_SPACE(Selfless_t*)       { return CODES::HAS_FOLLOWER_SPACE; }
    Int_t HASNT_FOLLOWER_SPACE(Selfless_t*)     { return CODES::HASNT_FOLLOWER_SPACE; }

    Int_t CAN_RESURRECT(Selfless_t*)            { return CODES::CAN_RESURRECT; }
    Int_t CANT_RESURRECT(Selfless_t*)           { return CODES::CANT_RESURRECT; }

    Int_t STYLE_DEFAULT(Selfless_t*)            { return CODES::STYLE::DEFAULT; }
    Int_t STYLE_WARRIOR(Selfless_t*)            { return CODES::STYLE::WARRIOR; }
    Int_t STYLE_MAGE(Selfless_t*)               { return CODES::STYLE::MAGE; }
    Int_t STYLE_ARCHER(Selfless_t*)             { return CODES::STYLE::ARCHER; }
    Int_t STYLE_COWARD(Selfless_t*)             { return CODES::STYLE::COWARD; }

    Int_t VITALITY_MORTAL(Selfless_t*)          { return CODES::VITALITY::MORTAL; }
    Int_t VITALITY_PROTECTED(Selfless_t*)       { return CODES::VITALITY::PROTECTED; }
    Int_t VITALITY_ESSENTIAL(Selfless_t*)       { return CODES::VITALITY::ESSENTIAL; }
    Int_t VITALITY_INVULNERABLE(Selfless_t*)    { return CODES::VITALITY::INVULNERABLE; }

    bool Register(Registry_t* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_codes", Selfless_t,           \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("SUCCESS", 0, Int_t, SUCCESS);
        ADD_GLOBAL("FAILURE", 0, Int_t, FAILURE);

        ADD_GLOBAL("OUT_OF_BOUNDS", 0, Int_t, OUT_OF_BOUNDS);

        ADD_GLOBAL("IS_ACTOR", 0, Int_t, IS_ACTOR);
        ADD_GLOBAL("ISNT_ACTOR", 0, Int_t, ISNT_ACTOR);
        ADD_GLOBAL("IS_MEMBER", 0, Int_t, IS_MEMBER);
        ADD_GLOBAL("ISNT_MEMBER", 0, Int_t, ISNT_MEMBER);
        ADD_GLOBAL("IS_DISPLAY", 0, Int_t, IS_DISPLAY);
        ADD_GLOBAL("ISNT_DISPLAY", 0, Int_t, ISNT_DISPLAY);

        ADD_GLOBAL("IS_STYLE", 0, Int_t, IS_STYLE);
        ADD_GLOBAL("ISNT_STYLE", 0, Int_t, ISNT_STYLE);
        ADD_GLOBAL("IS_DEFAULT", 0, Int_t, IS_DEFAULT);
        ADD_GLOBAL("IS_WARRIOR", 0, Int_t, IS_WARRIOR);
        ADD_GLOBAL("IS_MAGE", 0, Int_t, IS_MAGE);
        ADD_GLOBAL("IS_ARCHER", 0, Int_t, IS_ARCHER);
        ADD_GLOBAL("IS_COWARD", 0, Int_t, IS_COWARD);
        
        ADD_GLOBAL("HAS_MEMBER", 0, Int_t, HAS_MEMBER);
        ADD_GLOBAL("HASNT_MEMBER", 0, Int_t, HASNT_MEMBER);
        ADD_GLOBAL("HAS_MEMBER_SPACE", 0, Int_t, HAS_MEMBER_SPACE);
        ADD_GLOBAL("HASNT_MEMBER_SPACE", 0, Int_t, HASNT_MEMBER_SPACE);
        ADD_GLOBAL("HAS_DISPLAY", 0, Int_t, HAS_DISPLAY);
        ADD_GLOBAL("HASNT_DISPLAY", 0, Int_t, HASNT_DISPLAY);

        ADD_GLOBAL("HAS_FOLLOWER_SPACE", 0, Int_t, HAS_FOLLOWER_SPACE);
        ADD_GLOBAL("HASNT_FOLLOWER_SPACE", 0, Int_t, HASNT_FOLLOWER_SPACE);

        ADD_GLOBAL("CAN_RESURRECT", 0, Int_t, CAN_RESURRECT);
        ADD_GLOBAL("CANT_RESURRECT", 0, Int_t, CANT_RESURRECT);

        ADD_GLOBAL("STYLE_DEFAULT", 0, Int_t, STYLE_DEFAULT);
        ADD_GLOBAL("STYLE_WARRIOR", 0, Int_t, STYLE_WARRIOR);
        ADD_GLOBAL("STYLE_MAGE", 0, Int_t, STYLE_MAGE);
        ADD_GLOBAL("STYLE_ARCHER", 0, Int_t, STYLE_ARCHER);
        ADD_GLOBAL("STYLE_COWARD", 0, Int_t, STYLE_COWARD);

        ADD_GLOBAL("VITALITY_MORTAL", 0, Int_t, VITALITY_MORTAL);
        ADD_GLOBAL("VITALITY_PROTECTED", 0, Int_t, VITALITY_PROTECTED);
        ADD_GLOBAL("VITALITY_ESSENTIAL", 0, Int_t, VITALITY_ESSENTIAL);
        ADD_GLOBAL("VITALITY_INVULNERABLE", 0, Int_t, VITALITY_INVULNERABLE);

        #undef ADD_GLOBAL

        return true;
    }

}}}
