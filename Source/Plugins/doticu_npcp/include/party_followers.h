/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_main.h"

namespace doticu_npcp { namespace Party {

    /*
        V::Variable_tt<Bool_t>&     Do_Auto_Resurrect_Followers();
        V::Variable_tt<Bool_t>&     Do_Auto_Sojourn_Followers();
        V::Variable_tt<String_t>&   Follower_Sort_Algorithm();
        static Bool_t               Do_Level_Followers();
        static void                 Do_Level_Followers(Bool_t value);
    */

    class Followers_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t MAX_FOLLOWERS   = Main_t::MAX_FOLLOWERS;

    public:
        class Save_State
        {
        public:
            const some<Quest_t*>    quest;

        public:
            Save_State(const some<Quest_t*> quest);
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();

        public:
            some<V::Object_t*>  Object();

        public:
            void    Read();
            void    Write();
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        const some<Quest_t*>    quest;
        Save_State              save_state;

    public:
        Followers_t(some<Quest_t*> quest, Bool_t is_new_game);
        Followers_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Followers_t(const Followers_t& other)                                       = delete;
        Followers_t(Followers_t&& other) noexcept                                   = delete;
        Followers_t& operator =(const Followers_t& other)                           = delete;
        Followers_t& operator =(Followers_t&& other) noexcept                       = delete;
        ~Followers_t();

    public:
        void    Before_Save();
        void    After_Save();

    public:
        void    Validate();

    public:
        void    Log(std::string indent = "");
    };

}}
