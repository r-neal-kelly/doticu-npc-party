/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Movee_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Movee_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable();

        Actor_t* Actor();

        Int_t Start(Actor_t* actor);
        Int_t Stop();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
