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
#include "party_member_suit_buffer.h"
#include "party_member_suit_type.h"
#include "party_member_vitality.h"
#include "percent.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Members_t
    {
    public:
        static constexpr size_t                                 MAX_MEMBERS                             = Consts_t::NPCP::Int::MAX_MEMBERS;

        static constexpr Bool_t                                 DEFAULT_DO_ALLOW_MENU_FOR_ALL_ACTORS    = true;

        static constexpr Bool_t                                 DEFAULT_DO_FORCE_CLONE_UNIQUES          = false;
        static constexpr Bool_t                                 DEFAULT_DO_FORCE_CLONE_GENERICS         = false;
        static constexpr Bool_t                                 DEFAULT_DO_FORCE_UNCLONE_UNIQUES        = false;
        static constexpr Bool_t                                 DEFAULT_DO_FORCE_UNCLONE_GENERICS       = false;

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
            Bool_t                          do_allow_menu_for_all_actors;

            Bool_t                          do_force_clone_uniques;
            Bool_t                          do_force_clone_generics;
            Bool_t                          do_force_unclone_uniques;
            Bool_t                          do_force_unclone_generics;

            Bool_t                          has_untouchable_invulnerables;
            
            Bool_t                          do_suits;
            Bool_t                          do_suits_strictly;
            Bool_t                          do_fill_suits_automatically;
            Bool_t                          do_unfill_suits_into_pack;
            Bool_t                          do_change_suits_automatically;

            maybe<Member_Limit_t>           limit;

            maybe<Member_Sort_Type_e>       sort_type;

            maybe<Member_Clone_Suit_Type_e> clone_suit_type;

            maybe<Percent_t>                fill_suit_aura_percent;
            maybe<Percent_t>                fill_suit_body_percent;
            maybe<Percent_t>                fill_suit_feet_percent;
            maybe<Percent_t>                fill_suit_finger_percent;
            maybe<Percent_t>                fill_suit_forearm_percent;
            maybe<Percent_t>                fill_suit_forehead_percent;
            maybe<Percent_t>                fill_suit_hands_percent;
            maybe<Percent_t>                fill_suit_head_percent;
            maybe<Percent_t>                fill_suit_neck_percent;

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
            void    Write(std::ofstream& file);
            void    Read(std::ifstream& file);
        };

        class State_t
        {
        public:
            Save_t                          save;

            Member_t                        members[MAX_MEMBERS];

            const Vector_t<some<Spell_t*>>  ghost_abilities;

        public:
            State_t();
            State_t(const State_t& other) = delete;
            State_t(State_t&& other) noexcept = delete;
            State_t& operator =(const State_t& other) = delete;
            State_t& operator =(State_t&& other) noexcept = delete;
            ~State_t();
        };

    public:
        static void     Register_Me(some<Virtual::Machine_t*> machine);

        static Party_t& Party();

    public:
        State_t state;

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
        State_t&    State();
        Save_t&     Save();

    public:
        Bool_t                          Do_Allow_Menu_For_All_Actors();
        void                            Do_Allow_Menu_For_All_Actors(Bool_t value);

        Bool_t                          Do_Force_Clone_Uniques();
        void                            Do_Force_Clone_Uniques(Bool_t value);
        Bool_t                          Do_Force_Clone_Generics();
        void                            Do_Force_Clone_Generics(Bool_t value);
        Bool_t                          Do_Force_Unclone_Uniques();
        void                            Do_Force_Unclone_Uniques(Bool_t value);
        Bool_t                          Do_Force_Unclone_Generics();
        void                            Do_Force_Unclone_Generics(Bool_t value);

        Bool_t                          Has_Untouchable_Invulnerables();
        void                            Has_Untouchable_Invulnerables(Bool_t value);

        Bool_t                          Do_Suits();
        void                            Do_Suits(Bool_t value);
        Bool_t                          Do_Suits_Strictly();
        void                            Do_Suits_Strictly(Bool_t value);
        Bool_t                          Do_Fill_Suits_Automatically();
        void                            Do_Fill_Suits_Automatically(Bool_t value);
        Bool_t                          Do_Unfill_Suits_Into_Pack();
        void                            Do_Unfill_Suits_Into_Pack(Bool_t value);
        Bool_t                          Do_Change_Suits_Automatically();
        void                            Do_Change_Suits_Automatically(Bool_t value);

        some<Member_Limit_t>            Limit();
        void                            Limit(maybe<Member_Limit_t> value);

        some<Member_Sort_Type_e>        Sort_Type();
        void                            Sort_Type(maybe<Member_Sort_Type_e> value);

        some<Member_Clone_Suit_Type_e>  Clone_Suit_Type();
        void                            Clone_Suit_Type(maybe<Member_Clone_Suit_Type_e> value);

        some<Percent_t>                 Fill_Suit_Aura_Percent();
        void                            Fill_Suit_Aura_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Body_Percent();
        void                            Fill_Suit_Body_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Feet_Percent();
        void                            Fill_Suit_Feet_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Finger_Percent();
        void                            Fill_Suit_Finger_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Forearm_Percent();
        void                            Fill_Suit_Forearm_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Forehead_Percent();
        void                            Fill_Suit_Forehead_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Hands_Percent();
        void                            Fill_Suit_Hands_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Head_Percent();
        void                            Fill_Suit_Head_Percent(maybe<Percent_t> value);
        some<Percent_t>                 Fill_Suit_Neck_Percent();
        void                            Fill_Suit_Neck_Percent(maybe<Percent_t> value);

        some<Member_Alpha_t>            Default_Alpha();
        void                            Default_Alpha(maybe<Member_Alpha_t> value);
        maybe<Member_Combat_Style_e>    Default_Combat_Style();
        void                            Default_Combat_Style(maybe<Member_Combat_Style_e> value);
        maybe<Member_Rating_t>          Default_Rating();
        void                            Default_Rating(maybe<Member_Rating_t> value);
        maybe<Member_Relation_e>        Default_Relation();
        void                            Default_Relation(maybe<Member_Relation_e> value);
        maybe<Member_Suit_Type_e>       Default_Suit_Type();
        void                            Default_Suit_Type(maybe<Member_Suit_Type_e> value);
        maybe<Member_Vitality_e>        Default_Vitality();
        void                            Default_Vitality(maybe<Member_Vitality_e> value);

    public:
        void                        Reset_Options();

        some<Quest_t*>              Quest();
        some<Alias_Reference_t*>    Alias(some<Member_ID_t> id);
        Member_t&                   Member(some<Member_ID_t> id);
        maybe<Member_t*>            Active_Member(some<Actor_t*> actor);
        maybe<Member_t*>            Inactive_Member();
        size_t                      Active_Member_Count();
        size_t                      Inactive_Member_Count();

        maybe<Member_ID_t>          Add(some<Actor_t*> actor);
        maybe<Member_ID_t>          Add(some<Actor_Base_t*> base);
        maybe<Member_ID_t>          Add_Clone(some<Actor_t*> actor);
        Bool_t                      Remove(some<Member_ID_t> id);
        Bool_t                      Remove(some<Actor_t*> actor);
    };

}}
