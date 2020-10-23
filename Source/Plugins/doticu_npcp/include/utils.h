/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <utility>

#include "offsets.h"
#include "types.h"

#define M \
    do {

#define W \
    } while (0)

#if 1

#define NPCP_ASSERT(IS_TRUE)                                        \
M                                                                   \
    if (!(IS_TRUE)) {                                               \
        _MESSAGE("Asserted. Exiting Skyrim. Failed: %s", #IS_TRUE); \
        _AssertionFailed(__FILE__, __LINE__, #IS_TRUE);             \
    }                                                               \
W

#else

#define NPCP_ASSERT(IGNORED_PARAM_)

#endif

#define DOTICU_NPCP_PI 3.141592741f

#define DOTICU_NPCP_PRINT_PREFIX "doticu_npcp: "

namespace doticu_npcp { namespace Utils {

    template <typename Num>
    inline Bool_t Is_Odd(Num num)
    {
        return num & static_cast<Num>(1);
    }

    template <typename Num>
    inline Bool_t Is_Even(Num num)
    {
        return !Is_Odd(num);
    }
    
    inline Float_t To_Degrees(Float_t radians)
    {
        return radians * (180.0f / DOTICU_NPCP_PI);
    }

    inline Float_t To_Radians(Float_t degrees)
    {
        return degrees * DOTICU_NPCP_PI / 180.0f;
    }

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

    void CRC32_By_Size(UInt32& result, void* value, UInt32 size);
    void CRC32_By_32(UInt32& result, UInt32 value);
    void CRC32_By_64(UInt32& result, UInt64 value);

    template <typename Value>
    inline UInt32 CRC32_By_Size(Value value)
    {
        UInt32 result = 0;
        CRC32_By_Size(result, &value, sizeof(value));
        return result;
    }

    inline UInt32 CRC32(UInt16 value)
    {
        UInt32 result = 0;
        CRC32_By_32(result, (UInt32)value);
        return result;
    }

    inline UInt32 CRC32(UInt64 value)
    {
        UInt32 result = 0;
        CRC32_By_64(result, value);
        return result;
    }

    inline UInt32 CRC32(void* value)
    {
        UInt32 result = 0;
        CRC32_By_64(result, (UInt64)value);
        return result;
    }

    inline std::vector<char> To_Binary(void* data, size_t bytes)
    {
        static const char* half_bytes[16] = {
            "0000", "0001", "0010", "0011",
            "0100", "0101", "0110", "0111",
            "1000", "1001", "1010", "1011",
            "1100", "1101", "1110", "1111"
        };

        size_t bits = bytes * 8;
        size_t spaces = bytes * 1 - 1;
        size_t null = 1;
        std::vector<char> chars;
        chars.reserve(bits + spaces + null);

        u8* it = static_cast<u8*>(data) + bytes;
        while (it != data) {
            it -= 1;
            u8 byte = *it;
            char* left = const_cast<char*>(half_bytes[(byte & 0xF0) >> 4]);
            char* right = const_cast<char*>(half_bytes[byte & 0x0F]);
            for (size_t idx = 0; idx < 4; idx += 1) {
                chars.push_back(left[idx]);
            }
            for (size_t idx = 0; idx < 4; idx += 1) {
                chars.push_back(right[idx]);
            }
            chars.push_back(' ');
        }
        chars.at(chars.size() - 1) = '\0';

        return chars;
    }

}}
