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

        void Wait(Float_t seconds, Virtual_Callback_i** callback = nullptr);
        void Wait_Out_Of_Menu(Float_t seconds, Virtual_Callback_i** callback = nullptr);

        void Is_In_Menu_Mode(Virtual_Callback_i* vcallback);
        void Tap_Key(Int_t key, Virtual_Callback_i* vcallback);

        void Open_Container(Reference_t* container, Virtual_Callback_i* vcallback = nullptr);
        void Close_Menus(Callback_t<>* ucallback = nullptr);

        void Force_Third_Person(Virtual_Callback_i* vcallback = nullptr);

        void Enable(Reference_t* reference, Virtual_Callback_i* vcallback = nullptr);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}
