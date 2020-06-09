/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Form {

    const char *Get_Name(TESForm *ref_form);
    const char *Get_Type_String(TESForm *ref_form);
    bool Has_Keyword(TESForm *form, BGSKeyword *keyword);

}}

namespace doticu_npcp { namespace Form { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
