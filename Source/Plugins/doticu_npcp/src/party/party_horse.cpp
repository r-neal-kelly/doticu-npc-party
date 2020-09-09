/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "funcs.h"
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
    Variable_t* Horse_t::Name_Variable() { DEFINE_VARIABLE("p_str_name"); }

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
        NPCP_ASSERT(Is_Filled());
        return Actor2::Get_Base_Name(Actor());
    }

    String_t Horse_t::Reference_Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Actor2::Get_Ref_Name(Actor());
    }

    String_t Horse_t::Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Name_Variable()->String();
    }

    Bool_t Horse_t::Is_Ready()
    {
        return Is_Filled() && Actor_Variable()->Has_Object();
    }

    Bool_t Horse_t::Is_Alive()
    {
        return Is_Filled() && Actor2::Is_Alive(Actor());
    }

    Bool_t Horse_t::Is_Dead()
    {
        return Is_Filled() && Actor2::Is_Dead(Actor());
    }

    void Horse_t::Fill(Actor_t* actor, Follower_t* follower, Callback_t<Int_t, Horse_t*>** callback)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(follower);
        NPCP_ASSERT(callback);
        NPCP_ASSERT(Is_Unfilled());

        struct VCallback : public Virtual_Callback_t {
        public:
            Horse_t* self;
            Actor_t* actor;
            Follower_t* follower;
            Callback_t<Int_t, Horse_t*>* callback;
            VCallback(Horse_t* self, Actor_t* actor, Follower_t* follower, Callback_t<Int_t, Horse_t*>* callback) :
                self(self), actor(actor), follower(follower), callback(callback)
            {
                NPCP_ASSERT(callback);
            }
            void operator()(Variable_t* result)
            {
                self->Create(actor, follower);
                callback->operator()(CODES::SUCCESS, self);
                delete callback;
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this, actor, follower, *callback);
        Alias_t::Fill(actor, &vcallback);
    }

    void Horse_t::Unfill(Callback_t<Int_t, Follower_t*>** callback)
    {
        NPCP_ASSERT(callback);
        NPCP_ASSERT(Is_Filled());

        struct Destroy_Callback : public Callback_t<> {
            Horse_t* horse;
            Actor_t* actor;
            Follower_t* follower;
            Callback_t<Int_t, Follower_t*>* user_callback;
            Destroy_Callback(Horse_t* horse, Actor_t* actor, Follower_t* follower, Callback_t<Int_t, Follower_t*>* user_callback) :
                horse(horse), actor(actor), follower(follower), user_callback(user_callback)
            {
            }
            void operator()()
            {
                struct VCallback : public Virtual_Callback_t {
                public:
                    Actor_t* actor;
                    Follower_t* follower;
                    Callback_t<Int_t, Follower_t*>* user_callback;
                    VCallback(Actor_t* actor, Follower_t* follower, Callback_t<Int_t, Follower_t*>* user_callback) :
                        actor(actor), follower(follower), user_callback(user_callback)
                    {
                        NPCP_ASSERT(user_callback);
                    }
                    void operator()(Variable_t* result)
                    {
                        Object_Ref::Delete_Safe(actor);
                        user_callback->operator()(CODES::SUCCESS, follower);
                        delete user_callback;
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback(actor, follower, user_callback);
                horse->Alias_t::Unfill(&vcallback);
            }
        };
        Callback_t<>* destroy_callback = new Destroy_Callback(this, Actor(), Follower(), *callback);
        Destroy(&destroy_callback);
    }

    void Horse_t::Create(Actor_t* actor, Follower_t* follower)
    {
        Actor_Variable()->Pack(actor);
        Follower_Variable()->Pack(follower);
        Name_Variable()->String(Actor2::Get_Name(actor));

        Groom();
    }

    void Horse_t::Destroy(Callback_t<>** callback)
    {
        NPCP_ASSERT(callback);

        struct Enforce_Non_Groom_Callback : public Callback_t<> {
            Horse_t* horse;
            Callback_t<>* user_callback;
            Enforce_Non_Groom_Callback(Horse_t* horse, Callback_t<>* user_callback) :
                horse(horse), user_callback(user_callback)
            {
            }
            void operator()()
            {
                horse->Name_Variable()->String("");
                horse->Follower_Variable()->None(Follower_t::Class_Info());
                horse->Actor_Variable()->None(Class_Info_t::Fetch(Actor_t::kTypeID, true));

                user_callback->operator()();
                delete user_callback;
            }
        };
        Callback_t<>* enforce_non_groom_callback = new Enforce_Non_Groom_Callback(this, *callback);
        Enforce_Non_Groom(Actor(), enforce_non_groom_callback);
    }

    Int_t Horse_t::Groom()
    {
        if (Is_Ready()) {
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

        Follower_t* follower = Follower();
        Actor_t* follower_actor = follower->Actor();

        if (Is_Dead()) {
            Actor2::Resurrect(actor, false);
        }

        if (Cell() != follower->Cell()) {
            Object_Ref::Move_To_Orbit(actor, follower_actor, 140.0f, -90.0f);
        }

        Actor_t* mounted_actor = Actor2::Get_Mounted_Actor(actor);
        if (mounted_actor != follower_actor) {
            Formlist_t* formlist = Consts::Is_Saddler_Sitting_Globals_Formlist();
            Global_t* global = static_cast<Global_t*>(*(formlist->forms.entries + follower->ID()));
            global->value = 0.0f;
            Object_Ref::Move_To_Orbit(mounted_actor, actor, 140.0f, 180.0f);
        }

        Actor2::Owner(actor, Actor2::Dynamic_Base(follower_actor));

        Object_Ref::Enable(actor, false);
    }

    Int_t Horse_t::Ungroom()
    {
        if (Is_Ready()) {
            Actor_t* actor = Actor();
            Enforce_Non_Groom(actor);
            Actor2::Evaluate_Package(actor);

            return CODES::SUCCESS;
        } else {
            return CODES::HORSE;
        }
    }

    void Horse_t::Enforce_Non_Groom(Actor_t* actor, Callback_t<>* callback)
    {
        NPCP_ASSERT(actor);

        Actor_t* mounted_actor = Actor2::Get_Mounted_Actor(actor);
        if (mounted_actor) {
            struct VCallback : public Virtual_Callback_t {
                Horse_t* horse;
                Actor_t* actor;
                Callback_t<>* callback;
                VCallback(Horse_t* horse, Actor_t* actor, Callback_t<>* callback) :
                    horse(horse), actor(actor), callback(callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    horse->Enforce_Non_Groom(actor, callback);
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this, actor, callback);
            Modules::Funcs_t::Self()->Wait_Out_Of_Menu(1.0f, &vcallback);
        } else {
            if (Is_Ready()) {
                Global_t* is_saddler_sitting_global = static_cast<Global_t*>
                    (Consts::Is_Saddler_Sitting_Globals_Formlist()->forms.entries[Follower()->ID()]);
                is_saddler_sitting_global->value = 0.0f;
                Object_Ref::Move_To_Orbit(actor, Consts::Storage_Marker(), 0.0f, 0.0f);
                actor->Disable();
            }

            if (callback) {
                callback->operator()();
                delete callback;
            }
        }
    }

    void Horse_t::Enforce()
    {
        if (Is_Filled() && Is_Alive()) {
            Actor_t* actor = Actor();

            Enforce_Groom(actor);

            Actor2::Evaluate_Package(actor);
        }
    }

    Int_t Horse_t::Rename(String_t new_name)
    {
        if (Is_Filled()) {
            Name_Variable()->String(new_name);

            Actor_t* actor = Actor();
            Enforce_Name(actor, new_name);
            Actor2::Evaluate_Package(actor);

            return CODES::SUCCESS;
        } else {
            return CODES::MEMBER;
        }
    }

    void Horse_t::Enforce_Name(Actor_t* actor, String_t name)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(actor);
        NPCP_ASSERT(name);

        Object_Ref::Rename(actor, name);
    }

    void Horse_t::On_Activate(Reference_t* activator)
    {
        if (activator && activator->formType == kFormType_Character) {
            Actor_t* activator_actor = static_cast<Actor_t*>(activator);
            Follower_t* follower = Follower();
            if (follower && follower->Actor() == activator_actor) {
                Global_t* is_saddler_sitting_global = static_cast<Global_t*>
                    (Consts::Is_Saddler_Sitting_Globals_Formlist()->forms.entries[follower->ID()]);
                is_saddler_sitting_global->value = 1.0f;
                Actor2::Evaluate_Package(activator_actor);
            }
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

        METHOD("OnActivate", 1, void, On_Activate, Reference_t*);

        #undef METHOD
    }

}}}
