/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "intrinsic.h"
#include "party_displays.h"
#include "party_expoees.h"
#include "party_followers.h"
#include "party_member_id.h"
#include "party_member_update_ai.h"
#include "party_members.h"
#include "party_settlers.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Party_t
    {
    public:
        static constexpr size_t MAX_MEMBERS     = Consts_t::NPCP::Int::MAX_MEMBERS;
        static constexpr size_t MAX_FOLLOWERS   = Consts_t::NPCP::Int::MAX_FOLLOWERS;
        static constexpr size_t MAX_DISPLAYS    = Consts_t::NPCP::Int::MAX_DISPLAYS;

    public:
        class Save_t
        {
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
            Save_t                      save;

            Members_t                   members;
            Settlers_t                  settlers;
            Expoees_t                   expoees;
            Displays_t                  displays;
            Followers_t                 followers;

            maybe<Script_t*>            scripts[MAX_MEMBERS];
            maybe<Member_Update_AI_e>   update_ais[MAX_MEMBERS];

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

        static Bool_t   Is_Token(some<Bound_Object_t*> bound_object);

    public:
        State_t state;

    public:
        Party_t();
        Party_t(const Party_t& other) = delete;
        Party_t(Party_t&& other) noexcept = delete;
        Party_t& operator =(const Party_t& other) = delete;
        Party_t& operator =(Party_t&& other) noexcept = delete;
        ~Party_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);
        void    On_Update();

    public:
        State_t&        State();
        Save_t&         Save();

        Members_t&      Members();
        Settlers_t&     Settlers();
        Expoees_t&      Expoees();
        Displays_t&     Displays();
        Followers_t&    Followers();

    public:
        some<Script_t*>             Script(some<Member_ID_t> member_id);

        maybe<Member_Update_AI_e>   Update_AI(some<Member_ID_t> member_id);
        void                        Update_AI(some<Member_ID_t> member_id, some<Member_Update_AI_e> value);

    public:
        void    Evaluate();
        void    Evaluate_In_Parallel(some<Member_ID_t> id, std::mutex& parallel_lock);
    };

}}
