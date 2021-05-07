/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/ammo.h"
#include "doticu_skylib/armor.h"
#include "doticu_skylib/armor_set.h"
#include "doticu_skylib/combat_style.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_actor_bases.h"
#include "doticu_skylib/const_factions.h"
#include "doticu_skylib/const_spells.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/global.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/voice_type.h"
#include "doticu_skylib/virtual_macros.h"
#include "doticu_skylib/weapon.h"

#include "consts.h"
#include "main.h"
#include "npcp.h"
#include "party_members.h"
#include "party_member_suitcase.h"

namespace doticu_npcp { namespace Party {

    Members_t::Save_State::Save_State(const some<Quest_t*> quest) :
        quest(quest),

        limit(MAX_MEMBERS),

        fill_suit_aura_probability(DEFAULT_FILL_SUIT_AURA_PROBABILITY),
        fill_suit_body_probability(DEFAULT_FILL_SUIT_BODY_PROBABILITY),
        fill_suit_feet_probability(DEFAULT_FILL_SUIT_FEET_PROBABILITY),
        fill_suit_finger_probability(DEFAULT_FILL_SUIT_FINGER_PROBABILITY),
        fill_suit_forearm_probability(DEFAULT_FILL_SUIT_FOREARM_PROBABILITY),
        fill_suit_forehead_probability(DEFAULT_FILL_SUIT_FOREHEAD_PROBABILITY),
        fill_suit_hands_probability(DEFAULT_FILL_SUIT_HANDS_PROBABILITY),
        fill_suit_head_probability(DEFAULT_FILL_SUIT_HEAD_PROBABILITY),
        fill_suit_neck_probability(DEFAULT_FILL_SUIT_NECK_PROBABILITY),

        do_auto_suits(DEFAULT_DO_AUTO_SUITS),
        do_fill_suits(DEFAULT_DO_FILL_SUITS),
        do_fill_suits_automatically(DEFAULT_DO_FILL_SUITS_AUTOMATICALLY),
        do_fill_suits_strictly(DEFAULT_DO_FILL_SUITS_STRICTLY),
        do_unfill_suits_to_pack(DEFAULT_DO_UNFILL_SUITS_TO_PACK),

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
        flags_has_suit(Vector_t<Member_Flags_Has_Suit_e>(MAX_MEMBERS, 0)),
        flags_only_playables(Vector_t<Member_Flags_Only_Playables_e>(MAX_MEMBERS, 0)),

        names(Vector_t<String_t>(MAX_MEMBERS, "")),

        caches(Vector_t<maybe<Reference_t*>>(MAX_MEMBERS, none<Reference_t*>())),
        combat_styles(Vector_t<maybe<Combat_Style_t*>>(MAX_MEMBERS, none<Combat_Style_t*>())),
        ghost_abilities(Vector_t<maybe<Spell_t*>>(MAX_MEMBERS, none<Spell_t*>())),
        outfits(Vector_t<maybe<Outfit_t*>>(MAX_MEMBERS, none<Outfit_t*>())),
        packs(Vector_t<maybe<Reference_t*>>(MAX_MEMBERS, none<Reference_t*>())),
        suitcases(Vector_t<maybe<Member_Suitcase_t*>>(MAX_MEMBERS, none<Member_Suitcase_t*>())),
        voice_types(Vector_t<maybe<Voice_Type_t*>>(MAX_MEMBERS, none<Voice_Type_t*>())),

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

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Aura_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_aura_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Body_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_body_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Feet_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_feet_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Finger_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_finger_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Forearm_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_forearm_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Forehead_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_forehead_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Hands_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_hands_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Head_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_head_probability");
    }

