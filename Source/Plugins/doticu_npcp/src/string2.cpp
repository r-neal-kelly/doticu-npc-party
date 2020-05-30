/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "string2.h"

namespace doticu_npcp { namespace String2 {

    bool Is_Same(const char *str_a, const char *str_b) {
        return strcmp(str_a, str_b) == 0;
    }

    bool Starts_With(const char *str_subject, const char *str_object) {
        char char_subject;
        char char_object;
        for (u64 idx = 0; str_object[idx] != 0; idx += 1) {
            char_subject = str_subject[idx];
            char_object = str_object[idx];
            if (char_subject == 0 || char_subject != char_object) {
                return false;
            }
        }

        return true;
    }

    bool Contains(const char *str_subject, const char *str_object) {
        for (u64 idx = 0; str_subject[idx] != 0; idx += 1) {
            if (Starts_With(str_subject + idx, str_object)) {
                return true;
            }
        }

        return false;
    }

    bool Is_Same_Caseless(const char *str_a, const char *str_b) {
        return _stricmp(str_a, str_b) == 0;
    }

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
