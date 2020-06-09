/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "types.h"

namespace doticu_npcp { namespace Player {

    bool Is_Party_In_Combat(Player_t *player);

}}

namespace doticu_npcp { namespace Player { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
