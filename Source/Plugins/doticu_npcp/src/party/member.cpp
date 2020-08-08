/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "actor_base2.h"
#include "codes.h"
#include "consts.h"
#include "form.h"
#include "object_ref.h"
#include "party.h"
#include "party.inl"
#include "player.h"
#include "quest.h"
#include "spell.h"
#include "utils.h"
#include "vars.h"

namespace doticu_npcp { namespace Party {

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

    Variable_t* Member_t::Member_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_member"); }
    Variable_t* Member_t::Immobile_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_immobile"); }
    Variable_t* Member_t::Settler_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_settler"); }
    Variable_t* Member_t::Thrall_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_thrall"); }
    Variable_t* Member_t::Follower_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_follower"); }
    Variable_t* Member_t::Vanilla_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_vanilla"); }
    Variable_t* Member_t::Default_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_default"); }
    Variable_t* Member_t::Current_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_current"); }
    Variable_t* Member_t::Backup_Outfit2_Variable() { DEFINE_VARIABLE("p_outfit2_auto_backup"); }

    Variable_t* Member_t::Is_Clone_Variable() { DEFINE_VARIABLE("p_is_clone"); }
    Variable_t* Member_t::Is_Immobile_Variable() { DEFINE_VARIABLE("p_is_immobile"); }
    Variable_t* Member_t::Is_Settler_Variable() { DEFINE_VARIABLE("p_is_settler"); }
    Variable_t* Member_t::Is_Thrall_Variable() { DEFINE_VARIABLE("p_is_thrall"); }
    Variable_t* Member_t::Is_Paralyzed_Variable() { DEFINE_VARIABLE("p_is_paralyzed"); }
    Variable_t* Member_t::Is_Mannequin_Variable() { DEFINE_VARIABLE("p_is_mannequin"); }
    Variable_t* Member_t::Is_Display_Variable() { DEFINE_VARIABLE("p_is_display"); }
    Variable_t* Member_t::Is_Reanimated_Variable() { DEFINE_VARIABLE("p_is_reanimated"); }

    Variable_t* Member_t::Style_Variable() { DEFINE_VARIABLE("p_code_style"); }
    Variable_t* Member_t::Vitality_Variable() { DEFINE_VARIABLE("p_code_vitality"); }
    Variable_t* Member_t::Outfit2_Variable() { DEFINE_VARIABLE("p_code_outfit2"); }
    Variable_t* Member_t::Rating_Variable() { DEFINE_VARIABLE("p_int_rating"); }

    Variable_t* Member_t::Previous_Factions_Variable() { DEFINE_VARIABLE("p_prev_factions"); }
    Variable_t* Member_t::Previous_Faction_Ranks_Variable() { DEFINE_VARIABLE("p_prev_faction_ranks"); }
    Variable_t* Member_t::Previous_Crime_Faction_Variable() { DEFINE_VARIABLE("p_prev_faction_crime"); }
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
        return Actor2::Get_Name(Actor());
    }

