/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameForms.h"

#include "utils.h"
#include "form.h"
#include "object_ref.h"

namespace doticu_npcp { namespace Utils { namespace Exports {

    void Print(StaticFunctionTag *, BSFixedString str) {
        Console_Print(str.data);
    }

    void Log(StaticFunctionTag *, BSFixedString str) {
        _MESSAGE(str.data);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, BSFixedString>(
                "Print",
                "doticu_npcp",
                Print,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, BSFixedString>(
                "Log",
                "doticu_npcp",
                Log,
                registry)
        );

        return true;
    }

}}}
