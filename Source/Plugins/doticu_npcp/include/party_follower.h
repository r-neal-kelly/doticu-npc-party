/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_script_type.h"

#include "intrinsic.h"
#include "party_member.h"
#include "party_follower_id.h"

namespace doticu_npcp { namespace Party {

    class Follower_t
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
        Member_t            member;
        some<Follower_ID_t> id;
        Locker_t            locker;

    public:
        Follower_t(some<Follower_ID_t> id);
        Follower_t(const Follower_t& other) = delete;
        Follower_t(Follower_t&& other) noexcept;
        Follower_t& operator =(const Follower_t& other) = delete;
        Follower_t& operator =(Follower_t&& other) noexcept;
        ~Follower_t();

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
