/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Alias {

    Actor *Get_Actor(BGSBaseAlias *ptr_alias);
    SInt32 Get_Style(BGSBaseAlias *ptr_alias);
    SInt32 Get_Vitality(BGSBaseAlias *ptr_alias);
    SInt32 Get_Outfit2(BGSBaseAlias *ptr_alias);
    SInt32 Get_Rating(BGSBaseAlias *ptr_alias);
    bool Is_Created(BGSBaseAlias *ptr_alias);
    bool Is_Original(BGSBaseAlias *ptr_alias);
    bool Is_Clone(BGSBaseAlias *ptr_alias);
    bool Is_Follower(BGSBaseAlias *ptr_alias);
    bool Is_Settler(BGSBaseAlias *ptr_alias);
    bool Is_Immobile(BGSBaseAlias *ptr_alias);
    bool Is_Thrall(BGSBaseAlias *ptr_alias);
    bool Is_Paralyzed(BGSBaseAlias *ptr_alias);
    bool Is_Mannequin(BGSBaseAlias *ptr_alias);
    bool Is_Reanimated(BGSBaseAlias *ptr_alias);

}}
