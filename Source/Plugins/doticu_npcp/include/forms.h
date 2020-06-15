/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Forms {



}}

namespace doticu_npcp { namespace Forms { namespace Exports {

    VMResultArray<TESForm *> Slice(StaticFunctionTag *, VMArray<TESForm *> arr, SInt32 idx_from, SInt32 idx_to_ex);

    bool Register(VMClassRegistry *registry);

}}}
