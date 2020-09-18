/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Consts {

    using namespace Papyrus;

    constexpr size_t MAX_MEMBERS = 1024;
    constexpr size_t MAX_FOLLOWERS = 16;

    String_t Class_Name();
    Class_Info_t* Class_Info();

    // Skyrim Actors
    Actor_t* Player_Actor();

    // Skyrim Armors
    Armor_t* Belted_Tunic_Armor();
    Armor_t* Gold_Ring();

    // Skyrim Effect Shaders
    Effect_Shader_t* Reanimate_Effect_Shader();

    // Skyrim Factions
    Faction_t* No_Bard_Singer_Autostart_Faction();
    Faction_t* Current_Follower_Faction();
    Faction_t* Player_Follower_Faction();
    Faction_t* Potential_Follower_Faction();
    Faction_t* WI_No_Body_Cleanup_Faction();

    // Skyrim Globals
    Global_t* Player_Follower_Count_Global();

    // Skyrim Keywords
    Keyword_t* Fire_Damage_Magic_Keyword();
    Keyword_t* Frost_Damage_Magic_Keyword();
    Keyword_t* Shock_Damage_Magic_Keyword();
    Keyword_t* Vampire_Drain_Magic_Keyword();
    Keyword_t* Vampire_Keyword();
    Keyword_t* Staff_Vendor_Item_Keyword();
    Keyword_t* Sword_Weapon_Type_Keyword();
    Keyword_t* Greatsword_Weapon_Type_Keyword();
    Keyword_t* Waraxe_Weapon_Type_Keyword();
    Keyword_t* Battleaxe_Weapon_Type_Keyword();
    Keyword_t* Mace_Weapon_Type_Keyword();
    Keyword_t* Warhammer_Weapon_Type_Keyword();
    Keyword_t* Dagger_Weapon_Type_Keyword();
    Keyword_t* Bow_Weapon_Type_Keyword();
    Keyword_t* Staff_Weapon_Type_Keyword();

    // Skyrim Miscs
    Misc_t* Gold();

    // Skyrim Perks
    Perk_t* Vampire_Feed_Perk();

    // Skyrim Quests
    Quest_t* Bard_Songs_Quest();
    Quest_t* Follower_Dialogue_Quest();
    Quest_t* Player_Vampire_Quest();
    Quest_t* WI_Change_Location_01_Quest();
    Quest_t* WI_Remove_Item_04_Quest();

    // Skyrim Reference Markers
    Reference_t* Safe_Go_Back_Marker();

    // Skyrim Statics
    Static_t* X_Marker_Static();

    // Dawnguard Factions
    Faction_t* DLC1_Thrall_Faction();
    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction();
    
    // NPCP Actor Base
    Actor_Base_t* Menu_Actor_Base();

    // NPCP Armors
    Armor_t* Blank_Armor();

    // NPCP Branches
    Branch_t* Main_Branch();
    Branch_t* Main_Direct_Branch();
    Branch_t* Main_Outfit_Branch();
    Branch_t* Main_Style_Branch();
    Branch_t* Main_Vitality_Branch();
    Branch_t* Menu_Chests_Branch();
    Branch_t* Menu_Chests_Weapons_Branch();
    Branch_t* Menu_Chests_Apparel_Branch();
    Branch_t* Menu_Chests_Edibles_Branch();
    Branch_t* Menu_Chests_Misc_Branch();
    Branch_t* Menu_Chests_Books_Branch();
    Branch_t* Menu_Chests_Custom_Branch();
    Branch_t* Menu_Followers_Branch();

    // NPCP Cells
    Cell_t* Storage_Cell();

    // NPCP Containers
    Container_t* Empty_Container();
    Container_t* Outfit2_Container();
    Container_t* Immobile_Outfit2_Container();
    Container_t* Settler_Outfit2_Container();
    Container_t* Thrall_Outfit2_Container();
    Container_t* Follower_Outfit2_Container();

    // NPCP Factions
    Faction_t* Member_Faction();
    Faction_t* Horse_Faction();

    // NPCP Formlists
    Formlist_t* Is_Saddler_Sitting_Globals_Formlist();
    Formlist_t* Expo_Cell_Markers_Formlist();
    Formlist_t* Settler_Markers_Formlist();

    // NPCP Globals
    Global_t* Is_Installed_Global();
    Global_t* Allow_Dialogue_For_All_Global();
    Global_t* Allow_Chatter_Global();
    Global_t* Force_Clone_Uniques_Global();
    Global_t* Force_Clone_Generics_Global();
    Global_t* Force_Unclone_Uniques_Global();
    Global_t* Force_Unclone_Generics_Global();
    Global_t* Is_Leveling_Enabled_Global();
    Global_t* No_Body_Percent_Global();
    Global_t* No_Feet_Percent_Global();
    Global_t* No_Hands_Percent_Global();
    Global_t* No_Head_Percent_Global();

    // NPCP Ints
    Int_t NPCP_Major();
    Int_t NPCP_Minor();
    Int_t NPCP_Patch();

    // NPCP Leveled Actor
    Leveled_Actor_t* Horse_Leveled_Actor();

    // NPCP Location
    Location_t* Expo_Location();

    // NPCP Magic Effects
    Magic_Effect_t* Reanimate_Magic_Effect();
    Magic_Effect_t* Retreat_Magic_Effect();

    // NPCP Misc Tokens
    Misc_t* Member_Token();
    Misc_t* Generic_Token();
    Misc_t* Clone_Token();
    Misc_t* Greeter_Token();
    Misc_t* Movee_Token();
    Misc_t* Immobile_Token();
    Misc_t* Settler_Token();
    Misc_t* Thrall_Token();
    Misc_t* Paralyzed_Token();
    Misc_t* Mannequin_Token();
    Misc_t* Display_Token();
    Misc_t* Reanimated_Token();
    Misc_t* Banished_Token();
    Misc_t* Default_Style_Token();
    Misc_t* Warrior_Style_Token();
    Misc_t* Mage_Style_Token();
    Misc_t* Archer_Style_Token();
    Misc_t* Coward_Style_Token();
    Misc_t* Mortal_Vitality_Token();
    Misc_t* Protected_Vitality_Token();
    Misc_t* Essential_Vitality_Token();
    Misc_t* Invulnerable_Vitality_Token();
    Misc_t* Follower_Token();
    Misc_t* Sneak_Follower_Token();
    Misc_t* Saddler_Token();
    Misc_t* Retreater_Token();

    // NPCP Misc
    Misc_t* Form_Vector();

    // NPCP Outfits
    Outfit_t* Empty_Outfit();

    // NPCP Packages
    Package_t* Menu_Exit_Package();

    // NPCP Perks
    Perk_t* Kiss_Thrall_Perk();
    Perk_t* Reanimate_Perk();
    Perk_t* Resurrect_Perk();
    Perk_t* Unparalyze_Perk();

    // NPCP Quests
    Quest_t* Main_Quest();
    Quest_t* Vars_Quest();
    Quest_t* Funcs_Quest();
    Quest_t* Members_Quest();
    Quest_t* Followers_Quest();
    Quest_t* Control_Quest();
    Quest_t* Thrall_Dialogue_Quest();
    Quest_t* Reanimated_Dialogue_Quest();
    Quest_t* Female_Young_Eager_Quest();

    // NPCP Reference Categories
    Reference_t* Input_Category();
    Reference_t* Swords_Category();
    Reference_t* Greatswords_Category();
    Reference_t* Waraxes_Category();
    Reference_t* Battleaxes_Category();
    Reference_t* Maces_Category();
    Reference_t* Warhammers_Category();
    Reference_t* Daggers_Category();
    Reference_t* Staves_Category();
    Reference_t* Bows_Category();
    Reference_t* Ammo_Category();
    Reference_t* Weapons_Category();
    Reference_t* Light_Armor_Category();
    Reference_t* Heavy_Armor_Category();
    Reference_t* Shields_Category();
    Reference_t* Jewelry_Category();
    Reference_t* Clothes_Category();
    Reference_t* Potions_Category();
    Reference_t* Poisons_Category();
    Reference_t* Ingredients_Category();
    Reference_t* Food_Category();
    Reference_t* Soulgems_Category();
    Reference_t* Scrolls_Category();
    Reference_t* Metals_Category();
    Reference_t* Leather_Category();
    Reference_t* Gems_Category();
    Reference_t* Clutter_Category();
    Reference_t* Keys_Category();
    Reference_t* Misc_Category();
    Reference_t* Spell_Tomes_Category();
    Reference_t* Recipes_Category();
    Reference_t* A_Books_Category();
    Reference_t* B_Books_Category();
    Reference_t* C_Books_Category();
    Reference_t* D_Books_Category();
    Reference_t* E_Books_Category();
    Reference_t* F_Books_Category();
    Reference_t* G_Books_Category();
    Reference_t* H_Books_Category();
    Reference_t* I_Books_Category();
    Reference_t* J_Books_Category();
    Reference_t* K_Books_Category();
    Reference_t* L_Books_Category();
    Reference_t* M_Books_Category();
    Reference_t* N_Books_Category();
    Reference_t* O_Books_Category();
    Reference_t* P_Books_Category();
    Reference_t* Q_Books_Category();
    Reference_t* R_Books_Category();
    Reference_t* S_Books_Category();
    Reference_t* T_Books_Category();
    Reference_t* U_Books_Category();
    Reference_t* V_Books_Category();
    Reference_t* W_Books_Category();
    Reference_t* X_Books_Category();
    Reference_t* Y_Books_Category();
    Reference_t* Z_Books_Category();
    Reference_t* Books_Category();
    Reference_t* Custom_00_Category();
    Reference_t* Custom_01_Category();
    Reference_t* Custom_02_Category();
    Reference_t* Custom_03_Category();
    Reference_t* Custom_04_Category();
    Reference_t* Custom_05_Category();
    Reference_t* Custom_06_Category();
    Reference_t* Custom_07_Category();
    Reference_t* Custom_08_Category();
    Reference_t* Custom_09_Category();
    Reference_t* Custom_10_Category();
    Reference_t* Custom_11_Category();
    Reference_t* Custom_12_Category();
    Reference_t* Custom_13_Category();
    Reference_t* Custom_14_Category();
    Reference_t* Custom_15_Category();

    // NPCP Reference Containers
    Reference_t* Container_Ref_Buffer();

    // NPCP Reference Doors
    Reference_t* Expo_Exit_Door();

    // NPCP Reference Markers
    Reference_t* Cell_Marker();
    Reference_t* Expo_Antechamber_Marker();
    Reference_t* Storage_Marker();

    // NPCP Spells
    Spell_t* Reanimate_Ability_Spell();
    Spell_t* Retreat_Ability_Spell();

    // NPCP Topics
    Topic_t* Main_Topic();
    Topic_t* Main_Back_Topic();
    Topic_t* Main_Clone_Topic();
    Topic_t* Main_Direct_Topic();
    Topic_t* Main_Direct_Block_Topic();
    Topic_t* Main_Direct_Continue_Topic();
    Topic_t* Main_Direct_End_Topic();
    Topic_t* Main_Enthrall_Topic();
    Topic_t* Main_Follow_Topic();
    Topic_t* Main_Goodbye_Topic();
    Topic_t* Main_Hello_Topic();
    Topic_t* Main_Immobilize_Topic();
    Topic_t* Main_Member_Topic();
    Topic_t* Main_Mobilize_Topic();
    Topic_t* Main_Outfit_Topic();
    Topic_t* Main_Outfit2_Topic();
    Topic_t* Main_Outfit_Back_Topic();
    Topic_t* Main_Outfit_Current_Topic();
    Topic_t* Main_Outfit_Default_Topic();
    Topic_t* Main_Outfit_Follower_Topic();
    Topic_t* Main_Outfit_Immobile_Topic();
    Topic_t* Main_Outfit_Member_Topic();
    Topic_t* Main_Outfit_Settler_Topic();
    Topic_t* Main_Outfit_Thrall_Topic();
    Topic_t* Main_Outfit_Vanilla_Topic();
    Topic_t* Main_Pack_Topic();
    Topic_t* Main_Paralyze_Topic();
    Topic_t* Main_Resettle_Topic();
    Topic_t* Main_Saddle_Topic();
    Topic_t* Main_Settle_Topic();
    Topic_t* Main_Sneak_Topic();
    Topic_t* Main_Stash_Topic();
    Topic_t* Main_Style_Topic();
    Topic_t* Main_Style2_Topic();
    Topic_t* Main_Style_Archer_Topic();
    Topic_t* Main_Style_Back_Topic();
    Topic_t* Main_Style_Coward_Topic();
    Topic_t* Main_Style_Default_Topic();
    Topic_t* Main_Style_Mage_Topic();
    Topic_t* Main_Style_Warrior_Topic();
    Topic_t* Main_Unclone_Topic();
    Topic_t* Main_Unfollow_Topic();
    Topic_t* Main_Unmember_Topic();
    Topic_t* Main_Unsaddle_Topic();
    Topic_t* Main_Unsettle_Topic();
    Topic_t* Main_Unsneak_Topic();
    Topic_t* Main_Unthrall_Topic();
    Topic_t* Main_Vitality_Topic();
    Topic_t* Main_Vitality2_Topic();
    Topic_t* Main_Vitality_Back_Topic();
    Topic_t* Main_Vitality_Essential_Topic();
    Topic_t* Main_Vitality_Invulnerable_Topic();
    Topic_t* Main_Vitality_Mortal_Topic();
    Topic_t* Main_Vitality_Protected_Topic();
    Topic_t* Menu_Followers_Topic();
    Topic_t* Menu_Followers_Back_Topic();
    Topic_t* Menu_Followers_Immobilize_Topic();
    Topic_t* Menu_Followers_Mobilize_Topic();
    Topic_t* Menu_Followers_Saddle_Topic();
    Topic_t* Menu_Followers_Settle_Topic();
    Topic_t* Menu_Followers_Sneak_Topic();
    Topic_t* Menu_Followers_Stash_Topic();
    Topic_t* Menu_Followers_Summon_All_Topic();
    Topic_t* Menu_Followers_Summon_Immobile_Topic();
    Topic_t* Menu_Followers_Summon_Mobile_Topic();
    Topic_t* Menu_Followers_Unfollow_Topic();
    Topic_t* Menu_Followers_Unmember_Topic();
    Topic_t* Menu_Followers_Unsaddle_Topic();
    Topic_t* Menu_Followers_Unsettle_Topic();
    Topic_t* Menu_Followers_Unsneak_Topic();

    // NPCP Topic Infos
    Topic_Info_t* Menu_Chests_Input_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Swords_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Greatswords_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Waraxes_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Battleaxes_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Maces_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Warhammers_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Daggers_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Staves_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Bows_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Ammo_Topic_Info();
    Topic_Info_t* Menu_Chests_Weapons_Others_Topic_Info();
    Topic_Info_t* Menu_Chests_Apparel_Light_Armor_Topic_Info();
    Topic_Info_t* Menu_Chests_Apparel_Heavy_Armor_Topic_Info();
    Topic_Info_t* Menu_Chests_Apparel_Shields_Topic_Info();
    Topic_Info_t* Menu_Chests_Apparel_Jewelry_Topic_Info();
    Topic_Info_t* Menu_Chests_Apparel_Clothes_Topic_Info();
    Topic_Info_t* Menu_Chests_Edibles_Potions_Topic_Info();
    Topic_Info_t* Menu_Chests_Edibles_Poisons_Topic_Info();
    Topic_Info_t* Menu_Chests_Edibles_Ingredients_Topic_Info();
    Topic_Info_t* Menu_Chests_Edibles_Food_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Soulgems_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Scrolls_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Metals_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Leather_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Gems_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Clutter_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Keys_Topic_Info();
    Topic_Info_t* Menu_Chests_Misc_Others_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_Spell_Tomes_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_Recipes_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_A_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_B_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_C_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_D_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_E_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_F_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_G_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_H_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_I_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_J_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_K_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_L_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_M_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_N_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_O_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_P_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_Q_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_R_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_S_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_T_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_U_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_V_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_W_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_X_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_Y_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_Z_Topic_Info();
    Topic_Info_t* Menu_Chests_Books_Others_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_00_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_01_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_02_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_03_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_04_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_05_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_06_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_07_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_08_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_09_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_10_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_11_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_12_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_13_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_14_Topic_Info();
    Topic_Info_t* Menu_Chests_Custom_15_Topic_Info();

    // NPCP Weapons
    Weapon_t* Blank_Weapon();

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Registry_t* registry);

}}}
