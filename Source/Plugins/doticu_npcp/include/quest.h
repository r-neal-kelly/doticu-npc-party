/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest);

    void Force_Reference_To(Quest_t* quest, UInt32 alias_id, Reference_t* reference);
    bool Is_Alias_Filled(Quest_t* quest, UInt16 alias_id);
    Actor_t* Alias_Actor(Quest_t* quest, UInt16 alias_id);

    void Log_Aliases(Quest_t* quest);

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
