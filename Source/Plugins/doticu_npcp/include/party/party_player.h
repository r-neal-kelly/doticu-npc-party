/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Player_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Player_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

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

        void Begin_Combat();
        void Try_To_End_Combat();
        void End_Combat();

        void On_Init_Mod();
        void On_Load_Mod();
        void On_Cell_Change(Form_t* new_cell, Form_t* old_cell);
        void On_Control_Down(String_t control);
        void On_Actor_Action(Int_t action_code, Actor_t* actor, Form_t* tool, Int_t tool_slot);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
