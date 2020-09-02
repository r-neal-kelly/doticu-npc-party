/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "papyrus.h"

#include "party/party_aliases.h"
#include "party/party_followers.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Horse_t;

    class Horses_t : public Aliases_t {
    public:
        static constexpr size_t MAX = Consts::MAX_FOLLOWERS;
        static constexpr size_t HALF = MAX / 2;
        static constexpr size_t BEGIN = Followers_t::END;
        static constexpr size_t END = BEGIN + MAX;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Horses_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Range_t<UInt64> Indices();
        Range_t<Horse_t**> Aliases();

        Horse_t* From_ID(Int_t unique_id);
        Horse_t* From_Actor(Actor_t* actor);

        Int_t Add_Horse(Follower_t* follower);
        Int_t Remove_Horse(Follower_t* follower);

        void u_0_9_8();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
