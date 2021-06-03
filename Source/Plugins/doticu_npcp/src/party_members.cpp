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
#include "doticu_skylib/cell.h"
#include "doticu_skylib/combat_style.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_actor_bases.h"
#include "doticu_skylib/const_factions.h"
#include "doticu_skylib/const_spells.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/global.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/voice_type.h"
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

        do_change_suits_automatically(DEFAULT_DO_CHANGE_SUITS_AUTOMATICALLY),
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

        locks(Vector_t<std::mutex>(MAX_MEMBERS)),
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
        }
    }

    Members_t::Members_t(some<Quest_t*> quest, const Version_t<u16> version_to_update) :
        quest(quest),
        save_state(quest),

        locks(Vector_t<std::mutex>(MAX_MEMBERS)),
        custom_bases(Vector_t<maybe<Actor_Base_t*>>(MAX_MEMBERS)),

        vanilla_ghost_abilities(skylib::Const::Spells::Ghost_Abilities())
    {
        // update code goes here

        this->save_state.Read();
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
            Member_t member(idx);
            if (member) {
                member.Enforce();
                member.Actor()->Actor_Base(member.Original_Base(), false);
            }
        }
        this->save_state.Write();
    }

    void Members_t::After_Save()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            Member_t member(idx);
            if (member) {
                member.Actor()->Actor_Base(member.Custom_Base(), false);
            }
        }
    }

    void Members_t::Validate()
    {
        if (!this->save_state.limit) {
            this->save_state.limit = Member_Limit_t::_MAX_;
        } else {
            size_t member_count = Member_Count();
            if (this->save_state.limit() < member_count) {
                this->save_state.limit = member_count;
            }
        }

        if (!this->save_state.member_suit_fill_type) {
            this->save_state.member_suit_fill_type = DEFAULT_MEMBER_SUIT_FILL_TYPE;
        }

        if (!this->save_state.sort_type) {
            this->save_state.sort_type = DEFAULT_SORT_TYPE;
        }

        class Unfill_Aliases_Callback :
            public Callback_i<>
        {
        public:
            Members_t& self;

        public:
            Unfill_Aliases_Callback(Members_t& self) :
                self(self)
            {
            }

        public:
            virtual void operator ()() override
            {
                for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
                    Member_t member(idx);
                    if (member) {
                        this->self.Alias_Reference(idx)->Fill(member.Actor(), none<V::Callback_i*>());
                    } else {
                        this->self.Remove_Member(idx);
                    }
                }
            }
        };
        this->quest->Unfill_Aliases(new Unfill_Aliases_Callback(*this));
    }

    Main_t& Members_t::Main()
    {
        return NPCP.Main().Party();
    }

    some<Member_Limit_t> Members_t::Limit()
    {
        return this->save_state.limit;
    }

    void Members_t::Limit(some<Member_Limit_t> value)
    {
        SKYLIB_ASSERT_SOME(value);
        SKYLIB_ASSERT(value() >= Member_Count());

        this->save_state.limit = value;
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

    Bool_t Members_t::Do_Change_Suits_Automatically()
    {
        return this->save_state.do_change_suits_automatically;
    }

    void Members_t::Do_Change_Suits_Automatically(Bool_t value)
    {
        this->save_state.do_change_suits_automatically = value;
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

    some<Member_Sort_Type_e> Members_t::Sort_Type()
    {
        return this->save_state.sort_type;
    }

    void Members_t::Sort_Type(some<Member_Sort_Type_e> value)
    {
        SKYLIB_ASSERT_SOME(value);

        this->save_state.sort_type = value;
    }

    std::mutex& Members_t::Lock(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        return this->locks[member_id()];
    }

    some<Alias_Reference_t*> Members_t::Alias_Reference(some<Member_ID_t> member_id)
    {
        SKYLIB_ASSERT_SOME(member_id);

        some<Alias_Reference_t*> alias_reference = this->quest->Index_To_Alias_Reference(member_id())();
        SKYLIB_ASSERT_SOME(alias_reference);
        return alias_reference;
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
        Member_t member(member_id);
        maybe<Member_Suit_Type_e> default_suit_type = self->Default_Suit_Type();
        if (self->Do_Fill_Suits_Automatically()) {
            member.Add_Suit(Member_Suit_Type_e::MEMBER, actor, false);
            if (default_suit_type && default_suit_type != Member_Suit_Type_e::MEMBER) {
                member.Add_Suit(default_suit_type(), default_suit_type().As_Template());
            }
        } else {
            member.Add_Suit(Member_Suit_Type_e::MEMBER);
            if (default_suit_type && default_suit_type != Member_Suit_Type_e::MEMBER) {
                member.Add_Suit(default_suit_type());
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
                    Member_t(member_id()).Enforce();
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
                    Member_t(member_id()).Enforce();
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
                    Member_t(member_id()).Enforce();
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

}}
