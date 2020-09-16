/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Game {

    tArray<Reference_t*>& References();

    Form_t* Form(UInt32 form_id);
    Form_t* Mod_Form(const char* mod_name, UInt32 lower_form_id);
    Form_t* Skyrim_Form(UInt32 lower_form_id);
    Form_t* Skyrim_Update_Form(UInt32 lower_form_id);
    Form_t* Dawnguard_Form(UInt32 lower_form_id);
    Form_t* Hearthfires_Form(UInt32 lower_form_id);
    Form_t* Dragonborn_Form(UInt32 lower_form_id);
    Form_t* NPCP_Form(UInt32 lower_form_id);

    Bool_t Is_Form_In_Mod(UInt32 form_id, const char* mod_name);
    Bool_t Is_NPCP_Form(UInt32 form_id);

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names();
    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names();
    BGSVoiceType *Get_Voice_By_Name(BSFixedString str_name);

    Reference_t* Get_NPCP_Category(Form_t* form);
    Reference_t* Get_NPCP_Custom_Category(Form_t* form);
    void Update_NPCP_Categories();

}}

namespace doticu_npcp { namespace Game { namespace Exports {

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names(StaticFunctionTag *);
    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names(StaticFunctionTag *);
    BGSVoiceType *Get_Voice_By_Name(StaticFunctionTag *, BSFixedString str_name);

    bool Register(VMClassRegistry *registry);

}}}
