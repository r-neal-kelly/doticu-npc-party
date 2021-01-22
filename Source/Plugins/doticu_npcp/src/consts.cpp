/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game_macros.h"

#include "consts.h"

namespace doticu_npcp {

    /* SKYRIM */

    maybe<Mod_t*> Consts_t::Skyrim::Mod() { DEFINE_MOD("Skyrim.esm"); }

    some<Actor_t*> Consts_t::Skyrim::Actor::Player() { DEFINE_FORM(Mod(), Actor_t, 0x000014); }

    some<Armor_t*> Consts_t::Skyrim::Armor::Belted_Tunic()  { DEFINE_FORM(Mod(), Armor_t, 0x01BE1A); }
    some<Armor_t*> Consts_t::Skyrim::Armor::Gold_Ring()     { DEFINE_FORM(Mod(), Armor_t, 0x01CF2B); }

    some<Effect_Shader_t*> Consts_t::Skyrim::Effect_Shader::Reanimate() { DEFINE_FORM(Mod(), Effect_Shader_t, 0x075272); }

    some<Faction_t*> Consts_t::Skyrim::Faction::Bard_Singer_No_Autostart()  { DEFINE_FORM(Mod(), Faction_t, 0x0163FA); }
    some<Faction_t*> Consts_t::Skyrim::Faction::Current_Follower()          { DEFINE_FORM(Mod(), Faction_t, 0x05C84E); }
    some<Faction_t*> Consts_t::Skyrim::Faction::Player_Follower()           { DEFINE_FORM(Mod(), Faction_t, 0x084D1B); }
    some<Faction_t*> Consts_t::Skyrim::Faction::Potential_Follower()        { DEFINE_FORM(Mod(), Faction_t, 0x05C84D); }
    some<Faction_t*> Consts_t::Skyrim::Faction::WI_No_Body_Cleanup()        { DEFINE_FORM(Mod(), Faction_t, 0x09653A); }

    some<Global_t*> Consts_t::Skyrim::Global::Player_Follower_Count() { DEFINE_FORM(Mod(), Global_t, 0x0BCC98); }

