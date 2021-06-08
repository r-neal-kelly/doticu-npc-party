/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "intrinsic.h"
#include "party_follower.h"
#include "party_follower_id.h"
#include "party_follower_limit.h"
#include "party_member_id.h"
#include "party_member_sort_type.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_t;
    class Members_t;
    class Party_t;

    class Followers_t
    {
    public:
        static constexpr size_t                         MAX_FOLLOWERS                       = Consts_t::NPCP::Int::MAX_FOLLOWERS;

        static constexpr Bool_t                         DEFAULT_DO_LEVEL                    = true;
        static constexpr Bool_t                         DEFAULT_DO_RESURRECT_AUTOMATICALLY  = true;
        static constexpr Bool_t                         DEFAULT_DO_SOJOURN_AUTOMATICALLY    = false;

        static constexpr Follower_Limit_t::value_type   DEFAULT_LIMIT                       = MAX_FOLLOWERS;

        static constexpr Member_Sort_Type_e::value_type DEFAULT_SORT_TYPE                   = Member_Sort_Type_e::NAME;

    public:
        class Save_t
        {
        public:
            Bool_t                      do_level;
            Bool_t                      do_resurrect_automatically;
            Bool_t                      do_sojourn_automatically;

            maybe<Follower_Limit_t>     limit;

            maybe<Member_Sort_Type_e>   sort_type;

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
            Save_t      save;

            Follower_t  followers[MAX_FOLLOWERS];

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        static Party_t&     Party();
        static Members_t&   Members();

    public:
        State_t state;

    public:
        Followers_t();
        Followers_t(const Followers_t& other) = delete;
        Followers_t(Followers_t&& other) noexcept = delete;
        Followers_t& operator =(const Followers_t& other) = delete;
        Followers_t& operator =(Followers_t&& other) noexcept = delete;
        ~Followers_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);
        void    On_Update();

    public:
        State_t&    State();
        Save_t&     Save();

    public:
        Bool_t                      Do_Level();
        void                        Do_Level(Bool_t value);
        Bool_t                      Do_Resurrect_Automatically();
        void                        Do_Resurrect_Automatically(Bool_t value);
        Bool_t                      Do_Sojourn_Automatically();
        void                        Do_Sojourn_Automatically(Bool_t value);

        some<Follower_Limit_t>      Limit();
        void                        Limit(maybe<Follower_Limit_t> value);

        some<Member_Sort_Type_e>    Sort_Type();
        void                        Sort_Type(maybe<Member_Sort_Type_e> value);

    public:
        some<Quest_t*>              Quest();
        some<Alias_Reference_t*>    Alias(some<Follower_ID_t> follower_id);
        Follower_t&                 Follower(some<Follower_ID_t> follower_id);
        maybe<Follower_t*>          Follower(Member_t& member);
        maybe<Follower_t*>          Follower(some<Actor_t*> actor);

        maybe<Follower_ID_t>        Inactive_ID();
        size_t                      Active_Count();
        size_t                      Inactive_Count();

        Bool_t                      Has(Member_t& member);
        Bool_t                      Has(some<Actor_t*> actor);
        maybe<Follower_t*>          Add(Member_t& member);
        maybe<Follower_t*>          Add(some<Actor_t*> actor);
        Bool_t                      Remove(Follower_t& follower);
        Bool_t                      Remove(some<Actor_t*> actor);

        void                        Refill_Aliases();
        void                        Reset_Options();
    };

}}
