/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "game.h"
#include "utils.h"

#include "papyrus.inl"

/*
    We us macros in this module, because we want the
    assert to show us which variable is actually nullptr,
    instead of it being ambiguous through a template.
*/

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

    #define FORM(MOD_, TYPE_, MOD_ID_)              \
    {                                               \
        static TYPE_* value = static_cast<TYPE_*>   \
            (Game::MOD_(MOD_ID_));                  \
        NPCP_ASSERT(value);                         \
        return value;                               \
    }

    enum Skyrim_Forms {
        // Skyrim Actors
        ACTOR_PLAYER                                = 0x000014,

        // Skyrim Armors
        ARMOR_BELTED_TUNIC                          = 0x01BE1A,
        ARMOR_GOLD_RING                             = 0x01CF2B,

        // Skyrim Effect Shaders
        EFFECT_SHADER_REANIMATE                     = 0x075272,

        // Skyrim Factions
        FACTION_BARD_SINGER_NO_AUTOSTART            = 0x0163FA,
        FACTION_CURRENT_FOLLOWER                    = 0x05C84E,
        FACTION_PLAYER_FOLLOWER                     = 0x084D1B,
        FACTION_POTENTIAL_FOLLOWER                  = 0x05C84D,
        FACTION_WI_NO_BODY_CLEANUP                  = 0x09653A,

        // Skyrim Globals
        GLOBAL_PLAYER_FOLLOWER_COUNT                = 0x0BCC98,

        // Skyrim Keywords
        KEYWORD_MAGIC_DAMAGE_FIRE                   = 0x01CEAD,
        KEYWORD_MAGIC_DAMAGE_FROST                  = 0x01CEAE,
        KEYWORD_MAGIC_DAMAGE_SHOCK                  = 0x01CEAF,
        KEYWORD_MAGIC_VAMPIRE_DRAIN                 = 0x101BDE,
        KEYWORD_VAMPIRE                             = 0x0A82BB,
        KEYWORD_VENDOR_ITEM_STAFF                   = 0x0937A4,
        KEYWORD_WEAPON_TYPE_SWORD                   = 0x01E711,
        KEYWORD_WEAPON_TYPE_GREATSWORD              = 0x06D931,
        KEYWORD_WEAPON_TYPE_WARAXE                  = 0x01E712,
        KEYWORD_WEAPON_TYPE_BATTLEAXE               = 0x06D932,
        KEYWORD_WEAPON_TYPE_MACE                    = 0x01E714,
        KEYWORD_WEAPON_TYPE_WARHAMMER               = 0x06D930,
        KEYWORD_WEAPON_TYPE_DAGGER                  = 0x01E713,
        KEYWORD_WEAPON_TYPE_BOW                     = 0x01E715,
        KEYWORD_WEAPON_TYPE_STAFF                   = 0x01E716,

        // Skyrim Miscs
        MISC_GOLD                                   = 0x00000F,

        // Skyrim Perks
        PERK_VAMPIRE_FEED                           = 0x0CF02C,

        // Skyrim Quests
        QUEST_BARD_SONGS                            = 0x074A55,
        QUEST_DIALOGUE_FOLLOWER                     = 0x0750BA,
        QUEST_PLAYER_VAMPIRE                        = 0x0EAFD5,
        QUEST_WI_CHANGE_LOCATION_01                 = 0x0350F4,
        QUEST_WI_REMOVE_ITEM_04                     = 0x034DAB,

        // Skyrim Reference Markers
        REFERENCE_MARKER_GO_BACK_SAFE               = 0x01BDF3,

        // Skyrim Statics
        STATIC_MARKER_X                             = 0x00003B,
    };

    #define SKYRIM_FORM(TYPE_, MOD_ID_) FORM(Skyrim_Form, TYPE_, MOD_ID_);

    // Skyrim Actors
    Actor_t* Player_Actor() { SKYRIM_FORM(Actor_t, ACTOR_PLAYER); }

    // Skyrim Armors
    Armor_t* Belted_Tunic_Armor() { SKYRIM_FORM(Armor_t, ARMOR_BELTED_TUNIC); }
    Armor_t* Gold_Ring() { SKYRIM_FORM(Armor_t, ARMOR_GOLD_RING); }

    // Skyrim Effect Shaders
    Effect_Shader_t* Reanimate_Effect_Shader() { SKYRIM_FORM(Effect_Shader_t, EFFECT_SHADER_REANIMATE); }

    // Skyrim Factions
    Faction_t* No_Bard_Singer_Autostart_Faction() { SKYRIM_FORM(Faction_t, FACTION_BARD_SINGER_NO_AUTOSTART); }
    Faction_t* Current_Follower_Faction() { SKYRIM_FORM(Faction_t, FACTION_CURRENT_FOLLOWER); }
    Faction_t* Player_Follower_Faction() { SKYRIM_FORM(Faction_t, FACTION_PLAYER_FOLLOWER); }
    Faction_t* Potential_Follower_Faction() { SKYRIM_FORM(Faction_t, FACTION_POTENTIAL_FOLLOWER); }
    Faction_t* WI_No_Body_Cleanup_Faction() { SKYRIM_FORM(Faction_t, FACTION_WI_NO_BODY_CLEANUP); }

    // Skyrim Globals
    Global_t* Player_Follower_Count_Global() { SKYRIM_FORM(Global_t, GLOBAL_PLAYER_FOLLOWER_COUNT); }

    // Skyrim Keywords
    Keyword_t* Fire_Damage_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_FIRE); }
    Keyword_t* Frost_Damage_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_FROST); }
    Keyword_t* Shock_Damage_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_SHOCK); }
    Keyword_t* Vampire_Drain_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_VAMPIRE_DRAIN); }
    Keyword_t* Vampire_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_VAMPIRE); }
    Keyword_t* Staff_Vendor_Item_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_VENDOR_ITEM_STAFF); }
    Keyword_t* Sword_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_SWORD); }
    Keyword_t* Greatsword_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_GREATSWORD); }
    Keyword_t* Waraxe_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_WARAXE); }
    Keyword_t* Battleaxe_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_BATTLEAXE); }
    Keyword_t* Mace_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_MACE); }
    Keyword_t* Warhammer_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_WARHAMMER); }
    Keyword_t* Dagger_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_DAGGER); }
    Keyword_t* Bow_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_BOW); }
    Keyword_t* Staff_Weapon_Type_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_WEAPON_TYPE_STAFF); }

    // Skyrim Miscs
    Misc_t* Gold() { SKYRIM_FORM(Misc_t, MISC_GOLD); }

    // Skyrim Perks
    Perk_t* Vampire_Feed_Perk() { SKYRIM_FORM(Perk_t, PERK_VAMPIRE_FEED); }

    // Skyrim Quests
    Quest_t* Bard_Songs_Quest() { SKYRIM_FORM(Quest_t, QUEST_BARD_SONGS); }
    Quest_t* Follower_Dialogue_Quest() { SKYRIM_FORM(Quest_t, QUEST_DIALOGUE_FOLLOWER); }
    Quest_t* Player_Vampire_Quest() { SKYRIM_FORM(Quest_t, QUEST_PLAYER_VAMPIRE); }
    Quest_t* WI_Change_Location_01_Quest() { SKYRIM_FORM(Quest_t, QUEST_WI_CHANGE_LOCATION_01); }
    Quest_t* WI_Remove_Item_04_Quest() { SKYRIM_FORM(Quest_t, QUEST_WI_REMOVE_ITEM_04); }

    // Skyrim Reference Markers
    Reference_t* Safe_Go_Back_Marker() { SKYRIM_FORM(Reference_t, REFERENCE_MARKER_GO_BACK_SAFE); }

    // Skyrim Statics
    Static_t* X_Marker_Static() { SKYRIM_FORM(Static_t, STATIC_MARKER_X); }

    #undef SKYRIM_FORM

    enum Dawnguard_Forms {
        // Dawnguard Factions
        FACTION_DLC1_THRALL                         = 0x0162F7,
        FACTION_DLC1_VAMPIRE_FEED_NO_CRIME          = 0x014CBD,
    };

    #define DAWNGUARD_FORM(TYPE_, MOD_ID_) FORM(Dawnguard_Form, TYPE_, MOD_ID_);

    // Dawnguard Factions
    Faction_t* DLC1_Thrall_Faction() { DAWNGUARD_FORM(Faction_t, FACTION_DLC1_THRALL); }
    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction() { DAWNGUARD_FORM(Faction_t, FACTION_DLC1_VAMPIRE_FEED_NO_CRIME); }

    #undef DAWNGUARD_FORM

    enum NPCP_Forms {
        // NPCP Actor Base
        ACTOR_BASE_MENU                             = 0x317447,

        // NPCP Armors
        ARMOR_BLANK                                 = 0x1EF2A5,

        // NPCP Branches
        BRANCH_MAIN                                 = 0x0083EF,
        BRANCH_MAIN_DIRECT                          = 0x3A515A,
        BRANCH_MAIN_OUTFIT                          = 0x0CDE73,
        BRANCH_MAIN_STYLE                           = 0x040F0F,
        BRANCH_MAIN_VITALITY                        = 0x0CDE66,
        BRANCH_MENU_CHESTS                          = 0x32674F,
        BRANCH_MENU_CHESTS_APPAREL                  = 0x32B853,
        BRANCH_MENU_CHESTS_BOOKS                    = 0x32B859,
        BRANCH_MENU_CHESTS_CUSTOM                   = 0x3C37BA,
        BRANCH_MENU_CHESTS_EDIBLES                  = 0x32B855,
        BRANCH_MENU_CHESTS_MISC                     = 0x32B857,
        BRANCH_MENU_CHESTS_WEAPONS                  = 0x32B851,
        BRANCH_MENU_FOLLOWERS                       = 0x344DE2,

        // NPCP Cells
        CELL_STORAGE                                = 0x114F9C,

        // NPCP Containers
        CONTAINER_EMPTY                             = 0x0A5561,
        CONTAINER_OUTFIT2                           = 0x0B9A63,
        CONTAINER_OUTFIT2_IMMOBILE                  = 0x1663CE,
        CONTAINER_OUTFIT2_SETTLER                   = 0x1663CD,
        CONTAINER_OUTFIT2_THRALL                    = 0x1663CC,
        CONTAINER_OUTFIT2_FOLLOWER                  = 0x1663C7,

        // NPCP Factions
        FACTION_HORSE                               = 0x354111,
        FACTION_MEMBER                              = 0x091154,

        // NPCP Formlists
        FORMLIST_GLOBALS_IS_SADDLER_SITTING         = 0x395E54,
        FORMLIST_MARKERS_EXPO_CELL                  = 0x2928AF,
        FORMLIST_MARKERS_SETTLER                    = 0x00B46E,

        // NPCP Globals
        GLOBAL_IS_INSTALLED                         = 0x189ADD,
        GLOBAL_ALLOW_DIALOGUE_FOR_ALL               = 0x3B4463,
        GLOBAL_ALLOW_CHATTER                        = 0x3B9568,
        GLOBAL_FORCE_CLONE_UNIQUES                  = 0x05244D,
        GLOBAL_FORCE_CLONE_GENERICS                 = 0x05244E,
        GLOBAL_FORCE_UNCLONE_UNIQUES                = 0x05244F,
        GLOBAL_FORCE_UNCLONE_GENERICS               = 0x052450,
        GLOBAL_IS_LEVELING_ENABLED                  = 0x3B4464,
        GLOBAL_PERCENT_NO_BODY                      = 0x193CEA,
        GLOBAL_PERCENT_NO_FEET                      = 0x193CE7,
        GLOBAL_PERCENT_NO_HANDS                     = 0x193CE8,
        GLOBAL_PERCENT_NO_HEAD                      = 0x193CE6,

        // NPCP Leveled Actor
        LEVELED_ACTOR_HORSE                         = 0x354127,

        // NPCP Location
        LOCATION_EXPO                               = 0x27E48E,

        // NPCP Magic Effects
        MAGIC_EFFECT_REANIMATE                      = 0x3AF361,
        MAGIC_EFFECT_RETREAT                        = 0x2DF8FA,

        // NPCP Misc Tokens
        MISC_TOKEN_BANISHED                         = 0x003DFD,
        MISC_TOKEN_CLONE                            = 0x003DFC,
        MISC_TOKEN_DISPLAY                          = 0x13D7AC,
        MISC_TOKEN_FOLLOWER                         = 0x000D84,
        MISC_TOKEN_FOLLOWER_SNEAK                   = 0x000D85,
        MISC_TOKEN_GENERIC                          = 0x003DFE,
        MISC_TOKEN_GREETER                          = 0x057384,
        MISC_TOKEN_IMMOBILE                         = 0x000D77,
        MISC_TOKEN_MANNEQUIN                        = 0x264F42,
        MISC_TOKEN_MEMBER                           = 0x000D75,
        MISC_TOKEN_MOVEE                            = 0x1612B3,
        MISC_TOKEN_PARALYZED                        = 0x12E4A7,
        MISC_TOKEN_REANIMATED                       = 0x1E4E9D,
        MISC_TOKEN_RETREATER                        = 0x2F3D00,
        MISC_TOKEN_SADDLER                          = 0x34F000,
        MISC_TOKEN_SETTLER                          = 0x000D73,
        MISC_TOKEN_STYLE_ARCHER                     = 0x0A045E,
        MISC_TOKEN_STYLE_COWARD                     = 0x2D56F3,
        MISC_TOKEN_STYLE_DEFAULT                    = 0x0A045D,
        MISC_TOKEN_STYLE_MAGE                       = 0x0A045F,
        MISC_TOKEN_STYLE_WARRIOR                    = 0x0A0460,
        MISC_TOKEN_THRALL                           = 0x011E90,
        MISC_TOKEN_VITALITY_ESSENTIAL               = 0x0A0459,
        MISC_TOKEN_VITALITY_INVULNERABLE            = 0x0A045C,
        MISC_TOKEN_VITALITY_MORTAL                  = 0x0A045B,
        MISC_TOKEN_VITALITY_PROTECTED               = 0x0A045A,

        // NPCP Misc
        MISC_VECTOR_FORM                            = 0x15C1B2,

        // NPCP Outfits
        OUTFIT_EMPTY                                = 0x0C3C64,

        // NPCP_Packages
        PACKAGE_MENU_EXIT                           = 0x3309E0,

        // NPCP PERKS
        PERK_KISS_THRALL                            = 0x07CD48,
        PERK_REANIMATE                              = 0x1DFD9C,
        PERK_RESURRECT                              = 0x0D2F7C,
        PERK_UNPARALYZE                             = 0x16B4D1,

        // NPCP Quests
        QUEST_MAIN                                  = 0x005385,
        QUEST_VARS                                  = 0x003DFF,
        QUEST_FUNCS                                 = 0x005384,
        QUEST_MEMBERS                               = 0x00184C,
        QUEST_FOLLOWERS                             = 0x000D83,
        QUEST_CONTROL                               = 0x000D7F,
        QUEST_DIALOGUE_THRALL                       = 0x212D57,
        QUEST_DIALOGUE_REANIMATED                   = 0x2089A9,
        QUEST_FEMALE_YOUNG_EAGER                    = 0x3B9565,

        // NPCP Reference Categories
        REFERENCE_CATEGORY_INPUT                    = 0x395E55,
        REFERENCE_CATEGORY_SWORDS                   = 0x30D20A,
        REFERENCE_CATEGORY_GREATSWORDS              = 0x30D20B,
        REFERENCE_CATEGORY_WARAXES                  = 0x30D20C,
        REFERENCE_CATEGORY_BATTLEAXES               = 0x30D20D,
        REFERENCE_CATEGORY_MACES                    = 0x30D20E,
        REFERENCE_CATEGORY_WARHAMMERS               = 0x30D20F,
        REFERENCE_CATEGORY_DAGGERS                  = 0x30D210,
        REFERENCE_CATEGORY_STAVES                   = 0x30D212,
        REFERENCE_CATEGORY_BOWS                     = 0x30D211,
        REFERENCE_CATEGORY_AMMO                     = 0x30D23D,
        REFERENCE_CATEGORY_WEAPONS                  = 0x30D213,
        REFERENCE_CATEGORY_LIGHT_ARMOR              = 0x30D214,
        REFERENCE_CATEGORY_HEAVY_ARMOR              = 0x30D215,
        REFERENCE_CATEGORY_SHIELDS                  = 0x30D216,
        REFERENCE_CATEGORY_JEWELRY                  = 0x30D217,
        REFERENCE_CATEGORY_CLOTHES                  = 0x30D218,
        REFERENCE_CATEGORY_POTIONS                  = 0x30D219,
        REFERENCE_CATEGORY_POISONS                  = 0x30D21A,
        REFERENCE_CATEGORY_INGREDIENTS              = 0x30D23E,
        REFERENCE_CATEGORY_FOOD                     = 0x30D21B,
        REFERENCE_CATEGORY_SOULGEMS                 = 0x30D240,
        REFERENCE_CATEGORY_SCROLLS                  = 0x30D23F,
        REFERENCE_CATEGORY_METALS                   = 0x30D239,
        REFERENCE_CATEGORY_LEATHER                  = 0x30D23A,
        REFERENCE_CATEGORY_GEMS                     = 0x30D23B,
        REFERENCE_CATEGORY_CLUTTER                  = 0x30D23C,
        REFERENCE_CATEGORY_KEYS                     = 0x30D241,
        REFERENCE_CATEGORY_MISC                     = 0x30D242,
        REFERENCE_CATEGORY_SPELL_TOMES              = 0x30D21C,
        REFERENCE_CATEGORY_RECIPES                  = 0x30D21D,
        REFERENCE_CATEGORY_BOOKS_A                  = 0x30D21E,
        REFERENCE_CATEGORY_BOOKS_B                  = 0x30D21F,
        REFERENCE_CATEGORY_BOOKS_C                  = 0x30D220,
        REFERENCE_CATEGORY_BOOKS_D                  = 0x30D221,
        REFERENCE_CATEGORY_BOOKS_E                  = 0x30D222,
        REFERENCE_CATEGORY_BOOKS_F                  = 0x30D223,
        REFERENCE_CATEGORY_BOOKS_G                  = 0x30D224,
        REFERENCE_CATEGORY_BOOKS_H                  = 0x30D225,
        REFERENCE_CATEGORY_BOOKS_I                  = 0x30D226,
        REFERENCE_CATEGORY_BOOKS_J                  = 0x30D227,
        REFERENCE_CATEGORY_BOOKS_K                  = 0x30D228,
        REFERENCE_CATEGORY_BOOKS_L                  = 0x30D229,
        REFERENCE_CATEGORY_BOOKS_M                  = 0x30D22A,
        REFERENCE_CATEGORY_BOOKS_N                  = 0x30D22B,
        REFERENCE_CATEGORY_BOOKS_O                  = 0x30D22C,
        REFERENCE_CATEGORY_BOOKS_P                  = 0x30D22D,
        REFERENCE_CATEGORY_BOOKS_Q                  = 0x30D22E,
        REFERENCE_CATEGORY_BOOKS_R                  = 0x30D22F,
        REFERENCE_CATEGORY_BOOKS_S                  = 0x30D230,
        REFERENCE_CATEGORY_BOOKS_T                  = 0x30D231,
        REFERENCE_CATEGORY_BOOKS_U                  = 0x30D232,
        REFERENCE_CATEGORY_BOOKS_V                  = 0x30D233,
        REFERENCE_CATEGORY_BOOKS_W                  = 0x30D234,
        REFERENCE_CATEGORY_BOOKS_X                  = 0x30D235,
        REFERENCE_CATEGORY_BOOKS_Y                  = 0x30D236,
        REFERENCE_CATEGORY_BOOKS_Z                  = 0x30D237,
        REFERENCE_CATEGORY_BOOKS                    = 0x30D238,
        REFERENCE_CATEGORY_CUSTOM_00                = 0x3C37AA,
        REFERENCE_CATEGORY_CUSTOM_01                = 0x3C37AB,
        REFERENCE_CATEGORY_CUSTOM_02                = 0x3C37AC,
        REFERENCE_CATEGORY_CUSTOM_03                = 0x3C37AD,
        REFERENCE_CATEGORY_CUSTOM_04                = 0x3C37AE,
        REFERENCE_CATEGORY_CUSTOM_05                = 0x3C37AF,
        REFERENCE_CATEGORY_CUSTOM_06                = 0x3C37B0,
        REFERENCE_CATEGORY_CUSTOM_07                = 0x3C37B1,
        REFERENCE_CATEGORY_CUSTOM_08                = 0x3C37B2,
        REFERENCE_CATEGORY_CUSTOM_09                = 0x3C37B3,
        REFERENCE_CATEGORY_CUSTOM_10                = 0x3C37B4,
        REFERENCE_CATEGORY_CUSTOM_11                = 0x3C37B5,
        REFERENCE_CATEGORY_CUSTOM_12                = 0x3C37B6,
        REFERENCE_CATEGORY_CUSTOM_13                = 0x3C37B7,
        REFERENCE_CATEGORY_CUSTOM_14                = 0x3C37B8,
        REFERENCE_CATEGORY_CUSTOM_15                = 0x3C37B9,

        // NPCP Reference Containers
        REFERENCE_CONTAINER_BUFFER                  = 0x3C37A9,

        // NPCP Reference Markers
        REFERENCE_MARKER_CELL                       = 0x15C1AE,
        REFERENCE_MARKER_EXPO_ANTECHAMBER           = 0x2979B0,
        REFERENCE_MARKER_STORAGE                    = 0x114F9D,

        // NPCP Spells
        SPELL_ABILITY_REANIMATE                     = 0x3AF362,
        SPELL_ABILITY_RETREAT                       = 0x2F3CFF,

        // NPCP Topics
        TOPIC_MAIN                                  = 0x0083F1,
        TOPIC_MAIN_BACK                             = 0x0083F2,
        TOPIC_MAIN_CLONE                            = 0x020C2A,
        TOPIC_MAIN_DIRECT                           = 0x3A5158,
        TOPIC_MAIN_DIRECT_BLOCK                     = 0x3A515B,
        TOPIC_MAIN_DIRECT_CONTINUE                  = 0x3A515D,
        TOPIC_MAIN_DIRECT_END                       = 0x3A515F,
        TOPIC_MAIN_ENTHRALL                         = 0x02D231,
        TOPIC_MAIN_FOLLOW                           = 0x00AF09,
        TOPIC_MAIN_GOODBYE                          = 0x19DF1A,
        TOPIC_MAIN_HELLO                            = 0x08C049,
        TOPIC_MAIN_IMMOBILIZE                       = 0x00A440,
        TOPIC_MAIN_MEMBER                           = 0x00B9D2,
        TOPIC_MAIN_MOBILIZE                         = 0x00A442,
        TOPIC_MAIN_OUTFIT                           = 0x0CDE74,
        TOPIC_MAIN_OUTFIT2                          = 0x1C67B9,
        TOPIC_MAIN_OUTFIT_BACK                      = 0x0CDE76,
        TOPIC_MAIN_OUTFIT_CURRENT                   = 0x1335AA,
        TOPIC_MAIN_OUTFIT_DEFAULT                   = 0x1E9FA0,
        TOPIC_MAIN_OUTFIT_FOLLOWER                  = 0x0CDE77,
        TOPIC_MAIN_OUTFIT_IMMOBILE                  = 0x12E4A2,
        TOPIC_MAIN_OUTFIT_MEMBER                    = 0x0CDE75,
        TOPIC_MAIN_OUTFIT_SETTLER                   = 0x12E4A1,
        TOPIC_MAIN_OUTFIT_THRALL                    = 0x12E4A5,
        TOPIC_MAIN_OUTFIT_VANILLA                   = 0x1E9F9E,
        TOPIC_MAIN_PACK                             = 0x008EB9,
        TOPIC_MAIN_PARALYZE                         = 0x1705D2,
        TOPIC_MAIN_RESETTLE                         = 0x00B46F,
        TOPIC_MAIN_SADDLE                           = 0x36D62B,
        TOPIC_MAIN_SETTLE                           = 0x00A43F,
        TOPIC_MAIN_SNEAK                            = 0x00C498,
        TOPIC_MAIN_STASH                            = 0x312344,
        TOPIC_MAIN_STYLE                            = 0x040F10,
        TOPIC_MAIN_STYLE2                           = 0x1C67BB,
        TOPIC_MAIN_STYLE_ARCHER                     = 0x040F17,
        TOPIC_MAIN_STYLE_BACK                       = 0x040F11,
        TOPIC_MAIN_STYLE_COWARD                     = 0x2D56F6,
        TOPIC_MAIN_STYLE_DEFAULT                    = 0x040F14,
        TOPIC_MAIN_STYLE_MAGE                       = 0x040F16,
        TOPIC_MAIN_STYLE_WARRIOR                    = 0x040F15,
        TOPIC_MAIN_UNCLONE                          = 0x0233C8,
        TOPIC_MAIN_UNFOLLOW                         = 0x00AF0A,
        TOPIC_MAIN_UNMEMBER                         = 0x00B9D3,
        TOPIC_MAIN_UNSADDLE                         = 0x36D62C,
        TOPIC_MAIN_UNSETTLE                         = 0x00A441,
        TOPIC_MAIN_UNSNEAK                          = 0x00C499,
        TOPIC_MAIN_UNTHRALL                         = 0x02D232,
        TOPIC_MAIN_VITALITY                         = 0x0CDE67,
        TOPIC_MAIN_VITALITY2                        = 0x1C67BD,
        TOPIC_MAIN_VITALITY_BACK                    = 0x0CDE68,
        TOPIC_MAIN_VITALITY_ESSENTIAL               = 0x0CDE6B,
        TOPIC_MAIN_VITALITY_INVULNERABLE            = 0x0CDE6C,
        TOPIC_MAIN_VITALITY_MORTAL                  = 0x0CDE69,
        TOPIC_MAIN_VITALITY_PROTECTED               = 0x0CDE6A,
        TOPIC_MENU_FOLLOWERS                        = 0x344DE3,
        TOPIC_MENU_FOLLOWERS_BACK                   = 0x344DE4,
        TOPIC_MENU_FOLLOWERS_IMMOBILIZE             = 0x344DE9,
        TOPIC_MENU_FOLLOWERS_MOBILIZE               = 0x344DE8,
        TOPIC_MENU_FOLLOWERS_SADDLE                 = 0x36D62F,
        TOPIC_MENU_FOLLOWERS_SETTLE                 = 0x344DEC,
        TOPIC_MENU_FOLLOWERS_SNEAK                  = 0x344DEA,
        TOPIC_MENU_FOLLOWERS_STASH                  = 0x349EFD,
        TOPIC_MENU_FOLLOWERS_SUMMON_ALL             = 0x344DE5,
        TOPIC_MENU_FOLLOWERS_SUMMON_IMMOBILE        = 0x344DE7,
        TOPIC_MENU_FOLLOWERS_SUMMON_MOBILE          = 0x344DE6,
        TOPIC_MENU_FOLLOWERS_UNFOLLOW               = 0x344DEE,
        TOPIC_MENU_FOLLOWERS_UNMEMBER               = 0x344DEF,
        TOPIC_MENU_FOLLOWERS_UNSADDLE               = 0x36D630,
        TOPIC_MENU_FOLLOWERS_UNSETTLE               = 0x344DED,
        TOPIC_MENU_FOLLOWERS_UNSNEAK                = 0x344DEB,

        // NPCP Topic Infos
        TOPIC_INFO_MENU_CHESTS_INPUT                = 0x39AF57,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_SWORDS       = 0x32B8DC,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_GREATSWORDS  = 0x32B8D9,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_WARAXES      = 0x32B8DD,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_BATTLEAXES   = 0x32B8D6,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_MACES        = 0x32B8DA,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_WARHAMMERS   = 0x32B8DE,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_DAGGERS      = 0x32B8D8,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_STAVES       = 0x32B8DB,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_BOWS         = 0x32B8D7,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_AMMO         = 0x32B8CC,
        TOPIC_INFO_MENU_CHESTS_WEAPONS_OTHERS       = 0x32B8DF,
        TOPIC_INFO_MENU_CHESTS_APPAREL_LIGHT_ARMOR  = 0x32B8AA,
        TOPIC_INFO_MENU_CHESTS_APPAREL_HEAVY_ARMOR  = 0x32B8A8,
        TOPIC_INFO_MENU_CHESTS_APPAREL_SHIELDS      = 0x32B8AB,
        TOPIC_INFO_MENU_CHESTS_APPAREL_JEWELRY      = 0x32B8A9,
        TOPIC_INFO_MENU_CHESTS_APPAREL_CLOTHES      = 0x32B8A7,
        TOPIC_INFO_MENU_CHESTS_EDIBLES_POTIONS      = 0x32B8CB,
        TOPIC_INFO_MENU_CHESTS_EDIBLES_POISONS      = 0x32B8CA,
        TOPIC_INFO_MENU_CHESTS_EDIBLES_INGREDIENTS  = 0x32B8CF,
        TOPIC_INFO_MENU_CHESTS_EDIBLES_FOOD         = 0x32B8C9,
        TOPIC_INFO_MENU_CHESTS_MISC_SOULGEMS        = 0x32B8D5,
        TOPIC_INFO_MENU_CHESTS_MISC_SCROLLS         = 0x32B8D4,
        TOPIC_INFO_MENU_CHESTS_MISC_METALS          = 0x32B8D2,
        TOPIC_INFO_MENU_CHESTS_MISC_LEATHER         = 0x32B8D1,
        TOPIC_INFO_MENU_CHESTS_MISC_GEMS            = 0x32B8CE,
        TOPIC_INFO_MENU_CHESTS_MISC_CLUTTER         = 0x32B8CD,
        TOPIC_INFO_MENU_CHESTS_MISC_KEYS            = 0x32B8D0,
        TOPIC_INFO_MENU_CHESTS_MISC_OTHERS          = 0x32B8D3,
        TOPIC_INFO_MENU_CHESTS_BOOKS_SPELL_TOMES    = 0x32B8C1,
        TOPIC_INFO_MENU_CHESTS_BOOKS_RECIPES        = 0x32B8BF,
        TOPIC_INFO_MENU_CHESTS_BOOKS_A              = 0x32B8AC,
        TOPIC_INFO_MENU_CHESTS_BOOKS_B              = 0x32B8AD,
        TOPIC_INFO_MENU_CHESTS_BOOKS_C              = 0x32B8AE,
        TOPIC_INFO_MENU_CHESTS_BOOKS_D              = 0x32B8AF,
        TOPIC_INFO_MENU_CHESTS_BOOKS_E              = 0x32B8B0,
        TOPIC_INFO_MENU_CHESTS_BOOKS_F              = 0x32B8B1,
        TOPIC_INFO_MENU_CHESTS_BOOKS_G              = 0x32B8B2,
        TOPIC_INFO_MENU_CHESTS_BOOKS_H              = 0x32B8B3,
        TOPIC_INFO_MENU_CHESTS_BOOKS_I              = 0x32B8B4,
        TOPIC_INFO_MENU_CHESTS_BOOKS_J              = 0x32B8B5,
        TOPIC_INFO_MENU_CHESTS_BOOKS_K              = 0x32B8B6,
        TOPIC_INFO_MENU_CHESTS_BOOKS_L              = 0x32B8B7,
        TOPIC_INFO_MENU_CHESTS_BOOKS_M              = 0x32B8B8,
        TOPIC_INFO_MENU_CHESTS_BOOKS_N              = 0x32B8B9,
        TOPIC_INFO_MENU_CHESTS_BOOKS_O              = 0x32B8BA,
        TOPIC_INFO_MENU_CHESTS_BOOKS_P              = 0x32B8BC,
        TOPIC_INFO_MENU_CHESTS_BOOKS_Q              = 0x32B8BD,
        TOPIC_INFO_MENU_CHESTS_BOOKS_R              = 0x32B8BE,
        TOPIC_INFO_MENU_CHESTS_BOOKS_S              = 0x32B8C0,
        TOPIC_INFO_MENU_CHESTS_BOOKS_T              = 0x32B8C2,
        TOPIC_INFO_MENU_CHESTS_BOOKS_U              = 0x32B8C3,
        TOPIC_INFO_MENU_CHESTS_BOOKS_V              = 0x32B8C4,
        TOPIC_INFO_MENU_CHESTS_BOOKS_W              = 0x32B8C5,
        TOPIC_INFO_MENU_CHESTS_BOOKS_X              = 0x32B8C6,
        TOPIC_INFO_MENU_CHESTS_BOOKS_Y              = 0x32B8C7,
        TOPIC_INFO_MENU_CHESTS_BOOKS_Z              = 0x32B8C8,
        TOPIC_INFO_MENU_CHESTS_BOOKS_OTHERS         = 0x32B8BB,
        TOPIC_INFO_MENU_CHESTS_CUSTOM               = 0x3C37BE,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_00            = 0x3C37C0,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_01            = 0x3C37C2,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_02            = 0x3C37C4,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_03            = 0x3C37C6,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_04            = 0x3C37C8,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_05            = 0x3C37CA,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_06            = 0x3C37CC,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_07            = 0x3C37CE,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_08            = 0x3C37D0,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_09            = 0x3C37D2,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_10            = 0x3C37D4,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_11            = 0x3C37D6,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_12            = 0x3C37D8,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_13            = 0x3C37DA,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_14            = 0x3C37DC,
        TOPIC_INFO_MENU_CHESTS_CUSTOM_15            = 0x3C37DE,

        // NPCP Weapons
        WEAPON_BLANK                                = 0x0C8D65,
    };

    #define NPCP_FORM(TYPE_, MOD_ID_) FORM(NPCP_Form, TYPE_, MOD_ID_);

    // NPCP Actor Base
    Actor_Base_t* Menu_Actor_Base() { NPCP_FORM(Actor_Base_t, ACTOR_BASE_MENU); }

    // NPCP Armors
    Armor_t* Blank_Armor() { NPCP_FORM(Armor_t, ARMOR_BLANK); }

    // NPCP Branches
    Branch_t* Main_Branch() { NPCP_FORM(Branch_t, BRANCH_MAIN); }
    Branch_t* Main_Direct_Branch() { NPCP_FORM(Branch_t, BRANCH_MAIN_DIRECT); }
    Branch_t* Main_Outfit_Branch() { NPCP_FORM(Branch_t, BRANCH_MAIN_OUTFIT); }
    Branch_t* Main_Style_Branch() { NPCP_FORM(Branch_t, BRANCH_MAIN_STYLE); }
    Branch_t* Main_Vitality_Branch() { NPCP_FORM(Branch_t, BRANCH_MAIN_VITALITY); }
    Branch_t* Menu_Chests_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_CHESTS); }
    Branch_t* Menu_Chests_Weapons_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_CHESTS_WEAPONS); }
    Branch_t* Menu_Chests_Apparel_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_CHESTS_APPAREL); }
    Branch_t* Menu_Chests_Edibles_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_CHESTS_EDIBLES); }
    Branch_t* Menu_Chests_Misc_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_CHESTS_MISC); }
    Branch_t* Menu_Chests_Books_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_CHESTS_BOOKS); }
    Branch_t* Menu_Chests_Custom_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_CHESTS_CUSTOM); }
    Branch_t* Menu_Followers_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU_FOLLOWERS); }

    // NPCP Cells
    Cell_t* Storage_Cell() { NPCP_FORM(Cell_t, CELL_STORAGE); }

    // NPCP Containers
    Container_t* Empty_Container() { NPCP_FORM(Container_t, CONTAINER_EMPTY); }
    Container_t* Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2); }
    Container_t* Immobile_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_IMMOBILE); }
    Container_t* Settler_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_SETTLER); }
    Container_t* Thrall_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_THRALL); }
    Container_t* Follower_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_FOLLOWER); }

    // NPCP Factions
    Faction_t* Member_Faction() { NPCP_FORM(Faction_t, FACTION_MEMBER); }
    Faction_t* Horse_Faction() { NPCP_FORM(Faction_t, FACTION_HORSE); }

    // NPCP Formlists
    Formlist_t* Is_Saddler_Sitting_Globals_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_GLOBALS_IS_SADDLER_SITTING); }
    Formlist_t* Expo_Cell_Markers_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_MARKERS_EXPO_CELL); }
    Formlist_t* Settler_Markers_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_MARKERS_SETTLER); }

    // NPCP Globals
    Global_t* Is_Installed_Global() { NPCP_FORM(Global_t, GLOBAL_IS_INSTALLED); }
    Global_t* Allow_Dialogue_For_All_Global() { NPCP_FORM(Global_t, GLOBAL_ALLOW_DIALOGUE_FOR_ALL); }
    Global_t* Allow_Chatter_Global() { NPCP_FORM(Global_t, GLOBAL_ALLOW_CHATTER); }
    Global_t* Force_Clone_Uniques_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_CLONE_UNIQUES); }
    Global_t* Force_Clone_Generics_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_CLONE_GENERICS); }
    Global_t* Force_Unclone_Uniques_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_UNCLONE_UNIQUES); }
    Global_t* Force_Unclone_Generics_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_UNCLONE_GENERICS); }
    Global_t* Is_Leveling_Enabled_Global() { NPCP_FORM(Global_t, GLOBAL_IS_LEVELING_ENABLED); }
    Global_t* No_Body_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_BODY); }
    Global_t* No_Feet_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_FEET); }
    Global_t* No_Hands_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_HANDS); }
    Global_t* No_Head_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_HEAD); }

    // NPCP Ints
    Int_t NPCP_Major() { return 0; } // set manually upon each release
    Int_t NPCP_Minor() { return 9; } // set manually upon each release
    Int_t NPCP_Patch() { return 12; } // set manually upon each release

    // NPCP Leveled Actor
    Leveled_Actor_t* Horse_Leveled_Actor() { NPCP_FORM(Leveled_Actor_t, LEVELED_ACTOR_HORSE); }

    // NPCP Location
    Location_t* Expo_Location() { NPCP_FORM(Location_t, LOCATION_EXPO); }

    // NPCP Magic Effects
    Magic_Effect_t* Reanimate_Magic_Effect() { NPCP_FORM(Magic_Effect_t, MAGIC_EFFECT_REANIMATE); }
    Magic_Effect_t* Retreat_Magic_Effect() { NPCP_FORM(Magic_Effect_t, MAGIC_EFFECT_RETREAT); }

    // NPCP Misc Tokens
    Misc_t* Member_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_MEMBER); }
    Misc_t* Generic_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_GENERIC); }
    Misc_t* Clone_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_CLONE); }
    Misc_t* Greeter_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_GREETER); }
    Misc_t* Movee_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_MOVEE); }
    Misc_t* Immobile_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_IMMOBILE); }
    Misc_t* Settler_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SETTLER); }
    Misc_t* Thrall_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_THRALL); }
    Misc_t* Paralyzed_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_PARALYZED); }
    Misc_t* Mannequin_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_MANNEQUIN); }
    Misc_t* Display_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_DISPLAY); }
    Misc_t* Reanimated_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_REANIMATED); }
    Misc_t* Banished_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_BANISHED); }
    Misc_t* Default_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_DEFAULT); }
    Misc_t* Warrior_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_WARRIOR); }
    Misc_t* Mage_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_MAGE); }
    Misc_t* Archer_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_ARCHER); }
    Misc_t* Coward_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_COWARD); }
    Misc_t* Mortal_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_MORTAL); }
    Misc_t* Protected_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_PROTECTED); }
    Misc_t* Essential_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_ESSENTIAL); }
    Misc_t* Invulnerable_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_INVULNERABLE); }
    Misc_t* Follower_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER); }
    Misc_t* Sneak_Follower_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER_SNEAK); }
    Misc_t* Saddler_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SADDLER); }
    Misc_t* Retreater_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_RETREATER); }

    // NPCP Misc
    Misc_t* Form_Vector() { NPCP_FORM(Misc_t, MISC_VECTOR_FORM); }

    // NPCP Outfits
    Outfit_t* Empty_Outfit() { NPCP_FORM(Outfit_t, OUTFIT_EMPTY); }

    // NPCP Packages
    Package_t* Menu_Exit_Package() { NPCP_FORM(Package_t, PACKAGE_MENU_EXIT); }

    // NPCP Perks
    Perk_t* Kiss_Thrall_Perk() { NPCP_FORM(Perk_t, PERK_KISS_THRALL); }
    Perk_t* Reanimate_Perk() { NPCP_FORM(Perk_t, PERK_REANIMATE); }
    Perk_t* Resurrect_Perk() { NPCP_FORM(Perk_t, PERK_RESURRECT); }
    Perk_t* Unparalyze_Perk() { NPCP_FORM(Perk_t, PERK_UNPARALYZE); }

    // NPCP Quests
    Quest_t* Main_Quest() { NPCP_FORM(Quest_t, QUEST_MAIN); }
    Quest_t* Vars_Quest() { NPCP_FORM(Quest_t, QUEST_VARS); }
    Quest_t* Funcs_Quest() { NPCP_FORM(Quest_t, QUEST_FUNCS); }
    Quest_t* Members_Quest() { NPCP_FORM(Quest_t, QUEST_MEMBERS); }
    Quest_t* Followers_Quest() { NPCP_FORM(Quest_t, QUEST_FOLLOWERS); }
    Quest_t* Control_Quest() { NPCP_FORM(Quest_t, QUEST_CONTROL); }
    Quest_t* Thrall_Dialogue_Quest() { NPCP_FORM(Quest_t, QUEST_DIALOGUE_THRALL); }
    Quest_t* Reanimated_Dialogue_Quest() { NPCP_FORM(Quest_t, QUEST_DIALOGUE_REANIMATED); }
    Quest_t* Female_Young_Eager_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_YOUNG_EAGER); }

    // NPCP Reference Categories
    Reference_t* Input_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_INPUT); }
    Reference_t* Swords_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SWORDS); }
    Reference_t* Greatswords_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_GREATSWORDS); }
    Reference_t* Waraxes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WARAXES); }
    Reference_t* Battleaxes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BATTLEAXES); }
    Reference_t* Maces_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_MACES); }
    Reference_t* Warhammers_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WARHAMMERS); }
    Reference_t* Daggers_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_DAGGERS); }
    Reference_t* Staves_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_STAVES); }
    Reference_t* Bows_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOWS); }
    Reference_t* Ammo_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_AMMO); }
    Reference_t* Weapons_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WEAPONS); }
    Reference_t* Light_Armor_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_LIGHT_ARMOR); }
    Reference_t* Heavy_Armor_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_HEAVY_ARMOR); }
    Reference_t* Shields_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SHIELDS); }
    Reference_t* Jewelry_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_JEWELRY); }
    Reference_t* Clothes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CLOTHES); }
    Reference_t* Potions_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_POTIONS); }
    Reference_t* Poisons_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_POISONS); }
    Reference_t* Ingredients_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_INGREDIENTS); }
    Reference_t* Food_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_FOOD); }
    Reference_t* Soulgems_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SOULGEMS); }
    Reference_t* Scrolls_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SCROLLS); }
    Reference_t* Metals_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_METALS); }
    Reference_t* Leather_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_LEATHER); }
    Reference_t* Gems_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_GEMS); }
    Reference_t* Clutter_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CLUTTER); }
    Reference_t* Keys_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_KEYS); }
    Reference_t* Misc_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_MISC); }
    Reference_t* Spell_Tomes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SPELL_TOMES); }
    Reference_t* Recipes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_RECIPES); }
    Reference_t* A_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_A); }
    Reference_t* B_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_B); }
    Reference_t* C_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_C); }
    Reference_t* D_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_D); }
    Reference_t* E_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_E); }
    Reference_t* F_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_F); }
    Reference_t* G_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_G); }
    Reference_t* H_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_H); }
    Reference_t* I_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_I); }
    Reference_t* J_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_J); }
    Reference_t* K_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_K); }
    Reference_t* L_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_L); }
    Reference_t* M_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_M); }
    Reference_t* N_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_N); }
    Reference_t* O_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_O); }
    Reference_t* P_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_P); }
    Reference_t* Q_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Q); }
    Reference_t* R_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_R); }
    Reference_t* S_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_S); }
    Reference_t* T_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_T); }
    Reference_t* U_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_U); }
    Reference_t* V_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_V); }
    Reference_t* W_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_W); }
    Reference_t* X_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_X); }
    Reference_t* Y_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Y); }
    Reference_t* Z_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Z); }
    Reference_t* Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS); }
    Reference_t* Custom_00_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_00); }
    Reference_t* Custom_01_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_01); }
    Reference_t* Custom_02_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_02); }
    Reference_t* Custom_03_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_03); }
    Reference_t* Custom_04_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_04); }
    Reference_t* Custom_05_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_05); }
    Reference_t* Custom_06_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_06); }
    Reference_t* Custom_07_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_07); }
    Reference_t* Custom_08_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_08); }
    Reference_t* Custom_09_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_09); }
    Reference_t* Custom_10_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_10); }
    Reference_t* Custom_11_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_11); }
    Reference_t* Custom_12_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_12); }
    Reference_t* Custom_13_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_13); }
    Reference_t* Custom_14_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_14); }
    Reference_t* Custom_15_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CUSTOM_15); }

    // NPCP Reference Containers
    Reference_t* Container_Ref_Buffer() { NPCP_FORM(Reference_t, REFERENCE_CONTAINER_BUFFER); }

    // NPCP Reference Markers
    Reference_t* Cell_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_CELL); }
    Reference_t* Expo_Antechamber_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_EXPO_ANTECHAMBER); }
    Reference_t* Storage_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_STORAGE); }

    // NPCP Spells
    Spell_t* Reanimate_Ability_Spell() { NPCP_FORM(Spell_t, SPELL_ABILITY_REANIMATE); }
    Spell_t* Retreat_Ability_Spell() { NPCP_FORM(Spell_t, SPELL_ABILITY_RETREAT); }

    // NPCP Topics
    Topic_t* Main_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN); }
    Topic_t* Main_Back_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_BACK); }
    Topic_t* Main_Clone_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_CLONE); }
    Topic_t* Main_Direct_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_DIRECT); }
    Topic_t* Main_Direct_Block_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_DIRECT_BLOCK); }
    Topic_t* Main_Direct_Continue_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_DIRECT_CONTINUE); }
    Topic_t* Main_Direct_End_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_DIRECT_END); }
    Topic_t* Main_Enthrall_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_ENTHRALL); }
    Topic_t* Main_Follow_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_FOLLOW); }
    Topic_t* Main_Goodbye_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_GOODBYE); }
    Topic_t* Main_Hello_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_HELLO); }
    Topic_t* Main_Immobilize_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_IMMOBILIZE); }
    Topic_t* Main_Member_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_MEMBER); }
    Topic_t* Main_Mobilize_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_MOBILIZE); }
    Topic_t* Main_Outfit_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT); }
    Topic_t* Main_Outfit2_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT2); }
    Topic_t* Main_Outfit_Back_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_BACK); }
    Topic_t* Main_Outfit_Current_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_CURRENT); }
    Topic_t* Main_Outfit_Default_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_DEFAULT); }
    Topic_t* Main_Outfit_Follower_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_FOLLOWER); }
    Topic_t* Main_Outfit_Immobile_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_IMMOBILE); }
    Topic_t* Main_Outfit_Member_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_MEMBER); }
    Topic_t* Main_Outfit_Settler_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_SETTLER); }
    Topic_t* Main_Outfit_Thrall_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_THRALL); }
    Topic_t* Main_Outfit_Vanilla_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_OUTFIT_VANILLA); }
    Topic_t* Main_Pack_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_PACK); }
    Topic_t* Main_Paralyze_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_PARALYZE); }
    Topic_t* Main_Resettle_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_RESETTLE); }
    Topic_t* Main_Saddle_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_SADDLE); }
    Topic_t* Main_Settle_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_SETTLE); }
    Topic_t* Main_Sneak_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_SNEAK); }
    Topic_t* Main_Stash_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STASH); }
    Topic_t* Main_Style_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE); }
    Topic_t* Main_Style2_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE2); }
    Topic_t* Main_Style_Archer_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE_ARCHER); }
    Topic_t* Main_Style_Back_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE_BACK); }
    Topic_t* Main_Style_Coward_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE_COWARD); }
    Topic_t* Main_Style_Default_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE_DEFAULT); }
    Topic_t* Main_Style_Mage_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE_MAGE); }
    Topic_t* Main_Style_Warrior_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_STYLE_WARRIOR); }
    Topic_t* Main_Unclone_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_UNCLONE); }
    Topic_t* Main_Unfollow_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_UNFOLLOW); }
    Topic_t* Main_Unmember_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_UNMEMBER); }
    Topic_t* Main_Unsaddle_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_UNSADDLE); }
    Topic_t* Main_Unsettle_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_UNSETTLE); }
    Topic_t* Main_Unsneak_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_UNSNEAK); }
    Topic_t* Main_Unthrall_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_UNTHRALL); }
    Topic_t* Main_Vitality_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_VITALITY); }
    Topic_t* Main_Vitality2_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_VITALITY2); }
    Topic_t* Main_Vitality_Back_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_VITALITY_BACK); }
    Topic_t* Main_Vitality_Essential_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_VITALITY_ESSENTIAL); }
    Topic_t* Main_Vitality_Invulnerable_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_VITALITY_INVULNERABLE); }
    Topic_t* Main_Vitality_Mortal_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_VITALITY_MORTAL); }
    Topic_t* Main_Vitality_Protected_Topic() { NPCP_FORM(Topic_t, TOPIC_MAIN_VITALITY_PROTECTED); }
    Topic_t* Menu_Followers_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS); }
    Topic_t* Menu_Followers_Back_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_BACK); }
    Topic_t* Menu_Followers_Immobilize_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_IMMOBILIZE); }
    Topic_t* Menu_Followers_Mobilize_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_MOBILIZE); }
    Topic_t* Menu_Followers_Saddle_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_SADDLE); }
    Topic_t* Menu_Followers_Settle_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_SETTLE); }
    Topic_t* Menu_Followers_Sneak_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_SNEAK); }
    Topic_t* Menu_Followers_Stash_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_STASH); }
    Topic_t* Menu_Followers_Summon_All_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_SUMMON_ALL); }
    Topic_t* Menu_Followers_Summon_Immobile_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_SUMMON_IMMOBILE); }
    Topic_t* Menu_Followers_Summon_Mobile_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_SUMMON_MOBILE); }
    Topic_t* Menu_Followers_Unfollow_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_UNFOLLOW); }
    Topic_t* Menu_Followers_Unmember_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_UNMEMBER); }
    Topic_t* Menu_Followers_Unsaddle_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_UNSADDLE); }
    Topic_t* Menu_Followers_Unsettle_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_UNSETTLE); }
    Topic_t* Menu_Followers_Unsneak_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_FOLLOWERS_UNSNEAK); }

    // NPCP Topic Infos
    Topic_Info_t* Menu_Chests_Input_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_INPUT); }
    Topic_Info_t* Menu_Chests_Weapons_Swords_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_SWORDS); }
    Topic_Info_t* Menu_Chests_Weapons_Greatswords_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_GREATSWORDS); }
    Topic_Info_t* Menu_Chests_Weapons_Waraxes_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_WARAXES); }
    Topic_Info_t* Menu_Chests_Weapons_Battleaxes_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_BATTLEAXES); }
    Topic_Info_t* Menu_Chests_Weapons_Maces_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_MACES); }
    Topic_Info_t* Menu_Chests_Weapons_Warhammers_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_WARHAMMERS); }
    Topic_Info_t* Menu_Chests_Weapons_Daggers_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_DAGGERS); }
    Topic_Info_t* Menu_Chests_Weapons_Staves_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_STAVES); }
    Topic_Info_t* Menu_Chests_Weapons_Bows_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_BOWS); }
    Topic_Info_t* Menu_Chests_Weapons_Ammo_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_AMMO); }
    Topic_Info_t* Menu_Chests_Weapons_Others_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_WEAPONS_OTHERS); }
    Topic_Info_t* Menu_Chests_Apparel_Light_Armor_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_APPAREL_LIGHT_ARMOR); }
    Topic_Info_t* Menu_Chests_Apparel_Heavy_Armor_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_APPAREL_HEAVY_ARMOR); }
    Topic_Info_t* Menu_Chests_Apparel_Shields_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_APPAREL_SHIELDS); }
    Topic_Info_t* Menu_Chests_Apparel_Jewelry_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_APPAREL_JEWELRY); }
    Topic_Info_t* Menu_Chests_Apparel_Clothes_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_APPAREL_CLOTHES); }
    Topic_Info_t* Menu_Chests_Edibles_Potions_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_EDIBLES_POTIONS); }
    Topic_Info_t* Menu_Chests_Edibles_Poisons_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_EDIBLES_POISONS); }
    Topic_Info_t* Menu_Chests_Edibles_Ingredients_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_EDIBLES_INGREDIENTS); }
    Topic_Info_t* Menu_Chests_Edibles_Food_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_EDIBLES_FOOD); }
    Topic_Info_t* Menu_Chests_Misc_Soulgems_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_SOULGEMS); }
    Topic_Info_t* Menu_Chests_Misc_Scrolls_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_SCROLLS); }
    Topic_Info_t* Menu_Chests_Misc_Metals_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_METALS); }
    Topic_Info_t* Menu_Chests_Misc_Leather_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_LEATHER); }
    Topic_Info_t* Menu_Chests_Misc_Gems_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_GEMS); }
    Topic_Info_t* Menu_Chests_Misc_Clutter_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_CLUTTER); }
    Topic_Info_t* Menu_Chests_Misc_Keys_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_KEYS); }
    Topic_Info_t* Menu_Chests_Misc_Others_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_MISC_OTHERS); }
    Topic_Info_t* Menu_Chests_Books_Spell_Tomes_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_SPELL_TOMES); }
    Topic_Info_t* Menu_Chests_Books_Recipes_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_RECIPES); }
    Topic_Info_t* Menu_Chests_Books_A_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_A); }
    Topic_Info_t* Menu_Chests_Books_B_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_B); }
    Topic_Info_t* Menu_Chests_Books_C_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_C); }
    Topic_Info_t* Menu_Chests_Books_D_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_D); }
    Topic_Info_t* Menu_Chests_Books_E_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_E); }
    Topic_Info_t* Menu_Chests_Books_F_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_F); }
    Topic_Info_t* Menu_Chests_Books_G_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_G); }
    Topic_Info_t* Menu_Chests_Books_H_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_H); }
    Topic_Info_t* Menu_Chests_Books_I_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_I); }
    Topic_Info_t* Menu_Chests_Books_J_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_J); }
    Topic_Info_t* Menu_Chests_Books_K_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_K); }
    Topic_Info_t* Menu_Chests_Books_L_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_L); }
    Topic_Info_t* Menu_Chests_Books_M_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_M); }
    Topic_Info_t* Menu_Chests_Books_N_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_N); }
    Topic_Info_t* Menu_Chests_Books_O_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_O); }
    Topic_Info_t* Menu_Chests_Books_P_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_P); }
    Topic_Info_t* Menu_Chests_Books_Q_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_Q); }
    Topic_Info_t* Menu_Chests_Books_R_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_R); }
    Topic_Info_t* Menu_Chests_Books_S_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_S); }
    Topic_Info_t* Menu_Chests_Books_T_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_T); }
    Topic_Info_t* Menu_Chests_Books_U_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_U); }
    Topic_Info_t* Menu_Chests_Books_V_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_V); }
    Topic_Info_t* Menu_Chests_Books_W_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_W); }
    Topic_Info_t* Menu_Chests_Books_X_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_X); }
    Topic_Info_t* Menu_Chests_Books_Y_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_Y); }
    Topic_Info_t* Menu_Chests_Books_Z_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_Z); }
    Topic_Info_t* Menu_Chests_Books_Others_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_BOOKS_OTHERS); }
    Topic_Info_t* Menu_Chests_Custom_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM); }
    Topic_Info_t* Menu_Chests_Custom_00_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_00); }
    Topic_Info_t* Menu_Chests_Custom_01_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_01); }
    Topic_Info_t* Menu_Chests_Custom_02_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_02); }
    Topic_Info_t* Menu_Chests_Custom_03_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_03); }
    Topic_Info_t* Menu_Chests_Custom_04_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_04); }
    Topic_Info_t* Menu_Chests_Custom_05_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_05); }
    Topic_Info_t* Menu_Chests_Custom_06_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_06); }
    Topic_Info_t* Menu_Chests_Custom_07_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_07); }
    Topic_Info_t* Menu_Chests_Custom_08_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_08); }
    Topic_Info_t* Menu_Chests_Custom_09_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_09); }
    Topic_Info_t* Menu_Chests_Custom_10_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_10); }
    Topic_Info_t* Menu_Chests_Custom_11_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_11); }
    Topic_Info_t* Menu_Chests_Custom_12_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_12); }
    Topic_Info_t* Menu_Chests_Custom_13_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_13); }
    Topic_Info_t* Menu_Chests_Custom_14_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_14); }
    Topic_Info_t* Menu_Chests_Custom_15_Topic_Info() { NPCP_FORM(Topic_Info_t, TOPIC_INFO_MENU_CHESTS_CUSTOM_15); }

    // NPCP Weapons
    Weapon_t* Blank_Weapon() { NPCP_FORM(Weapon_t, WEAPON_BLANK); }

    #undef NPCP_FORM

    #undef FORM

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            auto lambda = [](Selfless_t*) -> RETURN_                    \
            {                                                           \
                return Consts::METHOD_();                               \
            };                                                          \
            ADD_CLASS_METHOD("doticu_npcp_consts", Selfless_t,          \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, lambda, __VA_ARGS__);             \
        W

        // Skyrim Actors
        ADD_GLOBAL("Player_Actor", 0, Actor_t*, Player_Actor);

        // Skyrim Quests
        ADD_GLOBAL("Bard_Songs_Quest", 0, Quest_t*, Bard_Songs_Quest);

        // NPCP Globals
        ADD_GLOBAL("Is_Installed_Global", 0, Global_t*, Is_Installed_Global);
        ADD_GLOBAL("Allow_Dialogue_For_All_Global", 0, Global_t*, Allow_Dialogue_For_All_Global);
        ADD_GLOBAL("Allow_Chatter_Global", 0, Global_t*, Allow_Chatter_Global);
        ADD_GLOBAL("Force_Clone_Uniques_Global", 0, Global_t*, Force_Clone_Uniques_Global);
        ADD_GLOBAL("Force_Clone_Generics_Global", 0, Global_t*, Force_Clone_Generics_Global);
        ADD_GLOBAL("Force_Unclone_Uniques_Global", 0, Global_t*, Force_Unclone_Uniques_Global);
        ADD_GLOBAL("Force_Unclone_Generics_Global", 0, Global_t*, Force_Unclone_Generics_Global);
        ADD_GLOBAL("No_Body_Percent_Global", 0, Global_t*, No_Body_Percent_Global);
        ADD_GLOBAL("No_Feet_Percent_Global", 0, Global_t*, No_Feet_Percent_Global);
        ADD_GLOBAL("No_Hands_Percent_Global", 0, Global_t*, No_Hands_Percent_Global);
        ADD_GLOBAL("No_Head_Percent_Global", 0, Global_t*, No_Head_Percent_Global);

        // NPCP Ints
        ADD_GLOBAL("NPCP_Major", 0, Int_t, NPCP_Major);
        ADD_GLOBAL("NPCP_Minor", 0, Int_t, NPCP_Minor);
        ADD_GLOBAL("NPCP_Patch", 0, Int_t, NPCP_Patch);

        // NPCP Quests
        ADD_GLOBAL("Main_Quest", 0, Quest_t*, Main_Quest);
        ADD_GLOBAL("Vars_Quest", 0, Quest_t*, Vars_Quest);
        ADD_GLOBAL("Funcs_Quest", 0, Quest_t*, Funcs_Quest);
        ADD_GLOBAL("Members_Quest", 0, Quest_t*, Members_Quest);
        ADD_GLOBAL("Followers_Quest", 0, Quest_t*, Followers_Quest);
        ADD_GLOBAL("Control_Quest", 0, Quest_t*, Control_Quest);

        #undef ADD_GLOBAL

        return true;
    }

}}}
