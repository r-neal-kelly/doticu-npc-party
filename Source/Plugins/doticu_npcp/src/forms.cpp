/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "forms.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Forms {



}}

namespace doticu_npcp { namespace Forms { namespace Exports {

    VMResultArray<TESForm *> Slice(StaticFunctionTag *, VMArray<TESForm *> arr, SInt32 idx_from, SInt32 idx_to_ex) {
        return Papyrus::Slice_Array<TESForm *>(arr, idx_from, idx_to_ex);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<TESForm *>, VMArray<TESForm *>, SInt32, SInt32>(
                "Forms_Slice",
                "doticu_npcp",
                Slice,
                registry)
        );

        return true;
    }

}}}
