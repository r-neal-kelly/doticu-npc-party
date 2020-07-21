/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "party.h"
#include "party.inl"
#include "utils.h"

namespace doticu_npcp { namespace Party {

    String_t Horse_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_horse");
        return class_name;
    }

    Class_Info_t* Horse_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Variable_t* Horse_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Follower_t* Horse_t::Follower()
    {
        Followers_t* followers = Followers_t::Self();
        if (followers) {
            return followers->From_ID(ID() - Followers_t::MAX);
        } else {
            return nullptr;
        }
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

}}

namespace doticu_npcp { namespace Party { namespace Horse { namespace Exports {

    Actor_t* Actor(Horse_t* self) FORWARD_POINTER(Horse_t::Actor());

    String_t Name(Horse_t* self) FORWARD_STRING(Horse_t::Name());

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Horse_t::Class_Name(), Horse_t,            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("Actor", 0, Actor_t*, Actor);

        ADD_METHOD("Name", 0, String_t, Name);

        #undef ADD_METHOD

        return true;
    }

}}}}
