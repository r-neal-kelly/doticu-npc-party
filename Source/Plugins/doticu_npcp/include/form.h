/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Form {

    using namespace Papyrus;

    const char *Get_Name(TESForm *ref_form);
    const char *Get_Type_String(TESForm *ref_form);
    const char* Get_Type_String(UInt32 form_type);
    const char* Get_Any_Name(Form_t* form);
    bool Has_Keyword(TESForm *form, BGSKeyword *keyword);
    void Log_Flags(Form_t* form);

    void Register_Key(Form_t* form, Int_t key_code, Virtual_Callback_i* vcallback = nullptr);
    void Unregister_Key(Form_t* form, Int_t key_code, Virtual_Callback_i* vcallback = nullptr);
    void Unregister_Keys(Form_t* form, Virtual_Callback_i* vcallback = nullptr);

    void Register_Mod_Event(Form_t* form, String_t event_name, String_t callback_name, Virtual_Callback_i* vcallback = nullptr);
    void Unregister_Mod_Event(Form_t* form, String_t event_name, Virtual_Callback_i* vcallback = nullptr);
    void Unregister_Mod_Events(Form_t* form, Virtual_Callback_i* vcallback = nullptr);

    void Queue(Form_t* form, Virtual_Callback_i* vcallback);

    const char* Name(Form_t* form);
    void Name(Form_t* form, const char* name);

}}
