/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <fstream>

#include "doticu_skylib/enum_script_type.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Hotkeys_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        static void Can_Use_Hotkeys(some<unique<Callback_i<Bool_t>>> callback);

    public:
        const some<Quest_t*>    quest;
        Int_t                   currently_pressed_key;

    public:
        Hotkeys_t();
        Hotkeys_t(const Hotkeys_t& other) = delete;
        Hotkeys_t(Hotkeys_t&& other) noexcept = delete;
        Hotkeys_t& operator =(const Hotkeys_t& other) = delete;
        Hotkeys_t& operator =(Hotkeys_t&& other) noexcept = delete;
        ~Hotkeys_t();

    public:
        some<V::Object_t*>                  Object();

        Bool_t                              On_Key_Down(V::Stack_ID_t stack_id, Int_t key_code);
        Bool_t                              On_Key_Up(V::Stack_ID_t stack_id, Int_t key_code, Float_t time_held);

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);
        void    On_Update();

    public:
        void Log(std::string indent = "");
    };

}}