    Outfit_t* Member_t::Vanilla_Outfit()
    {
        NPCP_ASSERT(Is_Filled());
        return Vanilla_Outfit_Variable()->Outfit();
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
            //variable->Pack(outfit2, Outfit2_t::Class_Info());
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
            //variable->Pack(outfit2, Outfit2_t::Class_Info());
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
            //variable->Pack(outfit2, Outfit2_t::Class_Info());
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
            //variable->Pack(outfit2, Outfit2_t::Class_Info());
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
            //variable->Pack(outfit2, Outfit2_t::Class_Info());
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
            //variable->Pack(outfit2, Outfit2_t::Class_Info());
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
            outfit2 = Outfit2_t::Create_Default();
            //variable->Pack(outfit2, Outfit2_t::Class_Info());
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

    void Member_t::On_Hit(Reference_t* attacker,
                          Form_t* tool,
                          Projectile_Base_t* projectile,
                          Bool_t is_power,
                          Bool_t is_sneak,
                          Bool_t is_bash,
                          Bool_t is_blocked)
    {
        static const String_t kill_func = String_t("p_Kill");
        NPCP_ASSERT(kill_func);

        if (Is_Filled() && Is_Alive_Unsafe()) {
            Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(Actor());
            if (value_owner->Get_Actor_Value(Actor_Value_t::HEALTH) <= 0.0) {
                Int_t vitality = Vitality();
                if (vitality == CODES::VITALITY::MORTAL ||
                    vitality == CODES::VITALITY::PROTECTED && attacker == Player::Actor()) {
                    if (tool->formType != kFormType_Spell || Spell::Can_Damage_Health(static_cast<Spell_t*>(tool))) {
                        Virtual_Machine_t::Self()->Send_Event(this, kill_func);
                    }
                }
            } else if (Vitality() == CODES::VITALITY::INVULNERABLE) {
                value_owner->Restore_Actor_Value(Actor_Modifier_t::DAMAGE, Actor_Value_t::HEALTH, 1000000000.0f);
            }
        }
    }

    bool Member_t::Has_Token(Misc_t* token, Int_t count)
    {
        NPCP_ASSERT(Is_Filled());
        return Object_Ref::Has_Token(Actor(), token, count);
    }

    void Member_t::Token(Misc_t* token, Int_t count)
    {
        NPCP_ASSERT(Is_Filled());
        Object_Ref::Token(Actor(), token, count);
    }

    void Member_t::Untoken(Misc_t* token)
    {
        NPCP_ASSERT(Is_Filled());
        Object_Ref::Untoken(Actor(), token);
    }

    void Member_t::Create(Actor_t* actor, Bool_t is_clone)
    {
        Actor_Variable()->Pack(actor);
        Pack_Variable()->Pack(Object_Ref::Create_Container());
        Mannequin_Marker_Variable()->None();
        Display_Marker_Variable()->None();
        Undisplay_Marker_Variable()->None();
        Vanilla_Outfit_Variable()->Pack(NPCS_t::Self()->Default_Outfit(actor));

        Is_Clone_Variable()->Bool(is_clone);
        Is_Immobile_Variable()->Bool(false);
        Is_Settler_Variable()->Bool(false);
        Is_Thrall_Variable()->Bool(false);
        Is_Paralyzed_Variable()->Bool(false);
        Is_Mannequin_Variable()->Bool(false);
        Is_Display_Variable()->Bool(false);
        Is_Reanimated_Variable()->Bool(false);

        Outfit2_Variable()->Int(CODES::OUTFIT2::MEMBER);
        Rating_Variable()->Int(0);

        Backup_State();

        /*
    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_MEMBER())
    p_Backup()

    p_Member()
    Stylize(VARS.auto_style)
    p_Vitalize(VARS.auto_vitality)
    p_Outfit()

    ; has to happen after p_Member() because it needs
    ; to have the token for the full dialogue
    if p_is_clone
        ACTORS.Greet_Player(p_ref_actor)
    endIf
        */
    }

    void Member_t::Destroy()
    {

    }

    void Member_t::Backup_State()
    {
        /*
        
    p_prev_factions = ACTORS.Get_Factions(p_ref_actor)
    p_prev_faction_ranks = ACTORS.Get_Faction_Ranks(p_ref_actor, p_prev_factions)
    p_prev_faction_crime = p_ref_actor.GetCrimeFaction()

    p_prev_aggression = p_ref_actor.GetBaseActorValue("Aggression")
    p_prev_confidence = p_ref_actor.GetBaseActorValue("Confidence")
    p_prev_assistance = p_ref_actor.GetBaseActorValue("Assistance")
    p_prev_morality = p_ref_actor.GetBaseActorValue("Morality")
        
        */
    }

    void Member_t::Restore_State()
    {
        /*
        
    p_ref_actor.SetActorValue("Morality", p_prev_morality)
    p_ref_actor.SetActorValue("Assistance", p_prev_assistance)
    p_ref_actor.SetActorValue("Confidence", p_prev_confidence)
    p_ref_actor.SetActorValue("Aggression", 0.0)

    ACTORS.Set_Factions(p_ref_actor, p_prev_factions, p_prev_faction_ranks)
    p_ref_actor.SetCrimeFaction(p_prev_faction_crime)
        
        */
    }

    void Member_t::Member()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

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

        Actor2::Remove_Faction(actor, Consts::Potential_Follower_Faction());
        Actor2::Remove_Faction(actor, Consts::Current_Follower_Faction());
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

    void Member_t::Unmember()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        if (Actor2::Race_Cant_Talk_To_Player(actor)) {
            Actor2::Talks_To_Player(actor, false);
        }

        Actor2::Leave_Player_Team(actor);

        Object_Ref::Untoken(actor, Consts::Member_Token());
        Object_Ref::Untoken(actor, Consts::Clone_Token());
        Object_Ref::Untoken(actor, Consts::Generic_Token());

        // Restore() handles the rest

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Mobilize()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Immobile_Variable()->Bool(false);

        Object_Ref::Untoken(actor, Consts::Immobile_Token());

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Immobilize()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Immobile_Variable()->Bool(true);

        Object_Ref::Token(actor, Consts::Immobile_Token());

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Settle()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Settler_Variable()->Bool(true);

        Object_Ref::Token(actor, Consts::Settler_Token());

        Object_Ref::Move_To_Orbit(Settler_Marker(), actor, 0.0f, 180.0f);

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Unsettle()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Settler_Variable()->Bool(false);

        Object_Ref::Untoken(actor, Consts::Settler_Token());

        Object_Ref::Move_To_Orbit(Settler_Marker(), Consts::Storage_Marker(), 0.0f, 0.0f);

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Enthrall()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Thrall_Variable()->Bool(true);

        Object_Ref::Token(actor, Consts::Thrall_Token());

        Actor2::Add_Faction(actor, Consts::DLC1_Vampire_Feed_No_Crime_Faction());

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Unthrall()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Thrall_Variable()->Bool(false);

        Object_Ref::Untoken(actor, Consts::Thrall_Token());

        Actor2::Remove_Faction(actor, Consts::DLC1_Vampire_Feed_No_Crime_Faction());

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Paralyze()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Paralyzed_Variable()->Bool(true);

        Object_Ref::Token(actor, Consts::Paralyzed_Token());

        Object_Ref::Block_All_Activation(actor);
        Actor2::Disable_AI(actor);
        Actor2::Ghostify(actor);

        actor->Update_3D_Position();

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Reparalyze()
    {

    }

    void Member_t::Unparalyze()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Is_Paralyzed_Variable()->Bool(false);

        Object_Ref::Untoken(actor, Consts::Paralyzed_Token());

        if (Isnt_Mannequin_Unsafe()) {
            Object_Ref::Unblock_All_Activation(actor);
            Actor2::Enable_AI(actor);
            Actor2::Unghostify(actor);
        }

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Mannequinize(Reference_t* marker)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(marker); // later on, we can make loose mannequins by providing a default marker
        Actor_t* actor = Actor();

        Is_Mannequin_Variable()->Bool(true);
        Mannequin_Marker_Variable()->Pack(marker);

        Object_Ref::Token(actor, Consts::Mannequin_Token());

        Object_Ref::Block_All_Activation(actor);
        Actor2::Disable_AI(actor);
        Actor2::Ghostify(actor);

        Actor2::Move_To_Orbit(actor, marker, 0.0f, 180.0f);

        actor->pos.x = marker->pos.x;
        actor->pos.y = marker->pos.y;
        actor->pos.z = marker->pos.z;
        actor->rot.z = marker->rot.z;
        actor->Update_Actor_3D_Position();

        Actor2::Fully_Update_3D_Model(actor);
        actor->Resurrect(false, true);

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Remannequinize()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();
    }

