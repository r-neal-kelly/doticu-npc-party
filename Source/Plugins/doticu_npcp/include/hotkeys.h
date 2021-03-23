/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "intrinsic.h"

namespace doticu_npcp {

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

    protected:
        const some<Quest_t*>    quest;
        Int_t                   currently_pressed_key;

    public:
        Hotkeys_t(some<Quest_t*> quest);
        Hotkeys_t(const Hotkeys_t& other)                   = delete;
        Hotkeys_t(Hotkeys_t&& other) noexcept               = delete;
        Hotkeys_t& operator =(const Hotkeys_t& other)       = delete;
        Hotkeys_t& operator =(Hotkeys_t&& other) noexcept   = delete;
        ~Hotkeys_t();

    protected:
        some<V::Object_t*>  Object();

        Bool_t              On_Key_Down(V::Stack_ID_t stack_id, Int_t key_code);
        Bool_t              On_Key_Up(V::Stack_ID_t stack_id, Int_t key_code, Float_t time_held);

    public:
        void    Before_Save();
        void    After_Save();
        void    Before_Load();
        void    After_Load();

    public:
        void Log(std::string indent = "");
    };

}
