/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusArgs.h"

#include "utils.h"
#include "papyrus.h"
#include "alias.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest);

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    VMResultArray<BGSBaseAlias *> Get_Used_Aliases(StaticFunctionTag *, TESQuest *ref_quest);
    VMResultArray<SInt32> Get_Free_Alias_IDs(StaticFunctionTag *, TESQuest *ref_quest);

    UInt32 Count_Used_Aliases(StaticFunctionTag *, TESQuest *ref_quest);
    UInt32 Count_Free_Aliases(StaticFunctionTag *, TESQuest *ref_quest);
    UInt32 Count_Mannequins(StaticFunctionTag *, TESQuest *ref_quest);

    bool Register(VMClassRegistry *registry);

}}}
