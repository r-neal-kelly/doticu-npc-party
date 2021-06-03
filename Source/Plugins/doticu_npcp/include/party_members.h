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
#include "party_member_alpha.h"
#include "party_member_clone_suit_type.h"
#include "party_member_combat_style.h"
#include "party_member_flags.h"
#include "party_member_flags_has_suit.h"
#include "party_member_flags_only_playables.h"
#include "party_member_id.h"
#include "party_member_limit.h"
#include "party_member_rating.h"
#include "party_member_relation.h"
#include "party_member_sort_type.h"
#include "party_member_suit_type.h"
#include "party_member_vitality.h"
#include "percent.h"

namespace doticu_skylib { namespace doticu_npcp {

    /*
        Okay, so we need to save info info for each actor and its base to be reconstituted upon game-load.
        Essentially, the form ids may no longer match to our member if the actor is removed from the game,
        or even its base actor. We need to at a minimum save each base and actor. However, we may want to store yet
        a third item, that being the indentifiable static base, which will ensure that our base actor is actually what
        we think it is. The identifiable static base essentially only comes into play when the actor base is dynamic.
        It is the first static base that can be used to identify that the dynamic base matches up to an existing
        mod and an existing base in that mod. We may actually be able to just save the indentifiable static base,
        because we can just read the actual base from the actor itself. However, we wouldn't be able to regen the actor if
        it is the only thing missing. I think we should have all three.

        Also, we may want to do the actors and all of their data dynamically sized, so that it's easy to add members in the future.
        (probably never going to happen, but it would allow us to expand if we really wanted to.)

        However, it would not be too difficult to do that in a future update when we actually need it. why add the complication now?
    */

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

        static constexpr Bool_t                                 DEFAULT_HAS_UNTOUCHABLE_INVULNERABLES   = false;

        static constexpr Bool_t                                 DEFAULT_DO_SUITS                        = true;
        static constexpr Bool_t                                 DEFAULT_DO_SUITS_STRICTLY               = false;
        static constexpr Bool_t                                 DEFAULT_DO_FILL_SUITS_AUTOMATICALLY     = true;
        static constexpr Bool_t                                 DEFAULT_DO_UNFILL_SUITS_INTO_PACK       = false;
        static constexpr Bool_t                                 DEFAULT_DO_CHANGE_SUITS_AUTOMATICALLY   = false;

        static constexpr Member_Limit_t::value_type             DEFAULT_LIMIT                           = MAX_MEMBERS;
        static constexpr Member_Sort_Type_e::value_type         DEFAULT_SORT_TYPE                       = Member_Sort_Type_e::NAME;
        static constexpr Member_Clone_Suit_Type_e::value_type   DEFAULT_CLONE_SUIT_TYPE                 = Member_Clone_Suit_Type_e::REFERENCE;

        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_AURA_PERCENT          = 100;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_BODY_PERCENT          = 100;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_FEET_PERCENT          = 66;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_FINGER_PERCENT        = 66;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_FOREARM_PERCENT       = 50;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_FOREHEAD_PERCENT      = 50;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_HANDS_PERCENT         = 66;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_HEAD_PERCENT          = 33;
        static constexpr Percent_t::value_type                  DEFAULT_FILL_SUIT_NECK_PERCENT          = 50;

        static constexpr Member_Alpha_t::value_type             DEFAULT_ALPHA                           = Member_Alpha_t::_MAX_;
        static constexpr Member_Combat_Style_e::value_type      DEFAULT_COMBAT_STYLE                    = Member_Combat_Style_e::_NONE_;
        static constexpr Member_Rating_t::value_type            DEFAULT_RATING                          = Member_Rating_t::_NONE_;
        static constexpr Member_Relation_e::value_type          DEFAULT_RELATION                        = Member_Relation_e::_NONE_;
        static constexpr Member_Suit_Type_e::value_type         DEFAULT_SUIT_TYPE                       = Member_Suit_Type_e::MEMBER;
        static constexpr Member_Vitality_e::value_type          DEFAULT_VITALITY                        = Member_Vitality_e::_NONE_;

    public:
        class Save_t
        {
        public:
            Bool_t                          has_untouchable_invulnerables;
            
            Bool_t                          do_suits;
            Bool_t                          do_suits_strictly;
            Bool_t                          do_fill_suits_automatically;
            Bool_t                          do_unfill_suits_into_pack;
            Bool_t                          do_change_suits_automatically;

            some<Member_Limit_t>            limit;
            some<Member_Sort_Type_e>        sort_type;
            some<Member_Clone_Suit_Type_e>  clone_suit_type;

            some<Percent_t>                 fill_suit_aura_percent;
            some<Percent_t>                 fill_suit_body_percent;
            some<Percent_t>                 fill_suit_feet_percent;
            some<Percent_t>                 fill_suit_finger_percent;
            some<Percent_t>                 fill_suit_forearm_percent;
            some<Percent_t>                 fill_suit_forehead_percent;
            some<Percent_t>                 fill_suit_hands_percent;
            some<Percent_t>                 fill_suit_head_percent;
            some<Percent_t>                 fill_suit_neck_percent;

            maybe<Member_Alpha_t>           default_alpha;
            maybe<Member_Combat_Style_e>    default_combat_style;
            maybe<Member_Rating_t>          default_rating;
            maybe<Member_Relation_e>        default_relation;
            maybe<Member_Suit_Type_e>       default_suit_type;
            maybe<Member_Vitality_e>        default_vitality;

        public:
            Save_t();
            Save_t(const Save_t& other) = delete;
            Save_t(Save_t&& other) noexcept = delete;
            Save_t& operator =(const Save_t& other) = delete;
            Save_t& operator =(Save_t&& other) noexcept = delete;
            ~Save_t();

        public:
            void    Read(std::ifstream& file);
            void    Write(std::ofstream& file);
        };

        class State_t
        {
        public:
            Save_t      save;

            Member_t    members[MAX_MEMBERS];

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        static void Register_Me(some<Virtual::Machine_t*> machine);

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
        Vector_t<std::mutex>            locks;
        const Vector_t<some<Spell_t*>>  vanilla_ghost_abilities;

    public:
        Members_t();
        Members_t(const Members_t& other) = delete;
        Members_t(Members_t&& other) noexcept = delete;
        Members_t& operator =(const Members_t& other) = delete;
        Members_t& operator =(Members_t&& other) noexcept = delete;
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

        static some<Reference_t*>   Suit_Buffer(); // we'll be using Consts_t::NPCP::Reference::Suit_Buffer(), needs to be locked.

    public:
        void    Log(std::string indent = "");
    };

}}
