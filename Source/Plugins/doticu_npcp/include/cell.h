/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace doticu_npcp { namespace Cell {

    bool Is_Interior(TESObjectCELL *cell);

}}

namespace doticu_npcp { namespace Cell { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
