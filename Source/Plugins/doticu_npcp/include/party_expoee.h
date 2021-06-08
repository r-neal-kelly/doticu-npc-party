/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_expoee_id.h"
#include "party_member_id.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Expoees_t;
    class Member_t;
    class Members_t;
    class Party_t;

    class Expoee_t
    {
    public:
        class Save_t
        {
        public:
            maybe<Member_ID_t>  member_id;

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
        static Expoees_t&   Expoees();

    public:
        State_t state;

    public:
        Expoee_t();
        Expoee_t(some<Member_ID_t> member_id, some<Expoee_ID_t> expoee_id);
        Expoee_t(const Expoee_t& other) = delete;
        Expoee_t(Expoee_t&& other) noexcept = delete;
        Expoee_t& operator =(const Expoee_t& other) = delete;
        Expoee_t& operator =(Expoee_t&& other) noexcept = delete;
        ~Expoee_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);

    public:
        State_t&            State();
        Save_t&             Save();

        maybe<Member_ID_t>  Paired_Member_ID();
        void                Paired_Member_ID(maybe<Member_ID_t> member_id);
        maybe<Member_t*>    Paired_Member();

        void                Reset();

    public:
        Bool_t              Is_Active();

        some<Member_ID_t>   Member_ID();
        some<Expoee_ID_t>   Expoee_ID();

        some<Actor_t*>      Actor();
        Member_t&           Member();

    public:
        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
