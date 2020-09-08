/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "commands.h"
#include "consts.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

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
        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "f_Begin_Combat");
    }

    void Player_t::Try_To_End_Combat()
    {

    }

    void Player_t::End_Combat()
    {

    }

    void Player_t::On_Control_Down(String_t control)
    {
        static Actor_t* player_actor = Actor();
        static Members_t* members = Members_t::Self();
        static Followers_t* followers = Followers_t::Self();

        if (String2::Is_Same_Caseless(control, "Sneak")) {
            if (Actor2::Is_Sneaking(player_actor) && Is_Party_In_Combat()) {
                followers->Retreat();
            } else {
                followers->Unretreat();
            }
        } else if (String2::Is_Same_Caseless(control, "Forward")) {
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

        #undef METHOD
    }

}}}
