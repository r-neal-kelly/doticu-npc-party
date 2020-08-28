/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Mannequins_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Mannequins_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable();

        Int_t Current_View();
        void Current_View(Int_t view_code);

        void Review_Mannequins();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
