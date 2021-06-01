/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party_settler.h"
#include "party_settler_flags_sitter.h"
#include "party_settler_value_index_sitter.h"

namespace doticu_npcp { namespace Party {

    class Settler_Sitter_t :
        public Settler_t
    {
    public:
        using Flags_e = Settler_Flags_Sitter_e;
        using Value_e = Settler_Value_Index_Sitter_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        Settler_Sitter_t(some<Settler_ID_t> id);
        Settler_Sitter_t(some<Settler_ID_t> id, std::mutex& lock);
        Settler_Sitter_t(const Settler_Sitter_t& other) = delete;
        Settler_Sitter_t(Settler_Sitter_t&& other) noexcept;
        Settler_Sitter_t& operator =(const Settler_Sitter_t& other) = delete;
        Settler_Sitter_t& operator =(Settler_Sitter_t&& other) noexcept;
        ~Settler_Sitter_t();

    public:
        Bool_t  Is_Valid();

    public:
        some<Package_t*>    Package();

    public:
        void    Log(std::string indent = "");
    };

}}
