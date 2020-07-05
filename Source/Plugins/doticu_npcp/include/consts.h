/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Consts {

    using namespace Papyrus;

    enum Forms
    {
        QUEST_DATA_STATIC = 0x0FBA9A,
        QUEST_DATA_DYNAMIC = 0x003DFF,
        QUEST_MEMBERS = 0x00184C,
        QUEST_FOLLOWERS = 0x000D83,
        QUEST_CONTROL = 0x000D7F
    };

    Consts_t* Self();
    Object_t* Object();

    void Log_Variables(Consts_t* self);
    void Log_Defaults(Consts_t* self);
    void Log_Properties(Consts_t* self);

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Registry_t* registry);

}}}
