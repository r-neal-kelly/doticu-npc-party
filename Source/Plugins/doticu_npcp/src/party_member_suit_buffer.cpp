/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/reference.h"

#include "party_member_suit_buffer.h"

namespace doticu_skylib { namespace doticu_npcp {

    std::mutex  Member_Suit_Buffer_t::lock;

    Member_Suit_Buffer_t::Member_Suit_Buffer_t() :
        locker(lock, std::defer_lock),
        reference(Consts_t::NPCP::Reference::Suit_Buffer())
    {
        if (!locker.owns_lock()) {
            locker.lock();
        }

        this->reference->Destroy_Non_Quest_Items();
    }

    Member_Suit_Buffer_t::Member_Suit_Buffer_t(Member_Suit_Buffer_t&& other) noexcept :
        locker(std::move(other.locker)),
        reference(std::move(other.reference))
    {
    }

    Member_Suit_Buffer_t& Member_Suit_Buffer_t::operator =(Member_Suit_Buffer_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->locker = std::move(other.locker);
            this->reference = std::move(other.reference);
        }
        return *this;
    }

    Member_Suit_Buffer_t::~Member_Suit_Buffer_t()
    {
        this->reference->Destroy_Non_Quest_Items();

        if (locker.owns_lock()) {
            locker.unlock();
        }
    }

}}
