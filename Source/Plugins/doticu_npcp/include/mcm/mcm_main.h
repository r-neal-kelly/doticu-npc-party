/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace MCM {

    using namespace Papyrus;

    enum Flags : Int_t {
        NONE = 0,
        DISABLE = 1 << 0,
        HIDE = 1 << 1,
        UNMAP = 1 << 2,
    };

    class Main_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Main_t* Self();
        static Object_t* Object();
    public:
        Variable_t* Variable(String_t variable_name);

        void Add_Option(String_t method, Variable_t* option_out, String_t text, String_t value, Int_t flags = 0);
        void Add_Text_Option(Variable_t* option_out, String_t text, String_t value, Int_t flags = 0);
        void Add_Menu_Option(Variable_t* option_out, String_t text, String_t value, Int_t flags = 0);

        void Set_Text_Option(Variable_t* option_in, String_t value, Bool_t do_render = true);
        void Set_Option_Flags(Variable_t* option_in, Int_t flags = 0, Bool_t do_render = true);

        void Enable_Option(Variable_t* option_in, Bool_t do_render = true);
        void Disable_Option(Variable_t* option_in, Bool_t do_render = true);
    public:
        static void Register_Me(Registry_t* registry);
    };

}}
