/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Member_t;

}}}

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Followers_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Followers_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable();
        Variable_t* Member_Variable();
        Variable_t* Do_Previous_Follower_Variable();
        Variable_t* Do_Next_Follower_Variable();

        Int_t Current_View();
        void Current_View(Int_t view_code);

        Party::Member_t* Member();
        void Member(Party::Member_t* member);

        void Review_Followers();
        void Request_Previous_Follower();
        void Request_Next_Follower();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
