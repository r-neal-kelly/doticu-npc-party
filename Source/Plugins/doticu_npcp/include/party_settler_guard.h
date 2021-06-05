/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party_settler.h"
#include "party_settler_flags_guard.h"
#include "party_settler_value_index_guard.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Guard_t :
        public Settler_t
    {
    public:
        using Flags_e = Settler_Flags_Guard_e;
        using Value_e = Settler_Value_Index_Guard_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        Settler_Guard_t(some<Settler_ID_t> id);
        Settler_Guard_t(some<Settler_ID_t> id, std::mutex& lock);
        Settler_Guard_t(const Settler_Guard_t& other) = delete;
        Settler_Guard_t(Settler_Guard_t&& other) noexcept;
        Settler_Guard_t& operator =(const Settler_Guard_t& other) = delete;
        Settler_Guard_t& operator =(Settler_Guard_t&& other) noexcept;
        ~Settler_Guard_t();

    public:
        Bool_t  Is_Valid();

    public:
        some<Package_t*>    Package();

    public:
        void    Log(std::string indent = "");
    };

}}
