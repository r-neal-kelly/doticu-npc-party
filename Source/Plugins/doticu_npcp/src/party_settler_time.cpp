/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "npcp.inl"
#include "party_settler_time.h"

namespace doticu_skylib { namespace doticu_npcp {

    u16 Settler_Time_t::Duration_In_Minutes(some<Calendar_Time_t> start, some<Calendar_Time_t> stop)
    {
        static constexpr u16 MAX_MINUTES = 24 * 60;

        SKYLIB_ASSERT_SOME(start);
        SKYLIB_ASSERT_SOME(stop);

        s64 start_minutes = start.In_Minutes();
        s64 stop_minutes = stop.In_Minutes();
        if (start_minutes == stop_minutes) {
            return MAX_MINUTES;
        } else if (stop_minutes > start_minutes) {
            return stop_minutes - start_minutes;
        } else {
            return MAX_MINUTES - start_minutes + stop_minutes;
        }
    }

    Settler_Time_t::Settler_Time_t() :
        start(), stop()
    {
    }

    Settler_Time_t::Settler_Time_t(const Settler_Time_t& other) :
        start(other.start), stop(other.stop)
    {
    }

    Settler_Time_t::Settler_Time_t(Settler_Time_t&& other) noexcept :
        start(std::move(other.start)), stop(std::move(other.stop))
    {
    }

    Settler_Time_t& Settler_Time_t::operator =(const Settler_Time_t& other)
    {
        if (this != std::addressof(other)) {
            this->start = other.start;
            this->stop = other.stop;
        }
        return *this;
    }

    Settler_Time_t& Settler_Time_t::operator =(Settler_Time_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->start = std::move(other.start);
            this->stop = std::move(other.stop);
        }
        return *this;
    }

    Settler_Time_t::~Settler_Time_t()
    {
    }

    void Settler_Time_t::Write(std::ofstream& file)
    {
        NPCP.Write(file, this->start);
        NPCP.Write(file, this->stop);
    }

    void Settler_Time_t::Read(std::ifstream& file)
    {
        NPCP.Read(file, this->start);
        NPCP.Read(file, this->stop);
    }

    Bool_t Settler_Time_t::Is_Valid() const
    {
        return this->start && this->stop;
    }

    u16 Settler_Time_t::Duration_In_Minutes() const
    {
        SKYLIB_ASSERT(Is_Valid());

        return Duration_In_Minutes(this->start(), this->stop());
    }

    Settler_Time_t::operator Bool_t() const
    {
        return Is_Valid();
    }

}}
