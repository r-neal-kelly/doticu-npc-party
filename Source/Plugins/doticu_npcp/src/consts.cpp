/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game_macros.h"

#include "consts.h"

namespace doticu_npcp {

    /* SKYRIM */

    maybe<Mod_t*>           Consts_t::Skyrim::Mod()                                         { DEFINE_MOD("Skyrim.esm"); }

    some<Actor_t*>          Consts_t::Skyrim::Actor::Player()                               { DEFINE_FORM(Mod(), Actor_t, 0x000014); }

    some<Armor_t*>          Consts_t::Skyrim::Armor::Belted_Tunic()                         { DEFINE_FORM(Mod(), Armor_t, 0x01BE1A); }
    some<Armor_t*>          Consts_t::Skyrim::Armor::Gold_Ring()                            { DEFINE_FORM(Mod(), Armor_t, 0x01CF2B); }

    some<Effect_Shader_t*>  Consts_t::Skyrim::Effect_Shader::Reanimate()                    { DEFINE_FORM(Mod(), Effect_Shader_t, 0x075272); }

    some<Faction_t*>        Consts_t::Skyrim::Faction::Bard_Singer_No_Autostart()           { DEFINE_FORM(Mod(), Faction_t, 0x0163FA); }
    some<Faction_t*>        Consts_t::Skyrim::Faction::Current_Follower()                   { DEFINE_FORM(Mod(), Faction_t, 0x05C84E); }
    some<Faction_t*>        Consts_t::Skyrim::Faction::Player_Follower()                    { DEFINE_FORM(Mod(), Faction_t, 0x084D1B); }
    some<Faction_t*>        Consts_t::Skyrim::Faction::Potential_Follower()                 { DEFINE_FORM(Mod(), Faction_t, 0x05C84D); }
    some<Faction_t*>        Consts_t::Skyrim::Faction::WI_No_Body_Cleanup()                 { DEFINE_FORM(Mod(), Faction_t, 0x09653A); }

