/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_preferred_speed.h"

#include "intrinsic.h"
#include "party_settler_attention.h"
#include "party_settler_flags_sitter.h"
#include "party_settler_id.h"
#include "party_settler_marker.h"
#include "party_settler_radius.h"
#include "party_settler_time.h"
#include "party_settler_type_i.h"
#include "party_settler_value_index_sitter.h"
#include "party_settler_wander_distance.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Sitter_t :
        public Settler_Type_i
    {
    public:
        using Flags_e   = Settler_Flags_Sitter_e;
        using Index_e   = Settler_Value_Index_Sitter_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        class Save_t
        {
        public:
            maybe<Reference_t*> seat;

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
        Settler_Sitter_t();
        Settler_Sitter_t(const Settler_Sitter_t& other) = delete;
        Settler_Sitter_t(Settler_Sitter_t&& other) noexcept = delete;
        Settler_Sitter_t& operator =(const Settler_Sitter_t& other) = delete;
        Settler_Sitter_t& operator =(Settler_Sitter_t&& other) noexcept = delete;

    public:
        virtual         ~Settler_Sitter_t();

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
        Bool_t              Only_Preferred_Path();
        void                Only_Preferred_Path(Bool_t value);
        Bool_t              Stop_Movement();
        void                Stop_Movement(Bool_t value);

        some<Package_t*>    Package(some<Settler_ID_t> settler_id);

    public:
        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
