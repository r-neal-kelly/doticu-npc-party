/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Actor_Base2 {

    BGSColorForm *Get_Hair_Color(TESNPC *actor_base);
    TESObjectARMO *Get_Skin(TESNPC *actor_base);
    bool Has_Same_Head(TESNPC *actor_base_a, TESNPC *actor_base_b);

    float Get_Max_Actor_Value(TESNPC *actor_base, BSFixedString name);

}}

namespace doticu_npcp { namespace Actor_Base2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
