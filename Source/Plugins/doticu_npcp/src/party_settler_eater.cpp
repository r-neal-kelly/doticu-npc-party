/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "party_settler_eater.h"

namespace doticu_npcp { namespace Party {

    some<Form_List_t*> Settler_Eater_t::Packages()
    {
        return Consts_t::NPCP::Form_List::Settler_Eater_Packages();
    }

    some<Misc_t*> Settler_Eater_t::Token()
    {
        return Consts_t::NPCP::Misc::Token::Settler_Eater();
    }

    Settler_Eater_t::Settler_Eater_t(some<Settler_ID_t> id) :
        Settler_t(id)
    {
    }

    Settler_Eater_t::Settler_Eater_t(some<Settler_ID_t> id, std::mutex& lock) :
        Settler_t(id, lock)
    {
    }

    Settler_Eater_t::Settler_Eater_t(Settler_Eater_t&& other) noexcept :
        Settler_t(std::move(other))
    {
    }

    Settler_Eater_t& Settler_Eater_t::operator =(Settler_Eater_t&& other) noexcept
    {
        Settler_t::operator =(std::move(other));
        return *this;
    }

    Settler_Eater_t::~Settler_Eater_t()
    {
    }

    Bool_t Settler_Eater_t::Is_Valid()
    {

    }

    some<Package_t*> Settler_Eater_t::Package()
    {

    }

}}
