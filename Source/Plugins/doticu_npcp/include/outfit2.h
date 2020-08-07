/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus {

    class Outfit2_t : public Reference_t {
    public:
        static constexpr Int_t MAX_FORMS = 16;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();

        static Outfit2_t* Create_Member();
        static Outfit2_t* Create_Immobile();
        static Outfit2_t* Create_Settler();
        static Outfit2_t* Create_Thrall();
        static Outfit2_t* Create_Follower();
        static Outfit2_t* Create_Vanilla();
        static Outfit2_t* Create_Default();
        static void Destroy(Outfit2_t* outfit2);
    public:
        Variable_t* Variable(String_t variable_name);
        Variable_t* Type_Variable();
        Variable_t* Name_Variable();
        Variable_t* Outfit1_Cache_Variable();

        Int_t Type();
        String_t Name();
        Reference_t* Outfit1_Cache();

        void Open();
        void Rename(String_t name);
        void Apply_To(Actor_t* actor, Reference_t* pack);
    };

}}

namespace doticu_npcp { namespace Papyrus { namespace Outfit2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}}
