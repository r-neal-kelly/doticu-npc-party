/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_time.h"
#include "doticu_skylib/enum_preferred_speed.h"

#include "intrinsic.h"
#include "party_settler_attention.h"
#include "party_settler_flags_eater.h"
#include "party_settler_id.h"
#include "party_settler_marker.h"
#include "party_settler_radius.h"
#include "party_settler_type.h"
#include "party_settler_value_index_eater.h"
#include "party_settler_wander_distance.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Eater_t
    {
    public:
        using Flags_e   = Settler_Flags_Eater_e;
        using Index_e   = Settler_Value_Index_Eater_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        class Save_t
        {
        public:
            Flags_e                             flags;
            maybe<Calendar_Time_t>              time;
            maybe<Calendar_Time_t>              duration;
            maybe<Settler_Marker_t>             marker;
            maybe<Settler_Radius_t>             radius;
            maybe<Preferred_Speed_e>            speed;
            maybe<Settler_Attention_t>          attention;
            maybe<Settler_Wander_Distance_t>    wander_distance;

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
        Settler_Eater_t();
        Settler_Eater_t(const Settler_Eater_t& other) = delete;
        Settler_Eater_t(Settler_Eater_t&& other) noexcept = delete;
        Settler_Eater_t& operator =(const Settler_Eater_t& other) = delete;
        Settler_Eater_t& operator =(Settler_Eater_t&& other) noexcept = delete;
        ~Settler_Eater_t();

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
        Bool_t              Is_Enabled();
        void                Is_Enabled(Bool_t value);

        some<Package_t*>    Package(some<Settler_ID_t> settler_id);

    public:
        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
