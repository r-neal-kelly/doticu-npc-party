/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <cstring>

#include "types.h"

namespace doticu_npcp { namespace String2 {

    bool Is_Same(const char *str_a, const char *str_b);
    bool Starts_With(const char *str_subject, const char *str_object);
    bool Contains(const char *str_subject, const char *str_object);

    bool Is_Same_Caseless(const char *str_a, const char *str_b);
    bool Starts_With_Caseless(const char *str_a, const char *str_b);
    bool Starts_With_Caseless(const char *str, const char chr);
    bool Contains_Caseless(const char *str_a, const char *str_b);

    size_t Length(const char* str);

}}

namespace doticu_npcp { namespace String2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
