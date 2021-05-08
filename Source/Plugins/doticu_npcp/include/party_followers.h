/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "intrinsic.h"
#include "party_follower_flags.h"
#include "party_follower_id.h"
#include "party_follower_limit.h"
#include "party_main.h"
#include "party_member_sort_type.h"

namespace doticu_npcp { namespace Party {

    class Followers_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t                         MAX_FOLLOWERS               = Consts_t::NPCP::Int::MAX_FOLLOWERS;

        static constexpr Follower_Limit_t::value_type   DEFAULT_LIMIT               = MAX_FOLLOWERS;

        static constexpr Bool_t                         DEFAULT_DO_AUTO_RESURRECT   = true;
        static constexpr Bool_t                         DEFAULT_DO_AUTO_SOJOURN     = false;
        static constexpr Bool_t                         DEFAULT_DO_LEVEL            = true;

        static constexpr Member_Sort_Type_e::value_type DEFAULT_SORT_TYPE           = Member_Sort_Type_e::NAME;

    public:
        class Save_State
        {
        public:
            const some<Quest_t*>            quest;

        public:
            some<Follower_Limit_t>          limit;

            Bool_t                          do_auto_resurrect;
            Bool_t                          do_auto_sojourn;
            Bool_t                          do_level;

            some<Member_Sort_Type_e>        sort_type;

        public:
            Vector_t<maybe<Member_ID_t>>    member_ids;

            Vector_t<Follower_Flags_e>      flags;

        public:
            Save_State(const some<Quest_t*> quest);
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();

        public:
            some<V::Object_t*>                  Object();

        public:
            V::Variable_tt<Int_t>&              Limit();

            V::Variable_tt<Bool_t>&             Do_Auto_Resurrect();
            V::Variable_tt<Bool_t>&             Do_Auto_Sojourn();
            V::Variable_tt<Bool_t>&             Do_Level();

            V::Variable_tt<String_t>&           Sort_Type();

        public:
            V::Variable_tt<Vector_t<Int_t>>&    Member_IDs();

            V::Variable_tt<Vector_t<Bool_t>>&   Flags_Is_Retreater();
            V::Variable_tt<Vector_t<Bool_t>>&   Flags_Is_Saddler();
            V::Variable_tt<Vector_t<Bool_t>>&   Flags_Is_Sojourner();

        public:
            void    Read();
            void    Write();
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        const some<Quest_t*>    quest;
        Save_State              save_state;

    public:
        Followers_t(some<Quest_t*> quest, Bool_t is_new_game);
        Followers_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Followers_t(const Followers_t& other)                                       = delete;
        Followers_t(Followers_t&& other) noexcept                                   = delete;
        Followers_t& operator =(const Followers_t& other)                           = delete;
        Followers_t& operator =(Followers_t&& other) noexcept                       = delete;
        ~Followers_t();

    public:
        void    Before_Save();
        void    After_Save();
        void    Validate();

    public:
        Main_t&     Main();
        Members_t&  Members();

    public:
        some<Follower_Limit_t>      Limit();
        void                        Limit(some<Follower_Limit_t> value);

        Bool_t                      Do_Auto_Resurrect();
        void                        Do_Auto_Resurrect(Bool_t value);
        Bool_t                      Do_Auto_Sojourn();
        void                        Do_Auto_Sojourn(Bool_t value);
        Bool_t                      Do_Level();
        void                        Do_Level(Bool_t value);

        some<Member_Sort_Type_e>    Sort_Type();
        void                        Sort_Type(some<Member_Sort_Type_e> value);

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
        some<Alias_Reference_t*>    Alias_Reference(some<Follower_ID_t> valid_follower_id);
        some<Actor_t*>              Actor(some<Follower_ID_t> valid_follower_id);
        some<Member_ID_t>           Member_ID(some<Follower_ID_t> valid_follower_id);

        Bool_t                      Is_Retreater(some<Follower_ID_t> valid_follower_id);
        void                        Is_Retreater(some<Follower_ID_t> valid_follower_id, Bool_t value);

        Bool_t                      Is_Saddler(some<Follower_ID_t> valid_follower_id);
        void                        Is_Saddler(some<Follower_ID_t> valid_follower_id, Bool_t value);

        Bool_t                      Is_Sojourner(some<Follower_ID_t> valid_follower_id);
        void                        Is_Sojourner(some<Follower_ID_t> valid_follower_id, Bool_t value);

    public:
        void    Enforce(some<Follower_ID_t> follower_id);

    public:
        void    Log(std::string indent = "");
    };

}}
