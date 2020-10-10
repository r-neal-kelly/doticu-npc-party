/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameData.h"

#include "types.h"

namespace doticu_npcp { namespace Game {

    DataHandler* Data_Handler();

    tArray<Reference_t*>& References();

    Form_t* Form(UInt32 form_id);
    Form_t* Mod_Form(const char* mod_name, UInt32 lower_form_id);
    Form_t* Skyrim_Form(UInt32 lower_form_id);
    Form_t* Skyrim_Update_Form(UInt32 lower_form_id);
    Form_t* Dawnguard_Form(UInt32 lower_form_id);
    Form_t* Hearthfires_Form(UInt32 lower_form_id);
    Form_t* Dragonborn_Form(UInt32 lower_form_id);
    Form_t* NPCP_Form(UInt32 lower_form_id);

    Bool_t Is_Mod_Installed(const char* mod_name);
    Bool_t Is_Better_Vampires_Installed();

    Bool_t Is_Form_In_Mod(UInt32 form_id, const char* mod_name);
    Bool_t Is_NPCP_Form(UInt32 form_id);

    Bool_t Is_Outsourced_Follower(Actor_t* actor);

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names();
    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names();
    BGSVoiceType *Get_Voice_By_Name(BSFixedString str_name);

    Reference_t* Get_NPCP_Category(Form_t* form);
    Reference_t* Get_NPCP_Custom_Category(Form_t* form);
    void Update_NPCP_Categories();

}}
