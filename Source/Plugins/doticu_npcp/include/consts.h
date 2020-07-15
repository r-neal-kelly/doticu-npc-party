/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Consts {

    using namespace Papyrus;

    enum Forms {
        QUEST_DATA_STATIC = 0x0FBA9A,
        QUEST_DATA_DYNAMIC = 0x003DFF,
        QUEST_MEMBERS = 0x00184C,
        QUEST_FOLLOWERS = 0x000D83,
        QUEST_CONTROL = 0x000D7F
    };

    Consts_t* Self();
    Object_t* Object();

    Variable_t* Variable(String_t variable_name);

    Misc_t* Default_Style_Token();
    Misc_t* Warrior_Style_Token();
    Misc_t* Mage_Style_Token();
    Misc_t* Archer_Style_Token();
    Misc_t* Coward_Style_Token();

    Misc_t* Mortal_Vitality_Token();
    Misc_t* Protected_Vitality_Token();
    Misc_t* Essential_Vitality_Token();
    Misc_t* Invulnerable_Vitality_Token();

    Misc_t* Display_Token();

    Misc_t* Sneak_Follower_Token();

    void Log_Variables(Consts_t* self);
    void Log_Defaults(Consts_t* self);
    void Log_Properties(Consts_t* self);

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Registry_t* registry);

}}}
