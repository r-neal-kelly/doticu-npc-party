/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <fstream>
#include <mutex>

#include "doticu_skylib/enum_script_type.h"

#include "consts.h"
#include "intrinsic.h"
#include "party.h"
#include "party_member.h"
#include "party_member_alpha.h"
#include "party_member_combat_style.h"
#include "party_member_flags.h"
#include "party_member_flags_has_suit.h"
#include "party_member_flags_only_playables.h"
#include "party_member_id.h"
#include "party_member_limit.h"
#include "party_member_rating.h"
#include "party_member_relation.h"
#include "party_member_sort_type.h"
#include "party_member_suit_fill_type.h"
#include "party_member_suit_type.h"
#include "party_member_vitality.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_Suitcase_t;

    class Members_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

    public:
        static constexpr size_t                                 MAX_MEMBERS                             = Consts_t::NPCP::Int::MAX_MEMBERS;

        static constexpr Member_Limit_t::value_type             DEFAULT_LIMIT                           = MAX_MEMBERS;

        static constexpr size_t                                 DEFAULT_FILL_SUIT_AURA_PROBABILITY      = 100;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_BODY_PROBABILITY      = 100;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_FEET_PROBABILITY      = 66;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_FINGER_PROBABILITY    = 66;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_FOREARM_PROBABILITY   = 50;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_FOREHEAD_PROBABILITY  = 50;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_HANDS_PROBABILITY     = 66;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_HEAD_PROBABILITY      = 33;
        static constexpr size_t                                 DEFAULT_FILL_SUIT_NECK_PROBABILITY      = 50;

        static constexpr Bool_t                                 DEFAULT_DO_CHANGE_SUITS_AUTOMATICALLY   = false;
        static constexpr Bool_t                                 DEFAULT_DO_FILL_SUITS_AUTOMATICALLY     = true;
        static constexpr Bool_t                                 DEFAULT_DO_FILL_SUITS_STRICTLY          = false;
        static constexpr Bool_t                                 DEFAULT_DO_UNFILL_SUITS_TO_PACK         = false;

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
            const some<Quest_t*>                    quest;

        public:
            some<Member_Limit_t>                    limit;

            u8                                      fill_suit_aura_probability;
            u8                                      fill_suit_body_probability;
            u8                                      fill_suit_feet_probability;
            u8                                      fill_suit_finger_probability;
            u8                                      fill_suit_forearm_probability;
            u8                                      fill_suit_forehead_probability;
            u8                                      fill_suit_hands_probability;
            u8                                      fill_suit_head_probability;
            u8                                      fill_suit_neck_probability;

            Bool_t                                  do_change_suits_automatically;
            Bool_t                                  do_fill_suits_automatically;
            Bool_t                                  do_fill_suits_strictly;
            Bool_t                                  do_unfill_suits_to_pack;

            Bool_t                                  has_untouchable_invulnerables;

            maybe<Member_Combat_Style_e>            default_combat_style;
            maybe<Member_Relation_e>                default_relation;
            maybe<Member_Suit_Type_e>               default_suit_type;
            maybe<Member_Vitality_e>                default_vitality;

            some<Member_Suit_Fill_Type_e>           member_suit_fill_type;
            some<Member_Sort_Type_e>                sort_type;

        public:
            Vector_t<maybe<Actor_t*>>               actors;
            Vector_t<maybe<Actor_Base_t*>>          original_bases;

            Vector_t<Member_Flags_e>                flags;
            Vector_t<Member_Flags_Has_Suit_e>       flags_has_suit;
            Vector_t<Member_Flags_Only_Playables_e> flags_only_playables;

            Vector_t<String_t>                      names;

            Vector_t<maybe<Reference_t*>>           caches;
            Vector_t<maybe<Combat_Style_t*>>        combat_styles;
            Vector_t<maybe<Spell_t*>>               ghost_abilities;
            Vector_t<maybe<Outfit_t*>>              outfits;
            Vector_t<maybe<Reference_t*>>           packs;
            Vector_t<maybe<Member_Suitcase_t*>>     suitcases;
            Vector_t<maybe<Voice_Type_t*>>          voice_types;

            Vector_t<maybe<Member_Alpha_t>>         alphas;
            Vector_t<maybe<Member_Rating_t>>        ratings;
            Vector_t<maybe<Member_Relation_e>>      relations;
            Vector_t<maybe<Member_Suit_Type_e>>     suit_types;
            Vector_t<maybe<Member_Vitality_e>>      vitalities;

        public:
            Save_State(const some<Quest_t*> quest);
            Save_State(const Save_State& other)                 = delete;
            Save_State(Save_State&& other) noexcept             = delete;
            Save_State& operator =(const Save_State& other)     = delete;
            Save_State& operator =(Save_State&& other) noexcept = delete;
            ~Save_State();

        public:
            some<V::Object_t*>                                  Object();

        public:
            V::Variable_tt<Int_t>&                              Limit();

            V::Variable_tt<Int_t>&                              Fill_Suit_Aura_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Body_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Feet_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Finger_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Forearm_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Forehead_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Hands_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Head_Probability();
            V::Variable_tt<Int_t>&                              Fill_Suit_Neck_Probability();

            V::Variable_tt<Bool_t>&                             Do_Change_Suits_Automatically();
            V::Variable_tt<Bool_t>&                             Do_Fill_Suits_Automatically();
            V::Variable_tt<Bool_t>&                             Do_Fill_Suits_Strictly();
            V::Variable_tt<Bool_t>&                             Do_Unfill_Suits_To_Pack();

            V::Variable_tt<Bool_t>&                             Has_Untouchable_Invulnerables();

            V::Variable_tt<String_t>&                           Default_Combat_Style();
            V::Variable_tt<String_t>&                           Default_Relation();
            V::Variable_tt<String_t>&                           Default_Suit_Type();
            V::Variable_tt<String_t>&                           Default_Vitality();

            V::Variable_tt<String_t>&                           Member_Suit_Fill_Type();
            V::Variable_tt<String_t>&                           Sort_Type();

        public:
            V::Variable_tt<Vector_t<maybe<Actor_t*>>>&          Actors();
            V::Variable_tt<Vector_t<maybe<Actor_Base_t*>>>&     Original_Bases();

            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Is_Banished();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Is_Clone();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Is_Immobile();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Is_Mannequin();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Is_Reanimated();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Is_Sneak();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Is_Thrall();

            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Archer();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Civilized();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Combatant();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Coward();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Dangerous();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Eater();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Exterior();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Follower();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Guard();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Home();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Immobile();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Inn();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Interior();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Mage();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Mannequin();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Member();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Sandboxer();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Settlement();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Sitter();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Sleeper();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Thrall();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Has_Suit_Warrior();

            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Archer();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Civilized();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Combatant();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Coward();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Dangerous();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Eater();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Exterior();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Follower();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Guard();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Home();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Immobile();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Inn();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Interior();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Mage();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Mannequin();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Member();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Sandboxer();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Settlement();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Sitter();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Sleeper();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Thrall();
            V::Variable_tt<Vector_t<Bool_t>>&                   Flags_Only_Playables_Warrior();

            V::Variable_tt<Vector_t<String_t>>&                 Names();

            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Caches();
            V::Variable_tt<Vector_t<maybe<Combat_Style_t*>>>&   Combat_Styles();
            V::Variable_tt<Vector_t<maybe<Spell_t*>>>&          Ghost_Abilities();
            V::Variable_tt<Vector_t<maybe<Outfit_t*>>>&         Outfits();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Packs();
            V::Variable_tt<Vector_t<maybe<Reference_t*>>>&      Suitcases();
            V::Variable_tt<Vector_t<maybe<Voice_Type_t*>>>&     Voice_Types();

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

    public:
        const some<Quest_t*>            quest;
        Save_State                      save_state;

        Vector_t<std::mutex>            locks;
        Vector_t<maybe<Actor_Base_t*>>  custom_bases;

        const Vector_t<some<Spell_t*>>  vanilla_ghost_abilities;

    public:
        Members_t();
        Members_t(const Members_t& other)                                           = delete;
        Members_t(Members_t&& other) noexcept                                       = delete;
        Members_t& operator =(const Members_t& other)                               = delete;
        Members_t& operator =(Members_t&& other) noexcept                           = delete;
        ~Members_t();

    public:
        void    On_After_New_Game();
        void    On_Before_Save_Game(std::ofstream& file);
        void    On_After_Save_Game();
        void    On_Before_Load_Game();
        void    On_After_Load_Game(std::ifstream& file);
        void    On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update);
        void    On_Update();

    public:
        void    Before_Save();
        void    After_Save();
        void    Validate();

    public:
        Main_t& Main();

    public:
        some<Member_Limit_t>        Limit();
        void                        Limit(some<Member_Limit_t> value);

        u8                          Fill_Suit_Aura_Probability();
        void                        Fill_Suit_Aura_Probability(u8 value);
        u8                          Fill_Suit_Body_Probability();
        void                        Fill_Suit_Body_Probability(u8 value);
        u8                          Fill_Suit_Feet_Probability();
        void                        Fill_Suit_Feet_Probability(u8 value);
        u8                          Fill_Suit_Finger_Probability();
        void                        Fill_Suit_Finger_Probability(u8 value);
        u8                          Fill_Suit_Forearm_Probability();
        void                        Fill_Suit_Forearm_Probability(u8 value);
        u8                          Fill_Suit_Forehead_Probability();
        void                        Fill_Suit_Forehead_Probability(u8 value);
        u8                          Fill_Suit_Hands_Probability();
        void                        Fill_Suit_Hands_Probability(u8 value);
        u8                          Fill_Suit_Head_Probability();
        void                        Fill_Suit_Head_Probability(u8 value);
        u8                          Fill_Suit_Neck_Probability();
        void                        Fill_Suit_Neck_Probability(u8 value);

        void                        Reset_Fill_Suit_Probabilities();

        Bool_t                      Do_Change_Suits_Automatically();
        void                        Do_Change_Suits_Automatically(Bool_t value);

        Bool_t                      Do_Fill_Suits_Automatically();
        void                        Do_Fill_Suits_Automatically(Bool_t value);

        Bool_t                      Do_Fill_Suits_Strictly();
        void                        Do_Fill_Suits_Strictly(Bool_t value);

        Bool_t                      Do_Unfill_Suits_To_Pack();
        void                        Do_Unfill_Suits_To_Pack(Bool_t value);

        Bool_t                      Has_Untouchable_Invulnerables();
        void                        Has_Untouchable_Invulnerables(Bool_t value);

        maybe<Member_Suit_Type_e>   Default_Suit_Type();
        void                        Default_Suit_Type(maybe<Member_Suit_Type_e> suit_type);

        some<Member_Sort_Type_e>    Sort_Type();
        void                        Sort_Type(some<Member_Sort_Type_e> value);

    public:
        std::mutex&                 Lock(some<Member_ID_t> member_id);
        some<Alias_Reference_t*>    Alias_Reference(some<Member_ID_t> member_id);

        Bool_t                      Has_Alias(some<Member_ID_t> member_id);
        Bool_t                      Has_Alias(Alias_ID_t alias_id);
        Bool_t                      Has_Member(some<Member_ID_t> member_id);
        Bool_t                      Has_Member(some<Actor_t*> actor);

        maybe<Member_ID_t>          Used_Member_ID(some<Actor_t*> actor);
        maybe<Member_ID_t>          Unused_Member_ID();

        maybe<Member_ID_t>          Add_Member(some<Actor_t*> actor);
        maybe<Member_ID_t>          Add_Member(some<Actor_Base_t*> base);
        maybe<Member_ID_t>          Add_Member_Clone(some<Actor_t*> actor);
        Bool_t                      Remove_Member(some<Member_ID_t> member_id);

        size_t                      Member_Count();

    public:
        void    Log(std::string indent = "");
    };

}}
