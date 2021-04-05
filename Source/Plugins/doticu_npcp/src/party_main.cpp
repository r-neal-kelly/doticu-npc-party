/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "party_displays.h"
#include "party_expoees.h"
#include "party_followers.h"
#include "party_main.h"
#include "party_members.h"
#include "party_settlers.h"

namespace doticu_npcp { namespace Party {

    void Main_t::Register_Me(some<V::Machine_t*> machine)
    {
        SKYLIB_ASSERT_SOME(machine);

        Members_t::Register_Me(machine);
        Settlers_t::Register_Me(machine);
        Expoees_t::Register_Me(machine);
        Displays_t::Register_Me(machine);
        Followers_t::Register_Me(machine);
    }

    Main_t::Main_t(Bool_t is_new_game) :
        members(new Members_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        settlers(new Settlers_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        expoees(new Expoees_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        displays(new Displays_t(Consts_t::NPCP::Quest::Members(), is_new_game)),
        followers(new Followers_t(Consts_t::NPCP::Quest::Followers(), is_new_game))
    {
    }

    Main_t::Main_t(const Version_t<u16> version_to_update) :
        members(new Members_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        settlers(new Settlers_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        expoees(new Expoees_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        displays(new Displays_t(Consts_t::NPCP::Quest::Members(), version_to_update)),
        followers(new Followers_t(Consts_t::NPCP::Quest::Followers(), version_to_update))
    {
    }

    Main_t::~Main_t()
    {
    }

    void Main_t::Before_Save()
    {
        members->Before_Save();
        settlers->Before_Save();
        expoees->Before_Save();
        displays->Before_Save();
        followers->Before_Save();
    }

    void Main_t::After_Save()
    {
        members->After_Save();
        settlers->After_Save();
        expoees->After_Save();
        displays->After_Save();
        followers->After_Save();
    }

    Members_t& Main_t::Members()
    {
        return *this->members;
    }

    Settlers_t& Main_t::Settlers()
    {
        return *this->settlers;
    }

    Expoees_t& Main_t::Expoees()
    {
        return *this->expoees;
    }

    Displays_t& Main_t::Displays()
    {
        return *this->displays;
    }

    Followers_t& Main_t::Followers()
    {
        return *this->followers;
    }

}}
