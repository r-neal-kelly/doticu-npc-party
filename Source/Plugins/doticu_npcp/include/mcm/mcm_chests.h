/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Chests_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Chests_t* Self();
        static Object_t* Object();

        static Main_t* Main();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Input_Option_Variable();

        Variable_t* Swords_Option_Variable();
        Variable_t* Greatswords_Option_Variable();
        Variable_t* Waraxes_Option_Variable();
        Variable_t* Battleaxes_Option_Variable();
        Variable_t* Maces_Option_Variable();
        Variable_t* Warhammers_Option_Variable();
        Variable_t* Daggers_Option_Variable();
        Variable_t* Staves_Option_Variable();
        Variable_t* Bows_Option_Variable();
        Variable_t* Ammo_Option_Variable();
        Variable_t* Weapons_Option_Variable();

        Variable_t* Light_Armor_Option_Variable();
        Variable_t* Heavy_Armor_Option_Variable();
        Variable_t* Shields_Option_Variable();
        Variable_t* Jewelry_Option_Variable();
        Variable_t* Clothes_Option_Variable();

        Variable_t* Potions_Option_Variable();
        Variable_t* Poisons_Option_Variable();
        Variable_t* Ingredients_Option_Variable();
        Variable_t* Food_Option_Variable();

        Variable_t* Soulgems_Option_Variable();
        Variable_t* Scrolls_Option_Variable();
        Variable_t* Metals_Option_Variable();
        Variable_t* Leather_Option_Variable();
        Variable_t* Gems_Option_Variable();
        Variable_t* Clutter_Option_Variable();
        Variable_t* Keys_Option_Variable();
        Variable_t* Misc_Option_Variable();

        Variable_t* Spell_Tomes_Option_Variable();
        Variable_t* Recipes_Option_Variable();
        Variable_t* A_Books_Option_Variable();
        Variable_t* B_Books_Option_Variable();
        Variable_t* C_Books_Option_Variable();
        Variable_t* D_Books_Option_Variable();
        Variable_t* E_Books_Option_Variable();
        Variable_t* F_Books_Option_Variable();
        Variable_t* G_Books_Option_Variable();
        Variable_t* H_Books_Option_Variable();
        Variable_t* I_Books_Option_Variable();
        Variable_t* J_Books_Option_Variable();
        Variable_t* K_Books_Option_Variable();
        Variable_t* L_Books_Option_Variable();
        Variable_t* M_Books_Option_Variable();
        Variable_t* N_Books_Option_Variable();
        Variable_t* O_Books_Option_Variable();
        Variable_t* P_Books_Option_Variable();
        Variable_t* Q_Books_Option_Variable();
        Variable_t* R_Books_Option_Variable();
        Variable_t* S_Books_Option_Variable();
        Variable_t* T_Books_Option_Variable();
        Variable_t* U_Books_Option_Variable();
        Variable_t* V_Books_Option_Variable();
        Variable_t* W_Books_Option_Variable();
        Variable_t* X_Books_Option_Variable();
        Variable_t* Y_Books_Option_Variable();
        Variable_t* Z_Books_Option_Variable();
        Variable_t* Books_Option_Variable();

        void Build_Page();

        void On_Option_Select(Int_t option);
        void On_Option_Menu_Open(Int_t option);
        void On_Option_Menu_Accept(Int_t option, Int_t idx);
        void On_Option_Slider_Open(Int_t option);
        void On_Option_Slider_Accept(Int_t option, Float_t value);
        void On_Option_Input_Accept(Int_t option, String_t value);
        void On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod);
        void On_Option_Default(Int_t option);
        void On_Option_Highlight(Int_t option);

        void Open_Chest(Reference_t* chest, String_t name);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
