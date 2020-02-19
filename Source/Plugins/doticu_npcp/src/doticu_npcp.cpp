/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_npcp.h"

namespace doticu_npcp {

    SInt32 Add_Ints(StaticFunctionTag *, SInt32 x, SInt32 y) {
        return x + y;
    }

    bool Register_Functions(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, SInt32, SInt32, SInt32>("Add_Ints", "doticu_npcp", doticu_npcp::Add_Ints, registry)
        );

        return true;
    }

}
