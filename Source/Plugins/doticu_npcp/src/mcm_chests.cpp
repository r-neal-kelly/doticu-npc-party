/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "mcm_chests.h"
#include "strings.h"

namespace doticu_npcp { namespace MCM {

    Chests_t::Options::Options()
    {
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            custom_chests[idx] = -1;
            custom_renames[idx] = -1;
        }
    }

    Chests_t::Options   Chests_t::options   = Chests_t::Options();
    Chests_t::Save_Data Chests_t::save_data = Chests_t::Save_Data();

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
        save_data = Save_Data();

        save_data.custom_names.reserve(MAX_CUSTOM_CHESTS);
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            save_data.custom_names.push_back(Index_To_Default_Custom_Name(idx));
        }
    }

    void Chests_t::Before_Save()
    {
        Custom_Names() = save_data.custom_names;
    }

    void Chests_t::After_Load()
    {
        save_data.custom_names = Custom_Names();
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS - save_data.custom_names.size(); idx < end; idx += 1) {
            save_data.custom_names.push_back(Index_To_Default_Custom_Name(idx));
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
        options.soulgems = mcm->Add_Text_Option(Strings_t::SOULGEMS, Strings_t::_NONE_);
        options.scrolls = mcm->Add_Text_Option(Strings_t::SCROLLS, Strings_t::_NONE_);
        options.metals = mcm->Add_Text_Option(Strings_t::METALS, Strings_t::_NONE_);
        options.leather = mcm->Add_Text_Option(Strings_t::LEATHER, Strings_t::_NONE_);
        options.gems = mcm->Add_Text_Option(Strings_t::GEMS, Strings_t::_NONE_);
        options.clutter = mcm->Add_Text_Option(Strings_t::CLUTTER, Strings_t::_NONE_);
        options.keys = mcm->Add_Text_Option(Strings_t::KEYS, Strings_t::_NONE_);
        options.miscellaneous = mcm->Add_Text_Option(Strings_t::MISCELLANEOUS, Strings_t::_NONE_);
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
        options.other_books = mcm->Add_Text_Option(Strings_t::_POUND_, Strings_t::_NONE_);
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(Strings_t::CUSTOM);
        mcm->Add_Empty_Option();
        for (size_t idx = 0, end = MAX_CUSTOM_CHESTS; idx < end; idx += 1) {
            options.custom_chests[idx] = mcm->Add_Text_Option(save_data.custom_names[idx], Strings_t::_NONE_);
            options.custom_renames[idx] = mcm->Add_Text_Option(Strings_t::RENAME, Strings_t::_NONE_);
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();
    }

    void Chests_t::On_Option_Select(Int_t option, Latent_ID_t latent_id)
    {
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
    }

    void Chests_t::On_Option_Keymap_Change(Int_t option, Int_t key, String_t conflict, String_t mod, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Default(Int_t option, Latent_ID_t latent_id)
    {
    }

    void Chests_t::On_Option_Highlight(Int_t option, Latent_ID_t latent_id)
    {
    }

}}
