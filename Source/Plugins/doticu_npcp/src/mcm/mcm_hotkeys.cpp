/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/Hooks_DirectInput8Create.h"

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "form.h"
#include "keys.h"
#include "papyrus.inl"
#include "utils.h"
#include "vars.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_hotkeys.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Hotkeys_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_hotkeys");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Hotkeys_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Hotkeys_t* Hotkeys_t::Self()
    {
        return static_cast<Hotkeys_t*>(Consts::Control_Quest());
    }

    Object_t* Hotkeys_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Hotkeys_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Hotkeys_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    // Buttons
    Variable_t* Hotkeys_t::Set_Defaults_Option_Variable() { DEFINE_VARIABLE("p_option_set_defaults"); }
    Variable_t* Hotkeys_t::Unset_All_Option_Variable() { DEFINE_VARIABLE("p_option_unset_all"); }

    // Global
    Variable_t* Hotkeys_t::G_Dialogue_Menu_Value_Option_Variable() { DEFINE_VARIABLE("p_option_g_dialogue_menu"); }
    Variable_t* Hotkeys_t::G_Dialogue_Menu_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_g_dialogue_menu_mods"); }

    // NPC
    Variable_t* Hotkeys_t::N_Toggle_Member_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_toggle_member"); }
    Variable_t* Hotkeys_t::N_Toggle_Move_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_toggle_move"); }
    Variable_t* Hotkeys_t::N_Move_Nearer_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_nearer"); }
    Variable_t* Hotkeys_t::N_Move_Farther_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_farther"); }
    Variable_t* Hotkeys_t::N_Move_Rotate_Left_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_rotate_left"); }
    Variable_t* Hotkeys_t::N_Move_Rotate_Right_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_rotate_right"); }
    Variable_t* Hotkeys_t::N_Has_Base_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_has_base"); }
    Variable_t* Hotkeys_t::N_Count_Base_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_count_base"); }
    Variable_t* Hotkeys_t::N_Has_Head_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_has_head"); }
    Variable_t* Hotkeys_t::N_Count_Heads_Value_Option_Variable() { DEFINE_VARIABLE("p_option_n_count_heads"); }
    Variable_t* Hotkeys_t::N_Toggle_Member_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_toggle_member_mods"); }
    Variable_t* Hotkeys_t::N_Toggle_Move_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_toggle_move_mods"); }
    Variable_t* Hotkeys_t::N_Move_Nearer_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_nearer_mods"); }
    Variable_t* Hotkeys_t::N_Move_Farther_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_farther_mods"); }
    Variable_t* Hotkeys_t::N_Move_Rotate_Left_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_rotate_left_mods"); }
    Variable_t* Hotkeys_t::N_Move_Rotate_Right_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_move_rotate_right_mods"); }
    Variable_t* Hotkeys_t::N_Has_Base_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_has_base_mods"); }
    Variable_t* Hotkeys_t::N_Count_Base_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_count_base_mods"); }
    Variable_t* Hotkeys_t::N_Has_Head_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_has_head_mods"); }
    Variable_t* Hotkeys_t::N_Count_Heads_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_n_count_heads_mods"); }

    // Member
    Variable_t* Hotkeys_t::M_Toggle_Clone_Value_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_clone"); }
    Variable_t* Hotkeys_t::M_Toggle_Settler_Value_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_settler"); }
    Variable_t* Hotkeys_t::M_Toggle_Thrall_Value_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_thrall"); }
    Variable_t* Hotkeys_t::M_Toggle_Immobile_Value_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_immobile"); }
    Variable_t* Hotkeys_t::M_Toggle_Paralyzed_Value_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_paralyzed"); }
    Variable_t* Hotkeys_t::M_Toggle_Follower_Value_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_follower"); }
    Variable_t* Hotkeys_t::M_Toggle_Clone_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_clone_mods"); }
    Variable_t* Hotkeys_t::M_Toggle_Settler_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_settler_mods"); }
    Variable_t* Hotkeys_t::M_Toggle_Thrall_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_thrall_mods"); }
    Variable_t* Hotkeys_t::M_Toggle_Immobile_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_immobile_mods"); }
    Variable_t* Hotkeys_t::M_Toggle_Paralyzed_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_paralyzed_mods"); }
    Variable_t* Hotkeys_t::M_Toggle_Follower_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_m_toggle_follower_mods"); }

    // Follower
    Variable_t* Hotkeys_t::F_Toggle_Sneak_Value_Option_Variable() { DEFINE_VARIABLE("p_option_f_toggle_sneak"); }
    Variable_t* Hotkeys_t::F_Toggle_Saddler_Value_Option_Variable() { DEFINE_VARIABLE("p_option_f_toggle_saddler"); }
    Variable_t* Hotkeys_t::F_Toggle_Sneak_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_f_toggle_sneak_mods"); }
    Variable_t* Hotkeys_t::F_Toggle_Saddler_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_f_toggle_saddler_mods"); }

    // Members
    Variable_t* Hotkeys_t::MS_Toggle_Display_Value_Option_Variable() { DEFINE_VARIABLE("p_option_ms_toggle_display"); }
    Variable_t* Hotkeys_t::MS_Display_Previous_Value_Option_Variable() { DEFINE_VARIABLE("p_option_ms_display_previous"); }
    Variable_t* Hotkeys_t::MS_Display_Next_Value_Option_Variable() { DEFINE_VARIABLE("p_option_ms_display_next"); }
    Variable_t* Hotkeys_t::MS_Toggle_Display_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_ms_toggle_display_mods"); }
    Variable_t* Hotkeys_t::MS_Display_Previous_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_ms_display_previous_mods"); }
    Variable_t* Hotkeys_t::MS_Display_Next_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_ms_display_next_mods"); }

    // Followers
    Variable_t* Hotkeys_t::FS_Summon_All_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_summon_all"); }
    Variable_t* Hotkeys_t::FS_Summon_Mobile_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_summon_mobile"); }
    Variable_t* Hotkeys_t::FS_Summon_Immobile_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_summon_immobile"); }
    Variable_t* Hotkeys_t::FS_Settle_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_settle"); }
    Variable_t* Hotkeys_t::FS_Unsettle_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_unsettle"); }
    Variable_t* Hotkeys_t::FS_Mobilize_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_mobilize"); }
    Variable_t* Hotkeys_t::FS_Immobilize_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_immobilize"); }
    Variable_t* Hotkeys_t::FS_Sneak_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_sneak"); }
    Variable_t* Hotkeys_t::FS_Unsneak_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_unsneak"); }
    Variable_t* Hotkeys_t::FS_Saddle_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_saddle"); }
    Variable_t* Hotkeys_t::FS_Unsaddle_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_unsaddle"); }
    Variable_t* Hotkeys_t::FS_Resurrect_Value_Option_Variable() { DEFINE_VARIABLE("p_option_fs_resurrect"); }
    Variable_t* Hotkeys_t::FS_Summon_All_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_summon_all_mods"); }
    Variable_t* Hotkeys_t::FS_Summon_Mobile_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_summon_mobile_mods"); }
    Variable_t* Hotkeys_t::FS_Summon_Immobile_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_summon_immobile_mods"); }
    Variable_t* Hotkeys_t::FS_Settle_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_settle_mods"); }
    Variable_t* Hotkeys_t::FS_Unsettle_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_unsettle_mods"); }
    Variable_t* Hotkeys_t::FS_Mobilize_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_mobilize_mods"); }
    Variable_t* Hotkeys_t::FS_Immobilize_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_immobilize_mods"); }
    Variable_t* Hotkeys_t::FS_Sneak_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_sneak_mods"); }
    Variable_t* Hotkeys_t::FS_Unsneak_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_unsneak_mods"); }
    Variable_t* Hotkeys_t::FS_Saddle_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_saddle_mods"); }
    Variable_t* Hotkeys_t::FS_Unsaddle_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_unsaddle_mods"); }
    Variable_t* Hotkeys_t::FS_Resurrect_Mods_Option_Variable() { DEFINE_VARIABLE("p_option_fs_resurrect_mods"); }

    // Buttons
    Int_t Hotkeys_t::Set_Defaults_Option() { return Set_Defaults_Option_Variable()->Int(); }
    Int_t Hotkeys_t::Unset_All_Option() { return Unset_All_Option_Variable()->Int(); }

    // Global
    Int_t Hotkeys_t::G_Dialogue_Menu_Value_Option() { return G_Dialogue_Menu_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::G_Dialogue_Menu_Mods_Option() { return G_Dialogue_Menu_Mods_Option_Variable()->Int(); }

    // NPC
    Int_t Hotkeys_t::N_Toggle_Member_Value_Option() { return N_Toggle_Member_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Toggle_Move_Value_Option() { return N_Toggle_Move_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Nearer_Value_Option() { return N_Move_Nearer_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Farther_Value_Option() { return N_Move_Farther_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Rotate_Left_Value_Option() { return N_Move_Rotate_Left_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Rotate_Right_Value_Option() { return N_Move_Rotate_Right_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Has_Base_Value_Option() { return N_Has_Base_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Count_Base_Value_Option() { return N_Count_Base_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Has_Head_Value_Option() { return N_Has_Head_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Count_Heads_Value_Option() { return N_Count_Heads_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Toggle_Member_Mods_Option() { return N_Toggle_Member_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Toggle_Move_Mods_Option() { return N_Toggle_Move_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Nearer_Mods_Option() { return N_Move_Nearer_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Farther_Mods_Option() { return N_Move_Farther_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Rotate_Left_Mods_Option() { return N_Move_Rotate_Left_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Move_Rotate_Right_Mods_Option() { return N_Move_Rotate_Right_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Has_Base_Mods_Option() { return N_Has_Base_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Count_Base_Mods_Option() { return N_Count_Base_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Has_Head_Mods_Option() { return N_Has_Head_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::N_Count_Heads_Mods_Option() { return N_Count_Heads_Mods_Option_Variable()->Int(); }

    // Member
    Int_t Hotkeys_t::M_Toggle_Clone_Value_Option() { return M_Toggle_Clone_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Settler_Value_Option() { return M_Toggle_Settler_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Thrall_Value_Option() { return M_Toggle_Thrall_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Immobile_Value_Option() { return M_Toggle_Immobile_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Paralyzed_Value_Option() { return M_Toggle_Paralyzed_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Follower_Value_Option() { return M_Toggle_Follower_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Clone_Mods_Option() { return M_Toggle_Clone_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Settler_Mods_Option() { return M_Toggle_Settler_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Thrall_Mods_Option() { return M_Toggle_Thrall_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Immobile_Mods_Option() { return M_Toggle_Immobile_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Paralyzed_Mods_Option() { return M_Toggle_Paralyzed_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::M_Toggle_Follower_Mods_Option() { return M_Toggle_Follower_Mods_Option_Variable()->Int(); }

    // Follower
    Int_t Hotkeys_t::F_Toggle_Sneak_Value_Option() { return F_Toggle_Sneak_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::F_Toggle_Saddler_Value_Option() { return F_Toggle_Saddler_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::F_Toggle_Sneak_Mods_Option() { return F_Toggle_Sneak_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::F_Toggle_Saddler_Mods_Option() { return F_Toggle_Saddler_Mods_Option_Variable()->Int(); }

    // Members
    Int_t Hotkeys_t::MS_Toggle_Display_Value_Option() { return MS_Toggle_Display_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::MS_Display_Previous_Value_Option() { return MS_Display_Previous_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::MS_Display_Next_Value_Option() { return MS_Display_Next_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::MS_Toggle_Display_Mods_Option() { return MS_Toggle_Display_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::MS_Display_Previous_Mods_Option() { return MS_Display_Previous_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::MS_Display_Next_Mods_Option() { return MS_Display_Next_Mods_Option_Variable()->Int(); }

    // Followers
    Int_t Hotkeys_t::FS_Summon_All_Value_Option() { return FS_Summon_All_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Summon_Mobile_Value_Option() { return FS_Summon_Mobile_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Summon_Immobile_Value_Option() { return FS_Summon_Immobile_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Settle_Value_Option() { return FS_Settle_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Unsettle_Value_Option() { return FS_Unsettle_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Mobilize_Value_Option() { return FS_Mobilize_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Immobilize_Value_Option() { return FS_Immobilize_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Sneak_Value_Option() { return FS_Sneak_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Unsneak_Value_Option() { return FS_Unsneak_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Saddle_Value_Option() { return FS_Saddle_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Unsaddle_Value_Option() { return FS_Unsaddle_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Resurrect_Value_Option() { return FS_Resurrect_Value_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Summon_All_Mods_Option() { return FS_Summon_All_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Summon_Mobile_Mods_Option() { return FS_Summon_Mobile_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Summon_Immobile_Mods_Option() { return FS_Summon_Immobile_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Settle_Mods_Option() { return FS_Settle_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Unsettle_Mods_Option() { return FS_Unsettle_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Mobilize_Mods_Option() { return FS_Mobilize_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Immobilize_Mods_Option() { return FS_Immobilize_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Sneak_Mods_Option() { return FS_Sneak_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Unsneak_Mods_Option() { return FS_Unsneak_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Saddle_Mods_Option() { return FS_Saddle_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Unsaddle_Mods_Option() { return FS_Unsaddle_Mods_Option_Variable()->Int(); }
    Int_t Hotkeys_t::FS_Resurrect_Mods_Option() { return FS_Resurrect_Mods_Option_Variable()->Int(); }

    void Hotkeys_t::On_Build_Page()
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        Keys_t* keys = Keys_t::Self();
        MCM::Main_t* mcm = Main();

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

        mcm->Title_Text(" Hotkeys ");

        mcm->Add_Header_Option(" Options ");
        mcm->Add_Empty_Option();
        {
            Set_Defaults_Option_Variable()->Int(mcm->Add_Text_Option(" Set All Defaults ", ""));
            Unset_All_Option_Variable()->Int(mcm->Add_Text_Option(" Unset All ", ""));
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        #define BUILD_HOTKEY(HOTKEY_, LABEL_)                                                   \
        M                                                                                       \
            HOTKEY_##_Value_Option_Variable()->Int(                                             \
                mcm->Add_Keymap_Option(LABEL_, vars->HOTKEY_##_Value(), MCM::Flags::UNMAP)      \
            );                                                                                  \
            HOTKEY_##_Mods_Option_Variable()->Int(                                              \
                mcm->Add_Text_Option(" Mods ", keys->Current_Mods_String(Keys_t::HOTKEY_()))    \
            );                                                                                  \
        W

        mcm->Add_Header_Option(" Global ");
        mcm->Add_Empty_Option();
        {
            BUILD_HOTKEY(G_Dialogue_Menu, " Dialogue Menu ");
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" NPC ");
        mcm->Add_Empty_Option();
        {
            BUILD_HOTKEY(N_Toggle_Member, " Toggle Member ");
            BUILD_HOTKEY(N_Toggle_Move, " Toggle Move ");
            BUILD_HOTKEY(N_Move_Nearer, " Move Nearer ");
            BUILD_HOTKEY(N_Move_Farther, " Move Farther ");
            BUILD_HOTKEY(N_Move_Rotate_Left, " Move Clockwise ");
            BUILD_HOTKEY(N_Move_Rotate_Right, " Move Counter-Clockwise ");
            BUILD_HOTKEY(N_Has_Base, " Has Base ");
            BUILD_HOTKEY(N_Count_Base, " Count Base ");
            BUILD_HOTKEY(N_Has_Head, " Has Head ");
            BUILD_HOTKEY(N_Count_Heads, " Count Heads ");
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Member ");
        mcm->Add_Empty_Option();
        {
            BUILD_HOTKEY(M_Toggle_Clone, " Toggle Clone ");
            BUILD_HOTKEY(M_Toggle_Settler, " Toggle Settler ");
            BUILD_HOTKEY(M_Toggle_Thrall, " Toggle Thrall ");
            BUILD_HOTKEY(M_Toggle_Immobile, " Toggle Immobile ");
            BUILD_HOTKEY(M_Toggle_Paralyzed, " Toggle Paralyzed ");
            BUILD_HOTKEY(M_Toggle_Follower, " Toggle Follower ");
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Follower ");
        mcm->Add_Empty_Option();
        {
            BUILD_HOTKEY(F_Toggle_Sneak, " Toggle Sneak ");
            BUILD_HOTKEY(F_Toggle_Saddler, " Toggle Saddler ");
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Members ");
        mcm->Add_Empty_Option();
        {
            BUILD_HOTKEY(MS_Toggle_Display, " Toggle Display ");
            BUILD_HOTKEY(MS_Display_Previous, " Display Previous ");
            BUILD_HOTKEY(MS_Display_Next, " Display Next ");
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        mcm->Add_Header_Option(" Followers ");
        mcm->Add_Empty_Option();
        {
            BUILD_HOTKEY(FS_Summon_All, " Summon All ");
            BUILD_HOTKEY(FS_Summon_Mobile, " Summon Mobile ");
            BUILD_HOTKEY(FS_Summon_Immobile, " Summon Immobile ");
            BUILD_HOTKEY(FS_Settle, " Settle ");
            BUILD_HOTKEY(FS_Unsettle, " Unsettle ");
            BUILD_HOTKEY(FS_Mobilize, " Mobilize ");
            BUILD_HOTKEY(FS_Immobilize, " Immobilize ");
            BUILD_HOTKEY(FS_Sneak, " Sneak ");
            BUILD_HOTKEY(FS_Unsneak, " Unsneak ");
            BUILD_HOTKEY(FS_Saddle, " Saddle ");
            BUILD_HOTKEY(FS_Unsaddle, " Unsaddle ");
            BUILD_HOTKEY(FS_Resurrect, " Resurrect ");
        }
        mcm->Add_Empty_Option();
        mcm->Add_Empty_Option();

        #undef BUILD_HOTKEY
    }

    void Hotkeys_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t* mcm = Main();

        if (option == Set_Defaults_Option()) {
            struct Callback : public Callback_t<Bool_t> {
                Hotkeys_t* self;
                UCallback_t* user_callback;
                Callback(Hotkeys_t* self, UCallback_t* user_callback) :
                    self(self), user_callback(user_callback)
                {
                }
                void operator()(Bool_t result)
                {
                    if (result) {
                        self->Reset_Hotkeys();
                    }
                    MCM::Main_t::Self()->Return_Latent(user_callback);
                }
            };
            mcm->Show_Message("This will set all NPC Party hotkeys to their defaults. "
                              "You will need to confirm any conflicts. Continue?",
                              true, " Yes ", " No ", new Callback(this, user_callback));
        } else if (option == Unset_All_Option()) {
            struct Callback : public Callback_t<Bool_t> {
                Hotkeys_t* self;
                UCallback_t* user_callback;
                Callback(Hotkeys_t* self, UCallback_t* user_callback) :
                    self(self), user_callback(user_callback)
                {
                }
                void operator()(Bool_t result)
                {
                    if (result) {
                        self->Unset_Hotkeys();
                    }
                    MCM::Main_t::Self()->Return_Latent(user_callback);
                }
            };
            mcm->Show_Message("This will unset all NPC Party hotkeys. Continue?",
                              true, " Yes ", " No ", new Callback(this, user_callback));
        } else {
            String_t hotkey = Mods_Option_To_Hotkey(option);
            if (hotkey && hotkey.data && hotkey.data[0]) {
                struct Callback : public Callback_t<Vector_t<Int_t>> {
                    Hotkeys_t* self;
                    Int_t option;
                    String_t hotkey;
                    UCallback_t* user_callback;
                    Callback(Hotkeys_t* self, Int_t option, String_t hotkey, UCallback_t* user_callback) :
                        self(self), option(option), hotkey(hotkey), user_callback(user_callback)
                    {
                    }
                    void operator()(Vector_t<Int_t> mods)
                    {
                        if (mods.size() > 0) {
                            Int_t value = Keys_t::Self()->Current_Value(hotkey);
                            struct Callback : public Callback_t<Hotkeys_t*, Bool_t> {
                                Int_t option;
                                Vector_t<Int_t> mods;
                                UCallback_t* user_callback;
                                Callback(Int_t option, Vector_t<Int_t>mods, UCallback_t* user_callback) :
                                    option(option), mods(mods), user_callback(user_callback)
                                {
                                }
                                void operator()(Hotkeys_t* self, Bool_t can_set_hotkey)
                                {
                                    if (can_set_hotkey) {
                                        self->Change_Hotkey_Mods(option, mods[0], mods[1], mods[2], true);
                                        MCM::Main_t::Self()->Return_Latent(user_callback);
                                    } else {
                                        MCM::Main_t::Self()->Return_Latent(user_callback);
                                    }
                                }
                            };
                            self->Can_Change_Hotkey(hotkey, value, mods[0], mods[1], mods[2], new Callback(option, mods, user_callback));
                        } else {
                            MCM::Main_t::Self()->Return_Latent(user_callback);
                        }
                    }
                };
                Read_Pressed_Mods(hotkey, new Callback(this, option, hotkey, user_callback));
            } else {
                mcm->Return_Latent(user_callback);
            }
        }
    }

    void Hotkeys_t::On_Option_Menu_Open(Int_t option)
    {

    }

    void Hotkeys_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {

    }

    void Hotkeys_t::On_Option_Slider_Open(Int_t option)
    {

    }

    void Hotkeys_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {

    }

    void Hotkeys_t::On_Option_Input_Accept(Int_t option, String_t value)
    {

    }

    void Hotkeys_t::On_Option_Keymap_Change(Int_t option,
                                            Int_t key_code,
                                            String_t conflict,
                                            String_t conflict_mod,
                                            Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        String_t hotkey = Value_Option_To_Hotkey(option);
        if (hotkey && hotkey.data && hotkey.data[0]) {
            if (key_code != Keys_t::Self()->Current_Value(hotkey)) {
                if (!conflict || !conflict.data) {
                    conflict = "";
                }
                if (!conflict_mod || !conflict_mod.data) {
                    conflict_mod = "";
                }
                if (key_code > -1 && conflict.data[0] && !String2::Is_Same_Caseless(conflict_mod, MCM::Main_t::MOD_NAME)) {
                    std::string str = std::string("This conflicts with '") + conflict.data + "'";
                    if (conflict_mod.data[0]) {
                        str += std::string(" in the mod '") + conflict_mod.data + "'.";
                    } else {
                        str += " in vanilla Skyrim.";
                    }
                    str += " Set key anyway?";
                    struct Callback : public Callback_t<Bool_t> {
                        Hotkeys_t* self;
                        Int_t option;
                        Int_t key_code;
                        String_t hotkey;
                        UCallback_t* user_callback;
                        Callback(Hotkeys_t* self, Int_t option, Int_t key_code, String_t hotkey, UCallback_t* user_callback) :
                            self(self), option(option), key_code(key_code), hotkey(hotkey), user_callback(user_callback)
                        {
                        }
                        void operator()(Bool_t can_set)
                        {
                            if (can_set) {
                                Vector_t<Int_t> mods = Keys_t::Self()->Current_Mods(hotkey);
                                struct Callback : public Callback_t<Hotkeys_t*, Bool_t> {
                                    Int_t option;
                                    Int_t key_code;
                                    UCallback_t* user_callback;
                                    Callback(Int_t option, Int_t key_code, UCallback_t* user_callback) :
                                        option(option), key_code(key_code), user_callback(user_callback)
                                    {
                                    }
                                    void operator()(Hotkeys_t* self, Bool_t can_set)
                                    {
                                        if (can_set) {
                                            self->Change_Hotkey_Value(option, key_code);
                                            MCM::Main_t::Self()->Return_Latent(user_callback);
                                        } else {
                                            MCM::Main_t::Self()->Return_Latent(user_callback);
                                        }
                                    }
                                };
                                self->Can_Change_Hotkey(hotkey, key_code, mods[0], mods[1], mods[2],
                                                        new Callback(option, key_code, user_callback));
                            } else {
                                MCM::Main_t::Self()->Return_Latent(user_callback);
                            }
                        }
                    };
                    MCM::Main_t::Self()->Show_Message(str.c_str(), true, " Yes ", " No ",
                                                      new Callback(this, option, key_code, hotkey, user_callback));
                } else {
                    Vector_t<Int_t> mods = Keys_t::Self()->Current_Mods(hotkey);
                    struct Callback : public Callback_t<Hotkeys_t*, Bool_t> {
                        Int_t option;
                        Int_t key_code;
                        UCallback_t* user_callback;
                        Callback(Int_t option, Int_t key_code, UCallback_t* user_callback) :
                            option(option), key_code(key_code), user_callback(user_callback)
                        {
                        }
                        void operator()(Hotkeys_t* self, Bool_t can_set)
                        {
                            if (can_set) {
                                self->Change_Hotkey_Value(option, key_code);
                                MCM::Main_t::Self()->Return_Latent(user_callback);
                            } else {
                                MCM::Main_t::Self()->Return_Latent(user_callback);
                            }
                        }
                    };
                    Can_Change_Hotkey(hotkey, key_code, mods[0], mods[1], mods[2], new Callback(option, key_code, user_callback));
                }
            } else {
                MCM::Main_t::Self()->Return_Latent(user_callback);
            }
        } else {
            MCM::Main_t::Self()->Return_Latent(user_callback);
        }
    }

    void Hotkeys_t::On_Option_Default(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        if (option != Set_Defaults_Option_Variable()->Int() &&
            option != Unset_All_Option_Variable()->Int()) {
            String_t hotkey = Value_Option_To_Hotkey(option);
            if (hotkey && hotkey.data && hotkey.data[0]) {
                Keys_t* keys = Keys_t::Self();
                Int_t value = keys->Default_Value(hotkey);
                Vector_t<Int_t> mods = keys->Current_Mods(hotkey);
                struct Callback : public Callback_t<Hotkeys_t*, Bool_t> {
                    Int_t option;
                    Int_t value;
                    UCallback_t* user_callback;
                    Callback(Int_t option, Int_t value, UCallback_t* user_callback) :
                        option(option), value(value), user_callback(user_callback)
                    {
                    }
                    void operator()(Hotkeys_t* self, Bool_t can_set)
                    {
                        if (can_set) {
                            self->Change_Hotkey_Value(option, value);
                            MCM::Main_t::Self()->Return_Latent(user_callback);
                        } else {
                            MCM::Main_t::Self()->Return_Latent(user_callback);
                        }
                    }
                };
                Can_Change_Hotkey(hotkey, value, mods[0], mods[1], mods[2], new Callback(option, value, user_callback));
            } else {
                hotkey = Mods_Option_To_Hotkey(option);
                if (hotkey && hotkey.data && hotkey.data[0]) {
                    Keys_t* keys = Keys_t::Self();
                    Int_t value = keys->Current_Value(hotkey);
                    Vector_t<Int_t> mods = keys->Default_Mods(hotkey);
                    struct Callback : public Callback_t<Hotkeys_t*, Bool_t> {
                        Int_t option;
                        Vector_t<Int_t> mods;
                        UCallback_t* user_callback;
                        Callback(Int_t option, Vector_t<Int_t> mods, UCallback_t* user_callback) :
                            option(option), mods(mods), user_callback(user_callback)
                        {
                        }
                        void operator()(Hotkeys_t* self, Bool_t can_set)
                        {
                            if (can_set) {
                                self->Change_Hotkey_Mods(option, mods[0], mods[1], mods[2]);
                                MCM::Main_t::Self()->Return_Latent(user_callback);
                            } else {
                                MCM::Main_t::Self()->Return_Latent(user_callback);
                            }
                        }
                    };
                    Can_Change_Hotkey(hotkey, value, mods[0], mods[1], mods[2], new Callback(option, mods, user_callback));
                }
            }
        }
    }

    void Hotkeys_t::On_Option_Highlight(Int_t option)
    {
        constexpr const char* MODS_INFO =
            "Set a combination of modifier keys that must be pressed for this hotkey to work.";

        Main_t* mcm = Main();

        if (option == Set_Defaults_Option()) {
            mcm->Info_Text("Set all hotkeys to their defaults. Will also set modifiers.");
        } else if (option == Unset_All_Option()) {
            mcm->Info_Text("Unset all hotkeys so that they will no longer be usable. Unsets all modifier also.");

        } else if (option == G_Dialogue_Menu_Value_Option()) { // Global Values
            mcm->Info_Text("Opens the global dialogue menu, which you can use to make global commands.");

        } else if (option == N_Toggle_Member_Value_Option()) { // NPC Values
            mcm->Info_Text("Causes an npc to be membered or unmembered.");
        } else if (option == N_Toggle_Move_Value_Option()) {
            mcm->Info_Text("Toggles the act of moving an npc.");
        } else if (option == N_Move_Nearer_Value_Option()) {
            mcm->Info_Text("While moving an npc, this will make them come closer to you.");
        } else if (option == N_Move_Farther_Value_Option()) {
            mcm->Info_Text("While moving an npc, this will make them go farther away from you.");
        } else if (option == N_Move_Rotate_Left_Value_Option()) {
            mcm->Info_Text("While moving an npc, this will make them turn clockwise.");
        } else if (option == N_Move_Rotate_Right_Value_Option()) {
            mcm->Info_Text("While moving an npc, this will make them turn counter-clockwise.");
        } else if (option == N_Has_Base_Value_Option()) {
            mcm->Info_Text("Shows whether or not you have a member with the same base as this npc.");
        } else if (option == N_Count_Base_Value_Option()) {
            mcm->Info_Text("Shows how many members you have with the same base as this npc.");
        } else if (option == N_Has_Head_Value_Option()) {
            mcm->Info_Text("Shows whether or not you have a member with the same head and face.");
        } else if (option == N_Count_Heads_Value_Option()) {
            mcm->Info_Text("Show how many members you have with the same head and face.");

        } else if (option == M_Toggle_Clone_Value_Option()) { // Member Values
            mcm->Info_Text("Causes an npc to be cloned or uncloned. The npc will become a member if they are not already.");
        } else if (option == M_Toggle_Settler_Value_Option()) {
            mcm->Info_Text("Causes an npc to be settled or unsettled. The npc will become a member if they are not already.");
        } else if (option == M_Toggle_Thrall_Value_Option()) {
            mcm->Info_Text("Causes an npc to be enthralled or unthralled. The npc will become a member if they are not already.");
        } else if (option == M_Toggle_Immobile_Value_Option()) {
            mcm->Info_Text("Causes an npc to be immobile or mobile. The npc will become a member if they are not already.");
        } else if (option == M_Toggle_Paralyzed_Value_Option()) {
            mcm->Info_Text("Causes an npc to be paralyzed or unparalyzed. The npc will become a member if they are not already.");
        } else if (option == M_Toggle_Follower_Value_Option()) {
            mcm->Info_Text("Causes an npc to follow or unfollow. The npc will become a member if they are not already.");

        } else if (option == F_Toggle_Sneak_Value_Option()) { // Follower Values
            mcm->Info_Text("Causes an npc to sneak or unsneak. The npc will become a member and a follower if they are not already.");
        } else if (option == F_Toggle_Saddler_Value_Option()) {
            mcm->Info_Text("Causes an npc to saddle or unsaddle. The npc will become a member and a follower if they are not already.");

        } else if (option == MS_Toggle_Display_Value_Option()) { // Members Values
            mcm->Info_Text("Toggles a member display.");
        } else if (option == MS_Display_Previous_Value_Option()) {
            mcm->Info_Text("Will loop through the previous members on display.");
        } else if (option == MS_Display_Next_Value_Option()) {
            mcm->Info_Text("Will loop through the next members on display.");

        } else if (option == FS_Summon_All_Value_Option()) { // Followers Values
            mcm->Info_Text("Summons all followers before you.");
        } else if (option == FS_Summon_Mobile_Value_Option()) {
            mcm->Info_Text("Summons only mobilized followers before you.");
        } else if (option == FS_Summon_Immobile_Value_Option()) {
            mcm->Info_Text("Summons only immobilized followers before you.");
        } else if (option == FS_Settle_Value_Option()) {
            mcm->Info_Text("Causes all followers to settle where they are currently standing.");
        } else if (option == FS_Unsettle_Value_Option()) {
            mcm->Info_Text("Causes all followers to no longer be settlers.");
        } else if (option == FS_Immobilize_Value_Option()) {
            mcm->Info_Text("Causes all followers to become immobile.");
        } else if (option == FS_Mobilize_Value_Option()) {
            mcm->Info_Text("Causes all followers to become mobile.");
        } else if (option == FS_Sneak_Value_Option()) {
            mcm->Info_Text("Causes all followers to start sneaking.");
        } else if (option == FS_Unsneak_Value_Option()) {
            mcm->Info_Text("Causes all followers to stop sneaking.");
        } else if (option == FS_Saddle_Value_Option()) {
            mcm->Info_Text("Causes all followers to saddle their horses.");
        } else if (option == FS_Unsaddle_Value_Option()) {
            mcm->Info_Text("Causes all followers to unsaddle their horses.");
        } else if (option == FS_Resurrect_Value_Option()) {
            mcm->Info_Text("Causes all dead followers to resurrect.");

        } else if (option == G_Dialogue_Menu_Mods_Option()) { // Global Mods
            mcm->Info_Text(MODS_INFO);

        } else if (option == N_Toggle_Member_Mods_Option()) { // NPC Mods
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Toggle_Move_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Move_Nearer_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Move_Farther_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Move_Rotate_Left_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Move_Rotate_Right_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Has_Base_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Count_Base_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Has_Head_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == N_Count_Heads_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);

        } else if (option == M_Toggle_Clone_Mods_Option()) { // Member Mods
            mcm->Info_Text(MODS_INFO);
        } else if (option == M_Toggle_Settler_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == M_Toggle_Thrall_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == M_Toggle_Immobile_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == M_Toggle_Paralyzed_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == M_Toggle_Follower_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);

        } else if (option == F_Toggle_Sneak_Mods_Option()) { // Follower Mods
            mcm->Info_Text(MODS_INFO);
        } else if (option == F_Toggle_Saddler_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);

        } else if (option == MS_Toggle_Display_Mods_Option()) { // Members Mods
            mcm->Info_Text(MODS_INFO);
        } else if (option == MS_Display_Previous_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == MS_Display_Next_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);

        } else if (option == FS_Summon_All_Mods_Option()) { // Followers Mods
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Summon_Mobile_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Summon_Immobile_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Settle_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Unsettle_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Immobilize_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Mobilize_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Sneak_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Unsneak_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Saddle_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Unsaddle_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        } else if (option == FS_Resurrect_Mods_Option()) {
            mcm->Info_Text(MODS_INFO);
        }
    }

    void Hotkeys_t::Can_Change_Hotkey(String_t hotkey, Int_t value, Int_t mod_1, Int_t mod_2, Int_t mod_3,
                                      Callback_t<Hotkeys_t*, Bool_t>* user_callback)
    {
        using UCallback_t = Callback_t<Hotkeys_t*, Bool_t>;
        NPCP_ASSERT(user_callback);

        if (value > 0) {
            String_t npcp_conflict = Keys_t::Self()->Conflicting_Hotkey(hotkey, value, mod_1, mod_2, mod_3);
            if (npcp_conflict && npcp_conflict.data && npcp_conflict.data[0]) {
                struct Callback : public Callback_t<Bool_t> {
                    Hotkeys_t* self;
                    UCallback_t* user_callback;
                    Callback(Hotkeys_t* self, UCallback_t* user_callback) :
                        self(self), user_callback(user_callback)
                    {
                    }
                    void operator()(Bool_t do_set)
                    {
                        user_callback->operator()(self, do_set);
                        delete user_callback;
                    }
                };
                Main()->Show_Message((std::string("This conflicts with '") + npcp_conflict.data + "'. Set key anyway?").c_str(),
                                     true, " Yes ", " No ", new Callback(this, user_callback));
            } else {
                user_callback->operator()(this, true);
                delete user_callback;
            }
        } else {
            user_callback->operator()(this, true);
            delete user_callback;
        }
    }

    void Hotkeys_t::Change_Hotkey_Value(Int_t option, Int_t value, Bool_t do_render)
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();

        if (option == G_Dialogue_Menu_Value_Option()) { // Global
            vars->G_Dialogue_Menu_Value(value);

        } else if (option == N_Toggle_Member_Value_Option()) { // NPC
            vars->N_Toggle_Member_Value(value);
        } else if (option == N_Toggle_Move_Value_Option()) {
            vars->N_Toggle_Move_Value(value);
        } else if (option == N_Move_Nearer_Value_Option()) {
            vars->N_Move_Nearer_Value(value);
        } else if (option == N_Move_Farther_Value_Option()) {
            vars->N_Move_Farther_Value(value);
        } else if (option == N_Move_Rotate_Left_Value_Option()) {
            vars->N_Move_Rotate_Left_Value(value);
        } else if (option == N_Move_Rotate_Right_Value_Option()) {
            vars->N_Move_Rotate_Right_Value(value);
        } else if (option == N_Has_Base_Value_Option()) {
            vars->N_Has_Base_Value(value);
        } else if (option == N_Count_Base_Value_Option()) {
            vars->N_Count_Base_Value(value);
        } else if (option == N_Has_Head_Value_Option()) {
            vars->N_Has_Head_Value(value);
        } else if (option == N_Count_Heads_Value_Option()) {
            vars->N_Count_Heads_Value(value);

        } else if (option == M_Toggle_Clone_Value_Option()) { // Member
            vars->M_Toggle_Clone_Value(value);
        } else if (option == M_Toggle_Settler_Value_Option()) {
            vars->M_Toggle_Settler_Value(value);
        } else if (option == M_Toggle_Thrall_Value_Option()) {
            vars->M_Toggle_Thrall_Value(value);
        } else if (option == M_Toggle_Immobile_Value_Option()) {
            vars->M_Toggle_Immobile_Value(value);
        } else if (option == M_Toggle_Paralyzed_Value_Option()) {
            vars->M_Toggle_Paralyzed_Value(value);
        } else if (option == M_Toggle_Follower_Value_Option()) {
            vars->M_Toggle_Follower_Value(value);

        } else if (option == F_Toggle_Sneak_Value_Option()) { // Follower
            vars->F_Toggle_Sneak_Value(value);
        } else if (option == F_Toggle_Saddler_Value_Option()) {
            vars->F_Toggle_Saddler_Value(value);

        } else if (option == MS_Toggle_Display_Value_Option()) { // Members
            vars->MS_Toggle_Display_Value(value);
        } else if (option == MS_Display_Previous_Value_Option()) {
            vars->MS_Display_Previous_Value(value);
        } else if (option == MS_Display_Next_Value_Option()) {
            vars->MS_Display_Next_Value(value);

        } else if (option == FS_Summon_All_Value_Option()) { // Followers
            vars->FS_Summon_All_Value(value);
        } else if (option == FS_Summon_Mobile_Value_Option()) {
            vars->FS_Summon_Mobile_Value(value);
        } else if (option == FS_Summon_Immobile_Value_Option()) {
            vars->FS_Summon_Immobile_Value(value);
        } else if (option == FS_Settle_Value_Option()) {
            vars->FS_Settle_Value(value);
        } else if (option == FS_Unsettle_Value_Option()) {
            vars->FS_Unsettle_Value(value);
        } else if (option == FS_Immobilize_Value_Option()) {
            vars->FS_Immobilize_Value(value);
        } else if (option == FS_Mobilize_Value_Option()) {
            vars->FS_Mobilize_Value(value);
        } else if (option == FS_Sneak_Value_Option()) {
            vars->FS_Sneak_Value(value);
        } else if (option == FS_Unsneak_Value_Option()) {
            vars->FS_Unsneak_Value(value);
        } else if (option == FS_Saddle_Value_Option()) {
            vars->FS_Saddle_Value(value);
        } else if (option == FS_Unsaddle_Value_Option()) {
            vars->FS_Unsaddle_Value(value);
        } else if (option == FS_Resurrect_Value_Option()) {
            vars->FS_Resurrect_Value(value);

        } else {
            NPCP_ASSERT(false);
        }

        Main()->Keymap_Option_Value(option, value, do_render);

        Keys_t::Self()->Register();
    }

    void Hotkeys_t::Change_Hotkey_Mods(Int_t option, Int_t mod_1, Int_t mod_2, Int_t mod_3, Bool_t do_render)
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        Keys_t::Mods_t mods(mod_1, mod_2, mod_3);
        Vector_t<Int_t> vector = mods.Vector();

        if (option == G_Dialogue_Menu_Mods_Option()) { // Global
            vars->G_Dialogue_Menu_Mods(vector);

        } else if (option == N_Toggle_Member_Mods_Option()) { // NPC
            vars->N_Toggle_Member_Mods(vector);
        } else if (option == N_Toggle_Move_Mods_Option()) {
            vars->N_Toggle_Move_Mods(vector);
        } else if (option == N_Move_Nearer_Mods_Option()) {
            vars->N_Move_Nearer_Mods(vector);
        } else if (option == N_Move_Farther_Mods_Option()) {
            vars->N_Move_Farther_Mods(vector);
        } else if (option == N_Move_Rotate_Left_Mods_Option()) {
            vars->N_Move_Rotate_Left_Mods(vector);
        } else if (option == N_Move_Rotate_Right_Mods_Option()) {
            vars->N_Move_Rotate_Right_Mods(vector);
        } else if (option == N_Has_Base_Mods_Option()) {
            vars->N_Has_Base_Mods(vector);
        } else if (option == N_Count_Base_Mods_Option()) {
            vars->N_Count_Base_Mods(vector);
        } else if (option == N_Has_Head_Mods_Option()) {
            vars->N_Has_Head_Mods(vector);
        } else if (option == N_Count_Heads_Mods_Option()) {
            vars->N_Count_Heads_Mods(vector);

        } else if (option == M_Toggle_Clone_Mods_Option()) { // Member
            vars->M_Toggle_Clone_Mods(vector);
        } else if (option == M_Toggle_Settler_Mods_Option()) {
            vars->M_Toggle_Settler_Mods(vector);
        } else if (option == M_Toggle_Thrall_Mods_Option()) {
            vars->M_Toggle_Thrall_Mods(vector);
        } else if (option == M_Toggle_Immobile_Mods_Option()) {
            vars->M_Toggle_Immobile_Mods(vector);
        } else if (option == M_Toggle_Paralyzed_Mods_Option()) {
            vars->M_Toggle_Paralyzed_Mods(vector);
        } else if (option == M_Toggle_Follower_Mods_Option()) {
            vars->M_Toggle_Follower_Mods(vector);

        } else if (option == F_Toggle_Sneak_Mods_Option()) { // Follower
            vars->F_Toggle_Sneak_Mods(vector);
        } else if (option == F_Toggle_Saddler_Mods_Option()) {
            vars->F_Toggle_Saddler_Mods(vector);

        } else if (option == MS_Toggle_Display_Mods_Option()) { // Members
            vars->MS_Toggle_Display_Mods(vector);
        } else if (option == MS_Display_Previous_Mods_Option()) {
            vars->MS_Display_Previous_Mods(vector);
        } else if (option == MS_Display_Next_Mods_Option()) {
            vars->MS_Display_Next_Mods(vector);

        } else if (option == FS_Summon_All_Mods_Option()) { // Followers
            vars->FS_Summon_All_Mods(vector);
        } else if (option == FS_Summon_Mobile_Mods_Option()) {
            vars->FS_Summon_Mobile_Mods(vector);
        } else if (option == FS_Summon_Immobile_Mods_Option()) {
            vars->FS_Summon_Immobile_Mods(vector);
        } else if (option == FS_Settle_Mods_Option()) {
            vars->FS_Settle_Mods(vector);
        } else if (option == FS_Unsettle_Mods_Option()) {
            vars->FS_Unsettle_Mods(vector);
        } else if (option == FS_Immobilize_Mods_Option()) {
            vars->FS_Immobilize_Mods(vector);
        } else if (option == FS_Mobilize_Mods_Option()) {
            vars->FS_Mobilize_Mods(vector);
        } else if (option == FS_Sneak_Mods_Option()) {
            vars->FS_Sneak_Mods(vector);
        } else if (option == FS_Unsneak_Mods_Option()) {
            vars->FS_Unsneak_Mods(vector);
        } else if (option == FS_Saddle_Mods_Option()) {
            vars->FS_Saddle_Mods(vector);
        } else if (option == FS_Unsaddle_Mods_Option()) {
            vars->FS_Unsaddle_Mods(vector);
        } else if (option == FS_Resurrect_Mods_Option()) {
            vars->FS_Resurrect_Mods(vector);

        } else {
            NPCP_ASSERT(false);
        }

        Main()->Text_Option_Value(option, mods.String(), do_render);
    }

    void Hotkeys_t::Reset_Hotkeys()
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        Keys_t* keys = Keys_t::Self();
        Main_t* mcm = Main();

        #define RESET_HOTKEY(HOTKEY_)                           \
        M                                                       \
            String_t hotkey = Keys_t::HOTKEY_();                \
            vars->HOTKEY_##_Value(keys->Default_Value(hotkey)); \
            vars->HOTKEY_##_Mods(keys->Default_Mods(hotkey));   \
        W

        // Global
        RESET_HOTKEY(G_Dialogue_Menu);

        // NPC
        RESET_HOTKEY(N_Toggle_Member);
        RESET_HOTKEY(N_Toggle_Move);
        RESET_HOTKEY(N_Move_Farther);
        RESET_HOTKEY(N_Move_Nearer);
        RESET_HOTKEY(N_Move_Rotate_Left);
        RESET_HOTKEY(N_Move_Rotate_Right);
        RESET_HOTKEY(N_Has_Base);
        RESET_HOTKEY(N_Count_Base);
        RESET_HOTKEY(N_Has_Head);
        RESET_HOTKEY(N_Count_Heads);

        // Member
        RESET_HOTKEY(M_Toggle_Clone);
        RESET_HOTKEY(M_Toggle_Settler);
        RESET_HOTKEY(M_Toggle_Thrall);
        RESET_HOTKEY(M_Toggle_Immobile);
        RESET_HOTKEY(M_Toggle_Paralyzed);
        RESET_HOTKEY(M_Toggle_Follower);

        // Follower
        RESET_HOTKEY(F_Toggle_Sneak);
        RESET_HOTKEY(F_Toggle_Saddler);

        // Members
        RESET_HOTKEY(MS_Toggle_Display);
        RESET_HOTKEY(MS_Display_Previous);
        RESET_HOTKEY(MS_Display_Next);

        // Followers
        RESET_HOTKEY(FS_Summon_All);
        RESET_HOTKEY(FS_Summon_Mobile);
        RESET_HOTKEY(FS_Summon_Immobile);
        RESET_HOTKEY(FS_Settle);
        RESET_HOTKEY(FS_Unsettle);
        RESET_HOTKEY(FS_Mobilize);
        RESET_HOTKEY(FS_Immobilize);
        RESET_HOTKEY(FS_Sneak);
        RESET_HOTKEY(FS_Unsneak);
        RESET_HOTKEY(FS_Saddle);
        RESET_HOTKEY(FS_Unsaddle);
        RESET_HOTKEY(FS_Resurrect);

        #undef RESET_HOTKEY
        
        keys->Register();

        mcm->Reset_Page();
        mcm->Unlock();
    }

    void Hotkeys_t::Unset_Hotkeys()
    {
        Modules::Vars_t* vars = Modules::Vars_t::Self();
        Keys_t* keys = Keys_t::Self();
        Main_t* mcm = Main();

        #define UNSET_HOTKEY(HOTKEY_)                           \
        M                                                       \
            vars->HOTKEY_##_Value(Keys_t::KEY_INVALID);         \
            vars->HOTKEY_##_Mods(Keys_t::Mods_t().Vector());    \
        W

        // Global
        UNSET_HOTKEY(G_Dialogue_Menu);

        // NPC
        UNSET_HOTKEY(N_Toggle_Member);
        UNSET_HOTKEY(N_Toggle_Move);
        UNSET_HOTKEY(N_Move_Farther);
        UNSET_HOTKEY(N_Move_Nearer);
        UNSET_HOTKEY(N_Move_Rotate_Left);
        UNSET_HOTKEY(N_Move_Rotate_Right);
        UNSET_HOTKEY(N_Has_Base);
        UNSET_HOTKEY(N_Count_Base);
        UNSET_HOTKEY(N_Has_Head);
        UNSET_HOTKEY(N_Count_Heads);

        // Member
        UNSET_HOTKEY(M_Toggle_Clone);
        UNSET_HOTKEY(M_Toggle_Settler);
        UNSET_HOTKEY(M_Toggle_Thrall);
        UNSET_HOTKEY(M_Toggle_Immobile);
        UNSET_HOTKEY(M_Toggle_Paralyzed);
        UNSET_HOTKEY(M_Toggle_Follower);

        // Follower
        UNSET_HOTKEY(F_Toggle_Sneak);
        UNSET_HOTKEY(F_Toggle_Saddler);

        // Members
        UNSET_HOTKEY(MS_Toggle_Display);
        UNSET_HOTKEY(MS_Display_Previous);
        UNSET_HOTKEY(MS_Display_Next);

        // Followers
        UNSET_HOTKEY(FS_Summon_All);
        UNSET_HOTKEY(FS_Summon_Mobile);
        UNSET_HOTKEY(FS_Summon_Immobile);
        UNSET_HOTKEY(FS_Settle);
        UNSET_HOTKEY(FS_Unsettle);
        UNSET_HOTKEY(FS_Mobilize);
        UNSET_HOTKEY(FS_Immobilize);
        UNSET_HOTKEY(FS_Sneak);
        UNSET_HOTKEY(FS_Unsneak);
        UNSET_HOTKEY(FS_Saddle);
        UNSET_HOTKEY(FS_Unsaddle);
        UNSET_HOTKEY(FS_Resurrect);

        #undef UNSET_HOTKEY

        keys->Register();

        mcm->Reset_Page();
        mcm->Unlock();
    }

    String_t Hotkeys_t::Value_Option_To_Hotkey(Int_t value_option)
    {
        if (value_option == G_Dialogue_Menu_Value_Option()) { // Global
            return Keys_t::G_Dialogue_Menu();

        } else if (value_option == N_Toggle_Member_Value_Option()) { // NPC
            return Keys_t::N_Toggle_Member();
        } else if (value_option == N_Toggle_Move_Value_Option()) {
            return Keys_t::N_Toggle_Move();
        } else if (value_option == N_Move_Nearer_Value_Option()) {
            return Keys_t::N_Move_Nearer();
        } else if (value_option == N_Move_Farther_Value_Option()) {
            return Keys_t::N_Move_Farther();
        } else if (value_option == N_Move_Rotate_Left_Value_Option()) {
            return Keys_t::N_Move_Rotate_Left();
        } else if (value_option == N_Move_Rotate_Right_Value_Option()) {
            return Keys_t::N_Move_Rotate_Right();
        } else if (value_option == N_Has_Base_Value_Option()) {
            return Keys_t::N_Has_Base();
        } else if (value_option == N_Count_Base_Value_Option()) {
            return Keys_t::N_Count_Base();
        } else if (value_option == N_Has_Head_Value_Option()) {
            return Keys_t::N_Has_Head();
        } else if (value_option == N_Count_Heads_Value_Option()) {
            return Keys_t::N_Count_Heads();

        } else if (value_option == M_Toggle_Clone_Value_Option()) { // Member
            return Keys_t::M_Toggle_Clone();
        } else if (value_option == M_Toggle_Settler_Value_Option()) {
            return Keys_t::M_Toggle_Settler();
        } else if (value_option == M_Toggle_Thrall_Value_Option()) {
            return Keys_t::M_Toggle_Thrall();
        } else if (value_option == M_Toggle_Immobile_Value_Option()) {
            return Keys_t::M_Toggle_Immobile();
        } else if (value_option == M_Toggle_Paralyzed_Value_Option()) {
            return Keys_t::M_Toggle_Paralyzed();
        } else if (value_option == M_Toggle_Follower_Value_Option()) {
            return Keys_t::M_Toggle_Follower();

        } else if (value_option == F_Toggle_Sneak_Value_Option()) { // Follower
            return Keys_t::F_Toggle_Sneak();
        } else if (value_option == F_Toggle_Saddler_Value_Option()) {
            return Keys_t::F_Toggle_Saddler();

        } else if (value_option == MS_Toggle_Display_Value_Option()) { // Members
            return Keys_t::MS_Toggle_Display();
        } else if (value_option == MS_Display_Previous_Value_Option()) {
            return Keys_t::MS_Display_Previous();
        } else if (value_option == MS_Display_Next_Value_Option()) {
            return Keys_t::MS_Display_Next();

        } else if (value_option == FS_Summon_All_Value_Option()) { // Followers
            return Keys_t::FS_Summon_All();
        } else if (value_option == FS_Summon_Mobile_Value_Option()) {
            return Keys_t::FS_Summon_Mobile();
        } else if (value_option == FS_Summon_Immobile_Value_Option()) {
            return Keys_t::FS_Summon_Immobile();
        } else if (value_option == FS_Settle_Value_Option()) {
            return Keys_t::FS_Settle();
        } else if (value_option == FS_Unsettle_Value_Option()) {
            return Keys_t::FS_Unsettle();
        } else if (value_option == FS_Immobilize_Value_Option()) {
            return Keys_t::FS_Immobilize();
        } else if (value_option == FS_Mobilize_Value_Option()) {
            return Keys_t::FS_Mobilize();
        } else if (value_option == FS_Sneak_Value_Option()) {
            return Keys_t::FS_Sneak();
        } else if (value_option == FS_Unsneak_Value_Option()) {
            return Keys_t::FS_Unsneak();
        } else if (value_option == FS_Saddle_Value_Option()) {
            return Keys_t::FS_Saddle();
        } else if (value_option == FS_Unsaddle_Value_Option()) {
            return Keys_t::FS_Unsaddle();
        } else if (value_option == FS_Resurrect_Value_Option()) {
            return Keys_t::FS_Resurrect();

        } else {
            return "";
        }
    }

    String_t Hotkeys_t::Mods_Option_To_Hotkey(Int_t mods_option)
    {
        if (mods_option == G_Dialogue_Menu_Mods_Option()) { // Global
            return Keys_t::G_Dialogue_Menu();

        } else if (mods_option == N_Toggle_Member_Mods_Option()) { // NPC
            return Keys_t::N_Toggle_Member();
        } else if (mods_option == N_Toggle_Move_Mods_Option()) {
            return Keys_t::N_Toggle_Move();
        } else if (mods_option == N_Move_Nearer_Mods_Option()) {
            return Keys_t::N_Move_Nearer();
        } else if (mods_option == N_Move_Farther_Mods_Option()) {
            return Keys_t::N_Move_Farther();
        } else if (mods_option == N_Move_Rotate_Left_Mods_Option()) {
            return Keys_t::N_Move_Rotate_Left();
        } else if (mods_option == N_Move_Rotate_Right_Mods_Option()) {
            return Keys_t::N_Move_Rotate_Right();
        } else if (mods_option == N_Has_Base_Mods_Option()) {
            return Keys_t::N_Has_Base();
        } else if (mods_option == N_Count_Base_Mods_Option()) {
            return Keys_t::N_Count_Base();
        } else if (mods_option == N_Has_Head_Mods_Option()) {
            return Keys_t::N_Has_Head();
        } else if (mods_option == N_Count_Heads_Mods_Option()) {
            return Keys_t::N_Count_Heads();

        } else if (mods_option == M_Toggle_Clone_Mods_Option()) { // Member
            return Keys_t::M_Toggle_Clone();
        } else if (mods_option == M_Toggle_Settler_Mods_Option()) {
            return Keys_t::M_Toggle_Settler();
        } else if (mods_option == M_Toggle_Thrall_Mods_Option()) {
            return Keys_t::M_Toggle_Thrall();
        } else if (mods_option == M_Toggle_Immobile_Mods_Option()) {
            return Keys_t::M_Toggle_Immobile();
        } else if (mods_option == M_Toggle_Paralyzed_Mods_Option()) {
            return Keys_t::M_Toggle_Paralyzed();
        } else if (mods_option == M_Toggle_Follower_Mods_Option()) {
            return Keys_t::M_Toggle_Follower();

        } else if (mods_option == F_Toggle_Sneak_Mods_Option()) { // Follower
            return Keys_t::F_Toggle_Sneak();
        } else if (mods_option == F_Toggle_Saddler_Mods_Option()) {
            return Keys_t::F_Toggle_Saddler();

        } else if (mods_option == MS_Toggle_Display_Mods_Option()) { // Members
            return Keys_t::MS_Toggle_Display();
        } else if (mods_option == MS_Display_Previous_Mods_Option()) {
            return Keys_t::MS_Display_Previous();
        } else if (mods_option == MS_Display_Next_Mods_Option()) {
            return Keys_t::MS_Display_Next();

        } else if (mods_option == FS_Summon_All_Mods_Option()) { // Followers
            return Keys_t::FS_Summon_All();
        } else if (mods_option == FS_Summon_Mobile_Mods_Option()) {
            return Keys_t::FS_Summon_Mobile();
        } else if (mods_option == FS_Summon_Immobile_Mods_Option()) {
            return Keys_t::FS_Summon_Immobile();
        } else if (mods_option == FS_Settle_Mods_Option()) {
            return Keys_t::FS_Settle();
        } else if (mods_option == FS_Unsettle_Mods_Option()) {
            return Keys_t::FS_Unsettle();
        } else if (mods_option == FS_Immobilize_Mods_Option()) {
            return Keys_t::FS_Immobilize();
        } else if (mods_option == FS_Mobilize_Mods_Option()) {
            return Keys_t::FS_Mobilize();
        } else if (mods_option == FS_Sneak_Mods_Option()) {
            return Keys_t::FS_Sneak();
        } else if (mods_option == FS_Unsneak_Mods_Option()) {
            return Keys_t::FS_Unsneak();
        } else if (mods_option == FS_Saddle_Mods_Option()) {
            return Keys_t::FS_Saddle();
        } else if (mods_option == FS_Unsaddle_Mods_Option()) {
            return Keys_t::FS_Unsaddle();
        } else if (mods_option == FS_Resurrect_Mods_Option()) {
            return Keys_t::FS_Resurrect();

        } else {
            return "";
        }
    }

    void Hotkeys_t::Read_Pressed_Mods(String_t hotkey, Callback_t<Vector_t<Int_t>>* user_callback)
    {
        static DIHookControl& controls = DIHookControl::GetSingleton();

        using UCallback_t = Callback_t<Vector_t<Int_t>>;

        struct Callback : public Callback_t<Bool_t> {
            Hotkeys_t* self;
            UCallback_t* user_callback;
            Callback(Hotkeys_t* self, UCallback_t* user_callback) :
                self(self), user_callback(user_callback)
            {
            }
            void operator()(Bool_t do_set)
            {
                if (do_set) {
                    struct Callback : public Callback_t<Bool_t> {
                        Hotkeys_t* self;
                        UCallback_t* user_callback;
                        Callback(Hotkeys_t* self, UCallback_t* user_callback) :
                            self(self), user_callback(user_callback)
                        {
                        }
                        void operator()(Bool_t do_change)
                        {
                            if (do_change) {
                                Vector_t<Int_t> mods;
                                mods.reserve(3);

                                size_t key_count = controls.GetNumKeysPressed();
                                if (key_count > 0) {
                                    mods.push_back(controls.GetNthKeyPressed(0));
                                } else {
                                    mods.push_back(-1);
                                }
                                if (key_count > 1) {
                                    mods.push_back(controls.GetNthKeyPressed(1));
                                } else {
                                    mods.push_back(-1);
                                }
                                if (key_count > 2) {
                                    mods.push_back(controls.GetNthKeyPressed(2));
                                } else {
                                    mods.push_back(-1);
                                }

                                user_callback->operator()(mods);
                                delete user_callback;
                            } else {
                                Vector_t<Int_t> mods;
                                user_callback->operator()(mods);
                                delete user_callback;
                            }
                        }
                    };
                    Main()->Show_Message("Press and hold up to three keys and click enter. Cancel will leave the mods as they are.",
                                         true, " Accept ", " Cancel ", new Callback(self, user_callback));
                } else {
                    struct Callback : public Callback_t<Bool_t> {
                        Hotkeys_t* self;
                        UCallback_t* user_callback;
                        Callback(Hotkeys_t* self, UCallback_t* user_callback) :
                            self(self), user_callback(user_callback)
                        {
                        }
                        void operator()(Bool_t do_clear)
                        {
                            if (do_clear) {
                                Vector_t<Int_t> mods;
                                mods.reserve(3);
                                mods.push_back(-1);
                                mods.push_back(-1);
                                mods.push_back(-1);
                                user_callback->operator()(mods);
                                delete user_callback;
                            } else {
                                Vector_t<Int_t> mods;
                                user_callback->operator()(mods);
                                delete user_callback;
                            }
                        }
                    };
                    Main()->Show_Message("Are you sure you want to clear mods?",
                                         true, " Yes ", " No ", new Callback(self, user_callback));
                }
            }
        };
        Main()->Show_Message("Set or Unset mods?",
                             true, " Set ", " Unset ", new Callback(this, user_callback));
    }

    void Hotkeys_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Hotkeys_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
