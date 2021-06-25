/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_preferred_speed.h"

#include "intrinsic.h"
#include "party_settler_flags.h"
#include "party_settler_id.h"
#include "party_settler_marker.h"
#include "party_settler_radius.h"
#include "party_settler_time.h"
#include "party_settler_type_e.h"
#include "party_settler_value_index.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Type_i
    {
    public:
        using Flags_e   = Settler_Flags_e;
        using Index_e   = Settler_Value_Index_e;

    public:
        static constexpr Settler_Radius_t::value_type   DEFAULT_RADIUS  = 2048;
        static constexpr Preferred_Speed_e::value_type  DEFAULT_SPEED   = Preferred_Speed_e::WALK;

    public:
        class Save_t
        {
        public:
            Flags_e                     flags;
            maybe<Settler_Time_t>       time;
            maybe<Settler_Marker_t>     marker;
            maybe<Settler_Radius_t>     radius;
            maybe<Preferred_Speed_e>    speed;

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
        Settler_Type_i();
        Settler_Type_i(const Settler_Type_i& other) = delete;
        Settler_Type_i(Settler_Type_i&& other) noexcept = delete;
        Settler_Type_i& operator =(const Settler_Type_i& other) = delete;
        Settler_Type_i& operator =(Settler_Type_i&& other) noexcept = delete;

    public:
        virtual         ~Settler_Type_i();

        virtual void    On_After_New_Game();
        virtual void    On_Before_Save_Game(std::ofstream& file);
        virtual void    On_After_Save_Game();
        virtual void    On_Before_Load_Game();
        virtual void    On_After_Load_Game(std::ifstream& file);
        virtual void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);

    public:
        State_t&        State();
        const State_t&  State() const;
        Save_t&         Save();
        const Save_t&   Save() const;

    public:
        Bool_t  Is_Active() const;

        Bool_t  Is_Enabled() const;
        void    Is_Enabled(Bool_t value);

        Bool_t  Allow_Swimming() const;
        void    Allow_Swimming(Bool_t value);
        Bool_t  Always_Sneak() const;
        void    Always_Sneak(Bool_t value);
        Bool_t  Ignore_Combat() const;
        void    Ignore_Combat(Bool_t value);
        Bool_t  Keep_Weapons_Drawn() const;
        void    Keep_Weapons_Drawn(Bool_t value);
        Bool_t  Hide_Weapons() const;
        void    Hide_Weapons(Bool_t value);
        Bool_t  Skip_Combat_Alert() const;
        void    Skip_Combat_Alert(Bool_t value);

        Bool_t  Allow_Hellos_To_Player() const;
        void    Allow_Hellos_To_Player(Bool_t value);
        Bool_t  Allow_Hellos_To_NPCs() const;
        void    Allow_Hellos_To_NPCs(Bool_t value);
        Bool_t  Allow_Idle_Chatter() const;
        void    Allow_Idle_Chatter(Bool_t value);
        Bool_t  Allow_Aggro_Radius() const;
        void    Allow_Aggro_Radius(Bool_t value);
        Bool_t  Allow_World_Interactions() const;
        void    Allow_World_Interactions(Bool_t value);
        Bool_t  Comment_On_Friendly_Fire() const;
        void    Comment_On_Friendly_Fire(Bool_t value);
        Bool_t  Inspect_Corpses() const;
        void    Inspect_Corpses(Bool_t value);
        Bool_t  Observe_Combat() const;
        void    Observe_Combat(Bool_t value);
        Bool_t  React_To_Player_Actions() const;
        void    React_To_Player_Actions(Bool_t value);

    public:
        some<Settler_Time_t>    Time() const;
        void                    Time(some<Settler_Time_t> value);

        some<Settler_Marker_t>  Marker() const;
        void                    Marker(some<Settler_Marker_t> value);

        some<Settler_Radius_t>  Radius() const;
        void                    Radius(some<Settler_Radius_t> value);

        some<Preferred_Speed_e> Speed() const;
        void                    Speed(some<Preferred_Speed_e> value);

    public:
        void    Activate(some<Settler_Time_t> time, some<Settler_Marker_t> marker);
        void    Deactivate();
    };

}}
