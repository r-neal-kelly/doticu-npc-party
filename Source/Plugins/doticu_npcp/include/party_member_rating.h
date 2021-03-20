/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    // the valid values are 0, 1, 2, 3, 4, 5

    class Member_Rating_t
    {
    public:
        using value_type = u8;

    public:
        value_type value;

    public:
        Member_Rating_t();
        Member_Rating_t(const Member_Rating_t& other) = delete;
        Member_Rating_t(Member_Rating_t&& other) noexcept = delete;
        Member_Rating_t& operator =(const Member_Rating_t& other) = delete;
        Member_Rating_t& operator =(Member_Rating_t&& other) noexcept = delete;
        ~Member_Rating_t();
    };

}}
