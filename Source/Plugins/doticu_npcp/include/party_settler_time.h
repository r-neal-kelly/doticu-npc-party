/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/numeric.h"

#include "intrinsic.h"
#include "party_settler_time_am_pm.h"
#include "party_settler_time_hour.h"
#include "party_settler_time_minute.h"

namespace doticu_npcp { namespace Party {

    class Settler_Time_t_data :
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

    class Settler_Time_t :
        public Numeric_t<Settler_Time_t_data>
    {
    public:
        static constexpr u32    AM_PM_MASK          = 0x00FF0000;
        static constexpr u32    HOUR_MASK           = 0x0000FF00;
        static constexpr u32    MINUTE_MASK         = 0x000000FF;

        static constexpr u32    AM_PM_BIT_INDEX     = 16;
        static constexpr u32    HOUR_BIT_INDEX      = 8;
        static constexpr u32    MINUTE_BIT_INDEX    = 0;

    public:
        using Numeric_t::Numeric_t;

    public:
        Settler_Time_t()                                    = default;
        Settler_Time_t(some<Settler_Time_AM_PM_e> am_pm,
                       some<Settler_Time_Hour_t> hour,
                       some<Settler_Time_Minute_t> minute);

    public:
        some<Settler_Time_AM_PM_e>  AM_PM() const;
        void                        AM_PM(some<Settler_Time_AM_PM_e> am_pm);

        some<Settler_Time_Hour_t>   Hour() const;
        void                        Hour(some<Settler_Time_Hour_t> hour);

        some<Settler_Time_Minute_t> Minute() const;
        void                        Minute(some<Settler_Time_Minute_t> minute);

        s32                         Military_Hour();

    public:
        operator    some<Settler_Time_AM_PM_e>() const;
        operator    some<Settler_Time_Hour_t>() const;
        operator    some<Settler_Time_Minute_t>() const;
    };

}}

namespace doticu_skylib {

    template <>
    class none<doticu_npcp::Party::Settler_Time_t> :
        public none_numeric<doticu_npcp::Party::Settler_Time_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<doticu_npcp::Party::Settler_Time_t> :
        public maybe_numeric<doticu_npcp::Party::Settler_Time_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<doticu_npcp::Party::Settler_Time_t> :
        public some_numeric<doticu_npcp::Party::Settler_Time_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
