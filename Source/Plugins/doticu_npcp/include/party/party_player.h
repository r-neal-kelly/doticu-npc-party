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

        Variable_t* Is_Locked_Variable(); // Bool_t
        Variable_t* Is_In_Combat_Variable(); // Bool_t
        Variable_t* Menu_Actor_Variable(); // Actor_t

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
        void Begin_Combat_Impl();

        void Add_Perk(Perk_t* perk);
        void Add_Perk_Impl(Perk_t* perk);
        void Remove_Perk(Perk_t* perk);
        void Remove_Perk_Impl(Perk_t* perk);

        void Drink_Blood_Of(Actor_t* victim, Callback_t<Player_t*, Actor_t*>* user_callback = nullptr);

        void Open_Global_Dialogue_Menu();
        void Close_Global_Dialogue_Menu();

        void On_Init_Mod();
        void On_Load_Mod();
        void On_Register();
        void On_Update();
        void On_Update_Impl();
        void On_Control_Down(String_t control);
        void On_Control_Down_Impl(String_t control);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
