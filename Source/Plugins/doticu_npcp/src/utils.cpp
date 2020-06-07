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

    bool Register(VMClassRegistry *registry) {
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

        return true;
    }

}}}
