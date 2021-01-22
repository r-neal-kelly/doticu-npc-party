/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "intrinsic.h"

namespace doticu_npcp {

    class Consts_t
    {
    public:
        class Skyrim
        {
        public:
            static maybe<Mod_t*> Mod();

        public:
            struct Actor
            {
                static some<Actor_t*> Player();
            };
            struct Armor
            {
                static some<Armor_t*> Belted_Tunic();
                static some<Armor_t*> Gold_Ring();
            };
            struct Effect_Shader
            {
                static some<Effect_Shader_t*> Reanimate();
            };
            struct Faction
            {
                static some<Faction_t*> Bard_Singer_No_Autostart();
                static some<Faction_t*> Current_Follower();
                static some<Faction_t*> Player_Follower();
                static some<Faction_t*> Potential_Follower();
                static some<Faction_t*> WI_No_Body_Cleanup();
            };
            struct Global
            {
                static some<Global_t*> Player_Follower_Count();
            };
            struct Keyword
            {
                static some<Keyword_t*> Magic_Damage_Fire();
                static some<Keyword_t*> Magic_Damage_Frost();
                static some<Keyword_t*> Magic_Damage_Shock();
                static some<Keyword_t*> Magic_Vampire_Drain();
                static some<Keyword_t*> Vampire();
                static some<Keyword_t*> Vendor_Item_Staff();
                static some<Keyword_t*> Weapon_Type_Sword();
                static some<Keyword_t*> Weapon_Type_Greatsword();
                static some<Keyword_t*> Weapon_Type_Waraxe();
                static some<Keyword_t*> Weapon_Type_Battleaxe();
                static some<Keyword_t*> Weapon_Type_Mace();
                static some<Keyword_t*> Weapon_Type_Warhammer();
                static some<Keyword_t*> Weapon_Type_Dagger();
                static some<Keyword_t*> Weapon_Type_Bow();
                static some<Keyword_t*> Weapon_Type_Staff();
            };
            struct Misc
            {
                static some<Misc_t*> Gold();
            };
            struct Package
            {
                static some<Package_t*> Follow_Template();
                static some<Package_t*> Follow_Player_Template();
                static some<Package_t*> Follow_And_Keep_Distance_Template();
                static some<Package_t*> Follow_In_Single_File_Template();
                static some<Package_t*> Follower_Template();
            };
            struct Perk
            {
                static some<Perk_t*> Vampire_Feed();
            };
            struct Quest
            {
                static some<Quest_t*> Bard_Songs();
                static some<Quest_t*> Follower_Dialogue();
                static some<Quest_t*> Player_Vampire();
                static some<Quest_t*> WI_Change_Location_01();
                static some<Quest_t*> WI_Remove_Item_04();
            };
            struct Reference
            {
                static some<Reference_t*> Riverwood_Location_Center_Marker();
            };
            struct Static
            {
                static some<Static_t*> X_Marker();
                static some<Static_t*> X_Marker_Heading();
            };
            struct Version
            {
                static const Version_t<u16> Required();
            };
        };

    public:
        class Dawnguard
        {
        public:
            static maybe<Mod_t*> Mod();

        public:
            struct Faction
            {
                static some<Faction_t*> DLC1_Thrall();
                static some<Faction_t*> DLC1_Vampire_Feed_No_Crime();
            };
        };

    public:
        class SKSE
        {
        public:
            struct Version
            {
                static const Version_t<u16> Minimum();
            };
        };

    public:
        class NPCP
        {
        public:
            static maybe<Mod_t*> Mod();

