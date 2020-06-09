/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "forms.h"

namespace doticu_npcp { namespace Forms { namespace Exports {

    VMResultArray<TESForm *> Slice(StaticFunctionTag *, VMArray<TESForm *> arr, UInt32 idx_from, UInt32 idx_to_ex) {
        return Papyrus::Array_Slice<TESForm *>(&arr, idx_from, idx_to_ex, NULL);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<TESForm *>, VMArray<TESForm *>, UInt32, UInt32>(
                "Forms_Slice",
                "doticu_npcp",
                Slice,
                registry)
        );

        _MESSAGE("Added Forms functions.");

        return true;
    }

}}}
