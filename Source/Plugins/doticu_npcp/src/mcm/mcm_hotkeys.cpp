/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "keys.h"
#include "utils.h"
#include "vars.h"

#include "mcm/mcm_hotkeys.h"

#include "papyrus.inl"
#include "party.inl"

namespace doticu_npcp { namespace MCM {

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

    void Hotkeys_t::Build_Page()
    {
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
                mcm->Add_Keymap_Option(LABEL_, Vars::HOTKEY_##_Value(), MCM::Flags::UNMAP)      \
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

    void Hotkeys_t::Hotkey_Value(Int_t option, String_t hotkey, Int_t value, Bool_t do_register_keys)
    {
        if (option == G_Dialogue_Menu_Value_Option()) { // Global
            Vars::G_Dialogue_Menu_Value(value);

        } else if (option == N_Toggle_Member_Value_Option()) { // NPC
            Vars::N_Toggle_Member_Value(value);
        } else if (option == N_Toggle_Move_Value_Option()) {
            Vars::N_Toggle_Move_Value(value);
        } else if (option == N_Move_Nearer_Value_Option()) {
            Vars::N_Move_Nearer_Value(value);
        } else if (option == N_Move_Farther_Value_Option()) {
            Vars::N_Move_Farther_Value(value);
        } else if (option == N_Move_Rotate_Left_Value_Option()) {
            Vars::N_Move_Rotate_Left_Value(value);
        } else if (option == N_Move_Rotate_Right_Value_Option()) {
            Vars::N_Move_Rotate_Right_Value(value);
        } else if (option == N_Has_Base_Value_Option()) {
            Vars::N_Has_Base_Value(value);
        } else if (option == N_Count_Base_Value_Option()) {
            Vars::N_Count_Base_Value(value);
        } else if (option == N_Has_Head_Value_Option()) {
            Vars::N_Has_Head_Value(value);
        } else if (option == N_Count_Heads_Value_Option()) {
            Vars::N_Count_Heads_Value(value);

        } else if (option == M_Toggle_Clone_Value_Option()) { // Member
            Vars::M_Toggle_Clone_Value(value);
        } else if (option == M_Toggle_Settler_Value_Option()) {
            Vars::M_Toggle_Settler_Value(value);
        } else if (option == M_Toggle_Thrall_Value_Option()) {
            Vars::M_Toggle_Thrall_Value(value);
        } else if (option == M_Toggle_Immobile_Value_Option()) {
            Vars::M_Toggle_Immobile_Value(value);
        } else if (option == M_Toggle_Paralyzed_Value_Option()) {
            Vars::M_Toggle_Paralyzed_Value(value);
        } else if (option == M_Toggle_Follower_Value_Option()) {
            Vars::M_Toggle_Follower_Value(value);

        } else if (option == F_Toggle_Sneak_Value_Option()) { // Follower
            Vars::F_Toggle_Sneak_Value(value);
        } else if (option == F_Toggle_Saddler_Value_Option()) {
            Vars::F_Toggle_Saddler_Value(value);

        } else if (option == MS_Toggle_Display_Value_Option()) { // Members
            Vars::MS_Toggle_Display_Value(value);
        } else if (option == MS_Display_Previous_Value_Option()) {
            Vars::MS_Display_Previous_Value(value);
        } else if (option == MS_Display_Next_Value_Option()) {
            Vars::MS_Display_Next_Value(value);

        } else if (option == FS_Summon_All_Value_Option()) { // Followers
            Vars::FS_Summon_All_Value(value);
        } else if (option == FS_Summon_Mobile_Value_Option()) {
            Vars::FS_Summon_Mobile_Value(value);
        } else if (option == FS_Summon_Immobile_Value_Option()) {
            Vars::FS_Summon_Immobile_Value(value);
        } else if (option == FS_Settle_Value_Option()) {
            Vars::FS_Settle_Value(value);
        } else if (option == FS_Unsettle_Value_Option()) {
            Vars::FS_Unsettle_Value(value);
        } else if (option == FS_Immobilize_Value_Option()) {
            Vars::FS_Immobilize_Value(value);
        } else if (option == FS_Mobilize_Value_Option()) {
            Vars::FS_Mobilize_Value(value);
        } else if (option == FS_Sneak_Value_Option()) {
            Vars::FS_Sneak_Value(value);
        } else if (option == FS_Unsneak_Value_Option()) {
            Vars::FS_Unsneak_Value(value);
        } else if (option == FS_Saddle_Value_Option()) {
            Vars::FS_Saddle_Value(value);
        } else if (option == FS_Unsaddle_Value_Option()) {
            Vars::FS_Unsaddle_Value(value);
        } else if (option == FS_Resurrect_Value_Option()) {
            Vars::FS_Resurrect_Value(value);

        } else {
            NPCP_ASSERT(false);
        }

        Main()->Keymap_Option_Value(option, value, true); // maybe don't render, or pass a bool

        if (do_register_keys) {
            Virtual_Machine_t::Self()->Call_Method(Keys_t::Self(), Keys_t::Class_Name(), "Update_Keys");
        }
    }

    void Hotkeys_t::Register_Me(Registry_t* registry)
    {
        using namespace Utils;

        auto Build_Page = Forward<void, Hotkeys_t, &Hotkeys_t::Build_Page>();
        auto Hotkey_Value = Forward<void, Hotkeys_t, Int_t, String_t, Int_t, Bool_t, &Hotkeys_t::Hotkey_Value>();

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), MCM::Hotkeys_t,              \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("f_Build_Page", 0, void, Build_Page);
        ADD_METHOD("p_Set_Hotkey_Value", 4, void, Hotkey_Value, Int_t, String_t, Int_t, Bool_t);

        #undef ADD_METHOD
    }

}}
