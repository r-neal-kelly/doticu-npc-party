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

using namespace doticu_npcp::Papyrus;

namespace doticu_npcp { namespace Vars {

    Vars_t* Self()
    {
        static Vars_t* vars;
        return vars ? vars : vars = (Vars_t*)Game::Get_NPCP_Form(Consts::QUEST_DATA_DYNAMIC);
    }

    Papyrus::Variable_t* Variable(Vars_t* self, Papyrus::String_t variable_name)
    {
        Papyrus::Object vars(self, "doticu_npcp_vars");
        return vars.Variable(variable_name);
    }

    Papyrus::Variable_t* Property(Vars_t* self, Papyrus::String_t property_name)
    {
        Papyrus::Object vars(self, "doticu_npcp_vars");
        return vars.Property(property_name);
    }

    void Log_Variables(Vars_t* self)
    {
        Papyrus::Object vars(self, "doticu_npcp_vars");
        vars.Log_Variables();
    }

    void Log_Properties(Vars_t* self)
    {
        Papyrus::Object vars(self, "doticu_npcp_vars");
        vars.m_info->Log_Properties();
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
