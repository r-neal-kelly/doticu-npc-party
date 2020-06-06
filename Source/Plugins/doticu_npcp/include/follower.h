/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "types.h"

namespace doticu_npcp { namespace Follower {

    Actor *Get_Actor(Follower_t *follower);
    Member_t *Get_Member(Follower_t *follower);

    bool Is_Created(Follower_t *follower);
    bool Is_Alive(Follower_t *follower);
    bool Is_Dead(Follower_t *follower);
    bool Is_Mobile(Follower_t *follower);
    bool Is_Immobile(Follower_t *follower);
    bool Is_Settler(Follower_t *follower);
    bool Isnt_Settler(Follower_t *follower);
    bool Is_Sneak(Follower_t *follower);
    bool Isnt_Sneak(Follower_t *follower);
    bool Is_Saddler(Follower_t *follower);
    bool Isnt_Saddler(Follower_t *follower);
    bool Is_Retreater(Follower_t *follower);
    bool Isnt_Retreater(Follower_t *follower);

    void Summon(Follower_t *follower, float distance = 120, float angle_degree = 0);

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
