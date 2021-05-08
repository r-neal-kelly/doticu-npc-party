/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "consts.h"
#include "intrinsic.h"
#include "party_main.h"

namespace doticu_npcp { namespace Party {

    class Displays_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t MAX_DISPLAYS    = Consts_t::NPCP::Int::MAX_DISPLAYS;

        static constexpr size_t DEFAULT_LIMIT   = 8;

    public:
        class Save_State
        {
        public:
            const some<Quest_t*>    quest;

            u16                     limit;

        public:
            Save_State(const some<Quest_t*> quest);
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();

        public:
            some<V::Object_t*>      Object();

            V::Variable_tt<Int_t>&  Limit();

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
        Displays_t(some<Quest_t*> quest, Bool_t is_new_game);
        Displays_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Displays_t(const Displays_t& other)                                         = delete;
        Displays_t(Displays_t&& other) noexcept                                     = delete;
        Displays_t& operator =(const Displays_t& other)                             = delete;
        Displays_t& operator =(Displays_t&& other) noexcept                         = delete;
        ~Displays_t();

    public:
        void    Before_Save();
        void    After_Save();
        void    Validate();

    public:
        void    Log(std::string indent = "");
    };

}}
