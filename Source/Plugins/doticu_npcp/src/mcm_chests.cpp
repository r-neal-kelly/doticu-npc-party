/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_chests.h"
#include "strings.h"

namespace doticu_npcp { namespace MCM {

    using Const_Chests_t = doticu_npcp::Chests_t;

    Chests_t::Options::Options()
    {
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            custom_chests[idx] = -1;
            custom_renames[idx] = -1;
        }
    }

    Chests_t::Options   Chests_t::options   = Chests_t::Options();
    Chests_t::Save      Chests_t::save      = Chests_t::Save();

    some<Chests_t*>     Chests_t::Self()        { return Consts_t::NPCP::Quest::Control(); }
    String_t            Chests_t::Class_Name()  { DEFINE_CLASS_NAME("doticu_npcp_mcm_chests"); }
    some<V::Class_t*>   Chests_t::Class()       { DEFINE_CLASS(); }
    some<V::Object_t*>  Chests_t::Object()      { DEFINE_OBJECT_STATIC(); }

    void Chests_t::Register_Me(some<V::Machine_t*> machine)
    {
    }

    V::Variable_tt<Vector_t<String_t>>& Chests_t::Custom_Names() { DEFINE_VARIABLE_REFERENCE(Vector_t<String_t>, "p_custom_names"); }

    static String_t Index_To_Default_Custom_Name(size_t index)
    {
        if (index < 9) {
            return std::string(Strings_t::CUSTOM) + "_0" + std::to_string(index + 1);
        } else {
            return std::string(Strings_t::CUSTOM) + "_" + std::to_string(index + 1);
        }
    }

