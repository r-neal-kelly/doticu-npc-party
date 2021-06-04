/*
    Copyright � 2020 r-neal-kelly, aka doticu
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
#include "npcp.h"
#include "party_members.h"
#include "party_member_suitcase.h"

namespace doticu_skylib { namespace doticu_npcp {

    Members_t::Save_t::Save_t() :
        do_allow_menu_for_all_actors(DEFAULT_DO_ALLOW_MENU_FOR_ALL_ACTORS),

        do_force_clone_uniques(DEFAULT_DO_FORCE_CLONE_UNIQUES),
        do_force_clone_generics(DEFAULT_DO_FORCE_CLONE_GENERICS),
        do_force_unclone_uniques(DEFAULT_DO_FORCE_UNCLONE_UNIQUES),
        do_force_unclone_generics(DEFAULT_DO_FORCE_UNCLONE_GENERICS),

        has_untouchable_invulnerables(DEFAULT_HAS_UNTOUCHABLE_INVULNERABLES),

        do_suits(DEFAULT_DO_SUITS),
        do_suits_strictly(DEFAULT_DO_SUITS_STRICTLY),
        do_fill_suits_automatically(DEFAULT_DO_FILL_SUITS_AUTOMATICALLY),
        do_unfill_suits_into_pack(DEFAULT_DO_UNFILL_SUITS_INTO_PACK),
        do_change_suits_automatically(DEFAULT_DO_CHANGE_SUITS_AUTOMATICALLY),

        limit(DEFAULT_LIMIT),

        sort_type(DEFAULT_SORT_TYPE),

        clone_suit_type(DEFAULT_CLONE_SUIT_TYPE),

        fill_suit_aura_percent(DEFAULT_FILL_SUIT_AURA_PERCENT),
        fill_suit_body_percent(DEFAULT_FILL_SUIT_BODY_PERCENT),
        fill_suit_feet_percent(DEFAULT_FILL_SUIT_FEET_PERCENT),
        fill_suit_finger_percent(DEFAULT_FILL_SUIT_FINGER_PERCENT),
        fill_suit_forearm_percent(DEFAULT_FILL_SUIT_FOREARM_PERCENT),
        fill_suit_forehead_percent(DEFAULT_FILL_SUIT_FOREHEAD_PERCENT),
        fill_suit_hands_percent(DEFAULT_FILL_SUIT_HANDS_PERCENT),
        fill_suit_head_percent(DEFAULT_FILL_SUIT_HEAD_PERCENT),
        fill_suit_neck_percent(DEFAULT_FILL_SUIT_NECK_PERCENT),

        default_alpha(DEFAULT_ALPHA),
        default_combat_style(DEFAULT_COMBAT_STYLE),
        default_rating(DEFAULT_RATING),
        default_relation(DEFAULT_RELATION),
        default_suit_type(DEFAULT_SUIT_TYPE),
        default_vitality(DEFAULT_VITALITY)
    {
    }

    Members_t::Save_t::~Save_t()
    {
    }

    void Members_t::Save_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->do_allow_menu_for_all_actors);

        NPCP.Write(file, this->do_force_clone_uniques);
        NPCP.Write(file, this->do_force_clone_generics);
        NPCP.Write(file, this->do_force_unclone_uniques);
        NPCP.Write(file, this->do_force_unclone_generics);

        NPCP.Write(file, this->has_untouchable_invulnerables);

        NPCP.Write(file, this->do_suits);
        NPCP.Write(file, this->do_suits_strictly);
        NPCP.Write(file, this->do_fill_suits_automatically);
        NPCP.Write(file, this->do_unfill_suits_into_pack);
        NPCP.Write(file, this->do_change_suits_automatically);

        NPCP.Write(file, this->limit);

        NPCP.Write(file, this->sort_type);

        NPCP.Write(file, this->clone_suit_type);

        NPCP.Write(file, this->fill_suit_aura_percent);
        NPCP.Write(file, this->fill_suit_body_percent);
        NPCP.Write(file, this->fill_suit_feet_percent);
        NPCP.Write(file, this->fill_suit_finger_percent);
        NPCP.Write(file, this->fill_suit_forearm_percent);
        NPCP.Write(file, this->fill_suit_forehead_percent);
        NPCP.Write(file, this->fill_suit_hands_percent);
        NPCP.Write(file, this->fill_suit_head_percent);
        NPCP.Write(file, this->fill_suit_neck_percent);

        NPCP.Write(file, this->default_alpha);
        NPCP.Write(file, this->default_combat_style);
        NPCP.Write(file, this->default_rating);
        NPCP.Write(file, this->default_relation);
        NPCP.Write(file, this->default_suit_type);
        NPCP.Write(file, this->default_vitality);
    }

    void Members_t::Save_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->do_allow_menu_for_all_actors);

        NPCP.Read(file, this->do_force_clone_uniques);
        NPCP.Read(file, this->do_force_clone_generics);
        NPCP.Read(file, this->do_force_unclone_uniques);
        NPCP.Read(file, this->do_force_unclone_generics);

        NPCP.Read(file, this->has_untouchable_invulnerables);

        NPCP.Read(file, this->do_suits);
        NPCP.Read(file, this->do_suits_strictly);
        NPCP.Read(file, this->do_fill_suits_automatically);
        NPCP.Read(file, this->do_unfill_suits_into_pack);
        NPCP.Read(file, this->do_change_suits_automatically);

        NPCP.Read(file, this->limit);

        NPCP.Read(file, this->sort_type);

        NPCP.Read(file, this->clone_suit_type);

        NPCP.Read(file, this->fill_suit_aura_percent);
        NPCP.Read(file, this->fill_suit_body_percent);
        NPCP.Read(file, this->fill_suit_feet_percent);
        NPCP.Read(file, this->fill_suit_finger_percent);
        NPCP.Read(file, this->fill_suit_forearm_percent);
        NPCP.Read(file, this->fill_suit_forehead_percent);
        NPCP.Read(file, this->fill_suit_hands_percent);
        NPCP.Read(file, this->fill_suit_head_percent);
        NPCP.Read(file, this->fill_suit_neck_percent);

        NPCP.Read(file, this->default_alpha);
        NPCP.Read(file, this->default_combat_style);
        NPCP.Read(file, this->default_rating);
        NPCP.Read(file, this->default_relation);
        NPCP.Read(file, this->default_suit_type);
        NPCP.Read(file, this->default_vitality);
    }

    Members_t::State_t::State_t() :
        save(),

        members(),

        ghost_abilities(Const::Spells::Ghost_Abilities())
    {
    }

    Members_t::State_t::~State_t()
    {
    }

    void Members_t::Register_Me(some<Virtual::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        Member_t::Register_Me(machine);
    }

    Party_t& Members_t::Party()
    {
        return NPCP.Party();
    }

    Members_t::Members_t() :
        state()
    {
    }

    Members_t::~Members_t()
    {
    }

    void Members_t::On_After_New_Game()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            State().members[idx].On_After_New_Game();
        }
    }

    void Members_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            State().members[idx].On_Before_Save_Game(file);
        }
    }

    void Members_t::On_After_Save_Game()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            State().members[idx].On_After_Save_Game();
        }
    }

    void Members_t::On_Before_Load_Game()
    {
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            State().members[idx].On_Before_Load_Game();
        }
    }

    void Members_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);
        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            State().members[idx].On_After_Load_Game(file);
        }
    }

    void Members_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        On_After_Load_Game(file);
    }

    void Members_t::On_Update()
    {
        Consts_t::NPCP::Global::Do_Allow_Menu_For_All_Actors()->Bool(Do_Allow_Menu_For_All_Actors());

        Consts_t::NPCP::Global::Do_Force_Clone_Uniques()->Bool(Do_Force_Clone_Uniques());
        Consts_t::NPCP::Global::Do_Force_Clone_Generics()->Bool(Do_Force_Clone_Generics());
        Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()->Bool(Do_Force_Unclone_Uniques());
        Consts_t::NPCP::Global::Do_Force_Unclone_Generics()->Bool(Do_Force_Unclone_Generics());

        for (size_t idx = 0, end = MAX_MEMBERS; idx < end; idx += 1) {
            State().members[idx].On_Update();
        }
    }

    Members_t::State_t& Members_t::State()
    {
        return this->state;
    }

    Members_t::Save_t& Members_t::Save()
    {
        return State().save;
    }

    Bool_t Members_t::Do_Allow_Menu_For_All_Actors()
    {
        return Save().do_allow_menu_for_all_actors;
    }

    void Members_t::Do_Allow_Menu_For_All_Actors(Bool_t value)
    {
        Save().do_allow_menu_for_all_actors = value;
    }

    Bool_t Members_t::Do_Force_Clone_Uniques()
    {
        return Save().do_force_clone_uniques;
    }

    void Members_t::Do_Force_Clone_Uniques(Bool_t value)
    {
        Save().do_force_clone_uniques = value;
    }

    Bool_t Members_t::Do_Force_Clone_Generics()
    {
        return Save().do_force_clone_generics;
    }

    void Members_t::Do_Force_Clone_Generics(Bool_t value)
    {
        Save().do_force_clone_generics = value;
    }

    Bool_t Members_t::Do_Force_Unclone_Uniques()
    {
        return Save().do_force_unclone_uniques;
    }

    void Members_t::Do_Force_Unclone_Uniques(Bool_t value)
    {
        Save().do_force_unclone_uniques = value;
    }

    Bool_t Members_t::Do_Force_Unclone_Generics()
    {
        return Save().do_force_unclone_generics;
    }

    void Members_t::Do_Force_Unclone_Generics(Bool_t value)
    {
        Save().do_force_unclone_generics = value;
    }

    Bool_t Members_t::Has_Untouchable_Invulnerables()
    {
        return Save().has_untouchable_invulnerables;
    }

    void Members_t::Has_Untouchable_Invulnerables(Bool_t value)
    {
        Save().has_untouchable_invulnerables = value;
    }

    Bool_t Members_t::Do_Suits()
    {
        return Save().do_suits;
    }

    void Members_t::Do_Suits(Bool_t value)
    {
        Save().do_suits = value;
    }

    Bool_t Members_t::Do_Suits_Strictly()
    {
        return Save().do_suits_strictly;
    }

    void Members_t::Do_Suits_Strictly(Bool_t value)
    {
        Save().do_suits_strictly = value;
    }

    Bool_t Members_t::Do_Fill_Suits_Automatically()
    {
        return Save().do_fill_suits_automatically;
    }

    void Members_t::Do_Fill_Suits_Automatically(Bool_t value)
    {
        Save().do_fill_suits_automatically = value;
    }

    Bool_t Members_t::Do_Unfill_Suits_Into_Pack()
    {
        return Save().do_unfill_suits_into_pack;
    }

    void Members_t::Do_Unfill_Suits_Into_Pack(Bool_t value)
    {
        Save().do_unfill_suits_into_pack = value;
    }

    Bool_t Members_t::Do_Change_Suits_Automatically()
    {
        return Save().do_change_suits_automatically;
    }

    void Members_t::Do_Change_Suits_Automatically(Bool_t value)
    {
        Save().do_change_suits_automatically = value;
    }

    some<Member_Limit_t> Members_t::Limit()
    {
        maybe<Member_Limit_t>& value = Save().limit;
        if (!value) {
            value = DEFAULT_LIMIT;
        }

        size_t active_count = Active_Count();
        if (value() < active_count) {
            value = active_count;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Limit(maybe<Member_Limit_t> value)
    {
        Save().limit = value;
    }

    some<Member_Sort_Type_e> Members_t::Sort_Type()
    {
        maybe<Member_Sort_Type_e>& value = Save().sort_type;
        if (!value) {
            value = DEFAULT_SORT_TYPE;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Sort_Type(maybe<Member_Sort_Type_e> value)
    {
        Save().sort_type = value;
    }

    some<Member_Clone_Suit_Type_e> Members_t::Clone_Suit_Type()
    {
        maybe<Member_Clone_Suit_Type_e>& value = Save().clone_suit_type;
        if (!value) {
            value = DEFAULT_CLONE_SUIT_TYPE;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Clone_Suit_Type(maybe<Member_Clone_Suit_Type_e> value)
    {
        Save().clone_suit_type = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Aura_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_aura_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_AURA_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Aura_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_aura_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Body_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_body_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_BODY_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Body_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_body_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Feet_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_feet_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_FEET_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Feet_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_feet_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Finger_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_finger_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_FINGER_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Finger_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_finger_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Forearm_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_forearm_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_FOREARM_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Forearm_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_forearm_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Forehead_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_forehead_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_FOREHEAD_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Forehead_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_forehead_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Hands_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_hands_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_HANDS_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Hands_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_hands_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Head_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_head_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_HEAD_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Head_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_head_percent = value;
    }

    some<Percent_t> Members_t::Fill_Suit_Neck_Percent()
    {
        maybe<Percent_t>& value = Save().fill_suit_neck_percent;
        if (!value) {
            value = DEFAULT_FILL_SUIT_NECK_PERCENT;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Fill_Suit_Neck_Percent(maybe<Percent_t> value)
    {
        Save().fill_suit_neck_percent = value;
    }

    some<Member_Alpha_t> Members_t::Default_Alpha()
    {
        maybe<Member_Alpha_t>& value = Save().default_alpha;
        if (!value) {
            value = DEFAULT_ALPHA;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Default_Alpha(maybe<Member_Alpha_t> value)
    {
        Save().default_alpha = value;
    }

    maybe<Member_Combat_Style_e> Members_t::Default_Combat_Style()
    {
        maybe<Member_Combat_Style_e>& value = Save().default_combat_style;
        if (!value) {
            value = DEFAULT_COMBAT_STYLE;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Default_Combat_Style(maybe<Member_Combat_Style_e> value)
    {
        Save().default_combat_style = value;
    }

    maybe<Member_Rating_t> Members_t::Default_Rating()
    {
        maybe<Member_Rating_t>& value = Save().default_rating;
        if (!value) {
            value = DEFAULT_RATING;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Default_Rating(maybe<Member_Rating_t> value)
    {
        Save().default_rating = value;
    }

    maybe<Member_Relation_e> Members_t::Default_Relation()
    {
        maybe<Member_Relation_e>& value = Save().default_relation;
        if (!value) {
            value = DEFAULT_RELATION;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Default_Relation(maybe<Member_Relation_e> value)
    {
        Save().default_relation = value;
    }

    maybe<Member_Suit_Type_e> Members_t::Default_Suit_Type()
    {
        maybe<Member_Suit_Type_e>& value = Save().default_suit_type;
        if (!value) {
            value = DEFAULT_SUIT_TYPE;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Default_Suit_Type(maybe<Member_Suit_Type_e> value)
    {
        Save().default_suit_type = value;
    }

    maybe<Member_Vitality_e> Members_t::Default_Vitality()
    {
        maybe<Member_Vitality_e>& value = Save().default_vitality;
        if (!value) {
            value = DEFAULT_VITALITY;
        }

        SKYLIB_ASSERT_SOME(value);

        return value();
    }

    void Members_t::Default_Vitality(maybe<Member_Vitality_e> value)
    {
        Save().default_vitality = value;
    }

    void Members_t::Reset_Options()
    {
        State().save.~Save_t();
        new (&State().save) Save_t();
    }






    void Members_t::Validate()
    {
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

    
    maybe<Member_Suit_Type_e> Members_t::Default_Suit_Type()
    {
        return this->save_state.default_suit_type;
    }

    void Members_t::Default_Suit_Type(maybe<Member_Suit_Type_e> suit_type)
    {
        SKYLIB_ASSERT(suit_type != Member_Suit_Type_e::ACTIVE);

        this->save_state.default_suit_type = suit_type;
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
