/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Player_t : public Alias_t {
    public:
        static constexpr Float_t UPDATE_INTERVAL = 5.0f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Player_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Is_Locked_Variable();
        Variable_t* Is_In_Combat_Variable();

        Actor_t* Actor();
        Player_Character_t* Player_Character();
        Location_t* Location();

        Bool_t Is_Party_In_Combat();
        Bool_t Is_In_Interior_Cell();
        Bool_t Is_In_Exterior_Cell();
        Bool_t Is_On_Mount();
        Bool_t Is_Vampire();
        Bool_t Is_Sneaking();

        void Lock(Callback_t<Player_t*>* on_lock, Float_t interval = 0.2f, Float_t limit = 10.0f);
        void Unlock();
        void Begin_Combat();
        void Try_To_End_Combat();
        void End_Combat();

        void On_Init_Mod();
        void On_Load_Mod();
        void On_Register();
        void On_Update();
        void On_Update_Impl();
        void On_Change_Crosshair(Reference_t* ref);
        void On_Cell_Change(Cell_t* new_cell, Cell_t* old_cell);
        void On_Control_Down(String_t control);
        void On_Actor_Action(Int_t action_code, Actor_t* actor, Form_t* tool, Int_t tool_slot);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
