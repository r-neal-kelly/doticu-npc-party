/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "funcs.h"
#include "papyrus.inl"

#include "party/party_alias.h"
#include "party/party_movee.h"
#include "party/party_members.h"
#include "party/party_member.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Movee_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_movee");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Movee_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Movee_t* Movee_t::Self()
    {
        return reinterpret_cast<Movee_t*>(*(Consts::Funcs_Quest()->aliases.entries + 2));
    }

    Object_t* Movee_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Movee_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Movee_t::Actor_Variable() { DEFINE_VARIABLE("p_ref_actor"); }

    Actor_t* Movee_t::Actor()
    {
        return Actor_Variable()->Actor();
    }

    Int_t Movee_t::Start(Actor_t* actor)
    {
        if (Is_Unfilled()) {
            if (actor) {
                Member_t* member = Members_t::Self()->From_Actor(actor);
                if (member) {
                    if (member->Is_Mannequin()) {
                        return CODES::MANNEQUIN;
                    } else if (member->Is_Display()) {
                        return CODES::DISPLAY;
                    }
                }

                Virtual_Machine_t* vm = Virtual_Machine_t::Self();
                String_t class_name = Class_Name();
                class Arguments : public Virtual_Arguments_t {
                public:
                    Actor_t* actor;
                    Arguments(Actor_t* actor) :
                        actor(actor)
                    {
                    }
                    Bool_t operator()(Arguments_t* arguments)
                    {
                        arguments->Resize(1);
                        arguments->At(0)->Pack(actor);
                        return true;
                    }
                } arguments(actor);
                vm->Call_Method(this, class_name, "f_Create", &arguments);
                vm->Call_Method(this, class_name, "f_Register");

                return CODES::SUCCESS;
            } else {
                return CODES::ACTOR;
            }
        } else {
            return CODES::MOVEE;
        }
    }

    Int_t Movee_t::Stop()
    {
        if (Is_Filled()) {
            Virtual_Machine_t* vm = Virtual_Machine_t::Self();
            String_t class_name = Class_Name();
            vm->Call_Method(this, class_name, "f_Unregister");
            vm->Call_Method(this, class_name, "f_Destroy");
            return CODES::SUCCESS;
        } else {
            return CODES::MOVEE;
        }
    }

    void Movee_t::Reload()
    {
        Actor_t* actor = Actor();
        if (actor) {
            Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
            value_owner->Set_Actor_Value(Actor_Value_t::PARALYSIS, 0.0f);
            Actor2::Move_To_Orbit(actor, Consts::Player_Actor(), 140.0f, 0.0f);

            if (Actor2::Is_Unloaded(actor)) {
                struct VCallback : public Virtual_Callback_t {
                    Actor_t* actor;
                    Actor_Value_Owner_t* value_owner;
                    VCallback(Actor_t* actor, Actor_Value_Owner_t* value_owner) :
                        actor(actor), value_owner(value_owner)
                    {
                    }
                    void operator()(Variable_t* result)
                    {
                        if (Actor2::Is_Unloaded(actor)) {
                            Virtual_Callback_i* vcallback = new VCallback(actor, value_owner);
                            Modules::Funcs_t::Self()->Wait_Out_Of_Menu(0.2f, &vcallback);
                        } else {
                            value_owner->Set_Actor_Value(Actor_Value_t::PARALYSIS, 1.0f);
                        }
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback(actor, value_owner);
                Modules::Funcs_t::Self()->Wait_Out_Of_Menu(0.2f, &vcallback);
            } else {
                value_owner->Set_Actor_Value(Actor_Value_t::PARALYSIS, 1.0f);
            }
        }
    }

    void Movee_t::On_Cell_Change(Cell_t* new_cell, Cell_t* old_cell)
    {
        if (Actor()) {
            Reload();
        }
    }

    void Movee_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Movee_t,               \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("p_Reload", 0, void, Reload);

        #undef METHOD
    }

}}}
