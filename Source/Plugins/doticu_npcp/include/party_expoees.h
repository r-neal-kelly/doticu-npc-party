/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "intrinsic.h"
#include "party_expoee.h"
#include "party_expoee_id.h"
#include "party_member_id.h"
#include "party_member_sort_type.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Members_t;
    class Party_t;

    class Expoees_t
    {
    public:
        static constexpr size_t                         MAX_EXPOEES         = Consts_t::NPCP::Int::MAX_EXPOEES;

        static constexpr Member_Sort_Type_e::value_type DEFAULT_SORT_TYPE   = Member_Sort_Type_e::_NONE_;

    public:
        class Save_t
        {
        public:
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

            Expoee_t    expoees[MAX_EXPOEES];

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
        Expoees_t();
        Expoees_t(const Expoees_t& other) = delete;
        Expoees_t(Expoees_t&& other) noexcept = delete;
        Expoees_t& operator =(const Expoees_t& other) = delete;
        Expoees_t& operator =(Expoees_t&& other) noexcept = delete;
        ~Expoees_t();

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
        Expoee_t&               Expoee(some<Expoee_ID_t> expoee_id);
        maybe<Expoee_t*>        Expoee(Member_t& member);
        maybe<Expoee_t*>        Expoee(some<Actor_t*> actor);

        maybe<Expoee_ID_t>      Inactive_ID();
        size_t                  Active_Count();
        size_t                  Inactive_Count();

        Bool_t                  Has(Member_t& member);
        Bool_t                  Has(some<Actor_t*> actor);
        maybe<Expoee_t*>        Add(Member_t& member);
        maybe<Expoee_t*>        Add(some<Actor_t*> actor);
        Bool_t                  Remove(Expoee_t& expoee);
        Bool_t                  Remove(some<Actor_t*> actor);

        void                    Reset_Options();
    };

}}
