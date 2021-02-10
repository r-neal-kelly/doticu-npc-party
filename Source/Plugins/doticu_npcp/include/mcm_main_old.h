/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once
#undef TEXT

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t : public SKI_Config_Base_t {
        const char*& Override_Page();
        void Reset_Page(String_t override_page = "");

        void Close_Menus(Callback_t<>* ucallback = nullptr);
        String_t Concat(const char* a, const char* b);
        String_t Concat(const char* a, const char* b, const char* c);
    };

}}}
