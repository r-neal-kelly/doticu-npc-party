/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "game.h"
#include "papyrus.h"
#include "utils.h"

namespace doticu_npcp { namespace Consts {

    Consts_t* Self()
    {
        static Consts_t* consts;
        return consts ? consts : consts = (Consts_t*)Game::Get_NPCP_Form(Consts::QUEST_DATA_STATIC);
    }

    void Log_Variables(Consts_t* self)
    {
        Papyrus::Object consts(self, "doticu_npcp_consts");
        consts.Log_Variables();
    }

    void Log_Defaults(Consts_t* self)
    {
        Papyrus::Object consts(self, "doticu_npcp_consts");
        consts.m_info->Log_Defaults();
    }

    void Log_Properties(Consts_t* self)
    {
        Papyrus::Object consts(self, "doticu_npcp_consts");
        consts.m_info->Log_Properties();
    }

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_consts", Consts_t,            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Consts::METHOD_, __VA_ARGS__);    \
        W

        ADD_METHOD("Log_Variables", 0, void, Log_Variables);
        ADD_METHOD("Log_Defaults", 0, void, Log_Defaults);
        ADD_METHOD("Log_Properties", 0, void, Log_Properties);

        #undef ADD_METHOD

        return true;
    }

}}}
