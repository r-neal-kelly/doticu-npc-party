/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party_settler_duration.h"

namespace doticu_npcp { namespace Party {

    Settler_Duration_t::Settler_Duration_t(some<Settler_Duration_Hours_t> hours,
                                           some<Settler_Duration_Minutes_t> minutes)
    {
        Hours(hours);
        Minutes(minutes);
    }

    some<Settler_Duration_Hours_t> Settler_Duration_t::Hours() const
    {
        maybe<Settler_Duration_Hours_t> hours =
            (static_cast<u32>(this->value) & HOURS_MASK) >> HOURS_BIT_INDEX;
        if (hours) {
            return hours();
        } else {
            return Settler_Duration_Hours_t::_MIN_;
        }
    }

    void Settler_Duration_t::Hours(some<Settler_Duration_Hours_t> hours)
    {
        SKYLIB_ASSERT_SOME(hours);

        this->value =
            ((static_cast<u32>(hours()) << HOURS_BIT_INDEX) & HOURS_MASK) |
            (static_cast<u32>(this->value) & ~HOURS_MASK);
    }

    some<Settler_Duration_Minutes_t> Settler_Duration_t::Minutes() const
    {
        maybe<Settler_Duration_Minutes_t> minutes =
            (static_cast<u32>(this->value) & MINUTES_MASK) >> MINUTES_BIT_INDEX;
        if (minutes) {
            if (Hours() == Settler_Duration_Hours_t::_MAX_) {
                return Settler_Duration_Minutes_t::_MIN_;
            } else {
                return minutes();
            }
        } else {
            return Settler_Duration_Minutes_t::_MIN_;
        }
    }

    void Settler_Duration_t::Minutes(some<Settler_Duration_Minutes_t> minutes)
    {
        SKYLIB_ASSERT_SOME(minutes);

        this->value =
            ((static_cast<u32>(minutes()) << MINUTES_BIT_INDEX) & MINUTES_MASK) |
            (static_cast<u32>(this->value) & ~MINUTES_MASK);
    }

    u32 Settler_Duration_t::Total_Minutes() const
    {
        return (Hours()() * 60) + Minutes()();
    }

    Settler_Duration_t::operator some<Settler_Duration_Hours_t>() const
    {
        return Hours();
    }

    Settler_Duration_t::operator some<Settler_Duration_Minutes_t>() const
    {
        return Minutes();
    }

}}
