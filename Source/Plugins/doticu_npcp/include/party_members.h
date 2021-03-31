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
#include "party_member_sort_type.h"
#include "party_member_style.h"
#include "party_member_suit_fill_type.h"
#include "party_member_suit_type.h"
#include "party_member_vitality.h"

namespace doticu_npcp { namespace Party {

    class Member_Suit_t;

    class Members_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t                                 MAX_MEMBERS                         = 1024;

        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_BODY_PERCENT    = 100;
        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_FEET_PERCENT    = 66;
        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_HANDS_PERCENT   = 66;
        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_HEAD_PERCENT    = 33;

        static constexpr Int_t                                  DEFAULT_LIMIT                       = MAX_MEMBERS;

        static constexpr Bool_t                                 DEFAULT_DO_AUTO_SUITS               = false;
        static constexpr Bool_t                                 DEFAULT_DO_AUTO_IMMOBILE_SUIT       = false;
        static constexpr Bool_t                                 DEFAULT_DO_FILL_SUITS               = true;

        static constexpr Member_Relation_e::value_type          DEFAULT_RELATION                    = Member_Relation_e::_NONE_;
        static constexpr Member_Style_e::value_type             DEFAULT_STYLE                       = Member_Style_e::DEFAULT;
        static constexpr Member_Suit_Type_e::value_type         DEFAULT_SUIT_TYPE                   = Member_Suit_Type_e::MEMBER;
        static constexpr Member_Vitality_e::value_type          DEFAULT_VITALITY                    = Member_Vitality_e::_NONE_;

        static constexpr Member_Suit_Fill_Type_e::value_type    DEFAULT_CLONE_SUIT_FILL_TYPE        = Member_Suit_Fill_Type_e::REFERENCE;
        static constexpr Member_Sort_Type_e::value_type         DEFAULT_SORT_TYPE                   = Member_Sort_Type_e::NAME;

    public:
        class Save_State
        {
        public:
            Members_t&                          members;

        public:
            Int_t                               limit;

            Bool_t                              do_auto_suits;
            Bool_t                              do_auto_immobile_suit;
            Bool_t                              do_fill_suits;

            some<Member_Relation_e>             default_relation;
            some<Member_Style_e>                default_style;
            maybe<Member_Suit_Type_e>           default_suit_type;
            some<Member_Vitality_e>             default_vitality;

            some<Member_Suit_Fill_Type_e>       clone_suit_fill_type;
            some<Member_Sort_Type_e>            sort_type;

            Vector_t<maybe<Actor_t*>>           actors;
            Vector_t<maybe<Actor_Base_t*>>      original_bases;

            Vector_t<Member_Flags_e>            flags;

            Vector_t<String_t>                  names;
            Vector_t<maybe<Reference_t*>>       packs;
            Vector_t<maybe<Voice_Type_t*>>      voice_types;

            Vector_t<maybe<Outfit_t*>>          default_outfits;
            Vector_t<maybe<Outfit_t*>>          vanilla_outfits;

            Vector_t<maybe<Member_Suit_t*>>     backup_suits;
            Vector_t<maybe<Member_Suit_t*>>     default_suits;
            Vector_t<maybe<Member_Suit_t*>>     follower_suits;
            Vector_t<maybe<Member_Suit_t*>>     immobile_suits;
            Vector_t<maybe<Member_Suit_t*>>     member_suits;
            Vector_t<maybe<Member_Suit_t*>>     settler_suits;
            Vector_t<maybe<Member_Suit_t*>>     thrall_suits;
            Vector_t<maybe<Member_Suit_t*>>     vanilla_suits;

            Vector_t<maybe<Member_Rating_t>>    ratings;
            Vector_t<maybe<Member_Relation_e>>  relations;
            Vector_t<maybe<Member_Style_e>>     styles;
            Vector_t<maybe<Member_Suit_Type_e>> suit_types;
            Vector_t<maybe<Member_Vitality_e>>  vitalities;

        public:
            Save_State(Members_t& members);
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();

        public:
            some<V::Object_t*>                              Object();

            V::Variable_tt<Int_t>&                          Limit();

            V::Variable_tt<Bool_t>&                         Do_Auto_Suits();
            V::Variable_tt<Bool_t>&                         Do_Auto_Immobile_Suit();
            V::Variable_tt<Bool_t>&                         Do_Fill_Suits();

            V::Variable_tt<String_t>&                       Default_Relation();
            V::Variable_tt<String_t>&                       Default_Style();
            V::Variable_tt<String_t>&                       Default_Suit_Type();
            V::Variable_tt<String_t>&                       Default_Vitality();

            V::Variable_tt<String_t>&                       Clone_Suit_Fill_Type();
            V::Variable_tt<String_t>&                       Sort_Type();

            V::Variable_tt<Vector_t<maybe<Actor_t*>>>&      Actors();
            V::Variable_tt<Vector_t<maybe<Actor_Base_t*>>>& Original_Bases();

