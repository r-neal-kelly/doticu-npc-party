/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Game {

    TESForm *Get_Form(UInt32 form_id);
    TESForm *Get_Mod_Form(const char *mod_name, UInt32 lower_form_id);
    TESForm *Get_NPCP_Form(UInt32 lower_form_id);

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
