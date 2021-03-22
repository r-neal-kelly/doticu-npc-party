/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcp { namespace Party {

    class Member_Rating_t
    {
    public:
        using value_type = u8;

    public:
        value_type value;

    public:
        Member_Rating_t();
        Member_Rating_t(u8 rating);
        Member_Rating_t(Int_t rating);
        Member_Rating_t(const Member_Rating_t& other);
        Member_Rating_t(Member_Rating_t&& other) noexcept;
        Member_Rating_t& operator =(const Member_Rating_t& other);
        Member_Rating_t& operator =(Member_Rating_t&& other) noexcept;
        ~Member_Rating_t();

    public:
        const char* As_String() const;

    public:
        operator value_type() const;
        operator String_t() const;
    };

}}
