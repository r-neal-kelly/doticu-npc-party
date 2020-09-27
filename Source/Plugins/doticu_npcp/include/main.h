/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Modules {

    using namespace Papyrus;

    class Main_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Main_t* Self();
        static Object_t* Object();
    public:
        Variable_t* Variable(String_t variable_name);

        Bool_t Is_Version_Less_Than(Int_t major,
                                    Int_t minor,
                                    Int_t patch,
                                    Int_t min_major,
                                    Int_t min_minor,
                                    Int_t min_patch);
        Bool_t Is_NPCP_Version_Less_Than(Int_t min_major,
                                         Int_t min_minor,
                                         Int_t min_patch);

        void Init_Mod();
        void Load_Mod();
        Bool_t Has_Requirements();
        Bool_t Try_Update();
        void Try_Cleanup();
        Int_t Force_Cleanup();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}
