/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "game.h"
#include "utils.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Consts {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_consts");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Consts_t* Self()
    {
        return static_cast<Consts_t*>(Static_Data_Quest());
    }

    Object_t* Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    enum Skyrim_Forms {
        FACTION_BARD_SINGER_NO_AUTOSTART    = 0x0163FA,
        FACTION_CURRENT_FOLLOWER            = 0x05C84E,
        FACTION_POTENTIAL_FOLLOWER          = 0x05C84D,
        FACTION_WI_NO_BODY_CLEANUP          = 0x09653A,

        STATIC_MARKER_X                     = 0x00003B,
    };

    Faction_t* No_Bard_Singer_Autostart_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_BARD_SINGER_NO_AUTOSTART));
        NPCP_ASSERT(value);
        return value;
    }

    Faction_t* Current_Follower_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_CURRENT_FOLLOWER));
        NPCP_ASSERT(value);
        return value;
    }

    Faction_t* Potential_Follower_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_POTENTIAL_FOLLOWER));
        NPCP_ASSERT(value);
        return value;
    }

    Faction_t* WI_No_Body_Cleanup_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::Skyrim_Form(FACTION_WI_NO_BODY_CLEANUP));
        NPCP_ASSERT(value);
        return value;
    }

    Static_t* Marker_X_Static()
    {
        static Static_t* value =
            static_cast<Static_t*>(Game::Skyrim_Form(STATIC_MARKER_X));
        NPCP_ASSERT(value);
        return value;
    }

    enum Dawnguard_Forms {
        FACTION_DLC1_THRALL                 = 0x0162F7,
        FACTION_DLC1_VAMPIRE_FEED_NO_CRIME  = 0x014CBD,
    };

    Faction_t* DLC1_Thrall_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::Dawnguard_Form(FACTION_DLC1_THRALL));
        NPCP_ASSERT(value);
        return value;
    }

    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::Dawnguard_Form(FACTION_DLC1_VAMPIRE_FEED_NO_CRIME));
        NPCP_ASSERT(value);
        return value;
    }

    enum NPCP_Forms {
        FACTION_HORSE                       = 0x354111,
        FACTION_MEMBER                      = 0x091154,

        FORMLIST_MARKERS_SETTLER            = 0x00B46E,

        MARKER_STORAGE                      = 0x114F9D,

        MISC_VECTOR_FORM                    = 0x15C1B2,

        QUEST_DATA_STATIC                   = 0x0FBA9A,
        QUEST_DATA_DYNAMIC                  = 0x003DFF,
        QUEST_MEMBERS                       = 0x00184C,
        QUEST_FOLLOWERS                     = 0x000D83,
        QUEST_CONTROL                       = 0x000D7F,

        TOKEN_BANISHED                      = 0x003DFD,
        TOKEN_CLONE                         = 0x003DFC,
        TOKEN_DISPLAY                       = 0x13D7AC,
        TOKEN_FOLLOWER                      = 0x000D84,
        TOKEN_FOLLOWER_SNEAK                = 0x000D85,
        TOKEN_GENERIC                       = 0x003DFE,
        TOKEN_GREETER                       = 0x057384,
        TOKEN_IMMOBILE                      = 0x000D77,
        TOKEN_MANNEQUIN                     = 0x264F42,
        TOKEN_MEMBER                        = 0x000D75,
        TOKEN_MOVEE                         = 0x1612B3,
        TOKEN_PARALYZED                     = 0x12E4A7,
        TOKEN_REANIMATED                    = 0x1E4E9D,
        TOKEN_RETREATER                     = 0x2F3D00,
        TOKEN_SADDLER                       = 0x34F000,
        TOKEN_SETTLER                       = 0x000D73,
        TOKEN_STYLE_ARCHER                  = 0x0A045E,
        TOKEN_STYLE_COWARD                  = 0x2D56F3,
        TOKEN_STYLE_DEFAULT                 = 0x0A045D,
        TOKEN_STYLE_MAGE                    = 0x0A045F,
        TOKEN_STYLE_WARRIOR                 = 0x0A0460,
        TOKEN_THRALL                        = 0x011E90,
        TOKEN_VITALITY_ESSENTIAL            = 0x0A0459,
        TOKEN_VITALITY_INVULNERABLE         = 0x0A045C,
        TOKEN_VITALITY_MORTAL               = 0x0A045B,
        TOKEN_VITALITY_PROTECTED            = 0x0A045A,

        WEAPON_BLANK                        = 0x0C8D65,
    };

    Faction_t* Member_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::NPCP_Form(FACTION_MEMBER));
        NPCP_ASSERT(value);
        return value;
    }

    Faction_t* Horse_Faction()
    {
        static Faction_t* value =
            static_cast<Faction_t*>(Game::NPCP_Form(FACTION_HORSE));
        NPCP_ASSERT(value);
        return value;
    }

    Formlist_t* Settler_Markers_Formlist()
    {
        static Formlist_t* value =
            static_cast<Formlist_t*>(Game::NPCP_Form(FORMLIST_MARKERS_SETTLER));
        NPCP_ASSERT(value);
        NPCP_ASSERT(value->forms.count == MAX_MEMBERS);
        return value;
    }

    Misc_t* Member_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_MEMBER));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Generic_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_GENERIC));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Clone_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_CLONE));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Immobile_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_IMMOBILE));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Settler_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_SETTLER));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Thrall_Token()
    {
        static Misc_t* value = static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_THRALL));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Paralyzed_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_PARALYZED));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Mannequin_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_MANNEQUIN));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Display_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_DISPLAY));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Default_Style_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_DEFAULT));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Warrior_Style_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_WARRIOR));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Mage_Style_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_MAGE));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Archer_Style_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_ARCHER));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Coward_Style_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_STYLE_COWARD));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Mortal_Vitality_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_MORTAL));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Protected_Vitality_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_PROTECTED));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Essential_Vitality_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_ESSENTIAL));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Invulnerable_Vitality_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_VITALITY_INVULNERABLE));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Sneak_Follower_Token()
    {
        static Misc_t* value =
            static_cast<Misc_t*>(Game::NPCP_Form(TOKEN_FOLLOWER_SNEAK));
        NPCP_ASSERT(value);
        return value;
    }

    Misc_t* Form_Vector()
    {
        static Misc_t* value = static_cast<Misc_t*>
            (Game::NPCP_Form(MISC_VECTOR_FORM));
        NPCP_ASSERT(value);
        return value;
    }

    Quest_t* Static_Data_Quest()
    {
        static Quest_t* value =
            static_cast<Quest_t*>(Game::NPCP_Form(QUEST_DATA_STATIC));
        NPCP_ASSERT(value);
        return value;
    }

    Quest_t* Dynamic_Data_Quest()
    {
        static Quest_t* value =
            static_cast<Quest_t*>(Game::NPCP_Form(QUEST_DATA_DYNAMIC));
        NPCP_ASSERT(value);
        return value;
    }

    Quest_t* Members_Quest()
    {
        static Quest_t* value =
            static_cast<Quest_t*>(Game::NPCP_Form(QUEST_MEMBERS));
        NPCP_ASSERT(value);
        return value;
    }

    Quest_t* Followers_Quest()
    {
        static Quest_t* value =
            static_cast<Quest_t*>(Game::NPCP_Form(QUEST_FOLLOWERS));
        NPCP_ASSERT(value);
        return value;
    }

    Quest_t* Control_Quest()
    {
        static Quest_t* value =
            static_cast<Quest_t*>(Game::NPCP_Form(QUEST_CONTROL));
        NPCP_ASSERT(value);
        return value;
    }

    Reference_t* Storage_Marker()
    {
        static Reference_t* value =
            static_cast<Reference_t*>(Game::NPCP_Form(MARKER_STORAGE));
        NPCP_ASSERT(value);
        return value;
    }

    Weapon_t* Blank_Weapon()
    {
        static Weapon_t* value =
            static_cast<Weapon_t*>(Game::NPCP_Form(WEAPON_BLANK));
        NPCP_ASSERT(value);
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
