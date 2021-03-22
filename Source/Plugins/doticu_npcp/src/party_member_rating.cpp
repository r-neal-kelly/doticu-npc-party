/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party_member_rating.h"

namespace doticu_npcp { namespace Party {

    Member_Rating_t::Member_Rating_t() :
        value(0)
    {
    }

    Member_Rating_t::Member_Rating_t(u8 rating) :
        value(rating <= 5 ? rating : 0)
    {
    }

    Member_Rating_t::Member_Rating_t(Int_t rating) :
        Member_Rating_t(static_cast<u8>(rating))
    {
    }

    Member_Rating_t::Member_Rating_t(const Member_Rating_t& other) :
        value(other)
    {
    }

    Member_Rating_t::Member_Rating_t(Member_Rating_t&& other) noexcept :
        value(Member_Rating_t(std::exchange(other.value, 0)))
    {
    }

    Member_Rating_t& Member_Rating_t::operator =(const Member_Rating_t& other)
    {
        if (this != std::addressof(other)) {
            this->value = other;
        }
        return *this;
    }

    Member_Rating_t& Member_Rating_t::operator =(Member_Rating_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->value = Member_Rating_t(std::exchange(other.value, 0));
        }
        return *this;
    }

    Member_Rating_t::~Member_Rating_t()
    {
        this->value = 0;
    }

    const char* Member_Rating_t::As_String() const
    {
        // switch this to use Strings_t
        if (*this == 1)         return " * ";
        else if (*this == 2)    return " ** ";
        else if (*this == 3)    return " *** ";
        else if (*this == 4)    return " **** ";
        else if (*this == 5)    return " ***** ";
        else                    return " - ";
    }

    Member_Rating_t::operator value_type() const
    {
        return this->value <= 5 ? this->value : 0;
    }

    Member_Rating_t::operator String_t() const
    {
        return As_String();
    }

}}
