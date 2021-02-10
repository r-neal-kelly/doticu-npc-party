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

        class Callback : public Callback_t<> {
        public:
            Reference_t* chest;
            UCallback_t* user_callback;
            Callback(Reference_t* chest, UCallback_t* user_callback) :
                chest(chest), user_callback(user_callback)
            {
            }
            void operator()()
            {
                Object_Ref::Open_Container(chest);
                MCM::Main_t::Self()->Return_Latent(user_callback);
            }
        };
        Main()->Close_Menus(new Callback(chest, user_callback));
    }

}}}