    V::Variable_tt<Int_t>& Members_t::Save_State::Fill_Suit_Neck_Probability()
    {
        DEFINE_VARIABLE_REFERENCE(Int_t, "fill_suit_neck_probability");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Auto_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_auto_suits");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Fill_Suits()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_fill_suits");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Fill_Suits_Automatically()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_fill_suits_automatically");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Fill_Suits_Strictly()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_fill_suits_strictly");
    }

    V::Variable_tt<Bool_t>& Members_t::Save_State::Do_Unfill_Suits_To_Pack()
    {
        DEFINE_VARIABLE_REFERENCE(Bool_t, "do_unfill_suits_to_pack");
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

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Is_Banished()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_banished");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Is_Clone()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_clone");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Is_Immobile()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_immobile");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Is_Mannequin()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_mannequin");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Is_Reanimated()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_reanimated");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Is_Thrall()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_is_thrall");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Archer()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_archer");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Civilized()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_civilized");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Combatant()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_combatant");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Coward()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_coward");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Dangerous()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_dangerous");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Eater()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_eater");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Exterior()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_exterior");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Follower()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_follower");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Guard()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_guard");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Home()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_home");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Immobile()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_immobile");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Inn()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_inn");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Interior()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_interior");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Mage()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_mage");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Mannequin()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_mannequin");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Member()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_member");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Sandboxer()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_sandboxer");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Settlement()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_settlement");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Sitter()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_sitter");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Sleeper()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_sleeper");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Thrall()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_thrall");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Has_Suit_Warrior()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_has_suit_warrior");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Archer()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_archer");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Civilized()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_civilized");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Combatant()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_combatant");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Coward()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_coward");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Dangerous()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_dangerous");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Eater()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_eater");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Exterior()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_exterior");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Follower()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_follower");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Guard()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_guard");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Home()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_home");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Immobile()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_immobile");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Inn()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_inn");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Interior()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_interior");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Mage()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_mage");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Mannequin()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_mannequin");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Member()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_member");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Sandboxer()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_sandboxer");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Settlement()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_settlement");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Sitter()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_sitter");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Sleeper()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_sleeper");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Thrall()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_thrall");
    }

    V::Variable_tt<Vector_t<Bool_t>>& Members_t::Save_State::Flags_Only_Playables_Warrior()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<Bool_t>, "flags_only_playables_warrior");
    }

    V::Variable_tt<Vector_t<String_t>>& Members_t::Save_State::Names()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "names");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Caches()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "caches");
    }

    V::Variable_tt<Vector_t<maybe<Combat_Style_t*>>>& Members_t::Save_State::Combat_Styles()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Combat_Style_t*>>, "combat_styles");
    }

    V::Variable_tt<Vector_t<maybe<Spell_t*>>>& Members_t::Save_State::Ghost_Abilities()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Spell_t*>>, "ghost_abilities");
    }

    V::Variable_tt<Vector_t<maybe<Outfit_t*>>>& Members_t::Save_State::Outfits()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Outfit_t*>>, "outfits");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Packs()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "packs");
    }

    V::Variable_tt<Vector_t<maybe<Reference_t*>>>& Members_t::Save_State::Suitcases()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Reference_t*>>, "suitcases");
    }

    V::Variable_tt<Vector_t<maybe<Voice_Type_t*>>>& Members_t::Save_State::Voice_Types()
    {
        DEFINE_VARIABLE_REFERENCE(Vector_t<maybe<Voice_Type_t*>>, "voice_types");
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

        this->fill_suit_aura_probability = Fill_Suit_Aura_Probability();
        this->fill_suit_body_probability = Fill_Suit_Body_Probability();
        this->fill_suit_feet_probability = Fill_Suit_Feet_Probability();
        this->fill_suit_finger_probability = Fill_Suit_Finger_Probability();
        this->fill_suit_forearm_probability = Fill_Suit_Forearm_Probability();
        this->fill_suit_forehead_probability = Fill_Suit_Forehead_Probability();
        this->fill_suit_hands_probability = Fill_Suit_Hands_Probability();
        this->fill_suit_head_probability = Fill_Suit_Head_Probability();
        this->fill_suit_neck_probability = Fill_Suit_Neck_Probability();

        this->do_auto_suits = Do_Auto_Suits();
        this->do_fill_suits = Do_Fill_Suits();
        this->do_fill_suits = Do_Fill_Suits_Automatically();
        this->do_fill_suits_strictly = Do_Fill_Suits_Strictly();
        this->do_unfill_suits_to_pack = Do_Unfill_Suits_To_Pack();

        this->has_untouchable_invulnerables = Has_Untouchable_Invulnerables();

        this->default_combat_style = Default_Combat_Style().As<String_t>();
        this->default_relation = Default_Relation().As<String_t>();
        this->default_suit_type = Default_Suit_Type().As<String_t>();
        this->default_vitality = Default_Vitality().As<String_t>();

        this->member_suit_fill_type = Member_Suit_Fill_Type().As<String_t>();
        this->sort_type = Sort_Type().As<String_t>();

        this->actors = Actors();
        this->original_bases = Original_Bases();

        Vector_t<Bool_t> flags_is_banished = Flags_Is_Banished();
        Vector_t<Bool_t> flags_is_clone = Flags_Is_Clone();
        Vector_t<Bool_t> flags_is_immobile = Flags_Is_Immobile();
        Vector_t<Bool_t> flags_is_mannequin = Flags_Is_Mannequin();
        Vector_t<Bool_t> flags_is_reanimated = Flags_Is_Reanimated();
        Vector_t<Bool_t> flags_is_thrall = Flags_Is_Thrall();

        Vector_t<Bool_t> flags_has_suit_archer = Flags_Has_Suit_Archer();
        Vector_t<Bool_t> flags_has_suit_civilized = Flags_Has_Suit_Civilized();
        Vector_t<Bool_t> flags_has_suit_combatant = Flags_Has_Suit_Combatant();
        Vector_t<Bool_t> flags_has_suit_coward = Flags_Has_Suit_Coward();
        Vector_t<Bool_t> flags_has_suit_dangerous = Flags_Has_Suit_Dangerous();
        Vector_t<Bool_t> flags_has_suit_eater = Flags_Has_Suit_Eater();
        Vector_t<Bool_t> flags_has_suit_exterior = Flags_Has_Suit_Exterior();
        Vector_t<Bool_t> flags_has_suit_follower = Flags_Has_Suit_Follower();
        Vector_t<Bool_t> flags_has_suit_guard = Flags_Has_Suit_Guard();
        Vector_t<Bool_t> flags_has_suit_home = Flags_Has_Suit_Home();
        Vector_t<Bool_t> flags_has_suit_immobile = Flags_Has_Suit_Immobile();
        Vector_t<Bool_t> flags_has_suit_inn = Flags_Has_Suit_Inn();
        Vector_t<Bool_t> flags_has_suit_interior = Flags_Has_Suit_Interior();
        Vector_t<Bool_t> flags_has_suit_mage = Flags_Has_Suit_Mage();
        Vector_t<Bool_t> flags_has_suit_mannequin = Flags_Has_Suit_Mannequin();
        Vector_t<Bool_t> flags_has_suit_member = Flags_Has_Suit_Member();
        Vector_t<Bool_t> flags_has_suit_sandboxer = Flags_Has_Suit_Sandboxer();
        Vector_t<Bool_t> flags_has_suit_settlement = Flags_Has_Suit_Settlement();
        Vector_t<Bool_t> flags_has_suit_sitter = Flags_Has_Suit_Sitter();
        Vector_t<Bool_t> flags_has_suit_sleeper = Flags_Has_Suit_Sleeper();
        Vector_t<Bool_t> flags_has_suit_thrall = Flags_Has_Suit_Thrall();
        Vector_t<Bool_t> flags_has_suit_warrior = Flags_Has_Suit_Warrior();

        Vector_t<Bool_t> flags_only_playables_archer = Flags_Only_Playables_Archer();
        Vector_t<Bool_t> flags_only_playables_civilized = Flags_Only_Playables_Civilized();
        Vector_t<Bool_t> flags_only_playables_combatant = Flags_Only_Playables_Combatant();
        Vector_t<Bool_t> flags_only_playables_coward = Flags_Only_Playables_Coward();
        Vector_t<Bool_t> flags_only_playables_dangerous = Flags_Only_Playables_Dangerous();
        Vector_t<Bool_t> flags_only_playables_eater = Flags_Only_Playables_Eater();
        Vector_t<Bool_t> flags_only_playables_exterior = Flags_Only_Playables_Exterior();
        Vector_t<Bool_t> flags_only_playables_follower = Flags_Only_Playables_Follower();
        Vector_t<Bool_t> flags_only_playables_guard = Flags_Only_Playables_Guard();
        Vector_t<Bool_t> flags_only_playables_home = Flags_Only_Playables_Home();
        Vector_t<Bool_t> flags_only_playables_immobile = Flags_Only_Playables_Immobile();
        Vector_t<Bool_t> flags_only_playables_inn = Flags_Only_Playables_Inn();
        Vector_t<Bool_t> flags_only_playables_interior = Flags_Only_Playables_Interior();
        Vector_t<Bool_t> flags_only_playables_mage = Flags_Only_Playables_Mage();
        Vector_t<Bool_t> flags_only_playables_mannequin = Flags_Only_Playables_Mannequin();
        Vector_t<Bool_t> flags_only_playables_member = Flags_Only_Playables_Member();
        Vector_t<Bool_t> flags_only_playables_sandboxer = Flags_Only_Playables_Sandboxer();
        Vector_t<Bool_t> flags_only_playables_settlement = Flags_Only_Playables_Settlement();
        Vector_t<Bool_t> flags_only_playables_sitter = Flags_Only_Playables_Sitter();
        Vector_t<Bool_t> flags_only_playables_sleeper = Flags_Only_Playables_Sleeper();
        Vector_t<Bool_t> flags_only_playables_thrall = Flags_Only_Playables_Thrall();
        Vector_t<Bool_t> flags_only_playables_warrior = Flags_Only_Playables_Warrior();

        this->names = Names();

        this->caches = Caches();
        this->combat_styles = Combat_Styles();
        this->ghost_abilities = Ghost_Abilities();
        this->outfits = Outfits();
        this->packs = Packs();
        this->suitcases = Suitcases().As<Vector_t<maybe<Member_Suitcase_t*>>>();
        this->voice_types = Voice_Types();

        Vector_t<Float_t> alphas = Alphas();
        Vector_t<Int_t> ratings = Ratings();
        Vector_t<String_t> relations = Relations();
        Vector_t<String_t> suit_types = Suit_Types();
        Vector_t<String_t> vitalities = Vitalities();

        this->actors.resize(MAX_MEMBERS);
        this->original_bases.resize(MAX_MEMBERS);

        flags_is_banished.resize(MAX_MEMBERS);
        flags_is_clone.resize(MAX_MEMBERS);
        flags_is_immobile.resize(MAX_MEMBERS);
        flags_is_mannequin.resize(MAX_MEMBERS);
        flags_is_reanimated.resize(MAX_MEMBERS);
        flags_is_thrall.resize(MAX_MEMBERS);

        flags_has_suit_archer.resize(MAX_MEMBERS);
        flags_has_suit_civilized.resize(MAX_MEMBERS);
        flags_has_suit_combatant.resize(MAX_MEMBERS);
        flags_has_suit_coward.resize(MAX_MEMBERS);
        flags_has_suit_dangerous.resize(MAX_MEMBERS);
        flags_has_suit_eater.resize(MAX_MEMBERS);
        flags_has_suit_exterior.resize(MAX_MEMBERS);
        flags_has_suit_follower.resize(MAX_MEMBERS);
        flags_has_suit_guard.resize(MAX_MEMBERS);
        flags_has_suit_home.resize(MAX_MEMBERS);
        flags_has_suit_immobile.resize(MAX_MEMBERS);
        flags_has_suit_inn.resize(MAX_MEMBERS);
        flags_has_suit_interior.resize(MAX_MEMBERS);
        flags_has_suit_mage.resize(MAX_MEMBERS);
        flags_has_suit_mannequin.resize(MAX_MEMBERS);
        flags_has_suit_member.resize(MAX_MEMBERS);
        flags_has_suit_sandboxer.resize(MAX_MEMBERS);
        flags_has_suit_settlement.resize(MAX_MEMBERS);
        flags_has_suit_sitter.resize(MAX_MEMBERS);
        flags_has_suit_sleeper.resize(MAX_MEMBERS);
        flags_has_suit_thrall.resize(MAX_MEMBERS);
        flags_has_suit_warrior.resize(MAX_MEMBERS);

        flags_only_playables_archer.resize(MAX_MEMBERS);
        flags_only_playables_civilized.resize(MAX_MEMBERS);
        flags_only_playables_combatant.resize(MAX_MEMBERS);
        flags_only_playables_coward.resize(MAX_MEMBERS);
        flags_only_playables_dangerous.resize(MAX_MEMBERS);
        flags_only_playables_eater.resize(MAX_MEMBERS);
        flags_only_playables_exterior.resize(MAX_MEMBERS);
        flags_only_playables_follower.resize(MAX_MEMBERS);
        flags_only_playables_guard.resize(MAX_MEMBERS);
        flags_only_playables_home.resize(MAX_MEMBERS);
        flags_only_playables_immobile.resize(MAX_MEMBERS);
        flags_only_playables_inn.resize(MAX_MEMBERS);
        flags_only_playables_interior.resize(MAX_MEMBERS);
        flags_only_playables_mage.resize(MAX_MEMBERS);
        flags_only_playables_mannequin.resize(MAX_MEMBERS);
        flags_only_playables_member.resize(MAX_MEMBERS);
        flags_only_playables_sandboxer.resize(MAX_MEMBERS);
        flags_only_playables_settlement.resize(MAX_MEMBERS);
        flags_only_playables_sitter.resize(MAX_MEMBERS);
        flags_only_playables_sleeper.resize(MAX_MEMBERS);
        flags_only_playables_thrall.resize(MAX_MEMBERS);
        flags_only_playables_warrior.resize(MAX_MEMBERS);

        this->names.resize(MAX_MEMBERS);

        this->caches.resize(MAX_MEMBERS);
        this->combat_styles.resize(MAX_MEMBERS);
        this->ghost_abilities.resize(MAX_MEMBERS);
        this->outfits.resize(MAX_MEMBERS);
        this->packs.resize(MAX_MEMBERS);
        this->suitcases.resize(MAX_MEMBERS);
        this->voice_types.resize(MAX_MEMBERS);

        alphas.resize(MAX_MEMBERS, DEFAULT_ALPHA);
        ratings.resize(MAX_MEMBERS, DEFAULT_RATING);
        relations.resize(MAX_MEMBERS);
        suit_types.resize(MAX_MEMBERS);
        vitalities.resize(MAX_MEMBERS);

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            Member_Flags_e& flags = this->flags[idx];
            flags.Is_Flagged(Member_Flags_e::IS_BANISHED, flags_is_banished[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_CLONE, flags_is_clone[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE, flags_is_immobile[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN, flags_is_mannequin[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_REANIMATED, flags_is_reanimated[idx]);
            flags.Is_Flagged(Member_Flags_e::IS_THRALL, flags_is_thrall[idx]);

            Member_Flags_Has_Suit_e& flags_has_suit = this->flags_has_suit[idx];
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::ARCHER, flags_has_suit_archer[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::CIVILIZED, flags_has_suit_civilized[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::COMBATANT, flags_has_suit_combatant[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::COWARD, flags_has_suit_coward[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::DANGEROUS, flags_has_suit_dangerous[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::EATER, flags_has_suit_eater[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::EXTERIOR, flags_has_suit_exterior[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::FOLLOWER, flags_has_suit_follower[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::GUARD, flags_has_suit_guard[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::HOME, flags_has_suit_home[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::IMMOBILE, flags_has_suit_immobile[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::INN, flags_has_suit_inn[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::INTERIOR, flags_has_suit_interior[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::MAGE, flags_has_suit_mage[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::MANNEQUIN, flags_has_suit_mannequin[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::MEMBER, flags_has_suit_member[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SANDBOXER, flags_has_suit_sandboxer[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SETTLEMENT, flags_has_suit_settlement[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SITTER, flags_has_suit_sitter[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SLEEPER, flags_has_suit_sleeper[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::THRALL, flags_has_suit_thrall[idx]);
            flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::WARRIOR, flags_has_suit_warrior[idx]);

            Member_Flags_Only_Playables_e& flags_only_playables = this->flags_only_playables[idx];
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::ARCHER, flags_only_playables_archer[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::CIVILIZED, flags_only_playables_civilized[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::COMBATANT, flags_only_playables_combatant[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::COWARD, flags_only_playables_coward[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::DANGEROUS, flags_only_playables_dangerous[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::EATER, flags_only_playables_eater[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::EXTERIOR, flags_only_playables_exterior[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::FOLLOWER, flags_only_playables_follower[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::GUARD, flags_only_playables_guard[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::HOME, flags_only_playables_home[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::IMMOBILE, flags_only_playables_immobile[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::INN, flags_only_playables_inn[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::INTERIOR, flags_only_playables_interior[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::MAGE, flags_only_playables_mage[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::MANNEQUIN, flags_only_playables_mannequin[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::MEMBER, flags_only_playables_member[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SANDBOXER, flags_only_playables_sandboxer[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SETTLEMENT, flags_only_playables_settlement[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SITTER, flags_only_playables_sitter[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SLEEPER, flags_only_playables_sleeper[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::THRALL, flags_only_playables_thrall[idx]);
            flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::WARRIOR, flags_only_playables_warrior[idx]);

            this->alphas[idx] = alphas[idx];
            this->ratings[idx] = ratings[idx];
            this->relations[idx] = relations[idx];
            this->suit_types[idx] = suit_types[idx];
            this->vitalities[idx] = vitalities[idx];
        }
    }

    void Members_t::Save_State::Write()
    {
        Vector_t<Bool_t> flags_is_banished(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_is_clone(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_is_immobile(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_is_mannequin(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_is_reanimated(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_is_thrall(MAX_MEMBERS, false);

        Vector_t<Bool_t> flags_has_suit_archer(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_civilized(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_combatant(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_coward(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_dangerous(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_eater(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_exterior(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_follower(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_guard(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_home(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_immobile(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_inn(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_interior(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_mage(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_mannequin(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_member(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_sandboxer(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_settlement(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_sitter(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_sleeper(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_thrall(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_has_suit_warrior(MAX_MEMBERS, false);

        Vector_t<Bool_t> flags_only_playables_archer(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_civilized(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_combatant(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_coward(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_dangerous(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_eater(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_exterior(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_follower(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_guard(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_home(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_immobile(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_inn(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_interior(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_mage(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_mannequin(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_member(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_sandboxer(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_settlement(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_sitter(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_sleeper(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_thrall(MAX_MEMBERS, false);
        Vector_t<Bool_t> flags_only_playables_warrior(MAX_MEMBERS, false);

        Vector_t<Float_t> alphas(MAX_MEMBERS, DEFAULT_ALPHA);
        Vector_t<Int_t> ratings(MAX_MEMBERS, DEFAULT_RATING);
        Vector_t<String_t> relations(MAX_MEMBERS, "");
        Vector_t<String_t> suit_types(MAX_MEMBERS, "");
        Vector_t<String_t> vitalities(MAX_MEMBERS, "");

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (this->actors[idx]) {
                Member_Flags_e flags = this->flags[idx];
                flags_is_banished[idx] = flags.Is_Flagged(Member_Flags_e::IS_BANISHED);
                flags_is_clone[idx] = flags.Is_Flagged(Member_Flags_e::IS_CLONE);
                flags_is_immobile[idx] = flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE);
                flags_is_mannequin[idx] = flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN);
                flags_is_reanimated[idx] = flags.Is_Flagged(Member_Flags_e::IS_REANIMATED);
                flags_is_thrall[idx] = flags.Is_Flagged(Member_Flags_e::IS_THRALL);

                Member_Flags_Has_Suit_e& flags_has_suit = this->flags_has_suit[idx];
                flags_has_suit_archer[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::ARCHER);
                flags_has_suit_civilized[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::CIVILIZED);
                flags_has_suit_combatant[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::COMBATANT);
                flags_has_suit_coward[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::COWARD);
                flags_has_suit_dangerous[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::DANGEROUS);
                flags_has_suit_eater[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::EATER);
                flags_has_suit_exterior[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::EXTERIOR);
                flags_has_suit_follower[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::FOLLOWER);
                flags_has_suit_guard[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::GUARD);
                flags_has_suit_home[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::HOME);
                flags_has_suit_immobile[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::IMMOBILE);
                flags_has_suit_inn[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::INN);
                flags_has_suit_interior[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::INTERIOR);
                flags_has_suit_mage[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::MAGE);
                flags_has_suit_mannequin[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::MANNEQUIN);
                flags_has_suit_member[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::MEMBER);
                flags_has_suit_sandboxer[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SANDBOXER);
                flags_has_suit_settlement[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SETTLEMENT);
                flags_has_suit_sitter[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SITTER);
                flags_has_suit_sleeper[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::SLEEPER);
                flags_has_suit_thrall[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::THRALL);
                flags_has_suit_warrior[idx] = flags_has_suit.Is_Flagged(Member_Flags_Has_Suit_e::WARRIOR);

                Member_Flags_Only_Playables_e& flags_only_playables = this->flags_only_playables[idx];
                flags_only_playables_archer[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::ARCHER);
                flags_only_playables_civilized[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::CIVILIZED);
                flags_only_playables_combatant[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::COMBATANT);
                flags_only_playables_coward[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::COWARD);
                flags_only_playables_dangerous[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::DANGEROUS);
                flags_only_playables_eater[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::EATER);
                flags_only_playables_exterior[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::EXTERIOR);
                flags_only_playables_follower[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::FOLLOWER);
                flags_only_playables_guard[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::GUARD);
                flags_only_playables_home[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::HOME);
                flags_only_playables_immobile[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::IMMOBILE);
                flags_only_playables_inn[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::INN);
                flags_only_playables_interior[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::INTERIOR);
                flags_only_playables_mage[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::MAGE);
                flags_only_playables_mannequin[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::MANNEQUIN);
                flags_only_playables_member[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::MEMBER);
                flags_only_playables_sandboxer[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SANDBOXER);
                flags_only_playables_settlement[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SETTLEMENT);
                flags_only_playables_sitter[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SITTER);
                flags_only_playables_sleeper[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::SLEEPER);
                flags_only_playables_thrall[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::THRALL);
                flags_only_playables_warrior[idx] = flags_only_playables.Is_Flagged(Member_Flags_Only_Playables_e::WARRIOR);

                alphas[idx] = this->alphas[idx]();
                ratings[idx] = this->ratings[idx]();
                relations[idx] = this->relations[idx]().As_String();
                suit_types[idx] = this->suit_types[idx]().As_String();
                vitalities[idx] = this->vitalities[idx]().As_String();
            }
        }

        Limit() = this->limit;

        Fill_Suit_Aura_Probability() = static_cast<Int_t>(this->fill_suit_aura_probability);
        Fill_Suit_Body_Probability() = static_cast<Int_t>(this->fill_suit_body_probability);
        Fill_Suit_Feet_Probability() = static_cast<Int_t>(this->fill_suit_feet_probability);
        Fill_Suit_Finger_Probability() = static_cast<Int_t>(this->fill_suit_finger_probability);
        Fill_Suit_Forearm_Probability() = static_cast<Int_t>(this->fill_suit_forearm_probability);
        Fill_Suit_Forehead_Probability() = static_cast<Int_t>(this->fill_suit_forehead_probability);
        Fill_Suit_Hands_Probability() = static_cast<Int_t>(this->fill_suit_hands_probability);
        Fill_Suit_Head_Probability() = static_cast<Int_t>(this->fill_suit_head_probability);
        Fill_Suit_Neck_Probability() = static_cast<Int_t>(this->fill_suit_neck_probability);

        Do_Auto_Suits() = this->do_auto_suits;
        Do_Fill_Suits() = this->do_fill_suits;
        Do_Fill_Suits_Automatically() = this->do_fill_suits_automatically;
        Do_Fill_Suits_Strictly() = this->do_fill_suits_strictly;
        Do_Unfill_Suits_To_Pack() = this->do_unfill_suits_to_pack;

        Has_Untouchable_Invulnerables() = this->has_untouchable_invulnerables;

        Default_Combat_Style() = this->default_combat_style().As_String();
        Default_Relation() = this->default_relation().As_String();
        Default_Suit_Type() = this->default_suit_type().As_String();
        Default_Vitality() = this->default_vitality().As_String();

        Member_Suit_Fill_Type() = this->member_suit_fill_type().As_String();
        Sort_Type() = this->sort_type().As_String();

        Actors() = this->actors;
        Original_Bases() = this->original_bases;

        Flags_Is_Banished() = flags_is_banished;
        Flags_Is_Clone() = flags_is_clone;
        Flags_Is_Immobile() = flags_is_immobile;
        Flags_Is_Mannequin() = flags_is_mannequin;
        Flags_Is_Reanimated() = flags_is_reanimated;
        Flags_Is_Thrall() = flags_is_thrall;

        Flags_Has_Suit_Archer() = flags_has_suit_archer;
        Flags_Has_Suit_Civilized() = flags_has_suit_civilized;
        Flags_Has_Suit_Combatant() = flags_has_suit_combatant;
        Flags_Has_Suit_Coward() = flags_has_suit_coward;
        Flags_Has_Suit_Dangerous() = flags_has_suit_dangerous;
        Flags_Has_Suit_Eater() = flags_has_suit_eater;
        Flags_Has_Suit_Exterior() = flags_has_suit_exterior;
        Flags_Has_Suit_Follower() = flags_has_suit_follower;
        Flags_Has_Suit_Guard() = flags_has_suit_guard;
        Flags_Has_Suit_Home() = flags_has_suit_home;
        Flags_Has_Suit_Immobile() = flags_has_suit_immobile;
        Flags_Has_Suit_Inn() = flags_has_suit_inn;
        Flags_Has_Suit_Interior() = flags_has_suit_interior;
        Flags_Has_Suit_Mage() = flags_has_suit_mage;
        Flags_Has_Suit_Mannequin() = flags_has_suit_mannequin;
        Flags_Has_Suit_Member() = flags_has_suit_member;
        Flags_Has_Suit_Sandboxer() = flags_has_suit_sandboxer;
        Flags_Has_Suit_Settlement() = flags_has_suit_settlement;
        Flags_Has_Suit_Sitter() = flags_has_suit_sitter;
        Flags_Has_Suit_Sleeper() = flags_has_suit_sleeper;
        Flags_Has_Suit_Thrall() = flags_has_suit_thrall;
        Flags_Has_Suit_Warrior() = flags_has_suit_warrior;

        Flags_Only_Playables_Archer() = flags_only_playables_archer;
        Flags_Only_Playables_Civilized() = flags_only_playables_civilized;
        Flags_Only_Playables_Combatant() = flags_only_playables_combatant;
        Flags_Only_Playables_Coward() = flags_only_playables_coward;
        Flags_Only_Playables_Dangerous() = flags_only_playables_dangerous;
        Flags_Only_Playables_Eater() = flags_only_playables_eater;
        Flags_Only_Playables_Exterior() = flags_only_playables_exterior;
        Flags_Only_Playables_Follower() = flags_only_playables_follower;
        Flags_Only_Playables_Guard() = flags_only_playables_guard;
        Flags_Only_Playables_Home() = flags_only_playables_home;
        Flags_Only_Playables_Immobile() = flags_only_playables_immobile;
        Flags_Only_Playables_Inn() = flags_only_playables_inn;
        Flags_Only_Playables_Interior() = flags_only_playables_interior;
        Flags_Only_Playables_Mage() = flags_only_playables_mage;
        Flags_Only_Playables_Mannequin() = flags_only_playables_mannequin;
        Flags_Only_Playables_Member() = flags_only_playables_member;
        Flags_Only_Playables_Sandboxer() = flags_only_playables_sandboxer;
        Flags_Only_Playables_Settlement() = flags_only_playables_settlement;
        Flags_Only_Playables_Sitter() = flags_only_playables_sitter;
        Flags_Only_Playables_Sleeper() = flags_only_playables_sleeper;
        Flags_Only_Playables_Thrall() = flags_only_playables_thrall;
        Flags_Only_Playables_Warrior() = flags_only_playables_warrior;

        Names() = this->names;

        Caches() = this->caches;
        Combat_Styles() = this->combat_styles;
        Ghost_Abilities() = this->ghost_abilities;
        Outfits() = this->outfits;
        Packs() = this->packs;
        Suitcases() = reinterpret_cast<Vector_t<maybe<Reference_t*>>&>(this->suitcases);
        Voice_Types() = this->voice_types;

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

    Members_t::Members_t(some<Quest_t*> quest, Bool_t is_new_game) :
        quest(quest),
        save_state(quest),
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
        vanilla_ghost_abilities(skylib::Const::Spells::Ghost_Abilities())
    {
        SKYLIB_ASSERT_SOME(quest);

        if (is_new_game) {
            Do_Allow_Menu_For_All_Actors(true);

            Do_Force_Clone_Uniques(false);
            Do_Force_Clone_Generics(false);
            Do_Force_Unclone_Uniques(false);
            Do_Force_Unclone_Generics(false);
        } else {
            this->save_state.Read();

            Validate();
        }
    }

    Members_t::Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        save_state(quest),
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),
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
    }

    void Members_t::Before_Save()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            if (Enforce(idx)) {
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

    Main_t& Members_t::Main()
    {
        return NPCP.Main().Party();
    }

    u8 Members_t::Fill_Suit_Aura_Probability()
    {
        return this->save_state.fill_suit_aura_probability;
    }

    void Members_t::Fill_Suit_Aura_Probability(u8 value)
    {
        this->save_state.fill_suit_aura_probability = value;
    }

    u8 Members_t::Fill_Suit_Body_Probability()
    {
        return this->save_state.fill_suit_body_probability;
    }

    void Members_t::Fill_Suit_Body_Probability(u8 value)
    {
        this->save_state.fill_suit_body_probability = value;
    }

    u8 Members_t::Fill_Suit_Feet_Probability()
    {
        return this->save_state.fill_suit_feet_probability;
    }

    void Members_t::Fill_Suit_Feet_Probability(u8 value)
    {
        this->save_state.fill_suit_feet_probability = value;
    }

    u8 Members_t::Fill_Suit_Finger_Probability()
    {
        return this->save_state.fill_suit_finger_probability;
    }

    void Members_t::Fill_Suit_Finger_Probability(u8 value)
    {
        this->save_state.fill_suit_finger_probability = value;
    }

    u8 Members_t::Fill_Suit_Forearm_Probability()
    {
        return this->save_state.fill_suit_forearm_probability;
    }

    void Members_t::Fill_Suit_Forearm_Probability(u8 value)
    {
        this->save_state.fill_suit_forearm_probability = value;
    }

    u8 Members_t::Fill_Suit_Forehead_Probability()
    {
        return this->save_state.fill_suit_forehead_probability;
    }

    void Members_t::Fill_Suit_Forehead_Probability(u8 value)
    {
        this->save_state.fill_suit_forehead_probability = value;
    }

    u8 Members_t::Fill_Suit_Hands_Probability()
    {
        return this->save_state.fill_suit_hands_probability;
    }

    void Members_t::Fill_Suit_Hands_Probability(u8 value)
    {
        this->save_state.fill_suit_hands_probability = value;
    }

    u8 Members_t::Fill_Suit_Head_Probability()
    {
        return this->save_state.fill_suit_head_probability;
    }

    void Members_t::Fill_Suit_Head_Probability(u8 value)
    {
        this->save_state.fill_suit_head_probability = value;
    }

    u8 Members_t::Fill_Suit_Neck_Probability()
    {
        return this->save_state.fill_suit_neck_probability;
    }

    void Members_t::Fill_Suit_Neck_Probability(u8 value)
    {
        this->save_state.fill_suit_neck_probability = value;
    }

    void Members_t::Reset_Fill_Suit_Probabilities()
    {
        Fill_Suit_Aura_Probability(DEFAULT_FILL_SUIT_AURA_PROBABILITY);
        Fill_Suit_Body_Probability(DEFAULT_FILL_SUIT_BODY_PROBABILITY);
        Fill_Suit_Feet_Probability(DEFAULT_FILL_SUIT_FEET_PROBABILITY);
        Fill_Suit_Finger_Probability(DEFAULT_FILL_SUIT_FINGER_PROBABILITY);
        Fill_Suit_Forearm_Probability(DEFAULT_FILL_SUIT_FOREARM_PROBABILITY);
        Fill_Suit_Forehead_Probability(DEFAULT_FILL_SUIT_FOREHEAD_PROBABILITY);
        Fill_Suit_Hands_Probability(DEFAULT_FILL_SUIT_HANDS_PROBABILITY);
        Fill_Suit_Head_Probability(DEFAULT_FILL_SUIT_HEAD_PROBABILITY);
        Fill_Suit_Neck_Probability(DEFAULT_FILL_SUIT_NECK_PROBABILITY);
    }

    Bool_t Members_t::Do_Fill_Suits_Automatically()
    {
        return this->save_state.do_fill_suits_automatically;
    }

    void Members_t::Do_Fill_Suits_Automatically(Bool_t value)
    {
        this->save_state.do_fill_suits_automatically = value;
    }

    Bool_t Members_t::Do_Fill_Suits_Strictly()
    {
        return this->save_state.do_fill_suits_strictly;
    }

    void Members_t::Do_Fill_Suits_Strictly(Bool_t value)
    {
        this->save_state.do_fill_suits_strictly = value;
    }

    Bool_t Members_t::Do_Unfill_Suits_To_Pack()
    {
        return this->save_state.do_unfill_suits_to_pack;
    }

    void Members_t::Do_Unfill_Suits_To_Pack(Bool_t value)
    {
        this->save_state.do_unfill_suits_to_pack = value;
    }

    Bool_t Members_t::Has_Untouchable_Invulnerables()
    {
        return this->save_state.has_untouchable_invulnerables;
    }

    void Members_t::Has_Untouchable_Invulnerables(Bool_t value)
    {
        this->save_state.has_untouchable_invulnerables = value;
    }

    maybe<Member_Suit_Type_e> Members_t::Default_Suit_Type()
    {
        return this->save_state.default_suit_type;
    }

    void Members_t::Default_Suit_Type(maybe<Member_Suit_Type_e> suit_type)
    {
        SKYLIB_ASSERT(suit_type != Member_Suit_Type_e::ACTIVE);

        this->save_state.default_suit_type = suit_type;
    }

    Bool_t Members_t::Has_Alias(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        return this->quest->Has_Alias_Index(member_id());
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

    static void Add_Member(some<Members_t*> self, Member_ID_t member_id, some<Actor_t*> actor, some<Actor_Base_t*> base)
    {
        SKYLIB_ASSERT_SOME(self);
        SKYLIB_ASSERT_SOME(actor);
        SKYLIB_ASSERT_SOME(base);

        self->save_state.actors[member_id] = actor();
        self->save_state.original_bases[member_id] = base();

        // do we handle flags here also?

        self->save_state.names[member_id] = actor->Name();

        self->save_state.caches[member_id] = none<Reference_t*>();
        self->save_state.combat_styles[member_id] = self->save_state.default_combat_style();
        self->save_state.ghost_abilities[member_id] = none<Spell_t*>(); // maybe should look at actor for any acceptable ability
        self->save_state.outfits[member_id] = base->Default_Outfit();
        self->save_state.packs[member_id] = none<Reference_t*>();
        self->save_state.suitcases[member_id] = none<Member_Suitcase_t*>();
        self->save_state.voice_types[member_id] = none<Voice_Type_t*>(); // we need to have 2 defaults: male/female

        // so the member_suit_fill_type determines whether we use a ref or a base to fill the member suit.
        // with a clone, that ref should be the original actor. when we clone, we could just copy all the items onto clone first

        self->save_state.alphas[member_id] = Members_t::DEFAULT_ALPHA;
        self->save_state.ratings[member_id] = Members_t::DEFAULT_RATING;
        self->save_state.relations[member_id] = self->save_state.default_relation;
        self->save_state.suit_types[member_id] = self->save_state.default_suit_type;
        self->save_state.vitalities[member_id] = self->save_state.default_vitality;

        // we can just do member suit by base for clone.
        maybe<Member_Suit_Type_e> default_suit_type = self->Default_Suit_Type();
        if (self->Do_Fill_Suits_Automatically()) {
            self->Add_Suit(member_id, Member_Suit_Type_e::MEMBER, actor, false);
            if (default_suit_type && default_suit_type != Member_Suit_Type_e::MEMBER) {
                self->Add_Suit(member_id, default_suit_type(), default_suit_type().As_Template());
            }
        } else {
            self->Add_Suit(member_id, Member_Suit_Type_e::MEMBER);
            if (default_suit_type && default_suit_type != Member_Suit_Type_e::MEMBER) {
                self->Add_Suit(member_id, default_suit_type());
            }
        }

        self->Alias_Reference(member_id)->Fill(actor, none<V::Callback_i*>());
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
                    Party::Add_Member(this, member_id(), actor(), base());
                    this->save_state.flags[member_id()].Flag(Member_Flags_e::IS_CLONE);
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

    Bool_t Members_t::Remove_Member(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        // this will cleanse anything under the id that it can, even if the data is incomplete in some manner, it cleans it up.
        // it fails gracefully and just defaults the values.

        // also, this must destroy the custom base so it's created again for the next actor

        // this should forcibly reset ai and make sure other state is reset that is needed.
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
                Alias_Reference(idx)->Fill(Actor(idx), none<V::Callback_i*>());
            } else {
                Remove_Member(idx);
            }
        }
    }

    some<Alias_Reference_t*> Members_t::Alias_Reference(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        some<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(valid_member_id())();
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

    some<Actor_Base_t*> Members_t::Original_Base(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        some<Actor_Base_t*> original_base = this->save_state.original_bases[valid_member_id()]();
        SKYLIB_ASSERT_SOME(original_base);
        return original_base;
    }

    some<Actor_Base_t*> Members_t::Custom_Base(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Actor_Base_t*>& custom_base = this->custom_bases[valid_member_id()];
        if (!custom_base) {
            custom_base = Actor_Base_t::Create_Temporary_Copy(Original_Base(valid_member_id))();
            custom_base->Default_Outfit(Outfit(valid_member_id));
            SKYLIB_ASSERT_SOME(custom_base);
        }

        return custom_base();
    }

    Bool_t Members_t::Is_Banished(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_BANISHED);
    }

    void Members_t::Is_Banished(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_BANISHED, value);
    }

    Bool_t Members_t::Is_Clone(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_CLONE);
    }

    void Members_t::Is_Clone(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_CLONE, value);
    }

    Bool_t Members_t::Is_Immobile(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_IMMOBILE);
    }

    void Members_t::Is_Immobile(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_IMMOBILE, value);
    }

    Bool_t Members_t::Is_Mannequin(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_MANNEQUIN);
    }

    void Members_t::Is_Mannequin(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_MANNEQUIN, value);
    }

    Bool_t Members_t::Is_Reanimated(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_REANIMATED);
    }

    void Members_t::Is_Reanimated(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_REANIMATED, value);
    }

    Bool_t Members_t::Is_Thrall(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_THRALL);
    }

    void Members_t::Is_Thrall(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.flags[valid_member_id()].Is_Flagged(Member_Flags_e::IS_THRALL, value);
    }

    Bool_t Members_t::Has_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Has_Suit_e flag = type().As_Member_Flag_Has_Suit();
        SKYLIB_ASSERT_SOME(flag);

        return this->save_state.flags_has_suit[valid_id()].Is_Flagged(flag);
    }

    void Members_t::Has_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Has_Suit_e flag = type().As_Member_Flag_Has_Suit();
        SKYLIB_ASSERT_SOME(flag);

        this->save_state.flags_has_suit[valid_id()].Is_Flagged(flag, value);
    }

    Bool_t Members_t::Only_Playables(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Only_Playables_e flag = type().As_Member_Flag_Only_Playables();
        SKYLIB_ASSERT_SOME(flag);

        return this->save_state.flags_only_playables[valid_id()].Is_Flagged(flag);
    }

    void Members_t::Only_Playables(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Only_Playables_e flag = type().As_Member_Flag_Only_Playables();
        SKYLIB_ASSERT_SOME(flag);

        this->save_state.flags_only_playables[valid_id()].Is_Flagged(flag, value);
    }

    String_t Members_t::Name(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        String_t name = this->save_state.names[valid_member_id()];
        if (!name) {
            name = Original_Base(valid_member_id)->Name();
        }

        return name;
    }

    void Members_t::Name(some<Member_ID_t> valid_member_id, String_t name)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.names[valid_member_id()] = name;
    }

    some<Reference_t*> Members_t::Cache(some<Member_ID_t> valid_id)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Has_Member(valid_id));

        maybe<Reference_t*>& cache = this->save_state.caches[valid_id()];
        if (!cache) {
            cache = Container_t::Create_Reference(
                Consts_t::NPCP::Container::Empty(),
                Consts_t::NPCP::Reference::Storage_Marker()
            )();
            SKYLIB_ASSERT_SOME(cache);
        }

        return cache();
    }

    maybe<Combat_Style_t*> Members_t::Combat_Style(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Combat_Style_t*> combat_style = this->save_state.combat_styles[valid_member_id()];
        if (!combat_style) {
            combat_style = Original_Base(valid_member_id)->Combat_Style();
        }

        return combat_style;
    }

    void Members_t::Combat_Style(some<Member_ID_t> valid_member_id, maybe<Combat_Style_t*> combat_style)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.combat_styles[valid_member_id()] = combat_style;
    }

    void Members_t::Combat_Style(some<Member_ID_t> valid_member_id, Member_Combat_Style_e combat_style)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Combat_Style(valid_member_id, combat_style.As_Combat_Style());
    }

    maybe<Spell_t*> Members_t::Ghost_Ability(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.ghost_abilities[valid_member_id()];
    }

    void Members_t::Ghost_Ability(some<Member_ID_t> valid_member_id, maybe<Spell_t*> ghost_ability)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.ghost_abilities[valid_member_id()] = ghost_ability;
    }

    maybe<Outfit_t*> Members_t::Outfit(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.outfits[valid_member_id()];
    }

    void Members_t::Outfit(some<Member_ID_t> valid_member_id, maybe<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.outfits[valid_member_id()] = outfit;
    }

    some<Reference_t*> Members_t::Pack(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Reference_t*>& pack = this->save_state.packs[valid_member_id()];
        if (!pack) {
            pack = Container_t::Create_Reference(
                Consts_t::NPCP::Container::Empty(),
                Consts_t::NPCP::Reference::Storage_Marker()
            )();
            SKYLIB_ASSERT_SOME(pack);
        }

        return pack();
    }

    some<Member_Suitcase_t*> Members_t::Suitcase(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Member_Suitcase_t*>& suitcase = this->save_state.suitcases[valid_member_id()];
        if (!suitcase) {
            suitcase = Member_Suitcase_t::Create()();
            SKYLIB_ASSERT_SOME(suitcase);
        }

        return suitcase();
    }

    some<Voice_Type_t*> Members_t::Voice_Type(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Voice_Type_t*> voice_type = this->save_state.voice_types[valid_member_id()];
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

    void Members_t::Voice_Type(some<Member_ID_t> valid_member_id, maybe<Voice_Type_t*> voice_type)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.voice_types[valid_member_id()] = voice_type;
    }

    maybe<Member_Alpha_t> Members_t::Alpha(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        if (!Is_Enabled(valid_member_id)) {
            return 0.0f;
        } else {
            return this->save_state.alphas[valid_member_id()];
        }
    }

    void Members_t::Alpha(some<Member_ID_t> valid_member_id, maybe<Member_Alpha_t> alpha)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.alphas[valid_member_id()] = alpha;
    }

    maybe<Member_Rating_t> Members_t::Rating(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return this->save_state.ratings[valid_member_id()];
    }

    void Members_t::Rating(some<Member_ID_t> valid_member_id, maybe<Member_Rating_t> rating)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.ratings[valid_member_id()] = rating;
    }

    some<Member_Relation_e> Members_t::Relation(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Member_Relation_e> relation = this->save_state.relations[valid_member_id()];
        if (!relation) {
            relation = Original_Base(valid_member_id)->Relation(skylib::Const::Actor_Base::Player());
        }

        SKYLIB_ASSERT_SOME(relation);

        return relation();
    }

    void Members_t::Relation(some<Member_ID_t> valid_member_id, maybe<Member_Relation_e> relation)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.relations[valid_member_id()] = relation;
    }

    maybe<Member_Suit_Type_e> Members_t::Suit_Type(some<Member_ID_t> valid_id)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Has_Member(valid_id));

        // this should calculate the suit type by precedence and whether or not auto-outfitting for this member is enabled.

        return this->save_state.suit_types[valid_id()];
    }

    void Members_t::Suit_Type(some<Member_ID_t> valid_id, maybe<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT(Has_Member(valid_id));

        if (type) {
            SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
            SKYLIB_ASSERT(Has_Suit(valid_id, type()));
            this->save_state.suit_types[valid_id()] = type;
        } else {
            this->save_state.suit_types[valid_id()] = none<Member_Suit_Type_e>();
        }
    }

    some<Member_Vitality_e> Members_t::Vitality(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        maybe<Member_Vitality_e> vitality = this->save_state.vitalities[valid_member_id()];
        if (!vitality) {
            vitality = Original_Base(valid_member_id)->Vitality();
        }

        SKYLIB_ASSERT_SOME(vitality);

        return vitality();
    }

    void Members_t::Vitality(some<Member_ID_t> valid_member_id, maybe<Member_Vitality_e> vitality)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        this->save_state.vitalities[valid_member_id()] = vitality;
    }

    Bool_t Members_t::Is_Mortal(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::MORTAL;
    }

    void Members_t::Is_Mortal(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::MORTAL);
    }

    Bool_t Members_t::Is_Protected(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::PROTECTED;
    }

    void Members_t::Is_Protected(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::PROTECTED);
    }

    Bool_t Members_t::Is_Essential(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::ESSENTIAL;
    }

    void Members_t::Is_Essential(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::ESSENTIAL);
    }

    Bool_t Members_t::Is_Invulnerable(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return Vitality(valid_member_id) == Member_Vitality_e::INVULNERABLE;
    }

    void Members_t::Is_Invulnerable(some<Member_ID_t> valid_member_id, Bool_t value)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        Vitality(valid_member_id, Member_Vitality_e::INVULNERABLE);
    }

    Bool_t Members_t::Is_Enabled(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return
            !Is_Banished(valid_member_id);
    }

    Bool_t Members_t::Is_Untouchable(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return
            (Has_Untouchable_Invulnerables() && Is_Invulnerable(valid_member_id));
    }

    Bool_t Members_t::Has_AI(some<Member_ID_t> valid_member_id)
    {
        SKYLIB_ASSERT_SOME(valid_member_id);
        SKYLIB_ASSERT(Has_Member(valid_member_id));

        return
            !Is_Banished(valid_member_id) &&
            !Is_Mannequin(valid_member_id);
    }

    void Members_t::Add_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(valid_id, type);
        Has_Suit(valid_id, type, true);
    }

    void Members_t::Add_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type, some<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT_SOME(outfit);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(valid_id, type);
        Has_Suit(valid_id, type, true);

        some<Reference_t*> cache = Cache(valid_id);
        outfit->Add_Items_To(cache);
        Suitcase(valid_id)->Move_From(cache,
                                      type,
                                      Member_Suitcase_t::filter_out_blank_or_token_objects,
                                      Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Members_t::Add_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type, some<Container_t*> container)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT_SOME(container);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(valid_id, type);
        Has_Suit(valid_id, type, true);

        some<Reference_t*> cache = Cache(valid_id);
        container->Container_Add_Items_To(cache);
        Suitcase(valid_id)->Move_From(cache,
                                      type,
                                      Member_Suitcase_t::filter_out_blank_or_token_objects,
                                      Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Members_t::Add_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type, some<Actor_Base_t*> actor_base)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT_SOME(actor_base);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(valid_id, type);
        Has_Suit(valid_id, type, true);

        some<Reference_t*> cache = Cache(valid_id);
        maybe<Outfit_t*> outfit = actor_base->Default_Outfit();
        actor_base->Container_Add_Items_To(cache);
        if (outfit) {
            outfit->Add_Items_To(cache);
        }
        Suitcase(valid_id)->Move_From(cache,
                                      type,
                                      Member_Suitcase_t::filter_out_blank_or_token_objects,
                                      Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Members_t::Add_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type, Member_Suit_Template_t suit_template)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(valid_id, type);
        Has_Suit(valid_id, type, true);

        some<Reference_t*> cache = Cache(valid_id);

        maybe<Armor_t*> aura = suit_template.armor.Aura(Fill_Suit_Aura_Probability());
        maybe<Armor_t*> body = suit_template.armor.Body(Fill_Suit_Body_Probability());
        maybe<Armor_t*> feet = suit_template.armor.Feet(Fill_Suit_Feet_Probability());
        maybe<Armor_t*> finger = suit_template.armor.Finger(Fill_Suit_Finger_Probability());
        maybe<Armor_t*> forearm = suit_template.armor.Forearm(Fill_Suit_Forearm_Probability());
        maybe<Armor_t*> forehead = suit_template.armor.Forehead(Fill_Suit_Forehead_Probability());
        maybe<Armor_t*> hands = suit_template.armor.Hands(Fill_Suit_Hands_Probability());
        maybe<Armor_t*> head = suit_template.armor.Head(Fill_Suit_Head_Probability());
        maybe<Armor_t*> neck = suit_template.armor.Neck(Fill_Suit_Neck_Probability());

        if (aura) cache->Add_Item(aura(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (body) cache->Add_Item(body(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (feet) cache->Add_Item(feet(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (finger) cache->Add_Item(finger(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (forearm) cache->Add_Item(forearm(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (forehead) cache->Add_Item(forehead(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (hands) cache->Add_Item(hands(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (head) cache->Add_Item(head(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (neck) cache->Add_Item(neck(), none<Extra_List_t*>(), 1, none<Reference_t*>());

        for (size_t idx = 0, end = suit_template.weapons.size(); idx < end; idx += 1) {
            cache->Add_Item(suit_template.weapons[idx], none<Extra_List_t*>(), 1, none<Reference_t*>());
        }

        if (suit_template.ammo) {
            cache->Add_Item(suit_template.ammo(), none<Extra_List_t*>(), 100, none<Reference_t*>());
        }

        Suitcase(valid_id)->Move_From(cache,
                                      type,
                                      Member_Suitcase_t::filter_out_blank_or_token_objects,
                                      Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Members_t::Add_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type, some<Reference_t*> reference, Bool_t do_copy)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT_SOME(reference);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(valid_id, type);
        Has_Suit(valid_id, type, true);

        if (do_copy) {
            Suitcase(valid_id)->Copy_From(reference,
                                          type,
                                          Member_Suitcase_t::filter_out_blank_or_token_objects,
                                          Member_Suitcase_t::filter_out_no_extra_lists);
        } else {
            Suitcase(valid_id)->Move_From(reference,
                                          type,
                                          Member_Suitcase_t::filter_out_blank_or_token_objects,
                                          Member_Suitcase_t::filter_out_quest_extra_lists);
        }
    }

    void Members_t::Remove_Suit(some<Member_ID_t> valid_id, some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT_SOME(valid_id);
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(Has_Member(valid_id));
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        if (Has_Suit(valid_id, type)) {
            Suitcase(valid_id)->Remove_Suit(Do_Unfill_Suits_To_Pack() ? Pack(valid_id)() : none<Reference_t*>()(), type);
            Has_Suit(valid_id, type, false);
        }
    }

    Bool_t Members_t::Enforce(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        // we may want a different smaller branch if the actor is in combat, or a separate func to call

        if (Has_Member(member_id)) {
            Main_t& main = Main();
            some<Actor_t*> actor = Actor(member_id);
            some<Actor_Base_t*> custom_base = Custom_Base(member_id);

            Vector_t<some<Spell_t*>> spells_to_add;
            spells_to_add.reserve(4);

            actor->Actor_Base(Custom_Base(member_id), false);

            main.Tokenize(member_id, Consts_t::NPCP::Misc::Token::Member(), member_id() + 1);
            actor->Faction_Rank(Consts_t::NPCP::Faction::Member(), 0);

            if (Is_Banished(member_id)) {
                main.Tokenize(member_id, Consts_t::NPCP::Misc::Token::Banished());
            } else {
                main.Untokenize(member_id, Consts_t::NPCP::Misc::Token::Banished());
            }

            if (Is_Immobile(member_id)) {
                main.Tokenize(member_id, Consts_t::NPCP::Misc::Token::Immobile());
            } else {
                main.Untokenize(member_id, Consts_t::NPCP::Misc::Token::Immobile());
            }

            if (Is_Reanimated(member_id)) {
                main.Tokenize(member_id, Consts_t::NPCP::Misc::Token::Reanimated());

                spells_to_add.push_back(Consts_t::NPCP::Spell::Reanimate_Ability());
            } else {
                main.Untokenize(member_id, Consts_t::NPCP::Misc::Token::Reanimated());

                actor->Remove_Spell(Consts_t::NPCP::Spell::Reanimate_Ability());
            }

            if (Is_Thrall(member_id)) {
                main.Tokenize(member_id, Consts_t::NPCP::Misc::Token::Thrall());
            } else {
                main.Untokenize(member_id, Consts_t::NPCP::Misc::Token::Thrall());
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

            maybe<Outfit_t*> outfit = Outfit(member_id);
            maybe<Outfit_t*> custom_outfit = custom_base->Default_Outfit();
            if (outfit != custom_outfit) {
                Outfit(member_id, custom_outfit);
            }

            maybe<Member_Suit_Type_e> suit_type = Suit_Type(member_id);
            if (suit_type) {
                some<Member_Suitcase_t*> suitcase = Suitcase(member_id);
                if (suitcase->Has_Inactive_Outfit_Item(actor)) {
                    // we need to have either a global option or member option here, to initiate the auto-change
                    Suit_Type(member_id, none<Member_Suit_Type_e>());
                    suit_type = none<Member_Suit_Type_e>();
                }
                if (suit_type) {
                    if (Only_Playables(member_id, suit_type())) {
                        suitcase->Apply_Unto(actor,
                                             suit_type(),
                                             Member_Suitcase_t::filter_out_blank_or_token_or_unplayable_objects,
                                             Do_Fill_Suits_Strictly(),
                                             Do_Unfill_Suits_To_Pack() ? Pack(member_id)() : none<Reference_t*>()());
                    } else {
                        suitcase->Apply_Unto(actor,
                                             suit_type(),
                                             Member_Suitcase_t::filter_out_blank_or_token_objects,
                                             Do_Fill_Suits_Strictly(),
                                             Do_Unfill_Suits_To_Pack() ? Pack(member_id)() : none<Reference_t*>()());
                    }
                }
            }

            custom_base->Voice_Type(Voice_Type(member_id)());

            actor->Alpha(Alpha(member_id)(), main.Script(member_id));

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
                    main.Update_AI(member_id, Member_Update_AI_e::RESET_AI);
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
                    main.Update_AI(member_id, Member_Update_AI_e::RESET_AI);
                }
            }

            return true;
        } else {
            Remove_Member(member_id);

            return false;
        }
    }

}}
