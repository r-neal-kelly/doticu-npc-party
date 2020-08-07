/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "object_ref.h"
#include "outfit2.h"
#include "papyrus.inl"
#include "party.h"
#include "utils.h"
#include "vars.h"

namespace doticu_npcp { namespace Papyrus {

    String_t Outfit2_t::Class_Name()
    {
        static String_t class_name = String_t("doticu_npcp_outfit");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Outfit2_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    static void Fill(Outfit2_t* outfit2, Container_t* container)
    {
        using namespace Papyrus;

        NPCP_ASSERT(outfit2);
        NPCP_ASSERT(container);

        BContainer_t& bcontainer = container->container;
        for (size_t idx = 0, count = bcontainer.numEntries; idx < count; idx += 1) {
            BEntry_t* bentry = bcontainer.entries[idx];
            if (bentry && bentry->form && bentry->count > 0) {
                Object_Ref::Add_Item(outfit2, bentry->form, bentry->count, true);
            }
        }
    }

    Outfit2_t* Outfit2_t::Create_Member()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::MEMBER);
        outfit2->Outfit1_Cache_Variable()->None();

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Immobile()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::IMMOBILE);
        outfit2->Outfit1_Cache_Variable()->None();

        if (Vars::Do_Fill_Outfit2s()) {
            Fill(outfit2, Consts::Immobile_Outfit2_Container());
        }

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Settler()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::SETTLER);
        outfit2->Outfit1_Cache_Variable()->None();

        if (Vars::Do_Fill_Outfit2s()) {
            Fill(outfit2, Consts::Settler_Outfit2_Container());
        }

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Thrall()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::THRALL);
        outfit2->Outfit1_Cache_Variable()->None();

        if (Vars::Do_Fill_Outfit2s()) {
            Fill(outfit2, Consts::Thrall_Outfit2_Container());
        }

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Follower()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::FOLLOWER);
        outfit2->Outfit1_Cache_Variable()->None();

        if (Vars::Do_Fill_Outfit2s()) {
            Fill(outfit2, Consts::Follower_Outfit2_Container());
        }

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Vanilla()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::VANILLA);
        outfit2->Outfit1_Cache_Variable()->None();

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Default()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::DEFAULT);
        outfit2->Outfit1_Cache_Variable()->None();

        return outfit2;
    }

    void Outfit2_t::Destroy(Outfit2_t* outfit2)
    {
        NPCP_ASSERT(outfit2);

        Object_Ref::Categorize(outfit2);

        Variable_t* outfit1_cache_variable = outfit2->Outfit1_Cache_Variable();
        if (!outfit1_cache_variable->Is_None()) {
            Object_Ref::Delete_Safe(outfit1_cache_variable->Reference());
        }

        Object_Ref::Delete_Unsafe(outfit2);
    }

    Variable_t* Outfit2_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Variable_t* Outfit2_t::Type_Variable() { DEFINE_VARIABLE("p_code_create"); }
    Variable_t* Outfit2_t::Name_Variable() { DEFINE_VARIABLE("p_str_name"); }
    Variable_t* Outfit2_t::Outfit1_Cache_Variable() { DEFINE_VARIABLE("p_cache_base"); }

    Int_t Outfit2_t::Type()
    {
        Variable_t* variable = Type_Variable();
        if (!variable->Is_None()) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    String_t Outfit2_t::Name()
    {
        Variable_t* variable = Name_Variable();
        if (!variable->Is_None()) {
            return variable->String();
        } else {
            return "";
        }
    }

    Reference_t* Outfit2_t::Outfit1_Cache()
    {
        Variable_t* variable = Outfit1_Cache_Variable();
        if (!variable->Is_None()) {
            return variable->Reference();
        } else {
            return nullptr;
        }
    }

    void Outfit2_t::Open()
    {
        Virtual_Machine_t::Self()->Send_Event(this, "Put");
    }

    void Outfit2_t::Rename(String_t name)
    {
        Object_Ref::Rename(this, name);
    }

    void Outfit2_t::Apply_To(Actor_t* actor, Reference_t* pack)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(pack);

        if (Actor2::Is_Alive(actor)) {
            Party::NPCS_t::Self()->Update_And_Apply_Default_Oufit_If_Needed(actor);
            Actor2::Set_Outfit2(actor, Outfit1_Cache(), this, pack);
        }
    }

}}

namespace doticu_npcp { namespace Papyrus { namespace Outfit2 { namespace Exports {

    void Apply_To(Outfit2_t* self, Actor_t* actor, Reference_t* pack) FORWARD_VOID(Apply_To(actor, pack));

    bool Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Outfit2_t::Class_Name(), Selfless_t,       \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        #undef ADD_GLOBAL

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Outfit2_t::Class_Name(), Outfit2_t,        \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("Apply_To", 2, void, Apply_To, Actor_t*, Reference_t*);

        #undef ADD_METHOD

        return true;
    }

}}}}
