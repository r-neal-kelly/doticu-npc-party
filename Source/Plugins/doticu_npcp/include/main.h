/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "hotkeys.h"
#include "intrinsic.h"
#include "mcm_main.h"
#include "party_main.h"

namespace doticu_npcp {

    class Main_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        class State_t
        {
        public:
            Party::Main_t   party;
            Hotkeys_t       hotkeys;
            //MCM::Main_t         mcm_main;

        public:
            State_t(Bool_t is_new_game);
            State_t(const Version_t<u16> version_to_update);
            State_t(const State_t& other)                       = delete;
            State_t(State_t&& other) noexcept                   = delete;
            State_t& operator =(const State_t& other)           = delete;
            State_t& operator =(State_t&& other) noexcept       = delete;
            ~State_t();

        public:
            void Before_Save();
            void After_Save();
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        const some<Quest_t*>    quest;
        maybe<State_t*>         state;

    public:
        Main_t(some<Quest_t*> quest);
        Main_t(const Main_t& other)                 = delete;
        Main_t(Main_t&& other) noexcept             = delete;
        Main_t& operator =(const Main_t& other)     = delete;
        Main_t& operator =(Main_t&& other) noexcept = delete;
        ~Main_t();

    public:
        some<V::Object_t*>      Object();

        V::Variable_tt<Bool_t>& Is_Initialized();

        V::Variable_tt<Int_t>&  Major_Version();
        V::Variable_tt<Int_t>&  Minor_Version();
        V::Variable_tt<Int_t>&  Patch_Version();

    public:
        const Version_t<u16>        Static_Version();
        const Version_t<u16>        Dynamic_Version();
        void                        Dynamic_Version(const Version_t<u16> dynamic_version);

        Vector_t<some<Quest_t*>>    Logic_Quests();

        void                        Create_State(Bool_t is_new_game);
        void                        Create_State(const Version_t<u16> version_to_update);
        void                        Delete_State();

    public:
        void    New_Game();
        void    Before_Save();
        void    After_Save();
        void    Before_Load();
        void    After_Load();
    };

}
