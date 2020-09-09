/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Follower_t;

    class Horse_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable();
        Variable_t* Follower_Variable();
        Variable_t* Name_Variable();

        Actor_t* Actor();
        Follower_t* Follower();
        Cell_t* Cell();
        String_t Base_Name();
        String_t Reference_Name();
        String_t Name();

        Bool_t Is_Ready();
        Bool_t Is_Alive();
        Bool_t Is_Dead();

        void Fill(Actor_t* actor, Follower_t* follower, Callback_t<Int_t, Horse_t*>** callback);
        void Unfill(Callback_t<Int_t, Follower_t*>** callback);
        void Create(Actor_t* actor, Follower_t* follower);
        void Destroy(Callback_t<>** callback);

        Int_t Groom();
        void Enforce_Groom(Actor_t* actor);
        Int_t Ungroom();
        void Enforce_Non_Groom(Actor_t* actor, Callback_t<>* callback = nullptr);

        void Enforce();

        Int_t Rename(String_t new_name);
        void Enforce_Name(Actor_t* actor, String_t name);

        void On_Activate(Reference_t* activator);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