    some<Global_t*>         Consts_t::Skyrim::Global::Player_Follower_Count()               { DEFINE_FORM(Mod(), Global_t, 0x0BCC98); }

    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Magic_Damage_Fire()                  { DEFINE_FORM(Mod(), Keyword_t, 0x01CEAD); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Magic_Damage_Frost()                 { DEFINE_FORM(Mod(), Keyword_t, 0x01CEAE); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Magic_Damage_Shock()                 { DEFINE_FORM(Mod(), Keyword_t, 0x01CEAF); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Magic_Vampire_Drain()                { DEFINE_FORM(Mod(), Keyword_t, 0x101BDE); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Vampire()                            { DEFINE_FORM(Mod(), Keyword_t, 0x0A82BB); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Vendor_Item_Staff()                  { DEFINE_FORM(Mod(), Keyword_t, 0x0937A4); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Sword()                  { DEFINE_FORM(Mod(), Keyword_t, 0x01E711); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Greatsword()             { DEFINE_FORM(Mod(), Keyword_t, 0x06D931); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Waraxe()                 { DEFINE_FORM(Mod(), Keyword_t, 0x01E712); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Battleaxe()              { DEFINE_FORM(Mod(), Keyword_t, 0x06D932); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Mace()                   { DEFINE_FORM(Mod(), Keyword_t, 0x01E714); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Warhammer()              { DEFINE_FORM(Mod(), Keyword_t, 0x06D930); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Dagger()                 { DEFINE_FORM(Mod(), Keyword_t, 0x01E713); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Bow()                    { DEFINE_FORM(Mod(), Keyword_t, 0x01E715); }
    some<Keyword_t*>        Consts_t::Skyrim::Keyword::Weapon_Type_Staff()                  { DEFINE_FORM(Mod(), Keyword_t, 0x01E716); }

    some<Misc_t*>           Consts_t::Skyrim::Misc::Gold()                                  { DEFINE_FORM(Mod(), Misc_t, 0x00000F); }

    some<Package_t*>        Consts_t::Skyrim::Package::Follow_Template()                    { DEFINE_FORM(Mod(), Package_t, 0x019B2C); }
    some<Package_t*>        Consts_t::Skyrim::Package::Follow_Player_Template()             { DEFINE_FORM(Mod(), Package_t, 0x0750BE); }
    some<Package_t*>        Consts_t::Skyrim::Package::Follow_And_Keep_Distance_Template()  { DEFINE_FORM(Mod(), Package_t, 0x06F8F0); }
    some<Package_t*>        Consts_t::Skyrim::Package::Follow_In_Single_File_Template()     { DEFINE_FORM(Mod(), Package_t, 0x0C5811); }
    some<Package_t*>        Consts_t::Skyrim::Package::Follower_Template()                  { DEFINE_FORM(Mod(), Package_t, 0x0D530D); }

    some<Perk_t*>           Consts_t::Skyrim::Perk::Vampire_Feed()                          { DEFINE_FORM(Mod(), Perk_t, 0x0CF02C); }

    some<Quest_t*>          Consts_t::Skyrim::Quest::Bard_Songs()                           { DEFINE_FORM(Mod(), Quest_t, 0x074A55); }
    some<Quest_t*>          Consts_t::Skyrim::Quest::Follower_Dialogue()                    { DEFINE_FORM(Mod(), Quest_t, 0x0750BA); }
    some<Quest_t*>          Consts_t::Skyrim::Quest::Player_Vampire()                       { DEFINE_FORM(Mod(), Quest_t, 0x0EAFD5); }
    some<Quest_t*>          Consts_t::Skyrim::Quest::WI_Change_Location_01()                { DEFINE_FORM(Mod(), Quest_t, 0x0350F4); }
    some<Quest_t*>          Consts_t::Skyrim::Quest::WI_Remove_Item_04()                    { DEFINE_FORM(Mod(), Quest_t, 0x034DAB); }

    some<Reference_t*>      Consts_t::Skyrim::Reference::Riverwood_Location_Center_Marker() { DEFINE_FORM(Mod(), Reference_t, 0x01BDF3); }

    some<Static_t*>         Consts_t::Skyrim::Static::X_Marker()                            { DEFINE_FORM(Mod(), Static_t, 0x00003B); }
    some<Static_t*>         Consts_t::Skyrim::Static::X_Marker_Heading()                    { DEFINE_FORM(Mod(), Static_t, 0x000034); }

    const Version_t<u16>    Consts_t::Skyrim::Version::Required()                           { DEFINE_VERSION(u16, 1, 5, 97, 0); }

    /* Dawnguard */

    maybe<Mod_t*>       Consts_t::Dawnguard::Mod()                                  { DEFINE_MOD("Dawnguard.esm"); }

    some<Faction_t*>    Consts_t::Dawnguard::Faction::DLC1_Thrall()                 { DEFINE_FORM(Mod(), Faction_t, 0x0162F7); }
    some<Faction_t*>    Consts_t::Dawnguard::Faction::DLC1_Vampire_Feed_No_Crime()  { DEFINE_FORM(Mod(), Faction_t, 0x014CBD); }

    /* SKSE */

    const Version_t<u16> Consts_t::SKSE::Version::Minimum() { DEFINE_VERSION(u16, 2, 0, 17); }

    /* NPCP */

    maybe<Mod_t*>               Consts_t::NPCP::Mod()                                       { DEFINE_MOD("doticu_npc_party.esp"); }

    some<Actor_Base_t*>         Consts_t::NPCP::Actor_Base::Menu()                          { DEFINE_FORM(Mod(), Actor_Base_t, 0x317447); }

    some<Armor_t*>              Consts_t::NPCP::Armor::Blank()                              { DEFINE_FORM(Mod(), Armor_t, 0x1EF2A5); }

    some<Cell_t*>               Consts_t::NPCP::Cell::Storage()                             { DEFINE_FORM(Mod(), Cell_t, 0x114F9C); }

    some<Container_t*>          Consts_t::NPCP::Container::Empty()                          { DEFINE_FORM(Mod(), Container_t, 0x0A5561); }
    some<Container_t*>          Consts_t::NPCP::Container::Outfit2()                        { DEFINE_FORM(Mod(), Container_t, 0x0B9A63); }
    some<Container_t*>          Consts_t::NPCP::Container::Immobile_Outfit2()               { DEFINE_FORM(Mod(), Container_t, 0x1663CE); }
    some<Container_t*>          Consts_t::NPCP::Container::Settler_Outfit2()                { DEFINE_FORM(Mod(), Container_t, 0x1663CD); }
    some<Container_t*>          Consts_t::NPCP::Container::Thrall_Outfit2()                 { DEFINE_FORM(Mod(), Container_t, 0x1663CC); }
    some<Container_t*>          Consts_t::NPCP::Container::Follower_Outfit2()               { DEFINE_FORM(Mod(), Container_t, 0x1663C7); }

    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu()                     { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x32674B); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Chests()              { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x32674F); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Chests_Weapons()      { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x32B851); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Chests_Apparel()      { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x32B853); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Chests_Edibles()      { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x32B855); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Chests_Misc()         { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x32B857); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Chests_Books()        { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x32B859); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Chests_Custom()       { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x3C37BA); }
    some<Dialogue_Branch_t*>    Consts_t::NPCP::Dialogue_Branch::Menu_Followers()           { DEFINE_FORM(Mod(), Dialogue_Branch_t, 0x344DE2); }

    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_00()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37BF); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_01()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37C1); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_02()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37C3); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_03()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37C5); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_04()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37C7); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_05()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37C9); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_06()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37CB); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_07()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37CD); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_08()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37CF); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_09()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37D1); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_10()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37D3); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_11()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37D5); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_12()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37D7); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_13()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37D9); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_14()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37DB); }
    some<Dialogue_Topic_t*>     Consts_t::NPCP::Dialogue_Topic::Menu_Chests_Custom_15()     { DEFINE_FORM(Mod(), Dialogue_Topic_t, 0x3C37DD); }

    some<Faction_t*>            Consts_t::NPCP::Faction::Horse()                            { DEFINE_FORM(Mod(), Faction_t, 0x354111); }
    some<Faction_t*>            Consts_t::NPCP::Faction::Member()                           { DEFINE_FORM(Mod(), Faction_t, 0x091154); }

    some<Form_List_t*>          Consts_t::NPCP::Form_List::Is_Saddler_Sitting_Globals()     { DEFINE_FORM(Mod(), Form_List_t, 0x395E54); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Expo_Cell_Markers()              { DEFINE_FORM(Mod(), Form_List_t, 0x2928AF); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Settler_Markers()                { DEFINE_FORM(Mod(), Form_List_t, 0x00B46E); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Settler_Packages()               { DEFINE_FORM(Mod(), Form_List_t, 0x3D2B03); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Settler_Sleeper_Packages()       { DEFINE_FORM(Mod(), Form_List_t, 0x3DCD0C); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Settler_Sitter_Packages()        { DEFINE_FORM(Mod(), Form_List_t, 0x3E1E18); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Settler_Eater_Packages()         { DEFINE_FORM(Mod(), Form_List_t, 0x3DCD0D); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Settler_Guard_Packages()         { DEFINE_FORM(Mod(), Form_List_t, 0x3DCD0E); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Follower_Sojourner_Packages()    { DEFINE_FORM(Mod(), Form_List_t, 0x40652D); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Expoee_Buttons()                 { DEFINE_FORM(Mod(), Form_List_t, 0x3C88DF); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Expoee_Markers()                 { DEFINE_FORM(Mod(), Form_List_t, 0x3C88E0); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Main_Branches()                  { DEFINE_FORM(Mod(), Form_List_t, 0x41748B); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Main_Direct_Branches()           { DEFINE_FORM(Mod(), Form_List_t, 0x41748C); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Main_Outfit_Branches()           { DEFINE_FORM(Mod(), Form_List_t, 0x41748D); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Main_Style_Branches()            { DEFINE_FORM(Mod(), Form_List_t, 0x41748E); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Main_Vitality_Branches()         { DEFINE_FORM(Mod(), Form_List_t, 0x41748F); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Main_Female_Topics()             { DEFINE_FORM(Mod(), Form_List_t, 0x417492); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Main_Male_Topics()               { DEFINE_FORM(Mod(), Form_List_t, 0x417493); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Female_Voice_Types()             { DEFINE_FORM(Mod(), Form_List_t, 0x417494); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Male_Voice_Types()               { DEFINE_FORM(Mod(), Form_List_t, 0x417495); }
    some<Form_List_t*>          Consts_t::NPCP::Form_List::Voice_Quests()                   { DEFINE_FORM(Mod(), Form_List_t, 0x4216D4); }

    some<Furniture_t*>          Consts_t::NPCP::Furniture::Bedroll()                        { DEFINE_FORM(Mod(), Furniture_t, 0x3E7F15); }

    some<Global_t*>             Consts_t::NPCP::Global::Is_Initialized()                    { DEFINE_FORM(Mod(), Global_t, 0x189ADD); }
    some<Global_t*>             Consts_t::NPCP::Global::Do_Allow_Dialogue_For_All()         { DEFINE_FORM(Mod(), Global_t, 0x3B4463); }
    some<Global_t*>             Consts_t::NPCP::Global::Do_Allow_Chatter()                  { DEFINE_FORM(Mod(), Global_t, 0x3B9568); }
    some<Global_t*>             Consts_t::NPCP::Global::Do_Force_Clone_Uniques()            { DEFINE_FORM(Mod(), Global_t, 0x05244D); }
    some<Global_t*>             Consts_t::NPCP::Global::Do_Force_Clone_Generics()           { DEFINE_FORM(Mod(), Global_t, 0x05244E); }
    some<Global_t*>             Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()          { DEFINE_FORM(Mod(), Global_t, 0x05244F); }
    some<Global_t*>             Consts_t::NPCP::Global::Do_Force_Unclone_Generics()         { DEFINE_FORM(Mod(), Global_t, 0x052450); }
    some<Global_t*>             Consts_t::NPCP::Global::Do_Level_Followers()                { DEFINE_FORM(Mod(), Global_t, 0x3B4464); }
    some<Global_t*>             Consts_t::NPCP::Global::Empty_Outfit_Body_Percent()         { DEFINE_FORM(Mod(), Global_t, 0x193CEA); }
    some<Global_t*>             Consts_t::NPCP::Global::Empty_Outfit_Feet_Percent()         { DEFINE_FORM(Mod(), Global_t, 0x193CE7); }
    some<Global_t*>             Consts_t::NPCP::Global::Empty_Outfit_Hands_Percent()        { DEFINE_FORM(Mod(), Global_t, 0x193CE8); }
    some<Global_t*>             Consts_t::NPCP::Global::Empty_Outfit_Head_Percent()         { DEFINE_FORM(Mod(), Global_t, 0x193CE6); }

    some<Leveled_Actor_Base_t*> Consts_t::NPCP::Leveled_Actor_Base::Horse()                 { DEFINE_FORM(Mod(), Leveled_Actor_Base_t, 0x354127); }

    some<Location_t*>           Consts_t::NPCP::Location::Expo()                            { DEFINE_FORM(Mod(), Location_t, 0x27E48E); }

    some<Magic_Effect_t*>       Consts_t::NPCP::Magic_Effect::Reanimate()                   { DEFINE_FORM(Mod(), Magic_Effect_t, 0x3AF361); }
    some<Magic_Effect_t*>       Consts_t::NPCP::Magic_Effect::Retreat()                     { DEFINE_FORM(Mod(), Magic_Effect_t, 0x2DF8FA); }

    some<Misc_t*>               Consts_t::NPCP::Misc::Form_Vector()                         { DEFINE_FORM(Mod(), Misc_t, 0x15C1B2); }

    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Member()                       { DEFINE_FORM(Mod(), Misc_t, 0x000D75); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Generic()                      { DEFINE_FORM(Mod(), Misc_t, 0x003DFE); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Clone()                        { DEFINE_FORM(Mod(), Misc_t, 0x003DFC); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Greeter()                      { DEFINE_FORM(Mod(), Misc_t, 0x057384); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Movee()                        { DEFINE_FORM(Mod(), Misc_t, 0x1612B3); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Immobile()                     { DEFINE_FORM(Mod(), Misc_t, 0x000D77); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Settler()                      { DEFINE_FORM(Mod(), Misc_t, 0x000D73); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Settler_Sleeper()              { DEFINE_FORM(Mod(), Misc_t, 0x3D7C07); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Settler_Sitter()               { DEFINE_FORM(Mod(), Misc_t, 0x3E1E16); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Settler_Eater()                { DEFINE_FORM(Mod(), Misc_t, 0x3D7C05); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Settler_Guard()                { DEFINE_FORM(Mod(), Misc_t, 0x3D7C08); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Thrall()                       { DEFINE_FORM(Mod(), Misc_t, 0x011E90); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Paralyzed()                    { DEFINE_FORM(Mod(), Misc_t, 0x12E4A7); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Mannequin()                    { DEFINE_FORM(Mod(), Misc_t, 0x264F42); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Display()                      { DEFINE_FORM(Mod(), Misc_t, 0x13D7AC); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Reanimated()                   { DEFINE_FORM(Mod(), Misc_t, 0x1E4E9D); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Banished()                     { DEFINE_FORM(Mod(), Misc_t, 0x003DFD); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Default_Style()                { DEFINE_FORM(Mod(), Misc_t, 0x0A045D); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Warrior_Style()                { DEFINE_FORM(Mod(), Misc_t, 0x0A0460); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Mage_Style()                   { DEFINE_FORM(Mod(), Misc_t, 0x0A045F); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Archer_Style()                 { DEFINE_FORM(Mod(), Misc_t, 0x0A045E); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Coward_Style()                 { DEFINE_FORM(Mod(), Misc_t, 0x2D56F3); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Mortal_Vitality()              { DEFINE_FORM(Mod(), Misc_t, 0x0A045B); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Protected_Vitality()           { DEFINE_FORM(Mod(), Misc_t, 0x0A045A); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Essential_Vitality()           { DEFINE_FORM(Mod(), Misc_t, 0x0A0459); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Invulnerable_Vitality()        { DEFINE_FORM(Mod(), Misc_t, 0x0A045C); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Follower()                     { DEFINE_FORM(Mod(), Misc_t, 0x000D84); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Sneak_Follower()               { DEFINE_FORM(Mod(), Misc_t, 0x000D85); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Sojourner_Follower()           { DEFINE_FORM(Mod(), Misc_t, 0x401417); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Active_Sojourner_Follower()    { DEFINE_FORM(Mod(), Misc_t, 0x40651D); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Saddler()                      { DEFINE_FORM(Mod(), Misc_t, 0x34F000); }
    some<Misc_t*>               Consts_t::NPCP::Misc::Token::Retreater()                    { DEFINE_FORM(Mod(), Misc_t, 0x2F3D00); }

    some<Outfit_t*>             Consts_t::NPCP::Outfit::Empty()                             { DEFINE_FORM(Mod(), Outfit_t, 0x0C3C64); }

    some<Package_t*>            Consts_t::NPCP::Package::Greeter()                          { DEFINE_FORM(Mod(), Package_t, 0x057385); }
    some<Package_t*>            Consts_t::NPCP::Package::Menu_Exit()                        { DEFINE_FORM(Mod(), Package_t, 0x3309E0); }

    some<Perk_t*>               Consts_t::NPCP::Perk::Kiss_Thrall()                         { DEFINE_FORM(Mod(), Perk_t, 0x07CD48); }
    some<Perk_t*>               Consts_t::NPCP::Perk::Reanimate()                           { DEFINE_FORM(Mod(), Perk_t, 0x1DFD9C); }
    some<Perk_t*>               Consts_t::NPCP::Perk::Resurrect()                           { DEFINE_FORM(Mod(), Perk_t, 0x0D2F7C); }
    some<Perk_t*>               Consts_t::NPCP::Perk::Unparalyze()                          { DEFINE_FORM(Mod(), Perk_t, 0x16B4D1); }

    some<Quest_t*>              Consts_t::NPCP::Quest::Main()                               { DEFINE_FORM(Mod(), Quest_t, 0x005385); }
    some<Quest_t*>              Consts_t::NPCP::Quest::Vars()                               { DEFINE_FORM(Mod(), Quest_t, 0x003DFF); }
    some<Quest_t*>              Consts_t::NPCP::Quest::Funcs()                              { DEFINE_FORM(Mod(), Quest_t, 0x005384); }
    some<Quest_t*>              Consts_t::NPCP::Quest::Members()                            { DEFINE_FORM(Mod(), Quest_t, 0x00184C); }
    some<Quest_t*>              Consts_t::NPCP::Quest::Followers()                          { DEFINE_FORM(Mod(), Quest_t, 0x000D83); }
    some<Quest_t*>              Consts_t::NPCP::Quest::Control()                            { DEFINE_FORM(Mod(), Quest_t, 0x000D7F); }

    some<Reference_t*>          Consts_t::NPCP::Reference::Buffer_Container()               { DEFINE_FORM(Mod(), Reference_t, 0x3C37A9); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Expo_Exit_Door()                 { DEFINE_FORM(Mod(), Reference_t, 0x25AB08); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Cell_Marker()                    { DEFINE_FORM(Mod(), Reference_t, 0x15C1AE); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Expo_Antechamber_Marker()        { DEFINE_FORM(Mod(), Reference_t, 0x2979B0); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Storage_Marker()                 { DEFINE_FORM(Mod(), Reference_t, 0x114F9D); }

    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Input()                { DEFINE_FORM(Mod(), Reference_t, 0x395E55); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Swords()               { DEFINE_FORM(Mod(), Reference_t, 0x30D20A); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Greatswords()          { DEFINE_FORM(Mod(), Reference_t, 0x30D20B); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Waraxes()              { DEFINE_FORM(Mod(), Reference_t, 0x30D20C); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Battleaxes()           { DEFINE_FORM(Mod(), Reference_t, 0x30D20D); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Maces()                { DEFINE_FORM(Mod(), Reference_t, 0x30D20E); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Warhammers()           { DEFINE_FORM(Mod(), Reference_t, 0x30D20F); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Daggers()              { DEFINE_FORM(Mod(), Reference_t, 0x30D210); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Staves()               { DEFINE_FORM(Mod(), Reference_t, 0x30D212); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Bows()                 { DEFINE_FORM(Mod(), Reference_t, 0x30D211); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Ammo()                 { DEFINE_FORM(Mod(), Reference_t, 0x30D23D); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Other_Weapons()        { DEFINE_FORM(Mod(), Reference_t, 0x30D213); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Light_Armor()          { DEFINE_FORM(Mod(), Reference_t, 0x30D214); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Heavy_Armor()          { DEFINE_FORM(Mod(), Reference_t, 0x30D215); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Shields()              { DEFINE_FORM(Mod(), Reference_t, 0x30D216); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Jewelry()              { DEFINE_FORM(Mod(), Reference_t, 0x30D217); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Clothes()              { DEFINE_FORM(Mod(), Reference_t, 0x30D218); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Potions()              { DEFINE_FORM(Mod(), Reference_t, 0x30D219); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Poisons()              { DEFINE_FORM(Mod(), Reference_t, 0x30D21A); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Ingredients()          { DEFINE_FORM(Mod(), Reference_t, 0x30D23E); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Food()                 { DEFINE_FORM(Mod(), Reference_t, 0x30D21B); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Soulgems()             { DEFINE_FORM(Mod(), Reference_t, 0x30D240); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Scrolls()              { DEFINE_FORM(Mod(), Reference_t, 0x30D23F); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Metals()               { DEFINE_FORM(Mod(), Reference_t, 0x30D239); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Leather()              { DEFINE_FORM(Mod(), Reference_t, 0x30D23A); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Gems()                 { DEFINE_FORM(Mod(), Reference_t, 0x30D23B); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Clutter()              { DEFINE_FORM(Mod(), Reference_t, 0x30D23C); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Keys()                 { DEFINE_FORM(Mod(), Reference_t, 0x30D241); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Misc()                 { DEFINE_FORM(Mod(), Reference_t, 0x30D242); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Spell_Tomes()          { DEFINE_FORM(Mod(), Reference_t, 0x30D21C); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Recipes()              { DEFINE_FORM(Mod(), Reference_t, 0x30D21D); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::A_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D21E); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::B_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D21F); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::C_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D220); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::D_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D221); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::E_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D222); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::F_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D223); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::G_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D224); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::H_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D225); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::I_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D226); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::J_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D227); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::K_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D228); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::L_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D229); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::M_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D22A); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::N_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D22B); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::O_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D22C); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::P_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D22D); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Q_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D22E); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::R_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D22F); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::S_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D230); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::T_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D231); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::U_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D232); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::V_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D233); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::W_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D234); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::X_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D235); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Y_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D236); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Z_Books()              { DEFINE_FORM(Mod(), Reference_t, 0x30D237); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Other_Books()          { DEFINE_FORM(Mod(), Reference_t, 0x30D238); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_00()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37AA); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_01()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37AB); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_02()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37AC); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_03()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37AD); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_04()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37AE); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_05()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37AF); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_06()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B0); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_07()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B1); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_08()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B2); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_09()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B3); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_10()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B4); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_11()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B5); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_12()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B6); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_13()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B7); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_14()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B8); }
    some<Reference_t*>          Consts_t::NPCP::Reference::Category::Custom_15()            { DEFINE_FORM(Mod(), Reference_t, 0x3C37B9); }

    some<Spell_t*>              Consts_t::NPCP::Spell::Reanimate_Ability()                  { DEFINE_FORM(Mod(), Spell_t, 0x3AF362); }
    some<Spell_t*>              Consts_t::NPCP::Spell::Retreat_Ability()                    { DEFINE_FORM(Mod(), Spell_t, 0x2F3CFF); }

    const Version_t<u16>        Consts_t::NPCP::Version::Current()                          { DEFINE_VERSION(u16, 0, 10, 0); }

    some<Weapon_t*>             Consts_t::NPCP::Weapon::Blank()                             { DEFINE_FORM(Mod(), Weapon_t, 0x0C8D65); }

}
