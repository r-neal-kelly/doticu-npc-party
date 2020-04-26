/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_npcp.h"

namespace doticu_npcp {

    void Print(StaticFunctionTag *, BSFixedString str) {
        Console_Print(str.data);
    }

}
