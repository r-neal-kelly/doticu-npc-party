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

        static Outfit2_t* Create_Member(Actor_t* actor, Reference_t* pack);
        static Outfit2_t* Create_Immobile();
        static Outfit2_t* Create_Settler();
        static Outfit2_t* Create_Thrall();
        static Outfit2_t* Create_Follower();
        static Outfit2_t* Create_Vanilla();
        static Outfit2_t* Create_Default(Actor_t* actor);
        static void Destroy(Outfit2_t* outfit2);
    public:
        Variable_t* Variable(String_t variable_name);
        Variable_t* Type_Variable();
        Variable_t* Outfit1_Cache_Variable();

        Int_t Type();
        Reference_t* Outfit1_Cache();
        Reference_t* Reset_Outfit1_Cache();

        Bool_t Has_Outfit1_Cache();
        Bool_t Hasnt_Outfit1_Cache();

        void Open(String_t outfit_name, Virtual_Callback_i** callback = nullptr);
        void Apply_To(Actor_t* actor, Reference_t* pack, Outfit_t* outfit1_to_apply = nullptr);
        void Cache_Static_Outfit1(Outfit_t* outfit);
        void Cache_Dynamic_Outfit1(Actor_t* actor);
    };

}}

namespace doticu_npcp { namespace Papyrus { namespace Outfit2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}}
