/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party.h"
#include "followers.h"

namespace doticu_npcp { namespace Party { namespace Horses {

    constexpr UInt64 MAX = 16;
    constexpr UInt64 BEGIN = Followers::END;
    constexpr UInt64 END = BEGIN + MAX;

    Range_t<UInt64> Indices(Horses_t* self);
    Range_t<Alias_t**> Aliases(Horses_t* self);
    Range_t<Horse_t**> Horses(Horses_t* self);

    Horse_t* From_Actor(Horses_t* self, Actor_t* actor);

}}}
