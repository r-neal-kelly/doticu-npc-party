/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Member_t;

}}}

namespace doticu_npcp { namespace Papyrus {

    class Outfit2_t : public Reference_t {
    public:
        static constexpr Int_t MAX_FORMS = 16;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();

        static Outfit2_t* Create_Member(Party::Member_t* member, Actor_t* actor, Reference_t* pack);
        static Outfit2_t* Create_Immobile(Party::Member_t* member);
        static Outfit2_t* Create_Settler(Party::Member_t* member);
        static Outfit2_t* Create_Thrall(Party::Member_t* member);
        static Outfit2_t* Create_Follower(Party::Member_t* member);
        static Outfit2_t* Create_Vanilla(Party::Member_t* member);
        static Outfit2_t* Create_Default(Party::Member_t* member, Actor_t* actor);
        static void Destroy(Outfit2_t* outfit2);
    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Member_Variable(); // Member_t*
        Variable_t* Type_Variable(); // Int_t
        Variable_t* Outfit1_Cache_Variable(); // Reference_t

        Party::Member_t* Member();
        Int_t Type();
        Reference_t* Outfit1_Cache();
        Reference_t* Reset_Outfit1_Cache();

        Bool_t Has_Outfit1_Cache();
        Bool_t Hasnt_Outfit1_Cache();

        void Clean_Blank_Items();

        void Open(String_t outfit_name, Virtual_Callback_i** callback = nullptr);
        void Apply_To(Actor_t* actor, Reference_t* pack, Callback_t<Actor_t*>* user_callback = nullptr);
        void Cache_Static_Outfit1(Outfit_t* outfit);
        void Cache_Dynamic_Outfit1(Actor_t* actor);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}
