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
    Variable_t* Player_t::Menu_Actor_Variable() { DEFINE_VARIABLE("p_menu_actor"); }

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
        struct Lock_t : public Callback_t<Player_t*> {
            void operator()(Player_t* self)
            {
                self->Begin_Combat_Impl();
                self->Unlock();
            }
        };
        Lock(new Lock_t());
    }

    void Player_t::Begin_Combat_Impl()
    {
        if (Is_In_Combat_Variable()->Bool() == false) {
            Is_In_Combat_Variable()->Bool(true);

            Followers_t* followers = Followers_t::Self();
            followers->Catch_Up();
            if (Is_Sneaking()) {
                followers->Retreat();
            }
        }
    }

    void Player_t::Add_Perk(Perk_t* perk)
    {
        struct Lock_t : public Callback_t<Player_t*> {
            Perk_t* perk;
            Lock_t(Perk_t* perk) :
                perk(perk)
            {
            }
            void operator()(Player_t* self)
            {
                self->Add_Perk_Impl(perk);
                self->Unlock();
            }
        };
        Lock(new Lock_t(perk));
    }

    void Player_t::Add_Perk_Impl(Perk_t* perk)
    {
        Actor()->AddPerk(perk, 0);
    }

    void Player_t::Remove_Perk(Perk_t* perk)
    {
        struct Lock_t : public Callback_t<Player_t*> {
            Perk_t* perk;
            Lock_t(Perk_t* perk) :
                perk(perk)
            {
            }
            void operator()(Player_t* self)
            {
                self->Remove_Perk_Impl(perk);
                self->Unlock();
            }
        };
        Lock(new Lock_t(perk));
    }

    void Player_t::Remove_Perk_Impl(Perk_t* perk)
    {
        Actor()->RemovePerk(perk);
    }

    void Player_t::Drink_Blood_Of(Actor_t* victim, Callback_t<Player_t*, Actor_t*>* user_callback)
    {
        using UCallback_t = Callback_t<Player_t*, Actor_t*>;

        if (victim) {
            struct VArguments : public Virtual_Arguments_t {
                Reference_t* victim;
                VArguments(Reference_t* victim) :
                    victim(victim)
                {
                }
                Bool_t operator()(Arguments_t* args)
                {
                    args->Resize(2);
                    args->At(0)->Pack(victim);
                    args->At(1)->None(Class_Info_t::Fetch(Actor_t::kTypeID, true));
                    return true;
                }
            } varguments(victim);
            struct VCallback : public Virtual_Callback_t {
                Player_t* self;
                Actor_t* victim;
                UCallback_t* user_callback;
                VCallback(Player_t* self, Actor_t* victim, UCallback_t* user_callback) :
                    self(self), victim(victim), user_callback(user_callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    if (user_callback) {
                        user_callback->operator()(self, victim);
                        delete user_callback;
                    }
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this, victim, user_callback);
            Virtual_Machine_t::Self()->Call_Method(
                Consts::Vampire_Feed_Perk(),
                "PRKF_VampireFeedBeds_000CF02C",
                "Fragment_15",
                &varguments,
                &vcallback
            );
        } else {
            if (user_callback) {
                user_callback->operator()(this, nullptr);
                delete user_callback;
            }
        }
    }

    void Player_t::Open_Global_Dialogue_Menu()
    {
        if (Menu_Actor_Variable()->Has_Object()) {
            Close_Global_Dialogue_Menu();
        }

        Actor_t* player_actor = Actor();
        Actor_t* menu_actor = static_cast<Actor_t*>
            (Object_Ref::Place_At_Me(player_actor, Consts::Menu_Actor_Base(), 1, true, false));
        Actor2::Move_To_Orbit(menu_actor, player_actor, 120.0f, 0.0f);
        //Object_Ref::Enable(menu_actor);

        Menu_Actor_Variable()->Pack(menu_actor);
    }

    void Player_t::Close_Global_Dialogue_Menu()
    {
        Actor_t* menu_actor = Menu_Actor_Variable()->Actor();
        if (menu_actor) {
            Object_Ref::Delete_Safe(menu_actor);
            Menu_Actor_Variable()->None(Class_Info_t::Fetch(Actor_t::kTypeID, true));
        }
    }

    void Player_t::On_Init_Mod()
    {
        On_Update();
    }

    void Player_t::On_Load_Mod()
    {
        On_Register();
        On_Update();
    }

    void Player_t::On_Register()
    {
        Register_Control("Sneak");
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
        static auto Update_Player = [&]()->void
        {
            Actor_t* actor = Actor();
            actor->AddPerk(Consts::Kiss_Thrall_Perk(), 0);
            actor->AddPerk(Consts::Resurrect_Perk(), 0);
            actor->AddPerk(Consts::Reanimate_Perk(), 0);
            actor->AddPerk(Consts::Unparalyze_Perk(), 0);
        };

        static auto End_Combat = [&]()->Bool_t
        {
            if (Is_In_Combat_Variable()->Bool() == true) {
                Is_In_Combat_Variable()->Bool(false);

                if (!Is_Sneaking()) {
                    Followers_t::Self()->Unretreat();
                }

                Members_t::Self()->Enforce_Loaded(Modules::Vars_t::Self()->Do_Auto_Resurrect_Followers());

                return true;
            } else {
                return false;
            }
        };

        static auto Update_Members = [&]()->void
        {
            Members_t* members = Members_t::Self();
            Vector_t<Member_t*> loaded_members = members->Loaded();
            for (size_t idx = 0, count = loaded_members.size(); idx < count; idx += 1) {
                loaded_members[idx]->Enforce();
            }
        };

        static auto Update_Cell = [&]()->void
        {
            Actor_t* player_actor = Consts::Player_Actor();
            Reference_t* cell_marker = Consts::Cell_Marker();
            doticu_npcp::Cell_t* new_cell = player_actor->parentCell;
            doticu_npcp::Cell_t* old_cell = cell_marker->parentCell;
            if (new_cell != old_cell) {
                Object_Ref::Move_To_Orbit(cell_marker, player_actor, 0.0f, 180.0f);
                Followers_t::Self()->Catch_Up(new_cell, old_cell);
                Party::Movee_t::Self()->On_Cell_Change(new_cell, old_cell);
            }
        };

        Update_Player();
        if (!Is_Party_In_Combat()) {
            if (!End_Combat()) {
                Update_Members();
            }
        }
        Update_Cell();
    }

    void Player_t::On_Control_Down(String_t control)
    {
        struct Lock_t : public Callback_t<Player_t*> {
            String_t control;
            Lock_t(String_t control) :
                control(control)
            {
            }
            void operator()(Player_t* self)
            {
                self->On_Control_Down_Impl(control);
                self->Unlock();
            }
        };
        Lock(new Lock_t(control));
    }

    void Player_t::On_Control_Down_Impl(String_t control)
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

    void Player_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Player_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("OnControlDown", 1, void, On_Control_Down, String_t);
        
        #undef METHOD
    }

}}}