    void Member_t::Unmannequinize()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();
        
        Is_Mannequin_Variable()->Bool(false);
        Mannequin_Marker_Variable()->None();

        Object_Ref::Untoken(actor, Consts::Mannequin_Token());

        if (Isnt_Paralyzed_Unsafe()) {
            Object_Ref::Unblock_All_Activation(actor);
            Actor2::Enable_AI(actor);
            Actor2::Unghostify(actor);
        }

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Display(Reference_t* origin, float radius, float degree)
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        if (Isnt_Display_Unsafe()) {
            Is_Display_Variable()->Bool(true);

            Object_Ref::Token(actor, Consts::Display_Token());

            Reference_t* undisplay_marker = Object_Ref::Create_Marker_At(actor);
            NPCP_ASSERT(undisplay_marker);
            Undisplay_Marker_Variable()->Pack(undisplay_marker);

            Cell_t* previous_cell = actor->parentCell;

            Actor2::Disable_Havok_Collision(actor);
            Actor2::Move_To_Orbit(actor, origin, radius, degree);

            if (!Actor2::Is_AI_Enabled(actor) && previous_cell == origin->parentCell) {
                Actor2::Fully_Update_3D_Model(actor);
            }

            Reference_t* display_marker = Object_Ref::Create_Marker_At(actor);
            NPCP_ASSERT(display_marker);
            Display_Marker_Variable()->Pack(display_marker);

            Reparalyze();
            Remannequinize();

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Redisplay()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        if (Is_Display_Unsafe()) {
            Object_Ref::Token(actor, Consts::Display_Token());
            Actor2::Disable_Havok_Collision(actor);
            Actor2::Move_To_Orbit(actor, Display_Marker(), 0.0f, 180.0f);

            Reparalyze(); // not sure about these two
            Remannequinize();

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Undisplay()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        if (Is_Display_Unsafe()) {
            Variable_t* display_marker_variable = Display_Marker_Variable();
            Reference_t* display_marker = display_marker_variable->Reference();

            Variable_t* undisplay_marker_variable = Undisplay_Marker_Variable();
            Reference_t* undisplay_marker = undisplay_marker_variable->Reference();

            Cell_t* previous_cell = actor->parentCell;

            if (undisplay_marker) {
                Actor2::Move_To_Orbit(actor, undisplay_marker, 0.0f, 180.0f);
            }
            Actor2::Enable_Havok_Collision(actor);
            
            if (!Actor2::Is_AI_Enabled(actor) && previous_cell == actor->parentCell) {
                Actor2::Fully_Update_3D_Model(actor);
            }

            Reparalyze();
            Remannequinize();

            undisplay_marker_variable->None();
            Object_Ref::Delete_Safe(undisplay_marker);

            display_marker_variable->None();
            Object_Ref::Delete_Safe(display_marker);

            Object_Ref::Untoken(actor, Consts::Display_Token());

            Is_Display_Variable()->Bool(false);

            Actor2::Evaluate_Package(actor);
        }
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
                Restylize_Default(actor);
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
                Restylize_Warrior(actor);
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
                Restylize_Mage(actor);
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
                Restylize_Archer(actor);
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
                Restylize_Coward(actor);
                Level();

                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            }
        } else {
            return CODES::MEMBER;
        }
    }

    void Member_t::Restylize(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);

        Int_t style = Style_Variable()->Int();
        if (style == CODES::STYLE::DEFAULT) {
            return Restylize_Default(actor);
        } else if (style == CODES::STYLE::WARRIOR) {
            return Restylize_Warrior(actor);
        } else if (style == CODES::STYLE::MAGE) {
            return Restylize_Mage(actor);
        } else if (style == CODES::STYLE::ARCHER) {
            return Restylize_Archer(actor);
        } else if (style == CODES::STYLE::COWARD) {
            return Restylize_Coward(actor);
        } else {
            NPCP_ASSERT(false);
        }
    }

    void Member_t::Restylize_Default(Actor_t* actor)
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

    void Member_t::Restylize_Warrior(Actor_t* actor)
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

    void Member_t::Restylize_Mage(Actor_t* actor)
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

    void Member_t::Restylize_Archer(Actor_t* actor)
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

    void Member_t::Restylize_Coward(Actor_t* actor)
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

    void Member_t::Vitalize(Int_t vitality)
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();
        
        if (vitality == CODES::VITALITY::MORTAL) {
            Vitality_Variable()->Int(CODES::VITALITY::MORTAL);
            Object_Ref::Token(actor, Consts::Mortal_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

            flags &= ~IS_PROTECTED;
            flags &= ~IS_ESSENTIAL;
        } else if (vitality == CODES::VITALITY::ESSENTIAL) {
            Vitality_Variable()->Int(CODES::VITALITY::ESSENTIAL);
            Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
            Object_Ref::Token(actor, Consts::Essential_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

            flags &= ~IS_PROTECTED;
            flags |= IS_ESSENTIAL;
        } else if (vitality == CODES::VITALITY::INVULNERABLE) {
            Vitality_Variable()->Int(CODES::VITALITY::INVULNERABLE);
            Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
            Object_Ref::Token(actor, Consts::Invulnerable_Vitality_Token());

            flags &= ~IS_PROTECTED;
            flags |= IS_ESSENTIAL;
        } else /* vitality == Vitality_e::PROTECTED */ {
            Vitality_Variable()->Int(CODES::VITALITY::PROTECTED);
            Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
            Object_Ref::Token(actor, Consts::Protected_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

            flags |= IS_PROTECTED;
            flags &= ~IS_ESSENTIAL;
        }

        Level();

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Unvitalize()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Vitality_Variable()->Int(0);

        Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
        Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Change_Outfit1(Outfit_t* outfit)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(outfit);

        Vanilla_Outfit_Variable()->Pack(outfit);
        Update_Outfit2(CODES::OUTFIT2::VANILLA, false);

        Actor_t* actor = Actor();
        if (Actor2::Base_Outfit(actor) != outfit) {
            Actor2::Set_Outfit(actor, outfit, false);
        }
        Actor2::Base_Outfit(actor, NPCS_t::Self()->Default_Outfit(actor)); // stops default outfit change on NPCS_t
        
        Vanilla_Outfit2()->Cache_Dynamic_Outfit1(actor);

        Apply_Outfit2();
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
        //Current_Outfit2_Variable()->Pack(current_outfit2, Outfit2_t::Class_Info());
        Current_Outfit2_Variable()->Pack(current_outfit2);
        Outfit2_Variable()->Int(outfit2_code);

        if (backup_outfit2) {
            //Backup_Outfit2_Variable()->Pack(backup_outfit2, Outfit2_t::Class_Info());
            Backup_Outfit2_Variable()->Pack(backup_outfit2);
        }
    }

    void Member_t::Open_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

        Outfit2_t* current_outfit2 = Current_Outfit2();
        Int_t current_outfit2_code = Outfit2();
        std::string outfit2_name = Name().c_str();

        struct Callback : public Virtual_Callback_i {
            Member_t* member;
            Callback(Member_t* member) :
                member(member)
            {
            }
            virtual void operator()(Variable_t* result)
            {
                member->Apply_Outfit2();
                Actor2::Evaluate_Package(member->Actor());
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

    void Member_t::Apply_Outfit2()
    {
        NPCP_ASSERT(Is_Filled());

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
            //Current_Outfit2_Variable()->Pack(current_outfit2, Outfit2_t::Class_Info());
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
            current_outfit2->Cache_Static_Outfit1(NPCS_t::Self()->Default_Outfit(Actor()));
        }

        current_outfit2->Apply_To(Actor(), Pack());
    }

    void Member_t::Rename(String_t new_name)
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor();

        Object_Ref::Rename(actor, new_name);

        Actor2::Evaluate_Package(actor);
    }

    void Member_t::Summon(Reference_t* origin, float radius, float degree)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(origin);
        Actor2::Move_To_Orbit(Actor(), origin, radius, degree);
    }

    void Member_t::Summon(float radius, float degree)
    {
        NPCP_ASSERT(Is_Filled());
        Summon(*g_thePlayer, radius, degree);
    }

    void Member_t::Summon_Ahead(float radius)
    {
        NPCP_ASSERT(Is_Filled());
        Summon(radius, 0);
    }

    void Member_t::Summon_Behind(float radius)
    {
        NPCP_ASSERT(Is_Filled());
        Summon(radius, 180);
    }

    void Member_t::Level()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = Follower();
        if (follower) {
            follower->Level();
        }
    }

    void Member_t::Log_Variable_Infos()
    {
        Class_Info()->Log_Variable_Infos();
    }

}}

