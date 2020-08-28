/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
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

    void Chests_t::Build_Page()
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
    }

    void Chests_t::On_Option_Select(Int_t option)
    {
        if (option == Input_Option_Variable()->Int()) { // Special
            Open_Chest(Consts::Input_Category(), " Input ");

        } else if (option == Swords_Option_Variable()->Int()) { // Weapons
            Open_Chest(Consts::Swords_Category(), " Swords ");
        } else if (option == Greatswords_Option_Variable()->Int()) {
            Open_Chest(Consts::Greatswords_Category(), " Greatswords ");
        } else if (option == Waraxes_Option_Variable()->Int()) {
            Open_Chest(Consts::Waraxes_Category(), " Waraxes ");
        } else if (option == Battleaxes_Option_Variable()->Int()) {
            Open_Chest(Consts::Battleaxes_Category(), " Battleaxes ");
        } else if (option == Maces_Option_Variable()->Int()) {
            Open_Chest(Consts::Maces_Category(), " Maces ");
        } else if (option == Warhammers_Option_Variable()->Int()) {
            Open_Chest(Consts::Warhammers_Category(), " Warhammers ");
        } else if (option == Daggers_Option_Variable()->Int()) {
            Open_Chest(Consts::Daggers_Category(), " Daggers ");
        } else if (option == Staves_Option_Variable()->Int()) {
            Open_Chest(Consts::Staves_Category(), " Staves ");
        } else if (option == Bows_Option_Variable()->Int()) {
            Open_Chest(Consts::Bows_Category(), " Bows ");
        } else if (option == Ammo_Option_Variable()->Int()) {
            Open_Chest(Consts::Ammo_Category(), " Ammo ");
        } else if (option == Weapons_Option_Variable()->Int()) {
            Open_Chest(Consts::Weapons_Category(), " Other Weapons ");

        } else if (option == Light_Armor_Option_Variable()->Int()) { // Armor
            Open_Chest(Consts::Light_Armor_Category(), " Light Armor ");
        } else if (option == Heavy_Armor_Option_Variable()->Int()) {
            Open_Chest(Consts::Heavy_Armor_Category(), " Heavy Armor ");
        } else if (option == Shields_Option_Variable()->Int()) {
            Open_Chest(Consts::Shields_Category(), " Shields ");
        } else if (option == Jewelry_Option_Variable()->Int()) {
            Open_Chest(Consts::Jewelry_Category(), " Jewelry ");
        } else if (option == Clothes_Option_Variable()->Int()) {
            Open_Chest(Consts::Clothes_Category(), " Clothes ");

        } else if (option == Potions_Option_Variable()->Int()) { // Edibles
            Open_Chest(Consts::Potions_Category(), " Potions ");
        } else if (option == Poisons_Option_Variable()->Int()) {
            Open_Chest(Consts::Poisons_Category(), " Poisons ");
        } else if (option == Ingredients_Option_Variable()->Int()) {
            Open_Chest(Consts::Ingredients_Category(), " Ingredients ");
        } else if (option == Food_Option_Variable()->Int()) {
            Open_Chest(Consts::Food_Category(), " Food ");

        } else if (option == Soulgems_Option_Variable()->Int()) { // Misc
            Open_Chest(Consts::Soulgems_Category(), " Soulgems ");
        } else if (option == Scrolls_Option_Variable()->Int()) {
            Open_Chest(Consts::Scrolls_Category(), " Scrolls ");
        } else if (option == Metals_Option_Variable()->Int()) {
            Open_Chest(Consts::Metals_Category(), " Metals ");
        } else if (option == Leather_Option_Variable()->Int()) {
            Open_Chest(Consts::Leather_Category(), " Leather ");
        } else if (option == Gems_Option_Variable()->Int()) {
            Open_Chest(Consts::Gems_Category(), " Gems ");
        } else if (option == Clutter_Option_Variable()->Int()) {
            Open_Chest(Consts::Clutter_Category(), " Clutter ");
        } else if (option == Keys_Option_Variable()->Int()) {
            Open_Chest(Consts::Keys_Category(), " Keys ");
        } else if (option == Misc_Option_Variable()->Int()) {
            Open_Chest(Consts::Misc_Category(), " Other Misc ");

        } else if (option == Spell_Tomes_Option_Variable()->Int()) { // Books
            Open_Chest(Consts::Spell_Tomes_Category(), " Spell Tomes ");
        } else if (option == Recipes_Option_Variable()->Int()) {
            Open_Chest(Consts::Recipes_Category(), " Recipes ");
        } else if (option == A_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::A_Books_Category(), " A Books ");
        } else if (option == B_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::B_Books_Category(), " B Books ");
        } else if (option == C_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::C_Books_Category(), " C Books ");
        } else if (option == D_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::D_Books_Category(), " D Books ");
        } else if (option == E_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::E_Books_Category(), " E Books ");
        } else if (option == F_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::F_Books_Category(), " F Books ");
        } else if (option == G_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::G_Books_Category(), " G Books ");
        } else if (option == H_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::H_Books_Category(), " H Books ");
        } else if (option == I_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::I_Books_Category(), " I Books ");
        } else if (option == J_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::J_Books_Category(), " J Books ");
        } else if (option == K_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::K_Books_Category(), " K Books ");
        } else if (option == L_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::L_Books_Category(), " L Books ");
        } else if (option == M_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::M_Books_Category(), " M Books ");
        } else if (option == N_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::N_Books_Category(), " N Books ");
        } else if (option == O_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::O_Books_Category(), " O Books ");
        } else if (option == P_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::P_Books_Category(), " P Books ");
        } else if (option == Q_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Q_Books_Category(), " Q Books ");
        } else if (option == R_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::R_Books_Category(), " R Books ");
        } else if (option == S_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::S_Books_Category(), " S Books ");
        } else if (option == T_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::T_Books_Category(), " T Books ");
        } else if (option == U_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::U_Books_Category(), " U Books ");
        } else if (option == V_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::V_Books_Category(), " V Books ");
        } else if (option == W_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::W_Books_Category(), " W Books ");
        } else if (option == X_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::X_Books_Category(), " X Books ");
        } else if (option == Y_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Y_Books_Category(), " Y Books ");
        } else if (option == Z_Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Z_Books_Category(), " Z Books ");
        } else if (option == Books_Option_Variable()->Int()) {
            Open_Chest(Consts::Books_Category(), " # Books ");
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

    }

    void Chests_t::On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod)
    {

    }

    void Chests_t::On_Option_Default(Int_t option)
    {

    }

    void Chests_t::On_Option_Highlight(Int_t option)
    {
        Main_t* mcm = Main();

        if (option == Input_Option_Variable()->Int()) {
            mcm->Info_Text("Opens the input chest. The items contained therein will be sorted into each respective category.");
        }
    }

    void Chests_t::Open_Chest(Reference_t* chest, String_t name)
    {
        Object_Ref::Categorize(Consts::Input_Category());
        Object_Ref::Rename(chest, name);

        class Callback : public Virtual_Callback_t {
        public:
            Reference_t* chest;
            Callback(Reference_t* chest) :
                chest(chest)
            {
            }
            void operator()(Variable_t* result)
            {
                Object_Ref::Open_Container(chest);
            }
        };
        Virtual_Callback_i* callback = new Callback(chest);
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

        METHOD("f_Build_Page", 0, void, Build_Page);

        METHOD("f_On_Option_Select", 1, void, On_Option_Select, Int_t);
        METHOD("f_On_Option_Menu_Open", 1, void, On_Option_Menu_Open, Int_t);
        METHOD("f_On_Option_Menu_Accept", 2, void, On_Option_Menu_Accept, Int_t, Int_t);
        METHOD("f_On_Option_Slider_Open", 1, void, On_Option_Slider_Open, Int_t);
        METHOD("f_On_Option_Slider_Accept", 2, void, On_Option_Slider_Accept, Int_t, Float_t);
        METHOD("f_On_Option_Input_Accept", 2, void, On_Option_Input_Accept, Int_t, String_t);
        METHOD("f_On_Option_Keymap_Change", 4, void, On_Option_Keymap_Change, Int_t, Int_t, String_t, String_t);
        METHOD("f_On_Option_Default", 1, void, On_Option_Default, Int_t);
        METHOD("f_On_Option_Highlight", 1, void, On_Option_Highlight, Int_t);

        #undef METHOD
    }

}}}
