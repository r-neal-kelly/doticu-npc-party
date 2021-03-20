/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/quest.h"

#include "intrinsic.h"
#include "party_member_rating.h"

namespace doticu_npcp { namespace Party {

    class Member_Outfit_t;

    class Members_t :
        public Quest_t
    {
    public:
        static constexpr size_t MAX_MEMBERS = 1024;

    public:
        class State
        {
        public:
            Vector_t<maybe<Actor_t*>>               actors;                     // u64

            Vector_t<maybe<const Actor_Base_t*>>    static_bases;               // u64
            Vector_t<maybe<Actor_Base_t*>>          custom_bases;               // u64

            Vector_t<maybe<Outfit_t*>>              default_outfits;            // u64
            Vector_t<maybe<Outfit_t*>>              vanilla_outfits;            // u64

            Vector_t<maybe<Member_Outfit_t*>>       member_member_outfits;      // u64
            Vector_t<maybe<Member_Outfit_t*>>       immobile_member_outfits;    // u64
            Vector_t<maybe<Member_Outfit_t*>>       settler_member_outfits;     // u64
            Vector_t<maybe<Member_Outfit_t*>>       thrall_member_outfits;      // u64
            Vector_t<maybe<Member_Outfit_t*>>       follower_member_outfits;    // u64
            Vector_t<maybe<Member_Outfit_t*>>       vanilla_member_outfits;     // u64
            Vector_t<maybe<Member_Outfit_t*>>       default_member_outfits;     // u64
            Vector_t<maybe<Member_Outfit_t*>>       current_member_outfits;     // u64
            Vector_t<maybe<Member_Outfit_t*>>       backup_member_outfits;      // u64

            Vector_t<String_t>                      names;                      // u64

            Vector_t<maybe<Reference_t*>>           packs;                      // u64

            Vector_t<maybe<Voice_Type_t*>>          voice_types;                // u64

            Vector_t<Relation_e>                    player_relations;           // u8
            //Vector_t<Style_e>                       styles;                     // u8 (we need to define this)
            Vector_t<Vitality_e>                    vitalities;                 // u8
            Vector_t<Member_Rating_t>               ratings;                    // u8

        public:
            State();
            State(const State& other)                   = delete;
            State(State&& other) noexcept               = delete;
            State& operator =(const State& other)       = delete;
            State& operator =(State&& other) noexcept   = delete;
            ~State();

        public:
            void Save();
            void Load();
        };

    public:
        static State state;

    public:
        static some<Members_t*>     Self();
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static some<V::Object_t*>   Object();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        static void Initialize();
        static void Before_Save();
        static void After_Load();

    public:
        void u_0_10_0();
    };

}}
