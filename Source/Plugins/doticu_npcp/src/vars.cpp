/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64_common/Relocation.h"

#include "consts.h"
#include "game.h"
#include "papyrus.h"
#include "utils.h"
#include "vars.h"

#include "papyrus.inl"

using namespace doticu_npcp::Papyrus;

namespace doticu_npcp { namespace Vars {

    Vars_t* Self()
    {
        static Vars_t* vars;
        return vars ? vars : vars = (Vars_t*)Game::Get_NPCP_Form(Consts::QUEST_DATA_DYNAMIC);
    }

    Object_t* Object()
    {
        static Object_t* object = Object_t::Fetch(Self(), "doticu_npcp_vars");
        return object;
    }

    Variable_t* Variable(String_t variable_name)
    {
        Object_t* object = Object();
        if (object) {
            return object->Variable(variable_name);
        } else {
            return nullptr;
        }
    }

    Variable_t* Property(String_t property_name)
    {
        Object_t* object = Object();
        if (object) {
            return object->Property(property_name);
        } else {
            return nullptr;
        }
    }

    String_t String_Variable(String_t variable_name)
    {
        Variable_t* variable = Variable(variable_name);
        if (variable) {
            return variable->String();
        } else {
            return "";
        }
    }

    void Log_Variables(Vars_t* self)
    {
        Object_t* object = Object();
        if (object) {
            object->Log_Variables();
        }
    }

    void Log_Properties(Vars_t* self)
    {
        Object_t* object = Object();
        if (object) {
            object->info->Log_Property_Infos();
        }
    }

}}

namespace doticu_npcp { namespace Vars { namespace Exports {

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_vars", Vars_t,                \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Vars::METHOD_, __VA_ARGS__);      \
        W

        ADD_METHOD("Log_Variables", 0, void, Log_Variables);
        ADD_METHOD("Log_Properties", 0, void, Log_Properties);

        #undef ADD_METHOD

        return true;
    }

}}}
