/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Spell {

    Bool_t Can_Damage_Health(Spell_t* spell);

}}

namespace doticu_npcp { namespace Spell { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
