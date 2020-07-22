/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "actor_base2.h"
#include "consts.h"
#include "object_ref.h"
#include "party.h"
#include "party.inl"
#include "utils.h"

namespace doticu_npcp { namespace Party {

    String_t Member_t::Class_Name()
    {
        static const String_t class_name = Utils::Assert(
            String_t("doticu_npcp_member")
        );
        return class_name;
    }

    Class_Info_t* Member_t::Class_Info()
    {
        static Class_Info_t* class_info = Utils::Assert(
            Class_Info_t::Fetch(Class_Name())
        );
        return class_info;
    }

    Variable_t* Member_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Variable_t* Member_t::Is_Immobile_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_is_immobile")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Member_t::Is_Settler_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_is_settler")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Member_t::Is_Thrall_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_is_thrall")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Member_t::Is_Paralyzed_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_is_paralyzed")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Member_t::Is_Mannequin_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_is_mannequin")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Member_t::Mannequin_Marker_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_marker_mannequin")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Member_t::Style_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_code_style")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Variable_t* Member_t::Vitality_Variable()
    {
        static const String_t variable_name = Utils::Assert(
            String_t("p_code_vitality")
        );
        return Utils::Assert(
            Variable(variable_name)
        );
    }

    Actor_t* Member_t::Actor()
    {
        static const String_t variable_name = String_t("p_ref_actor");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Actor();
        } else {
            return nullptr;
        }
    }

    Follower_t* Member_t::Follower()
    {
        Followers_t* followers = Followers_t::Self();
        if (followers) {
            return followers->From_Actor(Actor());
        } else {
            return nullptr;
        }
    }

    Reference_t* Member_t::Pack()
    {
        static const String_t variable_name = String_t("p_container_pack");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Reference();
        } else {
            return nullptr;
        }
    }

    Reference_t* Member_t::Settler_Marker()
    {
        Formlist_t* settler_markers = Consts::Settler_Markers_Formlist();
        NPCP_ASSERT(settler_markers->forms.count == Members_t::MAX);
        return static_cast<Reference_t*>(settler_markers->forms.entries[ID()]);
    }

    Cell_t* Member_t::Cell()
    {
        Actor_t* actor = Actor();
        return actor ? actor->parentCell : nullptr;
    }

    Int_t Member_t::Style()
    {
        return Style_Variable()->Int();
    }

    Int_t Member_t::Vitality()
    {
        return Vitality_Variable()->Int();
    }

    Int_t Member_t::Outfit2()
    {
        static const String_t variable_name = String_t("p_code_outfit2");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    Int_t Member_t::Rating()
    {
        static const String_t variable_name = String_t("p_int_rating");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    String_t Member_t::Sex()
    {
        static const String_t male = String_t("male");
        static const String_t female = String_t("female");
        static const String_t none = String_t("none");
        static const String_t invalid = String_t("");

        Int_t sex = Actor2::Sex(Actor());
        if (sex == 0) {
            return male;
        } else if (sex == 1) {
            return female;
        } else if (sex == -1) {
            return none;
        } else {
            return invalid;
        }
    }

    String_t Member_t::Race()
    {
        Actor_t* actor = Actor();
        return actor ? Actor2::Race(actor) : "";
    }

    String_t Member_t::Base_Name()
    {
        return Actor2::Get_Base_Name(Actor());
    }

    String_t Member_t::Reference_Name()
    {
        return Actor2::Get_Ref_Name(Actor());
    }

    String_t Member_t::Name()
    {
        return Actor2::Get_Name(Actor());
    }

    /*Bool_t Member_t::Is_Filled()
    {
        return Is_Created() && Actor() != nullptr;
    }

    Bool_t Member_t::Is_Unfilled()
    {
        return Is_Destroyed() || Actor() == nullptr;
    }*/

    Bool_t Member_t::Is_Loaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Loaded(actor);
    }

    Bool_t Member_t::Is_Unloaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unloaded(actor);
    }

    Bool_t Member_t::Is_Created()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Destroyed()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Unique()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unique(actor);
    }

    Bool_t Member_t::Is_Generic()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Generic(actor);
    }

    Bool_t Member_t::Is_Original()
    {
        static const String_t variable_name = String_t("p_is_clone");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Clone()
    {
        static const String_t variable_name = String_t("p_is_clone");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Alive()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Alive(actor);
    }

    Bool_t Member_t::Is_Dead()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Dead(actor);
    }

    Bool_t Member_t::Is_Mobile()
    {
        Variable_t* const variable = Is_Immobile_Variable();
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Immobile()
    {
        Variable_t* const variable = Is_Immobile_Variable();
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Settler()
    {
        Variable_t* const variable = Is_Settler_Variable();
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Settler()
    {
        Variable_t* const variable = Is_Settler_Variable();
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Thrall()
    {
        Variable_t* const variable = Is_Thrall_Variable();
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Thrall()
    {
        Variable_t* const variable = Is_Thrall_Variable();
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Paralyzed()
    {
        Variable_t* const variable = Is_Paralyzed_Variable();
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Paralyzed()
    {
        Variable_t* const variable = Is_Paralyzed_Variable();
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Mannequin()
    {
        Variable_t* const variable = Is_Mannequin_Variable();
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Mannequin()
    {
        Variable_t* const variable = Is_Mannequin_Variable();
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Reanimated()
    {
        static const String_t variable_name = String_t("p_is_reanimated");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Isnt_Reanimated()
    {
        static const String_t variable_name = String_t("p_is_reanimated");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Member_t::Is_Follower()
    {
        return Follower() != nullptr;
    }

    Bool_t Member_t::Isnt_Follower()
    {
        return Follower() == nullptr;
    }

    Bool_t Member_t::Is_Sneak()
    {
        Follower_t* follower = Follower();
        return follower && follower->Is_Sneak();
    }

    Bool_t Member_t::Isnt_Sneak()
    {
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Sneak();
    }

    Bool_t Member_t::Is_Saddler()
    {
        Follower_t* follower = Follower();
        return follower && follower->Is_Saddler();
    }

    Bool_t Member_t::Isnt_Saddler()
    {
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Saddler();
    }

    Bool_t Member_t::Is_Retreater()
    {
        Follower_t* follower = Follower();
        return follower && follower->Is_Retreater();
    }

    Bool_t Member_t::Isnt_Retreater()
    {
        Follower_t* follower = Follower();
        return follower && follower->Isnt_Retreater();
    }

    Bool_t Member_t::Has_Same_Head(Actor_t* other_actor)
    {
        if (other_actor) {
            Actor_t* alias_actor = Actor();
            if (alias_actor && Is_Created()) {
                Actor_Base_t* other_actor_base = static_cast<Actor_Base_t*>(other_actor->baseForm);
                Actor_Base_t* alias_actor_base = static_cast<Actor_Base_t*>(alias_actor->baseForm);
                if (other_actor_base && alias_actor_base && Actor_Base2::Has_Same_Head(other_actor_base, alias_actor_base)) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
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
        static const String_t kill_func = String_t("p_Kill");

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(Actor());
        if (value_owner && Is_Alive()) {
            Int_t vitality = Vitality();
            if (value_owner->Get_Actor_Value(Actor_Value_t::HEALTH) <= 0.0) {
                if (vitality == Vitality_e::MORTAL || vitality == Vitality_e::PROTECTED && attacker == *g_thePlayer) {
                    struct Args : public IFunctionArguments {
                        bool Copy(Output* output)
                        {
                            return true;
                        }
                    } func_args;
                    Handle_t handle(this);
                    handle.Registry()->QueueEvent(handle, &kill_func, &func_args);
                }
            } else if (vitality == Vitality_e::INVULNERABLE) {
                value_owner->Restore_Actor_Value(Actor_Modifier_t::DAMAGE, Actor_Value_t::HEALTH, 1000000000.0f);
            }
        }
    }

    bool Member_t::Has_Token(Misc_t* token, Int_t count)
    {
        return Object_Ref::Has_Token(Actor(), token, count);
    }

    void Member_t::Token(Misc_t* token, Int_t count)
    {
        Object_Ref::Token(Actor(), token, count);
    }

    void Member_t::Untoken(Misc_t* token)
    {
        Object_Ref::Untoken(Actor(), token);
    }

    void Member_t::Member()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Object_Ref::Token(actor, Consts::Member_Token(), ID() + 1);
            if (Is_Clone()) {
                Object_Ref::Token(actor, Consts::Clone_Token());
            } else {
                Object_Ref::Untoken(actor, Consts::Clone_Token());
            }
            if (Is_Generic()) {
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
            if (value_owner) {
                value_owner->Set_Actor_Value(Actor_Value_t::AGGRESSION, 0.0f);
                value_owner->Set_Actor_Value(Actor_Value_t::CONFIDENCE, 4.0f);
                value_owner->Set_Actor_Value(Actor_Value_t::ASSISTANCE, 2.0f);
                value_owner->Set_Actor_Value(Actor_Value_t::MORALITY, 0.0f);
                value_owner->Set_Actor_Value(Actor_Value_t::WAITING_FOR_PLAYER, 0.0f);
            }

            Actor2::Follow_Player(actor, true);

            if (Actor2::Cant_Talk_To_Player(actor)) {
                Actor2::Talks_To_Player(actor, true);
            }

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Unmember()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            if (Actor2::Race_Cant_Talk_To_Player(actor)) {
                Actor2::Talks_To_Player(actor, false);
            }

            Actor2::Unfollow_Player(actor);

            Object_Ref::Untoken(actor, Consts::Member_Token());
            Object_Ref::Untoken(actor, Consts::Clone_Token());
            Object_Ref::Untoken(actor, Consts::Generic_Token());

            // Restore() handles the rest

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Mobilize()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Immobile_Variable()->Bool(false);

            Object_Ref::Untoken(actor, Consts::Immobile_Token());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Immobilize()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Immobile_Variable()->Bool(true);

            Object_Ref::Token(actor, Consts::Immobile_Token());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Settle()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Settler_Variable()->Bool(true);

            Object_Ref::Token(actor, Consts::Settler_Token());

            Object_Ref::Move_To_Orbit(Settler_Marker(), actor, 0.0f, 180.0f);

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Unsettle()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Settler_Variable()->Bool(false);

            Object_Ref::Untoken(actor, Consts::Settler_Token());

            Object_Ref::Move_To_Orbit(Settler_Marker(), Consts::Storage_Marker(), 0.0f, 0.0f);

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Enthrall()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Thrall_Variable()->Bool(true);

            Object_Ref::Token(actor, Consts::Thrall_Token());

            Actor2::Add_Faction(actor, Consts::DLC1_Vampire_Feed_No_Crime_Faction());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Unthrall()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Thrall_Variable()->Bool(false);

            Object_Ref::Untoken(actor, Consts::Thrall_Token());

            Actor2::Remove_Faction(actor, Consts::DLC1_Vampire_Feed_No_Crime_Faction());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Paralyze()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Paralyzed_Variable()->Bool(true);

            Object_Ref::Token(actor, Consts::Paralyzed_Token());

            Object_Ref::Block_All_Activation(actor);
            Actor2::Disable_AI(actor);
            Actor2::Ghostify(actor);

            actor->Update_3D_Position();

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Unparalyze()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Paralyzed_Variable()->Bool(false);

            Object_Ref::Untoken(actor, Consts::Paralyzed_Token());

            if (Isnt_Mannequin()) {
                Object_Ref::Unblock_All_Activation(actor);
                Actor2::Enable_AI(actor);
                Actor2::Unghostify(actor);
            }

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Mannequinize(Reference_t* marker)
    {
        NPCP_ASSERT(marker); // later on, we can make loose mannequins by providing a default marker

        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Mannequin_Variable()->Bool(true);
            Mannequin_Marker_Variable()->Pack(marker);

            Object_Ref::Token(actor, Consts::Mannequin_Token());

            Object_Ref::Block_All_Activation(actor);
            Actor2::Disable_AI(actor);
            Actor2::Ghostify(actor);

            Object_Ref::Move_To_Orbit(actor, marker, 0.0f, 180.0f);
            actor->pos.x = marker->pos.x;
            actor->pos.y = marker->pos.y;
            actor->pos.z = marker->pos.z;
            actor->rot.z = marker->rot.z;
            actor->Update_Actor_3D_Position();

            Actor2::Fully_Update_3D_Model(actor);
            actor->Resurrect(false, true); // this feels good to have here

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Unmannequinize()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Is_Mannequin_Variable()->Bool(false);
            Mannequin_Marker_Variable()->None();

            Object_Ref::Untoken(actor, Consts::Mannequin_Token());

            if (Isnt_Paralyzed()) {
                Object_Ref::Unblock_All_Activation(actor);
                Actor2::Enable_AI(actor);
                Actor2::Unghostify(actor);
            }

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Stylize(Int_t style)
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            if (style == Style_e::WARRIOR) {
                Style_Variable()->Int(Style_e::WARRIOR);
                Object_Ref::Untoken(actor, Consts::Default_Style_Token());
                Object_Ref::Token(actor, Consts::Warrior_Style_Token());
                Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
                Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
                Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
            } else if (style == Style_e::MAGE) {
                Style_Variable()->Int(Style_e::MAGE);
                Object_Ref::Untoken(actor, Consts::Default_Style_Token());
                Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
                Object_Ref::Token(actor, Consts::Mage_Style_Token());
                Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
                Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
            } else if (style == Style_e::ARCHER) {
                Style_Variable()->Int(Style_e::ARCHER);
                Object_Ref::Untoken(actor, Consts::Default_Style_Token());
                Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
                Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
                Object_Ref::Token(actor, Consts::Archer_Style_Token());
                Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
            } else if (style == Style_e::COWARD) {
                Style_Variable()->Int(Style_e::COWARD);
                Object_Ref::Untoken(actor, Consts::Default_Style_Token());
                Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
                Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
                Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
                Object_Ref::Token(actor, Consts::Coward_Style_Token());
            } else /* style == Style_e::DEFAULT */ {
                Style_Variable()->Int(Style_e::DEFAULT);
                Object_Ref::Token(actor, Consts::Default_Style_Token());
                Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
                Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
                Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
                Object_Ref::Untoken(actor, Consts::Coward_Style_Token());
            }

            Level();

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Unstylize()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Style_Variable()->Int(0);

            Object_Ref::Untoken(actor, Consts::Default_Style_Token());
            Object_Ref::Untoken(actor, Consts::Warrior_Style_Token());
            Object_Ref::Untoken(actor, Consts::Mage_Style_Token());
            Object_Ref::Untoken(actor, Consts::Archer_Style_Token());
            Object_Ref::Untoken(actor, Consts::Coward_Style_Token());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Vitalize(Int_t vitality)
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            if (vitality == Vitality_e::MORTAL) {
                Vitality_Variable()->Int(Vitality_e::MORTAL);
                Object_Ref::Token(actor, Consts::Mortal_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());
            } else if (vitality == Vitality_e::ESSENTIAL) {
                Vitality_Variable()->Int(Vitality_e::ESSENTIAL);
                Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
                Object_Ref::Token(actor, Consts::Essential_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());
            } else if (vitality == Vitality_e::INVULNERABLE) {
                Vitality_Variable()->Int(Vitality_e::INVULNERABLE);
                Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
                Object_Ref::Token(actor, Consts::Invulnerable_Vitality_Token());
            } else /* vitality == Vitality_e::PROTECTED */ {
                Vitality_Variable()->Int(Vitality_e::PROTECTED);
                Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
                Object_Ref::Token(actor, Consts::Protected_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
                Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());
            }

            Level();

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Unvitalize()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Vitality_Variable()->Int(0);

            Object_Ref::Untoken(actor, Consts::Mortal_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Protected_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Essential_Vitality_Token());
            Object_Ref::Untoken(actor, Consts::Invulnerable_Vitality_Token());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Rename(String_t new_name)
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Object_Ref::Rename(actor, new_name);

            Actor2::Evaluate_Package(actor);
        }
    }

    void Member_t::Level()
    {
        Follower_t* follower = Follower();
        if (follower) {
            follower->Level();
        }
    }

    void Member_t::Log_Variable_Infos()
    {
        Object_t* script = Object_t::Fetch(this, "doticu_npcp_member");
        if (script) {
            Class_Info_t* info = script->info;
            while (info) {
                info->Log_Variable_Infos();
                info = info->parent != info ? info->parent : nullptr;
            }
        }
    }

}}

namespace doticu_npcp { namespace Party { namespace Member { namespace Exports {

    Actor_t* Actor(Member_t* self) FORWARD_POINTER(Actor());
    Int_t ID(Member_t* self) FORWARD_INT(ID());

    Int_t Style(Member_t* self) FORWARD_INT(Style());
    Int_t Vitality(Member_t* self) FORWARD_INT(Vitality());
    String_t Name(Member_t* self) FORWARD_STRING(Member_t::Name());

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
    void Stylize(Member_t* self, Int_t style) FORWARD_VOID(Member_t::Stylize(style));
    void Unstylize(Member_t* self) FORWARD_VOID(Member_t::Unstylize());
    void Vitalize(Member_t* self, Int_t vitality) FORWARD_VOID(Member_t::Vitalize(vitality));
    void Unvitalize(Member_t* self) FORWARD_VOID(Member_t::Unvitalize());

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
        ADD_METHOD("p_Stylize", 1, void, Stylize, Int_t);
        ADD_METHOD("p_Unstylize", 0, void, Unstylize);
        ADD_METHOD("p_Vitalize", 1, void, Vitalize, Int_t);
        ADD_METHOD("p_Unvitalize", 0, void, Unvitalize);

        ADD_METHOD("p_Rename", 1, void, Rename, String_t);

        ADD_METHOD("Log_Variable_Infos", 0, void, Log_Variable_Infos);

        #undef ADD_METHOD

        return true;
    }

}}}}
