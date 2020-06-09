/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "types.h"

namespace doticu_npcp { namespace Member {

    Actor *Get_Actor(Member_t *member);
    TESObjectREFR *Get_Pack(Member_t *member);
    SInt32 Get_Style(Member_t *member);
    SInt32 Get_Vitality(Member_t *member);
    SInt32 Get_Outfit2(Member_t *member);
    SInt32 Get_Rating(Member_t *member);

    bool Is_Created(Member_t *member);
    bool Is_Original(Member_t *member);
    bool Is_Clone(Member_t *member);
    bool Is_Follower(Member_t *member);
    bool Is_Mobile(Member_t *member);
    bool Is_Immobile(Member_t *member);
    bool Is_Settler(Member_t *member);
    bool Isnt_Settler(Member_t *member);
    bool Is_Thrall(Member_t *member);
    bool Isnt_Thrall(Member_t *member);
    bool Is_Paralyzed(Member_t *member);
    bool Isnt_Paralyzed(Member_t *member);
    bool Is_Mannequin(Member_t *member);
    bool Isnt_Mannequin(Member_t *member);
    bool Is_Reanimated(Member_t *member);
    bool Isnt_Reanimated(Member_t *member);

    void On_Hit(Member_t *member);

}}

namespace doticu_npcp { namespace Member { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
