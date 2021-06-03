/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/ammo.h"
#include "doticu_skylib/armor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_actor_bases.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/virtual_macros.h"
#include "doticu_skylib/weapon.h"

#include "npcp.inl"
#include "party.h"
#include "party_member.h"
#include "party_member_suitcase.h"
#include "party_members.h"

namespace doticu_skylib { namespace doticu_npcp {

    Member_t::Save_t::Save_t() :
        actual_base(),
        actor(),

        flags(),
        flags_has_suit(),
        flags_only_playables(),

        alpha(),
        rating(),
        relation(),
        suit_type(),
        vitality(),

        combat_style(),
        ghost_ability(),
        outfit(),
        pack(),
        suitcase(),
        voice_type(),

        name()
    {
    }

    Member_t::Save_t::~Save_t()
    {
    }

    void Member_t::Save_t::Write(std::ofstream& file)
    {
        maybe<Actor_Base_t*> static_base = none<Actor_Base_t*>();
        if (this->actual_base) {
            static_base = actual_base->Identifiable_Static_Base();
            if (!static_base) {
                static_base = this->actual_base;
            }
        }

        NPCP.Write(file, this->id);

        NPCP.Write_Form(file, static_base);
        NPCP.Write_Form(file, this->actual_base);
        NPCP.Write_Form(file, this->actor);

        NPCP.Write(file, this->flags);
        NPCP.Write(file, this->flags_has_suit);
        NPCP.Write(file, this->flags_only_playables);

        NPCP.Write(file, this->alpha);
        NPCP.Write(file, this->rating);
        NPCP.Write(file, this->relation);
        NPCP.Write(file, this->suit_type);
        NPCP.Write(file, this->vitality);

        NPCP.Write_Form(file, this->combat_style);
        NPCP.Write_Form(file, this->ghost_ability);
        NPCP.Write_Form(file, this->outfit);
        NPCP.Write_Form(file, this->pack);
        NPCP.Write_Form(file, this->suitcase);
        NPCP.Write_Form(file, this->voice_type);

        NPCP.Write_String(file, this->name);
    }

    void Member_t::Save_t::Read(std::ifstream& file)
    {
        maybe<Actor_Base_t*> static_base;

        NPCP.Read(file, this->id);

        NPCP.Read_Form(file, static_base);
        NPCP.Read_Form(file, this->actual_base);
        NPCP.Read_Form(file, this->actor);

        NPCP.Read(file, this->flags);
        NPCP.Read(file, this->flags_has_suit);
        NPCP.Read(file, this->flags_only_playables);

        NPCP.Read(file, this->alpha);
        NPCP.Read(file, this->rating);
        NPCP.Read(file, this->relation);
        NPCP.Read(file, this->suit_type);
        NPCP.Read(file, this->vitality);

        NPCP.Read_Form(file, this->combat_style);
        NPCP.Read_Form(file, this->ghost_ability);
        NPCP.Read_Form(file, this->outfit);
        NPCP.Read_Form(file, this->pack);
        NPCP.Read_Form(file, this->suitcase);
        NPCP.Read_Form(file, this->voice_type);

        NPCP.Read_String(file, this->name);

        if (this->id && static_base) {
            if (!this->actual_base || this->actual_base->Identifiable_Static_Base() != static_base) {
                this->actual_base = static_base;
            }
            if (!this->actor) {
                this->actor = Actor_t::Create(this->actual_base(), !this->actual_base->Does_Respawn(), true, false);
            }
            if (!this->actor) {
                this->id = none<Member_ID_t>();
                this->actual_base = none<Actor_Base_t*>();
                this->actor = none<Actor_t*>();
            }
        } else {
            this->id = none<Member_ID_t>();
            this->actual_base = none<Actor_Base_t*>();
            this->actor = none<Actor_t*>();
        }
    }

    Member_t::State_t::State_t() :
        save(),

        custom_base()
    {
    }

    Member_t::State_t::~State_t()
    {
    }

