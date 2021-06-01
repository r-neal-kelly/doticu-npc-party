/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "party_member.h"
#include "party_settler_id.h"

namespace doticu_npcp { namespace Party {

    class Settler_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ALIAS_REFERENCE,
        };

    public:
        static String_t             Class_Name();
        static some<V::Class_t*>    Class();
        static void                 Register_Me(some<V::Machine_t*> machine);

    public:
        Member_t    member;

    public:
        Settler_t(some<Settler_ID_t> id);
        Settler_t(some<Settler_ID_t> id, std::mutex& lock);
        Settler_t(const Settler_t& other) = delete;
        Settler_t(Settler_t&& other) noexcept;
        Settler_t& operator =(const Settler_t& other) = delete;
        Settler_t& operator =(Settler_t&& other) noexcept;
        ~Settler_t();

    public:
        Bool_t  Is_Valid();

    public:
        void    Enforce();

    public:
        explicit operator Bool_t();

    public:
        void    Log(std::string indent = "");
    };

}}
