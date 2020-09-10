/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "commands.h"
#include "consts.h"
#include "funcs.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"
#include "vars.h"

#include "party/party_player.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_followers.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Player_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_player");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Player_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Player_t* Player_t::Self()
    {
        return reinterpret_cast<Player_t*>(*(Consts::Funcs_Quest()->aliases.entries + 0));
    }

    Object_t* Player_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Player_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Player_t::Is_In_Combat_Variable() { DEFINE_VARIABLE("p_is_in_combat"); }

    Actor_t* Player_t::Actor()
    {
        return Consts::Player_Actor();
    }

    Player_Character_t* Player_t::Player_Character()
    {
        return static_cast<PlayerCharacter*>(Actor());
    }

    Location_t* Player_t::Location()
    {
        return Player_Character()->locationAC8;
    }

    Bool_t Player_t::Is_Party_In_Combat()
    {
        return Actor()->IsInCombat() || Party::Followers_t::Self()->Are_In_Combat();
    }

    Bool_t Player_t::Is_In_Interior_Cell()
    {
        return Object_Ref::Is_In_Interior_Cell(Actor());
    }

    Bool_t Player_t::Is_In_Exterior_Cell()
    {
        return Object_Ref::Is_In_Exterior_Cell(Actor());
    }

    Bool_t Player_t::Is_On_Mount()
    {
        return Actor2::Is_On_Mount(Actor());
    }

    Bool_t Player_t::Is_Vampire()
    {
        return Actor2::Is_Vampire(Actor());
    }

    Bool_t Player_t::Is_Sneaking()
    {
        return Actor2::Is_Sneaking(Actor());
    }

    void Player_t::Begin_Combat()
    {
        Variable_t* is_in_combat_variable = Is_In_Combat_Variable();
        if (is_in_combat_variable->Bool() == false) {
            is_in_combat_variable->Bool(true);

            
            Followers_t* followers = Followers_t::Self();
            followers->Catch_Up();
            if (Is_Sneaking()) {
                followers->Retreat();
            }

            Try_To_End_Combat();
        }
    }

    void Player_t::Try_To_End_Combat()
    {
        if (Is_Party_In_Combat()) {
            struct VCallback : public Virtual_Callback_t {
                Player_t* player;
                VCallback(Player_t* player) :
                    player(player)
                {
                }
                void operator()(Variable_t* result)
                {
                    player->Try_To_End_Combat();
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this);
            Modules::Funcs_t::Self()->Wait_Out_Of_Menu(5.0f, &vcallback);
        } else {
            End_Combat();
        }
    }

    void Player_t::End_Combat()
    {
        Is_In_Combat_Variable()->Bool(false);
        
        if (!Is_Sneaking()) {
            Followers_t::Self()->Unretreat();
        }

        Members_t::Self()->Enforce_Loaded(Vars::Do_Auto_Resurrect());
    }

    void Player_t::On_Init_Mod()
    {
        Actor2::Add_Spell(Actor(), Consts::Cell_Ability_Spell());
    }

    void Player_t::On_Load_Mod()
    {
        Actor2::Add_Spell(Actor(), Consts::Cell_Ability_Spell());

        if (!Is_Party_In_Combat()) {
            End_Combat();
        }
    }

    void Player_t::On_Cell_Change(Cell_t* new_cell, Cell_t* old_cell)
    {
        Actor_t* player_actor = Actor();
        if (!Actor2::Has_Magic_Effect(player_actor, Consts::Cell_Magic_Effect())) {
            Actor2::Add_Spell(player_actor, Consts::Cell_Ability_Spell());
        }
        Followers_t::Self()->Catch_Up();
    }

    void Player_t::On_Control_Down(String_t control)
    {
        Actor_t* player_actor = Actor();
        if (!Actor2::Has_Magic_Effect(player_actor, Consts::Cell_Magic_Effect())) {
            Actor2::Add_Spell(player_actor, Consts::Cell_Ability_Spell());
        }

        if (String2::Is_Same_Caseless(control, "Sneak")) {
            Followers_t* followers = Followers_t::Self();
            if (Is_Sneaking() && Is_Party_In_Combat()) {
                followers->Retreat();
            } else {
                followers->Unretreat();
            }
        } else if (String2::Is_Same_Caseless(control, "Forward")) {
            Members_t* members = Members_t::Self();
            Followers_t* followers = Followers_t::Self();
            Vector_t<Member_t*> loaded_members = members->Loaded();
            for (size_t idx = 0, count = loaded_members.size(); idx < count; idx += 1) {
                Member_t* member = loaded_members[idx];
                Actor_t* actor = member->Actor();
                member->Enforce_Name(actor, member->Name());

                Follower_t* follower = member->Follower();
                if (follower && !followers->Can_Actor_Follow(actor)) {
                    Modules::Control::Commands_t::Self()->Relinquish(actor);
                }
            }
        }
    }

    void Player_t::On_Actor_Action(Int_t action_code, Actor_t* actor, Form_t* tool, Int_t tool_slot)
    {
        if (actor == Actor()) {
            if (action_code == CODES::ACTION::DRAW_END) {
                if (!Is_Party_In_Combat()) {
                    Followers_t::Self()->Catch_Up();
                }
            }
        }
    }

    void Player_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Player_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("Is_Party_In_Combat", 0, Bool_t, Is_Party_In_Combat);
        METHOD("OnControlDown", 1, void, On_Control_Down, String_t);
        METHOD("OnActorAction", 4, void, On_Actor_Action, Int_t, Actor_t*, Form_t*, Int_t);
        
        #undef METHOD
    }

}}}
