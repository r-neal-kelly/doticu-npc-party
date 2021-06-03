/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "consts.h"
#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Member_Suit_Buffer_t
    {
    public:
        static std::mutex   lock;

    public:
        std::unique_lock<std::mutex>    locker;
        some<Reference_t*>              reference;

    public:
        Member_Suit_Buffer_t();
        Member_Suit_Buffer_t(const Member_Suit_Buffer_t& other) = delete;
        Member_Suit_Buffer_t(Member_Suit_Buffer_t&& other) noexcept;
        Member_Suit_Buffer_t& operator =(const Member_Suit_Buffer_t& other) = delete;
        Member_Suit_Buffer_t& operator =(Member_Suit_Buffer_t&& other) noexcept;
        ~Member_Suit_Buffer_t();
    };

}}
