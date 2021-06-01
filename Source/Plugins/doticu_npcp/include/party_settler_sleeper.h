/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party_settler.h"
#include "party_settler_flags_sleeper.h"
#include "party_settler_value_index_sleeper.h"

namespace doticu_npcp { namespace Party {

    class Settler_Sleeper_t :
        public Settler_t
    {
    public:
        using Flags_e = Settler_Flags_Sleeper_e;
        using Value_e = Settler_Value_Index_Sleeper_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        Settler_Sleeper_t(some<Settler_ID_t> id);
        Settler_Sleeper_t(some<Settler_ID_t> id, std::mutex& lock);
        Settler_Sleeper_t(const Settler_Sleeper_t& other) = delete;
        Settler_Sleeper_t(Settler_Sleeper_t&& other) noexcept;
        Settler_Sleeper_t& operator =(const Settler_Sleeper_t& other) = delete;
        Settler_Sleeper_t& operator =(Settler_Sleeper_t&& other) noexcept;
        ~Settler_Sleeper_t();

    public:
        Bool_t  Is_Valid();

    public:
        some<Package_t*>    Package();

    public:
        void    Log(std::string indent = "");
    };

}}
