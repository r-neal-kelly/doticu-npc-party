/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_follower.h"
#include "party/party_horse.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Horse_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_horse");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Horse_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Variable_t* Horse_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Variable_t* Horse_t::Actor_Variable() { DEFINE_VARIABLE("p_ref_actor"); }
    Variable_t* Horse_t::Follower_Variable() { DEFINE_VARIABLE("p_ref_follower"); }

    Actor_t* Horse_t::Actor()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor_Variable()->Actor();
        if (actor == nullptr) {
            actor = Alias_t::Actor();
            NPCP_ASSERT(actor);
            Actor_Variable()->Pack(actor);
        }
        return actor;
    }

    Follower_t* Horse_t::Follower()
    {
        NPCP_ASSERT(Is_Filled());
        Follower_t* follower = static_cast<Follower_t*>(Follower_Variable()->Alias());
        NPCP_ASSERT(follower);
        return follower;
    }

    Cell_t* Horse_t::Cell()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor()->parentCell;
    }

    String_t Horse_t::Base_Name()
    {
        return Actor2::Get_Base_Name(Actor());
    }

    String_t Horse_t::Reference_Name()
    {
        return Actor2::Get_Ref_Name(Actor());
    }

    String_t Horse_t::Name()
    {
        return Actor2::Get_Name(Actor());
    }

    Bool_t Horse_t::Is_Alive()
    {
        return Is_Filled() && Actor2::Is_Alive(Actor());
    }

    Bool_t Horse_t::Is_Dead()
    {
        return Is_Filled() && Actor2::Is_Dead(Actor());
    }

    void Horse_t::Fill(Actor_t* actor, Follower_t* follower)
    {
        struct Callback : public Virtual_Callback_t {
        public:
            Horse_t* self;
            Actor_t* actor;
            Follower_t* follower;
            Callback(Horse_t* self, Actor_t* actor, Follower_t* follower) :
                self(self), actor(actor), follower(follower)
            {
            }
            void operator()(Variable_t* result)
            {
                self->Create(actor, follower);
            }
        };
        Virtual_Callback_i* callback = new Callback(this, actor, follower);

        Alias_t::Fill(actor, &callback);
    }

    void Horse_t::Unfill(Virtual_Callback_i** callback)
    {
        Destroy();
        Alias_t::Unfill(callback);
    }

    void Horse_t::Create(Actor_t* actor, Follower_t* follower)
    {
        Actor_Variable()->Pack(actor);
        Follower_Variable()->Pack(follower);

        Groom();
    }

    void Horse_t::Destroy()
    {
        Follower_Variable()->None(Follower_t::Class_Info());
        Actor_Variable()->None(Class_Info_t::Fetch(Actor_t::kTypeID, true));
    }

    Int_t Horse_t::Groom()
    {
        if (Is_Filled()) {
            Actor_t* actor = Actor();
            Enforce_Groom(actor);
            Actor2::Evaluate_Package(actor);

            return CODES::SUCCESS;
        } else {
            return CODES::HORSE;
        }
    }

    void Horse_t::Enforce_Groom(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Actor2::Ignore_Friendly_Hits(actor);
        Actor2::Hide_From_Stealth_Eye(actor);
        Actor2::Talks_To_Player(actor, false);

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
        value_owner->Set_Actor_Value(Actor_Value_t::SPEED_MULT, Follower_t::MAX_UNSNEAK_SPEED);

        if (Is_Dead()) {
            Actor2::Resurrect(actor, false);
        }

        if (Cell() != Follower()->Cell()) {
            Object_Ref::Move_To_Orbit(actor, Follower()->Actor(), 140.0f, -90.0f);
        }

        if (Actor2::Get_Mounted_Actor(actor) != Follower()->Actor()) {
            Formlist_t* formlist = Consts::Is_Saddler_Sitting_Globals_Formlist();
            Global_t* global = static_cast<Global_t*>(*(formlist->forms.entries + Follower()->ID()));
            global->value = 0.0f; // don't know if this needs MarkChanged()
        }

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "p_Enable");
    }

    Int_t Horse_t::Ungroom()
    {
        if (Is_Filled()) {
            Actor_t* actor = Actor();
            Enforce_Non_Groom(actor);
            Actor2::Evaluate_Package(actor);

            return CODES::SUCCESS;
        } else {
            return CODES::HORSE;
        }
    }

    void Horse_t::Enforce_Non_Groom(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        class Callback : public Virtual_Callback_t {
        public:
            Actor_t* actor;
            Callback(Actor_t* actor) :
                actor(actor)
            {
            }
            void operator()(Variable_t* result)
            {
                Object_Ref::Move_To_Orbit(actor, Consts::Storage_Marker(), 0.0f, 0.0f);
            }
        };
        Virtual_Callback_i* callback = new Callback(actor);
        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "p_Disable", nullptr, &callback);
    }

    void Horse_t::Enforce()
    {
        if (Is_Filled() && Is_Alive()) {
            Actor_t* actor = Actor();

            Enforce_Groom(actor);

            Actor2::Evaluate_Package(actor);
        }
    }

    void Horse_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Horse_t,               \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("Actor", 0, Actor_t*, Actor);
        METHOD("Name", 0, String_t, Name);

        #undef METHOD
    }

}}}