    String_t Member_t::Class_Name()
    {
        DEFINE_CLASS_NAME("doticu_npcp_party_member");
    }

    some<Virtual::Class_t*> Member_t::Class()
    {
        DEFINE_CLASS();
    }

    void Member_t::Register_Me(some<Virtual::Machine_t*> machine)
    {
        using Type_t = Member_t;

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
            BIND_METHOD(machine, class_name, Type_t, METHOD_NAME_, WAITS_FOR_FRAME_,    \
                        RETURN_TYPE_, METHOD_, __VA_ARGS__);                            \
        SKYLIB_W

        #undef METHOD
    }

    Party_t& Member_t::Party()
    {
        return NPCP.Party();
    }

    Members_t& Member_t::Members()
    {
        return NPCP.Party().Members();
    }

    Member_t::Member_t() :
        state()
    {
    }

    Member_t::Member_t(some<Member_ID_t> id, some<Actor_t*> actor) :
        state()
    {
        SKYLIB_ASSERT_SOME(id);
        SKYLIB_ASSERT_SOME(actor);

        Save().id = id;

        Save().actual_base = actor->Actor_Base();
        Save().actor = actor;

        // need to fill in default values
        // needs to be added to alias, probably do that in Members_t
    }

    Member_t::~Member_t()
    {
        if (Is_Valid()) {
            if (State().custom_base) {
                Save().actor->Actor_Base(Save().actual_base(), false);
                Actor_Base_t::Destroy(State().custom_base());
                State().custom_base = none<Actor_Base_t*>();
            }
        }
        // needs to be removed from alias, probably do that in Members_t
    }

    void Member_t::On_After_New_Game()
    {
    }

    void Member_t::On_Before_Save_Game(std::ofstream& file)
    {
        Save().Write(file);
    }

    void Member_t::On_After_Save_Game()
    {
    }

    void Member_t::On_Before_Load_Game()
    {
    }

    void Member_t::On_After_Load_Game(std::ifstream& file)
    {
        Save().Read(file);
    }

    void Member_t::On_After_Load_Game(std::ifstream& file, const Version_t<u16> version_to_update)
    {
        Save().Read(file);
    }

    void Member_t::On_Update()
    {
    }

    Member_t::State_t& Member_t::State()
    {
        return this->state;
    }

    Member_t::Save_t& Member_t::Save()
    {
        return this->state.save;
    }

    Bool_t Member_t::Is_Valid()
    {
        return Save().id && Save().actual_base && Save().actor;
    }

