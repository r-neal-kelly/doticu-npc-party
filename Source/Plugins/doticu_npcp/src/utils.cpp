/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameForms.h"

#include "utils.h"
#include "string2.h"
#include "form.h"
#include "object_ref.h"
#include "quest.h"

namespace doticu_npcp { namespace Utils {

    void Print(const char *str) {
        Console_Print(str);
    }

}}

namespace doticu_npcp { namespace Utils { namespace Exports {

    VMResultArray<SInt32> Get_Plugin_Version(StaticFunctionTag *) {
        VMResultArray<SInt32> vec_versions;
        vec_versions.reserve(3);

        vec_versions.push_back(DOTICU_NPCP_VERSION_MAJOR);
        vec_versions.push_back(DOTICU_NPCP_VERSION_MINOR);
        vec_versions.push_back(DOTICU_NPCP_VERSION_PATCH);

        return vec_versions;
    }

    void Print(StaticFunctionTag *, BSFixedString str) {
        Console_Print(str.data);
    }

    void Log(StaticFunctionTag *, BSFixedString str) {
        _MESSAGE(str.data);
    }

    void Log_Cell(StaticFunctionTag *, TESObjectCELL *cell) {
        if (!cell) {
            return;
        }

        _MESSAGE("Cell: %s", cell->fullName.name.data);
        _MESSAGE("    Data unk030:");
        _MESSAGE("        UInt32 unk0: 0x%X", cell->unk030.unk0);
        _MESSAGE("        UInt32 unk4: 0x%X", cell->unk030.unk4);
        _MESSAGE("    Data unk038:");
        _MESSAGE("        UInt32 unk0: 0x%X", cell->unk030.unk0);
        _MESSAGE("        UInt32 unk4: 0x%X", cell->unk030.unk4);
        _MESSAGE("    UInt16 unk040: 0x%X, (maybe) is interior: %i", cell->unk040, (cell->unk040 & 1) == 1);
        _MESSAGE("    UInt16 unk042: 0x%X", cell->unk042);
        _MESSAGE("    UInt8 unk044: 0x%X", cell->unk044);
        _MESSAGE("    UInt8 unk045: 0x%X", cell->unk045);
        _MESSAGE("    UInt8 unk046: 0x%X", cell->unk046);
        _MESSAGE("    UInt8 pad047: 0x%X", cell->pad047);
    }

    using Int_Vector_t = Papyrus::Int_Vector_t;

    Int_Vector_t New_Int_Array(Selfless_t*, Int_t size = 0, Int_t fill = 0)
    {
        Int_Vector_t vec;

        vec.reserve(size);
        for (Int_t idx = 0; idx < size; idx += 1) {
            vec.push_back(fill);
        }

        return vec;
    }

    bool Register(VMClassRegistry *registry) {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("New_Int_Array", 2, Int_Vector_t, New_Int_Array, Int_t, Int_t);

        #undef ADD_GLOBAL

        registry->RegisterFunction(
            new NativeFunction0 <StaticFunctionTag, VMResultArray<SInt32>>(
                "Get_Plugin_Version",
                "doticu_npcp",
                Exports::Get_Plugin_Version,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, BSFixedString>(
                "Print",
                "doticu_npcp",
                Exports::Print,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, BSFixedString>(
                "Log",
                "doticu_npcp",
                Exports::Log,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, TESObjectCELL *>(
                "Log_Cell",
                "doticu_npcp",
                Exports::Log_Cell,
                registry)
        );

        return true;
    }

}}}
