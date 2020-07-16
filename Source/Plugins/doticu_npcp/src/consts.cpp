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
        static Consts_t* consts = static_cast<Consts_t*>(Game::NPCP_Form(QUEST_DATA_STATIC));
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

    Misc_t* Misc_Variable(String_t variable_name)
    {
        Variable_t* variable = Variable(variable_name);
        if (variable) {
            return variable->Misc();
        } else {
            return nullptr;
        }
    }

    Faction_t* Faction_Variable(String_t variable_name)
    {
        Variable_t* variable = Variable(variable_name);
        if (variable) {
            return variable->Faction();
        } else {
            return nullptr;
        }
    }

    Misc_t* Member_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_MEMBER));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Generic_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_GENERIC));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Clone_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_CLONE));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Default_Style_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_DEFAULT));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Warrior_Style_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_WARRIOR));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Mage_Style_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_MAGE));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Archer_Style_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_ARCHER));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Coward_Style_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_COWARD));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Mortal_Vitality_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_MORTAL));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Protected_Vitality_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_PROTECTED));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Essential_Vitality_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_ESSENTIAL));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Invulnerable_Vitality_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_INVULNERABLE));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Display_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_DISPLAY));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Misc_t* Sneak_Follower_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_FOLLOWER_SNEAK));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* No_Singer_Bard_Autostart_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_BARD_SINGER_NO_AUTOSTART));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* Current_Follower_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_CURRENT_FOLLOWER));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* Potential_Follower_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_POTENTIAL_FOLLOWER));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* WI_No_Body_Cleanup_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_WI_NO_BODY_CLEANUP));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* DLC1_Thrall_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::Dawnguard_Form(FACTION_DLC1_THRALL));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::Dawnguard_Form(FACTION_DLC1_VAMPIRE_FEED_NO_CRIME));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* Horse_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::NPCP_Form(FACTION_HORSE));
        NPCP_ASSERT(value != nullptr);
        return value;
    }

    Faction_t* Member_Faction()
    {
        static Faction_t* value = static_cast<Faction_t*>(Game::NPCP_Form(FACTION_MEMBER));
        NPCP_ASSERT(value != nullptr);
        return value;
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
