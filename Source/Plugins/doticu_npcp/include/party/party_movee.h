/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Movee_t : public Alias_t {
    public:
        static constexpr Float_t MIN_DISTANCE = 25.0f;
        static constexpr Float_t MAX_DISTANCE = 400.0f;
        static constexpr Float_t DEF_DISTANCE = 150.0f;
        static constexpr Float_t DISTANCE_INTERVAL = 20.0f;

        static constexpr Float_t MIN_ROTATION = 0.0f;
        static constexpr Float_t MAX_ROTATION = 360.f;
        static constexpr Float_t DEF_ROTATION = 0.0f;
        static constexpr Float_t ROTATION_INTERVAL = 12.0f;

        static constexpr Float_t UPDATE_INTERVAL = 0.05f;
        static constexpr Float_t SPEED = 600.0f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Movee_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable(); // Actor_t*

        Variable_t* Is_Created_Variable(); // Bool_t
        Variable_t* Is_Locked_Variable(); // Bool_t
        Variable_t* Is_Airborne_Variable(); // Bool_t
        Variable_t* Do_Distance_Farther_Variable(); // Bool_t
        Variable_t* Do_Distance_Nearer_Variable(); // Bool_t
        Variable_t* Do_Rotate_Right_Variable(); // Bool_t
        Variable_t* Do_Rotate_Left_Variable(); // Bool_t

        Variable_t* Distance_Variable(); // Float_t
        Variable_t* Rotation_Variable(); // Float_t

        Actor_t* Actor();

        Bool_t Is_Created();
        Bool_t Is_Locked();
        Bool_t Is_Airborne();
        Bool_t Do_Distance_Farther();
        Bool_t Do_Distance_Nearer();
        Bool_t Do_Rotate_Right();
        Bool_t Do_Rotate_Left();

        Float_t Distance();
        Float_t Rotation();

        void Actor(Actor_t* actor);

        void Is_Created(Bool_t value);
        void Is_Locked(Bool_t value);
        void Is_Airborne(Bool_t value);
        void Do_Distance_Farther(Bool_t value);
        void Do_Distance_Nearer(Bool_t value);
        void Do_Rotate_Right(Bool_t value);
        void Do_Rotate_Left(Bool_t value);

        void Distance(Float_t distance);
        void Rotation(Float_t rotation);

        void Lock(Callback_t<Movee_t*>* on_lock, Float_t interval = 0.2f, Float_t limit = 10.0f);
        void Unlock();

        Int_t Start(Actor_t* actor);
        void Start_Impl(Actor_t* actor, Callback_t<>* user_callback);
        Int_t Stop();
        void Stop_Impl(Callback_t<>* user_callback);

        void Register();
        void Unregister();
        void Update();
        void Update_Impl(Callback_t<>* user_callback);
        void Move();
        void Reload();

        void On_Load_Mod();
        void On_Cell_Change(Cell_t* new_cell, Cell_t* old_cell);
        void On_Key_Down(Int_t key_code);
        void On_Key_Up(Int_t key_code, Float_t time_held);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
