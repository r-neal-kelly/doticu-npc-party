/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "party_main.h"

namespace doticu_npcp { namespace Party {

    Main_t::Main_t(Bool_t is_new_game) :
        members(Consts_t::NPCP::Quest::Members(), is_new_game),
        settlers(Consts_t::NPCP::Quest::Members(), is_new_game),
        expoees(Consts_t::NPCP::Quest::Members(), is_new_game),
        displays(Consts_t::NPCP::Quest::Members(), is_new_game),
        followers(Consts_t::NPCP::Quest::Followers(), is_new_game)
    {
    }

    Main_t::Main_t(const Version_t<u16> version_to_update) :
        members(Consts_t::NPCP::Quest::Members(), version_to_update),
        settlers(Consts_t::NPCP::Quest::Members(), version_to_update),
        expoees(Consts_t::NPCP::Quest::Members(), version_to_update),
        displays(Consts_t::NPCP::Quest::Members(), version_to_update),
        followers(Consts_t::NPCP::Quest::Followers(), version_to_update)
    {
    }

    Main_t::~Main_t()
    {
    }

    void Main_t::Before_Save()
    {
        members.Before_Save();
        settlers.Before_Save();
        expoees.Before_Save();
        displays.Before_Save();
        followers.Before_Save();
    }

    void Main_t::After_Save()
    {
        members.After_Save();
        settlers.After_Save();
        expoees.After_Save();
        displays.After_Save();
        followers.After_Save();
    }

}}
