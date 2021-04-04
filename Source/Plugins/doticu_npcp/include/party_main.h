/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"
#include "party_displays.h"
#include "party_expoees.h"
#include "party_followers.h"
#include "party_members.h"
#include "party_settlers.h"

namespace doticu_npcp { namespace Party {

    class Main_t
    {
    public:
        Members_t   members;
        Settlers_t  settlers;
        Expoees_t   expoees;
        Displays_t  displays;
        Followers_t followers;

    public:
        Main_t(Bool_t is_new_game);
        Main_t(const Version_t<u16> version_to_update);
        Main_t(const Main_t& other)                     = delete;
        Main_t(Main_t&& other) noexcept                 = delete;
        Main_t& operator =(const Main_t& other)         = delete;
        Main_t& operator =(Main_t&& other) noexcept     = delete;
        ~Main_t();

    public:
        void    Before_Save();
        void    After_Save();

    public:
        void    Log(std::string indent = "");
    };

}}