namespace doticu_npcp { namespace Party { namespace Member { namespace Exports {

    Actor_t* Actor(Member_t* self) FORWARD_POINTER(Actor());
    Int_t ID(Member_t* self) FORWARD_INT(ID());

    Int_t Style(Member_t* self) FORWARD_INT(Style());
    Int_t Vitality(Member_t* self) FORWARD_INT(Vitality());
    String_t Name(Member_t* self) FORWARD_STRING(Member_t::Name());

    Bool_t Is_Filled(Member_t* self)        FORWARD_BOOL(Member_t::Is_Filled());
    Bool_t Is_Unfilled(Member_t* self)      FORWARD_BOOL(Member_t::Is_Unfilled());
    Bool_t Is_Loaded(Member_t* self)        FORWARD_BOOL(Member_t::Is_Loaded());
    Bool_t Is_Unloaded(Member_t* self)      FORWARD_BOOL(Member_t::Is_Unloaded());
    Bool_t Is_Unique(Member_t* self)        FORWARD_BOOL(Member_t::Is_Unique());
    Bool_t Is_Generic(Member_t* self)       FORWARD_BOOL(Member_t::Is_Generic());
    Bool_t Is_Original(Member_t* self)      FORWARD_BOOL(Member_t::Is_Original());
    Bool_t Is_Clone(Member_t* self)         FORWARD_BOOL(Member_t::Is_Clone());
    Bool_t Is_Alive(Member_t* self)         FORWARD_BOOL(Member_t::Is_Alive());
    Bool_t Is_Dead(Member_t* self)          FORWARD_BOOL(Member_t::Is_Dead());
    Bool_t Is_Mobile(Member_t* self)        FORWARD_BOOL(Member_t::Is_Mobile());
    Bool_t Is_Immobile(Member_t* self)      FORWARD_BOOL(Member_t::Is_Immobile());
    Bool_t Is_Settler(Member_t* self)       FORWARD_BOOL(Member_t::Is_Settler());
    Bool_t Isnt_Settler(Member_t* self)     FORWARD_BOOL(Member_t::Isnt_Settler());
    Bool_t Is_Thrall(Member_t* self)        FORWARD_BOOL(Member_t::Is_Thrall());
    Bool_t Isnt_Thrall(Member_t* self)      FORWARD_BOOL(Member_t::Isnt_Thrall());
    Bool_t Is_Paralyzed(Member_t* self)     FORWARD_BOOL(Member_t::Is_Paralyzed());
    Bool_t Isnt_Paralyzed(Member_t* self)   FORWARD_BOOL(Member_t::Isnt_Paralyzed());
    Bool_t Is_Mannequin(Member_t* self)     FORWARD_BOOL(Member_t::Is_Mannequin());
    Bool_t Isnt_Mannequin(Member_t* self)   FORWARD_BOOL(Member_t::Isnt_Mannequin());
    Bool_t Is_Display(Member_t* self)       FORWARD_BOOL(Member_t::Is_Display());
    Bool_t Isnt_Display(Member_t* self)     FORWARD_BOOL(Member_t::Isnt_Display());
    Bool_t Is_Reanimated(Member_t* self)    FORWARD_BOOL(Member_t::Is_Reanimated());
    Bool_t Isnt_Reanimated(Member_t* self)  FORWARD_BOOL(Member_t::Isnt_Reanimated());
    Bool_t Is_Follower(Member_t* self)      FORWARD_BOOL(Member_t::Is_Follower());
    Bool_t Isnt_Follower(Member_t* self)    FORWARD_BOOL(Member_t::Isnt_Follower());
    Bool_t Is_Sneak(Member_t* self)         FORWARD_BOOL(Member_t::Is_Sneak());
    Bool_t Isnt_Sneak(Member_t* self)       FORWARD_BOOL(Member_t::Isnt_Sneak());
    Bool_t Is_Saddler(Member_t* self)       FORWARD_BOOL(Member_t::Is_Saddler());
    Bool_t Isnt_Saddler(Member_t* self)     FORWARD_BOOL(Member_t::Isnt_Saddler());
    Bool_t Is_Retreater(Member_t* self)     FORWARD_BOOL(Member_t::Is_Retreater());
    Bool_t Isnt_Retreater(Member_t* self)   FORWARD_BOOL(Member_t::Isnt_Retreater());

