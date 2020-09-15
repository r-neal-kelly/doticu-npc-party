/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Form {

    using namespace Papyrus;

    const char *Get_Name(TESForm *ref_form);
    const char *Get_Type_String(TESForm *ref_form);
    const char* Get_Any_Name(Form_t* form);
    bool Has_Keyword(TESForm *form, BGSKeyword *keyword);
    void Log_Flags(Form_t* form);

    void Register_Key(Form_t* form, Int_t key_code, Virtual_Callback_i* vcallback = nullptr);
    void Unregister_Key(Form_t* form, Int_t key_code, Virtual_Callback_i* vcallback = nullptr);
    void Unregister_Keys(Form_t* form, Virtual_Callback_i* vcallback = nullptr);

}}

namespace doticu_npcp { namespace Form { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
