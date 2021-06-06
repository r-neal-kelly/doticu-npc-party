/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_settler_eater.h"
#include "party_settler_guard.h"
#include "party_settler_sandboxer.h"
#include "party_settler_sitter.h"
#include "party_settler_sleeper.h"
#include "party_settler_type.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Slot_t
    {
    public:
        class Save_t
        {
        public:
            maybe<Settler_Type_e>   settler_type;

        public:
            Save_t();
            Save_t(const Save_t& other) = delete;
            Save_t(Save_t&& other) noexcept = delete;
            Save_t& operator =(const Save_t& other) = delete;
            Save_t& operator =(Save_t&& other) noexcept = delete;
            ~Save_t();

        public:
            void    Write(std::ofstream& file);
            void    Read(std::ifstream& file);
        };

        union Settler_u
        {
        public:
            Settler_Sandboxer_t sandboxer;
            Settler_Sleeper_t   sleeper;
            Settler_Sitter_t    sitter;
            Settler_Eater_t     eater;
            Settler_Guard_t     guard;

        public:
            Settler_u();
            Settler_u(const Settler_u& other) = delete;
            Settler_u(Settler_u&& other) noexcept = delete;
            Settler_u& operator =(const Settler_u& other) = delete;
            Settler_u& operator =(Settler_u&& other) noexcept = delete;
            ~Settler_u();
        };

        class State_t
        {
        public:
            Save_t      save;

            Settler_u   settler;

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        State_t state;

    public:
        Settler_Slot_t();
        Settler_Slot_t(some<Settler_Type_e> settler_type);
        Settler_Slot_t(const Settler_Slot_t& other) = delete;
        Settler_Slot_t(Settler_Slot_t&& other) noexcept = delete;
        Settler_Slot_t& operator =(const Settler_Slot_t& other) = delete;
        Settler_Slot_t& operator =(Settler_Slot_t&& other) noexcept = delete;
        ~Settler_Slot_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);

    public:
        State_t&    State();
        Save_t&     Save();

    public:
        Bool_t  Is_Active();

        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
