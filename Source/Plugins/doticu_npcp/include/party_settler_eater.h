/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party_settler.h"
#include "party_settler_flags_eater.h"
#include "party_settler_value_index_eater.h"

namespace doticu_skylib { namespace doticu_npcp {

    class Settler_Eater_t :
        public Settler_t
    {
    public:
        using Flags_e = Settler_Flags_Eater_e;
        using Value_e = Settler_Value_Index_Eater_e;

    public:
        static some<Form_List_t*>   Packages();
        static some<Misc_t*>        Token();

    public:
        Settler_Eater_t(some<Settler_ID_t> id);
        Settler_Eater_t(some<Settler_ID_t> id, std::mutex& lock);
        Settler_Eater_t(const Settler_Eater_t& other) = delete;
        Settler_Eater_t(Settler_Eater_t&& other) noexcept;
        Settler_Eater_t& operator =(const Settler_Eater_t& other) = delete;
        Settler_Eater_t& operator =(Settler_Eater_t&& other) noexcept;
        ~Settler_Eater_t();

    public:
        Bool_t  Is_Valid();

    public:
        some<Package_t*>    Package();

    public:
        void    Log(std::string indent = "");
    };

}}
