/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Actor_Base2 {

    BGSColorForm *Get_Hair_Color(TESNPC *actor_base);
    TESObjectARMO *Get_Skin(TESNPC *actor_base);
    TESNPC::Color* Get_Skin_Color(TESNPC* actor_base);
    bool Has_Same_Skin_Color(TESNPC* actor_base_a, TESNPC* actor_base_b);
    bool Has_Same_Head(TESNPC *actor_base_a, TESNPC *actor_base_b);

    Actor_Value_Owner_t* Actor_Value_Owner(Actor_Base_t* actor_base);
    float Get_Actor_Value(TESNPC *actor_base, const char *name);
    float Get_Base_Actor_Value(TESNPC *actor_base, const char *name);
    float Get_Max_Actor_Value(TESNPC *actor_base, const char *name);

    Bool_t Is_Ghost(Actor_Base_t* actor_base);

    tArray<Relationship_t*>* Relationships(Actor_Base_t* actor_base);
    Relationship_t::Rank_e Relationship_Rank(Actor_Base_t* actor_base, Actor_Base_t* with_other);
    //void Relationship_Rank(Actor_Base_t* actor_base, Actor_Base_t* with_other, Relationship_t::Rank_e rank);

    void Essentialize(Actor_Base_t* actor_base);
    void Protect(Actor_Base_t* actor_base);
}}

namespace doticu_npcp { namespace Actor_Base2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
