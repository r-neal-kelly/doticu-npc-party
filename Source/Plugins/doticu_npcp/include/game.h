/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace doticu_npcp { namespace Game {

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names();
    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names();
    BGSVoiceType *Get_Voice_By_Name(BSFixedString str_name);

    TESObjectREFR *Get_NPCP_Category(TESForm *form);
}}

namespace doticu_npcp { namespace Game { namespace Exports {

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names(StaticFunctionTag *);
    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names(StaticFunctionTag *);
    BGSVoiceType *Get_Voice_By_Name(StaticFunctionTag *, BSFixedString str_name);

    bool Register(VMClassRegistry *registry);

}}}
