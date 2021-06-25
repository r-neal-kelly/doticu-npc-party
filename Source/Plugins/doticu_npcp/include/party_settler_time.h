/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_time.h"
#include "doticu_skylib/enum_comparator.h"

#include "intrinsic.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Time_t
    {
    public:
        static u16  Duration_In_Minutes(some<Calendar_Time_t> start, some<Calendar_Time_t> stop);
        static u16  Minutes_Between(some<Settler_Time_t> a, some<Settler_Time_t> b);

    public:
        maybe<Calendar_Time_t>  start;
        maybe<Calendar_Time_t>  stop;

    public:
        Settler_Time_t();
        Settler_Time_t(const Settler_Time_t& other);
        Settler_Time_t(Settler_Time_t&& other) noexcept;
        Settler_Time_t& operator =(const Settler_Time_t& other);
        Settler_Time_t& operator =(Settler_Time_t&& other) noexcept;
        ~Settler_Time_t();

    public:
        void    Write(std::ofstream& file);
        void    Read(std::ifstream& file);

    public:
        Bool_t  Is_Valid() const;

        u16     Duration_In_Minutes() const;

    public:
        explicit operator   Bool_t() const;
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Settler_Time_t> :
        public doticu_npcp::Settler_Time_t
    {
    public:
        using Settler_Time_t::Settler_Time_t;
    };

    template <>
    class maybe<doticu_npcp::Settler_Time_t> :
        public doticu_npcp::Settler_Time_t
    {
    public:
        using Settler_Time_t::Settler_Time_t;
    };

    template <>
    class some<doticu_npcp::Settler_Time_t> :
        public doticu_npcp::Settler_Time_t
    {
    public:
        using Settler_Time_t::Settler_Time_t;
    };

}
