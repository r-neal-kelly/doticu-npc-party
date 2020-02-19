/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusVM.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace doticu_npcp {

    // we can only use certain types, SInt32 is one of them.
    SInt32 Add_Ints(StaticFunctionTag *, SInt32 x, SInt32 y);

    bool Register_Functions(VMClassRegistry *registry);

}
