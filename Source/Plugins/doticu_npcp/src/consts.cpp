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

    Variable_t* Variable(String_t variable_name)
    {
        Object_t* object = Object();
        if (object) {
            return object->Variable(variable_name);
        } else {
            return nullptr;
        }
    }

    static inline Misc_t* Misc_Variable(String_t variable_name)
    {
        Variable_t* variable = Variable(variable_name);
        if (variable) {
            return variable->Misc();
        } else {
            return nullptr;
        }
    }

    // it would be faster to just get the actual formid and use that instead.
    Misc_t* Default_Style_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_STYLE_DEFAULT");
        return Misc_Variable(variable_name);
    }

    Misc_t* Warrior_Style_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_STYLE_WARRIOR");
        return Misc_Variable(variable_name);
    }

    Misc_t* Mage_Style_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_STYLE_MAGE");
        return Misc_Variable(variable_name);
    }

    Misc_t* Archer_Style_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_STYLE_ARCHER");
        return Misc_Variable(variable_name);
    }

    Misc_t* Coward_Style_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_STYLE_COWARD");
        return Misc_Variable(variable_name);
    }

    Misc_t* Mortal_Vitality_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_VITALITY_MORTAL");
        return Misc_Variable(variable_name);
    }

    Misc_t* Protected_Vitality_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_VITALITY_PROTECTED");
        return Misc_Variable(variable_name);
    }

    Misc_t* Essential_Vitality_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_VITALITY_ESSENTIAL");
        return Misc_Variable(variable_name);
    }

    Misc_t* Invulnerable_Vitality_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_VITALITY_INVULNERABLE");
        return Misc_Variable(variable_name);
    }

    Misc_t* Display_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_DISPLAY");
        return Misc_Variable(variable_name);
    }

    Misc_t* Sneak_Follower_Token()
    {
        static const String_t variable_name = String_t("p_TOKEN_FOLLOWER_SNEAK");
        return Misc_Variable(variable_name);
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
