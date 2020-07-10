/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest);

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
