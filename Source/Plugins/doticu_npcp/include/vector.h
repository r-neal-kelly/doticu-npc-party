/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <vector>

namespace doticu_npcp { namespace Vector {

    template <typename T>
    s64 Index_Of(std::vector<T> &vec, T &item) {
        for (s64 idx = 0, size = vec.size(); idx < size; idx += 1) {
            if (vec[idx] == item) {
                return idx;
            }
        }
        return -1;
    }

}}
