/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "form.h"

namespace doticu_npcp { namespace Form {

    const char *Get_Name(TESForm *ref_form) {
        TESFullName *str_full_name = DYNAMIC_CAST(ref_form, TESForm, TESFullName);
        if (str_full_name && str_full_name->name) {
            return str_full_name->name.data;
        } else {
            return NULL;
        }
    }

}}
