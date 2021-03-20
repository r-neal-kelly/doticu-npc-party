/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/quest.h"

#include "intrinsic.h"
#include "party_member_flags.h"
#include "party_member_rating.h"
#include "party_member_style.h"

namespace doticu_npcp { namespace Party {

    class Member_Suit_t;

    class Members_t :
        public Quest_t
    {
    public:
        static constexpr size_t MAX_MEMBERS = 1024;

    public:
        class State
        {
        public:
            Vector_t<maybe<Actor_t*>>       actors;
            Vector_t<maybe<Actor_Base_t*>>  original_bases;
            Vector_t<maybe<Actor_Base_t*>>  custom_bases;

            Vector_t<Member_Flags_e>        flags;

            Vector_t<String_t>              names;
            Vector_t<maybe<Reference_t*>>   packs;
            Vector_t<maybe<Voice_Type_t*>>  voice_types;

            Vector_t<maybe<Outfit_t*>>      default_outfits;
            Vector_t<maybe<Outfit_t*>>      vanilla_outfits;
            Vector_t<maybe<Member_Suit_t*>> member_suits;
            Vector_t<maybe<Member_Suit_t*>> immobile_suits;
            Vector_t<maybe<Member_Suit_t*>> settler_suits;
            Vector_t<maybe<Member_Suit_t*>> thrall_suits;
            Vector_t<maybe<Member_Suit_t*>> follower_suits;
            Vector_t<maybe<Member_Suit_t*>> vanilla_suits;
            Vector_t<maybe<Member_Suit_t*>> default_suits;
            Vector_t<maybe<Member_Suit_t*>> current_suits;
            Vector_t<maybe<Member_Suit_t*>> backup_suits;

            Vector_t<Member_Rating_t>       ratings;
            Vector_t<Relation_e>            relations;
            Vector_t<Member_Style_e>        styles;
            Vector_t<Vitality_e>            vitalities;

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