    void On_Hit(Member_t* self,
                Reference_t* attacker,
                Form_t* tool,
                Projectile_Base_t* projectile,
                Bool_t is_power,
                Bool_t is_sneak,
                Bool_t is_bash,
                Bool_t is_blocked)
        FORWARD_VOID(On_Hit(attacker, tool, projectile, is_power, is_sneak, is_bash, is_blocked));

    bool Has_Token(Member_t* self, Misc_t* token, Int_t count) FORWARD_BOOL(Member_t::Has_Token(token, count));
    void Token(Member_t* self, Misc_t* token, Int_t count) FORWARD_VOID(Member_t::Token(token, count));
    void Untoken(Member_t* self, Misc_t* token) FORWARD_VOID(Member_t::Untoken(token));

    void Member(Member_t* self) FORWARD_VOID(Member_t::Member());
    void Unmember(Member_t* self) FORWARD_VOID(Member_t::Unmember());
    void Mobilize(Member_t* self) FORWARD_VOID(Member_t::Mobilize());
    void Immobilize(Member_t* self) FORWARD_VOID(Member_t::Immobilize());
    void Settle(Member_t* self) FORWARD_VOID(Member_t::Settle());
    void Unsettle(Member_t* self) FORWARD_VOID(Member_t::Unsettle());
    void Enthrall(Member_t* self) FORWARD_VOID(Member_t::Enthrall());
    void Unthrall(Member_t* self) FORWARD_VOID(Member_t::Unthrall());
    void Paralyze(Member_t* self) FORWARD_VOID(Member_t::Paralyze());
    void Unparalyze(Member_t* self) FORWARD_VOID(Member_t::Unparalyze());
    void Mannequinize(Member_t* self, Reference_t* marker) FORWARD_VOID(Member_t::Mannequinize(marker));
    void Unmannequinize(Member_t* self) FORWARD_VOID(Member_t::Unmannequinize());

