/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "intrinsic.h"
#include "party_members.h"

namespace doticu_npcp { namespace Party {

    class Expoees_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t MAX_EXPOEES = Members_t::MAX_MEMBERS;

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
        Expoees_t(some<Quest_t*> quest, Bool_t is_new_game);
        Expoees_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Expoees_t(const Expoees_t& other)                                           = delete;
        Expoees_t(Expoees_t&& other) noexcept                                       = delete;
        Expoees_t& operator =(const Expoees_t& other)                               = delete;
        Expoees_t& operator =(Expoees_t&& other) noexcept                           = delete;
        ~Expoees_t();

    public:
        void    Before_Save();
        void    After_Save();

    public:
        void    Validate();

    public:
        void    Log(std::string indent = "");
    };

}}
