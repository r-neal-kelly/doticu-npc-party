/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_preferred_speed.h"

#include "intrinsic.h"
#include "party_settler_attention.h"
#include "party_settler_flags_sleeper.h"
#include "party_settler_id.h"
#include "party_settler_marker.h"
#include "party_settler_radius.h"
#include "party_settler_time.h"
#include "party_settler_type_i.h"
#include "party_settler_value_index_sleeper.h"
#include "party_settler_wander_distance.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Sleeper_t :
        public Settler_Type_i
    {
    public:
        using Flags_e   = Settler_Flags_Sleeper_e;
        using Index_e   = Settler_Value_Index_Sleeper_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        class Save_t
        {
        public:
            maybe<Settler_Attention_t>          attention;
            maybe<Settler_Wander_Distance_t>    wander_distance;
            maybe<Reference_t*>                 bed;

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
        Settler_Sleeper_t();
        Settler_Sleeper_t(const Settler_Sleeper_t& other) = delete;
        Settler_Sleeper_t(Settler_Sleeper_t&& other) noexcept = delete;
        Settler_Sleeper_t& operator =(const Settler_Sleeper_t& other) = delete;
        Settler_Sleeper_t& operator =(Settler_Sleeper_t&& other) noexcept = delete;

    public:
        virtual         ~Settler_Sleeper_t();

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
        Bool_t              Allow_Conversation();
        void                Allow_Conversation(Bool_t value);
        Bool_t              Allow_Eating();
        void                Allow_Eating(Bool_t value);
        Bool_t              Allow_Horse_Riding();
        void                Allow_Horse_Riding(Bool_t value);
        Bool_t              Allow_Idle_Markers();
        void                Allow_Idle_Markers(Bool_t value);
        Bool_t              Allow_Sitting();
        void                Allow_Sitting(Bool_t value);
        Bool_t              Allow_Sleeping();
        void                Allow_Sleeping(Bool_t value);
        Bool_t              Allow_Special_Furniture();
        void                Allow_Special_Furniture(Bool_t value);
        Bool_t              Allow_Wandering();
        void                Allow_Wandering(Bool_t value);
        Bool_t              Lock_Doors();
        void                Lock_Doors(Bool_t value);
        Bool_t              Only_Preferred_Path();
        void                Only_Preferred_Path(Bool_t value);
        Bool_t              Warn_Before_Locking();
        void                Warn_Before_Locking(Bool_t value);

        some<Package_t*>    Package(some<Settler_ID_t> settler_id);

    public:
        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
