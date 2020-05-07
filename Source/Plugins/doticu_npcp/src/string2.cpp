/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "string2.h"

namespace doticu_npcp { namespace String2 {

    bool Starts_With_Caseless(const char *str_a, const char *str_b) {
        char char_a;
        char char_b;
        for (u64 idx = 0; str_b[idx] != 0; idx += 1) {
            char_a = tolower(str_a[idx]);
            char_b = tolower(str_b[idx]);
            if (char_a == 0 || char_a != char_b) {
                return false;
            }
        }

        return true;
    }
    bool Contains_Caseless(const char *str_a, const char *str_b) {
        for (u64 idx = 0; str_a[idx] != 0; idx += 1) {
            if (Starts_With_Caseless(str_a + idx, str_b)) {
                return true;
            }
        }

        return false;
    }

}}
