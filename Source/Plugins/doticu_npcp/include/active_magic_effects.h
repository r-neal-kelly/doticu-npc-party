/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Active_Magic_Effects {

    void On_Effect_Start(Active_Magic_Effect_t* active_magic_effect, Actor_t* target, Actor_t* caster);
    void On_Effect_Finish(Active_Magic_Effect_t* active_magic_effect, Actor_t* target, Actor_t* caster);

}}}

namespace doticu_npcp { namespace Papyrus { namespace Active_Magic_Effects { namespace Exports {

    Bool_t Register(VMClassRegistry *registry);

}}}}
