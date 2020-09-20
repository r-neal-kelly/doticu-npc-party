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

    void CRC32_By_Size(UInt32& result, void* value, UInt32 size)
    {
        static auto crc32_by_size = reinterpret_cast
            <void (*)(UInt32&, void*, UInt32)>
            (RelocationManager::s_baseAddr + Offsets::CRC32::BY_SIZE);
        crc32_by_size(result, value, size);
    }

    void CRC32_By_32(UInt32& result, UInt32 value)
    {
        static auto crc32_by_32 = reinterpret_cast
            <void (*)(UInt32&, UInt32)>
            (RelocationManager::s_baseAddr + Offsets::CRC32::BY_32);
        crc32_by_32(result, value);
    }

    void CRC32_By_64(UInt32& result, UInt64 value)
    {
        static auto crc32_by_64 = reinterpret_cast
            <void (*)(UInt32&, UInt64)>
            (RelocationManager::s_baseAddr + Offsets::CRC32::BY_64);
        crc32_by_64(result, value);
    }

}}

namespace doticu_npcp { namespace Utils { namespace Exports {

    bool Register(VMClassRegistry *registry)
    {
        return true;
    }

}}}
