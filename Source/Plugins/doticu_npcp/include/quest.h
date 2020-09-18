/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Quest {

    using namespace Papyrus;

    const char *Get_Name(TESQuest *quest);

    bool Is_Alias_Filled(Quest_t* quest, UInt16 alias_id);
    Actor_t* Alias_Actor(Quest_t* quest, UInt16 alias_id);
    void Clear_Alias(Quest_t* quest, UInt16 alias_id);

    void Log_Aliases(Quest_t* quest);

    Bool_t Start(Quest_t* quest);
    //void Start(Quest_t* quest);
    void Start_All(const Vector_t<Quest_t*> quests, Callback_t<>* user_callback);

    void Log_Dialogue(Quest_t* quest);

    void Log_Start_Enabled_Dialogue();

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
