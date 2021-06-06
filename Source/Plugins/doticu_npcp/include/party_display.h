/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_display_id.h"
#include "party_member_id.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Displays_t;
    class Member_t;
    class Members_t;
    class Party_t;

    class Display_t
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
        static Displays_t&  Displays();

    public:
        State_t state;

    public:
        Display_t();
        Display_t(some<Member_ID_t> member_id);
        Display_t(const Display_t& other) = delete;
        Display_t(Display_t&& other) noexcept = delete;
        Display_t& operator =(const Display_t& other) = delete;
        Display_t& operator =(Display_t&& other) noexcept = delete;
        ~Display_t();

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
        some<Display_ID_t>  Display_ID();

        Member_t&           Member();

    public:
        void    Evaluate_In_Parallel(std::mutex& parallel_lock);
    };

}}
