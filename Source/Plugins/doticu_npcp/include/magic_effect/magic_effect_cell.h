/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Magic_Effect {

    class Cell_t : public Active_Magic_Effect_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        void On_Effect_Start(Actor_t* target, Actor_t* caster);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
