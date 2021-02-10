/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus {

    class Form_Vector_t;

}}

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class NPCS_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static NPCS_t* Self();
    public:
        void Initialize();
        void Uninitialize();
        void Reinitialize();

        Object_t* Object();
        Variable_t* Variable(String_t variable_name);
        Variable_t* Bases_Variable();
        Variable_t* Default_Outfits_Variable();

        Form_Vector_t* Bases();
        Form_Vector_t* Default_Outfits();

        Actor_Base_t* Base(Actor_t* actor);
        Int_t Base_Idx(Actor_t* actor);
        Outfit_t* Default_Outfit(Int_t base_idx);

        Bool_t Has_Base(Actor_t* actor);

        Int_t Add_Base_If_Needed(Actor_t* actor_with_base, Actor_t* actor_with_outfit);
        void Remove_Base(Int_t base_idx);
        void Add_Original(Actor_t* original);
        void Remove_Original(Actor_t* original);
        Actor_t* Add_Clone(Actor_t* original);
        void Remove_Clone(Actor_t* clone, Bool_t do_delete_clone);

        Outfit_t* Default_Outfit(Actor_t* actor);
        void Change_Default_Outfit(Actor_t* actor, Outfit_t* default_outfit);

        void Remove_All_Tokens(Actor_t* actor);

        void u_0_9_3();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
