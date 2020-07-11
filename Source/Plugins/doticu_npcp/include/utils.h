/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

#define M \
    do {

#define W \
    } while (0)

#define PRAGMA_PUSH_WARNING_DISABLE(ID_)    \
M                                           \
    __pragma(warning(push));                \
    __pragma(warning(disable: ID_));        \
W

#define PRAGMA_POP_WARNING()    \
M                               \
    __pragma(warning(pop));     \
W

#define NPCP_ASSERT(IS_TRUE)                                        \
M                                                                   \
    if (!(IS_TRUE)) {                                               \
        _MESSAGE("Asserted. Exiting Skyrim. Failed: %s", #IS_TRUE); \
        _AssertionFailed(__FILE__, __LINE__, #IS_TRUE);             \
    }                                                               \
W

#define DOTICU_NPCP_PI 3.141592741f

// set manually upon each release
#define DOTICU_NPCP_VERSION_MAJOR 0
#define DOTICU_NPCP_VERSION_MINOR 9
#define DOTICU_NPCP_VERSION_PATCH 2

#define DOTICU_NPCP_PRINT_PREFIX "doticu_npcp: "

#define ADD_CLASS_METHOD(STR_CLASS_, BASE_, STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...) \
M                                                                                       \
    registry->RegisterFunction(                                                         \
        new NativeFunction##ARG_NUM_ <BASE_, RETURN_, __VA_ARGS__>(                     \
            STR_FUNC_, STR_CLASS_, METHOD_, registry                                    \
        )                                                                               \
    );                                                                                  \
W

namespace doticu_npcp { namespace Utils {

    void Print(const char *str);

    template <typename Bits, typename Index>
    inline Bits Bit_On(Bits bits, Index idx)
    {
        return bits | (1llu << idx);
    }

    template <typename Bits, typename Index>
    inline Bits Bit_Off(Bits bits, Index idx)
    {
        return bits & ~(1llu << idx);
    }

    template <typename Bits, typename Index>
    inline bool Is_Bit_On(Bits bits, Index idx)
    {
        return 1llu & (bits >> idx);
    }

    template <typename Bits, typename Index>
    inline bool Is_Bit_Off(Bits bits, Index idx)
    {
        return !(1llu & (bits >> idx));
    }

    template <typename Bits, typename Index>
    inline Bits Toggle_Bit(Bits bits, Index idx)
    {
        return bits ^ (1llu << idx);
    }

    template <typename Bits, typename Index>
    inline Bits Clear_Bits(Bits bits, Index idx)
    {
        return 0;
    }

}}

namespace doticu_npcp { namespace Utils { namespace Exports {

    VMResultArray<SInt32> Get_Plugin_Version(StaticFunctionTag *);
    void Print(StaticFunctionTag *, BSFixedString str);
    void Log(StaticFunctionTag *, BSFixedString str);

    bool Register(VMClassRegistry *registry);

}}}
