/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Modules {

    using namespace Papyrus;

    class Funcs_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Funcs_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        void Wait_Out_Of_Menu(Float_t seconds, Virtual_Callback_i** callback = nullptr);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}
