/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "game.h"
#include "utils.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Consts {

    Consts_t* Self()
    {
        static Consts_t* consts = static_cast<Consts_t*>(Game::Get_NPCP_Form(Consts::QUEST_DATA_STATIC));
        return consts;
    }

    Object_t* Object()
    {
        static Object_t* object = Object_t::Fetch(Self(), "doticu_npcp_consts");
        return object;
    }

    void Log_Variables(Consts_t* self)
    {
        Object_t* object = Object();
        if (object) {
            object->Log_Variables();
        }
    }

    void Log_Defaults(Consts_t* self)
    {
        Object_t* object = Object();
        if (object) {
            object->info->Log_Default_Infos();
        }
    }

    void Log_Properties(Consts_t* self)
    {
        Object_t* object = Object();
        if (object) {
            object->info->Log_Property_Infos();
        }
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
