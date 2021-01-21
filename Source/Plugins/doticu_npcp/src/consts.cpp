/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game_macros.h"

#include "consts.h"

namespace doticu_npcp {

    const Version_t<u16> Consts_t::Skyrim::Required_Version() { DEFINE_VERSION(u16, 1, 5, 97, 0); }

    const Version_t<u16> Consts_t::SKSE::Minimum_Version() { DEFINE_VERSION(u16, 2, 0, 17); }

    const Version_t<u16> Consts_t::NPCP::Current_Version() { DEFINE_VERSION(u16, 0, 10, 0); }

}

/*#include "game.h"
#include "utils.h"

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

        // Skyrim Packages
        PACKAGE_TEMPLATE_FOLLOW                     = 0x019B2C,
        PACKAGE_TEMPLATE_FOLLOW_PLAYER              = 0x0750BE,
        PACKAGE_TEMPLATE_FOLLOW_AND_KEEP_DISTANCE   = 0x06F8F0,
        PACKAGE_TEMPLATE_FOLLOW_IN_SINGLE_FILE      = 0x0C5811,
        PACKAGE_TEMPLATE_FOLLOWER                   = 0x0D530D,

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
        STATIC_MARKER_X_DIRECTED                    = 0x000034,
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

    // Skyrim Packages
    Package_t* Follow_Template_Package() { SKYRIM_FORM(Package_t, PACKAGE_TEMPLATE_FOLLOW); }
    Package_t* Follow_Player_Template_Package() { SKYRIM_FORM(Package_t, PACKAGE_TEMPLATE_FOLLOW_PLAYER); }
    Package_t* Follow_And_Keep_Distance_Template_Package() { SKYRIM_FORM(Package_t, PACKAGE_TEMPLATE_FOLLOW_AND_KEEP_DISTANCE); }
    Package_t* Follow_In_Single_File_Template_Package() { SKYRIM_FORM(Package_t, PACKAGE_TEMPLATE_FOLLOW_IN_SINGLE_FILE); }
    Package_t* Follower_Template_Package() { SKYRIM_FORM(Package_t, PACKAGE_TEMPLATE_FOLLOWER); }

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
    Static_t* Directed_X_Marker_Static() { SKYRIM_FORM(Static_t, STATIC_MARKER_X_DIRECTED); }

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
        BRANCH_MENU                                 = 0x32674B,
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
        FORMLIST_PACKAGES_SETTLER                   = 0x3D2B03,
        FORMLIST_PACKAGES_SETTLER_SLEEPER           = 0x3DCD0C,
        FORMLIST_PACKAGES_SETTLER_SITTER            = 0x3E1E18,
        FORMLIST_PACKAGES_SETTLER_EATER             = 0x3DCD0D,
        FORMLIST_PACKAGES_SETTLER_GUARD             = 0x3DCD0E,
        FORMLIST_PACKAGES_FOLLOWER_SOJOURNER        = 0x40652D,
        FORMLIST_BUTTONS_EXPOEE                     = 0x3C88DF,
        FORMLIST_MARKERS_EXPOEE                     = 0x3C88E0,
        FORMLIST_BRANCHES_MAIN                      = 0x41748B,
        FORMLIST_BRANCHES_MAIN_DIRECT               = 0x41748C,
        FORMLIST_BRANCHES_MAIN_OUTFIT               = 0x41748D,
        FORMLIST_BRANCHES_MAIN_STYLE                = 0x41748E,
        FORMLIST_BRANCHES_MAIN_VITALITY             = 0x41748F,
        FORMLIST_TOPICS_FEMALE_MAIN                 = 0x417492,
        FORMLIST_TOPICS_MALE_MAIN                   = 0x417493,
        FORMLIST_VOICE_TYPES_FEMALE                 = 0x417494,
        FORMLIST_VOICE_TYPES_MALE                   = 0x417495,

        // NPCP Furnitures
        FURNITURE_BEDROLL                           = 0x3E7F15,

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
        MISC_TOKEN_FOLLOWER_SOJOURNER               = 0x401417,
        MISC_TOKEN_FOLLOWER_SOJOURNER_ACTIVE        = 0x40651D,
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
        MISC_TOKEN_SETTLER_SLEEPER                  = 0x3D7C07,
        MISC_TOKEN_SETTLER_SITTER                   = 0x3E1E16,
        MISC_TOKEN_SETTLER_EATER                    = 0x3D7C05,
        MISC_TOKEN_SETTLER_GUARD                    = 0x3D7C08,
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
        PACKAGE_GREETER                             = 0x057385,
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
        QUEST_FEMALE_ARGONIAN                       = 0x3C376A,
        QUEST_FEMALE_COMMANDER                      = 0x3C376B,
        QUEST_FEMALE_COMMONER                       = 0x3C376C,
        QUEST_FEMALE_CONDESCENDING                  = 0x3C376D,
        QUEST_FEMALE_COWARD                         = 0x3C376E,
        QUEST_FEMALE_DARK_ELF                       = 0x3C376F,
        QUEST_FEMALE_ELF_HAUGHTY                    = 0x3C3770,
        QUEST_FEMALE_EVEN_TONED                     = 0x3C3771,
        QUEST_FEMALE_KHAJIIT                        = 0x3C3772,
        QUEST_FEMALE_NORD                           = 0x3C3773,
        QUEST_FEMALE_OLD_GRUMPY                     = 0x3C3774,
        QUEST_FEMALE_OLD_KINDLY                     = 0x3C3775,
        QUEST_FEMALE_ORC                            = 0x3C3776,
        QUEST_FEMALE_OTHER                          = 0x3C377A,
        QUEST_FEMALE_SHRILL                         = 0x3C3777,
        QUEST_FEMALE_SOLDIER                        = 0x3C3778,
        QUEST_FEMALE_SULTRY                         = 0x3C3779,
        QUEST_FEMALE_YOUNG_EAGER                    = 0x3B9565,
        QUEST_MALE_ARGONIAN                         = 0x3C377B,
        QUEST_MALE_BANDIT                           = 0x3C377C,
        QUEST_MALE_BRUTE                            = 0x3C377D,
        QUEST_MALE_COMMANDER                        = 0x3C377E,
        QUEST_MALE_COMMONER                         = 0x3C377F,
        QUEST_MALE_COMMONER_ACCENTED                = 0x3C3780,
        QUEST_MALE_CONDESCENDING                    = 0x3C3781,
        QUEST_MALE_COWARD                           = 0x3C3782,
        QUEST_MALE_DARK_ELF                         = 0x3C3783,
        QUEST_MALE_DRUNK                            = 0x3C3784,
        QUEST_MALE_ELF_HAUGHTY                      = 0x3C3785,
        QUEST_MALE_EVEN_TONED                       = 0x3C3786,
        QUEST_MALE_EVEN_TONED_ACCENTED              = 0x3C3787,
        QUEST_MALE_FORSWORN                         = 0x3C3788,
        QUEST_MALE_GUARD                            = 0x3C3789,
        QUEST_MALE_KHAJIIT                          = 0x3C378A,
        QUEST_MALE_NORD                             = 0x3C378B,
        QUEST_MALE_NORD_COMMANDER                   = 0x3C378C,
        QUEST_MALE_OLD_GRUMPY                       = 0x3C378D,
        QUEST_MALE_OLD_KINDLY                       = 0x3C378E,
        QUEST_MALE_ORC                              = 0x3C378F,
        QUEST_MALE_OTHER                            = 0x3C3792,
        QUEST_MALE_SLY_CYNICAL                      = 0x3C3790,
        QUEST_MALE_SOLDIER                          = 0x3C3791,
        QUEST_MALE_WARLOCK                          = 0x3C3793,
        QUEST_MALE_YOUNG_EAGER                      = 0x3C3794,

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

        // NPCP Reference Doors
        REFERENCE_DOOR_EXPO_EXIT                    = 0x25AB08,

        // NPCP Reference Markers
        REFERENCE_MARKER_CELL                       = 0x15C1AE,
        REFERENCE_MARKER_EXPO_ANTECHAMBER           = 0x2979B0,
        REFERENCE_MARKER_STORAGE                    = 0x114F9D,

        // NPCP Spells
        SPELL_ABILITY_REANIMATE                     = 0x3AF362,
        SPELL_ABILITY_RETREAT                       = 0x2F3CFF,

        // NPCP Topics
        TOPIC_MENU_CHESTS_CUSTOM_00                 = 0x3C37BF,
        TOPIC_MENU_CHESTS_CUSTOM_01                 = 0x3C37C1,
        TOPIC_MENU_CHESTS_CUSTOM_02                 = 0x3C37C3,
        TOPIC_MENU_CHESTS_CUSTOM_03                 = 0x3C37C5,
        TOPIC_MENU_CHESTS_CUSTOM_04                 = 0x3C37C7,
        TOPIC_MENU_CHESTS_CUSTOM_05                 = 0x3C37C9,
        TOPIC_MENU_CHESTS_CUSTOM_06                 = 0x3C37CB,
        TOPIC_MENU_CHESTS_CUSTOM_07                 = 0x3C37CD,
        TOPIC_MENU_CHESTS_CUSTOM_08                 = 0x3C37CF,
        TOPIC_MENU_CHESTS_CUSTOM_09                 = 0x3C37D1,
        TOPIC_MENU_CHESTS_CUSTOM_10                 = 0x3C37D3,
        TOPIC_MENU_CHESTS_CUSTOM_11                 = 0x3C37D5,
        TOPIC_MENU_CHESTS_CUSTOM_12                 = 0x3C37D7,
        TOPIC_MENU_CHESTS_CUSTOM_13                 = 0x3C37D9,
        TOPIC_MENU_CHESTS_CUSTOM_14                 = 0x3C37DB,
        TOPIC_MENU_CHESTS_CUSTOM_15                 = 0x3C37DD,

        // NPCP Weapons
        WEAPON_BLANK                                = 0x0C8D65,
    };

    #define NPCP_FORM(TYPE_, MOD_ID_) FORM(NPCP_Form, TYPE_, MOD_ID_);

    // NPCP Actor Base
    Actor_Base_t* Menu_Actor_Base() { NPCP_FORM(Actor_Base_t, ACTOR_BASE_MENU); }

    // NPCP Armors
    Armor_t* Blank_Armor() { NPCP_FORM(Armor_t, ARMOR_BLANK); }

    // NPCP Branches
    Branch_t* Menu_Branch() { NPCP_FORM(Branch_t, BRANCH_MENU); }
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
    Formlist_t* Settler_Packages_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_PACKAGES_SETTLER); }
    Formlist_t* Settler_Sleeper_Packages_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_PACKAGES_SETTLER_SLEEPER); }
    Formlist_t* Settler_Sitter_Packages_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_PACKAGES_SETTLER_SITTER); }
    Formlist_t* Settler_Eater_Packages_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_PACKAGES_SETTLER_EATER); }
    Formlist_t* Settler_Guard_Packages_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_PACKAGES_SETTLER_GUARD); }
    Formlist_t* Follower_Sojourner_Packages_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_PACKAGES_FOLLOWER_SOJOURNER); }
    Formlist_t* Expoee_Buttons_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_BUTTONS_EXPOEE); }
    Formlist_t* Expoee_Markers_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_MARKERS_EXPOEE); }
    Formlist_t* Main_Branches_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_BRANCHES_MAIN); }
    Formlist_t* Main_Direct_Branches_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_BRANCHES_MAIN_DIRECT); }
    Formlist_t* Main_Outfit_Branches_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_BRANCHES_MAIN_OUTFIT); }
    Formlist_t* Main_Style_Branches_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_BRANCHES_MAIN_STYLE); }
    Formlist_t* Main_Vitality_Branches_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_BRANCHES_MAIN_VITALITY); }
    Formlist_t* Main_Female_Topics_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_TOPICS_FEMALE_MAIN); }
    Formlist_t* Main_Male_Topics_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_TOPICS_MALE_MAIN); }
    Formlist_t* Female_Voice_Types_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_VOICE_TYPES_FEMALE); }
    Formlist_t* Male_Voice_Types_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_VOICE_TYPES_MALE); }

    // NPCP Furnitures
    Furniture_t* Bedroll_Furniture() { NPCP_FORM(Furniture_t, FURNITURE_BEDROLL); }

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
    Int_t NPCP_Patch() { return 16; } // set manually upon each release

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
    Misc_t* Settler_Sleeper_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SETTLER_SLEEPER); }
    Misc_t* Settler_Sitter_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SETTLER_SITTER); }
    Misc_t* Settler_Eater_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SETTLER_EATER); }
    Misc_t* Settler_Guard_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SETTLER_GUARD); }
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
    Misc_t* Sojourner_Follower_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER_SOJOURNER); }
    Misc_t* Active_Sojourner_Follower_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER_SOJOURNER_ACTIVE); }
    Misc_t* Saddler_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SADDLER); }
    Misc_t* Retreater_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_RETREATER); }

    // NPCP Misc
    Misc_t* Form_Vector() { NPCP_FORM(Misc_t, MISC_VECTOR_FORM); }

    // NPCP Outfits
    Outfit_t* Empty_Outfit() { NPCP_FORM(Outfit_t, OUTFIT_EMPTY); }

    // NPCP Packages
    Package_t* Greeter_Package() { NPCP_FORM(Package_t, PACKAGE_GREETER); }
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
    Quest_t* Female_Argonian_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_ARGONIAN); }
    Quest_t* Female_Commander_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_COMMANDER); }
    Quest_t* Female_Commoner_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_COMMONER); }
    Quest_t* Female_Condescending_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_CONDESCENDING); }
    Quest_t* Female_Coward_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_COWARD); }
    Quest_t* Female_Dark_Elf_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_DARK_ELF); }
    Quest_t* Female_Elf_Haughty_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_ELF_HAUGHTY); }
    Quest_t* Female_Even_Toned_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_EVEN_TONED); }
    Quest_t* Female_Khajiit_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_KHAJIIT); }
    Quest_t* Female_Nord_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_NORD); }
    Quest_t* Female_Old_Grumpy_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_OLD_GRUMPY); }
    Quest_t* Female_Old_Kindly_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_OLD_KINDLY); }
    Quest_t* Female_Orc_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_ORC); }
    Quest_t* Female_Other_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_OTHER); }
    Quest_t* Female_Shrill_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_SHRILL); }
    Quest_t* Female_Soldier_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_SOLDIER); }
    Quest_t* Female_Sultry_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_SULTRY); }
    Quest_t* Female_Young_Eager_Quest() { NPCP_FORM(Quest_t, QUEST_FEMALE_YOUNG_EAGER); }
    Quest_t* Male_Argonian_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_ARGONIAN); }
    Quest_t* Male_Bandit_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_BANDIT); }
    Quest_t* Male_Brute_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_BRUTE); }
    Quest_t* Male_Commander_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_COMMANDER); }
    Quest_t* Male_Commoner_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_COMMONER); }
    Quest_t* Male_Commoner_Accented_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_COMMONER_ACCENTED); }
    Quest_t* Male_Condescending_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_CONDESCENDING); }
    Quest_t* Male_Coward_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_COWARD); }
    Quest_t* Male_Dark_Elf_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_DARK_ELF); }
    Quest_t* Male_Drunk_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_DRUNK); }
    Quest_t* Male_Elf_Haughty_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_ELF_HAUGHTY); }
    Quest_t* Male_Even_Toned_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_EVEN_TONED); }
    Quest_t* Male_Even_Toned_Accented_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_EVEN_TONED_ACCENTED); }
    Quest_t* Male_Forsworn_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_FORSWORN); }
    Quest_t* Male_Guard_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_GUARD); }
    Quest_t* Male_Khajiit_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_KHAJIIT); }
    Quest_t* Male_Nord_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_NORD); }
    Quest_t* Male_Nord_Commander_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_NORD_COMMANDER); }
    Quest_t* Male_Old_Grumpy_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_OLD_GRUMPY); }
    Quest_t* Male_Old_Kindly_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_OLD_KINDLY); }
    Quest_t* Male_Orc_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_ORC); }
    Quest_t* Male_Other_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_OTHER); }
    Quest_t* Male_Sly_Cynical_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_SLY_CYNICAL); }
    Quest_t* Male_Soldier_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_SOLDIER); }
    Quest_t* Male_Warlock_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_WARLOCK); }
    Quest_t* Male_Young_Eager_Quest() { NPCP_FORM(Quest_t, QUEST_MALE_YOUNG_EAGER); }

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

    // NPCP Reference Doors
    Reference_t* Expo_Exit_Door() { NPCP_FORM(Reference_t, REFERENCE_DOOR_EXPO_EXIT); }

    // NPCP Reference Markers
    Reference_t* Cell_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_CELL); }
    Reference_t* Expo_Antechamber_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_EXPO_ANTECHAMBER); }
    Reference_t* Storage_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_STORAGE); }

    // NPCP Spells
    Spell_t* Reanimate_Ability_Spell() { NPCP_FORM(Spell_t, SPELL_ABILITY_REANIMATE); }
    Spell_t* Retreat_Ability_Spell() { NPCP_FORM(Spell_t, SPELL_ABILITY_RETREAT); }

    // NPCP Topics
    Topic_t* Menu_Chests_Custom_00_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_00); }
    Topic_t* Menu_Chests_Custom_01_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_01); }
    Topic_t* Menu_Chests_Custom_02_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_02); }
    Topic_t* Menu_Chests_Custom_03_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_03); }
    Topic_t* Menu_Chests_Custom_04_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_04); }
    Topic_t* Menu_Chests_Custom_05_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_05); }
    Topic_t* Menu_Chests_Custom_06_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_06); }
    Topic_t* Menu_Chests_Custom_07_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_07); }
    Topic_t* Menu_Chests_Custom_08_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_08); }
    Topic_t* Menu_Chests_Custom_09_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_09); }
    Topic_t* Menu_Chests_Custom_10_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_10); }
    Topic_t* Menu_Chests_Custom_11_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_11); }
    Topic_t* Menu_Chests_Custom_12_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_12); }
    Topic_t* Menu_Chests_Custom_13_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_13); }
    Topic_t* Menu_Chests_Custom_14_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_14); }
    Topic_t* Menu_Chests_Custom_15_Topic() { NPCP_FORM(Topic_t, TOPIC_MENU_CHESTS_CUSTOM_15); }

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

        #undef ADD_GLOBAL

        return true;
    }

}}}*/
