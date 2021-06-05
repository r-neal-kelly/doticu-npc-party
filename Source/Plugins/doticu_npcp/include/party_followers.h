/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <fstream>

#include "consts.h"
#include "party.h"
#include "party_follower.h"
#include "party_follower_id.h"
#include "party_follower_limit.h"
#include "party_member_sort_type.h"

namespace doticu_skylib { namespace doticu_npcp {

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
        static void     Register_Me(some<Virtual::Machine_t*> machine);

        static Party_t& Party();

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
        Bool_t                      Do_Auto_Resurrect();
        void                        Do_Auto_Resurrect(Bool_t value);
        Bool_t                      Do_Auto_Sojourn();
        void                        Do_Auto_Sojourn(Bool_t value);
        Bool_t                      Do_Level();
        void                        Do_Level(Bool_t value);

        some<Follower_Limit_t>      Limit();
        void                        Limit(maybe<Follower_Limit_t> value);

        some<Member_Sort_Type_e>    Sort_Type();
        void                        Sort_Type(maybe<Member_Sort_Type_e> value);

    public:
        Bool_t                  Has_Alias(some<Follower_ID_t> follower_id);
        Bool_t                  Has_Alias(Alias_ID_t alias_id);
        Bool_t                  Has_Follower(some<Follower_ID_t> follower_id);
        Bool_t                  Has_Follower(some<Member_ID_t> member_id);
        Bool_t                  Has_Follower(some<Actor_t*> actor);

        maybe<Follower_ID_t>    Used_Follower_ID(some<Member_ID_t> member_id);
        maybe<Follower_ID_t>    Used_Follower_ID(some<Actor_t*> actor);
        maybe<Follower_ID_t>    Unused_Follower_ID();

        maybe<Follower_ID_t>    Add_Follower(some<Member_ID_t> member_id);
        Bool_t                  Remove_Follower(some<Follower_ID_t> follower_id);

        size_t                  Follower_Count();

    public:
        some<Alias_Reference_t*>    Alias(some<Follower_ID_t> valid_follower_id);
        some<Actor_t*>              Actor(some<Follower_ID_t> valid_follower_id);
        some<Member_ID_t>           Member_ID(some<Follower_ID_t> valid_follower_id);

        Bool_t                      Is_Retreater(some<Follower_ID_t> valid_follower_id);
        void                        Is_Retreater(some<Follower_ID_t> valid_follower_id, Bool_t value);

        Bool_t                      Is_Saddler(some<Follower_ID_t> valid_follower_id);
        void                        Is_Saddler(some<Follower_ID_t> valid_follower_id, Bool_t value);

        Bool_t                      Is_Sojourner(some<Follower_ID_t> valid_follower_id);
        void                        Is_Sojourner(some<Follower_ID_t> valid_follower_id, Bool_t value);
    };

}}
