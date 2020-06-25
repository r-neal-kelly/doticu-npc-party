/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Follower {

    Actor *Get_Actor(Follower_t *follower);
    Member_t *Get_Member(Follower_t *follower);
    Horse_t *Get_Horse(Follower_t *follower);
    Actor *Horse_Actor(Follower_t *follower);

    bool Is_Created(Follower_t *follower);
    bool Is_Alive(Follower_t *follower);
    bool Is_Dead(Follower_t *follower);
    bool Is_Mobile(Follower_t *follower);
    bool Is_Immobile(Follower_t *follower);
    bool Is_Settler(Follower_t *follower);
    bool Isnt_Settler(Follower_t *follower);
    bool Is_Paralyzed(Follower_t *follower);
    bool Isnt_Paralyzed(Follower_t *follower);
    bool Is_Mannequin(Follower_t *follower);
    bool Isnt_Mannequin(Follower_t *follower);
    bool Is_Sneak(Follower_t *follower);
    bool Isnt_Sneak(Follower_t *follower);
    bool Is_Saddler(Follower_t *follower);
    bool Isnt_Saddler(Follower_t *follower);
    bool Is_Retreater(Follower_t *follower);
    bool Isnt_Retreater(Follower_t *follower);
    bool Exists(Follower_t *follower);
    bool Is_Near_Player(Follower_t *follower, float distance = 4096.0f);
    bool Isnt_Near_Player(Follower_t *follower, float distance = 4096.0f);
    bool Is_In_Interior_Cell(Follower_t *follower);
    bool Is_In_Exterior_Cell(Follower_t *follower);

    void Summon(Follower_t *follower, float distance = 140, float angle_degree = 0);
    void Summon_Ahead(Follower_t* follower, float distance = 140);
    void Summon_Behind(Follower_t *follower, float distance = 140);
    void Catch_Up(Follower_t *follower);
    void Level(Follower_t *follower);
    void Unlevel(Follower_t *follower);
    void Saddle(Follower_t *follower);

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
