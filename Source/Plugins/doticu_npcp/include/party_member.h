/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "intrinsic.h"

#include "party_member_flags.h"
#include "party_member_id.h"
#include "party_member_rating.h"
#include "party_member_relation.h"
#include "party_member_style.h"
#include "party_member_suit_type.h"
#include "party_member_vitality.h"

namespace doticu_npcp { namespace Party {

    class Member_Suit_t;
    class Members_t;

    class Member_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ALIAS_REFERENCE,
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        some<Members_t*>            members;
        Member_ID_t                 member_id;

        some<Alias_Reference_t*>    alias_reference;
        some<Actor_t*>              actor;
        some<Actor_Base_t*>         original_base;
        some<Actor_Base_t*>         custom_base;

        Member_Flags_e              flags;

        String_t                    name;
        maybe<Reference_t*>         pack; // maybe some?
        some<Voice_Type_t*>         voice_type;

        maybe<Outfit_t*>            default_outfit;
        maybe<Outfit_t*>            vanilla_outfit;

        some<Member_Suit_t*>        backup_suit;
        maybe<Member_Suit_t*>       default_suit;
        maybe<Member_Suit_t*>       follower_suit;
        maybe<Member_Suit_t*>       immobile_suit;
        some<Member_Suit_t*>        member_suit;
        maybe<Member_Suit_t*>       settler_suit;
        maybe<Member_Suit_t*>       thrall_suit;
        maybe<Member_Suit_t*>       vanilla_suit;

        maybe<Member_Rating_t>      rating;
        some<Member_Relation_e>     relation;
        some<Member_Style_e>        style;
        maybe<Member_Suit_Type_e>   suit_type;
        some<Member_Vitality_e>     member_vitality;

    public:
        Member_t(some<Members_t*> members, Member_ID_t member_id);
        Member_t(const Member_t& other)                                                 = delete;
        Member_t(Member_t&& other) noexcept                                             = delete;
        Member_t& operator =(const Member_t& other)                                     = delete;
        Member_t& operator =(Member_t&& other) noexcept                                 = delete;
        ~Member_t();

    public:
        Bool_t Is_Valid();

    public:
        void Log(std::string indent = "");
    };

}}
