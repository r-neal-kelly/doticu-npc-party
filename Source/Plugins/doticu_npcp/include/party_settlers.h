/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_members.h"

namespace doticu_npcp { namespace Party {

    class Settlers_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t MAX_SETTLERS    = Members_t::MAX_MEMBERS;

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
        Settlers_t(some<Quest_t*> quest, Bool_t is_new_game);
        Settlers_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Settlers_t(const Settlers_t& other)                                         = delete;
        Settlers_t(Settlers_t&& other) noexcept                                     = delete;
        Settlers_t& operator =(const Settlers_t& other)                             = delete;
        Settlers_t& operator =(Settlers_t&& other) noexcept                         = delete;
        ~Settlers_t();

    public:
        void    Before_Save();
        void    After_Save();

    public:
        void    Validate();

    public:
        void    Log(std::string indent = "");
    };

}}
