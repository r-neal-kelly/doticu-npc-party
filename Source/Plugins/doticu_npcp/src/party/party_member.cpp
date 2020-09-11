/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "actor2.h"
#include "actor_base2.h"
#include "codes.h"
#include "consts.h"
#include "form.h"
#include "object_ref.h"
#include "outfit2.h"
#include "papyrus.inl"
#include "quest.h"
#include "spell.h"
#include "utils.h"
#include "vars.h"
#include "xlist.h"

#include "party/party_alias.inl"
#include "party/party_player.h"
#include "party/party_movee.h"
#include "party/party_npcs.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_mannequins.h"
#include "party/party_followers.h"
#include "party/party_follower.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Member_t::Class_Name()
    {
        static String_t class_name = String_t("doticu_npcp_member");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Member_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Variable_t* Member_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Variable_t* Member_t::Actor_Variable() { DEFINE_VARIABLE("p_ref_actor"); }
    Variable_t* Member_t::Pack_Variable() { DEFINE_VARIABLE("p_container_pack"); }
    Variable_t* Member_t::Mannequin_Marker_Variable() { DEFINE_VARIABLE("p_marker_mannequin"); }
    Variable_t* Member_t::Display_Marker_Variable() { DEFINE_VARIABLE("p_marker_display"); }
    Variable_t* Member_t::Undisplay_Marker_Variable() { DEFINE_VARIABLE("p_marker_undisplay"); }
    Variable_t* Member_t::Vanilla_Outfit_Variable() { DEFINE_VARIABLE("p_outfit_vanilla"); }
    Variable_t* Member_t::Default_Outfit_Variable() { DEFINE_VARIABLE("p_outfit_default"); }

    Variable_t* Member_t::Member_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_member"); }
    Variable_t* Member_t::Immobile_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_immobile"); }
    Variable_t* Member_t::Settler_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_settler"); }
    Variable_t* Member_t::Thrall_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_thrall"); }
    Variable_t* Member_t::Follower_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_follower"); }
    Variable_t* Member_t::Vanilla_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_vanilla"); }
    Variable_t* Member_t::Default_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_default"); }
    Variable_t* Member_t::Current_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_current"); }
    Variable_t* Member_t::Backup_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_auto_backup"); }

    Variable_t* Member_t::Is_Locked_Variable() { DEFINE_VARIABLE("p_is_locked"); }
    Variable_t* Member_t::Is_Clone_Variable() { DEFINE_VARIABLE("p_is_clone"); }
    Variable_t* Member_t::Is_Immobile_Variable() { DEFINE_VARIABLE("p_is_immobile"); }
    Variable_t* Member_t::Is_Settler_Variable() { DEFINE_VARIABLE("p_is_settler"); }
    Variable_t* Member_t::Is_Thrall_Variable() { DEFINE_VARIABLE("p_is_thrall"); }
    Variable_t* Member_t::Is_Paralyzed_Variable() { DEFINE_VARIABLE("p_is_paralyzed"); }
    Variable_t* Member_t::Is_Mannequin_Variable() { DEFINE_VARIABLE("p_is_mannequin"); }
    Variable_t* Member_t::Is_Display_Variable() { DEFINE_VARIABLE("p_is_display"); }
    Variable_t* Member_t::Is_Reanimated_Variable() { DEFINE_VARIABLE("p_is_reanimated"); }
    Variable_t* Member_t::Do_Skip_On_Load_Variable() { DEFINE_VARIABLE("p_do_skip_on_load"); }

    Variable_t* Member_t::Style_Variable() { DEFINE_VARIABLE("p_code_style"); }
    Variable_t* Member_t::Vitality_Variable() { DEFINE_VARIABLE("p_code_vitality"); }
    Variable_t* Member_t::Outfit2_Variable() { DEFINE_VARIABLE("p_code_outfit2"); }
    Variable_t* Member_t::Rating_Variable() { DEFINE_VARIABLE("p_int_rating"); }

    Variable_t* Member_t::Name_Variable() { DEFINE_VARIABLE("p_str_name"); }

    Variable_t* Member_t::Previous_Factions_Variable() { DEFINE_VARIABLE("p_prev_factions"); }
    Variable_t* Member_t::Previous_Crime_Faction_Variable() { DEFINE_VARIABLE("p_prev_faction_crime"); }
    Variable_t* Member_t::Previous_Potential_Follower_Faction_Variable() { DEFINE_VARIABLE("p_prev_faction_potential_follower"); }
    Variable_t* Member_t::Previous_No_Body_Cleanup_Faction_Variable() { DEFINE_VARIABLE("p_prev_faction_no_body_cleanup"); }
    Variable_t* Member_t::Previous_Aggression_Variable() { DEFINE_VARIABLE("p_prev_aggression"); }
    Variable_t* Member_t::Previous_Confidence_Variable() { DEFINE_VARIABLE("p_prev_confidence"); }
    Variable_t* Member_t::Previous_Assistance_Variable() { DEFINE_VARIABLE("p_prev_assistance"); }
    Variable_t* Member_t::Previous_Morality_Variable() { DEFINE_VARIABLE("p_prev_morality"); }

    Actor_t* Member_t::Actor()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor_Variable()->Actor();
        if (actor == nullptr) {
            actor = Alias_t::Actor();
            NPCP_ASSERT(actor);
            Actor_Variable()->Pack(actor);
        }
        return actor;
    }

    Follower_t* Member_t::Follower()
    {
        NPCP_ASSERT(Is_Filled());
        return Followers_t::Self()->From_Actor(Actor());
    }

    Reference_t* Member_t::Pack()
    {
        NPCP_ASSERT(Is_Filled());
        return Pack_Variable()->Reference();
    }

    Reference_t* Member_t::Settler_Marker()
    {
        NPCP_ASSERT(Is_Filled());
        return static_cast<Reference_t*>(Consts::Settler_Markers_Formlist()->forms.entries[ID()]);
    }

    Reference_t* Member_t::Mannequin_Marker()
    {
        NPCP_ASSERT(Is_Filled());
        return Mannequin_Marker_Variable()->Reference();
    }

    Reference_t* Member_t::Display_Marker()
    {
        NPCP_ASSERT(Is_Filled());
        return Display_Marker_Variable()->Reference();
    }

    Reference_t* Member_t::Undisplay_Marker()
    {
        NPCP_ASSERT(Is_Filled());
        return Undisplay_Marker_Variable()->Reference();
    }

    Cell_t* Member_t::Cell()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor()->parentCell;
    }

    Int_t Member_t::Style()
    {
        NPCP_ASSERT(Is_Filled());
        return Style_Variable()->Int();
    }

    Int_t Member_t::Vitality()
    {
        NPCP_ASSERT(Is_Filled());
        return Vitality_Variable()->Int();
    }

    Int_t Member_t::Outfit2()
    {
        NPCP_ASSERT(Is_Filled());
        return Outfit2_Variable()->Int();
    }

    Int_t Member_t::Rating()
    {
        NPCP_ASSERT(Is_Filled());
        return Rating_Variable()->Int();
    }

    Int_t Member_t::Relationship_Rank()
    {
        NPCP_ASSERT(Is_Filled());

        return static_cast<Int_t>(Relationships_t::Self()->Relationship_Rank(
            Actor2::Dynamic_Base(Consts::Player_Actor()),
            Actor2::Dynamic_Base(Actor())
        ));
    }

    String_t Member_t::Sex()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Sex_String(Actor());
    }

    String_t Member_t::Race()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Race(Actor());
    }

    String_t Member_t::Base_Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Get_Base_Name(Actor());
    }

    String_t Member_t::Reference_Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Get_Ref_Name(Actor());
    }

    String_t Member_t::Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Name_Variable()->String();
    }

    String_t Member_t::Rating_Stars()
    {
        NPCP_ASSERT(Is_Filled());

        Int_t rating = Rating();
        if (rating < 1) {
            return "-";
        } else if (rating == 1) {
            return "*";
        } else if (rating == 2) {
            return "**";
        } else if (rating == 3) {
            return "***";
        } else if (rating == 4) {
            return "****";
        } else if (rating == 5) {
            return "*****";
        } else {
            NPCP_ASSERT(false);
        }
    }

    String_t Member_t::Relationship_Rank_String()
    {
        NPCP_ASSERT(Is_Filled());

        return Relationship_t::Rank_To_String(
            Relationships_t::Self()->Relationship_Rank(
                Actor2::Dynamic_Base(Consts::Player_Actor()),
                Actor2::Dynamic_Base(Actor())
            )
        );
    }

    Outfit_t* Member_t::Vanilla_Outfit()
    {
        NPCP_ASSERT(Is_Filled());
        return Vanilla_Outfit_Variable()->Outfit();
    }

    Outfit_t* Member_t::Default_Outfit()
    {
        NPCP_ASSERT(Is_Filled());
        Outfit_t* outfit = Default_Outfit_Variable()->Outfit();
        if (!outfit) {
            outfit = NPCS_t::Self()->Default_Outfit(Actor());
            Default_Outfit_Variable()->Pack(outfit);
        }
        return outfit;
    }

    Outfit2_t* Member_t::Member_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Variable_t* variable = Member_Outfit2_Variable();

        Outfit2_t* outfit2 = nullptr;
        if (variable->Has_Object()) {
            outfit2 = static_cast<Outfit2_t*>(variable->Reference());
        } else {
            outfit2 = Outfit2_t::Create_Member(Actor(), Pack());
            variable->Pack(outfit2);
        }
        NPCP_ASSERT(outfit2);

        return outfit2;
    }

    Outfit2_t* Member_t::Immobile_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Variable_t* variable = Immobile_Outfit2_Variable();

        Outfit2_t* outfit2 = nullptr;
        if (variable->Has_Object()) {
            outfit2 = static_cast<Outfit2_t*>(variable->Reference());
        } else {
            outfit2 = Outfit2_t::Create_Immobile();
            variable->Pack(outfit2);
        }
        NPCP_ASSERT(outfit2);

        return outfit2;
    }

    Outfit2_t* Member_t::Settler_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Variable_t* variable = Settler_Outfit2_Variable();

        Outfit2_t* outfit2 = nullptr;
        if (variable->Has_Object()) {
            outfit2 = static_cast<Outfit2_t*>(variable->Reference());
        } else {
            outfit2 = Outfit2_t::Create_Settler();
            variable->Pack(outfit2);
        }
        NPCP_ASSERT(outfit2);

        return outfit2;
    }

    Outfit2_t* Member_t::Thrall_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Variable_t* variable = Thrall_Outfit2_Variable();

        Outfit2_t* outfit2 = nullptr;
        if (variable->Has_Object()) {
            outfit2 = static_cast<Outfit2_t*>(variable->Reference());
        } else {
            outfit2 = Outfit2_t::Create_Thrall();
            variable->Pack(outfit2);
        }
        NPCP_ASSERT(outfit2);

        return outfit2;
    }

    Outfit2_t* Member_t::Follower_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Variable_t* variable = Follower_Outfit2_Variable();

        Outfit2_t* outfit2 = nullptr;
        if (variable->Has_Object()) {
            outfit2 = static_cast<Outfit2_t*>(variable->Reference());
        } else {
            outfit2 = Outfit2_t::Create_Follower();
            variable->Pack(outfit2);
        }
        NPCP_ASSERT(outfit2);

        return outfit2;
    }

    Outfit2_t* Member_t::Vanilla_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Variable_t* variable = Vanilla_Outfit2_Variable();

        Outfit2_t* outfit2 = nullptr;
        if (variable->Has_Object()) {
            outfit2 = static_cast<Outfit2_t*>(variable->Reference());
        } else {
            outfit2 = Outfit2_t::Create_Vanilla();
            variable->Pack(outfit2);
        }
        NPCP_ASSERT(outfit2);

        return outfit2;
    }

    Outfit2_t* Member_t::Default_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Variable_t* variable = Default_Outfit2_Variable();

        Outfit2_t* outfit2 = nullptr;
        if (variable->Has_Object()) {
            outfit2 = static_cast<Outfit2_t*>(variable->Reference());
        } else {
            outfit2 = Outfit2_t::Create_Default(Actor());
            variable->Pack(outfit2);
        }
        NPCP_ASSERT(outfit2);

        return outfit2;
    }

    Outfit2_t* Member_t::Current_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>(Current_Outfit2_Variable()->Reference());
        NPCP_ASSERT(outfit2);
        return outfit2;
    }

    Outfit2_t* Member_t::Backup_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>(Backup_Outfit2_Variable()->Reference());
        NPCP_ASSERT(outfit2);
        return outfit2;
    }

    Bool_t Member_t::Is_Ready()
    {
        return Is_Filled() && Actor_Variable()->Has_Object();
    }

    Bool_t Member_t::Is_Unready()
    {
        return Is_Filled() && !Actor_Variable()->Has_Object();
    }

    Bool_t Member_t::Is_Loaded()
    {
        return Is_Filled() && Actor2::Is_Loaded(Actor());
    }

    Bool_t Member_t::Is_Unloaded()
    {
        return Is_Filled() && Actor2::Is_Unloaded(Actor());
    }

    Bool_t Member_t::Is_Unique()
    {
        return Is_Filled() && Actor2::Is_Unique(Actor());
    }

    Bool_t Member_t::Is_Generic()
    {
        return Is_Filled() && Actor2::Is_Generic(Actor());
    }

    Bool_t Member_t::Is_Original()
    {
        return Is_Filled() && !Is_Clone_Variable()->Bool();
    }

    Bool_t Member_t::Is_Clone()
    {
        return Is_Filled() && Is_Clone_Variable()->Bool();
    }

    Bool_t Member_t::Is_Alive()
    {
        return Is_Filled() && Actor2::Is_Alive(Actor());
    }

    Bool_t Member_t::Is_Dead()
    {
        return Is_Filled() && Actor2::Is_Dead(Actor());
    }

    Bool_t Member_t::Is_Mobile()
    {
        return Is_Filled() && !Is_Immobile_Variable()->Bool();
    }

    Bool_t Member_t::Is_Immobile()
    {
        return Is_Filled() && Is_Immobile_Variable()->Bool();
    }

    Bool_t Member_t::Is_Settler()
    {
        return Is_Filled() && Is_Settler_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Settler()
    {
        return Is_Filled() && !Is_Settler_Variable()->Bool();
    }

    Bool_t Member_t::Is_Thrall()
    {
        return Is_Filled() && Is_Thrall_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Thrall()
    {
        return Is_Filled() && !Is_Thrall_Variable()->Bool();
    }

    Bool_t Member_t::Is_Paralyzed()
    {
        return Is_Filled() && Is_Paralyzed_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Paralyzed()
    {
        return Is_Filled() && !Is_Paralyzed_Variable()->Bool();
    }

    Bool_t Member_t::Is_Mannequin()
    {
        return Is_Filled() && Is_Mannequin_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Mannequin()
    {
        return Is_Filled() && !Is_Mannequin_Variable()->Bool();
    }

    Bool_t Member_t::Is_Display()
    {
        return Is_Filled() && Is_Display_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Display()
    {
        return Is_Filled() && !Is_Display_Variable()->Bool();
    }

    Bool_t Member_t::Is_Reanimated()
    {
        return Is_Filled() && Is_Reanimated_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Reanimated()
    {
        return Is_Filled() && !Is_Reanimated_Variable()->Bool();
    }

    Bool_t Member_t::Is_Follower()
    {
        return Is_Filled() && Follower() != nullptr;
    }

    Bool_t Member_t::Isnt_Follower()
    {
        return Is_Filled() && Follower() == nullptr;
    }

    Bool_t Member_t::Is_Sneak()
    {
        if (Is_Filled()) {
            Follower_t* follower = Follower();
            return follower && follower->Is_Sneak();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Sneak()
    {
        if (Is_Filled()) {
            Follower_t* follower = Follower();
            return follower && follower->Isnt_Sneak();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Saddler()
    {
        if (Is_Filled()) {
            Follower_t* follower = Follower();
            return follower && follower->Is_Saddler();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Saddler()
    {
        if (Is_Filled()) {
            Follower_t* follower = Follower();
            return follower && follower->Isnt_Saddler();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Retreater()
    {
        if (Is_Filled()) {
            Follower_t* follower = Follower();
            return follower && follower->Is_Retreater();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Retreater()
    {
        if (Is_Filled()) {
            Follower_t* follower = Follower();
            return follower && follower->Isnt_Retreater();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Loaded_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Is_Loaded(Actor());
    }

    Bool_t Member_t::Is_Unloaded_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Is_Unloaded(Actor());
    }

    Bool_t Member_t::Is_Unique_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Is_Unique(Actor());
    }

    Bool_t Member_t::Is_Generic_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Is_Generic(Actor());
    }

    Bool_t Member_t::Is_Original_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Clone_Variable()->Bool();
    }

    Bool_t Member_t::Is_Clone_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Clone_Variable()->Bool();
    }

    Bool_t Member_t::Is_Alive_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Is_Alive(Actor());
    }

    Bool_t Member_t::Is_Dead_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Is_Dead(Actor());
    }

    Bool_t Member_t::Is_Mobile_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Immobile_Variable()->Bool();
    }

    Bool_t Member_t::Is_Immobile_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Immobile_Variable()->Bool();
    }

    Bool_t Member_t::Is_Settler_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Settler_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Settler_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Settler_Variable()->Bool();
    }

    Bool_t Member_t::Is_Thrall_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Thrall_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Thrall_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Thrall_Variable()->Bool();
    }

    Bool_t Member_t::Is_Paralyzed_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Paralyzed_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Paralyzed_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Paralyzed_Variable()->Bool();
    }

    Bool_t Member_t::Is_Mannequin_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Mannequin_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Mannequin_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Mannequin_Variable()->Bool();
    }

    Bool_t Member_t::Is_Display_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Display_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Display_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Display_Variable()->Bool();
    }

    Bool_t Member_t::Is_Reanimated_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Reanimated_Variable()->Bool();
    }

    Bool_t Member_t::Isnt_Reanimated_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return !Is_Reanimated_Variable()->Bool();
    }

    Bool_t Member_t::Is_Follower_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Follower() != nullptr;
    }

    Bool_t Member_t::Isnt_Follower_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        return Follower() == nullptr;
    }

    Bool_t Member_t::Is_Sneak_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        return follower && follower->Is_Sneak();
    }

    Bool_t Member_t::Isnt_Sneak_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Sneak();
    }

    Bool_t Member_t::Is_Saddler_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        return follower && follower->Is_Saddler();
    }

    Bool_t Member_t::Isnt_Saddler_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Saddler();
    }

    Bool_t Member_t::Is_Retreater_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        return follower && follower->Is_Retreater();
    }

    Bool_t Member_t::Isnt_Retreater_Unsafe()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Retreater();
    }

    Bool_t Member_t::Has_Same_Base(Actor_t* other_actor)
    {
        if (Is_Filled() && other_actor) {
            Actor_Base_t* alias_base = static_cast<Actor_Base_t*>(Actor()->baseForm);
            Actor_Base_t* other_base = static_cast<Actor_Base_t*>(other_actor->baseForm);
            return alias_base == other_base;
        } else {
            return false;
        }
    }

    Bool_t Member_t::Has_Same_Head(Actor_t* other_actor)
    {
        if (Is_Filled() && other_actor) {
            Actor_Base_t* alias_base = static_cast<Actor_Base_t*>(Actor()->baseForm);
            Actor_Base_t* other_base = static_cast<Actor_Base_t*>(other_actor->baseForm);
            return Actor_Base2::Has_Same_Head(alias_base, other_base);
        } else {
            return false;
        }
    }

    Bool_t Member_t::Has_Same_Base_Unsafe(Actor_t* other_actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(other_actor);
        Actor_Base_t* alias_base = static_cast<Actor_Base_t*>(Actor()->baseForm);
        Actor_Base_t* other_base = static_cast<Actor_Base_t*>(other_actor->baseForm);
        return alias_base == other_base;
    }

    Bool_t Member_t::Has_Same_Head_Unsafe(Actor_t* other_actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(other_actor);
        Actor_Base_t* alias_base = static_cast<Actor_Base_t*>(Actor()->baseForm);
        Actor_Base_t* other_base = static_cast<Actor_Base_t*>(other_actor->baseForm);
        return Actor_Base2::Has_Same_Head(alias_base, other_base);
    }

    Bool_t Member_t::Should_Unclone()
    {
        NPCP_ASSERT(Is_Filled());
        return Is_Clone() && Members_t::Self()->Should_Unclone(Actor());
    }

    Bool_t Member_t::Is_In_Location(Location_t* location)
    {
        NPCP_ASSERT(Is_Filled());
        if (location) {
            Cell_t* cell = Cell();
            if (cell) {
                ExtraLocation* xlocation = static_cast<ExtraLocation*>
                    (reinterpret_cast<XList_t*>(&cell->unk048)->GetByType(kExtraData_Location));
                return xlocation && xlocation->location == location;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void Member_t::On_Load()
    {
        if (Is_Ready()) {
            if (Do_Skip_On_Load_Variable()->Bool()) {
                Do_Skip_On_Load_Variable()->Bool(false);
            } else {
                Enforce();
            }
        }
    }

    void Member_t::On_Death(Actor_t* killer)
    {
        if (Is_Ready()) {
            Enforce_Kill(Actor());
        }
    }

    void Member_t::On_Activate(Reference_t* activator)
    {
        if (Is_Ready()) {
            Player_t* player = Player_t::Self();
            if (activator == player->Actor()) {
                Actor_t* actor = Actor();
                if (Is_Alive()) {
                    if (Actor2::Is_AI_Enabled(actor)) {
                        class Callback : public Virtual_Callback_t {
                        public:
                            Actor_t* actor;
                            Callback(Actor_t* actor) :
                                actor(actor)
                            {
                            }
                            void operator()(Variable_t* result)
                            {
                                if (result && !result->Bool()) {
                                    Actor2::Greet_Player(actor);
                                }
                            }
                        };
                        Virtual_Callback_i* callback = new Callback(actor);
                        Actor2::Is_Talking_To_Player(actor, &callback);
                    }
                    Enforce();
                } else {
                    Open_Outfit2();
                }
            }
        }
    }

    void Member_t::On_Combat_State_Changed(Actor_t* target, Int_t combat_code)
    {
        if (Is_Ready() && Is_Alive()) {
            Player_t* player = Player_t::Self();
            Actor_t* actor = Actor();

            if (target == player->Actor()) {
                Actor2::Pacify(actor);
            } else if (Members_t::Self()->Has_Actor(target)) {
                Actor2::Pacify(actor);
                Actor2::Pacify(target);
            }

            if (Is_Follower()) {
                if (combat_code == CODES::COMBAT::YES) {
                    player->Begin_Combat();
                }
            }
        }
    }

    void Member_t::On_Hit(Reference_t* attacker,
                          Form_t* tool,
                          Projectile_Base_t* projectile,
                          Bool_t is_power,
                          Bool_t is_sneak,
                          Bool_t is_bash,
                          Bool_t is_blocked)
    {
        if (Is_Ready() && Is_Alive_Unsafe()) {
            Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(Actor());
            if (value_owner->Get_Actor_Value(Actor_Value_t::HEALTH) <= 0.0) {
                Int_t vitality = Vitality();
                if (vitality == CODES::VITALITY::MORTAL ||
                    vitality == CODES::VITALITY::PROTECTED && attacker == Player_t::Self()->Actor()) {
                    if (tool->formType != kFormType_Spell || Spell::Can_Damage_Health(static_cast<Spell_t*>(tool))) {
                        Kill();
                    }
                }
            } else if (Vitality() == CODES::VITALITY::INVULNERABLE) {
                value_owner->Restore_Actor_Value(Actor_Modifier_t::DAMAGE, Actor_Value_t::HEALTH, 1000000000.0f);
            }
        }
    }

    void Member_t::On_Package_Change(Package_t* new_package)
    {
        Enforce_Name(Actor(), Name());
    }

    void Member_t::Lock(Callback_t<Member_t*>* on_lock, Float_t interval, Float_t limit)
    {
        Alias_t::Lock(this, on_lock, interval, limit);
    }

    void Member_t::Unlock()
    {
        Alias_t::Unlock(this);
    }

    void Member_t::Fill(Actor_t* actor, Bool_t is_clone, Callback_t<Int_t, Member_t*>** user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<Int_t, Member_t*>;

        struct VCallback : public Virtual_Callback_t {
        public:
            Member_t* member;
            Actor_t* actor;
            Bool_t is_clone;
            UCallback_t* user_callback;
            VCallback(Member_t* member, Actor_t* actor, Bool_t is_clone, UCallback_t* user_callback) :
                member(member), actor(actor), is_clone(is_clone), user_callback(user_callback)
            {
            }
            void operator()(Variable_t* result)
            {
                member->Create(actor, is_clone);
                user_callback->operator()(CODES::SUCCESS, member);
                delete user_callback;
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this, actor, is_clone, *user_callback);
        Alias_t::Fill(actor, &vcallback);
    }

    void Member_t::Unfill(Callback_t<Int_t, Actor_t*>** user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<Int_t, Actor_t*>;

        struct Destroy_Callback : public Callback_t<> {
            Member_t* member;
            Actor_t* actor;
            UCallback_t* user_callback;
            Destroy_Callback(Member_t* member, Actor_t* actor, UCallback_t* user_callback) :
                member(member), actor(actor), user_callback(user_callback)
            {
            }
            void operator()()
            {
                struct VCallback : public Virtual_Callback_t {
                    Actor_t* actor;
                    UCallback_t* user_callback;
                    VCallback(Actor_t* actor, UCallback_t* user_callback) :
                        actor(actor), user_callback(user_callback)
                    {
                    }
                    void operator()(Variable_t* result)
                    {
                        user_callback->operator()(CODES::SUCCESS, actor);
                        delete user_callback;
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback(actor, user_callback);
                member->Alias_t::Unfill(&vcallback);
            }
        };
        Callback_t<>* destroy_callback = new Destroy_Callback(this, Actor(), *user_callback);
        Destroy(&destroy_callback);
    }

    void Member_t::Create(Actor_t* actor, Bool_t is_clone)
    {
        Class_Info_t* reference_class_info = Object_Ref::Class_Info();

        Actor_Variable()->Pack(actor);
        Pack_Variable()->Pack(Object_Ref::Create_Container());
        Mannequin_Marker_Variable()->None(reference_class_info);
        Display_Marker_Variable()->None(reference_class_info);
        Undisplay_Marker_Variable()->None(reference_class_info);

        Outfit_t* default_outfit = NPCS_t::Self()->Default_Outfit(actor);
        NPCP_ASSERT(default_outfit);
        Vanilla_Outfit_Variable()->Pack(default_outfit);
        Default_Outfit_Variable()->Pack(default_outfit);

        Is_Clone_Variable()->Bool(is_clone);
        Is_Immobile_Variable()->Bool(false);
        Is_Settler_Variable()->Bool(false);
        Is_Thrall_Variable()->Bool(false);
        Is_Paralyzed_Variable()->Bool(false);
        Is_Mannequin_Variable()->Bool(false);
        Is_Display_Variable()->Bool(false);
        Is_Reanimated_Variable()->Bool(false);

        Rating_Variable()->Int(0);

        Name_Variable()->String(Actor2::Get_Name(actor));

        Backup_State(actor);

        Enforce_Member(actor);
        Stylize(Vars::Default_Style());
        Vitalize(Vars::Default_Vitality());

        Update_Outfit2(CODES::OUTFIT2::MEMBER);
        Enforce_Outfit2(actor);

        if (is_clone) {
            Actor2::Greet_Player(actor);
        }
    }

    void Member_t::Destroy(Callback_t<>** user_callback)
    {
        NPCP_ASSERT(user_callback);

        using UCallback_t = Callback_t<>;

        if (Is_Follower()) {
            struct Remove_Callback : public Callback_t<Int_t, Member_t*> {
                UCallback_t* user_callback;
                Remove_Callback(UCallback_t* user_callback) :
                    user_callback(user_callback)
                {
                }
                void operator()(Int_t code, Member_t* member)
                {
                    member->Destroy(&user_callback);
                }
            };
            Callback_t<Int_t, Member_t*>* remove_callback = new Remove_Callback(*user_callback);
            Followers_t::Self()->Remove_Follower(this, &remove_callback);
        } else {
            Actor_t* actor = Actor();
            Class_Info_t* actor_class_info = Class_Info_t::Fetch(Actor_t::kTypeID, true);
            Class_Info_t* reference_class_info = Object_Ref::Class_Info();
            Class_Info_t* outfit1_class_info = Class_Info_t::Fetch(Outfit_t::kTypeID, true);
            Class_Info_t* outfit2_class_info = Outfit2_t::Class_Info();
            Class_Info_t* faction_class_info = Class_Info_t::Fetch(Faction_t::kTypeID, true);

            Unvitalize();
            Unstylize();
            if (Is_Reanimated()) {
                Destroy_Reanimated(actor);
            }
            if (Is_Display()) {
                Destroy_Display(actor);
            }
            if (Is_Mannequin()) {
                Destroy_Mannequin(actor);
            }
            if (Is_Paralyzed()) {
                Destroy_Paralyzed(actor);
            }
            if (Is_Thrall()) {
                Destroy_Thrall(actor);
            }
            if (Is_Settler()) {
                Destroy_Settler(actor);
            }
            if (Is_Immobile()) {
                Destroy_Immobile(actor);
            }
            Destroy_Member(actor);

            Restore_State(actor);
            Destroy_Outfit2s();
            Destroy_Containers();

            Previous_Morality_Variable()->Float(0.0f);
            Previous_Assistance_Variable()->Float(0.0f);
            Previous_Confidence_Variable()->Float(0.0f);
            Previous_Aggression_Variable()->Float(0.0f);

            Previous_No_Body_Cleanup_Faction_Variable()->Bool(false);
            Previous_Potential_Follower_Faction_Variable()->Bool(false);
            Previous_Crime_Faction_Variable()->None(faction_class_info);

            Name_Variable()->String("");

            Rating_Variable()->Int(0);
            Outfit2_Variable()->Int(0);
            Vitality_Variable()->Int(0);
            Style_Variable()->Int(0);

            Is_Reanimated_Variable()->Bool(false);
            Is_Display_Variable()->Bool(false);
            Is_Mannequin_Variable()->Bool(false);
            Is_Paralyzed_Variable()->Bool(false);
            Is_Thrall_Variable()->Bool(false);
            Is_Settler_Variable()->Bool(false);
            Is_Immobile_Variable()->Bool(false);
            Is_Clone_Variable()->Bool(false);

            Backup_Outfit2_Variable()->None(outfit2_class_info);
            Current_Outfit2_Variable()->None(outfit2_class_info);
            Default_Outfit2_Variable()->None(outfit2_class_info);
            Vanilla_Outfit2_Variable()->None(outfit2_class_info);
            Follower_Outfit2_Variable()->None(outfit2_class_info);
            Thrall_Outfit2_Variable()->None(outfit2_class_info);
            Settler_Outfit2_Variable()->None(outfit2_class_info);
            Immobile_Outfit2_Variable()->None(outfit2_class_info);
            Member_Outfit2_Variable()->None(outfit2_class_info);

            Default_Outfit_Variable()->None(outfit1_class_info);
            Vanilla_Outfit_Variable()->None(outfit1_class_info);

            Undisplay_Marker_Variable()->None(reference_class_info);
            Display_Marker_Variable()->None(reference_class_info);
            Mannequin_Marker_Variable()->None(reference_class_info);
            Pack_Variable()->None(reference_class_info);

            Actor_Variable()->None(actor_class_info);

            (*user_callback)->operator()();
            delete (*user_callback);
        }
    }

    void Member_t::Destroy_Containers()
    {
        Reference_t* pack = Pack();
        Object_Ref::Categorize(pack);
        Object_Ref::Delete_Safe(pack);
    }

    void Member_t::Destroy_Outfit2s()
    {
        Outfit2_t* default_outfit2 = static_cast<Outfit2_t*>(Default_Outfit2_Variable()->Reference());
        if (default_outfit2) {
            Outfit2_t::Destroy(default_outfit2);
        }
        Outfit2_t* vanilla_outfit2 = static_cast<Outfit2_t*>(Vanilla_Outfit2_Variable()->Reference());
        if (vanilla_outfit2) {
            Outfit2_t::Destroy(vanilla_outfit2);
        }
        Outfit2_t* follower_outfit2 = static_cast<Outfit2_t*>(Follower_Outfit2_Variable()->Reference());
        if (follower_outfit2) {
            Outfit2_t::Destroy(follower_outfit2);
        }
        Outfit2_t* thrall_outfit2 = static_cast<Outfit2_t*>(Thrall_Outfit2_Variable()->Reference());
        if (thrall_outfit2) {
            Outfit2_t::Destroy(thrall_outfit2);
        }
        Outfit2_t* settler_outfit2 = static_cast<Outfit2_t*>(Settler_Outfit2_Variable()->Reference());
        if (settler_outfit2) {
            Outfit2_t::Destroy(settler_outfit2);
        }
        Outfit2_t* immobile_outfit2 = static_cast<Outfit2_t*>(Immobile_Outfit2_Variable()->Reference());
        if (immobile_outfit2) {
            Outfit2_t::Destroy(immobile_outfit2);
        }
        Outfit2_t* member_outfit2 = static_cast<Outfit2_t*>(Member_Outfit2_Variable()->Reference());
        if (member_outfit2) {
            Outfit2_t::Destroy(member_outfit2);
        }
    }

    void Member_t::Backup_State(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Previous_Crime_Faction_Variable()->Pack(Actor2::Crime_Faction(actor));
        //Previous_Potential_Follower_Faction_Variable()->Bool(Actor2::Has_Faction(actor, Consts::Potential_Follower_Faction()));
        Previous_No_Body_Cleanup_Faction_Variable()->Bool(Actor2::Has_Faction(actor, Consts::WI_No_Body_Cleanup_Faction()));

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
        Previous_Aggression_Variable()->Float(value_owner->Get_Base_Actor_Value(Actor_Value_t::AGGRESSION));
        Previous_Confidence_Variable()->Float(value_owner->Get_Base_Actor_Value(Actor_Value_t::CONFIDENCE));
        Previous_Assistance_Variable()->Float(value_owner->Get_Base_Actor_Value(Actor_Value_t::ASSISTANCE));
        Previous_Morality_Variable()->Float(value_owner->Get_Base_Actor_Value(Actor_Value_t::MORALITY));
    }

    void Member_t::Restore_State(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Actor2::Add_Crime_Faction(actor, Previous_Crime_Faction_Variable()->Faction());
        /*if (Previous_Potential_Follower_Faction_Variable()->Bool()) {
            Actor2::Add_Faction(actor, Consts::Potential_Follower_Faction(), 0);
        } else {
            Actor2::Remove_Faction(actor, Consts::Potential_Follower_Faction());
        }*/
        if (Previous_No_Body_Cleanup_Faction_Variable()->Bool()) {
            Actor2::Add_Faction(actor, Consts::WI_No_Body_Cleanup_Faction(), 0);
        } else {
            Actor2::Remove_Faction(actor, Consts::WI_No_Body_Cleanup_Faction());
        }

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
        value_owner->Set_Actor_Value(Actor_Value_t::AGGRESSION, Previous_Aggression_Variable()->Float());
        value_owner->Set_Actor_Value(Actor_Value_t::CONFIDENCE, Previous_Confidence_Variable()->Float());
        value_owner->Set_Actor_Value(Actor_Value_t::ASSISTANCE, Previous_Assistance_Variable()->Float());
        value_owner->Set_Actor_Value(Actor_Value_t::MORALITY, Previous_Morality_Variable()->Float());
    }

    void Member_t::Enforce_Member(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());

        Object_Ref::Token(actor, Consts::Member_Token(), ID() + 1);
        if (Is_Clone_Unsafe()) {
            Object_Ref::Token(actor, Consts::Clone_Token());
        } else {
            Object_Ref::Untoken(actor, Consts::Clone_Token());
        }
        if (Is_Generic_Unsafe()) {
            Object_Ref::Token(actor, Consts::Generic_Token());
        } else {
            Object_Ref::Untoken(actor, Consts::Generic_Token());
        }

        //Actor2::Remove_Faction(actor, Consts::Potential_Follower_Faction());
        //Actor2::Remove_Faction(actor, Consts::Current_Follower_Faction());
        Actor2::Add_Faction(actor, Consts::WI_No_Body_Cleanup_Faction());
        Actor2::Add_Faction(actor, Consts::Member_Faction());
        Actor2::Remove_Crime_Faction(actor);

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
        value_owner->Set_Actor_Value(Actor_Value_t::AGGRESSION, 0.0f);
        value_owner->Set_Actor_Value(Actor_Value_t::CONFIDENCE, 4.0f);
        value_owner->Set_Actor_Value(Actor_Value_t::ASSISTANCE, 2.0f);
        value_owner->Set_Actor_Value(Actor_Value_t::MORALITY, 0.0f);

        // maybe we can check this, and if it's set, immobilize the member
        value_owner->Set_Actor_Value(Actor_Value_t::WAITING_FOR_PLAYER, 0.0f);

        Actor2::Join_Player_Team(actor, true);

        if (Actor2::Cant_Talk_To_Player(actor)) {
            Actor2::Talks_To_Player(actor, true);
        }

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Destroy_Member(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Enforce_Non_Member(actor);
    }

    void Member_t::Enforce_Non_Member(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        if (Actor2::Race_Cant_Talk_To_Player(actor)) {
            Actor2::Talks_To_Player(actor, false);
        }

        Actor2::Leave_Player_Team(actor);

        Object_Ref::Untoken(actor, Consts::Member_Token());
        Object_Ref::Untoken(actor, Consts::Clone_Token());
        Object_Ref::Untoken(actor, Consts::Generic_Token());

        Actor2::Evaluate_Package(actor);
    }

    Int_t Member_t::Mobilize()
    {
        if (Is_Filled()) {
            if (Is_Immobile()) {
                Actor_t* actor = Actor();

                Destroy_Immobile(actor);
                Enforce_Outfit2(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Destroy_Immobile(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Is_Immobile_Variable()->Bool(false);
        Enforce_Mobile(actor);
    }

    void Member_t::Enforce_Mobile(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Untoken(actor, Consts::Immobile_Token());
    }

    Int_t Member_t::Immobilize()
    {
        if (Is_Filled()) {
            if (Is_Mobile()) {
                Is_Immobile_Variable()->Bool(true);

                Actor_t* actor = Actor();
                Enforce_Immobile(actor);
                Enforce_Outfit2(actor);

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Immobile(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Token(actor, Consts::Immobile_Token());
    }

    Int_t Member_t::Settle()
    {
        if (Is_Filled()) {
            if (Isnt_Settler()) {
                Is_Settler_Variable()->Bool(true);

                Actor_t* actor = Actor();
                Object_Ref::Move_To_Orbit(Settler_Marker(), actor, 0.0f, 180.0f);
                Enforce_Settler(actor);
                Enforce_Outfit2(actor);

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Settler(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Token(actor, Consts::Settler_Token());
    }

    Int_t Member_t::Resettle()
    {
        if (Is_Filled()) {
            if (Is_Settler()) {
                Actor_t* actor = Actor();
                Object_Ref::Move_To_Orbit(Settler_Marker(), actor, 0.0f, 180.0f);
                Enforce_Settler(actor);
                Enforce_Outfit2(actor);

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::ISNT;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Unsettle()
    {
        if (Is_Filled()) {
            if (Is_Settler()) {
                Actor_t* actor = Actor();

                Destroy_Settler(actor);
                Enforce_Outfit2(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Destroy_Settler(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Is_Settler_Variable()->Bool(false);
        Object_Ref::Move_To_Orbit(Settler_Marker(), Consts::Storage_Marker(), 0.0f, 0.0f);
        Enforce_Non_Settler(actor);
    }

    void Member_t::Enforce_Non_Settler(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Untoken(actor, Consts::Settler_Token());
    }

    Int_t Member_t::Enthrall()
    {
        if (Is_Filled()) {
            if (Player_t::Self()->Is_Vampire()) {
                if (Isnt_Thrall()) {
                    Is_Thrall_Variable()->Bool(true);

                    Actor_t* actor = Actor();
                    Enforce_Thrall(actor);
                    Enforce_Outfit2(actor);

                    Actor2::Evaluate_Package(actor);

                    return CODES::SUCCESS;
                } else {
                    return CODES::IS;
                }
            } else {
                return CODES::VAMPIRE;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Thrall(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Token(actor, Consts::Thrall_Token());
        Actor2::Add_Faction(actor, Consts::DLC1_Vampire_Feed_No_Crime_Faction());
    }

    Int_t Member_t::Unthrall()
    {
        if (Is_Filled()) {
            if (Player_t::Self()->Is_Vampire()) {
                if (Is_Thrall()) {
                    Actor_t* actor = Actor();

                    Destroy_Thrall(actor);
                    Enforce_Outfit2(actor);
                    Actor2::Evaluate_Package(actor);

                    return CODES::SUCCESS;
                } else {
                    return CODES::IS;
                }
            } else {
                return CODES::VAMPIRE;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Destroy_Thrall(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Is_Thrall_Variable()->Bool(false);
        Enforce_Non_Thrall(actor);
    }

    void Member_t::Enforce_Non_Thrall(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Untoken(actor, Consts::Thrall_Token());
        Actor2::Remove_Faction(actor, Consts::DLC1_Vampire_Feed_No_Crime_Faction());
    }

    Int_t Member_t::Paralyze()
    {
        if (Is_Filled()) {
            if (Isnt_Paralyzed()) {
                Is_Paralyzed_Variable()->Bool(true);

                Actor_t* actor = Actor();
                Enforce_Paralyzed(actor);

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Paralyzed(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Token(actor, Consts::Paralyzed_Token());

        Object_Ref::Block_All_Activation(actor);
        Actor2::Disable_AI(actor);
        Actor2::Ghostify(actor);

        actor->Update_3D_Position();

        // Debug.SendAnimationEvent(p_ref_actor, "IdleForceDefaultState")
    }

    Int_t Member_t::Unparalyze()
    {
        if (Is_Filled()) {
            if (Is_Paralyzed()) {
                Actor_t* actor = Actor();

                Destroy_Paralyzed(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Destroy_Paralyzed(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Is_Paralyzed_Variable()->Bool(false);
        Enforce_Non_Paralyzed(actor);
    }

    void Member_t::Enforce_Non_Paralyzed(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Untoken(actor, Consts::Paralyzed_Token());

        if (Isnt_Mannequin_Unsafe()) {
            Object_Ref::Unblock_All_Activation(actor);
            Actor2::Enable_AI(actor);
            Actor2::Unghostify(actor);
        }
    }

    Int_t Member_t::Mannequinize(Reference_t* marker)
    {
        if (Is_Filled()) {
            if (Isnt_Mannequin()) {
                if (marker) { // later on, we can make loose mannequins by providing a default marker
                    Is_Mannequin_Variable()->Bool(true);
                    Mannequin_Marker_Variable()->Pack(marker);

                    Actor_t* actor = Actor();
                    Enforce_Mannequin(actor, marker);
                    Actor2::Fully_Update_3D_Model(actor);
                    actor->Resurrect(false, true);

                    Follower_t* follower = Follower();
                    if (follower) {
                        Unfollow();
                    }

                    Movee_t* movee = Movee_t::Self();
                    if (movee->Actor() == actor) {
                        movee->Stop();
                    }

                    Actor2::Evaluate_Package(actor);

                    return CODES::SUCCESS;
                } else {
                    return CODES::MARKER;
                }
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Mannequin(Actor_t* actor, Reference_t* marker)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(marker); 

        Object_Ref::Token(actor, Consts::Mannequin_Token());

        Object_Ref::Block_All_Activation(actor);
        Actor2::Disable_AI(actor);
        Actor2::Ghostify(actor);

        if (Isnt_Display()) {
            Actor2::Move_To_Orbit(actor, marker, 0.0f, 180.0f);

            actor->pos.x = marker->pos.x;
            actor->pos.y = marker->pos.y;
            actor->pos.z = marker->pos.z;
            actor->rot.z = marker->rot.z;
            actor->Update_Actor_3D_Position();
        }
    }

    Int_t Member_t::Unmannequinize()
    {
        if (Is_Filled()) {
            if (Is_Mannequin()) {
                Actor_t* actor = Actor();

                Destroy_Mannequin(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Destroy_Mannequin(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Is_Mannequin_Variable()->Bool(false);
        Mannequin_Marker_Variable()->None(Object_Ref::Class_Info());
        Enforce_Non_Mannequin(actor);
    }

    void Member_t::Enforce_Non_Mannequin(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        
        Object_Ref::Untoken(actor, Consts::Mannequin_Token());

        if (Isnt_Paralyzed_Unsafe()) {
            Object_Ref::Unblock_All_Activation(actor);
            Actor2::Enable_AI(actor);
            Actor2::Unghostify(actor);
        }
    }

    Int_t Member_t::Display(Reference_t* origin, Float_t radius, Float_t degree)
    {
        if (Is_Filled()) {
            if (Isnt_Display()) {
                Actor_t* actor = Actor();
                Create_Display(actor, origin, radius, degree);
                Actor2::Evaluate_Package(actor);
                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Create_Display(Actor_t* actor, Reference_t* origin, Float_t radius, Float_t degree)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(origin);

        Is_Display_Variable()->Bool(true);

        Reference_t* display_marker = Object_Ref::Create_Marker_At(actor);
        NPCP_ASSERT(display_marker);
        Display_Marker_Variable()->Pack(display_marker);
        Object_Ref::Move_To_Orbit(display_marker, origin, radius, degree);

        Reference_t* undisplay_marker = Object_Ref::Create_Marker_At(actor);
        NPCP_ASSERT(undisplay_marker);
        Undisplay_Marker_Variable()->Pack(undisplay_marker);

        Enforce_Display(actor, display_marker);
    }

    void Member_t::Enforce_Display(Actor_t* actor, Reference_t* display_marker)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(display_marker);

        Object_Ref::Token(actor, Consts::Display_Token());
        Actor2::Disable_Havok_Collision(actor);

        if (!Actor2::Is_AI_Enabled(actor) && actor->parentCell == display_marker->parentCell) {
            Object_Ref::Move_To_Orbit(actor, display_marker, 0.0f, 180.0f);
            Do_Skip_On_Load_Variable()->Bool(true);
            Actor2::Fully_Update_3D_Model(actor);
        } else {
            Object_Ref::Move_To_Orbit(actor, display_marker, 0.0f, 180.0f);
            Actor2::Update_3D_Model(actor);
        }
    }

    Int_t Member_t::Undisplay()
    {
        if (Is_Filled()) {
            if (Is_Display()) {
                Actor_t* actor = Actor();
                Destroy_Display(actor);
                Actor2::Evaluate_Package(actor);
                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Destroy_Display(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Is_Display_Variable()->Bool(false);

        Variable_t* display_marker_variable = Display_Marker_Variable();
        Reference_t* display_marker = display_marker_variable->Reference();

        Variable_t* undisplay_marker_variable = Undisplay_Marker_Variable();
        Reference_t* undisplay_marker = undisplay_marker_variable->Reference();

        if (undisplay_marker) {
            if (!Actor2::Is_AI_Enabled(actor) && actor->parentCell == undisplay_marker->parentCell) {
                Object_Ref::Move_To_Orbit(actor, undisplay_marker, 0.0f, 180.0f);
                Actor2::Fully_Update_3D_Model(actor);
            } else {
                Object_Ref::Move_To_Orbit(actor, undisplay_marker, 0.0f, 180.0f);
                Actor2::Update_3D_Model(actor);
            }
        }

        undisplay_marker_variable->None(Object_Ref::Class_Info());
        Object_Ref::Delete_Safe(undisplay_marker);

        display_marker_variable->None(Object_Ref::Class_Info());
        Object_Ref::Delete_Safe(display_marker);

        Enforce_Non_Display(actor);
    }

    void Member_t::Enforce_Non_Display(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Untoken(actor, Consts::Display_Token());
        Actor2::Enable_Havok_Collision(actor);
    }

    Int_t Member_t::Reanimate()
    {
        if (Is_Filled()) {
            if (Isnt_Reanimated()) {
                Is_Reanimated_Variable()->Bool(true);

                Actor_t* actor = Actor();
                if (Is_Dead()) {
                    Resurrect();
                }
                Enforce_Reanimated(actor);

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Reanimated(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        if (Is_Alive()) {
            Object_Ref::Token(actor, Consts::Reanimated_Token());
            if (!Actor2::Has_Magic_Effect(actor, Consts::Reanimate_Magic_Effect())) {
                Actor2::Add_Spell(actor, Consts::Reanimate_Ability_Spell());
            }
        } else {
            Deanimate();
        }
    }

    Int_t Member_t::Deanimate()
    {
        if (Is_Filled()) {
            if (Is_Reanimated()) {
                Actor_t* actor = Actor();
                Destroy_Reanimated(actor);
                Actor2::Evaluate_Package(actor);
                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Destroy_Reanimated(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Is_Reanimated_Variable()->Bool(false);
        if (Is_Alive()) {
            Kill();
        }
        Enforce_Non_Reanimated(actor);
    }

    void Member_t::Enforce_Non_Reanimated(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Object_Ref::Untoken(actor, Consts::Reanimated_Token());
        Actor2::Remove_Spell(actor, Consts::Reanimate_Ability_Spell());
    }

    Int_t Member_t::Stylize(Int_t style)
    {
        if (Is_Filled()) {
            if (style == CODES::STYLE::DEFAULT) {
                return Stylize_Default();
            } else if (style == CODES::STYLE::WARRIOR) {
                return Stylize_Warrior();
            } else if (style == CODES::STYLE::MAGE) {
                return Stylize_Mage();
            } else if (style == CODES::STYLE::ARCHER) {
                return Stylize_Archer();
            } else if (style == CODES::STYLE::COWARD) {
                return Stylize_Coward();
            } else {
                return CODES::ISNT;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Stylize_Default()
    {
        if (Is_Filled()) {
            Variable_t* style_variable = Style_Variable();
            if (style_variable->Int() == CODES::STYLE::DEFAULT) {
                return CODES::IS;
            } else {
                style_variable->Int(CODES::STYLE::DEFAULT);

                Actor_t* actor = Actor();
                Enforce_Default_Style(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Stylize_Warrior()
    {
        if (Is_Filled()) {
            Variable_t* style_variable = Style_Variable();
            if (style_variable->Int() == CODES::STYLE::WARRIOR) {
                return CODES::IS;
            } else {
                style_variable->Int(CODES::STYLE::WARRIOR);

                Actor_t* actor = Actor();
                Enforce_Warrior_Style(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Stylize_Mage()
    {
        if (Is_Filled()) {
            Variable_t* style_variable = Style_Variable();
            if (style_variable->Int() == CODES::STYLE::MAGE) {
                return CODES::IS;
            } else {
                style_variable->Int(CODES::STYLE::MAGE);

                Actor_t* actor = Actor();
                Enforce_Mage_Style(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Stylize_Archer()
    {
        if (Is_Filled()) {
            Variable_t* style_variable = Style_Variable();
            if (style_variable->Int() == CODES::STYLE::ARCHER) {
                return CODES::IS;
            } else {
                style_variable->Int(CODES::STYLE::ARCHER);

                Actor_t* actor = Actor();
                Enforce_Archer_Style(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Stylize_Coward()
    {
        if (Is_Filled()) {
            Variable_t* style_variable = Style_Variable();
            if (style_variable->Int() == CODES::STYLE::COWARD) {
                return CODES::IS;
            } else {
                style_variable->Int(CODES::STYLE::COWARD);

                Actor_t* actor = Actor();
                Enforce_Coward_Style(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Style(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Int_t style = Style_Variable()->Int();
        if (style == CODES::STYLE::DEFAULT) {
            return Enforce_Default_Style(actor);
        } else if (style == CODES::STYLE::WARRIOR) {
            return Enforce_Warrior_Style(actor);
        } else if (style == CODES::STYLE::MAGE) {
            return Enforce_Mage_Style(actor);
        } else if (style == CODES::STYLE::ARCHER) {
            return Enforce_Archer_Style(actor);
        } else if (style == CODES::STYLE::COWARD) {
            return Enforce_Coward_Style(actor);
        } else {
            NPCP_ASSERT(false);
        }
    }

    void Member_t::Enforce_Default_Style(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Style_Variable()->Int() == CODES::STYLE::DEFAULT);

        Object_Ref::Token(actor, Consts::Default_Style_Token());
        Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
        Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
        Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
        Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
    }

    void Member_t::Enforce_Warrior_Style(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Style_Variable()->Int() == CODES::STYLE::WARRIOR);

        Object_Ref::Untoken(actor, Consts::Default_Style_Token());
        Object_Ref::Token(actor, Consts::Warrior_Style_Token());
        Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
        Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
        Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
    }

    void Member_t::Enforce_Mage_Style(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Style_Variable()->Int() == CODES::STYLE::MAGE);

        Object_Ref::Untoken(actor, Consts::Default_Style_Token());
        Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
        Object_Ref::Token(actor, Consts::Mage_Style_Token());
        Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
        Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
    }

    void Member_t::Enforce_Archer_Style(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Style_Variable()->Int() == CODES::STYLE::ARCHER);

        Object_Ref::Untoken(actor, Consts::Default_Style_Token());
        Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
        Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
        Object_Ref::Token(actor, Consts::Archer_Style_Token());
        Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
    }

    void Member_t::Enforce_Coward_Style(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Style_Variable()->Int() == CODES::STYLE::COWARD);

        Object_Ref::Untoken(actor, Consts::Default_Style_Token());
        Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
        Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
        Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
        Object_Ref::Token(actor, Consts::Coward_Style_Token());
    }

    Int_t Member_t::Unstylize()
    {
        if (Is_Filled()) {
            Style_Variable()->Int(0);

            Actor_t* actor = Actor();
            Object_Ref::Untoken(actor, Consts::Default_Style_Token());
            Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
            Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
            Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
            Object_Ref::Untoken(actor, Consts::Coward_Style_Token());

            Actor2::Evaluate_Package(actor);

            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Vitalize(Int_t vitality)
    {
        if (Is_Filled()) {
            if (vitality == CODES::VITALITY::MORTAL) {
                return Vitalize_Mortal();
            } else if (vitality == CODES::VITALITY::PROTECTED) {
                return Vitalize_Protected();
            } else if (vitality == CODES::VITALITY::ESSENTIAL) {
                return Vitalize_Essential();
            } else if (vitality == CODES::VITALITY::INVULNERABLE) {
                return Vitalize_Invulnerable();
            } else {
                return CODES::ISNT;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Vitalize_Mortal()
    {
        if (Is_Filled()) {
            Variable_t* vitality_variable = Vitality_Variable();
            if (vitality_variable->Int() == CODES::VITALITY::MORTAL) {
                return CODES::IS;
            } else {
                vitality_variable->Int(CODES::VITALITY::MORTAL);

                Actor_t* actor = Actor();
                Enforce_Mortal_Vitality(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Vitalize_Protected()
    {
        if (Is_Filled()) {
            Variable_t* vitality_variable = Vitality_Variable();
            if (vitality_variable->Int() == CODES::VITALITY::PROTECTED) {
                return CODES::IS;
            } else {
                vitality_variable->Int(CODES::VITALITY::PROTECTED);

                Actor_t* actor = Actor();
                Enforce_Protected_Vitality(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Vitalize_Essential()
    {
        if (Is_Filled()) {
            Variable_t* vitality_variable = Vitality_Variable();
            if (vitality_variable->Int() == CODES::VITALITY::ESSENTIAL) {
                return CODES::IS;
            } else {
                vitality_variable->Int(CODES::VITALITY::ESSENTIAL);

                Actor_t* actor = Actor();
                Enforce_Essential_Vitality(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Vitalize_Invulnerable()
    {
        if (Is_Filled()) {
            Variable_t* vitality_variable = Vitality_Variable();
            if (vitality_variable->Int() == CODES::VITALITY::INVULNERABLE) {
                return CODES::IS;
            } else {
                vitality_variable->Int(CODES::VITALITY::INVULNERABLE);

                Actor_t* actor = Actor();
                Enforce_Invulnerable_Vitality(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Vitality(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Int_t vitality = Vitality_Variable()->Int();
        if (vitality == CODES::VITALITY::MORTAL) {
            return Enforce_Mortal_Vitality(actor);
        } else if (vitality == CODES::VITALITY::PROTECTED) {
            return Enforce_Protected_Vitality(actor);
        } else if (vitality == CODES::VITALITY::ESSENTIAL) {
            return Enforce_Essential_Vitality(actor);
        } else if (vitality == CODES::VITALITY::INVULNERABLE) {
            return Enforce_Invulnerable_Vitality(actor);
        } else {
            NPCP_ASSERT(false);
        }
    }

    void Member_t::Enforce_Mortal_Vitality(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Vitality_Variable()->Int() == CODES::VITALITY::MORTAL);

        Object_Ref::Token(actor, Consts::Mortal_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

        flags &= ~IS_PROTECTED;
        flags &= ~IS_ESSENTIAL;
    }

    void Member_t::Enforce_Protected_Vitality(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Vitality_Variable()->Int() == CODES::VITALITY::PROTECTED);

        Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
        Object_Ref::Token(actor, Consts::Protected_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

        flags |= IS_PROTECTED;
        flags &= ~IS_ESSENTIAL;
    }

    void Member_t::Enforce_Essential_Vitality(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Vitality_Variable()->Int() == CODES::VITALITY::ESSENTIAL);

        Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
        Object_Ref::Token(actor, Consts::Essential_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

        flags &= ~IS_PROTECTED;
        flags |= IS_ESSENTIAL;
    }

    void Member_t::Enforce_Invulnerable_Vitality(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(Vitality_Variable()->Int() == CODES::VITALITY::INVULNERABLE);

        Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
        Object_Ref::Token(actor, Consts::Invulnerable_Vitality_Token());

        flags &= ~IS_PROTECTED;
        flags |= IS_ESSENTIAL;
    }

    Int_t Member_t::Unvitalize()
    {
        if (Is_Filled()) {
            Vitality_Variable()->Int(0);

            Actor_t* actor = Actor();
            Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

            flags &= ~IS_PROTECTED;
            flags |= IS_ESSENTIAL;

            Actor2::Evaluate_Package(actor);

            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Change_Outfit1(Outfit_t* outfit)
    {
        NPCP_ASSERT(Is_Filled());

        if (!outfit) {
            outfit = Consts::Empty_Outfit();
        }

        Actor_t* actor = Actor();
        Outfit_t* old_outfit = Actor2::Base_Outfit(actor);
        Actor2::Set_Outfit_Basic(actor, outfit, false, false);

        Vanilla_Outfit_Variable()->Pack(outfit);
        Update_Outfit2(CODES::OUTFIT2::VANILLA, false);
        Vanilla_Outfit2()->Cache_Dynamic_Outfit1(actor);

        Actor2::Set_Outfit_Basic(actor, old_outfit, false, false);

        Enforce_Outfit2(actor);
    }

    Int_t Member_t::Change_Outfit2(Int_t outfit2_code)
    {
        if (Is_Filled()) {
            if (outfit2_code == CODES::OUTFIT2::CURRENT) {
                outfit2_code = Outfit2();
            }

            if (outfit2_code == CODES::OUTFIT2::MEMBER) {
                return Change_Member_Outfit2();
            } else if (outfit2_code == CODES::OUTFIT2::IMMOBILE) {
                return Change_Immobile_Outfit2();
            } else if (outfit2_code == CODES::OUTFIT2::SETTLER) {
                return Change_Settler_Outfit2();
            } else if (outfit2_code == CODES::OUTFIT2::THRALL) {
                return Change_Thrall_Outfit2();
            } else if (outfit2_code == CODES::OUTFIT2::FOLLOWER) {
                return Change_Follower_Outfit2();
            } else if (outfit2_code == CODES::OUTFIT2::VANILLA) {
                return Change_Vanilla_Outfit2();
            } else if (outfit2_code == CODES::OUTFIT2::DEFAULT) {
                return Change_Default_Outfit2();
            } else {
                return Change_Member_Outfit2();
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Member_Outfit2()
    {
        if (Is_Filled()) {
            Update_Outfit2(CODES::OUTFIT2::MEMBER);
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Immobile_Outfit2()
    {
        if (Is_Filled()) {
            Update_Outfit2(CODES::OUTFIT2::IMMOBILE);
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Settler_Outfit2()
    {
        if (Is_Filled()) {
            Update_Outfit2(CODES::OUTFIT2::SETTLER);
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Thrall_Outfit2()
    {
        if (Is_Filled()) {
            Update_Outfit2(CODES::OUTFIT2::THRALL);
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Follower_Outfit2()
    {
        if (Is_Filled()) {
            Update_Outfit2(CODES::OUTFIT2::FOLLOWER);
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Vanilla_Outfit2()
    {
        if (Is_Filled()) {
            if (Outfit2() != CODES::OUTFIT2::VANILLA) {
                Update_Outfit2(CODES::OUTFIT2::VANILLA, true);
            } else {
                Update_Outfit2(CODES::OUTFIT2::VANILLA, false);
            }
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Default_Outfit2()
    {
        if (Is_Filled()) {
            if (Outfit2() != CODES::OUTFIT2::DEFAULT) {
                Update_Outfit2(CODES::OUTFIT2::DEFAULT, true);
            } else {
                Update_Outfit2(CODES::OUTFIT2::DEFAULT, false);
            }
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Change_Current_Outfit2()
    {
        if (Is_Filled()) {
            Update_Outfit2(Outfit2());
            Open_Outfit2();
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Update_Outfit2(Int_t outfit2_code, Bool_t do_cache_outfit1)
    {
        NPCP_ASSERT(Is_Filled());

        Outfit2_t* current_outfit2 = nullptr;
        Outfit2_t* backup_outfit2 = nullptr;
        if (outfit2_code == CODES::OUTFIT2::MEMBER) {
            current_outfit2 = Member_Outfit2();
            backup_outfit2 = current_outfit2;
        } else if (outfit2_code == CODES::OUTFIT2::IMMOBILE) {
            current_outfit2 = Immobile_Outfit2();
        } else if (outfit2_code == CODES::OUTFIT2::SETTLER) {
            current_outfit2 = Settler_Outfit2();
        } else if (outfit2_code == CODES::OUTFIT2::THRALL) {
            current_outfit2 = Thrall_Outfit2();
        } else if (outfit2_code == CODES::OUTFIT2::FOLLOWER) {
            current_outfit2 = Follower_Outfit2();
        } else if (outfit2_code == CODES::OUTFIT2::VANILLA) {
            current_outfit2 = Vanilla_Outfit2();
            backup_outfit2 = current_outfit2;
            if (do_cache_outfit1) {
                current_outfit2->Cache_Static_Outfit1(Vanilla_Outfit());
            }
        } else if (outfit2_code == CODES::OUTFIT2::DEFAULT) {
            current_outfit2 = Default_Outfit2();
            backup_outfit2 = current_outfit2;
            if (do_cache_outfit1) {
                current_outfit2->Cache_Static_Outfit1(NPCS_t::Self()->Default_Outfit(Actor()));
            }
        } else {
            current_outfit2 = Current_Outfit2();
            outfit2_code = Outfit2();
        }

        NPCP_ASSERT(current_outfit2);
        Current_Outfit2_Variable()->Pack(current_outfit2);
        Outfit2_Variable()->Int(outfit2_code);

        if (backup_outfit2) {
            Backup_Outfit2_Variable()->Pack(backup_outfit2);
        }
    }

    void Member_t::Open_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Outfit2_t* current_outfit2 = Current_Outfit2();
        Int_t current_outfit2_code = Outfit2();
        std::string outfit2_name = Name().c_str();

        struct Callback : public Virtual_Callback_t {
            Member_t* member;
            Callback(Member_t* member) :
                member(member)
            {
            }
            virtual void operator()(Variable_t* result)
            {
                Actor_t* actor = member->Actor();
                member->Enforce_Outfit2(actor);
                Actor2::Evaluate_Package(actor);
            }
        };
        Virtual_Callback_i* callback = new Callback(this);

        if (current_outfit2_code == CODES::OUTFIT2::MEMBER) {
            current_outfit2->Open((outfit2_name + "'s Member Outfit").c_str(), &callback);
        } else if (current_outfit2_code == CODES::OUTFIT2::IMMOBILE) {
            current_outfit2->Open((outfit2_name + "'s Immobile Outfit").c_str(), &callback);
        } else if (current_outfit2_code == CODES::OUTFIT2::SETTLER) {
            current_outfit2->Open((outfit2_name + "'s Settler Outfit").c_str(), &callback);
        } else if (current_outfit2_code == CODES::OUTFIT2::THRALL) {
            current_outfit2->Open((outfit2_name + "'s Thrall Outfit").c_str(), &callback);
        } else if (current_outfit2_code == CODES::OUTFIT2::FOLLOWER) {
            current_outfit2->Open((outfit2_name + "'s Follower Outfit").c_str(), &callback);
        } else if (current_outfit2_code == CODES::OUTFIT2::VANILLA) {
            current_outfit2->Open((outfit2_name + "'s Vanilla Outfit").c_str(), &callback);
        } else if (current_outfit2_code == CODES::OUTFIT2::DEFAULT) {
            current_outfit2->Open((outfit2_name + "'s Default Outfit").c_str(), &callback);
        } else {
            NPCP_ASSERT(false);
        }
    }

    void Member_t::Enforce_Outfit2(Actor_t* actor, Callback_t<Actor_t*>* user_callback)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Outfit2_t* current_outfit2;
        Int_t current_outfit2_code;
        if (Vars::Do_Auto_Outfit2s()) {
            if (Is_Immobile() && Vars::Do_Auto_Immobile_Outfit2()) {
                current_outfit2 = Immobile_Outfit2();
                current_outfit2_code = CODES::OUTFIT2::IMMOBILE;
            } else if (Is_Follower()) {
                current_outfit2 = Follower_Outfit2();
                current_outfit2_code = CODES::OUTFIT2::FOLLOWER;
            } else if (Is_Thrall()) {
                current_outfit2 = Thrall_Outfit2();
                current_outfit2_code = CODES::OUTFIT2::THRALL;
            } else if (Is_Settler()) {
                current_outfit2 = Settler_Outfit2();
                current_outfit2_code = CODES::OUTFIT2::SETTLER;
            } else {
                Outfit2_t* backup_outfit2 = Backup_Outfit2();
                Outfit2_t* vanilla_outfit2 = Vanilla_Outfit2();
                Outfit2_t* default_outfit2 = Default_Outfit2();
                if (backup_outfit2 == vanilla_outfit2) {
                    current_outfit2 = Vanilla_Outfit2();
                    current_outfit2_code = CODES::OUTFIT2::VANILLA;
                } else if (backup_outfit2 == default_outfit2) {
                    current_outfit2 = Default_Outfit2();
                    current_outfit2_code = CODES::OUTFIT2::DEFAULT;
                } else {
                    current_outfit2 = Member_Outfit2();
                    current_outfit2_code = CODES::OUTFIT2::MEMBER;
                }
            }
            Current_Outfit2_Variable()->Pack(current_outfit2);
            Outfit2_Variable()->Int(current_outfit2_code);
        } else {
            current_outfit2 = Current_Outfit2();
            current_outfit2_code = Outfit2();
        }
        NPCP_ASSERT(current_outfit2);

        // maybe we can do this upfront on a update now
        if (current_outfit2_code == CODES::OUTFIT2::VANILLA && current_outfit2->Hasnt_Outfit1_Cache()) {
            current_outfit2->Cache_Static_Outfit1(Vanilla_Outfit());
        } else if (current_outfit2_code == CODES::OUTFIT2::DEFAULT && current_outfit2->Hasnt_Outfit1_Cache()) {
            current_outfit2->Cache_Static_Outfit1(NPCS_t::Self()->Default_Outfit(actor));
        }

        if (Actor2::Is_Alive(actor)) {
            Outfit_t* default_outfit1 = NPCS_t::Self()->Default_Outfit(actor);
            if (Default_Outfit() != default_outfit1) {
                Default_Outfit_Variable()->Pack(default_outfit1);
                Actor2::Set_Outfit_Basic(actor, default_outfit1, false, false);
                current_outfit2->Apply_To(actor, Pack(), user_callback);
            } else if (Actor2::Base_Outfit(actor) != default_outfit1 || !Object_Ref::Is_Worn(actor, Consts::Blank_Armor())) {
                Actor2::Set_Outfit_Basic(actor, default_outfit1, false, false);
                current_outfit2->Apply_To(actor, Pack(), user_callback);
            } else {
                current_outfit2->Apply_To(actor, Pack(), user_callback);
            }
        }
    }

    Int_t Member_t::Rate(Int_t rating)
    {
        if (Is_Filled()) {
            if (rating > -1 && rating < 6) {
                Rating_Variable()->Int(rating);
                return CODES::SUCCESS;
            } else {
                return CODES::ISNT;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Rename(String_t new_name)
    {
        if (Is_Filled()) {
            Name_Variable()->String(new_name);

            Actor_t* actor = Actor();
            Enforce_Name(actor, new_name);
            Actor2::Evaluate_Package(actor);

            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Name(Actor_t* actor, String_t name)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(name);

        Object_Ref::Rename(actor, name);
    }

    void Member_t::Enforce()
    {
        if (Is_Ready() && Is_Alive()) {
            Actor_t* actor = Actor();

            Enforce_Member(actor); // Backup should be Member, and Restore Unmember. pass actor as well

            if (Is_Mobile()) {
                Enforce_Mobile(actor);
            } else {
                Enforce_Immobile(actor);
            }

            if (Is_Settler()) {
                Enforce_Settler(actor);
            } else {
                Enforce_Non_Settler(actor);
            }

            if (Is_Thrall()) {
                Enforce_Thrall(actor);
            } else {
                Enforce_Non_Thrall(actor);
            }

            if (Is_Paralyzed()) {
                Enforce_Paralyzed(actor);
            } else {
                Enforce_Non_Paralyzed(actor);
            }

            if (Is_Mannequin()) {
                Enforce_Mannequin(actor, Mannequin_Marker());
            } else {
                Enforce_Non_Mannequin(actor);
            }

            if (Is_Display()) {
                Enforce_Display(actor, Display_Marker());
            } else {
                Enforce_Non_Display(actor);
            }

            if (Is_Reanimated()) {
                Enforce_Reanimated(actor);
            } else {
                Enforce_Non_Reanimated(actor);
            }

            Enforce_Style(actor);

            Enforce_Vitality(actor);

            Enforce_Outfit2(actor);

            Enforce_Name(actor, Name_Variable()->String());

            Follower_t* follower = Follower();
            if (follower) {
                follower->Enforce();
            }

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Summon(Reference_t* origin, Float_t radius, Float_t degree)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(origin);

        Actor2::Move_To_Orbit(Actor(), origin, radius, degree);
    }

    Int_t Member_t::Summon(Float_t radius, Float_t degree)
    {
        if (Is_Filled()) {
            if (Isnt_Mannequin()) {
                Summon(Player_t::Self()->Actor(), radius, degree);
                return CODES::SUCCESS;
            } else {
                return CODES::MANNEQUIN;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Summon_Ahead(Float_t radius)
    {
        return Summon(radius, 0.0f);
    }

    Int_t Member_t::Summon_Behind(Float_t radius)
    {
        return Summon(radius, 180.0f);
    }

    Int_t Member_t::Goto(Int_t radius, Int_t degree)
    {
        if (Is_Filled()) {
            Mannequins_t::Self()->Update_Go_Back_Marker(this);
            Object_Ref::Move_To_Orbit(Player_t::Self()->Actor(), Actor(), radius, degree);
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Open_Pack()
    {
        if (Is_Filled()) {
            Reference_t* pack = Pack();
            std::string name = Name().c_str();
            Object_Ref::Rename(pack, (name + "'s Pack").c_str());
            Object_Ref::Open_Container(pack);
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Stash()
    {
        if (Is_Filled()) {
            Object_Ref::Categorize(Pack());
            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Resurrect()
    {
        if (Is_Filled()) {
            if (Is_Dead()) {
                Actor2::Resurrect(Actor(), false);
                Enforce();
                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    Int_t Member_t::Kill()
    {
        if (Is_Filled()) {
            if (Is_Alive()) {
                Actor_t* actor = Actor();
                UInt32 backup_flags = flags;

                flags &= ~IS_PROTECTED;
                flags &= ~IS_ESSENTIAL;

                Actor2::Kill(actor, nullptr, 0.0f, true, true); // send event doesn't work?

                flags = backup_flags;

                Enforce_Kill(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Enforce_Kill(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        if (Is_Reanimated()) {
            Deanimate();
        }
    }

    Int_t Member_t::Unfollow()
    {
        if (Is_Filled()) {
            if (Is_Follower()) {
                struct Callback : public Callback_t<Int_t, Member_t*> {
                    void operator()(Int_t code, Member_t* member) { }
                };
                Callback_t<Int_t, Member_t*>* callback = new Callback();
                Followers_t::Self()->Remove_Follower(this, &callback);
                return CODES::SUCCESS;
            } else {
                return CODES::FOLLOWER;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Level()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        if (follower) {
            follower->Level();
        }
    }

    void Member_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define BMETHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...) \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Alias_t,               \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Member_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("Actor", 0, Actor_t*, Actor);
        METHOD("Follower", 0, Follower_t*, Follower);
        METHOD("Style", 0, Int_t, Style);
        METHOD("Vitality", 0, Int_t, Vitality);
        METHOD("Rating", 0, Int_t, Rating);
        METHOD("Name", 0, String_t, Name);
        METHOD("Rating_Stars", 0, String_t, Rating_Stars);

        BMETHOD("Is_Filled", 0, Bool_t, Is_Filled);
        METHOD("Is_Mannequin", 0, Bool_t, Is_Mannequin);
        METHOD("Isnt_Mannequin", 0, Bool_t, Isnt_Mannequin);
        METHOD("Is_Follower", 0, Bool_t, Is_Follower);

        METHOD("Mannequinize", 1, Int_t, Mannequinize, Reference_t*);
        METHOD("Unmannequinize", 0, Int_t, Unmannequinize);

        METHOD("Rate", 1, Int_t, Rate, Int_t);

        METHOD("Rename", 1, Int_t, Rename, String_t);

        METHOD("Stash", 0, Int_t, Stash);

        METHOD("OnLoad", 0, void, On_Load);
        METHOD("OnDeath", 1, void, On_Death, Actor_t*);
        METHOD("OnActivate", 1, void, On_Activate, Reference_t*);
        METHOD("OnCombatStateChanged", 2, void, On_Combat_State_Changed, Actor_t*, Int_t);
        METHOD("OnHit", 7, void, On_Hit, Reference_t*, Form_t*, Projectile_Base_t*, Bool_t, Bool_t, Bool_t, Bool_t);
        METHOD("OnPackageChange", 1, void, On_Package_Change, Package_t*);

        #undef BMETHOD
        #undef METHOD
    }

}}}
