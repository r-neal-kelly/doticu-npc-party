/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_settler_attention.h"
#include "party_settler_flags_guard.h"
#include "party_settler_id.h"
#include "party_settler_type_i.h"
#include "party_settler_value_index_guard.h"
#include "party_settler_wander_distance.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Guard_t :
        public Settler_Type_i
    {
    public:
        using Flags_e   = Settler_Flags_Guard_e;
        using Index_e   = Settler_Value_Index_Guard_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        class Save_t
        {
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

        class State_t
        {
        public:
            Save_t  save;

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
        Settler_Guard_t();
        Settler_Guard_t(const Settler_Guard_t& other) = delete;
        Settler_Guard_t(Settler_Guard_t&& other) noexcept = delete;
        Settler_Guard_t& operator =(const Settler_Guard_t& other) = delete;
        Settler_Guard_t& operator =(Settler_Guard_t&& other) noexcept = delete;

    public:
        virtual         ~Settler_Guard_t();

        virtual void    On_After_New_Game() override;
        virtual void    On_Before_Save_Game(std::ofstream& file) override;
        virtual void    On_After_Save_Game() override;
        virtual void    On_Before_Load_Game() override;
        virtual void    On_After_Load_Game(std::ifstream& file) override;
        virtual void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update) override;

    public:
        State_t&        State();
        const State_t&  State() const;
        Save_t&         Save();
        const Save_t&   Save() const;

    public:
        some<Package_t*>    Package(some<Settler_ID_t> settler_id);

    public:
        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
