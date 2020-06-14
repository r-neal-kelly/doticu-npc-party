/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Package {

    void Decompile(TESPackage *package, TESObjectREFR *target);

}}

namespace doticu_npcp { namespace Package { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
