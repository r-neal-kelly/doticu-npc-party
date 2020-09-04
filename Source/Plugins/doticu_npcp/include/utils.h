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

#define PRAGMA_PUSH_WARNING_DISABLE(ID_)    \
M                                           \
    __pragma(warning(push));                \
    __pragma(warning(disable: ID_));        \
W

#define PRAGMA_POP_WARNING()    \
M                               \
    __pragma(warning(pop));     \
W

#if 1

#define NPCP_ASSERT(IS_TRUE)                                        \
M                                                                   \
    if (!(IS_TRUE)) {                                               \
        _MESSAGE("Asserted. Exiting Skyrim. Failed: %s", #IS_TRUE); \
        _AssertionFailed(__FILE__, __LINE__, #IS_TRUE);             \
    }                                                               \
W

#else

#define NPCP_ASSERT(IS_TRUE)                                        \
M                                                                   \
    if (!(IS_TRUE)) {                                               \
        _MESSAGE("Asserted. Exiting Skyrim. Failed: %s", #IS_TRUE); \
        _AssertionFailed(__FILE__, __LINE__, #IS_TRUE);             \
    } else {                                                        \
        _MESSAGE("Passed. %s, %s, %u",                              \
                 __FILE__, __func__, __LINE__);                     \
    }                                                               \
W

#endif

#define DOTICU_NPCP_PI 3.141592741f

#define DOTICU_NPCP_PRINT_PREFIX "doticu_npcp: "

#if 0

#define FORWARD_POINTER(METHOD_)                                                \
{                                                                               \
    _MESSAGE("in func: %s, file: %s, line: %u", __func__, __FILE__, __LINE__);  \
    auto result = self ? self->METHOD_ : nullptr;                               \
    _MESSAGE("out of func: %s", __func__);                                      \
    return result;                                                              \
}

#define FORWARD_BOOL(METHOD_)                                                   \
{                                                                               \
    _MESSAGE("in func: %s, file: %s, line: %u", __func__, __FILE__, __LINE__);  \
    auto result = self ? self->METHOD_ : false;                                 \
    _MESSAGE("out of func: %s", __func__);                                      \
    return result;                                                              \
}

#define FORWARD_INT(METHOD_)                                                    \
{                                                                               \
    _MESSAGE("in func: %s, file: %s, line: %u", __func__, __FILE__, __LINE__);  \
    auto result = self ? self->METHOD_ : 0;                                     \
    _MESSAGE("out of func: %s", __func__);                                      \
    return result;                                                              \
}

#define FORWARD_STRING(METHOD_)                                                 \
{                                                                               \
    _MESSAGE("in func: %s, file: %s, line: %u", __func__, __FILE__, __LINE__);  \
    auto result = self ? self->METHOD_ : "";                                    \
    _MESSAGE("out of func: %s", __func__);                                      \
    return result;                                                              \
}

#define FORWARD_VECTOR(METHOD_, TYPE_)                                          \
{                                                                               \
    _MESSAGE("in func: %s, file: %s, line: %u", __func__, __FILE__, __LINE__);  \
    auto result = self ? self->METHOD_ : Vector_t<TYPE_>();                     \
    _MESSAGE("out of func: %s", __func__);                                      \
    return result;                                                              \
}

#define FORWARD_VOID(METHOD_)                                                   \
{                                                                               \
    _MESSAGE("in func: %s, file: %s, line: %u", __func__, __FILE__, __LINE__);  \
    self ? self->METHOD_, 1 : 0;                                                \
    _MESSAGE("out of func: %s", __func__);                                      \
}

#else

#define FORWARD_POINTER(METHOD_) { return self ? self->METHOD_ : nullptr; }
#define FORWARD_BOOL(METHOD_) { return self ? self->METHOD_ : false; }
#define FORWARD_INT(METHOD_) { return self ? self->METHOD_ : 0; }
#define FORWARD_STRING(METHOD_) { return self ? self->METHOD_ : ""; }
#define FORWARD_VECTOR(METHOD_, TYPE_) { return self ? self->METHOD_ : Vector_t<TYPE_>(); }
#define FORWARD_VOID(METHOD_) { self ? self->METHOD_, 1 : 0; }
#define FORWARD(METHOD_) { NPCP_ASSERT(self); return self->METHOD_; }

#endif

#define ADD_CLASS_METHOD(STR_CLASS_, BASE_, STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...) \
M                                                                                       \
    registry->RegisterFunction(                                                         \
        new NativeFunction##ARG_NUM_ <BASE_, RETURN_, __VA_ARGS__>(                     \
            STR_FUNC_, STR_CLASS_, METHOD_, registry                                    \
        )                                                                               \
    );                                                                                  \
W

#define FORWARD_METHOD(VM_, STR_CLASS_, TYPE_, STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
M                                                                                           \
    auto METHOD_ = Utils::Forward<RETURN_, TYPE_, __VA_ARGS__, &TYPE_::METHOD_>();          \
    VM_->Bind_Function(                                                                     \
        new NativeFunction##ARG_NUM_ <TYPE_, RETURN_, __VA_ARGS__>(                         \
            STR_FUNC_, STR_CLASS_, METHOD_, reinterpret_cast<Registry_t*>(VM_)              \
        )                                                                                   \
    );                                                                                      \
W

#define DEFINE_STRING(NAME_)                        \
M                                                   \
    static const String_t string = String_t(NAME_); \
    NPCP_ASSERT(string);                            \
    return string;                                  \
W

#define DEFINE_VARIABLE(NAME_)                              \
M                                                           \
    static const String_t variable_name = String_t(NAME_);  \
    NPCP_ASSERT(variable_name);                             \
    Variable_t* variable = Variable(variable_name);         \
    NPCP_ASSERT(variable);                                  \
    return variable;                                        \
W

#define DEFINE_PROPERTY(NAME_)                              \
M                                                           \
    static const String_t property_name = String_t(NAME_);  \
    NPCP_ASSERT(property_name);                             \
    Variable_t* _property = Property(property_name);        \
    NPCP_ASSERT(_property);                                 \
    return _property;                                       \
W

namespace doticu_npcp { namespace Utils {

    template <
        typename Return_t, typename Base_t,
        Return_t(Base_t::* method)()
    > auto Forward()
    {
        return [](Base_t* base)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)();
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A,
        Return_t(Base_t::* method)(A)
    > auto Forward()
    {
        return [](Base_t* base, A a)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B,
        Return_t(Base_t::* method)(A, B)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C,
        Return_t(Base_t::* method)(A, B, C)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D,
        Return_t(Base_t::* method)(A, B, C, D)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c, D d)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c, d);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E,
        Return_t(Base_t::* method)(A, B, C, D, E)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c, d, e);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F,
        Return_t(Base_t::* method)(A, B, C, D, E, F)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G, H)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g, h);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G, H, I)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h, I i)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g, h, i);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G, H, I, J)
    > auto Forward()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)->Return_t
        {
            NPCP_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g, h, i, j);
        };
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

namespace doticu_npcp { namespace Utils { namespace Exports {

    void Print(StaticFunctionTag *, BSFixedString str);
    void Log(StaticFunctionTag *, BSFixedString str);

    bool Register(VMClassRegistry *registry);

}}}
