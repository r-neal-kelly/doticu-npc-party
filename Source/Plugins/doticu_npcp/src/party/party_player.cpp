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

#include "party/party_alias.inl"
#include "party/party_player.h"
#include "party/party_movee.h"
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

    Variable_t* Player_t::Is_Locked_Variable() { DEFINE_VARIABLE("p_is_locked"); }
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

    void Player_t::Lock(Callback_t<Player_t*>* on_lock, Float_t interval, Float_t limit)
    {
        Alias_t::Lock(this, on_lock, interval, limit);
    }
    void Player_t::Unlock()
    {
        Alias_t::Unlock(this);
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
            Modules::Funcs_t::Self()->Wait_Out_Of_Menu(UPDATE_INTERVAL, &vcallback);
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
        On_Update();
    }

    void Player_t::On_Load_Mod()
    {
        if (!Is_Party_In_Combat()) {
            End_Combat();
        }

        On_Update();
    }

    void Player_t::On_Register()
    {
        Register_For_Crosshair_Change();
        Register_Control("Sneak");
        Register_Action(CODES::ACTION::DRAW_END);
    }

    void Player_t::On_Update()
    {
        struct Lock_t : public Callback_t<Player_t*> {
            void operator()(Player_t* self)
            {
                self->On_Update_Impl();

                struct VCallback : public Virtual_Callback_t {
                    Player_t* player;
                    VCallback(Player_t* player) :
                        player(player)
                    {
                    }
                    void operator()(Variable_t* result)
                    {
                        player->On_Update();
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback(self);
                Modules::Funcs_t::Self()->Wait_Out_Of_Menu(UPDATE_INTERVAL, &vcallback);

                self->Unlock();
            }
        };
        Lock(new Lock_t());
    }

    void Player_t::On_Update_Impl()
    {
        static auto Update_Members = [&]()
        {
            if (!Is_Party_In_Combat()) {
                Members_t* members = Members_t::Self();
                Vector_t<Member_t*> loaded_members = members->Loaded();
                for (size_t idx = 0, count = loaded_members.size(); idx < count; idx += 1) {
                    loaded_members[idx]->Enforce();
                }
            }
        };

        static auto Update_Cell = [&]()
        {
            Actor_t* player_actor = Consts::Player_Actor();
            Reference_t* cell_marker = Consts::Cell_Marker();
            doticu_npcp::Cell_t* new_cell = player_actor->parentCell;
            doticu_npcp::Cell_t* old_cell = cell_marker->parentCell;
            if (new_cell != old_cell) {
                Object_Ref::Move_To_Orbit(cell_marker, player_actor, 0.0f, 180.0f);
                Party::Player_t::Self()->On_Cell_Change(new_cell, old_cell);
                Party::Movee_t::Self()->On_Cell_Change(new_cell, old_cell);
            }
        };

        Update_Members();
        Update_Cell();
    }

    void Player_t::On_Change_Crosshair(Reference_t* ref)
    {
        if (ref && ref->formType == kFormType_Character) {
            Actor_t* actor = static_cast<Actor_t*>(ref);
            if (!actor->IsInCombat()) {
                Member_t* member = Members_t::Self()->From_Actor(actor);
                if (member) {
                    member->Enforce();
                }
            }
        }
    }

    void Player_t::On_Cell_Change(Cell_t* new_cell, Cell_t* old_cell)
    {
        Followers_t::Self()->Catch_Up(new_cell, old_cell);
    }

    void Player_t::On_Control_Down(String_t control)
    {
        if (String2::Is_Same_Caseless(control, "Sneak")) {
            Followers_t* followers = Followers_t::Self();
            if (Is_Sneaking() && Is_Party_In_Combat()) {
                followers->Retreat();
            } else {
                followers->Unretreat();
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

        METHOD("On_Register", 0, void, On_Register);
        METHOD("OnCrosshairRefChange", 1, void, On_Change_Crosshair, Reference_t*);
        METHOD("OnControlDown", 1, void, On_Control_Down, String_t);
        METHOD("OnActorAction", 4, void, On_Actor_Action, Int_t, Actor_t*, Form_t*, Int_t);
        
        #undef METHOD
    }

}}}