    Int_t Stylize(Member_t* self, Int_t style) FORWARD_INT(Member_t::Stylize(style));
    Int_t Stylize_Default(Member_t* self) FORWARD_INT(Member_t::Stylize_Default());
    Int_t Stylize_Warrior(Member_t* self) FORWARD_INT(Member_t::Stylize_Warrior());
    Int_t Stylize_Mage(Member_t* self) FORWARD_INT(Member_t::Stylize_Mage());
    Int_t Stylize_Archer(Member_t* self) FORWARD_INT(Member_t::Stylize_Archer());
    Int_t Stylize_Coward(Member_t* self) FORWARD_INT(Member_t::Stylize_Coward());
    void Restylize(Member_t* self, Actor_t* actor) FORWARD_VOID(Member_t::Restylize(actor));
    Int_t Unstylize(Member_t* self) FORWARD_INT(Member_t::Unstylize());

    void Vitalize(Member_t* self, Int_t vitality) FORWARD_VOID(Member_t::Vitalize(vitality));
    void Unvitalize(Member_t* self) FORWARD_VOID(Member_t::Unvitalize());

    void Change_Outfit1(Member_t* self, Outfit_t* outfit) FORWARD_VOID(Change_Outfit1(outfit));
    Int_t Change_Outfit2(Member_t* self, Int_t outfit2_code) FORWARD_INT(Change_Outfit2(outfit2_code));
    Int_t Change_Member_Outfit2(Member_t* self) FORWARD_INT(Change_Member_Outfit2());
    Int_t Change_Immobile_Outfit2(Member_t* self) FORWARD_INT(Change_Immobile_Outfit2());
    Int_t Change_Settler_Outfit2(Member_t* self) FORWARD_INT(Change_Settler_Outfit2());
    Int_t Change_Thrall_Outfit2(Member_t* self) FORWARD_INT(Change_Thrall_Outfit2());
    Int_t Change_Follower_Outfit2(Member_t* self) FORWARD_INT(Change_Follower_Outfit2());
    Int_t Change_Vanilla_Outfit2(Member_t* self) FORWARD_INT(Change_Vanilla_Outfit2());
    Int_t Change_Default_Outfit2(Member_t* self) FORWARD_INT(Change_Default_Outfit2());
    Int_t Change_Current_Outfit2(Member_t* self) FORWARD_INT(Change_Current_Outfit2());
    void Update_Outfit2(Member_t* self, Int_t outfit2_code, Bool_t do_cache_outfit1) FORWARD_VOID(Update_Outfit2(outfit2_code, do_cache_outfit1));
    void Open_Outfit2(Member_t* self) FORWARD_VOID(Open_Outfit2());
    void Apply_Outfit2(Member_t* self) FORWARD_VOID(Apply_Outfit2());