    void Chests_t::Initialize()
    {
        options = Options();
        save = Save();

        save.custom_names.reserve(MAX_CUSTOM_CHESTS);
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            save.custom_names.push_back(Index_To_Default_Custom_Name(idx));
        }
    }

    void Chests_t::Before_Save()
    {
        Custom_Names() = save.custom_names;
    }

    void Chests_t::After_Load()
    {
        save.custom_names = Custom_Names();
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS - save.custom_names.size(); idx < end; idx += 1) {
            save.custom_names.push_back(Index_To_Default_Custom_Name(idx));
        }
    }

    void Chests_t::On_Config_Open()
    {
    }

    void Chests_t::On_Config_Close()
    {
    }

    void Chests_t::On_Page_Open(Bool_t is_refresh, Latent_ID_t latent_id)
    {
        some<Main_t*> mcm = Main_t::Self();

        options = Options();

        mcm->Title_Text(Strings_t::CHESTS);
        mcm->Current_Cursor_Position() = 0;
        mcm->Current_Cursor_Mode() = mcmlib::Cursor_e::LEFT_TO_RIGHT;

        mcm->Add_Header_Option(Strings_t::SPECIAL);
        mcm->Add_Empty_Option();
        options.input = mcm->Add_Text_Option(Strings_t::INPUT, Strings_t::_NONE_);
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Strings_t::WEAPONS);
        mcm->Add_Empty_Option();
        options.swords = mcm->Add_Text_Option(Strings_t::SWORDS, Strings_t::_NONE_);
        options.greatswords = mcm->Add_Text_Option(Strings_t::GREATSWORDS, Strings_t::_NONE_);
        options.waraxes = mcm->Add_Text_Option(Strings_t::WARAXES, Strings_t::_NONE_);
        options.battleaxes = mcm->Add_Text_Option(Strings_t::BATTLEAXES, Strings_t::_NONE_);
        options.maces = mcm->Add_Text_Option(Strings_t::MACES, Strings_t::_NONE_);
        options.warhammers = mcm->Add_Text_Option(Strings_t::WARHAMMERS, Strings_t::_NONE_);
        options.daggers = mcm->Add_Text_Option(Strings_t::DAGGERS, Strings_t::_NONE_);
        options.staves = mcm->Add_Text_Option(Strings_t::STAVES, Strings_t::_NONE_);
        options.bows = mcm->Add_Text_Option(Strings_t::BOWS, Strings_t::_NONE_);
        options.ammo = mcm->Add_Text_Option(Strings_t::AMMO, Strings_t::_NONE_);
        options.other_weapons = mcm->Add_Text_Option(Strings_t::OTHER_WEAPONS, Strings_t::_NONE_);
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Strings_t::APPAREL);
        mcm->Add_Empty_Option();
        options.light_armor = mcm->Add_Text_Option(Strings_t::LIGHT_ARMOR, Strings_t::_NONE_);
        options.heavy_armor = mcm->Add_Text_Option(Strings_t::HEAVY_ARMOR, Strings_t::_NONE_);
        options.shields = mcm->Add_Text_Option(Strings_t::SHIELDS, Strings_t::_NONE_);
        options.jewelry = mcm->Add_Text_Option(Strings_t::JEWELRY, Strings_t::_NONE_);
        options.clothes = mcm->Add_Text_Option(Strings_t::CLOTHES, Strings_t::_NONE_);
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Strings_t::EDIBLES);
        mcm->Add_Empty_Option();
        options.potions = mcm->Add_Text_Option(Strings_t::POTIONS, Strings_t::_NONE_);
        options.poisons = mcm->Add_Text_Option(Strings_t::POISONS, Strings_t::_NONE_);
        options.ingredients = mcm->Add_Text_Option(Strings_t::INGREDIENTS, Strings_t::_NONE_);
        options.food = mcm->Add_Text_Option(Strings_t::FOOD, Strings_t::_NONE_);
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Strings_t::MISCELLANEOUS);
        mcm->Add_Empty_Option();
        options.soul_gems = mcm->Add_Text_Option(Strings_t::SOUL_GEMS, Strings_t::_NONE_);
        options.scrolls = mcm->Add_Text_Option(Strings_t::SCROLLS, Strings_t::_NONE_);
        options.metals = mcm->Add_Text_Option(Strings_t::METALS, Strings_t::_NONE_);
        options.leather = mcm->Add_Text_Option(Strings_t::LEATHER, Strings_t::_NONE_);
        options.gems = mcm->Add_Text_Option(Strings_t::GEMS, Strings_t::_NONE_);
        options.clutter = mcm->Add_Text_Option(Strings_t::CLUTTER, Strings_t::_NONE_);
        options.keys = mcm->Add_Text_Option(Strings_t::KEYS, Strings_t::_NONE_);
        options.other_misc = mcm->Add_Text_Option(Strings_t::OTHER_MISC, Strings_t::_NONE_);
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Strings_t::BOOKS);
        mcm->Add_Empty_Option();
        options.spell_tomes = mcm->Add_Text_Option(Strings_t::SPELL_TOMES, Strings_t::_NONE_);
        options.recipes = mcm->Add_Text_Option(Strings_t::RECIPES, Strings_t::_NONE_);
        options.a_books = mcm->Add_Text_Option(Strings_t::A, Strings_t::_NONE_);
        options.b_books = mcm->Add_Text_Option(Strings_t::B, Strings_t::_NONE_);
        options.c_books = mcm->Add_Text_Option(Strings_t::C, Strings_t::_NONE_);
        options.d_books = mcm->Add_Text_Option(Strings_t::D, Strings_t::_NONE_);
        options.e_books = mcm->Add_Text_Option(Strings_t::E, Strings_t::_NONE_);
        options.f_books = mcm->Add_Text_Option(Strings_t::F, Strings_t::_NONE_);
        options.g_books = mcm->Add_Text_Option(Strings_t::G, Strings_t::_NONE_);
        options.h_books = mcm->Add_Text_Option(Strings_t::H, Strings_t::_NONE_);
        options.i_books = mcm->Add_Text_Option(Strings_t::I, Strings_t::_NONE_);
        options.j_books = mcm->Add_Text_Option(Strings_t::J, Strings_t::_NONE_);
        options.k_books = mcm->Add_Text_Option(Strings_t::K, Strings_t::_NONE_);
        options.l_books = mcm->Add_Text_Option(Strings_t::L, Strings_t::_NONE_);
        options.m_books = mcm->Add_Text_Option(Strings_t::M, Strings_t::_NONE_);
        options.n_books = mcm->Add_Text_Option(Strings_t::N, Strings_t::_NONE_);
        options.o_books = mcm->Add_Text_Option(Strings_t::O, Strings_t::_NONE_);
        options.p_books = mcm->Add_Text_Option(Strings_t::P, Strings_t::_NONE_);
        options.q_books = mcm->Add_Text_Option(Strings_t::Q, Strings_t::_NONE_);
        options.r_books = mcm->Add_Text_Option(Strings_t::R, Strings_t::_NONE_);
        options.s_books = mcm->Add_Text_Option(Strings_t::S, Strings_t::_NONE_);
        options.t_books = mcm->Add_Text_Option(Strings_t::T, Strings_t::_NONE_);
        options.u_books = mcm->Add_Text_Option(Strings_t::U, Strings_t::_NONE_);
        options.v_books = mcm->Add_Text_Option(Strings_t::V, Strings_t::_NONE_);
        options.w_books = mcm->Add_Text_Option(Strings_t::W, Strings_t::_NONE_);
        options.x_books = mcm->Add_Text_Option(Strings_t::X, Strings_t::_NONE_);
        options.y_books = mcm->Add_Text_Option(Strings_t::Y, Strings_t::_NONE_);
        options.z_books = mcm->Add_Text_Option(Strings_t::Z, Strings_t::_NONE_);
        options.other_books = mcm->Add_Text_Option(Strings_t::OTHER_BOOKS, Strings_t::_NONE_);
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Strings_t::CUSTOM);
        mcm->Add_Empty_Option();
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            options.custom_chests[idx] = mcm->Add_Text_Option(save.custom_names[idx], Strings_t::_NONE_);
            options.custom_renames[idx] = mcm->Add_Input_Option(Strings_t::RENAME, Strings_t::_NONE_);
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
    }

    void Chests_t::On_Option_Select(Int_t option, Latent_ID_t latent_id)
    {
        if (option == options.input)                    Const_Chests_t::Open_Chest(Chest_e::INPUT, Strings_t::INPUT);

        else if (option == options.swords)              Const_Chests_t::Open_Chest(Chest_e::SWORDS, Strings_t::SWORDS);
        else if (option == options.greatswords)         Const_Chests_t::Open_Chest(Chest_e::GREATSWORDS, Strings_t::GREATSWORDS);
        else if (option == options.waraxes)             Const_Chests_t::Open_Chest(Chest_e::WARAXES, Strings_t::WARAXES);
        else if (option == options.battleaxes)          Const_Chests_t::Open_Chest(Chest_e::BATTLEAXES, Strings_t::BATTLEAXES);
        else if (option == options.maces)               Const_Chests_t::Open_Chest(Chest_e::MACES, Strings_t::MACES);
        else if (option == options.warhammers)          Const_Chests_t::Open_Chest(Chest_e::WARHAMMERS, Strings_t::WARHAMMERS);
        else if (option == options.daggers)             Const_Chests_t::Open_Chest(Chest_e::DAGGERS, Strings_t::DAGGERS);
        else if (option == options.staves)              Const_Chests_t::Open_Chest(Chest_e::STAVES, Strings_t::STAVES);
        else if (option == options.bows)                Const_Chests_t::Open_Chest(Chest_e::BOWS, Strings_t::BOWS);
        else if (option == options.ammo)                Const_Chests_t::Open_Chest(Chest_e::AMMO, Strings_t::AMMO);
        else if (option == options.other_weapons)       Const_Chests_t::Open_Chest(Chest_e::OTHER_WEAPONS, Strings_t::OTHER_WEAPONS);

        else if (option == options.light_armor)         Const_Chests_t::Open_Chest(Chest_e::LIGHT_ARMOR, Strings_t::LIGHT_ARMOR);
        else if (option == options.heavy_armor)         Const_Chests_t::Open_Chest(Chest_e::HEAVY_ARMOR, Strings_t::HEAVY_ARMOR);
        else if (option == options.shields)             Const_Chests_t::Open_Chest(Chest_e::SHIELDS, Strings_t::SHIELDS);
        else if (option == options.jewelry)             Const_Chests_t::Open_Chest(Chest_e::JEWELRY, Strings_t::JEWELRY);
        else if (option == options.clothes)             Const_Chests_t::Open_Chest(Chest_e::CLOTHES, Strings_t::CLOTHES);

        else if (option == options.potions)             Const_Chests_t::Open_Chest(Chest_e::POTIONS, Strings_t::POTIONS);
        else if (option == options.poisons)             Const_Chests_t::Open_Chest(Chest_e::POISONS, Strings_t::POISONS);
        else if (option == options.ingredients)         Const_Chests_t::Open_Chest(Chest_e::INGREDIENTS, Strings_t::INGREDIENTS);
        else if (option == options.food)                Const_Chests_t::Open_Chest(Chest_e::FOOD, Strings_t::FOOD);

        else if (option == options.soul_gems)           Const_Chests_t::Open_Chest(Chest_e::SOUL_GEMS, Strings_t::SOUL_GEMS);
        else if (option == options.scrolls)             Const_Chests_t::Open_Chest(Chest_e::SCROLLS, Strings_t::SCROLLS);
        else if (option == options.metals)              Const_Chests_t::Open_Chest(Chest_e::METALS, Strings_t::METALS);
        else if (option == options.leather)             Const_Chests_t::Open_Chest(Chest_e::LEATHER, Strings_t::LEATHER);
        else if (option == options.gems)                Const_Chests_t::Open_Chest(Chest_e::GEMS, Strings_t::GEMS);
        else if (option == options.clutter)             Const_Chests_t::Open_Chest(Chest_e::CLUTTER, Strings_t::CLUTTER);
        else if (option == options.keys)                Const_Chests_t::Open_Chest(Chest_e::KEYS, Strings_t::KEYS);
        else if (option == options.other_misc)          Const_Chests_t::Open_Chest(Chest_e::OTHER_MISC, Strings_t::OTHER_MISC);

        else if (option == options.spell_tomes)         Const_Chests_t::Open_Chest(Chest_e::SPELL_TOMES, Strings_t::SPELL_TOMES);
        else if (option == options.recipes)             Const_Chests_t::Open_Chest(Chest_e::RECIPES, Strings_t::RECIPES);
        else if (option == options.a_books)             Const_Chests_t::Open_Chest(Chest_e::A_BOOKS, Strings_t::A_BOOKS);
        else if (option == options.b_books)             Const_Chests_t::Open_Chest(Chest_e::B_BOOKS, Strings_t::B_BOOKS);
        else if (option == options.c_books)             Const_Chests_t::Open_Chest(Chest_e::C_BOOKS, Strings_t::C_BOOKS);
        else if (option == options.d_books)             Const_Chests_t::Open_Chest(Chest_e::D_BOOKS, Strings_t::D_BOOKS);
        else if (option == options.e_books)             Const_Chests_t::Open_Chest(Chest_e::E_BOOKS, Strings_t::E_BOOKS);
        else if (option == options.f_books)             Const_Chests_t::Open_Chest(Chest_e::F_BOOKS, Strings_t::F_BOOKS);
        else if (option == options.g_books)             Const_Chests_t::Open_Chest(Chest_e::G_BOOKS, Strings_t::G_BOOKS);
        else if (option == options.h_books)             Const_Chests_t::Open_Chest(Chest_e::H_BOOKS, Strings_t::H_BOOKS);
        else if (option == options.i_books)             Const_Chests_t::Open_Chest(Chest_e::I_BOOKS, Strings_t::I_BOOKS);
        else if (option == options.j_books)             Const_Chests_t::Open_Chest(Chest_e::J_BOOKS, Strings_t::J_BOOKS);
        else if (option == options.k_books)             Const_Chests_t::Open_Chest(Chest_e::K_BOOKS, Strings_t::K_BOOKS);
        else if (option == options.l_books)             Const_Chests_t::Open_Chest(Chest_e::L_BOOKS, Strings_t::L_BOOKS);
        else if (option == options.m_books)             Const_Chests_t::Open_Chest(Chest_e::M_BOOKS, Strings_t::M_BOOKS);
        else if (option == options.n_books)             Const_Chests_t::Open_Chest(Chest_e::N_BOOKS, Strings_t::N_BOOKS);
        else if (option == options.o_books)             Const_Chests_t::Open_Chest(Chest_e::O_BOOKS, Strings_t::O_BOOKS);
        else if (option == options.p_books)             Const_Chests_t::Open_Chest(Chest_e::P_BOOKS, Strings_t::P_BOOKS);
        else if (option == options.q_books)             Const_Chests_t::Open_Chest(Chest_e::Q_BOOKS, Strings_t::Q_BOOKS);
        else if (option == options.r_books)             Const_Chests_t::Open_Chest(Chest_e::R_BOOKS, Strings_t::R_BOOKS);
        else if (option == options.s_books)             Const_Chests_t::Open_Chest(Chest_e::S_BOOKS, Strings_t::S_BOOKS);
        else if (option == options.t_books)             Const_Chests_t::Open_Chest(Chest_e::T_BOOKS, Strings_t::T_BOOKS);
        else if (option == options.u_books)             Const_Chests_t::Open_Chest(Chest_e::U_BOOKS, Strings_t::U_BOOKS);
        else if (option == options.v_books)             Const_Chests_t::Open_Chest(Chest_e::V_BOOKS, Strings_t::V_BOOKS);
        else if (option == options.w_books)             Const_Chests_t::Open_Chest(Chest_e::W_BOOKS, Strings_t::W_BOOKS);
        else if (option == options.x_books)             Const_Chests_t::Open_Chest(Chest_e::X_BOOKS, Strings_t::X_BOOKS);
        else if (option == options.y_books)             Const_Chests_t::Open_Chest(Chest_e::Y_BOOKS, Strings_t::Y_BOOKS);
        else if (option == options.z_books)             Const_Chests_t::Open_Chest(Chest_e::Z_BOOKS, Strings_t::Z_BOOKS);
        else if (option == options.other_books)         Const_Chests_t::Open_Chest(Chest_e::OTHER_BOOKS, Strings_t::OTHER_BOOKS);

        else if (option == options.custom_chests[0])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_00, save.custom_names[0]);
        else if (option == options.custom_chests[1])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_01, save.custom_names[1]);
        else if (option == options.custom_chests[2])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_02, save.custom_names[2]);
        else if (option == options.custom_chests[3])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_03, save.custom_names[3]);
        else if (option == options.custom_chests[4])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_04, save.custom_names[4]);
        else if (option == options.custom_chests[5])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_05, save.custom_names[5]);
        else if (option == options.custom_chests[6])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_06, save.custom_names[6]);
        else if (option == options.custom_chests[7])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_07, save.custom_names[7]);
        else if (option == options.custom_chests[8])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_08, save.custom_names[8]);
        else if (option == options.custom_chests[9])    Const_Chests_t::Open_Chest(Chest_e::CUSTOM_09, save.custom_names[9]);
        else if (option == options.custom_chests[10])   Const_Chests_t::Open_Chest(Chest_e::CUSTOM_10, save.custom_names[10]);
        else if (option == options.custom_chests[11])   Const_Chests_t::Open_Chest(Chest_e::CUSTOM_11, save.custom_names[11]);
        else if (option == options.custom_chests[12])   Const_Chests_t::Open_Chest(Chest_e::CUSTOM_12, save.custom_names[12]);
        else if (option == options.custom_chests[13])   Const_Chests_t::Open_Chest(Chest_e::CUSTOM_13, save.custom_names[13]);
        else if (option == options.custom_chests[14])   Const_Chests_t::Open_Chest(Chest_e::CUSTOM_14, save.custom_names[14]);
        else if (option == options.custom_chests[15])   Const_Chests_t::Open_Chest(Chest_e::CUSTOM_15, save.custom_names[15]);
    }

    void Chests_t::On_Option_Menu_Open(Int_t option, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Menu_Accept(Int_t option, Int_t index, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Slider_Open(Int_t option, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Slider_Accept(Int_t option, Float_t value, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Input_Accept(Int_t option, String_t value, Latent_ID_t latent_id)
    {
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            if (options.custom_renames[idx] == option) {
                save.custom_names[idx] = value ? value : Index_To_Default_Custom_Name(idx);
                Main_t::Self()->Reset_Page();
                return;
            }
        }
    }

    void Chests_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Default(Int_t option, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Highlight(Int_t option, Latent_ID_t latent_id)
    {
        some<Main_t*> mcm = Main_t::Self();

        if (option == options.input) {
            mcm->Current_Info_Text() =
                "Opens the input chest. The items contained therein will be sorted into each respective category below.\n"
                "Items will first be filtered through Custom Categories by their form id, and then into other chests.";
        }
    }

}}
