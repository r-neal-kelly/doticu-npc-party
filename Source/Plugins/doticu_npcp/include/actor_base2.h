/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_npcp { namespace Actor_Base2 {

    TESObjectARMO *Get_Skin(TESNPC *actor_base);
    TESNPC::Color* Get_Skin_Color(TESNPC* actor_base);
    Bool_t Has_Same_Hair_Color(Actor_Base_t* actor_base_a, Actor_Base_t* actor_base_b);
    bool Has_Same_Skin_Color(TESNPC* actor_base_a, TESNPC* actor_base_b);
    bool Has_Same_Head(TESNPC *actor_base_a, TESNPC *actor_base_b);

}}
