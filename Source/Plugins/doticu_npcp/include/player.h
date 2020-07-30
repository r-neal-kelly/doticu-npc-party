/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Player {

    Actor_t* Actor();
    PlayerCharacter* Player_Character();
    bool Is_Party_In_Combat(Player_t *player);
    bool Is_In_Interior_Cell();
    bool Is_In_Exterior_Cell();
    bool Is_On_Mount();

}}

namespace doticu_npcp { namespace Player { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
