/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party_settler.h"

namespace doticu_npcp { namespace Party {

    Settler_t::Settler_t(some<Settler_ID_t> id) :
        member(id)
    {
    }

    Settler_t::Settler_t(some<Settler_ID_t> id, std::mutex& lock) :
        member(id, lock)
    {
    }

    Settler_t::Settler_t(Settler_t&& other) noexcept :
        member(std::move(other.member))
    {
    }

    Settler_t& Settler_t::operator =(Settler_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->member = std::move(other.member);
        }
        return *this;
    }

    Settler_t::~Settler_t()
    {
    }

}}
