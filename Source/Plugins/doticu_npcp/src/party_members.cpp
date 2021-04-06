/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/combat_style.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_actor_bases.h"
#include "doticu_skylib/const_factions.h"
#include "doticu_skylib/const_spells.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/global.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/script.h"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/voice_type.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "party_members.h"
#include "party_member_suit.h"

namespace doticu_npcp { namespace Party {

    Members_t::Save_State::Save_State(const some<Quest_t*> quest) :
        quest(quest),

        limit(MAX_MEMBERS),

        do_auto_suits(DEFAULT_DO_AUTO_SUITS),
        do_auto_immobile_suit(DEFAULT_DO_AUTO_IMMOBILE_SUIT),
        do_fill_suits(DEFAULT_DO_FILL_SUITS),

        has_untouchable_invulnerables(DEFAULT_HAS_UNTOUCHABLE_INVULNERABLES),

        default_combat_style(DEFAULT_COMBAT_STYLE),
        default_relation(DEFAULT_RELATION),
        default_suit_type(DEFAULT_SUIT_TYPE),
        default_vitality(DEFAULT_VITALITY),

        member_suit_fill_type(DEFAULT_MEMBER_SUIT_FILL_TYPE),
        sort_type(DEFAULT_SORT_TYPE),

        actors(Vector_t<maybe<Actor_t*>>(MAX_MEMBERS, none<Actor_t*>())),
        original_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS, none<Actor_Base_t*>())),

        flags(Vector_t<Member_Flags_e>(MAX_MEMBERS, 0)),

        names(Vector_t<String_t>(MAX_MEMBERS, "")),
        packs(Vector_t<maybe<Reference_t*>>(MAX_MEMBERS, none<Reference_t*>())),
        combat_styles(Vector_t<maybe<Combat_Style_t*>>(MAX_MEMBERS, none<Combat_Style_t*>())),
        ghost_abilities(Vector_t<maybe<Spell_t*>>(MAX_MEMBERS, none<Spell_t*>())),
        voice_types(Vector_t<maybe<Voice_Type_t*>>(MAX_MEMBERS, none<Voice_Type_t*>())),

        default_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS, none<Outfit_t*>())),
        vanilla_outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS, none<Outfit_t*>())),

        backup_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),
        default_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),
        follower_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),
        immobile_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),
        member_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),
        settler_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),
        thrall_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),
        vanilla_suits(Vector_t<maybe<Member_Suit_t*>>(MAX_MEMBERS, none<Member_Suit_t*>())),

        alphas(Vector_t<maybe<Member_Alpha_t>>(MAX_MEMBERS, DEFAULT_ALPHA)),
        ratings(Vector_t<maybe<Member_Rating_t>>(MAX_MEMBERS, DEFAULT_RATING)),
        relations(Vector_t<maybe<Member_Relation_e>>(MAX_MEMBERS, DEFAULT_RELATION)),
        suit_types(Vector_t<maybe<Member_Suit_Type_e>>(MAX_MEMBERS, DEFAULT_SUIT_TYPE)),
        vitalities(Vector_t<maybe<Member_Vitality_e>>(MAX_MEMBERS, DEFAULT_VITALITY))
    {
    }

    Members_t::Save_State::~Save_State()
    {
    }

    some<V::Object_t*> Members_t::Save_State::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->quest());
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Limit()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "limit");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Auto_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_auto_suits");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Auto_Immobile_Suit()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_auto_immobile_suit");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Fill_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_fill_suits");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Has_Untouchable_Invulnerables()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "has_untouchable_invulnerables");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Combat_Style()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_combat_style");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Relation()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_relation");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Suit_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_suit_type");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Vitality()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_vitality");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Member_Suit_Fill_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "member_suit_fill_type");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Sort_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "sort_type");
    }

    V::Variable_tt<Vector_t<maybe<Actor_t*>>>& Members_t::Save_State::Actors()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Actor_t*>>, "actors");
    }

    V::Variable_tt<Vector_t<maybe<Actor_Base_t*>>>& Members_t::Save_State::Original_Bases()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Actor_Base_t*>>, "original_bases");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Banished_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_banished_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Clone_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_clone_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Immobile_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_immobile_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Mannequin_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_mannequin_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Paralyzed_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_paralyzed_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Reanimated_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_reanimated_flags");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Is_Thrall_Flags()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "is_thrall_flags");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Names()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "names");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Packs()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "packs");
    }

    V::Variable_tt<Vector_t<maybe<Combat_Style_t*>>>& Members_t::Save_State::Combat_Styles()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Combat_Style_t*>>, "combat_styles");
    }

    V::Variable_tt<Vector_t<maybe<Spell_t*>>>& Members_t::Save_State::Ghost_Abilities()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Spell_t*>>, "ghost_abilities");
    }

    V::Variable_tt<Vector_t<maybe<Voice_Type_t*>>>& Members_t::Save_State::Voice_Types()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Voice_Type_t*>>, "voice_types");
    }

    V::Variable_tt<Vector_t<maybe<Outfit_t*>>>& Members_t::Save_State::Default_Outfits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Outfit_t*>>, "default_outfits");
    }

    V::Variable_tt<Vector_t<maybe<Outfit_t*>>>& Members_t::Save_State::Vanilla_Outfits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Outfit_t*>>, "vanilla_outfits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Backup_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "backup_suits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Default_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "default_suits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Follower_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "follower_suits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Immobile_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "immobile_suits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Member_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "member_suits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Settler_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "settler_suits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Thrall_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "thrall_suits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Vanilla_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "vanilla_suits");
    }

    V::Variable_tt<Vector_t<Float_t>>& Members_t::Save_State::Alphas()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Float_t>, "alphas");
    }

    V::Variable_tt<Vector_t<Int_t>>& Members_t::Save_State::Ratings()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "ratings");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Relations()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "relations");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Suit_Types()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "suit_types");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Vitalities()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "vitalities");
    }

    void Members_t::Save_State::Read()
    {
        this->limit = Limit();

        this->do_auto_suits = Do_Auto_Suits();
        this->do_auto_immobile_suit = Do_Auto_Immobile_Suit();
        this->do_fill_suits = Do_Fill_Suits();

        this->has_untouchable_invulnerables = Has_Untouchable_Invulnerables();

        this->default_combat_style = Default_Combat_Style().As<String_t>();
        this->default_relation = Default_Relation().As<String_t>();
        this->default_suit_type = Default_Suit_Type().As<String_t>();
        this->default_vitality = Default_Vitality().As<String_t>();

        this->member_suit_fill_type = Member_Suit_Fill_Type().As<String_t>();
        this->sort_type = Sort_Type().As<String_t>();

        this->actors = Actors();
        this->original_bases = Original_Bases();

        Vector_t<Bool_t> is_banished_flags = Is_Banished_Flags();
        Vector_t<Bool_t> is_clone_flags = Is_Clone_Flags();
        Vector_t<Bool_t> is_immobile_flags = Is_Immobile_Flags();
        Vector_t<Bool_t> is_mannequin_flags = Is_Mannequin_Flags();
        Vector_t<Bool_t> is_paralyzed_flags = Is_Paralyzed_Flags();
        Vector_t<Bool_t> is_reanimated_flags = Is_Reanimated_Flags();
        Vector_t<Bool_t> is_thrall_flags = Is_Thrall_Flags();

        this->names = Names();
        this->packs = Packs();
        this->combat_styles = Combat_Styles();
        this->ghost_abilities = Ghost_Abilities();
        this->voice_types = Voice_Types();

        this->default_outfits = Default_Outfits();
        this->vanilla_outfits = Vanilla_Outfits();

        this->backup_suits = Backup_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();
        this->default_suits = Default_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();
        this->follower_suits = Follower_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();
        this->immobile_suits = Immobile_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();
        this->member_suits = Member_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();
        this->settler_suits = Settler_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();
        this->thrall_suits = Thrall_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();
        this->vanilla_suits = Vanilla_Suits().As<Vector_t<maybe<Member_Suit_t*>>>();

        Vector_t<Float_t> alphas = Alphas();
        Vector_t<Int_t> ratings = Ratings();
        Vector_t<String_t> relations = Relations();
        Vector_t<String_t> suit_types = Suit_Types();
        Vector_t<String_t> vitalities = Vitalities();

        this->actors.resize(MAX_MEMBERS);
        this->original_bases.resize(MAX_MEMBERS);

        is_banished_flags.resize(MAX_MEMBERS);
        is_clone_flags.resize(MAX_MEMBERS);
        is_immobile_flags.resize(MAX_MEMBERS);
        is_mannequin_flags.resize(MAX_MEMBERS);
        is_paralyzed_flags.resize(MAX_MEMBERS);
        is_reanimated_flags.resize(MAX_MEMBERS);
        is_thrall_flags.resize(MAX_MEMBERS);

        this->names.resize(MAX_MEMBERS);
        this->packs.resize(MAX_MEMBERS);
        this->combat_styles.resize(MAX_MEMBERS);
        this->ghost_abilities.resize(MAX_MEMBERS);
        this->voice_types.resize(MAX_MEMBERS);

        this->default_outfits.resize(MAX_MEMBERS);
        this->vanilla_outfits.resize(MAX_MEMBERS);

        this->backup_suits.resize(MAX_MEMBERS);
        this->default_suits.resize(MAX_MEMBERS);
        this->follower_suits.resize(MAX_MEMBERS);
        this->immobile_suits.resize(MAX_MEMBERS);
        this->member_suits.resize(MAX_MEMBERS);
        this->settler_suits.resize(MAX_MEMBERS);
        this->thrall_suits.resize(MAX_MEMBERS);
        this->vanilla_suits.resize(MAX_MEMBERS);

        alphas.resize(MAX_MEMBERS, DEFAULT_ALPHA);
        ratings.resize(MAX_MEMBERS, DEFAULT_RATING);
        relations.resize(MAX_MEMBERS);
        suit_types.resize(MAX_MEMBERS);
        vitalities.resize(MAX_MEMBERS);

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            Member_Flags_e& flags = this->flags[idx];
            flags.Is_Flagged(Member_Flags_e::IS_BANISHED, is_banished_flags[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_CLONE, is_clone_flags[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE, is_immobile_flags[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN, is_mannequin_flags[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_PARALYZED, is_paralyzed_flags[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_REANIMATED, is_reanimated_flags[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_THRALL, is_thrall_flags[idx]);

            this->alphas[idx] = alphas[idx];
            this->ratings[idx] = ratings[idx];
            this->relations[idx] = relations[idx];
            this->suit_types[idx] = suit_types[idx];
            this->vitalities[idx] = vitalities[idx];
        }
    }

    void Members_t::Save_State::Write()
    {
        Vector_t<Bool_t> is_banished_flags(MAX_MEMBERS, false);
        Vector_t<Bool_t> is_clone_flags(MAX_MEMBERS, false);
        Vector_t<Bool_t> is_immobile_flags(MAX_MEMBERS, false);
        Vector_t<Bool_t> is_mannequin_flags(MAX_MEMBERS, false);
        Vector_t<Bool_t> is_paralyzed_flags(MAX_MEMBERS, false);
        Vector_t<Bool_t> is_reanimated_flags(MAX_MEMBERS, false);
        Vector_t<Bool_t> is_thrall_flags(MAX_MEMBERS, false);

        Vector_t<Float_t> alphas(MAX_MEMBERS, DEFAULT_ALPHA);
        Vector_t<Int_t> ratings(MAX_MEMBERS, DEFAULT_RATING);
        Vector_t<String_t> relations(MAX_MEMBERS, "");
        Vector_t<String_t> suit_types(MAX_MEMBERS, "");
        Vector_t<String_t> vitalities(MAX_MEMBERS, "");

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (this->actors[idx]) {
                Member_Flags_e flags = this->flags[idx];
                is_banished_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_BANISHED);
                is_clone_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_CLONE);
                is_immobile_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE);
                is_mannequin_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN);
                is_paralyzed_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_PARALYZED);
                is_reanimated_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_REANIMATED);
                is_thrall_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_THRALL);

                alphas[idx] = this->alphas[idx]();
                ratings[idx] = this->ratings[idx]();
                relations[idx] = this->relations[idx]().As_String();
                suit_types[idx] = this->suit_types[idx]().As_String();
                vitalities[idx] = this->vitalities[idx]().As_String();
            }
        }

        Limit() = this->limit;

        Do_Auto_Suits() = this->do_auto_suits;
        Do_Auto_Immobile_Suit() = this->do_auto_immobile_suit;
        Do_Fill_Suits() = this->do_fill_suits;

        Has_Untouchable_Invulnerables() = this->has_untouchable_invulnerables;

        Default_Combat_Style() = this->default_combat_style().As_String();
        Default_Relation() = this->default_relation().As_String();
        Default_Suit_Type() = this->default_suit_type().As_String();
        Default_Vitality() = this->default_vitality().As_String();

        Member_Suit_Fill_Type() = this->member_suit_fill_type().As_String();
        Sort_Type() = this->sort_type().As_String();

        Actors() = this->actors;
        Original_Bases() = this->original_bases;

        Is_Banished_Flags() = is_banished_flags;
        Is_Clone_Flags() = is_clone_flags;
        Is_Immobile_Flags() = is_immobile_flags;
        Is_Mannequin_Flags() = is_mannequin_flags;
        Is_Paralyzed_Flags() = is_paralyzed_flags;
        Is_Reanimated_Flags() = is_reanimated_flags;
        Is_Thrall_Flags() = is_thrall_flags;

        Names() = this->names;
        Packs() = this->packs;
        Combat_Styles() = this->combat_styles;
        Ghost_Abilities() = this->ghost_abilities;
        Voice_Types() = this->voice_types;

        Default_Outfits() = this->default_outfits;
        Vanilla_Outfits() = this->vanilla_outfits;

        Backup_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->backup_suits);
        Default_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->default_suits);
        Follower_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->follower_suits);
        Immobile_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->immobile_suits);
        Member_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->member_suits);
        Settler_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->settler_suits);
        Thrall_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->thrall_suits);
        Vanilla_Suits() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->vanilla_suits);

        Alphas() = alphas;
        Ratings() = ratings;
        Relations() = relations;
        Suit_Types() = suit_types;
        Vitalities() = vitalities;
    }

    String_t Members_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_party_members");
    }

    some<V::Class_t*> Members_t::Class()
    {
        DEFINE_CLASS();
    }

    void Members_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        String_t class_name = Class_Name();

        #define STATIC(STATIC_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, STATIC_, ...)  \
        SKYLIB_M                                                                    \
            BIND_STATIC(machine, class_name, STATIC_NAME_, WAITS_FOR_FRAME_,        \
                        RETURN_TYPE_, STATIC_, __VA_ARGS__);                        \
        SKYLIB_W

        #undef STATIC

        #define METHOD(METHOD_NAME_, WAITS_FOR_FRAME_, RETURN_TYPE_, METHOD_, ...)      \
        SKYLIB_M                                                                        \
            BIND_METHOD(machine, class_name, Members_t, METHOD_NAME_, WAITS_FOR_FRAME_, \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                            \
        SKYLIB_W

        #undef METHOD
    }

    Bool_t Members_t::Do_Allow_Menu_For_All_Actors()
    {
        return Consts_t::NPCP::Global::Do_Allow_Menu_For_All_Actors()->Bool();
    }

    void Members_t::Do_Allow_Menu_For_All_Actors(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Allow_Menu_For_All_Actors()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Clone_Uniques()
    {
        return Consts_t::NPCP::Global::Do_Force_Clone_Uniques()->Bool();
    }

    void Members_t::Do_Force_Clone_Uniques(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Clone_Uniques()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Clone_Generics()
    {
        return Consts_t::NPCP::Global::Do_Force_Clone_Generics()->Bool();
    }

    void Members_t::Do_Force_Clone_Generics(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Clone_Generics()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Unclone_Uniques()
    {
        return Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()->Bool();
    }

    void Members_t::Do_Force_Unclone_Uniques(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()->Bool(value);
    }

    Bool_t Members_t::Do_Force_Unclone_Generics()
    {
        return Consts_t::NPCP::Global::Do_Force_Unclone_Generics()->Bool();
    }

    void Members_t::Do_Force_Unclone_Generics(Bool_t value)
    {
        Consts_t::NPCP::Global::Do_Force_Unclone_Generics()->Bool(value);
    }

    Int_t Members_t::Fill_Outfit_Body_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Body_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Body_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Body_Percent()->Percent(100 - value);
    }

    Int_t Members_t::Fill_Outfit_Feet_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Feet_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Feet_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Feet_Percent()->Percent(100 - value);
    }

    Int_t Members_t::Fill_Outfit_Hands_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Hands_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Hands_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Hands_Percent()->Percent(100 - value);
    }

    Int_t Members_t::Fill_Outfit_Head_Percent()
    {
        return 100 - Consts_t::NPCP::Global::Empty_Outfit_Head_Percent()->Percent();
    }

    void Members_t::Fill_Outfit_Head_Percent(Int_t value)
    {
        Consts_t::NPCP::Global::Empty_Outfit_Head_Percent()->Percent(100 - value);
    }

    Members_t::Members_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest),
        save_state(quest),

        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        scripts(Vector_t<maybe<Script_t*>>(MAX_MEMBERS)),
        update_ais(Vector_t<maybe<Member_Update_AI_e>>(MAX_MEMBERS, Member_Update_AI_e::RESET_AI)),

        vanilla_ghost_abilities(skylib::Const::Spells::Ghost_Abilities())
    {
        SKYLIB_ASSERT_SOME(quest);

        if (is_new_game) {
            Do_Allow_Menu_For_All_Actors(true);

            Do_Force_Clone_Uniques(false);
            Do_Force_Clone_Generics(false);
            Do_Force_Unclone_Uniques(false);
            Do_Force_Unclone_Generics(false);

            Fill_Outfit_Body_Percent(DEFAULT_FILL_OUTFIT_BODY_PERCENT);
            Fill_Outfit_Feet_Percent(DEFAULT_FILL_OUTFIT_FEET_PERCENT);
            Fill_Outfit_Hands_Percent(DEFAULT_FILL_OUTFIT_HANDS_PERCENT);
            Fill_Outfit_Head_Percent(DEFAULT_FILL_OUTFIT_HEAD_PERCENT);
        } else {
            this->save_state.Read();

            Validate();
        }
    }

    Members_t::Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        save_state(quest),

        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        scripts(Vector_t<maybe<Script_t*>>(MAX_MEMBERS)),
        update_ais(Vector_t<maybe<Member_Update_AI_e>>(MAX_MEMBERS, Member_Update_AI_e::RESET_AI)),

        vanilla_ghost_abilities(skylib::Const::Spells::Ghost_Abilities())
    {
        // update code goes here

        this->save_state.Read();

        Validate();
    }

    Members_t::~Members_t()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            maybe<Actor_Base_t*> custom_base = this->custom_bases[idx];
            if (custom_base) {
                maybe<Actor_t*> actor = this->save_state.actors[idx];
                if (actor) {
                    maybe<Actor_Base_t*> original_base = this->save_state.original_bases[idx];
                    if (original_base) {
                        actor->Actor_Base(original_base(), false);
                        Actor_Base_t::Destroy(custom_base());
                    }
                } else {
                    Actor_Base_t::Destroy(custom_base());
                }
                this->custom_bases[idx] = none<Actor_Base_t*>();
            }
        }

        // we need to destroy scripts too
    }

    void Members_t::Before_Save()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (Validate_Member(idx)) {
                Actor(idx)->Actor_Base(Original_Base(idx), false);
            }
        }
        this->save_state.Write();
    }

    void Members_t::After_Save()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (Has_Member(idx)) {
                Actor(idx)->Actor_Base(Custom_Base(idx), false);
            }
        }
    }

    Bool_t Members_t::Has_Untouchable_Invulnerables()
    {
        return this->save_state.has_untouchable_invulnerables;
    }

    void Members_t::Has_Untouchable_Invulnerables(Bool_t value)
    {
        this->save_state.has_untouchable_invulnerables = value;
    }

    Bool_t Members_t::Has_Alias(Member_ID_t member_id)
    {
        return this->quest->Has_Alias_Index(member_id);
    }

    Bool_t Members_t::Has_Alias(Alias_ID_t alias_id)
    {
        return this->quest->Has_Alias_ID(alias_id);
    }

    Bool_t Members_t::Has_Member(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        maybe<Actor_t*> actor = this->save_state.actors[member_id()];
        maybe<Actor_Base_t*> base = this->save_state.original_bases[member_id()];
        return
            actor && actor->Is_Valid() && actor->Isnt_Deleted() &&
            base && base->Is_Valid() && base->Isnt_Deleted();
    }

    Bool_t Members_t::Has_Member(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (this->save_state.actors[idx] == actor) {
                return Has_Member(idx);
            }
        }
        return false;
    }

    maybe<Member_ID_t> Members_t::Used_Member_ID(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (this->save_state.actors[idx] == actor && Has_Member(idx)) {
                return idx;
            }
        }
        return none<Member_ID_t>();
    }

    maybe<Member_ID_t> Members_t::Unused_Member_ID()
    {
        // this needs to be locked.
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (!Has_Member(idx)) {
                return idx;
            }
        }
        return none<Member_ID_t>();
    }

    static void Add_Member(some<Members_t*> self, Member_ID_t member_id, some<Actor_t*> actor, some<Actor_Base_t*> base);
    static void Fill_Member(some<Members_t*> self, Member_ID_t member_id, some<Actor_t*> actor);

    static void Add_Member(some<Members_t*> self, Member_ID_t member_id, some<Actor_t*> actor, some<Actor_Base_t*> base)
    {
        SKYLIB_ASSERT_SOME(self);
        SKYLIB_ASSERT_SOME(actor);
        SKYLIB_ASSERT_SOME(base);

        self->save_state.actors[member_id] = actor();
        self->save_state.original_bases[member_id] = base();

        // do we handle flags here also?

        self->save_state.names[member_id] = actor->Name();
        self->save_state.packs[member_id] = none<Reference_t*>();
        self->save_state.combat_styles[member_id] = self->save_state.default_combat_style();
        self->save_state.ghost_abilities[member_id] = none<Spell_t*>(); // maybe should look at actor for any acceptable ability
        self->save_state.voice_types[member_id] = none<Voice_Type_t*>(); // we need to have 2 defaults: male/female

        maybe<Outfit_t*> default_outfit = base->Default_Outfit();
        self->save_state.default_outfits[member_id] = default_outfit;
        self->save_state.vanilla_outfits[member_id] = default_outfit;

        // so the member_suit_fill_type determines whether we use a ref or a base to fill the member suit.
        // with a clone, that ref should be the original actor. when we clone, we could just copy all the items onto clone first
        self->save_state.backup_suits[member_id] = none<Member_Suit_t*>(); // should be set to member
        self->save_state.default_suits[member_id] = none<Member_Suit_t*>();
        self->save_state.follower_suits[member_id] = none<Member_Suit_t*>();
        self->save_state.immobile_suits[member_id] = none<Member_Suit_t*>();
        self->save_state.member_suits[member_id] = none<Member_Suit_t*>(); // shall be created in this func.
        self->save_state.settler_suits[member_id] = none<Member_Suit_t*>();
        self->save_state.thrall_suits[member_id] = none<Member_Suit_t*>();
        self->save_state.vanilla_suits[member_id] = none<Member_Suit_t*>();

        self->save_state.alphas[member_id] = Members_t::DEFAULT_ALPHA;
        self->save_state.ratings[member_id] = Members_t::DEFAULT_RATING;
        self->save_state.relations[member_id] = self->save_state.default_relation;
        self->save_state.suit_types[member_id] = self->save_state.default_suit_type;
        self->save_state.vitalities[member_id] = self->save_state.default_vitality;

        Fill_Member(self, member_id, actor);
    }

    static void Fill_Member(some<Members_t*> self, Member_ID_t member_id, some<Actor_t*> actor)
    {
        class Fill_Callback :
            public V::Callback_t
        {
        public:
            some<Members_t*>    self;
            Member_ID_t         member_id;

        public:
            Fill_Callback(some<Members_t*> self, Member_ID_t member_id) :
                self(self), member_id(member_id)
            {
            }

        public:
            virtual void operator ()(V::Variable_t*) override
            {
                this->self->Validate_Member(this->member_id);
            }
        };
        self->Alias_Reference(member_id)->Fill(actor, new Fill_Callback(self, member_id));
    }

    maybe<Member_ID_t> Members_t::Add_Member(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        if (actor->Is_Valid() && actor->Isnt_Deleted() && !Has_Member(actor)) {
            maybe<Actor_Base_t*> base = actor->Actor_Base();
            if (base && base->Is_Valid() && base->Isnt_Deleted()) {
                maybe<Member_ID_t> member_id = Unused_Member_ID();
                if (member_id) {
                    Party::Add_Member(this, member_id(), actor, base());
                    return member_id;
                } else {
                    return none<Member_ID_t>();
                }
            } else {
                return none<Member_ID_t>();
            }
        } else {
            return none<Member_ID_t>();
        }
    }

    maybe<Member_ID_t> Members_t::Add_Member(some<Actor_Base_t*> base)
    {
        SKYLIB_ASSERT_SOME(base);

        if (base->Is_Valid() && base->Isnt_Deleted()) {
            maybe<Member_ID_t> member_id = Unused_Member_ID();
            if (member_id) {
                maybe<Actor_t*> actor = Actor_t::Create(base, true, true, true);
                if (actor && actor->Is_Valid() && actor->Isnt_Deleted()) {
                    Party::Add_Member(this, member_id(), actor(), base);
                    return member_id;
                } else {
                    return none<Member_ID_t>();
                }
            } else {
                return none<Member_ID_t>();
            }
        } else {
            return none<Member_ID_t>();
        }
    }

    maybe<Member_ID_t> Members_t::Add_Member_Clone(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Actor_Base_t*> base = actor->Actor_Base();
        if (base && base->Is_Valid() && base->Isnt_Deleted()) {
            maybe<Member_ID_t> member_id = Unused_Member_ID();
            if (member_id) {
                maybe<Actor_t*> actor = Actor_t::Create(base(), true, true, true);
                if (actor && actor->Is_Valid() && actor->Isnt_Deleted()) {
                    this->save_state.flags[member_id()].Flag(Member_Flags_e::IS_CLONE);
                    Party::Add_Member(this, member_id(), actor(), base());
                    return member_id;
                } else {
                    return none<Member_ID_t>();
                }
            } else {
                return none<Member_ID_t>();
            }
        } else {
            return none<Member_ID_t>();
        }
    }

    Bool_t Members_t::Remove_Member(Member_ID_t member_id)
    {
        // this will cleanse anything under the id that it can, even if the data is incomplete in some manner, it cleans it up.
        // it fails gracefully and just defaults the values.

        // also, this must destroy the custom base so it's created again for the next actor
        return false;
    }

    size_t Members_t::Member_Count()
    {
        size_t result = 0;
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (Has_Member(idx)) {
                result += 1;
            }
        }
        return result;
    }

    void Members_t::Validate()
    {
        size_t member_count = Member_Count();
        if (this->save_state.limit < member_count) {
            this->save_state.limit = member_count;
        } else if (this->save_state.limit < 1) {
            this->save_state.limit = 1;
        } else if (this->save_state.limit > MAX_MEMBERS) {
            this->save_state.limit = MAX_MEMBERS;
        }

        if (!this->save_state.member_suit_fill_type) {
            this->save_state.member_suit_fill_type = DEFAULT_MEMBER_SUIT_FILL_TYPE;
        }
        if (!this->save_state.sort_type) {
            this->save_state.sort_type = DEFAULT_SORT_TYPE;
        }

        // we unfill first because the quest currently doesn't allow dupe aliases.
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            maybe<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(idx);
            SKYLIB_ASSERT_SOME(alias_reference);
            alias_reference->Unfill(none<V::Callback_i*>());
        }

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (Has_Member(idx)) {
                Fill_Member(this, idx, Actor(idx));
            } else {
                Remove_Member(idx);
            }
        }
    }

    some<Alias_Reference_t*> Members_t::Alias_Reference(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        some<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(valid_member_id)();
        SKYLIB_ASSERT_SOME(alias_reference);
        return alias_reference;
    }

    some<Actor_t*> Members_t::Actor(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        some<Actor_t*> actor = this->save_state.actors[valid_member_id()]();
        SKYLIB_ASSERT_SOME(actor);
        return actor;
    }

    some<Actor_Base_t*> Members_t::Original_Base(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        some<Actor_Base_t*> original_base = this->save_state.original_bases[valid_member_id]();
        SKYLIB_ASSERT_SOME(original_base);
        return original_base;
    }

    some<Actor_Base_t*> Members_t::Custom_Base(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Actor_Base_t*>& custom_base = this->custom_bases[valid_member_id];
        if (!custom_base) {
            custom_base = Actor_Base_t::Create_Temporary_Copy(Original_Base(valid_member_id))();
            SKYLIB_ASSERT_SOME(custom_base);
        }

        return custom_base();
    }

    some<Script_t*> Members_t::Script(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Script_t*>& script = this->scripts[valid_member_id];
        if (!script) {
            script = Script_t::Create()();
            SKYLIB_ASSERT_SOME(script);
        }

        return script();
    }

    void Members_t::Update_AI(Member_ID_t valid_member_id, some<Member_Update_AI_e> update_ai)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(update_ai);

        maybe<Member_Update_AI_e>& this_update_ai = this->update_ais[valid_member_id];
        if (this_update_ai != Member_Update_AI_e::RESET_AI) {
            this_update_ai = update_ai;
        }
    }

    Bool_t Members_t::Is_Banished(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_BANISHED);
    }

    void Members_t::Is_Banished(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_BANISHED, value);
    }

    Bool_t Members_t::Is_Clone(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_CLONE);
    }

    void Members_t::Is_Clone(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_CLONE, value);
    }

    Bool_t Members_t::Is_Immobile(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_IMMOBILE);
    }

    void Members_t::Is_Immobile(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_IMMOBILE, value);
    }

    Bool_t Members_t::Is_Mannequin(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_MANNEQUIN);
    }

    void Members_t::Is_Mannequin(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_MANNEQUIN, value);
    }

    Bool_t Members_t::Is_Paralyzed(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_PARALYZED);
    }

    void Members_t::Is_Paralyzed(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_PARALYZED, value);
    }

    Bool_t Members_t::Is_Reanimated(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_REANIMATED);
    }

    void Members_t::Is_Reanimated(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_REANIMATED, value);
    }

    Bool_t Members_t::Is_Thrall(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_THRALL);
    }

    void Members_t::Is_Thrall(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id].Is_Flagged(Member_Flags_e::IS_THRALL, value);
    }

    String_t Members_t::Name(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        String_t name = this->save_state.names[valid_member_id];
        if (!name) {
            name = Original_Base(valid_member_id)->Name();
        }

        return name;
    }

    void Members_t::Name(Member_ID_t valid_member_id, String_t name)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.names[valid_member_id] = name;
    }

    maybe<Combat_Style_t*> Members_t::Combat_Style(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Combat_Style_t*> combat_style = this->save_state.combat_styles[valid_member_id];
        if (!combat_style) {
            combat_style = Original_Base(valid_member_id)->Combat_Style();
        }

        return combat_style;
    }

    void Members_t::Combat_Style(Member_ID_t valid_member_id, maybe<Combat_Style_t*> combat_style)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.combat_styles[valid_member_id] = combat_style;
    }

    void Members_t::Combat_Style(Member_ID_t valid_member_id, Member_Combat_Style_e combat_style)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Combat_Style(valid_member_id, combat_style.As_Combat_Style());
    }

    maybe<Spell_t*> Members_t::Ghost_Ability(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.ghost_abilities[valid_member_id];
    }

    void Members_t::Ghost_Ability(Member_ID_t valid_member_id, maybe<Spell_t*> ghost_ability)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.ghost_abilities[valid_member_id] = ghost_ability;
    }

    some<Voice_Type_t*> Members_t::Voice_Type(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Voice_Type_t*> voice_type = this->save_state.voice_types[valid_member_id];
        if (!voice_type) {
            voice_type = Original_Base(valid_member_id)->Voice_Type();
            if (!voice_type) {
                voice_type = Actor(valid_member_id)->Race_Voice_Type();
                if (!voice_type) {
                    voice_type = Consts_t::NPCP::Voice_Type::Blank()();
                }
            }
        }

        SKYLIB_ASSERT_SOME(voice_type);

        return voice_type();
    }

    void Members_t::Voice_Type(Member_ID_t valid_member_id, maybe<Voice_Type_t*> voice_type)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.voice_types[valid_member_id] = voice_type;
    }

    maybe<Member_Alpha_t> Members_t::Alpha(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        if (!Is_Enabled(valid_member_id)) {
            return 0.0f;
        } else {
            return this->save_state.alphas[valid_member_id];
        }
    }

    void Members_t::Alpha(Member_ID_t valid_member_id, maybe<Member_Alpha_t> alpha)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.alphas[valid_member_id] = alpha;
    }

    maybe<Member_Rating_t> Members_t::Rating(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.ratings[valid_member_id];
    }

    void Members_t::Rating(Member_ID_t valid_member_id, maybe<Member_Rating_t> rating)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.ratings[valid_member_id] = rating;
    }

    some<Member_Relation_e> Members_t::Relation(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Member_Relation_e> relation = this->save_state.relations[valid_member_id];
        if (!relation) {
            relation = Original_Base(valid_member_id)->Relation(skylib::Const::Actor_Base::Player());
        }

        SKYLIB_ASSERT_SOME(relation);

        return relation();
    }

    void Members_t::Relation(Member_ID_t valid_member_id, maybe<Member_Relation_e> relation)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.relations[valid_member_id] = relation;
    }

    maybe<Member_Suit_Type_e> Members_t::Suit_Type(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        // this should at least partially calculate what outfit is going to be worn.

        return this->save_state.suit_types[valid_member_id];
    }

    void Members_t::Suit_Type(Member_ID_t valid_member_id, maybe<Member_Suit_Type_e> suit_type)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));
    }

    some<Member_Vitality_e> Members_t::Vitality(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Member_Vitality_e> vitality = this->save_state.vitalities[valid_member_id];
        if (!vitality) {
            vitality = Original_Base(valid_member_id)->Vitality();
        }

        SKYLIB_ASSERT_SOME(vitality);

        return vitality();
    }

    void Members_t::Vitality(Member_ID_t valid_member_id, maybe<Member_Vitality_e> vitality)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.vitalities[valid_member_id] = vitality;
    }

    Bool_t Members_t::Is_Mortal(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::MORTAL;
    }

    void Members_t::Is_Mortal(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::MORTAL);
    }

    Bool_t Members_t::Is_Protected(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::PROTECTED;
    }

    void Members_t::Is_Protected(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::PROTECTED);
    }

    Bool_t Members_t::Is_Essential(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::ESSENTIAL;
    }

    void Members_t::Is_Essential(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::ESSENTIAL);
    }

    Bool_t Members_t::Is_Invulnerable(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::INVULNERABLE;
    }

    void Members_t::Is_Invulnerable(Member_ID_t valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::INVULNERABLE);
    }

    Bool_t Members_t::Is_Enabled(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return
            !Is_Banished(valid_member_id);
    }

    Bool_t Members_t::Is_Untouchable(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return
            (Has_Untouchable_Invulnerables() && Is_Invulnerable(valid_member_id));
    }

    Bool_t Members_t::Has_AI(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return
            !Is_Banished(valid_member_id) &&
            !Is_Mannequin(valid_member_id) &&
            !Is_Paralyzed(valid_member_id);
    }

    maybe<Member_Suit_t*> Members_t::Suit(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        // this needs to calc the exact suit to oufit the actor with, if any.
        // it may also need to create it and insert it into save_state.

        return none<Member_Suit_t*>();
    }

    void Members_t::Tokenize(Member_ID_t valid_member_id,
                             some<Bound_Object_t*> object,
                             Container_Entry_Count_t count)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT(count > 0);

        some<Actor_t*> actor = Actor(valid_member_id);
        Reference_Container_t container = actor->Container();
        some<Reference_Container_Entry_t*> entry = container.Some_Entry(object);
        entry->Decrement_Count(&container, Container_Entry_Count_t::_MAX_);
        entry->Increment_Count(&container, count);
    }

    void Members_t::Untokenize(Member_ID_t valid_member_id,
                               some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(object);

        some<Actor_t*> actor = Actor(valid_member_id);
        Reference_Container_t container = actor->Container();
        some<Reference_Container_Entry_t*> entry = container.Some_Entry(object);
        entry->Decrement_Count(&container, Container_Entry_Count_t::_MAX_);
    }

    Bool_t Members_t::Validate_Member(Member_ID_t member_id)
    {
        // we may want a different smaller branch if the actor is in combat, or a separate func to call

        if (Has_Member(member_id)) {
            some<Actor_t*> actor = Actor(member_id);
            some<Actor_Base_t*> custom_base = Custom_Base(member_id);

            Vector_t<some<Spell_t*>> spells_to_add;
            spells_to_add.reserve(4);

            actor->Actor_Base(Custom_Base(member_id), false);

            Tokenize(member_id, Consts_t::NPCP::Misc::Token::Member(), member_id + 1);
            actor->Faction_Rank(Consts_t::NPCP::Faction::Member(), 0);

            if (Is_Banished(member_id)) {
                Tokenize(member_id, Consts_t::NPCP::Misc::Token::Banished());
            } else {
                Untokenize(member_id, Consts_t::NPCP::Misc::Token::Banished());
            }

            if (Is_Immobile(member_id)) {
                Tokenize(member_id, Consts_t::NPCP::Misc::Token::Immobile());
            } else {
                Untokenize(member_id, Consts_t::NPCP::Misc::Token::Immobile());
            }

            if (Is_Reanimated(member_id)) {
                Tokenize(member_id, Consts_t::NPCP::Misc::Token::Reanimated());

                spells_to_add.push_back(Consts_t::NPCP::Spell::Reanimate_Ability());
            } else {
                Untokenize(member_id, Consts_t::NPCP::Misc::Token::Reanimated());

                actor->Remove_Spell(Consts_t::NPCP::Spell::Reanimate_Ability());
            }

            if (Is_Thrall(member_id)) {
                Tokenize(member_id, Consts_t::NPCP::Misc::Token::Thrall());
            } else {
                Untokenize(member_id, Consts_t::NPCP::Misc::Token::Thrall());
            }

            custom_base->Name(Name(member_id));
            actor->x_list.Destroy_Extra_Text_Display();

            custom_base->Combat_Style(Combat_Style(member_id));

            maybe<Spell_t*> ghost_ability = Ghost_Ability(member_id);
            for (size_t idx = 0, end = this->vanilla_ghost_abilities.size(); idx < end; idx += 1) {
                some<Spell_t*> vanilla_ghost_ability = this->vanilla_ghost_abilities[idx];
                if (vanilla_ghost_ability != ghost_ability) {
                    actor->Remove_Spell(this->vanilla_ghost_abilities[idx]);
                }
            }
            if (ghost_ability) {
                spells_to_add.push_back(ghost_ability());
            }

            custom_base->Voice_Type(Voice_Type(member_id)());

            actor->Alpha(Alpha(member_id)());

            custom_base->Relation(skylib::Const::Actor_Base::Player(), Relation(member_id));

            custom_base->Vitality(Vitality(member_id), false);

            if (Is_Enabled(member_id)) {
                if (actor->Is_Disabled()) {
                    actor->Enable();
                }
            } else {
                if (actor->Is_Enabled()) {
                    actor->Disable();
                }
            }

            if (Is_Untouchable(member_id)) {
                actor->Is_Ghost(true);
            } else {
                actor->Is_Ghost(false);
            }

            if (Has_AI(member_id)) {
                if (!actor->Has_AI()) {
                    actor->Has_AI(true);
                    Update_AI(member_id, Member_Update_AI_e::RESET_AI);
                }
            } else {
                if (actor->Has_AI()) {
                    actor->Has_AI(false);
                }
            }

            if (actor->Is_Attached()) {
                for (size_t idx = 0, end = spells_to_add.size(); idx < end; idx += 1) {
                    some<Spell_t*> spell = spells_to_add[idx];
                    if (!actor->Has_Magic_Effects(spell)) {
                        actor->Reset_Spell(spell);
                    }
                }
            } else {
                for (size_t idx = 0, end = spells_to_add.size(); idx < end; idx += 1) {
                    actor->Remove_Spell(spells_to_add[idx]);
                }
            }

            maybe<Actor_t*> combat_target = actor->Current_Combat_Target();
            if (combat_target) {
                if (combat_target == skylib::Const::Actor::Player() || Has_Member(combat_target())) {
                    // we need to handle aggression also, but that needs to be done along with other factors?
                    actor->Stop_Combat_And_Alarm();
                    actor->actor_flags_2.Unflag(skylib::Actor_Flags_2_e::IS_ANGRY_WITH_PLAYER);
                    Update_AI(member_id, Member_Update_AI_e::RESET_AI);
                }
            }

            // we need to call other Validate methods, Settlers, Displays, Followers, etc. before updating ai

            maybe<Member_Update_AI_e>& update_ai = this->update_ais[member_id];
            if (update_ai == Member_Update_AI_e::RESET_AI) {
                actor->Reset_AI();
            } else if (update_ai == Member_Update_AI_e::EVALUATE_PACKAGE) {
                actor->Evaluate_Package(true, false);
            }
            update_ai = Member_Update_AI_e::_NONE_;

            return true;
        } else {
            Remove_Member(member_id);

            return false;
        }
    }

    void Members_t::Validate_Members()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            Validate_Member(idx);
        }
    }

}}
