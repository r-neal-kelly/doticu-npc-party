/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/ammo.h"
#include "doticu_skylib/armor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/combat_style.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_actor_bases.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/virtual_macros.h"
#include "doticu_skylib/voice_type.h"
#include "doticu_skylib/weapon.h"

#include "npcp.inl"
#include "party.h"
#include "party_displays.h"
#include "party_expoees.h"
#include "party_followers.h"
#include "party_member.h"
#include "party_member_suit_buffer.h"
#include "party_member_suitcase.h"
#include "party_members.h"
#include "party_settlers.h"

namespace doticu_skylib { namespace doticu_npcp {

    Member_t::Save_t::Save_t() :
        member_id(),
        settler_id(),
        expoee_id(),
        display_id(),
        follower_id(),

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

        NPCP.Write(file, this->member_id);
        NPCP.Write(file, this->settler_id);
        NPCP.Write(file, this->expoee_id);
        NPCP.Write(file, this->display_id);
        NPCP.Write(file, this->follower_id);

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

        NPCP.Read(file, this->member_id);
        NPCP.Read(file, this->settler_id);
        NPCP.Read(file, this->expoee_id);
        NPCP.Read(file, this->display_id);
        NPCP.Read(file, this->follower_id);

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

        if (this->member_id && static_base && !static_base->Is_Deleted()) {
            if (!this->actual_base ||
                this->actual_base->Is_Deleted() ||
                this->actual_base->Identifiable_Static_Base() != static_base) {
                this->actual_base = static_base;
            }
        } else {
            this->member_id = none<Member_ID_t>();
            this->actual_base = none<Actor_Base_t*>();
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

    Settlers_t& Member_t::Settlers()
    {
        return NPCP.Party().Settlers();
    }

    Expoees_t& Member_t::Expoees()
    {
        return NPCP.Party().Expoees();
    }

    Displays_t& Member_t::Displays()
    {
        return NPCP.Party().Displays();
    }

    Followers_t& Member_t::Followers()
    {
        return NPCP.Party().Followers();
    }

    Member_t::Member_t() :
        state()
    {
    }

    Member_t::Member_t(some<Member_ID_t> member_id, some<Actor_t*> actor, Bool_t is_clone) :
        state()
    {
        SKYLIB_ASSERT_SOME(member_id);
        SKYLIB_ASSERT_SOME(actor);

        Save().member_id = member_id;
        Save().actual_base = actor->Actor_Base();
        Save().actor = actor;

        if (Is_Active()) { // is this necessary?
            Is_Clone(is_clone);
            // need to fill in default values
        }
    }

    Member_t::~Member_t()
    {
        if (Is_Active()) {
            if (State().custom_base) {
                Save().actor->Actor_Base(Save().actual_base(), false);
                Actor_Base_t::Destroy(State().custom_base());
                State().custom_base = none<Actor_Base_t*>();
            }
        }
        // we also need to delete things like the pack, or make them static refs
        // maybe same thing with suit buffers
        // needs to be removed from alias, probably do that in Members_t
    }

    void Member_t::On_After_New_Game()
    {
    }

    void Member_t::On_Before_Save_Game(std::ofstream& file)
    {
        if (Is_Active()) {
            // we check, because I'm not sure if creating a ref here would freeze the game.
            // we should try it.
            if (Save().actor) {
                Save().actor->Actor_Base(Actual_Base(), false);
            }
        }

        Save().Write(file);
    }

    void Member_t::On_After_Save_Game()
    {
        if (Is_Active()) {
            Actor()->Actor_Base(Custom_Base(), false);
        }
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

    Member_t::State_t& Member_t::State()
    {
        return this->state;
    }

    Member_t::Save_t& Member_t::Save()
    {
        return this->state.save;
    }

    Bool_t Member_t::Is_Active()
    {
        return Save().member_id && Save().actual_base;
    }

    Bool_t Member_t::Is_Banished()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_BANISHED);
    }

    void Member_t::Is_Banished(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().flags.Is_Flagged(Member_Flags_e::IS_BANISHED, value);
    }

