/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party.h"
#include "party.inl"
#include "quest.h"

namespace doticu_npcp { namespace Party {

    Int_t Alias_t::ID()
    {
        return id;
    }

    Actor_t* Alias_t::Actor()
    {
        return Quest::Alias_Actor(quest, id);
    }

    Bool_t Alias_t::Is_Filled()
    {
        return Quest::Is_Alias_Filled(quest, id);
    }

    Bool_t Alias_t::Is_Unfilled()
    {
        return !Quest::Is_Alias_Filled(quest, id);
    }

}}