    void Rename(Member_t* self, String_t new_name) FORWARD_VOID(Member_t::Rename(new_name));

    void Log_Variable_Infos(Member_t* self) FORWARD_VOID(Log_Variable_Infos());

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Member_t::Class_Name(), Member_t,          \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("Actor", 0, Actor_t*, Actor);
        ADD_METHOD("ID", 0, Int_t, ID);

        ADD_METHOD("Style", 0, Int_t, Style);
        ADD_METHOD("Vitality", 0, Int_t, Vitality);
        ADD_METHOD("Name", 0, String_t, Name);

        ADD_METHOD("Is_Filled", 0, Bool_t, Is_Filled);
        ADD_METHOD("Is_Unfilled", 0, Bool_t, Is_Unfilled);
        ADD_METHOD("Is_Loaded", 0, Bool_t, Is_Loaded);
        ADD_METHOD("Is_Unloaded", 0, Bool_t, Is_Unloaded);
        ADD_METHOD("Is_Unique", 0, Bool_t, Is_Unique);
        ADD_METHOD("Is_Generic", 0, Bool_t, Is_Generic);
        ADD_METHOD("Is_Original", 0, Bool_t, Is_Original);
        ADD_METHOD("Is_Clone", 0, Bool_t, Is_Clone);
        ADD_METHOD("Is_Alive", 0, Bool_t, Is_Alive);
        ADD_METHOD("Is_Dead", 0, Bool_t, Is_Dead);
        ADD_METHOD("Is_Mobile", 0, Bool_t, Is_Mobile);
        ADD_METHOD("Is_Immobile", 0, Bool_t, Is_Immobile);
        ADD_METHOD("Is_Settler", 0, Bool_t, Is_Settler);
        ADD_METHOD("Isnt_Settler", 0, Bool_t, Isnt_Settler);
        ADD_METHOD("Is_Thrall", 0, Bool_t, Is_Thrall);
        ADD_METHOD("Isnt_Thrall", 0, Bool_t, Isnt_Thrall);
        ADD_METHOD("Is_Paralyzed", 0, Bool_t, Is_Paralyzed);
        ADD_METHOD("Isnt_Paralyzed", 0, Bool_t, Isnt_Paralyzed);
        ADD_METHOD("Is_Mannequin", 0, Bool_t, Is_Mannequin);
        ADD_METHOD("Isnt_Mannequin", 0, Bool_t, Isnt_Mannequin);
        ADD_METHOD("Is_Display", 0, Bool_t, Is_Display);
        ADD_METHOD("Isnt_Display", 0, Bool_t, Isnt_Display);
        ADD_METHOD("Is_Reanimated", 0, Bool_t, Is_Reanimated);
        ADD_METHOD("Isnt_Reanimated", 0, Bool_t, Isnt_Reanimated);
        ADD_METHOD("Is_Follower", 0, Bool_t, Is_Follower);
        ADD_METHOD("Isnt_Follower", 0, Bool_t, Isnt_Follower);
        ADD_METHOD("Is_Sneak", 0, Bool_t, Is_Sneak);
        ADD_METHOD("Isnt_Sneak", 0, Bool_t, Isnt_Sneak);
        ADD_METHOD("Is_Saddler", 0, Bool_t, Is_Saddler);
        ADD_METHOD("Isnt_Saddler", 0, Bool_t, Isnt_Saddler);
        ADD_METHOD("Is_Retreater", 0, Bool_t, Is_Retreater);
        ADD_METHOD("Isnt_Retreater", 0, Bool_t, Isnt_Retreater);

