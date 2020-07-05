/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party.h"

namespace doticu_npcp { namespace Party { namespace Members {

    constexpr UInt64 MAX = 1024;
    constexpr UInt64 BEGIN = 0;
    constexpr UInt64 END = BEGIN + MAX;

    String_t Class_Name();
    Class_Info_t* Class_Info();
    Members_t* Self();
    Object_t* Object();

    Range_t<UInt64> Indices(Members_t* self);
    Range_t<Alias_t**> Aliases(Members_t* self);
    Range_t<Member_t**> Members(Members_t* self);

    Member_t* From_Actor(Members_t* self, Actor_t* actor);

}}}

namespace doticu_npcp { namespace Party { namespace Members { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}











































#include "types.h"

namespace doticu_npcp { namespace Members {

    void Enforce_Loaded(Members_t *members);

    VMResultArray<Member_t *> Get_Loaded(Members_t *members);

}}

namespace doticu_npcp { namespace Members { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
