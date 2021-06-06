/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "intrinsic.h"
#include "party_display.h"
#include "party_display_id.h"
#include "party_display_limit.h"
#include "party_member_id.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Members_t;
    class Party_t;

    class Displays_t
    {
    public:
        static constexpr size_t                         MAX_DISPLAYS    = Consts_t::NPCP::Int::MAX_DISPLAYS;

        static constexpr Display_Limit_t::value_type    DEFAULT_LIMIT   = MAX_DISPLAYS;

    public:
        class Save_t
        {
        public:
            maybe<Display_Limit_t>  limit;

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

            Display_t   displays[MAX_DISPLAYS];

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
        Displays_t();
        Displays_t(const Displays_t& other) = delete;
        Displays_t(Displays_t&& other) noexcept = delete;
        Displays_t& operator =(const Displays_t& other) = delete;
        Displays_t& operator =(Displays_t&& other) noexcept = delete;
        ~Displays_t();

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
        Display_t&          Display(some<Display_ID_t> display_id);

        maybe<Display_t*>   Active_Display(some<Member_ID_t> member_id);
    };

}}
