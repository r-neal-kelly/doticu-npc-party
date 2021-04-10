/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"
#include "doticu_skylib/numeric.h"

#include "intrinsic.h"
#include "party_settler_duration_hours.h"
#include "party_settler_duration_minutes.h"

namespace doticu_npcp { namespace Party {

    class Settler_Duration_t_data :
        public Numeric_Data_t<Int_t>
    {
    public:
        static constexpr value_type _NONE_  = -1;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value != _NONE_;
        }
    };

    class Settler_Duration_t :
        public Numeric_t<Settler_Duration_t_data>
    {
    public:
        static constexpr u32    HOURS_MASK          = 0xFFFF0000;
        static constexpr u32    MINUTES_MASK        = 0x0000FFFF;

        static constexpr u32    HOURS_BIT_INDEX     = 16;
        static constexpr u32    MINUTES_BIT_INDEX   = 0;

        static constexpr u32    MIN_DURATION        = 0;
        static constexpr u32    MAX_DURATION        = Settler_Duration_Hours_t::_MAX_ * 60;

    public:
        using Numeric_t::Numeric_t;

    public:
        Settler_Duration_t()                                            = default;
        Settler_Duration_t(some<Settler_Duration_Hours_t> hours,
                           some<Settler_Duration_Minutes_t> minutes);

    public:
        some<Settler_Duration_Hours_t>      Hours() const;
        void                                Hours(some<Settler_Duration_Hours_t> hours);

        some<Settler_Duration_Minutes_t>    Minutes() const;
        void                                Minutes(some<Settler_Duration_Minutes_t> minutes);

        u32                                 Total_Minutes() const;

    public:
        operator    some<Settler_Duration_Hours_t>() const;
        operator    some<Settler_Duration_Minutes_t>() const;
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Party::Settler_Duration_t> :
        public none_numeric<doticu_npcp::Party::Settler_Duration_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<doticu_npcp::Party::Settler_Duration_t> :
        public maybe_numeric<doticu_npcp::Party::Settler_Duration_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<doticu_npcp::Party::Settler_Duration_t> :
        public some_numeric<doticu_npcp::Party::Settler_Duration_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
