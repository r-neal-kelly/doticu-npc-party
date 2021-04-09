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
        class Better_Vampires
        {
        public:
            static maybe<Mod_t*> Mod();
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
            struct Cell
            {
                static some<Cell_t*> Storage();
            };
            struct Combat_Style
            {
                static some<Combat_Style_t*> Archer();
                static some<Combat_Style_t*> Coward();
                static some<Combat_Style_t*> Mage();
                static some<Combat_Style_t*> Warrior();
            };
            struct Container
            {
                static some<Container_t*> Empty();
                static some<Container_t*> Immobile_Outfit_Template();
                static some<Container_t*> Settler_Outfit_Template();
                static some<Container_t*> Thrall_Outfit_Template();
                static some<Container_t*> Follower_Outfit_Template();
            };
            struct Dialogue_Branch
            {
                static some<Dialogue_Branch_t*> Menu();
                static some<Dialogue_Branch_t*> Menu_Chests();
                static some<Dialogue_Branch_t*> Menu_Chests_Weapons();
                static some<Dialogue_Branch_t*> Menu_Chests_Apparel();
                static some<Dialogue_Branch_t*> Menu_Chests_Edibles();
                static some<Dialogue_Branch_t*> Menu_Chests_Misc();
                static some<Dialogue_Branch_t*> Menu_Chests_Books();
                static some<Dialogue_Branch_t*> Menu_Chests_Custom();
                static some<Dialogue_Branch_t*> Menu_Followers();
            };
            struct Dialogue_Topic
            {
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_00();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_01();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_02();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_03();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_04();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_05();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_06();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_07();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_08();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_09();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_10();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_11();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_12();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_13();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_14();
                static some<Dialogue_Topic_t*> Menu_Chests_Custom_15();
            };
            struct Faction
            {
                static some<Faction_t*> Horse();
                static some<Faction_t*> Member();
                static some<Faction_t*> Outfit();
            };
            struct Form_List
            {
                static some<Form_List_t*> Is_Saddler_Sitting_Globals();
                static some<Form_List_t*> Expo_Cell_Markers();
                static some<Form_List_t*> Settler_Markers();
                static some<Form_List_t*> Settler_Sandboxer_Packages();
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
                static some<Form_List_t*> Voice_Quests();
            };
            struct Furniture
            {
                static some<Furniture_t*> Bedroll();
            };
            struct Global
            {
                static some<Global_t*> Do_Allow_Menu_For_All_Actors();
                static some<Global_t*> Do_Force_Clone_Uniques();
                static some<Global_t*> Do_Force_Clone_Generics();
                static some<Global_t*> Do_Force_Unclone_Uniques();
                static some<Global_t*> Do_Force_Unclone_Generics();
                static some<Global_t*> Empty_Outfit_Body_Percent();
                static some<Global_t*> Empty_Outfit_Feet_Percent();
                static some<Global_t*> Empty_Outfit_Hands_Percent();
                static some<Global_t*> Empty_Outfit_Head_Percent();
            };
            struct Int
            {
                static constexpr size_t MAX_MEMBERS     = 1024;
                static constexpr size_t MAX_SETTLERS    = 1024;
                static constexpr size_t MAX_EXPOEES     = 1024;
                static constexpr size_t MAX_DISPLAYS    = 16;
                static constexpr size_t MAX_FOLLOWERS   = 16;
            };
            struct Leveled_Actor_Base
            {
                static some<Leveled_Actor_Base_t*> Horse();
            };
            struct Location
            {
                static some<Location_t*> Expo();
            };
            struct Magic_Effect
            {
                static some<Magic_Effect_t*> Reanimate();
                static some<Magic_Effect_t*> Retreat();
            };
            struct Misc
            {
                struct Token
                {
                    static some<Misc_t*> Member();
                    static some<Misc_t*> Generic();
                    static some<Misc_t*> Clone();
                    static some<Misc_t*> Greeter();
                    static some<Misc_t*> Movee();
                    static some<Misc_t*> Immobile();
                    static some<Misc_t*> Settler_Sandboxer();
                    static some<Misc_t*> Settler_Sleeper();
                    static some<Misc_t*> Settler_Sitter();
                    static some<Misc_t*> Settler_Eater();
                    static some<Misc_t*> Settler_Guard();
                    static some<Misc_t*> Thrall();
                    static some<Misc_t*> Paralyzed();
                    static some<Misc_t*> Mannequin();
                    static some<Misc_t*> Display();
                    static some<Misc_t*> Reanimated();
                    static some<Misc_t*> Banished();
                    static some<Misc_t*> Default_Style();
                    static some<Misc_t*> Warrior_Style();
                    static some<Misc_t*> Mage_Style();
                    static some<Misc_t*> Archer_Style();
                    static some<Misc_t*> Coward_Style();
                    static some<Misc_t*> Mortal_Vitality();
                    static some<Misc_t*> Protected_Vitality();
                    static some<Misc_t*> Essential_Vitality();
                    static some<Misc_t*> Invulnerable_Vitality();
                    static some<Misc_t*> Follower();
                    static some<Misc_t*> Sneak_Follower();
                    static some<Misc_t*> Sojourner_Follower();
                    static some<Misc_t*> Active_Sojourner_Follower();
                    static some<Misc_t*> Saddler();
                    static some<Misc_t*> Retreater();
                };
            };
            struct Outfit
            {
                static some<Outfit_t*> Empty();
            };
            struct Package
            {
                static some<Package_t*> Greeter();
                static some<Package_t*> Menu_Exit();
            };
            struct Perk
            {
                static some<Perk_t*> Kiss_Thrall();
                static some<Perk_t*> Reanimate();
                static some<Perk_t*> Resurrect();
                static some<Perk_t*> Unparalyze();
            };
            struct Quest
            {
                static some<Quest_t*> Main();
                static some<Quest_t*> Funcs();
                static some<Quest_t*> Members();
                static some<Quest_t*> Followers();
                static some<Quest_t*> Control();
            };
            struct Reference
            {
                static some<Reference_t*> Buffer_Container();
                static some<Reference_t*> Expo_Exit_Door();
                static some<Reference_t*> Cell_Marker();
                static some<Reference_t*> Expo_Antechamber_Marker();
                static some<Reference_t*> Storage_Marker();

                struct Chest
                {
                    static some<Reference_t*> Input();
                    static some<Reference_t*> Swords();
                    static some<Reference_t*> Greatswords();
                    static some<Reference_t*> Waraxes();
                    static some<Reference_t*> Battleaxes();
                    static some<Reference_t*> Maces();
                    static some<Reference_t*> Warhammers();
                    static some<Reference_t*> Daggers();
                    static some<Reference_t*> Staves();
                    static some<Reference_t*> Bows();
                    static some<Reference_t*> Ammo();
                    static some<Reference_t*> Other_Weapons();
                    static some<Reference_t*> Light_Armor();
                    static some<Reference_t*> Heavy_Armor();
                    static some<Reference_t*> Shields();
                    static some<Reference_t*> Jewelry();
                    static some<Reference_t*> Clothes();
                    static some<Reference_t*> Potions();
                    static some<Reference_t*> Poisons();
                    static some<Reference_t*> Ingredients();
                    static some<Reference_t*> Food();
                    static some<Reference_t*> Soul_Gems();
                    static some<Reference_t*> Scrolls();
                    static some<Reference_t*> Metals();
                    static some<Reference_t*> Leather();
                    static some<Reference_t*> Gems();
                    static some<Reference_t*> Clutter();
                    static some<Reference_t*> Keys();
                    static some<Reference_t*> Other_Misc();
                    static some<Reference_t*> Spell_Tomes();
                    static some<Reference_t*> Recipes();
                    static some<Reference_t*> A_Books();
                    static some<Reference_t*> B_Books();
                    static some<Reference_t*> C_Books();
                    static some<Reference_t*> D_Books();
                    static some<Reference_t*> E_Books();
                    static some<Reference_t*> F_Books();
                    static some<Reference_t*> G_Books();
                    static some<Reference_t*> H_Books();
                    static some<Reference_t*> I_Books();
                    static some<Reference_t*> J_Books();
                    static some<Reference_t*> K_Books();
                    static some<Reference_t*> L_Books();
                    static some<Reference_t*> M_Books();
                    static some<Reference_t*> N_Books();
                    static some<Reference_t*> O_Books();
                    static some<Reference_t*> P_Books();
                    static some<Reference_t*> Q_Books();
                    static some<Reference_t*> R_Books();
                    static some<Reference_t*> S_Books();
                    static some<Reference_t*> T_Books();
                    static some<Reference_t*> U_Books();
                    static some<Reference_t*> V_Books();
                    static some<Reference_t*> W_Books();
                    static some<Reference_t*> X_Books();
                    static some<Reference_t*> Y_Books();
                    static some<Reference_t*> Z_Books();
                    static some<Reference_t*> Other_Books();
                    static some<Reference_t*> Custom_00();
                    static some<Reference_t*> Custom_01();
                    static some<Reference_t*> Custom_02();
                    static some<Reference_t*> Custom_03();
                    static some<Reference_t*> Custom_04();
                    static some<Reference_t*> Custom_05();
                    static some<Reference_t*> Custom_06();
                    static some<Reference_t*> Custom_07();
                    static some<Reference_t*> Custom_08();
                    static some<Reference_t*> Custom_09();
                    static some<Reference_t*> Custom_10();
                    static some<Reference_t*> Custom_11();
                    static some<Reference_t*> Custom_12();
                    static some<Reference_t*> Custom_13();
                    static some<Reference_t*> Custom_14();
                    static some<Reference_t*> Custom_15();
                };
            };
            struct Spell
            {
                static some<Spell_t*> Reanimate_Ability();
                static some<Spell_t*> Retreat_Ability();
            };
            struct Version
            {
                static const Version_t<u16> Current();
            };
            struct Voice_Type
            {
                static some<Voice_Type_t*> Blank();
            };
            struct Weapon
            {
                static some<Weapon_t*> Blank();
            };
        };
    };

}
