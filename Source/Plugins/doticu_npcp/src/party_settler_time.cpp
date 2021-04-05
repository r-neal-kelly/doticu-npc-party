/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party_settler_time.h"

namespace doticu_npcp { namespace Party {

    Settler_Time_t::Settler_Time_t(some<Settler_Time_AM_PM_e> am_pm,
                                   some<Settler_Time_Hour_t> hour,
                                   some<Settler_Time_Minute_t> minute)
    {
        AM_PM(am_pm);
        Hour(hour);
        Minute(minute);
    }

    maybe<Settler_Time_AM_PM_e> Settler_Time_t::AM_PM() const
    {
        return (static_cast<u32>(this->value) & AM_PM_MASK) >> AM_PM_BIT_INDEX;
    }

    void Settler_Time_t::AM_PM(some<Settler_Time_AM_PM_e> am_pm)
    {
        SKYLIB_ASSERT_SOME(am_pm);

        this->value =
            ((static_cast<u32>(am_pm()) << AM_PM_BIT_INDEX) & AM_PM_MASK) |
            (static_cast<u32>(this->value) & ~AM_PM_MASK);
    }

    maybe<Settler_Time_Hour_t> Settler_Time_t::Hour() const
    {
        return (static_cast<u32>(this->value) & HOUR_MASK) >> HOUR_BIT_INDEX;
    }

    void Settler_Time_t::Hour(some<Settler_Time_Hour_t> hour)
    {
        SKYLIB_ASSERT_SOME(hour);

        this->value =
            ((static_cast<u32>(hour()) << HOUR_BIT_INDEX) & HOUR_MASK) |
            (static_cast<u32>(this->value) & ~HOUR_MASK);
    }

    maybe<Settler_Time_Minute_t> Settler_Time_t::Minute() const
    {
        return (static_cast<u32>(this->value) & MINUTE_MASK) >> MINUTE_BIT_INDEX;
    }

    void Settler_Time_t::Minute(some<Settler_Time_Minute_t> minute)
    {
        SKYLIB_ASSERT_SOME(minute);

        this->value =
            ((static_cast<u32>(minute()) << MINUTE_BIT_INDEX) & MINUTE_MASK) |
            (static_cast<u32>(this->value) & ~MINUTE_MASK);
    }

    Settler_Time_t::operator maybe<Settler_Time_AM_PM_e>() const
    {
        return AM_PM();
    }

    Settler_Time_t::operator maybe<Settler_Time_Hour_t>() const
    {
        return Hour();
    }

    Settler_Time_t::operator maybe<Settler_Time_Minute_t>() const
    {
        return Minute();
    }

}}
