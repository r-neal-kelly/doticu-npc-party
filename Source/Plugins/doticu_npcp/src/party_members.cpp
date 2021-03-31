/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/global.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/voice_type.h"
#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "party_members.h"
#include "party_member_suit.h"

namespace doticu_npcp { namespace Party {

    Members_t::Save_State::Save_State(Members_t& members) :
        members(members),

        limit(MAX_MEMBERS),

        do_auto_suits(DEFAULT_DO_AUTO_SUITS),
        do_auto_immobile_suit(DEFAULT_DO_AUTO_IMMOBILE_SUIT),
        do_fill_suits(DEFAULT_DO_FILL_SUITS),

        default_relation(DEFAULT_RELATION),
        default_style(DEFAULT_STYLE),
        default_suit_type(DEFAULT_SUIT_TYPE),
        default_vitality(DEFAULT_VITALITY),

        clone_suit_fill_type(DEFAULT_CLONE_SUIT_FILL_TYPE),
        sort_type(DEFAULT_SORT_TYPE),

        actors(Vector_t<maybe<Actor_t*>>(MAX_MEMBERS, none<Actor_t*>())),
        original_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS, none<Actor_Base_t*>())),

        flags(Vector_t<Member_Flags_e>(MAX_MEMBERS, 0)),

        names(Vector_t<String_t>(MAX_MEMBERS, "")),
        packs(Vector_t<maybe<Reference_t*>>(MAX_MEMBERS, none<Reference_t*>())),
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

        ratings(Vector_t<maybe<Member_Rating_t>>(MAX_MEMBERS, 0)),
        relations(Vector_t<maybe<Member_Relation_e>>(MAX_MEMBERS, DEFAULT_RELATION)),
        styles(Vector_t<maybe<Member_Style_e>>(MAX_MEMBERS, DEFAULT_STYLE)),
        suit_types(Vector_t<maybe<Member_Suit_Type_e>>(MAX_MEMBERS, DEFAULT_SUIT_TYPE)),
        vitalities(Vector_t<maybe<Member_Vitality_e>>(MAX_MEMBERS, DEFAULT_VITALITY))
    {
    }

    Members_t::Save_State::~Save_State()
    {
    }

    some<V::Object_t*> Members_t::Save_State::Object()
    {
        DEFINE_COMPONENT_OBJECT_METHOD(this->members.quest());
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

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Relation()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_relation");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Style()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_style");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Suit_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_suit_type");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Default_Vitality()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "default_vitality");
    }

    V::Variable_tt<String_t>& Members_t::Save_State::Clone_Suit_Fill_Type()
    {
        DEFINE_VARIABLE_REFERENCE(String_t, "clone_suit_fill_type");
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

    V::Variable_tt<Vector_t<Int_t>>& Members_t::Save_State::Ratings()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Int_t>, "ratings");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Relations()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "relations");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Styles()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "styles");
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

        this->default_relation = Default_Relation().As<String_t>();
        this->default_style = Default_Style().As<String_t>();
        this->default_suit_type = Default_Suit_Type().As<String_t>();
        this->default_vitality = Default_Vitality().As<String_t>();

        this->clone_suit_fill_type = Clone_Suit_Fill_Type().As<String_t>();
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

        Vector_t<Int_t> ratings = Ratings();
        Vector_t<String_t> relations = Relations();
        Vector_t<String_t> styles = Styles();
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

        ratings.resize(MAX_MEMBERS);
        relations.resize(MAX_MEMBERS);
        styles.resize(MAX_MEMBERS);
        suit_types.resize(MAX_MEMBERS);
        vitalities.resize(MAX_MEMBERS);

        for (Member_ID_t member_id = 0, end = this->actors.size(); member_id < end; member_id += 1) {
            Member_Flags_e& flags = this->flags[member_id];
            flags.Is_Flagged(Member_Flags_e::IS_BANISHED, is_banished_flags[member_id]);
            flags.Is_Flagged(Member_Flags_e::IS_CLONE, is_clone_flags[member_id]);
            flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE, is_immobile_flags[member_id]);
            flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN, is_mannequin_flags[member_id]);
            flags.Is_Flagged(Member_Flags_e::IS_PARALYZED, is_paralyzed_flags[member_id]);
            flags.Is_Flagged(Member_Flags_e::IS_REANIMATED, is_reanimated_flags[member_id]);
            flags.Is_Flagged(Member_Flags_e::IS_THRALL, is_thrall_flags[member_id]);

            this->ratings[member_id] = ratings[member_id];
            this->relations[member_id] = relations[member_id];
            this->styles[member_id] = styles[member_id];
            this->suit_types[member_id] = suit_types[member_id];
            this->vitalities[member_id] = vitalities[member_id];
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

        Vector_t<Int_t> ratings(MAX_MEMBERS, Member_Rating_t::_NONE_);
        Vector_t<String_t> relations(MAX_MEMBERS, "");
        Vector_t<String_t> styles(MAX_MEMBERS, "");
        Vector_t<String_t> suit_types(MAX_MEMBERS, "");
        Vector_t<String_t> vitalities(MAX_MEMBERS, "");

        for (Member_ID_t idx = 0, end = this->actors.size(); idx < end; idx += 1) {
            if (this->actors[idx]) {
                Member_Flags_e flags = this->flags[idx];
                is_banished_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_BANISHED);
                is_clone_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_CLONE);
                is_immobile_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE);
                is_mannequin_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN);
                is_paralyzed_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_PARALYZED);
                is_reanimated_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_REANIMATED);
                is_thrall_flags[idx] = flags.Is_Flagged(Member_Flags_e::IS_THRALL);

                ratings[idx] = this->ratings[idx]();
                relations[idx] = this->relations[idx]().As_String();
                styles[idx] = this->styles[idx]().As_String();
                suit_types[idx] = this->suit_types[idx]().As_String();
                vitalities[idx] = this->vitalities[idx]().As_String();
            }
        }

        Limit() = this->limit;

        Do_Auto_Suits() = this->do_auto_suits;
        Do_Auto_Immobile_Suit() = this->do_auto_immobile_suit;
        Do_Fill_Suits() = this->do_fill_suits;

        Default_Relation() = this->default_relation().As_String();
        Default_Style() = this->default_style().As_String();
        Default_Suit_Type() = this->default_suit_type().As_String();
        Default_Vitality() = this->default_vitality().As_String();

        Clone_Suit_Fill_Type() = this->clone_suit_fill_type().As_String();
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

        Ratings() = ratings;
        Relations() = relations;
        Styles() = styles;
        Suit_Types() = suit_types;
        Vitalities() = vitalities;
    }

    String_t Members_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_members");
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
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        save_state(*this)
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
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        save_state(*this)
    {
        // update code goes here

        new (this) Members_t(quest, false);
    }

    Members_t::~Members_t()
    {
        for (Member_ID_t member_id = 0, end = this->custom_bases.size(); member_id < end; member_id += 1) {
            maybe<Actor_Base_t*> custom_base = this->custom_bases[member_id];
            if (custom_base) {
                maybe<Actor_t*> actor = this->save_state.actors[member_id];
                if (actor) {
                    maybe<Actor_Base_t*> original_base = this->save_state.original_bases[member_id];
                    if (original_base) {
                        actor->Actor_Base(original_base(), false);
                        Actor_Base_t::Destroy(custom_base());
                        this->custom_bases[member_id] = none<Actor_Base_t*>();
                    } else {
                        this->custom_bases[member_id] = none<Actor_Base_t*>();
                    }
                } else {
                    Actor_Base_t::Destroy(custom_base());
                    this->custom_bases[member_id] = none<Actor_Base_t*>();
                }
            }
        }
    }

    Bool_t Members_t::Has_Alias(Member_ID_t member_id)
    {
        return this->quest->Has_Alias_Index(member_id);
    }

    Bool_t Members_t::Has_Alias(Alias_ID_t alias_id)
    {
        return this->quest->Has_Alias_ID(alias_id);
    }

    Bool_t Members_t::Has_Member(Member_ID_t member_id)
    {
        maybe<Actor_t*> actor = this->save_state.actors[member_id];
        maybe<Actor_Base_t*> base = this->save_state.original_bases[member_id];
        return
            actor && actor->Is_Valid() && actor->Isnt_Deleted() &&
            base && base->Is_Valid() && base->Isnt_Deleted();
    }

    Bool_t Members_t::Has_Member(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        for (size_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (this->save_state.actors[member_id] == actor) {
                return Has_Member(member_id);
            }
        }
    }

    maybe<Member_ID_t> Members_t::Maybe_Free_Member_ID()
    {
        // this needs to be locked.
        for (size_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (!Has_Member(member_id)) {
                return member_id;
            }
        }
        return none<Member_ID_t>();
    }

    maybe<Member_ID_t> Members_t::Add_Member(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        if (actor->Is_Valid() && actor->Isnt_Deleted() && !Has_Member(actor)) {
            maybe<Actor_Base_t*> base = actor->Actor_Base();
            if (base && base->Is_Valid() && base->Isnt_Deleted()) {
                maybe<Member_ID_t> maybe_member_id = Maybe_Free_Member_ID();
                if (maybe_member_id.Has_Value()) {
                    Member_ID_t member_id = maybe_member_id.Value();
                    this->save_state.actors[member_id] = actor();
                    this->save_state.original_bases[member_id] = base;
                    Validate_Member(member_id);
                    Alias_Reference(member_id)->Fill(actor, none<V::Callback_i*>());
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
            maybe<Member_ID_t> maybe_member_id = Maybe_Free_Member_ID();
            if (maybe_member_id.Has_Value()) {
                maybe<Actor_t*> actor = Actor_t::Create(base, true, true, true);
                if (actor && actor->Is_Valid() && actor->Isnt_Deleted()) {
                    Member_ID_t member_id = maybe_member_id.Value();
                    this->save_state.actors[member_id] = actor;
                    this->save_state.original_bases[member_id] = base();
                    Validate_Member(member_id);
                    Alias_Reference(member_id)->Fill(actor(), none<V::Callback_i*>());
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
            maybe<Member_ID_t> maybe_member_id = Maybe_Free_Member_ID();
            if (maybe_member_id.Has_Value()) {
                maybe<Actor_t*> actor = Actor_t::Create(base(), true, true, true);
                if (actor && actor->Is_Valid() && actor->Isnt_Deleted()) {
                    Member_ID_t member_id = maybe_member_id.Value();
                    this->save_state.actors[member_id] = actor();
                    this->save_state.original_bases[member_id] = base();
                    Validate_Member(member_id);
                    Alias_Reference(member_id)->Fill(actor(), none<V::Callback_i*>());
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
        return false;
    }

    size_t Members_t::Member_Count()
    {
        size_t result = 0;
        for (size_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Has_Member(member_id)) {
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

        if (!this->save_state.default_relation) {
            this->save_state.default_relation = DEFAULT_RELATION;
        }
        if (!this->save_state.default_style) {
            this->save_state.default_style = DEFAULT_STYLE;
        }
        if (!this->save_state.default_vitality) {
            this->save_state.default_vitality = DEFAULT_VITALITY;
        }

        if (!this->save_state.clone_suit_fill_type) {
            this->save_state.clone_suit_fill_type = DEFAULT_CLONE_SUIT_FILL_TYPE;
        }
        if (!this->save_state.sort_type) {
            this->save_state.sort_type = DEFAULT_SORT_TYPE;
        }

        // we unfill first because the quest currently doesn't allow dupe aliases.
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            maybe<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(member_id);
            SKYLIB_ASSERT_SOME(alias_reference);
            alias_reference->Unfill(none<V::Callback_i*>());
        }

        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Has_Member(member_id)) {
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
                Alias_Reference(member_id)->Fill(Actor(member_id), new Fill_Callback(this, member_id));
            } else {
                Remove_Member(member_id);
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

    some<Actor_t*> Members_t::Actor(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        some<Actor_t*> actor = this->save_state.actors[valid_member_id]();
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

    maybe<Member_Suit_Type_e> Members_t::Maybe_Current_Suit_Type(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.suit_types[valid_member_id];
    }

    maybe<Member_Suit_t*> Members_t::Maybe_Current_Suit(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Member_Suit_Type_e> current_suit_type = Maybe_Current_Suit_Type(valid_member_id);
        if (current_suit_type == Member_Suit_Type_e::MEMBER) {
            return this->save_state.member_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::IMMOBILE) {
            return this->save_state.immobile_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::SETTLER) {
            return this->save_state.settler_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::THRALL) {
            return this->save_state.thrall_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::FOLLOWER) {
            return this->save_state.follower_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::VANILLA) {
            return this->save_state.vanilla_suits[valid_member_id];
        } else if (current_suit_type == Member_Suit_Type_e::DEFAULT) {
            return this->save_state.default_suits[valid_member_id];
        } else {
            none<Member_Suit_t*>();
        }
    }

    some<Voice_Type_t*> Members_t::Voice_Type(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Voice_Type_t*>& voice_type = this->save_state.voice_types[valid_member_id];
        if (!voice_type) {
            voice_type = Original_Base(valid_member_id)->Voice_Type();
            if (!voice_type) {
                voice_type = Actor(valid_member_id)->Race_Voice_Type();
                if (!voice_type) {
                    voice_type = Consts_t::NPCP::Voice_Type::Blank()();
                }
            }
            SKYLIB_ASSERT_SOME(voice_type);
        }

        return voice_type();
    }

    void Members_t::Voice_Type(Member_ID_t valid_member_id, some<Voice_Type_t*> voice_type)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(voice_type);

        this->save_state.voice_types[valid_member_id] = voice_type();
    }

    some<Member_Vitality_e> Members_t::Vitality(Member_ID_t valid_member_id)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Vitality_e>& vitality = this->save_state.vitalities[valid_member_id];
        if (!vitality) {
            vitality = Original_Base(valid_member_id)->Vitality();
            SKYLIB_ASSERT_SOME(vitality);
        }

        return vitality();
    }

    void Members_t::Vitality(Member_ID_t valid_member_id, some<Member_Vitality_e> vitality)
    {
        SKYLIB_ASSERT(Has_Member(valid_member_id));
        SKYLIB_ASSERT_SOME(vitality);

        this->save_state.vitalities[valid_member_id] = vitality();
    }

    Bool_t Members_t::Validate_Member(Member_ID_t member_id)
    {
        if (Has_Member(member_id)) {
            some<Actor_t*> actor = Actor(member_id);
            some<Actor_Base_t*> custom_base = Custom_Base(member_id);
            custom_base->Voice_Type(Voice_Type(member_id)());
            custom_base->Vitality(Vitality(member_id), false);
            actor->Actor_Base(Custom_Base(member_id), false);
            return true;
        } else {
            Remove_Member(member_id);
            return false;
        }
    }

    void Members_t::Before_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Validate_Member(member_id)) {
                Actor(member_id)->Actor_Base(Original_Base(member_id), false);
            }
        }
        this->save_state.Write();
    }

    void Members_t::After_Save()
    {
        for (Member_ID_t member_id = 0, end = this->save_state.actors.size(); member_id < end; member_id += 1) {
            if (Has_Member(member_id)) {
                Actor(member_id)->Actor_Base(Custom_Base(member_id), false);
            }
        }
    }

}}