        public:
            struct Actor_Base
            {
                static some<Actor_Base_t*> Menu();
            };
            struct Armor
            {
                static some<Armor_t*> Blank();
            };
            struct Branch
            {
                /*
    Branch_t* Menu_Branch();
    Branch_t* Menu_Chests_Branch();
    Branch_t* Menu_Chests_Weapons_Branch();
    Branch_t* Menu_Chests_Apparel_Branch();
    Branch_t* Menu_Chests_Edibles_Branch();
    Branch_t* Menu_Chests_Misc_Branch();
    Branch_t* Menu_Chests_Books_Branch();
    Branch_t* Menu_Chests_Custom_Branch();
    Branch_t* Menu_Followers_Branch();
                */
            };
            struct Cell
            {
                static some<Cell_t*> Storage();
            };
            struct Container
            {
                static some<Container_t*> Empty();
                static some<Container_t*> Outfit2();
                static some<Container_t*> Immobile_Outfit2();
                static some<Container_t*> Settler_Outfit2();
                static some<Container_t*> Thrall_Outfit2();
                static some<Container_t*> Follower_Outfit2();
            };
            struct Faction
            {
                static some<Faction_t*> Horse();
                static some<Faction_t*> Member();
            };
            struct Form_List
            {
                static some<Form_List_t*> Is_Saddler_Sitting_Globals();
                static some<Form_List_t*> Expo_Cell_Markers();
                static some<Form_List_t*> Settler_Markers();
                static some<Form_List_t*> Settler_Packages();
                static some<Form_List_t*> Settler_Sleeper_Packages();
                static some<Form_List_t*> Settler_Sitter_Packages();
                static some<Form_List_t*> Settler_Eater_Packages();
                static some<Form_List_t*> Settler_Guard_Packages();
                static some<Form_List_t*> Follower_Sojourner_Packages();
                static some<Form_List_t*> Expoee_Buttons();
                static some<Form_List_t*> Expoee_Markers();
                static some<Form_List_t*> Main_Branches();
                static some<Form_List_t*> Main_Direct_Branches();
                static some<Form_List_t*> Main_Outfit_Branches();
                static some<Form_List_t*> Main_Style_Branches();
                static some<Form_List_t*> Main_Vitality_Branches();
                static some<Form_List_t*> Main_Female_Topics();
                static some<Form_List_t*> Main_Male_Topics();
                static some<Form_List_t*> Female_Voice_Types();
                static some<Form_List_t*> Male_Voice_Types();
            };
            struct Furniture
            {
                static some<Furniture_t*> Bedroll();
            };
            struct Global
            {
                static some<Global_t*> Is_Installed();
                static some<Global_t*> Allow_Dialogue_For_All();
                static some<Global_t*> Allow_Chatter();
                static some<Global_t*> Force_Clone_Uniques();
                static some<Global_t*> Force_Clone_Generics();
                static some<Global_t*> Force_Unclone_Uniques();
                static some<Global_t*> Force_Unclone_Generics();
                static some<Global_t*> Is_Leveling_Enabled();
                static some<Global_t*> No_Body_Percent();
                static some<Global_t*> No_Feet_Percent();
                static some<Global_t*> No_Hands_Percent();
                static some<Global_t*> No_Head_Percent();
            };
            struct Int
            {
                /*
    constexpr size_t MAX_MEMBERS = 1024;
    constexpr size_t MAX_FOLLOWERS = 16;
                */
            };
            struct Leveled_Actor_Base
            {
                /*
    Leveled_Actor_t* Horse_Leveled_Actor();
                */
            };
            struct Location
            {
                /*
    Location_t* Expo_Location();
                */
            };
            struct Magic_Effect
            {
                /*
    Magic_Effect_t* Reanimate_Magic_Effect();
    Magic_Effect_t* Retreat_Magic_Effect();
                */
            };
            struct Misc
            {
                /*
    Misc_t* Form_Vector();
                */
                struct Token
                {
                    /*
    Misc_t* Member_Token();
    Misc_t* Generic_Token();
    Misc_t* Clone_Token();
    Misc_t* Greeter_Token();
    Misc_t* Movee_Token();
    Misc_t* Immobile_Token();
    Misc_t* Settler_Token();
    Misc_t* Settler_Sleeper_Token();
    Misc_t* Settler_Sitter_Token();
    Misc_t* Settler_Eater_Token();
    Misc_t* Settler_Guard_Token();
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
    Misc_t* Sojourner_Follower_Token();
    Misc_t* Active_Sojourner_Follower_Token();
    Misc_t* Saddler_Token();
    Misc_t* Retreater_Token();
                */
                };
            };
            struct Outfit
            {
                /*
    Outfit_t* Empty_Outfit();
                */
            };
            struct Package
            {
                /*
    Package_t* Greeter_Package();
    Package_t* Menu_Exit_Package();
                */
            };
            struct Perk
            {
                /*
    Perk_t* Kiss_Thrall_Perk();
    Perk_t* Reanimate_Perk();
    Perk_t* Resurrect_Perk();
    Perk_t* Unparalyze_Perk();
                */
            };
            struct Quest
            {
                static some<Quest_t*> Main();
                static some<Quest_t*> Vars();
                static some<Quest_t*> Funcs();
                static some<Quest_t*> Members();
                static some<Quest_t*> Followers();
                static some<Quest_t*> Control();
                /*
    Quest_t* Female_Argonian_Quest();
    Quest_t* Female_Commander_Quest();
    Quest_t* Female_Commoner_Quest();
    Quest_t* Female_Condescending_Quest();
    Quest_t* Female_Coward_Quest();
    Quest_t* Female_Dark_Elf_Quest();
    Quest_t* Female_Elf_Haughty_Quest();
    Quest_t* Female_Even_Toned_Quest();
    Quest_t* Female_Khajiit_Quest();
    Quest_t* Female_Nord_Quest();
    Quest_t* Female_Old_Grumpy_Quest();
    Quest_t* Female_Old_Kindly_Quest();
    Quest_t* Female_Orc_Quest();
    Quest_t* Female_Other_Quest();
    Quest_t* Female_Shrill_Quest();
    Quest_t* Female_Soldier_Quest();
    Quest_t* Female_Sultry_Quest();
    Quest_t* Female_Young_Eager_Quest();
    Quest_t* Male_Argonian_Quest();
    Quest_t* Male_Bandit_Quest();
    Quest_t* Male_Brute_Quest();
    Quest_t* Male_Commander_Quest();
    Quest_t* Male_Commoner_Quest();
    Quest_t* Male_Commoner_Accented_Quest();
    Quest_t* Male_Condescending_Quest();
    Quest_t* Male_Coward_Quest();
    Quest_t* Male_Dark_Elf_Quest();
    Quest_t* Male_Drunk_Quest();
    Quest_t* Male_Elf_Haughty_Quest();
    Quest_t* Male_Even_Toned_Quest();
    Quest_t* Male_Even_Toned_Accented_Quest();
    Quest_t* Male_Forsworn_Quest();
    Quest_t* Male_Guard_Quest();
    Quest_t* Male_Khajiit_Quest();
    Quest_t* Male_Nord_Quest();
    Quest_t* Male_Nord_Commander_Quest();
    Quest_t* Male_Old_Grumpy_Quest();
    Quest_t* Male_Old_Kindly_Quest();
    Quest_t* Male_Orc_Quest();
    Quest_t* Male_Other_Quest();
    Quest_t* Male_Sly_Cynical_Quest();
    Quest_t* Male_Soldier_Quest();
    Quest_t* Male_Warlock_Quest();
    Quest_t* Male_Young_Eager_Quest();
                */
            };
            struct Reference
            {
                /*
    Reference_t* Container_Ref_Buffer();
    Reference_t* Expo_Exit_Door();
    Reference_t* Cell_Marker();
    Reference_t* Expo_Antechamber_Marker();
    Reference_t* Storage_Marker();
                */
                struct Category
                {
                    /*
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
                */
                };
            };
            struct Spell
            {
                /*
    Spell_t* Reanimate_Ability_Spell();
    Spell_t* Retreat_Ability_Spell();
                */
            };
            struct Topic
            {
                /*
    Topic_t* Menu_Chests_Custom_00_Topic();
    Topic_t* Menu_Chests_Custom_01_Topic();
    Topic_t* Menu_Chests_Custom_02_Topic();
    Topic_t* Menu_Chests_Custom_03_Topic();
    Topic_t* Menu_Chests_Custom_04_Topic();
    Topic_t* Menu_Chests_Custom_05_Topic();
    Topic_t* Menu_Chests_Custom_06_Topic();
    Topic_t* Menu_Chests_Custom_07_Topic();
    Topic_t* Menu_Chests_Custom_08_Topic();
    Topic_t* Menu_Chests_Custom_09_Topic();
    Topic_t* Menu_Chests_Custom_10_Topic();
    Topic_t* Menu_Chests_Custom_11_Topic();
    Topic_t* Menu_Chests_Custom_12_Topic();
    Topic_t* Menu_Chests_Custom_13_Topic();
    Topic_t* Menu_Chests_Custom_14_Topic();
    Topic_t* Menu_Chests_Custom_15_Topic();
                */
            };
            struct Version
            {
                static const Version_t<u16> Current();
            };
            struct Weapon
            {
                static some<Weapon_t*> Blank();
            };
        };
    };

}
