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

namespace doticu_npcp { namespace Utils { namespace Exports {

    void Print(StaticFunctionTag *, BSFixedString str);
    void Log(StaticFunctionTag *, BSFixedString str);

    bool Register(VMClassRegistry *registry);

}}}