        ADD_METHOD("OnHit", 7, void, On_Hit, Reference_t*, Form_t*, Projectile_Base_t*, Bool_t, Bool_t, Bool_t, Bool_t);

        ADD_METHOD("Has_Token", 2, bool, Has_Token, Misc_t*, Int_t);
        ADD_METHOD("Token", 2, void, Token, Misc_t*, Int_t);
        ADD_METHOD("Untoken", 1, void, Untoken, Misc_t*);

        ADD_METHOD("p_Member", 0, void, Member);
        ADD_METHOD("p_Unmember", 0, void, Unmember);
        ADD_METHOD("p_Mobilize", 0, void, Mobilize);
        ADD_METHOD("p_Immobilize", 0, void, Immobilize);
        ADD_METHOD("p_Settle", 0, void, Settle);
        ADD_METHOD("p_Unsettle", 0, void, Unsettle);
        ADD_METHOD("p_Enthrall", 0, void, Enthrall);
        ADD_METHOD("p_Unthrall", 0, void, Unthrall);
        ADD_METHOD("p_Paralyze", 0, void, Paralyze);
        ADD_METHOD("p_Unparalyze", 0, void, Unparalyze);
        ADD_METHOD("p_Mannequinize", 1, void, Mannequinize, Reference_t*);
        ADD_METHOD("p_Unmannequinize", 0, void, Unmannequinize);

        ADD_METHOD("Stylize", 1, Int_t, Stylize, Int_t);
        ADD_METHOD("Stylize_Default", 0, Int_t, Stylize_Default);
        ADD_METHOD("Stylize_Warrior", 0, Int_t, Stylize_Warrior);
        ADD_METHOD("Stylize_Mage", 0, Int_t, Stylize_Mage);
        ADD_METHOD("Stylize_Archer", 0, Int_t, Stylize_Archer);
        ADD_METHOD("Stylize_Coward", 0, Int_t, Stylize_Coward);
        ADD_METHOD("p_Restylize", 1, void, Restylize, Actor_t*);
        ADD_METHOD("Unstylize", 0, Int_t, Unstylize);

        ADD_METHOD("p_Vitalize", 1, void, Vitalize, Int_t);
        ADD_METHOD("p_Unvitalize", 0, void, Unvitalize);

        ADD_METHOD("p_Change_Outfit1", 1, void, Change_Outfit1, Outfit_t*);
        ADD_METHOD("Change_Outfit2", 1, Int_t, Change_Outfit2, Int_t);
        ADD_METHOD("Change_Member_Outfit2", 0, Int_t, Change_Member_Outfit2);
        ADD_METHOD("Change_Immobile_Outfit2", 0, Int_t, Change_Immobile_Outfit2);
        ADD_METHOD("Change_Settler_Outfit2", 0, Int_t, Change_Settler_Outfit2);
        ADD_METHOD("Change_Thrall_Outfit2", 0, Int_t, Change_Thrall_Outfit2);
        ADD_METHOD("Change_Follower_Outfit2", 0, Int_t, Change_Follower_Outfit2);
        ADD_METHOD("Change_Vanilla_Outfit2", 0, Int_t, Change_Vanilla_Outfit2);
        ADD_METHOD("Change_Default_Outfit2", 0, Int_t, Change_Default_Outfit2);
        ADD_METHOD("Change_Current_Outfit2", 0, Int_t, Change_Current_Outfit2);
        ADD_METHOD("p_Update_Outfit2", 2, void, Update_Outfit2, Int_t, Bool_t);
        ADD_METHOD("p_Open_Outfit2", 0, void, Open_Outfit2);
        ADD_METHOD("p_Apply_Outfit2", 0, void, Apply_Outfit2);

        ADD_METHOD("p_Rename", 1, void, Rename, String_t);

        ADD_METHOD("Log_Variable_Infos", 0, void, Log_Variable_Infos);

        #undef ADD_METHOD

        return true;
    }

}}}}
