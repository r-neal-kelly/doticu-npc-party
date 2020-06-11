/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Cell {

    bool Is_Interior(TESObjectCELL *cell);
    bool Is_Exterior(TESObjectCELL *cell);

}}

namespace doticu_npcp { namespace Cell { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