    Bool_t Member_t::Is_Clone()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_CLONE);
    }

    void Member_t::Is_Clone(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().flags.Is_Flagged(Member_Flags_e::IS_CLONE, value);
    }

    Bool_t Member_t::Is_Immobile()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE);
    }

    void Member_t::Is_Immobile(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().flags.Is_Flagged(Member_Flags_e::IS_IMMOBILE, value);
    }

    Bool_t Member_t::Is_Mannequin()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN);
    }

    void Member_t::Is_Mannequin(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().flags.Is_Flagged(Member_Flags_e::IS_MANNEQUIN, value);
    }

    Bool_t Member_t::Is_Reanimated()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_REANIMATED);
    }

    void Member_t::Is_Reanimated(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().flags.Is_Flagged(Member_Flags_e::IS_REANIMATED, value);
    }

    Bool_t Member_t::Is_Sneak()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_SNEAK);
    }

    void Member_t::Is_Sneak(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().flags.Is_Flagged(Member_Flags_e::IS_SNEAK, value);
    }

    Bool_t Member_t::Is_Thrall()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().flags.Is_Flagged(Member_Flags_e::IS_THRALL);
    }

    void Member_t::Is_Thrall(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().flags.Is_Flagged(Member_Flags_e::IS_THRALL, value);
    }

    Bool_t Member_t::Is_Enabled()
    {
        SKYLIB_ASSERT(Is_Active());

        return !Is_Banished();
    }

    Bool_t Member_t::Is_Untouchable()
    {
        SKYLIB_ASSERT(Is_Active());

        return Members().Has_Untouchable_Invulnerables() && Is_Invulnerable();
    }

    Bool_t Member_t::Is_Warrior()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::WARRIOR;
    }

    Bool_t Member_t::Is_Mage()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::MAGE;
    }

    Bool_t Member_t::Is_Archer()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::ARCHER;
    }

    Bool_t Member_t::Is_Coward()
    {
        SKYLIB_ASSERT(Is_Active());

        return Member_Combat_Style_e::From_Combat_Style(Combat_Style()) == Member_Combat_Style_e::COWARD;
    }

    Bool_t Member_t::Is_Mortal()
    {
        SKYLIB_ASSERT(Is_Active());

        return Vitality() == Member_Vitality_e::MORTAL;
    }

    Bool_t Member_t::Is_Protected()
    {
        SKYLIB_ASSERT(Is_Active());

        return Vitality() == Member_Vitality_e::PROTECTED;
    }

    Bool_t Member_t::Is_Essential()
    {
        SKYLIB_ASSERT(Is_Active());

        return Vitality() == Member_Vitality_e::ESSENTIAL;
    }

    Bool_t Member_t::Is_Invulnerable()
    {
        SKYLIB_ASSERT(Is_Active());

        return Vitality() == Member_Vitality_e::INVULNERABLE;
    }

    Bool_t Member_t::Has_AI()
    {
        SKYLIB_ASSERT(Is_Active());

        return !Is_Banished() && !Is_Mannequin();
    }

    Bool_t Member_t::Has_Suit(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Has_Suit_e flag = type().As_Member_Flag_Has_Suit();
        SKYLIB_ASSERT_SOME(flag);

        return Save().flags_has_suit.Is_Flagged(flag);
    }

    void Member_t::Has_Suit(some<Member_Suit_Type_e> type, Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Has_Suit_e flag = type().As_Member_Flag_Has_Suit();
        SKYLIB_ASSERT_SOME(flag);

        Save().flags_has_suit.Is_Flagged(flag, value);
    }

    Bool_t Member_t::Has_Only_Playables(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Only_Playables_e flag = type().As_Member_Flag_Only_Playables();
        SKYLIB_ASSERT_SOME(flag);

        return Save().flags_only_playables.Is_Flagged(flag);
    }

    void Member_t::Has_Only_Playables(some<Member_Suit_Type_e> type, Bool_t value)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Member_Flags_Only_Playables_e flag = type().As_Member_Flag_Only_Playables();
        SKYLIB_ASSERT_SOME(flag);

        Save().flags_only_playables.Is_Flagged(flag, value);
    }

    some<Member_ID_t> Member_t::Member_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().member_id();
    }

    maybe<Settler_ID_t> Member_t::Settler_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().settler_id;
    }

    maybe<Expoee_ID_t> Member_t::Expoee_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().expoee_id;
    }

    maybe<Display_ID_t> Member_t::Display_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().display_id;
    }

    maybe<Follower_ID_t> Member_t::Follower_ID()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().follower_id;
    }

    some<Alias_Reference_t*> Member_t::Alias()
    {
        SKYLIB_ASSERT(Is_Active());

        return Members().Alias(Member_ID());
    }

    some<Actor_Base_t*> Member_t::Actual_Base()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().actual_base();
    }

    some<Actor_Base_t*> Member_t::Custom_Base()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Actor_Base_t*>& custom_base = State().custom_base;
        if (!custom_base) {
            custom_base = Actor_Base_t::Create_Temporary_Copy(Actual_Base());
            SKYLIB_ASSERT_SOME(custom_base);
        }

        return custom_base();
    }

    some<Actor_t*> Member_t::Actor()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Actor_t*>& actor = Save().actor;
        if (!actor || actor->Is_Deleted()) {
            some<Actor_Base_t*> actual_base = Actual_Base();
            actor = Actor_t::Create(actual_base, !actual_base->Does_Respawn(), true, false);
            SKYLIB_ASSERT_SOME(actor);
        }

        return actor();
    }

    maybe<Settler_t*> Member_t::Settler()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Settler_ID_t> settler_id = Settler_ID();
        if (settler_id) {
            Settler_t& settler = Settlers().Settler(settler_id());
            SKYLIB_ASSERT(settler.Member_ID() == Member_ID());
            return &settler;
        } else {
            return none<Settler_t*>();
        }
    }

    maybe<Expoee_t*> Member_t::Expoee()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Expoee_ID_t> expoee_id = Expoee_ID();
        if (expoee_id) {
            Expoee_t& expoee = Expoees().Expoee(expoee_id());
            SKYLIB_ASSERT(expoee.Member_ID() == Member_ID());
            return &expoee;
        } else {
            return none<Expoee_t*>();
        }
    }

    maybe<Display_t*> Member_t::Display()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Display_ID_t> display_id = Display_ID();
        if (display_id) {
            Display_t& display = Displays().Display(display_id());
            SKYLIB_ASSERT(display.Member_ID() == Member_ID());
            return &display;
        } else {
            return none<Display_t*>();
        }
    }

    maybe<Follower_t*> Member_t::Follower()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Follower_ID_t> follower_id = Follower_ID();
        if (follower_id) {
            Follower_t& follower = Followers().Follower(follower_id());
            SKYLIB_ASSERT(follower.Member_ID() == Member_ID());
            return &follower;
        } else {
            return none<Follower_t*>();
        }
    }

    maybe<Member_Alpha_t> Member_t::Alpha()
    {
        SKYLIB_ASSERT(Is_Active());

        if (!Is_Enabled()) {
            return 0.0f;
        } else {
            return Save().alpha;
        }
    }

    void Member_t::Alpha(some<Member_Alpha_t> alpha)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(alpha);

        Save().alpha = alpha;
    }

    maybe<Combat_Style_t*> Member_t::Combat_Style()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Combat_Style_t*> combat_style = Save().combat_style;
        if (!combat_style) {
            combat_style = Actual_Base()->Combat_Style();
        }

        return combat_style;
    }

    void Member_t::Combat_Style(maybe<Combat_Style_t*> combat_style)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().combat_style = combat_style;
    }

    void Member_t::Combat_Style(maybe<Member_Combat_Style_e> combat_style)
    {
        SKYLIB_ASSERT(Is_Active());

        if (combat_style) {
            Combat_Style(combat_style().As_Combat_Style());
        } else {
            Combat_Style(none<Combat_Style_t*>());
        }
    }

    maybe<Spell_t*> Member_t::Ghost_Ability()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().ghost_ability;
    }

    void Member_t::Ghost_Ability(maybe<Spell_t*> ghost_ability)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().ghost_ability = ghost_ability;
    }

    String_t Member_t::Name()
    {
        SKYLIB_ASSERT(Is_Active());

        String_t name = Save().name;
        if (!name) {
            name = Actor()->Name();
        }

        return name;
    }

    void Member_t::Name(String_t name)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().name = name;
    }

    maybe<Outfit_t*> Member_t::Outfit()
    {
        SKYLIB_ASSERT(Is_Active());

        return Save().outfit; // maybe should grab from base
    }

    void Member_t::Outfit(maybe<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().outfit = outfit;
    }

    some<Reference_t*> Member_t::Pack()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Reference_t*>& pack = Save().pack;
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
        SKYLIB_ASSERT(Is_Active());

        return Save().rating;
    }

    void Member_t::Rating(maybe<Member_Rating_t> rating)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().rating = rating;
    }

    some<Member_Relation_e> Member_t::Relation()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Member_Relation_e> relation = Save().relation;
        if (!relation) {
            relation = Actual_Base()->Relation(Const::Actor_Base::Player());
            SKYLIB_ASSERT_SOME(relation);
        }

        return relation();
    }

    void Member_t::Relation(maybe<Member_Relation_e> relation)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().relation = relation;
    }

    maybe<Member_Suit_Type_e> Member_t::Suit_Type()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Member_Suit_Type_e> suit_type = Save().suit_type;
        if (suit_type && Members().Do_Change_Suits_Automatically()) {
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
            /*} else if (Has_Suit(Member_Suit_Type_e::FOLLOWER) && Party().Is_Follower(ID())) {
                return Member_Suit_Type_e::FOLLOWER;
            } else if (Has_Suit(Member_Suit_Type_e::GUARD) && Party().Is_Active_Guard(ID())) {
                return Member_Suit_Type_e::GUARD;
            } else if (Has_Suit(Member_Suit_Type_e::EATER) && Party().Is_Active_Eater(ID())) {
                return Member_Suit_Type_e::EATER;
            } else if (Has_Suit(Member_Suit_Type_e::SITTER) && Party().Is_Active_Sitter(ID())) {
                return Member_Suit_Type_e::SITTER;
            } else if (Has_Suit(Member_Suit_Type_e::SLEEPER) && Party().Is_Active_Sleeper(ID())) {
                return Member_Suit_Type_e::SLEEPER;
            } else if (Has_Suit(Member_Suit_Type_e::SANDBOXER) && Party().Is_Active_Sandboxer(ID())) {
                return Member_Suit_Type_e::SANDBOXER;*/
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
        SKYLIB_ASSERT(Is_Active());

        if (type) {
            SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
            SKYLIB_ASSERT(Has_Suit(type()));
            Save().suit_type = type;
        } else {
            Save().suit_type = none<Member_Suit_Type_e>();
        }
    }

    some<Member_Suitcase_t*> Member_t::Suitcase()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Member_Suitcase_t*>& suitcase = Save().suitcase;
        if (!suitcase) {
            suitcase = Member_Suitcase_t::Create();
            SKYLIB_ASSERT_SOME(suitcase);
        }

        return suitcase();
    }

    some<Member_Vitality_e> Member_t::Vitality()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Member_Vitality_e> vitality = Save().vitality;
        if (!vitality) {
            vitality = Actual_Base()->Vitality();
            SKYLIB_ASSERT_SOME(vitality);
        }

        return vitality();
    }

    void Member_t::Vitality(maybe<Member_Vitality_e> vitality)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().vitality = vitality;
    }

    some<Voice_Type_t*> Member_t::Voice_Type()
    {
        SKYLIB_ASSERT(Is_Active());

        maybe<Voice_Type_t*> voice_type = Save().voice_type;
        if (!voice_type) {
            voice_type = Actual_Base()->Voice_Type();
            if (!voice_type) {
                voice_type = Actor()->Race_Voice_Type();
                if (!voice_type) {
                    voice_type = Consts_t::NPCP::Voice_Type::Blank();
                }
            }
            SKYLIB_ASSERT_SOME(voice_type);
        }

        return voice_type();
    }

    void Member_t::Voice_Type(maybe<Voice_Type_t*> voice_type)
    {
        SKYLIB_ASSERT(Is_Active());

        Save().voice_type = voice_type;
    }

    void Member_t::Tokenize(some<Bound_Object_t*> object, Container_Entry_Count_t count)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT(count > 0);

        Reference_Container_t container = Actor()->Container();
        some<Reference_Container_Entry_t*> entry = container.Some_Entry(object);
        if (entry->Non_Extra_Lists_Count() != count) {
            entry->Decrement_Count(container, Container_Entry_Count_t::_MAX_);
            entry->Increment_Count(container, count);
            Party().Update_AI(Member_ID(), Member_Update_AI_e::EVALUATE_PACKAGE);
        }
    }

    void Member_t::Untokenize(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(object);

        Reference_Container_t container = Actor()->Container();
        maybe<Reference_Container_Entry_t*> entry = container.Maybe_Entry(object);
        if (entry && entry->Non_Extra_Lists_Count() > 0) {
            entry->Decrement_Count(container, Container_Entry_Count_t::_MAX_);
            Party().Update_AI(Member_ID(), Member_Update_AI_e::EVALUATE_PACKAGE);
        }
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(type);
        Has_Suit(type, true);
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
        SKYLIB_ASSERT_SOME(outfit);

        Remove_Suit(type);
        Has_Suit(type, true);

        Member_Suit_Buffer_t buffer;
        outfit->Add_Items_To(buffer.reference);
        Suitcase()->Move_From(buffer.reference,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Container_t*> container)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
        SKYLIB_ASSERT_SOME(container);

        Remove_Suit(type);
        Has_Suit(type, true);

        Member_Suit_Buffer_t buffer;
        container->Container_Add_Items_To(buffer.reference);
        Suitcase()->Move_From(buffer.reference,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Actor_Base_t*> actor_base)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);
        SKYLIB_ASSERT_SOME(actor_base);

        Remove_Suit(type);
        Has_Suit(type, true);

        Member_Suit_Buffer_t buffer;
        maybe<Outfit_t*> outfit = actor_base->Default_Outfit();
        actor_base->Container_Add_Items_To(buffer.reference);
        if (outfit) {
            outfit->Add_Items_To(buffer.reference);
        }
        Suitcase()->Move_From(buffer.reference,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
    }

    void Member_t::Add_Suit(some<Member_Suit_Type_e> type, some<Reference_t*> reference, Bool_t do_copy)
    {
        SKYLIB_ASSERT(Is_Active());
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
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        Remove_Suit(type);
        Has_Suit(type, true);

        Member_Suit_Buffer_t buffer;

        maybe<Armor_t*> aura = suit_template.armor.Aura(Members().Fill_Suit_Aura_Percent()());
        maybe<Armor_t*> body = suit_template.armor.Body(Members().Fill_Suit_Body_Percent()());
        maybe<Armor_t*> feet = suit_template.armor.Feet(Members().Fill_Suit_Feet_Percent()());
        maybe<Armor_t*> finger = suit_template.armor.Finger(Members().Fill_Suit_Finger_Percent()());
        maybe<Armor_t*> forearm = suit_template.armor.Forearm(Members().Fill_Suit_Forearm_Percent()());
        maybe<Armor_t*> forehead = suit_template.armor.Forehead(Members().Fill_Suit_Forehead_Percent()());
        maybe<Armor_t*> hands = suit_template.armor.Hands(Members().Fill_Suit_Hands_Percent()());
        maybe<Armor_t*> head = suit_template.armor.Head(Members().Fill_Suit_Head_Percent()());
        maybe<Armor_t*> neck = suit_template.armor.Neck(Members().Fill_Suit_Neck_Percent()());

        if (aura) buffer.reference->Add_Item(aura(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (body) buffer.reference->Add_Item(body(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (feet) buffer.reference->Add_Item(feet(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (finger) buffer.reference->Add_Item(finger(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (forearm) buffer.reference->Add_Item(forearm(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (forehead) buffer.reference->Add_Item(forehead(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (hands) buffer.reference->Add_Item(hands(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (head) buffer.reference->Add_Item(head(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        if (neck) buffer.reference->Add_Item(neck(), none<Extra_List_t*>(), 1, none<Reference_t*>());

        if (suit_template.weapon_a) {
            buffer.reference->Add_Item(suit_template.weapon_a(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        }
        if (suit_template.weapon_b) {
            buffer.reference->Add_Item(suit_template.weapon_b(), none<Extra_List_t*>(), 1, none<Reference_t*>());
        }
        if (suit_template.ammo) {
            buffer.reference->Add_Item(suit_template.ammo(), none<Extra_List_t*>(), 100, none<Reference_t*>());
        }

        Suitcase()->Move_From(buffer.reference,
                              type,
                              Member_Suitcase_t::filter_out_blank_or_token_objects,
                              Member_Suitcase_t::filter_out_quest_extra_lists);
    }

    void Member_t::Remove_Suit(some<Member_Suit_Type_e> type)
    {
        SKYLIB_ASSERT(Is_Active());
        SKYLIB_ASSERT_SOME(type);
        SKYLIB_ASSERT(type != Member_Suit_Type_e::ACTIVE);

        if (Has_Suit(type)) {
            Suitcase()->Remove_Suit(Members().Do_Unfill_Suits_Into_Pack() ? Pack()() : none<Reference_t*>()(), type);
            Has_Suit(type, false);
        }
    }

    void Member_t::Evaluate_In_Parallel(std::mutex& parallel_lock)
    {
        SKYLIB_ASSERT(Is_Active());

        // we may want a different smaller branch if the actor is in combat, or a separate func to call
        Members_t& members = Members();
        some<Actor_t*> actor = Actor();
        some<Actor_Base_t*> custom_base = Custom_Base();

        Vector_t<some<Spell_t*>> spells_to_add;
        spells_to_add.reserve(4);

        actor->Actor_Base(Custom_Base(), false);

        Tokenize(Consts_t::NPCP::Misc::Token::Member(), Member_ID()() + 1);
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
                actor->Is_Forced_To_Sneak(true, Party().Script(Member_ID()));
            }
        } else {
            Untokenize(Consts_t::NPCP::Misc::Token::Sneak());

            if (actor->Is_Forced_To_Sneak()) {
                actor->Is_Forced_To_Sneak(false, Party().Script(Member_ID()));
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

        /*maybe<Spell_t*> ghost_ability = Ghost_Ability();
        for (size_t idx = 0, end = members.vanilla_ghost_abilities.size(); idx < end; idx += 1) {
            some<Spell_t*> vanilla_ghost_ability = members.vanilla_ghost_abilities[idx];
            if (vanilla_ghost_ability != ghost_ability) {
                actor->Remove_Spell(members.vanilla_ghost_abilities[idx]);
            }
        }
        if (ghost_ability) {
            spells_to_add.push_back(ghost_ability());
        }*/

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
                                             members.Do_Suits_Strictly(),
                                             members.Do_Unfill_Suits_Into_Pack() ? Pack()() : none<Reference_t*>()());
                    } else {
                        suitcase->Apply_Unto(actor,
                                             suit_type(),
                                             Member_Suitcase_t::filter_out_blank_or_token_objects,
                                             members.Do_Suits_Strictly(),
                                             members.Do_Unfill_Suits_Into_Pack() ? Pack()() : none<Reference_t*>()());
                    }
                }
            }
        }

        custom_base->Voice_Type(Voice_Type()());

        actor->Alpha(Alpha()(), Party().Script(Member_ID()));

        custom_base->Relation(Const::Actor_Base::Player(), Relation());

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
                Party().Update_AI(Member_ID(), Member_Update_AI_e::RESET_AI);
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
            if (combat_target == Const::Actor::Player() || members.Has(combat_target())) {// just check token to make it parallel
                // we need to handle aggression also, but that needs to be done along with other factors?
                actor->Stop_Combat_And_Alarm();
                actor->actor_flags_2.Unflag(Actor_Flags_2_e::IS_ANGRY_WITH_PLAYER);
                Party().Update_AI(Member_ID(), Member_Update_AI_e::RESET_AI);
            }
        }
    }

}}
