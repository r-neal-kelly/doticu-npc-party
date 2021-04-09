/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/container_entry_count.h"

#include "consts.h"
#include "intrinsic.h"
#include "party_main.h"
#include "party_member_alpha.h"
#include "party_member_combat_style.h"
#include "party_member_flags.h"
#include "party_member_id.h"
#include "party_member_rating.h"
#include "party_member_relation.h"
#include "party_member_sort_type.h"
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
        static constexpr size_t                                 MAX_MEMBERS                             = Consts_t::NPCP::Int::MAX_MEMBERS;

        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_BODY_PERCENT        = 100;
        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_FEET_PERCENT        = 66;
        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_HANDS_PERCENT       = 66;
        static constexpr size_t                                 DEFAULT_FILL_OUTFIT_HEAD_PERCENT        = 33;

        static constexpr Int_t                                  DEFAULT_LIMIT                           = MAX_MEMBERS;

        static constexpr Bool_t                                 DEFAULT_DO_AUTO_SUITS                   = false;
        static constexpr Bool_t                                 DEFAULT_DO_AUTO_IMMOBILE_SUIT           = false;
        static constexpr Bool_t                                 DEFAULT_DO_FILL_SUITS                   = true;

        static constexpr Bool_t                                 DEFAULT_HAS_UNTOUCHABLE_INVULNERABLES   = false;

        static constexpr Member_Alpha_t::value_type             DEFAULT_ALPHA                           = Member_Alpha_t::_MAX_;
        static constexpr Member_Rating_t::value_type            DEFAULT_RATING                          = Member_Rating_t::_NONE_;
        static constexpr Member_Relation_e::value_type          DEFAULT_RELATION                        = Member_Relation_e::_NONE_;
        static constexpr Member_Combat_Style_e::value_type      DEFAULT_COMBAT_STYLE                    = Member_Combat_Style_e::_NONE_;
        static constexpr Member_Suit_Type_e::value_type         DEFAULT_SUIT_TYPE                       = Member_Suit_Type_e::MEMBER;
        static constexpr Member_Vitality_e::value_type          DEFAULT_VITALITY                        = Member_Vitality_e::_NONE_;
        // maybe default male and default female voices?

        static constexpr Member_Suit_Fill_Type_e::value_type    DEFAULT_MEMBER_SUIT_FILL_TYPE           = Member_Suit_Fill_Type_e::REFERENCE;
        static constexpr Member_Sort_Type_e::value_type         DEFAULT_SORT_TYPE                       = Member_Sort_Type_e::NAME;

    public:
        class Save_State
        {
        public:
            const some<Quest_t*>                quest;

            Int_t                               limit;

            Bool_t                              do_auto_suits;
            Bool_t                              do_auto_immobile_suit;
            Bool_t                              do_fill_suits;

            Bool_t                              has_untouchable_invulnerables;

            maybe<Member_Combat_Style_e>        default_combat_style;
            maybe<Member_Relation_e>            default_relation;
            maybe<Member_Suit_Type_e>           default_suit_type;
            maybe<Member_Vitality_e>            default_vitality;

            some<Member_Suit_Fill_Type_e>       member_suit_fill_type;
            some<Member_Sort_Type_e>            sort_type;

            Vector_t<maybe<Actor_t*>>           actors;
            Vector_t<maybe<Actor_Base_t*>>      original_bases;

            Vector_t<Member_Flags_e>            flags;

            Vector_t<String_t>                  names;
            Vector_t<maybe<Reference_t*>>       packs;
            Vector_t<maybe<Combat_Style_t*>>    combat_styles;
            Vector_t<maybe<Spell_t*>>           ghost_abilities;
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

            Vector_t<maybe<Member_Alpha_t>>     alphas;
            Vector_t<maybe<Member_Rating_t>>    ratings;
            Vector_t<maybe<Member_Relation_e>>  relations;
            Vector_t<maybe<Member_Suit_Type_e>> suit_types;
            Vector_t<maybe<Member_Vitality_e>>  vitalities;

        public:
            Save_State(const some<Quest_t*> quest);
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();

        public:
            some<V::Object_t*>                                  Object();

            V::Variable_tt<Int_t>&                              Limit();

            V::Variable_tt<Bool_t>&                             Do_Auto_Suits();
            V::Variable_tt<Bool_t>&                             Do_Auto_Immobile_Suit();
            V::Variable_tt<Bool_t>&                             Do_Fill_Suits();

            V::Variable_tt<Bool_t>&                             Has_Untouchable_Invulnerables();

            V::Variable_tt<String_t>&                           Default_Combat_Style();
            V::Variable_tt<String_t>&                           Default_Relation();
            V::Variable_tt<String_t>&                           Default_Suit_Type();
            V::Variable_tt<String_t>&                           Default_Vitality();

            V::Variable_tt<String_t>&                           Member_Suit_Fill_Type();
            V::Variable_tt<String_t>&                           Sort_Type();

            V::Variable_tt<Vector_t<maybe<Actor_t*>>>&          Actors();
            V::Variable_tt<Vector_t<maybe<Actor_Base_t*>>>&     Original_Bases();

            V::Variable_tt<Vector_t<Bool_t>>&                   Is_Banished_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&                   Is_Clone_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&                   Is_Immobile_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&                   Is_Mannequin_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&                   Is_Paralyzed_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&                   Is_Reanimated_Flags();
            V::Variable_tt<Vector_t<Bool_t>>&                   Is_Thrall_Flags();

            V::Variable_tt<Vector_t<String_t>>&                 Names();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Packs();
            V::Variable_tt<Vector_t<maybe<Combat_Style_t*>>>&   Combat_Styles();
            V::Variable_tt<Vector_t<maybe<Spell_t*>>>&          Ghost_Abilities();
            V::Variable_tt<Vector_t<maybe<Voice_Type_t*>>>&     Voice_Types();

            V::Variable_tt<Vector_t<maybe<Outfit_t*>>>&         Default_Outfits();
            V::Variable_tt<Vector_t<maybe<Outfit_t*>>>&         Vanilla_Outfits();

            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Backup_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Default_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Follower_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Immobile_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Member_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Settler_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Thrall_Suits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Vanilla_Suits();

            V::Variable_tt<Vector_t<Float_t>>&                  Alphas();
            V::Variable_tt<Vector_t<Int_t>>&                    Ratings();
            V::Variable_tt<Vector_t<String_t>>&                 Relations();
            V::Variable_tt<Vector_t<String_t>>&                 Suit_Types();
            V::Variable_tt<Vector_t<String_t>>&                 Vitalities();

        public:
            void    Read();
            void    Write();
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
        const some<Quest_t*>                quest;
        Save_State                          save_state;

        Vector_t<maybe<Actor_Base_t*>>      custom_bases;
        Vector_t<maybe<Script_t*>>          scripts;

        const Vector_t<some<Spell_t*>>      vanilla_ghost_abilities;

    public:
        Members_t(some<Quest_t*> quest, Bool_t is_new_game);
        Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update);
        Members_t(const Members_t& other)                                           = delete;
        Members_t(Members_t&& other) noexcept                                       = delete;
        Members_t& operator =(const Members_t& other)                               = delete;
        Members_t& operator =(Members_t&& other) noexcept                           = delete;
        ~Members_t();

    public:
        void    Before_Save();
        void    After_Save();

    public:
        Main_t& Main();

        Bool_t  Has_Untouchable_Invulnerables();
        void    Has_Untouchable_Invulnerables(Bool_t value);

    public:
        Bool_t              Has_Alias(Member_ID_t member_id);
        Bool_t              Has_Alias(Alias_ID_t alias_id);
        Bool_t              Has_Member(some<Member_ID_t> member_id);
        Bool_t              Has_Member(some<Actor_t*> actor);

        maybe<Member_ID_t>  Used_Member_ID(some<Actor_t*> actor);
        maybe<Member_ID_t>  Unused_Member_ID();

        maybe<Member_ID_t>  Add_Member(some<Actor_t*> actor);
        maybe<Member_ID_t>  Add_Member(some<Actor_Base_t*> base);
        maybe<Member_ID_t>  Add_Member_Clone(some<Actor_t*> actor);
        Bool_t              Remove_Member(Member_ID_t member_id);

        size_t              Member_Count();

        void                Validate();

    public:
        some<Alias_Reference_t*>    Alias_Reference(Member_ID_t valid_member_id);
        some<Actor_t*>              Actor(some<Member_ID_t> valid_member_id);
        some<Actor_Base_t*>         Original_Base(Member_ID_t valid_member_id);
        some<Actor_Base_t*>         Custom_Base(Member_ID_t valid_member_id);
        some<Script_t*>             Script(Member_ID_t valid_member_id);
        void                        Update_AI(some<Member_ID_t> valid_member_id, some<Member_Update_AI_e> update_ai);

        Bool_t                      Is_Banished(Member_ID_t valid_member_id);
        void                        Is_Banished(Member_ID_t valid_member_id, Bool_t value);

        Bool_t                      Is_Clone(Member_ID_t valid_member_id);
        void                        Is_Clone(Member_ID_t valid_member_id, Bool_t value);

        Bool_t                      Is_Immobile(Member_ID_t valid_member_id);
        void                        Is_Immobile(Member_ID_t valid_member_id, Bool_t value);

        Bool_t                      Is_Mannequin(Member_ID_t valid_member_id);
        void                        Is_Mannequin(Member_ID_t valid_member_id, Bool_t value);

        Bool_t                      Is_Paralyzed(Member_ID_t valid_member_id);
        void                        Is_Paralyzed(Member_ID_t valid_member_id, Bool_t value);

        Bool_t                      Is_Reanimated(Member_ID_t valid_member_id);
        void                        Is_Reanimated(Member_ID_t valid_member_id, Bool_t value);

        Bool_t                      Is_Thrall(Member_ID_t valid_member_id);
        void                        Is_Thrall(Member_ID_t valid_member_id, Bool_t value);

        String_t                    Name(Member_ID_t valid_member_id);
        void                        Name(Member_ID_t valid_member_id, String_t name);

        maybe<Combat_Style_t*>      Combat_Style(Member_ID_t valid_member_id);
        void                        Combat_Style(Member_ID_t valid_member_id, maybe<Combat_Style_t*> combat_style);
        void                        Combat_Style(Member_ID_t valid_member_id, Member_Combat_Style_e combat_style);

        maybe<Spell_t*>             Ghost_Ability(Member_ID_t valid_member_id);
        void                        Ghost_Ability(Member_ID_t valid_member_id, maybe<Spell_t*> ghost_ability);

        some<Voice_Type_t*>         Voice_Type(Member_ID_t valid_member_id);
        void                        Voice_Type(Member_ID_t valid_member_id, maybe<Voice_Type_t*> voice_type);

        maybe<Member_Alpha_t>       Alpha(Member_ID_t valid_member_id);
        void                        Alpha(Member_ID_t valid_member_id, maybe<Member_Alpha_t> alpha);

        maybe<Member_Rating_t>      Rating(Member_ID_t valid_member_id);
        void                        Rating(Member_ID_t valid_member_id, maybe<Member_Rating_t> rating);

        some<Member_Relation_e>     Relation(Member_ID_t valid_member_id);
        void                        Relation(Member_ID_t valid_member_id, maybe<Member_Relation_e> relation);

        maybe<Member_Suit_Type_e>   Suit_Type(Member_ID_t valid_member_id);
        void                        Suit_Type(Member_ID_t valid_member_id, maybe<Member_Suit_Type_e> suit_type);

        some<Member_Vitality_e>     Vitality(Member_ID_t valid_member_id);
        void                        Vitality(Member_ID_t valid_member_id, maybe<Member_Vitality_e> vitality);
        Bool_t                      Is_Mortal(Member_ID_t valid_member_id);
        void                        Is_Mortal(Member_ID_t valid_member_id, Bool_t value);
        Bool_t                      Is_Protected(Member_ID_t valid_member_id);
        void                        Is_Protected(Member_ID_t valid_member_id, Bool_t value);
        Bool_t                      Is_Essential(Member_ID_t valid_member_id);
        void                        Is_Essential(Member_ID_t valid_member_id, Bool_t value);
        Bool_t                      Is_Invulnerable(Member_ID_t valid_member_id);
        void                        Is_Invulnerable(Member_ID_t valid_member_id, Bool_t value);

    public:
        // part of this functionality should probably go on main
        Bool_t                      Is_Enabled(Member_ID_t valid_member_id);
        Bool_t                      Is_Untouchable(Member_ID_t valid_member_id);
        Bool_t                      Has_AI(Member_ID_t valid_member_id);

        maybe<Member_Suit_t*>       Suit(Member_ID_t valid_member_id);

        void                        Tokenize(some<Member_ID_t> valid_member_id,
                                             some<Bound_Object_t*> object,
                                             Container_Entry_Count_t count = 1);
        void                        Untokenize(some<Member_ID_t> valid_member_id,
                                               some<Bound_Object_t*> object);

        Bool_t                      Enforce(Member_ID_t member_id);

    public:
        void    Log(std::string indent = "");
    };

    /*
        Just some quick outfitting notes:
            We should use the owner faction on x_lists to with a custom faction indicating that the item is an outfit item.
            We can mark x_lists as outfit items and point to the default outfit that is on the base actor. then we won't need any blank armor.
    */

}}
