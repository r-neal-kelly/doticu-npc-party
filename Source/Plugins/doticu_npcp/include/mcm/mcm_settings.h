/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    using namespace Modules;

    class Main_t;

    class Settings_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Settings_t* Self();
        static Object_t* Object();

        static Main_t* Main();

    public:
        Variable_t* Variable(String_t variable_name);

        // General
        Variable_t* Allow_Dialogue_For_All_Option_Variable();
        Variable_t* Allow_Chatter_Option_Variable();
        Variable_t* Force_Cleanup_Option_Variable();

        // Members
        Variable_t* Member_Limit_Option_Variable();
        Variable_t* Member_Display_Limit_Option_Variable();
        Variable_t* Default_Member_Style_Option_Variable();
        Variable_t* Default_Member_Vitality_Option_Variable();

        // Clones
        Variable_t* Force_Clone_Uniques_Option_Variable();
        Variable_t* Force_Clone_Generics_Option_Variable();
        Variable_t* Force_Unclone_Uniques_Option_Variable();
        Variable_t* Force_Unclone_Generics_Option_Variable();
        Variable_t* Clone_Outfit_Algorithm_Option_Variable();

        // Followers
        Variable_t* Do_Auto_Resurrect_Followers_Option_Variable();
        Variable_t* Do_Level_Followers_Option_Variable();

        // Outfits
        Variable_t* Do_Auto_Change_Outfits_Option_Variable();
        Variable_t* Do_Auto_Change_Immobile_Outfit_Option_Variable();
        Variable_t* Do_Auto_Fill_Outfits_Option_Variable();
        Variable_t* Fill_Outfit_Body_Chance_Option_Variable();
        Variable_t* Fill_Outfit_Head_Chance_Option_Variable();
        Variable_t* Fill_Outfit_Hands_Chance_Option_Variable();
        Variable_t* Fill_Outfit_Feet_Chance_Option_Variable();        
        
        // Sorting
        Variable_t* Member_Sort_Algorithm_Option_Variable();
        Variable_t* Follower_Sort_Algorithm_Option_Variable();

        void On_Build_Page();
        void On_Option_Select(Int_t option, Callback_t<>* user_callback);
        void On_Option_Menu_Open(Int_t option);
        void On_Option_Menu_Accept(Int_t option, Int_t idx);
        void On_Option_Slider_Open(Int_t option);
        void On_Option_Slider_Accept(Int_t option, Float_t value);
        void On_Option_Input_Accept(Int_t option, String_t value);
        void On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod, Callback_t<>* user_callback);
        void On_Option_Default(Int_t option);
        void On_Option_Highlight(Int_t option);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
