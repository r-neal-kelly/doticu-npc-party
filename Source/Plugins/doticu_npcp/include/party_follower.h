/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_follower_id.h"
#include "party_member_id.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Followers_t;
    class Member_t;
    class Members_t;
    class Party_t;

    class Follower_t
    {
    public:
        class Save_t
        {
        public:
            maybe<Member_ID_t>  member_id;

            Bool_t              is_retreater;
            Bool_t              is_saddler;
            Bool_t              is_sojourner;

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
        static Party_t&     Party();
        static Members_t&   Members();
        static Followers_t& Followers();

    public:
        State_t state;

    public:
        Follower_t();
        Follower_t(some<Member_ID_t> member_id);
        Follower_t(const Follower_t& other) = delete;
        Follower_t(Follower_t&& other) noexcept = delete;
        Follower_t& operator =(const Follower_t& other) = delete;
        Follower_t& operator =(Follower_t&& other) noexcept = delete;
        ~Follower_t();

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
        Bool_t              Is_Active();

        some<Member_ID_t>   Member_ID();
        some<Follower_ID_t> Follower_ID();

        Member_t&           Member();

    public:
        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