            V::Variable_tt<Vector_t<Bool_t>>&               Is_Banished_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&               Is_Clone_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&               Is_Immobile_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&               Is_Mannequin_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&               Is_Paralyzed_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&               Is_Reanimated_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&               Is_Thrall_Flags();

            V::Variable_tt<Vector_t<String_t>>&             Names();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Packs();
            V::Variable_tt<Vector_t<maybe<Voice_Type_t*>>>& Voice_Types();

            V::Variable_tt<Vector_t<maybe<Outfit_t*>>>&     Default_Outfits();
            V::Variable_tt<Vector_t<maybe<Outfit_t*>>>&     Vanilla_Outfits();

            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Backup_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Default_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Follower_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Immobile_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Member_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Settler_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Thrall_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&  Vanilla_Suits();

            V::Variable_tt<Vector_t<Int_t>>&                Ratings();
            V::Variable_tt<Vector_t<String_t>>&             Relations();
            V::Variable_tt<Vector_t<String_t>>&             Styles();
            V::Variable_tt<Vector_t<String_t>>&             Suit_Types();
            V::Variable_tt<Vector_t<String_t>>&             Vitalities();

        public:
            void Read();
            void Write();
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        static Bool_t   Do_Allow_Menu_For_All_Actors();
        static void     Do_Allow_Menu_For_All_Actors(Bool_t value);

        static Bool_t   Do_Force_Clone_Uniques();
        static void     Do_Force_Clone_Uniques(Bool_t value);
        static Bool_t   Do_Force_Clone_Generics();
        static void     Do_Force_Clone_Generics(Bool_t value);
        static Bool_t   Do_Force_Unclone_Uniques();
        static void     Do_Force_Unclone_Uniques(Bool_t value);
        static Bool_t   Do_Force_Unclone_Generics();
        static void     Do_Force_Unclone_Generics(Bool_t value);

        static Int_t    Fill_Outfit_Body_Percent();
        static void     Fill_Outfit_Body_Percent(Int_t value);
        static Int_t    Fill_Outfit_Feet_Percent();
        static void     Fill_Outfit_Feet_Percent(Int_t value);
        static Int_t    Fill_Outfit_Hands_Percent();
        static void     Fill_Outfit_Hands_Percent(Int_t value);
        static Int_t    Fill_Outfit_Head_Percent();
        static void     Fill_Outfit_Head_Percent(Int_t value);

    public:
        const some<Quest_t*>            quest;
        Vector_t<maybe<Actor_Base_t*>>  custom_bases;
        Save_State                      save_state;

    public:
        Members_t(some<Quest_t*> quest, Bool_t is_new_game);
        Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Members_t(const Members_t& other)                                           = delete;
        Members_t(Members_t&& other) noexcept                                       = delete;
        Members_t& operator =(const Members_t& other)                               = delete;
        Members_t& operator =(Members_t&& other) noexcept                           = delete;
        ~Members_t();

    public:
        Bool_t                      Has_Alias(Member_ID_t member_id);
        Bool_t                      Has_Alias(Alias_ID_t alias_id);
        Bool_t                      Has_Member(Member_ID_t member_id);
        Bool_t                      Has_Member(some<Actor_t*> actor);

        maybe<Member_ID_t>          Maybe_Free_Member_ID();
        maybe<Member_ID_t>          Add_Member(some<Actor_t*> actor);
        maybe<Member_ID_t>          Add_Member(some<Actor_Base_t*> base);
        maybe<Member_ID_t>          Add_Member_Clone(some<Actor_t*> actor);
        Bool_t                      Remove_Member(Member_ID_t member_id);

        size_t                      Member_Count();

        void                        Validate();

    public:
        some<Alias_Reference_t*>    Alias_Reference(Member_ID_t valid_member_id);
        some<Actor_t*>              Actor(Member_ID_t valid_member_id);
        some<Actor_Base_t*>         Original_Base(Member_ID_t valid_member_id);
        some<Actor_Base_t*>         Custom_Base(Member_ID_t valid_member_id);

        maybe<Member_Suit_Type_e>   Maybe_Current_Suit_Type(Member_ID_t valid_member_id);
        maybe<Member_Suit_t*>       Maybe_Current_Suit(Member_ID_t valid_member_id);

        some<Voice_Type_t*>         Voice_Type(Member_ID_t valid_member_id);
        void                        Voice_Type(Member_ID_t valid_member_id, some<Voice_Type_t*> voice_type);

        some<Member_Vitality_e>     Vitality(Member_ID_t valid_member_id);
        void                        Vitality(Member_ID_t valid_member_id, some<Member_Vitality_e> vitality);

        Bool_t                      Validate_Member(Member_ID_t member_id);

    public:
        void    Before_Save();
        void    After_Save();

    public:
        void Log(std::string indent = "");
    };

    /*
        Just some quick outfitting notes:
            We should use the owner faction on x_lists to with a custom faction indicating that the item is an outfit item.
            We can mark x_lists as outfit items and point to the default outfit that is on the base actor. then we won't need any blank armor.
    */

}}
