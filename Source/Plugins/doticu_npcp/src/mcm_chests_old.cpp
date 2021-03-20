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
