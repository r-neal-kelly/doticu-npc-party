/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "party_settler_sleeper.h"

namespace doticu_npcp { namespace Party {

    some<Form_List_t*> Settler_Sleeper_t::Packages()
    {
        return Consts_t::NPCP::Form_List::Settler_Sleeper_Packages();
    }

    some<Misc_t*> Settler_Sleeper_t::Token()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sleeper();
    }

    Settler_Sleeper_t::Settler_Sleeper_t(some<Settler_ID_t> id) :
        Settler_t(id)
    {
    }

    Settler_Sleeper_t::Settler_Sleeper_t(some<Settler_ID_t> id, std::mutex& lock) :
        Settler_t(id, lock)
    {
    }

    Settler_Sleeper_t::Settler_Sleeper_t(Settler_Sleeper_t&& other) noexcept :
        Settler_t(std::move(other))
    {
    }

    Settler_Sleeper_t& Settler_Sleeper_t::operator =(Settler_Sleeper_t&& other) noexcept
    {
        Settler_t::operator =(std::move(other));
        return *this;
    }

    Settler_Sleeper_t::~Settler_Sleeper_t()
    {
    }

    Bool_t Settler_Sleeper_t::Is_Valid()
    {

    }

    some<Package_t*> Settler_Sleeper_t::Package()
    {

    }

}}
