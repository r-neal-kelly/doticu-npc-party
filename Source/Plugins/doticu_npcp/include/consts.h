/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Consts {

    using namespace Papyrus;

    enum Skyrim_Forms {
        FACTION_BARD_SINGER_NO_AUTOSTART    = 0x0163FA,
        FACTION_CURRENT_FOLLOWER            = 0x05C84E,
        FACTION_POTENTIAL_FOLLOWER          = 0x05C84D,
        FACTION_WI_NO_BODY_CLEANUP          = 0x09653A,
    };

    enum Dawnguard_Forms {
        FACTION_DLC1_THRALL                 = 0x0162F7,
        FACTION_DLC1_VAMPIRE_FEED_NO_CRIME  = 0x014CBD,
    };

    enum NPCP_Forms {
        FACTION_HORSE                       = 0x354111,
        FACTION_MEMBER                      = 0x091154,

        FORMLIST_MARKERS_SETTLER            = 0x00B46E,

        MARKER_STORAGE                      = 0x114F9D,

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

    Consts_t* Self();
    Object_t* Object();

    Variable_t* Variable(String_t variable_name);
    Misc_t* Misc_Variable(String_t variable_name);
    Faction_t* Faction_Variable(String_t variable_name);

    Misc_t* Member_Token();
    Misc_t* Generic_Token();
    Misc_t* Clone_Token();
    Misc_t* Immobile_Token();
    Misc_t* Settler_Token();
    Misc_t* Thrall_Token();
    Misc_t* Paralyzed_Token();
    Misc_t* Mannequin_Token();

    Misc_t* Default_Style_Token();
    Misc_t* Warrior_Style_Token();
    Misc_t* Mage_Style_Token();
    Misc_t* Archer_Style_Token();
    Misc_t* Coward_Style_Token();

    Misc_t* Mortal_Vitality_Token();
    Misc_t* Protected_Vitality_Token();
    Misc_t* Essential_Vitality_Token();
    Misc_t* Invulnerable_Vitality_Token();

    Misc_t* Display_Token();

    Misc_t* Sneak_Follower_Token();

    Faction_t* No_Singer_Bard_Autostart_Faction();
    Faction_t* Current_Follower_Faction();
    Faction_t* Potential_Follower_Faction();
    Faction_t* WI_No_Body_Cleanup_Faction();

    Faction_t* DLC1_Thrall_Faction();
    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction();

    Faction_t* Member_Faction();

    Formlist_t* Settler_Markers_Formlist();

    Reference_t* Storage_Marker();

    Weapon_t* Blank_Weapon();

    void Log_Variables(Consts_t* self);
    void Log_Defaults(Consts_t* self);
    void Log_Properties(Consts_t* self);

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Registry_t* registry);

}}}
