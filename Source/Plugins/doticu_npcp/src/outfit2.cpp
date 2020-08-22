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
                Object_Ref::Add_Item(outfit2, bentry->form, bentry->count, true); // this needs to be handled better
            }
        }
    }

    Outfit2_t* Outfit2_t::Create_Member(Actor_t* actor, Reference_t* pack)
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));
        NPCP_ASSERT(outfit2);

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::MEMBER);
        outfit2->Outfit1_Cache_Variable()->None();

        Actor2::Split_Inventory(actor, outfit2, pack);

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Immobile()
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));
        NPCP_ASSERT(outfit2);

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
        NPCP_ASSERT(outfit2);

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
        NPCP_ASSERT(outfit2);

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
        NPCP_ASSERT(outfit2);

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
        NPCP_ASSERT(outfit2);

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::VANILLA);
        outfit2->Outfit1_Cache_Variable()->None();

        return outfit2;
    }

    Outfit2_t* Outfit2_t::Create_Default(Actor_t* actor)
    {
        Outfit2_t* outfit2 = static_cast<Outfit2_t*>
            (Object_Ref::Place_At_Me(Consts::Storage_Marker(), Consts::Outfit2_Container(), 1));
        NPCP_ASSERT(outfit2);

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::DEFAULT);
        outfit2->Outfit1_Cache_Variable()->None();

        Actor2::Cache_BContainer(actor, outfit2);

        struct Callback : public Virtual_Callback_t {
            Outfit2_t* outfit2;
            Callback(Outfit2_t* outfit2) :
                outfit2(outfit2)
            {
            }
            virtual void operator()(Variable_t*)
            {
                Object_Ref::Remove_Unwearables(outfit2);
            }
        };
        Virtual_Callback_i* callback = new Callback(outfit2);

        Object_Ref::Add_Item_And_Callback(outfit2, Consts::Gold(), 1, false, &callback);

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

        outfit2->Type_Variable()->Int(CODES::OUTFIT2::DELETED);
        Object_Ref::Delete_Unsafe(outfit2);
    }

    Variable_t* Outfit2_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Variable_t* Outfit2_t::Type_Variable() { DEFINE_VARIABLE("p_code_create"); }
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

    Reference_t* Outfit2_t::Outfit1_Cache()
    {
        Variable_t* variable = Outfit1_Cache_Variable();
        if (variable->Has_Object()) {
            return variable->Reference();
        } else {
            return nullptr;
        }
    }

    Reference_t* Outfit2_t::Reset_Outfit1_Cache()
    {
        Variable_t* variable = Outfit1_Cache_Variable();

        if (variable->Has_Object()) {
            Reference_t* old_cache = variable->Reference();
            Object_Ref::Delete_Safe(old_cache);
        }

        Reference_t* new_cache = Object_Ref::Create_Container();
        variable->Pack(new_cache);

        return new_cache;
    }

    Bool_t Outfit2_t::Has_Outfit1_Cache()
    {
        return Outfit1_Cache_Variable()->Has_Object();
    }

    Bool_t Outfit2_t::Hasnt_Outfit1_Cache()
    {
        return !Outfit1_Cache_Variable()->Has_Object();
    }

    void Outfit2_t::Open(String_t outfit_name, Virtual_Callback_i** callback)
    {
        NPCP_ASSERT(outfit_name);

        Object_Ref::Rename(this, outfit_name);
        Object_Ref::Open_Container(this, callback);
    }

    void Outfit2_t::Apply_To(Actor_t* actor, Reference_t* pack, Outfit_t* outfit1_to_apply)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(pack);

        if (Actor2::Is_Alive(actor)) {
            if (outfit1_to_apply) {
                Actor2::Set_Outfit_Basic(actor, outfit1_to_apply, false, false);
            }

            class Callback : public Virtual_Callback_t {
            public:
                Outfit2_t* outfit2;
                Actor_t* actor;
                Reference_t* pack;
                Callback(Outfit2_t* outfit2, Actor_t* actor, Reference_t* pack) :
                    outfit2(outfit2), actor(actor), pack(pack)
                {
                }
                void operator()(Variable_t* result)
                {
                    Actor2::Leave_Player_Team(actor);
                    Actor2::Set_Outfit2(actor, outfit2->Outfit1_Cache(), outfit2, pack);
                    Actor2::Join_Player_Team(actor);
                    Actor2::Update_Equipment(actor);
                }
            };
            Virtual_Callback_i* callback = new Callback(this, actor, pack);
            Object_Ref::Remove_Item_And_Callback(this, Consts::Blank_Weapon(), 0, false, nullptr, &callback);
        }
    }

    void Outfit2_t::Cache_Static_Outfit1(Outfit_t* outfit)
    {
        NPCP_ASSERT(outfit);

        Reference_t* outfit1_cache = Reset_Outfit1_Cache();
        Form_t* linchpin = Consts::Blank_Armor();
        for (size_t idx = 0, count = outfit->armorOrLeveledItemArray.count; idx < count; idx += 1) {
            Form_t* form = outfit->armorOrLeveledItemArray.entries[idx];
            if (form != linchpin) {
                Object_Ref::Add_Item(outfit1_cache, form, 1, true);
            }
        }
    }

    void Outfit2_t::Cache_Dynamic_Outfit1(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Reference_t* outfit1_cache = Reset_Outfit1_Cache();
        Actor2::Cache_Worn(actor, outfit1_cache);
    }

}}

namespace doticu_npcp { namespace Papyrus { namespace Outfit2 { namespace Exports {

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

        #undef ADD_METHOD

        return true;
    }

}}}}
