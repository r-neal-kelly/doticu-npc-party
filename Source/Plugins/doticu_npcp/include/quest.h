/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest);

    bool Is_Alias_Filled(Quest_t* quest, UInt16 alias_id);
    Actor_t* Alias_Actor(Quest_t* quest, UInt16 alias_id);
    void Clear_Alias(Quest_t* quest, UInt16 alias_id);

    void Log_Aliases(Quest_t* quest);

    Bool_t Start(Quest_t* quest);
    //void Start(Quest_t* quest);

    void Log_Dialogue(Quest_t* quest);

    void Log_Start_Enabled_Dialogue();
    void Log_0A0(Quest_t* quest);

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
