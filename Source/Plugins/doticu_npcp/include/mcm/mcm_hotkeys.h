/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Hotkeys_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Hotkeys_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

        // Buttons
        Variable_t* Set_Defaults_Option_Variable();
        Variable_t* Unset_All_Option_Variable();

        // Global
        Variable_t* G_Dialogue_Menu_Value_Option_Variable();
        Variable_t* G_Dialogue_Menu_Mods_Option_Variable();

        // NPC
        Variable_t* N_Toggle_Member_Value_Option_Variable();
        Variable_t* N_Toggle_Move_Value_Option_Variable();
        Variable_t* N_Move_Nearer_Value_Option_Variable();
        Variable_t* N_Move_Farther_Value_Option_Variable();
        Variable_t* N_Move_Rotate_Left_Value_Option_Variable();
        Variable_t* N_Move_Rotate_Right_Value_Option_Variable();
        Variable_t* N_Has_Base_Value_Option_Variable();
        Variable_t* N_Count_Base_Value_Option_Variable();
        Variable_t* N_Has_Head_Value_Option_Variable();
        Variable_t* N_Count_Heads_Value_Option_Variable();
        Variable_t* N_Toggle_Member_Mods_Option_Variable();
        Variable_t* N_Toggle_Move_Mods_Option_Variable();
        Variable_t* N_Move_Nearer_Mods_Option_Variable();
        Variable_t* N_Move_Farther_Mods_Option_Variable();
        Variable_t* N_Move_Rotate_Left_Mods_Option_Variable();
        Variable_t* N_Move_Rotate_Right_Mods_Option_Variable();
        Variable_t* N_Has_Base_Mods_Option_Variable();
        Variable_t* N_Count_Base_Mods_Option_Variable();
        Variable_t* N_Has_Head_Mods_Option_Variable();
        Variable_t* N_Count_Heads_Mods_Option_Variable();

        // Member
        Variable_t* M_Toggle_Clone_Value_Option_Variable();
        Variable_t* M_Toggle_Settler_Value_Option_Variable();
        Variable_t* M_Toggle_Thrall_Value_Option_Variable();
        Variable_t* M_Toggle_Immobile_Value_Option_Variable();
        Variable_t* M_Toggle_Paralyzed_Value_Option_Variable();
        Variable_t* M_Toggle_Follower_Value_Option_Variable();
        Variable_t* M_Toggle_Clone_Mods_Option_Variable();
        Variable_t* M_Toggle_Settler_Mods_Option_Variable();
        Variable_t* M_Toggle_Thrall_Mods_Option_Variable();
        Variable_t* M_Toggle_Immobile_Mods_Option_Variable();
        Variable_t* M_Toggle_Paralyzed_Mods_Option_Variable();
        Variable_t* M_Toggle_Follower_Mods_Option_Variable();

        // Follower
        Variable_t* F_Toggle_Sneak_Value_Option_Variable();
        Variable_t* F_Toggle_Saddler_Value_Option_Variable();
        Variable_t* F_Toggle_Sneak_Mods_Option_Variable();
        Variable_t* F_Toggle_Saddler_Mods_Option_Variable();

        // Members
        Variable_t* MS_Toggle_Display_Value_Option_Variable();
        Variable_t* MS_Display_Previous_Value_Option_Variable();
        Variable_t* MS_Display_Next_Value_Option_Variable();
        Variable_t* MS_Toggle_Display_Mods_Option_Variable();
        Variable_t* MS_Display_Previous_Mods_Option_Variable();
        Variable_t* MS_Display_Next_Mods_Option_Variable();

        // Followers
        Variable_t* FS_Summon_All_Value_Option_Variable();
        Variable_t* FS_Summon_Mobile_Value_Option_Variable();
        Variable_t* FS_Summon_Immobile_Value_Option_Variable();
        Variable_t* FS_Settle_Value_Option_Variable();
        Variable_t* FS_Unsettle_Value_Option_Variable();
        Variable_t* FS_Mobilize_Value_Option_Variable();
        Variable_t* FS_Immobilize_Value_Option_Variable();
        Variable_t* FS_Sneak_Value_Option_Variable();
        Variable_t* FS_Unsneak_Value_Option_Variable();
        Variable_t* FS_Saddle_Value_Option_Variable();
        Variable_t* FS_Unsaddle_Value_Option_Variable();
        Variable_t* FS_Resurrect_Value_Option_Variable();
        Variable_t* FS_Summon_All_Mods_Option_Variable();
        Variable_t* FS_Summon_Mobile_Mods_Option_Variable();
        Variable_t* FS_Summon_Immobile_Mods_Option_Variable();
        Variable_t* FS_Settle_Mods_Option_Variable();
        Variable_t* FS_Unsettle_Mods_Option_Variable();
        Variable_t* FS_Mobilize_Mods_Option_Variable();
        Variable_t* FS_Immobilize_Mods_Option_Variable();
        Variable_t* FS_Sneak_Mods_Option_Variable();
        Variable_t* FS_Unsneak_Mods_Option_Variable();
        Variable_t* FS_Saddle_Mods_Option_Variable();
        Variable_t* FS_Unsaddle_Mods_Option_Variable();
        Variable_t* FS_Resurrect_Mods_Option_Variable();

        // Buttons
        Int_t Set_Defaults_Option();
        Int_t Unset_All_Option();

        // Global
        Int_t G_Dialogue_Menu_Value_Option();
        Int_t G_Dialogue_Menu_Mods_Option();

        // NPC
        Int_t N_Toggle_Member_Value_Option();
        Int_t N_Toggle_Move_Value_Option();
        Int_t N_Move_Nearer_Value_Option();
        Int_t N_Move_Farther_Value_Option();
        Int_t N_Move_Rotate_Left_Value_Option();
        Int_t N_Move_Rotate_Right_Value_Option();
        Int_t N_Has_Base_Value_Option();
        Int_t N_Count_Base_Value_Option();
        Int_t N_Has_Head_Value_Option();
        Int_t N_Count_Heads_Value_Option();
        Int_t N_Toggle_Member_Mods_Option();
        Int_t N_Toggle_Move_Mods_Option();
        Int_t N_Move_Nearer_Mods_Option();
        Int_t N_Move_Farther_Mods_Option();
        Int_t N_Move_Rotate_Left_Mods_Option();
        Int_t N_Move_Rotate_Right_Mods_Option();
        Int_t N_Has_Base_Mods_Option();
        Int_t N_Count_Base_Mods_Option();
        Int_t N_Has_Head_Mods_Option();
        Int_t N_Count_Heads_Mods_Option();

        // Member
        Int_t M_Toggle_Clone_Value_Option();
        Int_t M_Toggle_Settler_Value_Option();
        Int_t M_Toggle_Thrall_Value_Option();
        Int_t M_Toggle_Immobile_Value_Option();
        Int_t M_Toggle_Paralyzed_Value_Option();
        Int_t M_Toggle_Follower_Value_Option();
        Int_t M_Toggle_Clone_Mods_Option();
        Int_t M_Toggle_Settler_Mods_Option();
        Int_t M_Toggle_Thrall_Mods_Option();
        Int_t M_Toggle_Immobile_Mods_Option();
        Int_t M_Toggle_Paralyzed_Mods_Option();
        Int_t M_Toggle_Follower_Mods_Option();

        // Follower
        Int_t F_Toggle_Sneak_Value_Option();
        Int_t F_Toggle_Saddler_Value_Option();
        Int_t F_Toggle_Sneak_Mods_Option();
        Int_t F_Toggle_Saddler_Mods_Option();

        // Members
        Int_t MS_Toggle_Display_Value_Option();
        Int_t MS_Display_Previous_Value_Option();
        Int_t MS_Display_Next_Value_Option();
        Int_t MS_Toggle_Display_Mods_Option();
        Int_t MS_Display_Previous_Mods_Option();
        Int_t MS_Display_Next_Mods_Option();

        // Followers
        Int_t FS_Summon_All_Value_Option();
        Int_t FS_Summon_Mobile_Value_Option();
        Int_t FS_Summon_Immobile_Value_Option();
        Int_t FS_Settle_Value_Option();
        Int_t FS_Unsettle_Value_Option();
        Int_t FS_Mobilize_Value_Option();
        Int_t FS_Immobilize_Value_Option();
        Int_t FS_Sneak_Value_Option();
        Int_t FS_Unsneak_Value_Option();
        Int_t FS_Saddle_Value_Option();
        Int_t FS_Unsaddle_Value_Option();
        Int_t FS_Resurrect_Value_Option();
        Int_t FS_Summon_All_Mods_Option();
        Int_t FS_Summon_Mobile_Mods_Option();
        Int_t FS_Summon_Immobile_Mods_Option();
        Int_t FS_Settle_Mods_Option();
        Int_t FS_Unsettle_Mods_Option();
        Int_t FS_Mobilize_Mods_Option();
        Int_t FS_Immobilize_Mods_Option();
        Int_t FS_Sneak_Mods_Option();
        Int_t FS_Unsneak_Mods_Option();
        Int_t FS_Saddle_Mods_Option();
        Int_t FS_Unsaddle_Mods_Option();
        Int_t FS_Resurrect_Mods_Option();

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

        void Can_Change_Hotkey(String_t hotkey, Int_t value, Int_t mod_1, Int_t mod_2, Int_t mod_3,
                               Callback_t<Hotkeys_t*, Bool_t>* user_callback);
        void Change_Hotkey_Value(Int_t option, Int_t value, Bool_t do_render = true);
        void Change_Hotkey_Mods(Int_t option, Int_t mod_1, Int_t mod_2, Int_t mod_3, Bool_t do_render = true);
        void Reset_Hotkeys();
        void Unset_Hotkeys();
        String_t Value_Option_To_Hotkey(Int_t value_option);
        String_t Mods_Option_To_Hotkey(Int_t mods_option);

        void Read_Pressed_Mods(String_t hotkey, Callback_t<Vector_t<Int_t>>* user_callback);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
