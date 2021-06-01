/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party_settler.h"
#include "party_settler_flags_sandboxer.h"
#include "party_settler_value_index_sandboxer.h"

namespace doticu_npcp { namespace Party {

    class Settler_Sandboxer_t :
        public Settler_t
    {
    public:
        using Flags_e = Settler_Flags_Sandboxer_e;
        using Value_e = Settler_Value_Index_Sandboxer_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        Settler_Sandboxer_t(some<Settler_ID_t> id);
        Settler_Sandboxer_t(some<Settler_ID_t> id, std::mutex& lock);
        Settler_Sandboxer_t(const Settler_Sandboxer_t& other) = delete;
        Settler_Sandboxer_t(Settler_Sandboxer_t&& other) noexcept;
        Settler_Sandboxer_t& operator =(const Settler_Sandboxer_t& other) = delete;
        Settler_Sandboxer_t& operator =(Settler_Sandboxer_t&& other) noexcept;
        ~Settler_Sandboxer_t();

    public:
        Bool_t  Is_Valid();

    public:
        some<Package_t*>    Package();

    public:
        void    Log(std::string indent = "");
    };

}}
