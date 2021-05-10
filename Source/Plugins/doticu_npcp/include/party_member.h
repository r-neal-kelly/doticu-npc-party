/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "intrinsic.h"
#include "party_member_alpha.h"
#include "party_member_combat_style.h"
#include "party_member_id.h"
#include "party_member_rating.h"
#include "party_member_relation.h"
#include "party_member_suit_type.h"
#include "party_member_vitality.h"

namespace doticu_npcp { namespace Party {

    class Member_Suitcase_t;

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
        some<Member_ID_t>   id;
        Locker_t            locker;

    public:
        Member_t(some<Member_ID_t> id);
        Member_t(const Member_t& other) = delete;
        Member_t(Member_t&& other) noexcept;
        Member_t& operator =(const Member_t& other) = delete;
        Member_t& operator =(Member_t&& other) noexcept;
        ~Member_t();

    public:
        Bool_t  Is_Valid();

    public:
        Bool_t  Is_Banished();
        void    Is_Banished(Bool_t value);

        Bool_t  Is_Clone();
        void    Is_Clone(Bool_t value);

        Bool_t  Is_Enabled();

        Bool_t  Is_Immobile();
        void    Is_Immobile(Bool_t value);

        Bool_t  Is_Mannequin();
        void    Is_Mannequin(Bool_t value);

        Bool_t  Is_Reanimated();
        void    Is_Reanimated(Bool_t value);

        Bool_t  Is_Sneak();
        void    Is_Sneak(Bool_t value);

        Bool_t  Is_Thrall();
        void    Is_Thrall(Bool_t value);

        Bool_t  Is_Untouchable();

        Bool_t  Is_Warrior();
        Bool_t  Is_Mage();
        Bool_t  Is_Archer();
        Bool_t  Is_Coward();

        Bool_t  Is_Mortal();
        void    Is_Mortal(Bool_t value);

        Bool_t  Is_Protected();
        void    Is_Protected(Bool_t value);

        Bool_t  Is_Essential();
        void    Is_Essential(Bool_t value);

        Bool_t  Is_Invulnerable();
        void    Is_Invulnerable(Bool_t value);

        Bool_t  Has_AI();

        Bool_t  Has_Only_Playables(some<Member_Suit_Type_e> type);
        void    Has_Only_Playables(some<Member_Suit_Type_e> type, Bool_t value);

        Bool_t  Has_Suit(some<Member_Suit_Type_e> type);
        void    Has_Suit(some<Member_Suit_Type_e> type, Bool_t value);

    public:
        some<Alias_Reference_t*>    Alias_Reference();
        some<Actor_t*>              Actor();

        some<Actor_Base_t*>         Original_Base();
        some<Actor_Base_t*>         Custom_Base();

        maybe<Member_Alpha_t>       Alpha();
        void                        Alpha(maybe<Member_Alpha_t> alpha);

        some<Reference_t*>          Cache();

        maybe<Combat_Style_t*>      Combat_Style();
        void                        Combat_Style(maybe<Combat_Style_t*> combat_style);
        void                        Combat_Style(Member_Combat_Style_e combat_style);

        maybe<Spell_t*>             Ghost_Ability();
        void                        Ghost_Ability(maybe<Spell_t*> ghost_ability);

        String_t                    Name();
        void                        Name(String_t name);

        maybe<Outfit_t*>            Outfit();
        void                        Outfit(maybe<Outfit_t*> outfit);

        some<Reference_t*>          Pack();

        maybe<Member_Rating_t>      Rating();
        void                        Rating(maybe<Member_Rating_t> rating);

        some<Member_Relation_e>     Relation();
        void                        Relation(maybe<Member_Relation_e> relation);

        maybe<Member_Suit_Type_e>   Suit_Type();
        void                        Suit_Type(maybe<Member_Suit_Type_e> type);

        some<Member_Suitcase_t*>    Suitcase();

        some<Member_Vitality_e>     Vitality();
        void                        Vitality(maybe<Member_Vitality_e> vitality);

        some<Voice_Type_t*>         Voice_Type();
        void                        Voice_Type(maybe<Voice_Type_t*> voice_type);

    public:
        void    Tokenize(some<Bound_Object_t*> object, Container_Entry_Count_t count = 1);
        void    Untokenize(some<Bound_Object_t*> object);

        void    Add_Suit(some<Member_Suit_Type_e> type);
        void    Add_Suit(some<Member_Suit_Type_e> type, some<Outfit_t*> outfit);
        void    Add_Suit(some<Member_Suit_Type_e> type, some<Container_t*> container);
        void    Add_Suit(some<Member_Suit_Type_e> type, some<Actor_Base_t*> actor_base);
        void    Add_Suit(some<Member_Suit_Type_e> type, some<Reference_t*> reference, Bool_t do_copy);
        void    Add_Suit(some<Member_Suit_Type_e> type, Member_Suit_Template_t suit_template);
        void    Remove_Suit(some<Member_Suit_Type_e> type);

        void    Enforce();

    public:
        explicit operator Bool_t();

    public:
        void    Log(std::string indent = "");
    };

}}
