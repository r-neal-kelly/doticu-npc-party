/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "party_settler_sandboxer.h"

namespace doticu_npcp { namespace Party {

    some<Form_List_t*> Settler_Sandboxer_t::Packages()
    {
        return Consts_t::NPCP::Form_List::Settler_Sandboxer_Packages();
    }

    some<Misc_t*> Settler_Sandboxer_t::Token()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Sandboxer();
    }

    Settler_Sandboxer_t::Settler_Sandboxer_t(some<Settler_ID_t> id) :
        Settler_t(id)
    {
    }

    Settler_Sandboxer_t::Settler_Sandboxer_t(some<Settler_ID_t> id, std::mutex& lock) :
        Settler_t(id, lock)
    {
    }

    Settler_Sandboxer_t::Settler_Sandboxer_t(Settler_Sandboxer_t&& other) noexcept :
        Settler_t(std::move(other))
    {
    }

    Settler_Sandboxer_t& Settler_Sandboxer_t::operator =(Settler_Sandboxer_t&& other) noexcept
    {
        Settler_t::operator =(std::move(other));
        return *this;
    }

    Settler_Sandboxer_t::~Settler_Sandboxer_t()
    {
    }

    Bool_t Settler_Sandboxer_t::Is_Valid()
    {

    }

    some<Package_t*> Settler_Sandboxer_t::Package()
    {

    }

}}
