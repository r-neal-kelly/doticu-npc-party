/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "game.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_chests.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Chests_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_chests");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Chests_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Chests_t* Chests_t::Self()
    {
        return static_cast<Chests_t*>(Consts::Control_Quest());
    }

    Object_t* Chests_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Chests_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Chests_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Chests_t::Input_Option_Variable() { DEFINE_VARIABLE("p_option_input"); }

    Variable_t* Chests_t::Swords_Option_Variable() { DEFINE_VARIABLE("p_option_swords"); }
    Variable_t* Chests_t::Greatswords_Option_Variable() { DEFINE_VARIABLE("p_option_greatswords"); }
    Variable_t* Chests_t::Waraxes_Option_Variable() { DEFINE_VARIABLE("p_option_waraxes"); }
    Variable_t* Chests_t::Battleaxes_Option_Variable() { DEFINE_VARIABLE("p_option_battleaxes"); }
    Variable_t* Chests_t::Maces_Option_Variable() { DEFINE_VARIABLE("p_option_maces"); }
    Variable_t* Chests_t::Warhammers_Option_Variable() { DEFINE_VARIABLE("p_option_warhammers"); }
    Variable_t* Chests_t::Daggers_Option_Variable() { DEFINE_VARIABLE("p_option_daggers"); }
    Variable_t* Chests_t::Staves_Option_Variable() { DEFINE_VARIABLE("p_option_staves"); }
    Variable_t* Chests_t::Bows_Option_Variable() { DEFINE_VARIABLE("p_option_bows"); }
    Variable_t* Chests_t::Ammo_Option_Variable() { DEFINE_VARIABLE("p_option_ammo"); }
    Variable_t* Chests_t::Weapons_Option_Variable() { DEFINE_VARIABLE("p_option_weapons"); }

    Variable_t* Chests_t::Light_Armor_Option_Variable() { DEFINE_VARIABLE("p_option_light_armor"); }
    Variable_t* Chests_t::Heavy_Armor_Option_Variable() { DEFINE_VARIABLE("p_option_heavy_armor"); }
    Variable_t* Chests_t::Shields_Option_Variable() { DEFINE_VARIABLE("p_option_shields"); }
    Variable_t* Chests_t::Jewelry_Option_Variable() { DEFINE_VARIABLE("p_option_jewelry"); }
    Variable_t* Chests_t::Clothes_Option_Variable() { DEFINE_VARIABLE("p_option_clothes"); }

    Variable_t* Chests_t::Potions_Option_Variable() { DEFINE_VARIABLE("p_option_potions"); }
    Variable_t* Chests_t::Poisons_Option_Variable() { DEFINE_VARIABLE("p_option_poisons"); }
    Variable_t* Chests_t::Ingredients_Option_Variable() { DEFINE_VARIABLE("p_option_ingredients"); }
    Variable_t* Chests_t::Food_Option_Variable() { DEFINE_VARIABLE("p_option_food"); }

    Variable_t* Chests_t::Soulgems_Option_Variable() { DEFINE_VARIABLE("p_option_soulgems"); }
    Variable_t* Chests_t::Scrolls_Option_Variable() { DEFINE_VARIABLE("p_option_scrolls"); }
    Variable_t* Chests_t::Metals_Option_Variable() { DEFINE_VARIABLE("p_option_metals"); }
    Variable_t* Chests_t::Leather_Option_Variable() { DEFINE_VARIABLE("p_option_leather"); }
    Variable_t* Chests_t::Gems_Option_Variable() { DEFINE_VARIABLE("p_option_gems"); }
    Variable_t* Chests_t::Clutter_Option_Variable() { DEFINE_VARIABLE("p_option_clutter"); }
    Variable_t* Chests_t::Keys_Option_Variable() { DEFINE_VARIABLE("p_option_keys"); }
    Variable_t* Chests_t::Misc_Option_Variable() { DEFINE_VARIABLE("p_option_misc"); }

    Variable_t* Chests_t::Spell_Tomes_Option_Variable() { DEFINE_VARIABLE("p_option_spell_tomes"); }
    Variable_t* Chests_t::Recipes_Option_Variable() { DEFINE_VARIABLE("p_option_recipes"); }
    Variable_t* Chests_t::A_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_a"); }
    Variable_t* Chests_t::B_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_b"); }
    Variable_t* Chests_t::C_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_c"); }
    Variable_t* Chests_t::D_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_d"); }
    Variable_t* Chests_t::E_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_e"); }
    Variable_t* Chests_t::F_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_f"); }
    Variable_t* Chests_t::G_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_g"); }
    Variable_t* Chests_t::H_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_h"); }
    Variable_t* Chests_t::I_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_i"); }
    Variable_t* Chests_t::J_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_j"); }
    Variable_t* Chests_t::K_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_k"); }
    Variable_t* Chests_t::L_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_l"); }
    Variable_t* Chests_t::M_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_m"); }
    Variable_t* Chests_t::N_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_n"); }
    Variable_t* Chests_t::O_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_o"); }
    Variable_t* Chests_t::P_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_p"); }
    Variable_t* Chests_t::Q_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_q"); }
    Variable_t* Chests_t::R_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_r"); }
    Variable_t* Chests_t::S_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_s"); }
    Variable_t* Chests_t::T_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_t"); }
    Variable_t* Chests_t::U_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_u"); }
    Variable_t* Chests_t::V_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_v"); }
    Variable_t* Chests_t::W_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_w"); }
    Variable_t* Chests_t::X_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_x"); }
    Variable_t* Chests_t::Y_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_y"); }
    Variable_t* Chests_t::Z_Books_Option_Variable() { DEFINE_VARIABLE("p_option_books_z"); }
    Variable_t* Chests_t::Books_Option_Variable() { DEFINE_VARIABLE("p_option_books"); }

    Variable_t* Chests_t::Custom_00_Option_Variable() { DEFINE_VARIABLE("p_option_custom_00"); }
    Variable_t* Chests_t::Custom_01_Option_Variable() { DEFINE_VARIABLE("p_option_custom_01"); }
    Variable_t* Chests_t::Custom_02_Option_Variable() { DEFINE_VARIABLE("p_option_custom_02"); }
    Variable_t* Chests_t::Custom_03_Option_Variable() { DEFINE_VARIABLE("p_option_custom_03"); }
    Variable_t* Chests_t::Custom_04_Option_Variable() { DEFINE_VARIABLE("p_option_custom_04"); }
    Variable_t* Chests_t::Custom_05_Option_Variable() { DEFINE_VARIABLE("p_option_custom_05"); }
    Variable_t* Chests_t::Custom_06_Option_Variable() { DEFINE_VARIABLE("p_option_custom_06"); }
    Variable_t* Chests_t::Custom_07_Option_Variable() { DEFINE_VARIABLE("p_option_custom_07"); }
    Variable_t* Chests_t::Custom_08_Option_Variable() { DEFINE_VARIABLE("p_option_custom_08"); }
    Variable_t* Chests_t::Custom_09_Option_Variable() { DEFINE_VARIABLE("p_option_custom_09"); }
    Variable_t* Chests_t::Custom_10_Option_Variable() { DEFINE_VARIABLE("p_option_custom_10"); }
    Variable_t* Chests_t::Custom_11_Option_Variable() { DEFINE_VARIABLE("p_option_custom_11"); }
    Variable_t* Chests_t::Custom_12_Option_Variable() { DEFINE_VARIABLE("p_option_custom_12"); }
    Variable_t* Chests_t::Custom_13_Option_Variable() { DEFINE_VARIABLE("p_option_custom_13"); }
    Variable_t* Chests_t::Custom_14_Option_Variable() { DEFINE_VARIABLE("p_option_custom_14"); }
    Variable_t* Chests_t::Custom_15_Option_Variable() { DEFINE_VARIABLE("p_option_custom_15"); }

    Variable_t* Chests_t::Rename_Custom_00_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_00"); }
    Variable_t* Chests_t::Rename_Custom_01_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_01"); }
    Variable_t* Chests_t::Rename_Custom_02_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_02"); }
    Variable_t* Chests_t::Rename_Custom_03_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_03"); }
    Variable_t* Chests_t::Rename_Custom_04_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_04"); }
    Variable_t* Chests_t::Rename_Custom_05_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_05"); }
    Variable_t* Chests_t::Rename_Custom_06_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_06"); }
    Variable_t* Chests_t::Rename_Custom_07_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_07"); }
    Variable_t* Chests_t::Rename_Custom_08_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_08"); }
    Variable_t* Chests_t::Rename_Custom_09_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_09"); }
    Variable_t* Chests_t::Rename_Custom_10_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_10"); }
    Variable_t* Chests_t::Rename_Custom_11_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_11"); }
    Variable_t* Chests_t::Rename_Custom_12_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_12"); }
    Variable_t* Chests_t::Rename_Custom_13_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_13"); }
    Variable_t* Chests_t::Rename_Custom_14_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_14"); }
    Variable_t* Chests_t::Rename_Custom_15_Option_Variable() { DEFINE_VARIABLE("p_option_rename_custom_15"); }

    Variable_t* Chests_t::Custom_Names_Array_Variable() { DEFINE_VARIABLE("p_custom_names"); }

    Array_t* Chests_t::Custom_Names_Array()
    {
        Array_t* custom_names_array = Custom_Names_Array_Variable()->Array();
        if (!custom_names_array) {
            Initialize();
            custom_names_array = Custom_Names_Array_Variable()->Array();
        }
        NPCP_ASSERT(custom_names_array);
        return custom_names_array;
    }

    void Chests_t::Initialize()
    {
        Vector_t<String_t> custom_names;
        custom_names.reserve(MAX_CUSTOM_CATEGORIES);
        for (size_t idx = 0, count = MAX_CUSTOM_CATEGORIES; idx < count; idx += 1) {
            if (idx < 9) {
                custom_names.push_back((std::string("Custom 0") + std::to_string(idx + 1) + " ").c_str());
            } else {
                custom_names.push_back((std::string("Custom ") + std::to_string(idx + 1) + " ").c_str());
            }
        }
        Custom_Names_Array_Variable()->Pack(custom_names);
    }

    void Chests_t::Uninitialize()
    {
        Vector_t<String_t> custom_names;
        Custom_Names_Array_Variable()->Pack(custom_names);
    }

    void Chests_t::Reinitialize()
    {
        Uninitialize();
        Initialize();
    }

    void Chests_t::On_Build_Page()
    {
        Main_t* mcm = Main();

        mcm->Title_Text(" Chests ");
        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

        mcm->Add_Header_Option(" Special ");
        mcm->Add_Empty_Option();
        {
            Input_Option_Variable()->Int(
                mcm->Add_Text_Option(" Input ", "")
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        
        mcm->Add_Header_Option(" Weapons ");
        mcm->Add_Empty_Option();
        {
            Swords_Option_Variable()->Int(
                mcm->Add_Text_Option(" Swords ", "")
            );
            Greatswords_Option_Variable()->Int(
                mcm->Add_Text_Option(" Greatswords ", "")
            );
            Waraxes_Option_Variable()->Int(
                mcm->Add_Text_Option(" Waraxes ", "")
            );
            Battleaxes_Option_Variable()->Int(
                mcm->Add_Text_Option(" Battleaxes ", "")
            );
            Maces_Option_Variable()->Int(
                mcm->Add_Text_Option(" Maces ", "")
            );
            Warhammers_Option_Variable()->Int(
                mcm->Add_Text_Option(" Warhammers ", "")
            );
            Daggers_Option_Variable()->Int(
                mcm->Add_Text_Option(" Daggers ", "")
            );
            Staves_Option_Variable()->Int(
                mcm->Add_Text_Option(" Staves ", "")
            );
            Bows_Option_Variable()->Int(
                mcm->Add_Text_Option(" Bows ", "")
            );
            Ammo_Option_Variable()->Int(
                mcm->Add_Text_Option(" Ammo ", "")
            );
            Weapons_Option_Variable()->Int(
                mcm->Add_Text_Option(" Others ", "")
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Apparel ");
        mcm->Add_Empty_Option();
        {
            Light_Armor_Option_Variable()->Int(
                mcm->Add_Text_Option(" Light Armor ", "")
            );
            Heavy_Armor_Option_Variable()->Int(
                mcm->Add_Text_Option(" Heavy Armor ", "")
            );
            Shields_Option_Variable()->Int(
                mcm->Add_Text_Option(" Shields ", "")
            );
            Jewelry_Option_Variable()->Int(
                mcm->Add_Text_Option(" Jewelry ", "")
            );
            Clothes_Option_Variable()->Int(
                mcm->Add_Text_Option(" Clothes ", "")
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Edibles ");
        mcm->Add_Empty_Option();
        {
            Potions_Option_Variable()->Int(
                mcm->Add_Text_Option(" Potions ", "")
            );
            Poisons_Option_Variable()->Int(
                mcm->Add_Text_Option(" Poisons ", "")
            );
            Ingredients_Option_Variable()->Int(
                mcm->Add_Text_Option(" Ingredients ", "")
            );
            Food_Option_Variable()->Int(
                mcm->Add_Text_Option(" Food ", "")
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Misc ");
        mcm->Add_Empty_Option();
        {
            Soulgems_Option_Variable()->Int(
                mcm->Add_Text_Option(" Soulgems ", "")
            );
            Scrolls_Option_Variable()->Int(
                mcm->Add_Text_Option(" Scrolls ", "")
            );
            Metals_Option_Variable()->Int(
                mcm->Add_Text_Option(" Metals ", "")
            );
            Leather_Option_Variable()->Int(
                mcm->Add_Text_Option(" Leather ", "")
            );
            Gems_Option_Variable()->Int(
                mcm->Add_Text_Option(" Gems ", "")
            );
            Clutter_Option_Variable()->Int(
                mcm->Add_Text_Option(" Clutter ", "")
            );
            Keys_Option_Variable()->Int(
                mcm->Add_Text_Option(" Keys ", "")
            );
            Misc_Option_Variable()->Int(
                mcm->Add_Text_Option(" Others ", "")
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Books ");
        mcm->Add_Empty_Option();
        {
            Spell_Tomes_Option_Variable()->Int(
                mcm->Add_Text_Option(" Spell Tomes ", "")
            );
            Recipes_Option_Variable()->Int(
                mcm->Add_Text_Option(" Recipes ", "")
            );
            A_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" A ", "")
            );
            B_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" B ", "")
            );
            C_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" C ", "")
            );
            D_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" D ", "")
            );
            E_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" E ", "")
            );
            F_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" F ", "")
            );
            G_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" G ", "")
            );
            H_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" H ", "")
            );
            I_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" I ", "")
            );
            J_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" J ", "")
            );
            K_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" K ", "")
            );
            L_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" L ", "")
            );
            M_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" M ", "")
            );
            N_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" N ", "")
            );
            O_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" O ", "")
            );
            P_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" P ", "")
            );
            Q_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" Q ", "")
            );
            R_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" R ", "")
            );
            S_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" S ", "")
            );
            T_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" T ", "")
            );
            U_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" U ", "")
            );
            V_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" V ", "")
            );
            W_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" W ", "")
            );
            X_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" X ", "")
            );
            Y_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" Y ", "")
            );
            Z_Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" Z ", "")
            );
            Books_Option_Variable()->Int(
                mcm->Add_Text_Option(" # ", "")
            );
        }
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Custom ");
        mcm->Add_Empty_Option();
        {
            Custom_00_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(0)->String(), "")
            );
            Rename_Custom_00_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_01_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(1)->String(), "")
            );
            Rename_Custom_01_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_02_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(2)->String(), "")
            );
            Rename_Custom_02_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_03_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(3)->String(), "")
            );
            Rename_Custom_03_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_04_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(4)->String(), "")
            );
            Rename_Custom_04_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_05_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(5)->String(), "")
            );
            Rename_Custom_05_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_06_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(6)->String(), "")
            );
            Rename_Custom_06_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_07_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(7)->String(), "")
            );
            Rename_Custom_07_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_08_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(8)->String(), "")
            );
            Rename_Custom_08_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_09_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(9)->String(), "")
            );
            Rename_Custom_09_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_10_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(10)->String(), "")
            );
            Rename_Custom_10_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_11_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(11)->String(), "")
            );
            Rename_Custom_11_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_12_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(12)->String(), "")
            );
            Rename_Custom_12_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_13_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(13)->String(), "")
            );
            Rename_Custom_13_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_14_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(14)->String(), "")
            );
            Rename_Custom_14_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
            Custom_15_Option_Variable()->Int(
                mcm->Add_Text_Option(Custom_Names_Array()->Point(15)->String(), "")
            );
            Rename_Custom_15_Option_Variable()->Int(
                mcm->Add_Input_Option(" Rename ", "")
            );
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
    }

    void Chests_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        if (option == Input_Option_Variable()->Int()) { // Special
            Open_Chest(Consts::Input_Category(), " Input ", user_callback);

        } else if (option == Swords_Option_Variable()->Int()) { // Weapons
            Open_Chest(Consts::Swords_Category(), " Swords ", user_callback);
        } else if (option == Greatswords_Option_Variable()->Int()) {
            Open_Chest(Consts::Greatswords_Category(), " Greatswords ", user_callback);
        } else if (option == Waraxes_Option_Variable()->Int()) {
            Open_Chest(Consts::Waraxes_Category(), " Waraxes ", user_callback);
        } else if (option == Battleaxes_Option_Variable()->Int()) {
            Open_Chest(Consts::Battleaxes_Category(), " Battleaxes ", user_callback);
        } else if (option == Maces_Option_Variable()->Int()) {
            Open_Chest(Consts::Maces_Category(), " Maces ", user_callback);
        } else if (option == Warhammers_Option_Variable()->Int()) {
            Open_Chest(Consts::Warhammers_Category(), " Warhammers ", user_callback);
        } else if (option == Daggers_Option_Variable()->Int()) {
            Open_Chest(Consts::Daggers_Category(), " Daggers ", user_callback);
        } else if (option == Staves_Option_Variable()->Int()) {
            Open_Chest(Consts::Staves_Category(), " Staves ", user_callback);
        } else if (option == Bows_Option_Variable()->Int()) {
            Open_Chest(Consts::Bows_Category(), " Bows ", user_callback);
        } else if (option == Ammo_Option_Variable()->Int()) {
            Open_Chest(Consts::Ammo_Category(), " Ammo ", user_callback);
        } else if (option == Weapons_Option_Variable()->Int()) {
            Open_Chest(Consts::Weapons_Category(), " Other Weapons ", user_callback);

        } else if (option == Light_Armor_Option_Variable()->Int()) { // Armor
            Open_Chest(Consts::Light_Armor_Category(), " Light Armor ", user_callback);
        } else if (option == Heavy_Armor_Option_Variable()->Int()) {
            Open_Chest(Consts::Heavy_Armor_Category(), " Heavy Armor ", user_callback);
        } else if (option == Shields_Option_Variable()->Int()) {
            Open_Chest(Consts::Shields_Category(), " Shields ", user_callback);
        } else if (option == Jewelry_Option_Variable()->Int()) {
            Open_Chest(Consts::Jewelry_Category(), " Jewelry ", user_callback);
        } else if (option == Clothes_Option_Variable()->Int()) {
            Open_Chest(Consts::Clothes_Category(), " Clothes ", user_callback);

        } else if (option == Potions_Option_Variable()->Int()) { // Edibles
            Open_Chest(Consts::Potions_Category(), " Potions ", user_callback);
        } else if (option == Poisons_Option_Variable()->Int()) {
            Open_Chest(Consts::Poisons_Category(), " Poisons ", user_callback);
        } else if (option == Ingredients_Option_Variable()->Int()) {
            Open_Chest(Consts::Ingredients_Category(), " Ingredients ", user_callback);
        } else if (option == Food_Option_Variable()->Int()) {
            Open_Chest(Consts::Food_Category(), " Food ", user_callback);

        } else if (option == Soulgems_Option_Variable()->Int()) { // Misc
            Open_Chest(Consts::Soulgems_Category(), " Soulgems ", user_callback);
        } else if (option == Scrolls_Option_Variable()->Int()) {
            Open_Chest(Consts::Scrolls_Category(), " Scrolls ", user_callback);
        } else if (option == Metals_Option_Variable()->Int()) {
            Open_Chest(Consts::Metals_Category(), " Metals ", user_callback);
        } else if (option == Leather_Option_Variable()->Int()) {
            Open_Chest(Consts::Leather_Category(), " Leather ", user_callback);
        } else if (option == Gems_Option_Variable()->Int()) {
            Open_Chest(Consts::Gems_Category(), " Gems ", user_callback);
        } else if (option == Clutter_Option_Variable()->Int()) {
            Open_Chest(Consts::Clutter_Category(), " Clutter ", user_callback);
        } else if (option == Keys_Option_Variable()->Int()) {
            Open_Chest(Consts::Keys_Category(), " Keys ", user_callback);
        } else if (option == Misc_Option_Variable()->Int()) {
            Open_Chest(Consts::Misc_Category(), " Other Misc ", user_callback);

        } else if (option == Spell_Tomes_Option_Variable()->Int()) { // Books
            Open_Chest(Consts::Spell_Tomes_Category(), " Spell Tomes ", user_callback);
        } else if (option == Recipes_Option_Variable()->Int()) {
            Open_Chest(Consts::Recipes_Category(), " Recipes ", user_callback);
        } else if (option == A_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::A_Books_Category(), " A Books ", user_callback);
        } else if (option == B_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::B_Books_Category(), " B Books ", user_callback);
        } else if (option == C_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::C_Books_Category(), " C Books ", user_callback);
        } else if (option == D_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::D_Books_Category(), " D Books ", user_callback);
        } else if (option == E_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::E_Books_Category(), " E Books ", user_callback);
        } else if (option == F_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::F_Books_Category(), " F Books ", user_callback);
        } else if (option == G_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::G_Books_Category(), " G Books ", user_callback);
        } else if (option == H_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::H_Books_Category(), " H Books ", user_callback);
        } else if (option == I_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::I_Books_Category(), " I Books ", user_callback);
        } else if (option == J_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::J_Books_Category(), " J Books ", user_callback);
        } else if (option == K_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::K_Books_Category(), " K Books ", user_callback);
        } else if (option == L_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::L_Books_Category(), " L Books ", user_callback);
        } else if (option == M_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::M_Books_Category(), " M Books ", user_callback);
        } else if (option == N_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::N_Books_Category(), " N Books ", user_callback);
        } else if (option == O_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::O_Books_Category(), " O Books ", user_callback);
        } else if (option == P_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::P_Books_Category(), " P Books ", user_callback);
        } else if (option == Q_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Q_Books_Category(), " Q Books ", user_callback);
        } else if (option == R_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::R_Books_Category(), " R Books ", user_callback);
        } else if (option == S_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::S_Books_Category(), " S Books ", user_callback);
        } else if (option == T_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::T_Books_Category(), " T Books ", user_callback);
        } else if (option == U_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::U_Books_Category(), " U Books ", user_callback);
        } else if (option == V_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::V_Books_Category(), " V Books ", user_callback);
        } else if (option == W_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::W_Books_Category(), " W Books ", user_callback);
        } else if (option == X_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::X_Books_Category(), " X Books ", user_callback);
        } else if (option == Y_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Y_Books_Category(), " Y Books ", user_callback);
        } else if (option == Z_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Z_Books_Category(), " Z Books ", user_callback);
        } else if (option == Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Books_Category(), " # Books ", user_callback);

        } else if (option == Custom_00_Option_Variable()->Int()) { // Custom
            Open_Chest(Consts::Custom_00_Category(), Custom_Names_Array()->Point(0)->String(), user_callback);
        } else if (option == Custom_01_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_01_Category(), Custom_Names_Array()->Point(1)->String(), user_callback);
        } else if (option == Custom_02_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_02_Category(), Custom_Names_Array()->Point(2)->String(), user_callback);
        } else if (option == Custom_03_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_03_Category(), Custom_Names_Array()->Point(3)->String(), user_callback);
        } else if (option == Custom_04_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_04_Category(), Custom_Names_Array()->Point(4)->String(), user_callback);
        } else if (option == Custom_05_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_05_Category(), Custom_Names_Array()->Point(5)->String(), user_callback);
        } else if (option == Custom_06_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_06_Category(), Custom_Names_Array()->Point(6)->String(), user_callback);
        } else if (option == Custom_07_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_07_Category(), Custom_Names_Array()->Point(7)->String(), user_callback);
        } else if (option == Custom_08_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_08_Category(), Custom_Names_Array()->Point(8)->String(), user_callback);
        } else if (option == Custom_09_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_09_Category(), Custom_Names_Array()->Point(9)->String(), user_callback);
        } else if (option == Custom_10_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_10_Category(), Custom_Names_Array()->Point(10)->String(), user_callback);
        } else if (option == Custom_11_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_11_Category(), Custom_Names_Array()->Point(11)->String(), user_callback);
        } else if (option == Custom_12_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_12_Category(), Custom_Names_Array()->Point(12)->String(), user_callback);
        } else if (option == Custom_13_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_13_Category(), Custom_Names_Array()->Point(13)->String(), user_callback);
        } else if (option == Custom_14_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_14_Category(), Custom_Names_Array()->Point(14)->String(), user_callback);
        } else if (option == Custom_15_Option_Variable()->Int()) {
            Open_Chest(Consts::Custom_15_Category(), Custom_Names_Array()->Point(15)->String(), user_callback);
        } else {
            MCM::Main_t::Self()->Return_Latent(user_callback);
        }
    }

    void Chests_t::On_Option_Menu_Open(Int_t option)
    {

    }

    void Chests_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {

    }

    void Chests_t::On_Option_Slider_Open(Int_t option)
    {

    }

    void Chests_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {

    }

    void Chests_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        auto Update_Value = [&](Variable_t* custom_variable, Int_t idx, String_t value)->void
        {
            Custom_Names_Array()->Point(idx)->String(value);
            Main()->Reset_Page();
        };

        if (value && value.data && value.data[0]) {
            if (option == Rename_Custom_00_Option_Variable()->Int()) {
                Update_Value(Custom_00_Option_Variable(), 0, value);
            } else if (option == Rename_Custom_01_Option_Variable()->Int()) {
                Update_Value(Custom_01_Option_Variable(), 1, value);
            } else if (option == Rename_Custom_02_Option_Variable()->Int()) {
                Update_Value(Custom_02_Option_Variable(), 2, value);
            } else if (option == Rename_Custom_03_Option_Variable()->Int()) {
                Update_Value(Custom_03_Option_Variable(), 3, value);
            } else if (option == Rename_Custom_04_Option_Variable()->Int()) {
                Update_Value(Custom_04_Option_Variable(), 4, value);
            } else if (option == Rename_Custom_05_Option_Variable()->Int()) {
                Update_Value(Custom_05_Option_Variable(), 5, value);
            } else if (option == Rename_Custom_06_Option_Variable()->Int()) {
                Update_Value(Custom_06_Option_Variable(), 6, value);
            } else if (option == Rename_Custom_07_Option_Variable()->Int()) {
                Update_Value(Custom_07_Option_Variable(), 7, value);
            } else if (option == Rename_Custom_08_Option_Variable()->Int()) {
                Update_Value(Custom_08_Option_Variable(), 8, value);
            } else if (option == Rename_Custom_09_Option_Variable()->Int()) {
                Update_Value(Custom_09_Option_Variable(), 9, value);
            } else if (option == Rename_Custom_10_Option_Variable()->Int()) {
                Update_Value(Custom_10_Option_Variable(), 10, value);
            } else if (option == Rename_Custom_11_Option_Variable()->Int()) {
                Update_Value(Custom_11_Option_Variable(), 11, value);
            } else if (option == Rename_Custom_12_Option_Variable()->Int()) {
                Update_Value(Custom_12_Option_Variable(), 12, value);
            } else if (option == Rename_Custom_13_Option_Variable()->Int()) {
                Update_Value(Custom_13_Option_Variable(), 13, value);
            } else if (option == Rename_Custom_14_Option_Variable()->Int()) {
                Update_Value(Custom_14_Option_Variable(), 14, value);
            } else if (option == Rename_Custom_15_Option_Variable()->Int()) {
                Update_Value(Custom_15_Option_Variable(), 15, value);
            }
        }
    }

    void Chests_t::On_Option_Keymap_Change(Int_t option,
                                           Int_t key_code,
                                           String_t conflict,
                                           String_t conflicting_mod,
                                           Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Chests_t::On_Option_Default(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Chests_t::On_Option_Highlight(Int_t option)
    {
        Main_t* mcm = Main();

        if (option == Input_Option_Variable()->Int()) {
            mcm->Info_Text("Opens the input chest. The items contained therein will be sorted into each respective category.\n"
                           "Items will first be filtered through Custom Categories by their form id, and then into the rest.");
        }
    }

    void Chests_t::Open_Chest(Reference_t* chest, String_t name, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        Game::Update_NPCP_Categories();
        Object_Ref::Rename(chest, name);

        class Callback : public Virtual_Callback_t {
        public:
            Reference_t* chest;
            UCallback_t* user_callback;
            Callback(Reference_t* chest, UCallback_t* user_callback) :
                chest(chest), user_callback(user_callback)
            {
            }
            void operator()(Variable_t* result)
            {
                Object_Ref::Open_Container(chest);
                MCM::Main_t::Self()->Return_Latent(user_callback);
            }
        };
        Virtual_Callback_i* callback = new Callback(chest, user_callback);
        Main()->Close_Menus(&callback);
    }

    void Chests_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Chests_t,              \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
