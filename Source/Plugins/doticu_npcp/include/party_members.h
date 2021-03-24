/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_member_flags.h"
#include "party_member_rating.h"
#include "party_member_style.h"

namespace doticu_npcp { namespace Party {

    using Member_ID_t = size_t;

    class Member_Suit_t;

    class Members_t
    {
    public:
        static constexpr size_t MAX_MEMBERS = 1024;

    protected:
        class Save_State
        {
        public:
            Vector_t<maybe<Actor_t*>>       actors;
            Vector_t<maybe<Actor_Base_t*>>  original_bases;

            Vector_t<Member_Flags_e>        flags;

            Vector_t<String_t>              names;
            Vector_t<maybe<Reference_t*>>   packs;
            Vector_t<maybe<Voice_Type_t*>>  voice_types;

            Vector_t<maybe<Outfit_t*>>      default_outfits;
            Vector_t<maybe<Outfit_t*>>      vanilla_outfits;

            Vector_t<maybe<Member_Suit_t*>> backup_suits;
            Vector_t<maybe<Member_Suit_t*>> current_suits;
            Vector_t<maybe<Member_Suit_t*>> default_suits;
            Vector_t<maybe<Member_Suit_t*>> follower_suits;
            Vector_t<maybe<Member_Suit_t*>> immobile_suits;
            Vector_t<maybe<Member_Suit_t*>> member_suits;
            Vector_t<maybe<Member_Suit_t*>> settler_suits;
            Vector_t<maybe<Member_Suit_t*>> thrall_suits;
            Vector_t<maybe<Member_Suit_t*>> vanilla_suits;

            Vector_t<Member_Rating_t>       ratings;
            Vector_t<Relation_e>            relations;
            Vector_t<Member_Style_e>        styles;
            Vector_t<Vitality_e>            vitalities;

        public:
            Save_State();
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    protected:
        const some<Quest_t*>            quest;
        Vector_t<maybe<Actor_Base_t*>>  custom_bases;
        Save_State                      save_state;

    public:
        Members_t(some<Quest_t*> quest);
        Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Members_t(const Members_t& other)                                           = delete;
        Members_t(Members_t&& other) noexcept                                       = delete;
        Members_t& operator =(const Members_t& other)                               = delete;
        Members_t& operator =(Members_t&& other) noexcept                           = delete;
        ~Members_t();

    protected:
        some<V::Object_t*>                          Object();

        V::Variable_tt<Vector_t<Actor_t*>>&         Actors_Variable();
        V::Variable_tt<Vector_t<Actor_Base_t*>>&    Original_Bases_Variable();

        V::Variable_tt<Vector_t<Bool_t>>&           Is_Banished_Flags_Variable();
        V::Variable_tt<Vector_t<Bool_t>>&           Is_Clone_Flags_Variable();
        V::Variable_tt<Vector_t<Bool_t>>&           Is_Immobile_Flags_Variable();
        V::Variable_tt<Vector_t<Bool_t>>&           Is_Mannequin_Flags_Variable();
        V::Variable_tt<Vector_t<Bool_t>>&           Is_Paralyzed_Flags_Variable();
        V::Variable_tt<Vector_t<Bool_t>>&           Is_Reanimated_Flags_Variable();
        V::Variable_tt<Vector_t<Bool_t>>&           Is_Thrall_Flags_Variable();

        V::Variable_tt<Vector_t<String_t>>&         Names_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Packs_Variable();
        V::Variable_tt<Vector_t<Voice_Type_t*>>&    Voice_Types_Variable();

        V::Variable_tt<Vector_t<Outfit_t*>>&        Default_Outfits_Variable();
        V::Variable_tt<Vector_t<Outfit_t*>>&        Vanilla_Outfits_Variable();

        V::Variable_tt<Vector_t<Reference_t*>>&     Backup_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Current_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Default_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Follower_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Immobile_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Member_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Settler_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Thrall_Suits_Variable();
        V::Variable_tt<Vector_t<Reference_t*>>&     Vanilla_Suits_Variable();

        V::Variable_tt<Vector_t<Int_t>>&            Ratings_Variable();
        V::Variable_tt<Vector_t<Int_t>>&            Relations_Variable();
        V::Variable_tt<Vector_t<String_t>>&         Styles_Variables();
        V::Variable_tt<Vector_t<String_t>>&         Vitalities_Variables();

    public:
        void    Initialize();
        void    Before_Save();
        void    After_Save();
        void    Before_Load();
        void    After_Load();

        void    u_0_10_0();

    public:
        maybe<Member_ID_t>      Add_Member(some<Actor_t*> actor);
        maybe<Member_ID_t>      Add_Member_Clone(some<Actor_t*> actor);
        void                    Remove_Member(Member_ID_t member_id);
        Bool_t                  Validate_Member(Member_ID_t member_id);

        some<Actor_t*>          Some_Actor(Member_ID_t valid_member_id);
        some<Actor_Base_t*>     Some_Original_Base(Member_ID_t valid_member_id);
        some<Actor_Base_t*>     Some_Custom_Base(Member_ID_t valid_member_id);

        maybe<Member_Suit_t*>   Maybe_Current_Suit(Member_ID_t valid_member_id); // if none, they are excluded from algorithm, else we need a flag
        void                    Maybe_Current_Suit(Member_ID_t valid_member_id, maybe<Member_Suit_t*> current_suit);

    public:
        void Log(std::string indent = "");
    };

    /*
        Just some quick outfitting notes:
            We should use the owner faction on x_lists to with a custom faction indicating that the item is an outfit item.
            We can mark x_lists as outfit items and point to the default outfit that is on the base actor. then we won't need any blank armor.
    */

}}