    Bool_t Member_t::Is_Banished()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_BANISHED);
    }

    void Member_t::Is_Banished(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Save().flags.Is_Flagged(Member_Flags_e::IS_BANISHED, value);
    }

    Bool_t Member_t::Is_Clone()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_CLONE);
    }

    void Member_t::Is_Clone(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Save().flags.Is_Flagged(Member_Flags_e::IS_CLONE, value);
    }

    Bool_t Member_t::Is_Enabled()
    {
        SKYLIB_ASSERT(Is_Valid());

        return !Is_Banished();
    }

    Bool_t Member_t::Is_Immobile()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE);
    }

    void Member_t::Is_Immobile(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Save().flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE, value);
    }

    Bool_t Member_t::Is_Mannequin()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN);
    }

    void Member_t::Is_Mannequin(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Save().flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN, value);
    }

    Bool_t Member_t::Is_Reanimated()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_REANIMATED);
    }

    void Member_t::Is_Reanimated(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Save().flags.Is_Flagged(Member_Flags_e::IS_REANIMATED, value);
    }

    Bool_t Member_t::Is_Sneak()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_SNEAK);
    }

    void Member_t::Is_Sneak(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Save().flags.Is_Flagged(Member_Flags_e::IS_SNEAK, value);
    }

    Bool_t Member_t::Is_Thrall()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_THRALL);
    }

    void Member_t::Is_Thrall(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Save().flags.Is_Flagged(Member_Flags_e::IS_THRALL, value);
    }

    Bool_t Member_t::Is_Untouchable()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Members().Has_Untouchable_Invulnerables() && Is_Invulnerable();
    }

    Bool_t Member_t::Is_Warrior()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::WARRIOR;
    }

    Bool_t Member_t::Is_Mage()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::MAGE;
    }

    Bool_t Member_t::Is_Archer()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::ARCHER;
    }

    Bool_t Member_t::Is_Coward()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::COWARD;
    }

    Bool_t Member_t::Is_Mortal()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Vitality() == Member_Vitality_e::MORTAL;
    }

    void Member_t::Is_Mortal(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Vitality(Member_Vitality_e::MORTAL);
    }

    Bool_t Member_t::Is_Protected()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Vitality() == Member_Vitality_e::PROTECTED;
    }

    void Member_t::Is_Protected(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Vitality(Member_Vitality_e::PROTECTED);
    }

    Bool_t Member_t::Is_Essential()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Vitality() == Member_Vitality_e::ESSENTIAL;
    }

    void Member_t::Is_Essential(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Vitality(Member_Vitality_e::ESSENTIAL);
    }

    Bool_t Member_t::Is_Invulnerable()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Vitality() == Member_Vitality_e::INVULNERABLE;
    }

    void Member_t::Is_Invulnerable(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        Vitality(Member_Vitality_e::INVULNERABLE);
    }

    Bool_t Member_t::Has_AI()
    {
        SKYLIB_ASSERT(Is_Valid());

        return !Is_Banished() && !Is_Mannequin();
    }

    Bool_t Member_t::Has_Suit(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Has_Suit_e flag = type().As_Member_Flag_Has_Suit();
        SKYLIB_ASSERT_SOME(flag);

        return Save().flags_has_suit.Is_Flagged(flag);
    }

    void Member_t::Has_Suit(some<Member_Suit_Type_e> type, Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Has_Suit_e flag = type().As_Member_Flag_Has_Suit();
        SKYLIB_ASSERT_SOME(flag);

        Save().flags_has_suit.Is_Flagged(flag, value);
    }

    Bool_t Member_t::Has_Only_Playables(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Only_Playables_e flag = type().As_Member_Flag_Only_Playables();
        SKYLIB_ASSERT_SOME(flag);

        return Save().flags_only_playables.Is_Flagged(flag);
    }

    void Member_t::Has_Only_Playables(some<Member_Suit_Type_e> type, Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Only_Playables_e flag = type().As_Member_Flag_Only_Playables();
        SKYLIB_ASSERT_SOME(flag);

        Save().flags_only_playables.Is_Flagged(flag, value);
    }

    some<Member_ID_t> Member_t::ID()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().id;
    }

    some<Alias_Reference_t*> Member_t::Alias()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Members().Alias_Reference(ID());
    }

    some<Actor_Base_t*> Member_t::Actual_Base()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Save().actual_base();
    }

    some<Actor_Base_t*> Member_t::Custom_Base()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Actor_Base_t*>& custom_base = Members().custom_bases[this->id()];
        if (!custom_base) {
            custom_base = Actor_Base_t::Create_Temporary_Copy(Original_Base())();
            custom_base->Default_Outfit(Outfit());
            SKYLIB_ASSERT_SOME(custom_base);
        }

        return custom_base();
    }

    some<Actor_t*> Member_t::Actor()
    {
        SKYLIB_ASSERT(Is_Valid());

        some<Actor_t*> actor = State().actors[this->id()]();
        SKYLIB_ASSERT_SOME(actor);
        return actor;
    }

    maybe<Member_Alpha_t> Member_t::Alpha()
    {
        SKYLIB_ASSERT(Is_Valid());

        if (!Is_Enabled()) {
            return 0.0f;
        } else {
            return State().alphas[this->id()];
        }
    }

    void Member_t::Alpha(maybe<Member_Alpha_t> alpha)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().alphas[this->id()] = alpha;
    }

    some<Reference_t*> Member_t::Cache()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Reference_t*>& cache = State().caches[this->id()];
        if (!cache) {
            cache = Container_t::Create_Reference(
                Consts_t::NPCP::Container::Empty(),
                Consts_t::NPCP::Reference::Storage_Marker()
            )();
            SKYLIB_ASSERT_SOME(cache);
        }

        return cache();
    }

    maybe<Combat_Style_t*> Member_t::Combat_Style()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Combat_Style_t*> combat_style = State().combat_styles[this->id()];
        if (!combat_style) {
            combat_style = Original_Base()->Combat_Style();
        }

        return combat_style;
    }

    void Member_t::Combat_Style(maybe<Combat_Style_t*> combat_style)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().combat_styles[this->id()] = combat_style;
    }

    void Member_t::Combat_Style(Member_Combat_Style_e combat_style)
    {
        SKYLIB_ASSERT(Is_Valid());

        Combat_Style(combat_style.As_Combat_Style());
    }

    maybe<Spell_t*> Member_t::Ghost_Ability()
    {
        SKYLIB_ASSERT(Is_Valid());

        return State().ghost_abilities[this->id()];
    }

    void Member_t::Ghost_Ability(maybe<Spell_t*> ghost_ability)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().ghost_abilities[this->id()] = ghost_ability;
    }

    String_t Member_t::Name()
    {
        SKYLIB_ASSERT(Is_Valid());

        String_t name = State().names[this->id()];
        if (!name) {
            name = Original_Base()->Name();
        }

        return name;
    }

    void Member_t::Name(String_t name)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().names[this->id()] = name;
    }

    maybe<Outfit_t*> Member_t::Outfit()
    {
        SKYLIB_ASSERT(Is_Valid());

        return State().outfits[this->id()];
    }

    void Member_t::Outfit(maybe<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().outfits[this->id()] = outfit;
    }

    some<Reference_t*> Member_t::Pack()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Reference_t*>& pack = State().packs[this->id()];
        if (!pack) {
            pack = Container_t::Create_Reference(
                Consts_t::NPCP::Container::Empty(),
                Consts_t::NPCP::Reference::Storage_Marker()
            )();
            SKYLIB_ASSERT_SOME(pack);
        }

        return pack();
    }

    maybe<Member_Rating_t> Member_t::Rating()
    {
        SKYLIB_ASSERT(Is_Valid());

        return State().ratings[this->id()];
    }

    void Member_t::Rating(maybe<Member_Rating_t> rating)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().ratings[this->id()] = rating;
    }

    some<Member_Relation_e> Member_t::Relation()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Member_Relation_e> relation = State().relations[this->id()];
        if (!relation) {
            relation = Original_Base()->Relation(skylib::Const::Actor_Base::Player());
            SKYLIB_ASSERT_SOME(relation);
        }

        return relation();
    }

    void Member_t::Relation(maybe<Member_Relation_e> relation)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().relations[this->id()] = relation;
    }

    maybe<Member_Suit_Type_e> Member_t::Suit_Type()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Member_Suit_Type_e> suit_type = State().suit_types[this->id()];
        if (suit_type && Members().Do_Change_Suits_Automatically()) {
            Main_t& main = Members().Main();
            some<Actor_t*> actor = Actor();
            maybe<Cell_t*> cell = actor->Cell(true);
            maybe<Location_t*> location = actor->Location();

            if (Has_Suit(Member_Suit_Type_e::MANNEQUIN) && Is_Mannequin()) {
                return Member_Suit_Type_e::MANNEQUIN;
            } else if (Has_Suit(Member_Suit_Type_e::IMMOBILE) && Is_Immobile()) {
                return Member_Suit_Type_e::IMMOBILE;
            } else if (Has_Suit(Member_Suit_Type_e::COMBATANT) && actor->Is_In_Combat()) {
                return Member_Suit_Type_e::COMBATANT;
            } else if (location && Has_Suit(Member_Suit_Type_e::INN) && location->Is_Inn()) {
                return Member_Suit_Type_e::INN;
            } else if (location && Has_Suit(Member_Suit_Type_e::HOME) && location->Is_Likely_Home()) {
                return Member_Suit_Type_e::HOME;
            } else if (location && Has_Suit(Member_Suit_Type_e::SETTLEMENT) && location->Is_Likely_City_Or_Town()) {
                return Member_Suit_Type_e::SETTLEMENT;
            } else if (Has_Suit(Member_Suit_Type_e::FOLLOWER) && main.Is_Follower(this->id)) {
                return Member_Suit_Type_e::FOLLOWER;
            } else if (Has_Suit(Member_Suit_Type_e::GUARD) && main.Is_Active_Guard(this->id)) {
                return Member_Suit_Type_e::GUARD;
            } else if (Has_Suit(Member_Suit_Type_e::EATER) && main.Is_Active_Eater(this->id)) {
                return Member_Suit_Type_e::EATER;
            } else if (Has_Suit(Member_Suit_Type_e::SITTER) && main.Is_Active_Sitter(this->id)) {
                return Member_Suit_Type_e::SITTER;
            } else if (Has_Suit(Member_Suit_Type_e::SLEEPER) && main.Is_Active_Sleeper(this->id)) {
                return Member_Suit_Type_e::SLEEPER;
            } else if (Has_Suit(Member_Suit_Type_e::SANDBOXER) && main.Is_Active_Sandboxer(this->id)) {
                return Member_Suit_Type_e::SANDBOXER;
            } else if (location && Has_Suit(Member_Suit_Type_e::DANGEROUS) && location->Is_Likely_Dangerous()) {
                return Member_Suit_Type_e::DANGEROUS;
            } else if (location && Has_Suit(Member_Suit_Type_e::CIVILIZED) && location->Is_Likely_Civilized()) {
                return Member_Suit_Type_e::CIVILIZED;
            } else if (cell && Has_Suit(Member_Suit_Type_e::INTERIOR) && cell->Is_Interior()) {
                return Member_Suit_Type_e::INTERIOR;
            } else if (cell && Has_Suit(Member_Suit_Type_e::EXTERIOR) && cell->Is_Exterior()) {
                return Member_Suit_Type_e::EXTERIOR;
            } else if (Has_Suit(Member_Suit_Type_e::COWARD) && Is_Coward()) {
                return Member_Suit_Type_e::COWARD;
            } else if (Has_Suit(Member_Suit_Type_e::ARCHER) && Is_Archer()) {
                return Member_Suit_Type_e::ARCHER;
            } else if (Has_Suit(Member_Suit_Type_e::MAGE) && Is_Mage()) {
                return Member_Suit_Type_e::MAGE;
            } else if (Has_Suit(Member_Suit_Type_e::WARRIOR) && Is_Warrior()) {
                return Member_Suit_Type_e::WARRIOR;
            } else if (Has_Suit(Member_Suit_Type_e::THRALL) && Is_Thrall()) {
                return Member_Suit_Type_e::THRALL;
            } else {
                return Member_Suit_Type_e::MEMBER;
            }
        } else {
            return suit_type;
        }
    }

    void Member_t::Suit_Type(maybe<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Valid());

        if (type) {
            SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
            SKYLIB_ASSERT(Has_Suit(type()));
            State().suit_types[this->id()] = type;
        } else {
            State().suit_types[this->id()] = none<Member_Suit_Type_e>();
        }
    }

    some<Member_Suitcase_t*> Member_t::Suitcase()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Member_Suitcase_t*>& suitcase = State().suitcases[this->id()];
        if (!suitcase) {
            suitcase = Member_Suitcase_t::Create()();
            SKYLIB_ASSERT_SOME(suitcase);
        }

        return suitcase();
    }

    some<Member_Vitality_e> Member_t::Vitality()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Member_Vitality_e> vitality = State().vitalities[this->id()];
        if (!vitality) {
            vitality = Original_Base()->Vitality();
            SKYLIB_ASSERT_SOME(vitality);
        }

        return vitality();
    }

    void Member_t::Vitality(maybe<Member_Vitality_e> vitality)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().vitalities[this->id()] = vitality;
    }

    some<Voice_Type_t*> Member_t::Voice_Type()
    {
        SKYLIB_ASSERT(Is_Valid());

        maybe<Voice_Type_t*> voice_type = State().voice_types[this->id()];
        if (!voice_type) {
            voice_type = Original_Base()->Voice_Type();
            if (!voice_type) {
                voice_type = Actor()->Race_Voice_Type();
                if (!voice_type) {
                    voice_type = Consts_t::NPCP::Voice_Type::Blank()();
                }
            }
            SKYLIB_ASSERT_SOME(voice_type);
        }

        return voice_type();
    }

    void Member_t::Voice_Type(maybe<Voice_Type_t*> voice_type)
    {
        SKYLIB_ASSERT(Is_Valid());

        State().voice_types[this->id()] = voice_type;
    }

    void Member_t::Tokenize(some<Bound_Object_t*> object, Container_Entry_Count_t count)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT(count > 0);

        Reference_Container_t container = Actor()->Container();
        some<Reference_Container_Entry_t*> entry = container.Some_Entry(object);
        if (entry->Non_Extra_Lists_Count() != count) {
            entry->Decrement_Count(container, Container_Entry_Count_t::_MAX_);
            entry->Increment_Count(container, count);
            Main().Update_AI(this->id, Member_Update_AI_e::EVALUATE_PACKAGE);
        }
    }

    void Member_t::Untokenize(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);

        Reference_Container_t container = Actor()->Container();
        maybe<Reference_Container_Entry_t*> entry = container.Maybe_Entry(object);
        if (entry && entry->Non_Extra_Lists_Count() > 0) {
            entry->Decrement_Count(container, Container_Entry_Count_t::_MAX_);
            Main().Update_AI(this->id, Member_Update_AI_e::EVALUATE_PACKAGE);
        }
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(type);
        Has_Suit(type, true);
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
        SKYLIB_ASSERT_SOME(outfit);

        Remove_Suit(type);
        Has_Suit(type, true);

        some<Reference_t*> cache = Cache();
        outfit->Add_Items_To(cache);
        Suitcase()->Move_From(cache,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Container_t*> container)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
        SKYLIB_ASSERT_SOME(container);

        Remove_Suit(type);
        Has_Suit(type, true);

        some<Reference_t*> cache = Cache();
        container->Container_Add_Items_To(cache);
        Suitcase()->Move_From(cache,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Actor_Base_t*> actor_base)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
        SKYLIB_ASSERT_SOME(actor_base);

        Remove_Suit(type);
        Has_Suit(type, true);

        some<Reference_t*> cache = Cache();
        maybe<Outfit_t*> outfit = actor_base->Default_Outfit();
        actor_base->Container_Add_Items_To(cache);
        if (outfit) {
            outfit->Add_Items_To(cache);
        }
        Suitcase()->Move_From(cache,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Reference_t*> reference, Bool_t do_copy)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
        SKYLIB_ASSERT_SOME(reference);

        Remove_Suit(type);
        Has_Suit(type, true);

        if (do_copy) {
            Suitcase()->Copy_From(reference,
                                  type,
                                  Member_Suitcase_t::filter_out_blank_or_token_objects,
                                  Member_Suitcase_t::filter_out_no_extra_lists);
        } else {
            Suitcase()->Move_From(reference,
                                  type,
                                  Member_Suitcase_t::filter_out_blank_or_token_objects,
                                  Member_Suitcase_t::filter_out_quest_extra_lists);
        }
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, Member_Suit_Template_t suit_template)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(type);
        Has_Suit(type, true);

        some<Reference_t*> cache = Cache();

        maybe<Armor_t*> aura = suit_template.armor.Aura(Members().Fill_Suit_Aura_Probability());
        maybe<Armor_t*> body = suit_template.armor.Body(Members().Fill_Suit_Body_Probability());
        maybe<Armor_t*> feet = suit_template.armor.Feet(Members().Fill_Suit_Feet_Probability());
        maybe<Armor_t*> finger = suit_template.armor.Finger(Members().Fill_Suit_Finger_Probability());
        maybe<Armor_t*> forearm = suit_template.armor.Forearm(Members().Fill_Suit_Forearm_Probability());
        maybe<Armor_t*> forehead = suit_template.armor.Forehead(Members().Fill_Suit_Forehead_Probability());
        maybe<Armor_t*> hands = suit_template.armor.Hands(Members().Fill_Suit_Hands_Probability());
        maybe<Armor_t*> head = suit_template.armor.Head(Members().Fill_Suit_Head_Probability());
        maybe<Armor_t*> neck = suit_template.armor.Neck(Members().Fill_Suit_Neck_Probability());

        if (aura) cache->Add_Item(aura(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (body) cache->Add_Item(body(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (feet) cache->Add_Item(feet(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (finger) cache->Add_Item(finger(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (forearm) cache->Add_Item(forearm(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (forehead) cache->Add_Item(forehead(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (hands) cache->Add_Item(hands(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (head) cache->Add_Item(head(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (neck) cache->Add_Item(neck(), none<Extra_List_t*>(), 1, none<Reference_t*>());

        if (suit_template.weapon_a) {
            cache->Add_Item(suit_template.weapon_a(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        }
        if (suit_template.weapon_b) {
            cache->Add_Item(suit_template.weapon_b(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        }
        if (suit_template.ammo) {
            cache->Add_Item(suit_template.ammo(), none<Extra_List_t*>(), 100, none<Reference_t*>());
        }

        Suitcase()->Move_From(cache,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
        cache->Destroy_Non_Quest_Items();
    }

    void Member_t::Remove_Suit(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        if (Has_Suit(type)) {
            Suitcase()->Remove_Suit(Members().Do_Unfill_Suits_To_Pack() ? Pack()() : none<Reference_t*>()(), type);
            Has_Suit(type, false);
        }
    }

    void Member_t::Enforce()
    {
        SKYLIB_ASSERT(Is_Valid());

        // we may want a different smaller branch if the actor is in combat, or a separate func to call
        Main_t& main = Main();
        Members_t& members = Members();
        some<Actor_t*> actor = Actor();
        some<Actor_Base_t*> custom_base = Custom_Base();

        Vector_t<some<Spell_t*>> spells_to_add;
        spells_to_add.reserve(4);

        actor->Actor_Base(Custom_Base(), false);

        Tokenize(Consts_t::NPCP::Misc::Token::Member(), this->id() + 1);
        actor->Faction_Rank(Consts_t::NPCP::Faction::Member(), 0);

        if (Is_Banished()) {
            Tokenize(Consts_t::NPCP::Misc::Token::Banished());
        } else {
            Untokenize(Consts_t::NPCP::Misc::Token::Banished());
        }

        if (Is_Immobile()) {
            Tokenize(Consts_t::NPCP::Misc::Token::Immobile());
        } else {
            Untokenize(Consts_t::NPCP::Misc::Token::Immobile());
        }

        if (Is_Reanimated()) {
            Tokenize(Consts_t::NPCP::Misc::Token::Reanimated());

            spells_to_add.push_back(Consts_t::NPCP::Spell::Reanimate_Ability());
        } else {
            Untokenize(Consts_t::NPCP::Misc::Token::Reanimated());

            actor->Remove_Spell(Consts_t::NPCP::Spell::Reanimate_Ability());
        }

        if (Is_Sneak()) {
            Tokenize(Consts_t::NPCP::Misc::Token::Sneak());

            if (!actor->Is_Forced_To_Sneak()) {
                actor->Is_Forced_To_Sneak(true, main.Script(this->id));
            }
        } else {
            Untokenize(Consts_t::NPCP::Misc::Token::Sneak());

            if (actor->Is_Forced_To_Sneak()) {
                actor->Is_Forced_To_Sneak(false, main.Script(this->id));
            }
        }

        if (Is_Thrall()) {
            Tokenize(Consts_t::NPCP::Misc::Token::Thrall());
        } else {
            Untokenize(Consts_t::NPCP::Misc::Token::Thrall());
        }

        custom_base->Name(Name(), false);
        actor->x_list.Destroy_Extra_Text_Display();

        custom_base->Combat_Style(Combat_Style());

        maybe<Spell_t*> ghost_ability = Ghost_Ability();
        for (size_t idx = 0, end = members.vanilla_ghost_abilities.size(); idx < end; idx += 1) {
            some<Spell_t*> vanilla_ghost_ability = members.vanilla_ghost_abilities[idx];
            if (vanilla_ghost_ability != ghost_ability) {
                actor->Remove_Spell(members.vanilla_ghost_abilities[idx]);
            }
        }
        if (ghost_ability) {
            spells_to_add.push_back(ghost_ability());
        }

        maybe<Outfit_t*> outfit = Outfit();
        maybe<Outfit_t*> custom_outfit = custom_base->Default_Outfit();
        if (outfit != custom_outfit) {
            Outfit(custom_outfit);
        }

        // if we limit to attached actors, we need to stop the disabling of suit on the first suitup
        if (!actor->Is_In_Combat()) {
            maybe<Member_Suit_Type_e> suit_type = Suit_Type();
            if (suit_type) {
                some<Member_Suitcase_t*> suitcase = Suitcase();
                if (suitcase->Has_Inactive_Outfit_Item(actor)) {
                    // we need to have either a global option or member option here, to initiate the auto-change
                    Suit_Type(none<Member_Suit_Type_e>());
                    suit_type = none<Member_Suit_Type_e>();
                }
                if (suit_type) {
                    if (Has_Only_Playables(suit_type())) {
                        suitcase->Apply_Unto(actor,
                                             suit_type(),
                                             Member_Suitcase_t::filter_out_blank_or_token_or_unplayable_objects,
                                             members.Do_Fill_Suits_Strictly(),
                                             members.Do_Unfill_Suits_To_Pack() ? Pack()() : none<Reference_t*>()());
                    } else {
                        suitcase->Apply_Unto(actor,
                                             suit_type(),
                                             Member_Suitcase_t::filter_out_blank_or_token_objects,
                                             members.Do_Fill_Suits_Strictly(),
                                             members.Do_Unfill_Suits_To_Pack() ? Pack()() : none<Reference_t*>()());
                    }
                }
            }
        }

        custom_base->Voice_Type(Voice_Type()());

        actor->Alpha(Alpha()(), main.Script(this->id));

        custom_base->Relation(skylib::Const::Actor_Base::Player(), Relation());

        custom_base->Vitality(Vitality(), false);

        if (Is_Enabled()) {
            if (actor->Is_Disabled()) {
                actor->Enable();
            }
        } else {
            if (actor->Is_Enabled()) {
                actor->Disable();
            }
        }

        if (Is_Untouchable()) {
            actor->Is_Ghost(true);
        } else {
            actor->Is_Ghost(false);
        }

        if (Has_AI()) {
            if (!actor->Has_AI()) {
                actor->Has_AI(true);
                main.Update_AI(this->id, Member_Update_AI_e::RESET_AI);
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
            if (combat_target == skylib::Const::Actor::Player() || members.Has_Member(combat_target())) {
                // we need to handle aggression also, but that needs to be done along with other factors?
                actor->Stop_Combat_And_Alarm();
                actor->actor_flags_2.Unflag(skylib::Actor_Flags_2_e::IS_ANGRY_WITH_PLAYER);
                main.Update_AI(this->id, Member_Update_AI_e::RESET_AI);
            }
        }
    }

    Member_t::operator Bool_t()
    {
        return Is_Valid();
    }

}}