    some<Keyword_t*> Consts_t::Skyrim::Keyword::Magic_Damage_Fire()         { DEFINE_FORM(Mod(), Keyword_t, 0x01CEAD); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Magic_Damage_Frost()        { DEFINE_FORM(Mod(), Keyword_t, 0x01CEAE); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Magic_Damage_Shock()        { DEFINE_FORM(Mod(), Keyword_t, 0x01CEAF); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Magic_Vampire_Drain()       { DEFINE_FORM(Mod(), Keyword_t, 0x101BDE); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Vampire()                   { DEFINE_FORM(Mod(), Keyword_t, 0x0A82BB); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Vendor_Item_Staff()         { DEFINE_FORM(Mod(), Keyword_t, 0x0937A4); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Sword()         { DEFINE_FORM(Mod(), Keyword_t, 0x01E711); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Greatsword()    { DEFINE_FORM(Mod(), Keyword_t, 0x06D931); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Waraxe()        { DEFINE_FORM(Mod(), Keyword_t, 0x01E712); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Battleaxe()     { DEFINE_FORM(Mod(), Keyword_t, 0x06D932); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Mace()          { DEFINE_FORM(Mod(), Keyword_t, 0x01E714); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Warhammer()     { DEFINE_FORM(Mod(), Keyword_t, 0x06D930); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Dagger()        { DEFINE_FORM(Mod(), Keyword_t, 0x01E713); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Bow()           { DEFINE_FORM(Mod(), Keyword_t, 0x01E715); }
    some<Keyword_t*> Consts_t::Skyrim::Keyword::Weapon_Type_Staff()         { DEFINE_FORM(Mod(), Keyword_t, 0x01E716); }

    some<Misc_t*> Consts_t::Skyrim::Misc::Gold() { DEFINE_FORM(Mod(), Misc_t, 0x00000F); }

    some<Package_t*> Consts_t::Skyrim::Package::Follow_Template()                   { DEFINE_FORM(Mod(), Package_t, 0x019B2C); }
    some<Package_t*> Consts_t::Skyrim::Package::Follow_Player_Template()            { DEFINE_FORM(Mod(), Package_t, 0x0750BE); }
    some<Package_t*> Consts_t::Skyrim::Package::Follow_And_Keep_Distance_Template() { DEFINE_FORM(Mod(), Package_t, 0x06F8F0); }
    some<Package_t*> Consts_t::Skyrim::Package::Follow_In_Single_File_Template()    { DEFINE_FORM(Mod(), Package_t, 0x0C5811); }
    some<Package_t*> Consts_t::Skyrim::Package::Follower_Template()                 { DEFINE_FORM(Mod(), Package_t, 0x0D530D); }

    some<Perk_t*> Consts_t::Skyrim::Perk::Vampire_Feed() { DEFINE_FORM(Mod(), Perk_t, 0x0CF02C); }

    some<Quest_t*> Consts_t::Skyrim::Quest::Bard_Songs()            { DEFINE_FORM(Mod(), Quest_t, 0x074A55); }
    some<Quest_t*> Consts_t::Skyrim::Quest::Follower_Dialogue()     { DEFINE_FORM(Mod(), Quest_t, 0x0750BA); }
    some<Quest_t*> Consts_t::Skyrim::Quest::Player_Vampire()        { DEFINE_FORM(Mod(), Quest_t, 0x0EAFD5); }
    some<Quest_t*> Consts_t::Skyrim::Quest::WI_Change_Location_01() { DEFINE_FORM(Mod(), Quest_t, 0x0350F4); }
    some<Quest_t*> Consts_t::Skyrim::Quest::WI_Remove_Item_04()     { DEFINE_FORM(Mod(), Quest_t, 0x034DAB); }

    some<Reference_t*> Consts_t::Skyrim::Reference::Riverwood_Location_Center_Marker() { DEFINE_FORM(Mod(), Reference_t, 0x01BDF3); }

    some<Static_t*> Consts_t::Skyrim::Static::X_Marker()            { DEFINE_FORM(Mod(), Static_t, 0x00003B); }
    some<Static_t*> Consts_t::Skyrim::Static::X_Marker_Heading()    { DEFINE_FORM(Mod(), Static_t, 0x000034); }

    const Version_t<u16> Consts_t::Skyrim::Version::Required() { DEFINE_VERSION(u16, 1, 5, 97, 0); }

    /* Dawnguard */

    maybe<Mod_t*> Consts_t::Dawnguard::Mod() { DEFINE_MOD("Dawnguard.esm"); }

    some<Faction_t*> Consts_t::Dawnguard::Faction::DLC1_Thrall()                { DEFINE_FORM(Mod(), Faction_t, 0x0162F7); }
    some<Faction_t*> Consts_t::Dawnguard::Faction::DLC1_Vampire_Feed_No_Crime() { DEFINE_FORM(Mod(), Faction_t, 0x014CBD); }

    /* SKSE */

    const Version_t<u16> Consts_t::SKSE::Version::Minimum() { DEFINE_VERSION(u16, 2, 0, 17); }

    /* NPCP */

    maybe<Mod_t*> Consts_t::NPCP::Mod() { DEFINE_MOD("doticu_npc_party.esp"); }

    some<Actor_Base_t*> Consts_t::NPCP::Actor_Base::Menu() { DEFINE_FORM(Mod(), Actor_Base_t, 0x317447); }

    some<Armor_t*> Consts_t::NPCP::Armor::Blank() { DEFINE_FORM(Mod(), Armor_t, 0x1EF2A5); }

    /*
        BRANCH_MENU                                 = 0x32674B,
        BRANCH_MENU_CHESTS                          = 0x32674F,
        BRANCH_MENU_CHESTS_APPAREL                  = 0x32B853,
        BRANCH_MENU_CHESTS_BOOKS                    = 0x32B859,
        BRANCH_MENU_CHESTS_CUSTOM                   = 0x3C37BA,
        BRANCH_MENU_CHESTS_EDIBLES                  = 0x32B855,
        BRANCH_MENU_CHESTS_MISC                     = 0x32B857,
        BRANCH_MENU_CHESTS_WEAPONS                  = 0x32B851,
        BRANCH_MENU_FOLLOWERS                       = 0x344DE2,
    */

    some<Cell_t*> Consts_t::NPCP::Cell::Storage() { DEFINE_FORM(Mod(), Cell_t, 0x114F9C); }

    some<Container_t*> Consts_t::NPCP::Container::Empty()               { DEFINE_FORM(Mod(), Container_t, 0x0A5561); }
    some<Container_t*> Consts_t::NPCP::Container::Outfit2()             { DEFINE_FORM(Mod(), Container_t, 0x0B9A63); }
    some<Container_t*> Consts_t::NPCP::Container::Immobile_Outfit2()    { DEFINE_FORM(Mod(), Container_t, 0x1663CE); }
    some<Container_t*> Consts_t::NPCP::Container::Settler_Outfit2()     { DEFINE_FORM(Mod(), Container_t, 0x1663CD); }
    some<Container_t*> Consts_t::NPCP::Container::Thrall_Outfit2()      { DEFINE_FORM(Mod(), Container_t, 0x1663CC); }
    some<Container_t*> Consts_t::NPCP::Container::Follower_Outfit2()    { DEFINE_FORM(Mod(), Container_t, 0x1663C7); }

    some<Faction_t*> Consts_t::NPCP::Faction::Horse()   { DEFINE_FORM(Mod(), Faction_t, 0x354111); }
    some<Faction_t*> Consts_t::NPCP::Faction::Member()  { DEFINE_FORM(Mod(), Faction_t, 0x091154); }

    some<Form_List_t*> Consts_t::NPCP::Form_List::Is_Saddler_Sitting_Globals()  { DEFINE_FORM(Mod(), Form_List_t, 0x395E54); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Expo_Cell_Markers()           { DEFINE_FORM(Mod(), Form_List_t, 0x2928AF); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Settler_Markers()             { DEFINE_FORM(Mod(), Form_List_t, 0x00B46E); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Settler_Packages()            { DEFINE_FORM(Mod(), Form_List_t, 0x3D2B03); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Settler_Sleeper_Packages()    { DEFINE_FORM(Mod(), Form_List_t, 0x3DCD0C); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Settler_Sitter_Packages()     { DEFINE_FORM(Mod(), Form_List_t, 0x3E1E18); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Settler_Eater_Packages()      { DEFINE_FORM(Mod(), Form_List_t, 0x3DCD0D); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Settler_Guard_Packages()      { DEFINE_FORM(Mod(), Form_List_t, 0x3DCD0E); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Follower_Sojourner_Packages() { DEFINE_FORM(Mod(), Form_List_t, 0x40652D); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Expoee_Buttons()              { DEFINE_FORM(Mod(), Form_List_t, 0x3C88DF); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Expoee_Markers()              { DEFINE_FORM(Mod(), Form_List_t, 0x3C88E0); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Main_Branches()               { DEFINE_FORM(Mod(), Form_List_t, 0x41748B); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Main_Direct_Branches()        { DEFINE_FORM(Mod(), Form_List_t, 0x41748C); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Main_Outfit_Branches()        { DEFINE_FORM(Mod(), Form_List_t, 0x41748D); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Main_Style_Branches()         { DEFINE_FORM(Mod(), Form_List_t, 0x41748E); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Main_Vitality_Branches()      { DEFINE_FORM(Mod(), Form_List_t, 0x41748F); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Main_Female_Topics()          { DEFINE_FORM(Mod(), Form_List_t, 0x417492); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Main_Male_Topics()            { DEFINE_FORM(Mod(), Form_List_t, 0x417493); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Female_Voice_Types()          { DEFINE_FORM(Mod(), Form_List_t, 0x417494); }
    some<Form_List_t*> Consts_t::NPCP::Form_List::Male_Voice_Types()            { DEFINE_FORM(Mod(), Form_List_t, 0x417495); }

    some<Furniture_t*> Consts_t::NPCP::Furniture::Bedroll() { DEFINE_FORM(Mod(), Furniture_t, 0x3E7F15); }

    some<Global_t*> Consts_t::NPCP::Global::Is_Installed()              { DEFINE_FORM(Mod(), Global_t, 0x189ADD); }
    some<Global_t*> Consts_t::NPCP::Global::Allow_Dialogue_For_All()    { DEFINE_FORM(Mod(), Global_t, 0x3B4463); }
    some<Global_t*> Consts_t::NPCP::Global::Allow_Chatter()             { DEFINE_FORM(Mod(), Global_t, 0x3B9568); }
    some<Global_t*> Consts_t::NPCP::Global::Force_Clone_Uniques()       { DEFINE_FORM(Mod(), Global_t, 0x05244D); }
    some<Global_t*> Consts_t::NPCP::Global::Force_Clone_Generics()      { DEFINE_FORM(Mod(), Global_t, 0x05244E); }
    some<Global_t*> Consts_t::NPCP::Global::Force_Unclone_Uniques()     { DEFINE_FORM(Mod(), Global_t, 0x05244F); }
    some<Global_t*> Consts_t::NPCP::Global::Force_Unclone_Generics()    { DEFINE_FORM(Mod(), Global_t, 0x052450); }
    some<Global_t*> Consts_t::NPCP::Global::Is_Leveling_Enabled()       { DEFINE_FORM(Mod(), Global_t, 0x3B4464); }
    some<Global_t*> Consts_t::NPCP::Global::No_Body_Percent()           { DEFINE_FORM(Mod(), Global_t, 0x193CEA); }
    some<Global_t*> Consts_t::NPCP::Global::No_Feet_Percent()           { DEFINE_FORM(Mod(), Global_t, 0x193CE7); }
    some<Global_t*> Consts_t::NPCP::Global::No_Hands_Percent()          { DEFINE_FORM(Mod(), Global_t, 0x193CE8); }
    some<Global_t*> Consts_t::NPCP::Global::No_Head_Percent()           { DEFINE_FORM(Mod(), Global_t, 0x193CE6); }

    /*
        LEVELED_ACTOR_HORSE                         = 0x354127,
    */

    /*
        LOCATION_EXPO                               = 0x27E48E,
    */

    /*
        MAGIC_EFFECT_REANIMATE                      = 0x3AF361,
        MAGIC_EFFECT_RETREAT                        = 0x2DF8FA,
    */

    /*
        MISC_VECTOR_FORM                            = 0x15C1B2,
    */

    /*
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
    */

    /*
        OUTFIT_EMPTY                                = 0x0C3C64,
    */

    /*
        PACKAGE_GREETER                             = 0x057385,
        PACKAGE_MENU_EXIT                           = 0x3309E0,
    */

    /*
        PERK_KISS_THRALL                            = 0x07CD48,
        PERK_REANIMATE                              = 0x1DFD9C,
        PERK_RESURRECT                              = 0x0D2F7C,
        PERK_UNPARALYZE                             = 0x16B4D1,
    */

    some<Quest_t*> Consts_t::NPCP::Quest::Main()        { DEFINE_FORM(Mod(), Quest_t, 0x005385); }
    some<Quest_t*> Consts_t::NPCP::Quest::Vars()        { DEFINE_FORM(Mod(), Quest_t, 0x003DFF); }
    some<Quest_t*> Consts_t::NPCP::Quest::Funcs()       { DEFINE_FORM(Mod(), Quest_t, 0x005384); }
    some<Quest_t*> Consts_t::NPCP::Quest::Members()     { DEFINE_FORM(Mod(), Quest_t, 0x00184C); }
    some<Quest_t*> Consts_t::NPCP::Quest::Followers()   { DEFINE_FORM(Mod(), Quest_t, 0x000D83); }
    some<Quest_t*> Consts_t::NPCP::Quest::Control()     { DEFINE_FORM(Mod(), Quest_t, 0x000D7F); }
    /*
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
    */

    /*
        REFERENCE_CONTAINER_BUFFER                  = 0x3C37A9,
        REFERENCE_DOOR_EXPO_EXIT                    = 0x25AB08,
        REFERENCE_MARKER_CELL                       = 0x15C1AE,
        REFERENCE_MARKER_EXPO_ANTECHAMBER           = 0x2979B0,
        REFERENCE_MARKER_STORAGE                    = 0x114F9D,
    */

    /*
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
    */

    /*
        SPELL_ABILITY_REANIMATE                     = 0x3AF362,
        SPELL_ABILITY_RETREAT                       = 0x2F3CFF,
    */

    /*
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
    */

    const Version_t<u16> Consts_t::NPCP::Version::Current() { DEFINE_VERSION(u16, 0, 10, 0); }

    some<Weapon_t*> Consts_t::NPCP::Weapon::Blank() { DEFINE_FORM(Mod(), Weapon_t, 0x0C8D65); }

}
