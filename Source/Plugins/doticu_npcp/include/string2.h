/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <cstring>

#include "utils.h"

namespace doticu_npcp { namespace String2 {

    bool Starts_With_Caseless(const char *str_a, const char *str_b);
    bool Contains_Caseless(const char *str_a, const char *str_b);

}}
