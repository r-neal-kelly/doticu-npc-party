/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "common/IDebugLog.h"

#include "skse64/PapyrusNativeFunctions.h"

#define M \
    do {

#define W \
    } while (0)

#define Assert(IS_TRUE)                                             \
M                                                                   \
    if (!(IS_TRUE)) {                                               \
        _MESSAGE("Asserted. Exiting Skyrim. Failed: %s", #IS_TRUE); \
        _AssertionFailed(__FILE__, __LINE__, #IS_TRUE);             \
    }                                                               \
W

#define DOTICU_NPCP_PI 3.141592741f

#define Bit_Set(BITS, BIT_IDX) \
    ( (BITS) |=  ( (1llu) << (BIT_IDX) ) )

#define Bit_Unset(BITS, BIT_IDX) \
    ( (BITS) &= ~( (1llu) << (BIT_IDX) ) )

#define Bit_Is_Set(BITS, BIT_IDX) \
    ( (1llu) &   ( (BITS) >> (BIT_IDX) ) )

#define Bit_Toggle(BITS, BIT_IDX) \
    ( (BITS) ^=  ( (1llu) << (BIT_IDX) ) )

#define Bit_Clear(BITS)\
    ( (BITS) = 0 )

// set manually upon each release
#define DOTICU_NPCP_VERSION_MAJOR 0
#define DOTICU_NPCP_VERSION_MINOR 9
#define DOTICU_NPCP_VERSION_PATCH 1

#define DOTICU_NPCP_PRINT_PREFIX "doticu_npcp: "

namespace doticu_npcp {

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
    typedef int8_t s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

}

namespace doticu_npcp { namespace Utils {

    void Print(const char *str);

}}

namespace doticu_npcp { namespace Utils { namespace Exports {

    VMResultArray<SInt32> Get_Plugin_Version(StaticFunctionTag *);
    void Print(StaticFunctionTag *, BSFixedString str);
    void Log(StaticFunctionTag *, BSFixedString str);

    bool Register(VMClassRegistry *registry);

}}}
