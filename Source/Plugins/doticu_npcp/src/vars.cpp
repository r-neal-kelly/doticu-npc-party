/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64_common/Relocation.h"

#include "consts.h"
#include "game.h"
#include "papyrus.h"
#include "utils.h"
#include "vars.h"

#include "papyrus.inl"

using namespace doticu_npcp::Papyrus;

namespace doticu_npcp { namespace Vars {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_vars");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Vars_t* Self()
    {
        return static_cast<Vars_t*>(Consts::Vars_Quest());
    }

    Object_t* Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Property(String_t property_name)
    {
        return Object()->Property(property_name);
    }

    Variable_t* NPCP_Major_Variable() { DEFINE_VARIABLE("p_version_major"); }
    Variable_t* NPCP_Minor_Variable() { DEFINE_VARIABLE("p_version_minor"); }
    Variable_t* NPCP_Patch_Variable() { DEFINE_VARIABLE("p_version_patch"); }

    Int_t NPCP_Major() { return NPCP_Major_Variable()->Int(); }
    Int_t NPCP_Minor() { return NPCP_Minor_Variable()->Int(); }
    Int_t NPCP_Patch() { return NPCP_Patch_Variable()->Int(); }

    void NPCP_Major(Int_t npcp_major) { NPCP_Major_Variable()->Int(npcp_major); }
    void NPCP_Minor(Int_t npcp_minor) { NPCP_Minor_Variable()->Int(npcp_minor); }
    void NPCP_Patch(Int_t npcp_patch) { NPCP_Patch_Variable()->Int(npcp_patch); }

    Bool_t Is_Leveling_Enabled() { return Consts::Is_Leveling_Enabled()->value > 0.0f; }
    void Enable_Leveling() { Consts::Is_Leveling_Enabled()->value = 1.0f; }
    void Disable_Leveling() { Consts::Is_Leveling_Enabled()->value = 0.0f; }

    // Global Keys
    Variable_t* G_Dialogue_Menu_Value_Property() { DEFINE_PROPERTY("key_g_dialogue_menu"); }

    Variable_t* G_Dialogue_Menu_Mods_Property() { DEFINE_PROPERTY("key_g_dialogue_menu_mods"); }

    Int_t G_Dialogue_Menu_Value() { return G_Dialogue_Menu_Value_Property()->Int(); }

    Vector_t<Int_t> G_Dialogue_Menu_Mods() { return G_Dialogue_Menu_Mods_Property()->Vector<Int_t>(); }

    void G_Dialogue_Menu_Value(Int_t value) { G_Dialogue_Menu_Value_Property()->Int(value); }

    void G_Dialogue_Menu_Mods(Vector_t<Int_t> value) { G_Dialogue_Menu_Mods_Property()->Pack(value); }

    // NPC Keys
    Variable_t* N_Toggle_Member_Value_Property() { DEFINE_PROPERTY("key_n_toggle_member"); }
    Variable_t* N_Toggle_Move_Value_Property() { DEFINE_PROPERTY("key_n_toggle_move"); }
    Variable_t* N_Move_Nearer_Value_Property() { DEFINE_PROPERTY("key_n_move_nearer"); }
    Variable_t* N_Move_Farther_Value_Property() { DEFINE_PROPERTY("key_n_move_farther"); }
    Variable_t* N_Move_Rotate_Left_Value_Property() { DEFINE_PROPERTY("key_n_move_rotate_left"); }
    Variable_t* N_Move_Rotate_Right_Value_Property() { DEFINE_PROPERTY("key_n_move_rotate_right"); }
    Variable_t* N_Has_Base_Value_Property() { DEFINE_PROPERTY("key_n_has_base"); }
    Variable_t* N_Count_Base_Value_Property() { DEFINE_PROPERTY("key_n_count_base"); }
    Variable_t* N_Has_Head_Value_Property() { DEFINE_PROPERTY("key_n_has_head"); }
    Variable_t* N_Count_Heads_Value_Property() { DEFINE_PROPERTY("key_n_count_heads"); }

    Variable_t* N_Toggle_Member_Mods_Property() { DEFINE_PROPERTY("key_n_toggle_member_mods"); }
    Variable_t* N_Toggle_Move_Mods_Property() { DEFINE_PROPERTY("key_n_toggle_move_mods"); }
    Variable_t* N_Move_Nearer_Mods_Property() { DEFINE_PROPERTY("key_n_move_nearer_mods"); }
    Variable_t* N_Move_Farther_Mods_Property() { DEFINE_PROPERTY("key_n_move_farther_mods"); }
    Variable_t* N_Move_Rotate_Left_Mods_Property() { DEFINE_PROPERTY("key_n_move_rotate_left_mods"); }
    Variable_t* N_Move_Rotate_Right_Mods_Property() { DEFINE_PROPERTY("key_n_move_rotate_right_mods"); }
    Variable_t* N_Has_Base_Mods_Property() { DEFINE_PROPERTY("key_n_has_base_mods"); }
    Variable_t* N_Count_Base_Mods_Property() { DEFINE_PROPERTY("key_n_count_base_mods"); }
    Variable_t* N_Has_Head_Mods_Property() { DEFINE_PROPERTY("key_n_has_head_mods"); }
    Variable_t* N_Count_Heads_Mods_Property() { DEFINE_PROPERTY("key_n_count_heads_mods"); }

    Int_t N_Toggle_Member_Value() { return N_Toggle_Member_Value_Property()->Int(); }
    Int_t N_Toggle_Move_Value() { return N_Toggle_Move_Value_Property()->Int(); }
    Int_t N_Move_Nearer_Value() { return N_Move_Nearer_Value_Property()->Int(); }
    Int_t N_Move_Farther_Value() { return N_Move_Farther_Value_Property()->Int(); }
    Int_t N_Move_Rotate_Left_Value() { return N_Move_Rotate_Left_Value_Property()->Int(); }
    Int_t N_Move_Rotate_Right_Value() { return N_Move_Rotate_Right_Value_Property()->Int(); }
    Int_t N_Has_Base_Value() { return N_Has_Base_Value_Property()->Int(); }
    Int_t N_Count_Base_Value() { return N_Count_Base_Value_Property()->Int(); }
    Int_t N_Has_Head_Value() { return N_Has_Head_Value_Property()->Int(); }
    Int_t N_Count_Heads_Value() { return N_Count_Heads_Value_Property()->Int(); }

    Vector_t<Int_t> N_Toggle_Member_Mods() { return N_Toggle_Member_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Toggle_Move_Mods() { return N_Toggle_Move_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Move_Nearer_Mods() { return N_Move_Nearer_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Move_Farther_Mods() { return N_Move_Farther_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Move_Rotate_Left_Mods() { return N_Move_Rotate_Left_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Move_Rotate_Right_Mods() { return N_Move_Rotate_Right_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Has_Base_Mods() { return N_Has_Base_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Count_Base_Mods() { return N_Count_Base_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Has_Head_Mods() { return N_Has_Head_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> N_Count_Heads_Mods() { return N_Count_Heads_Mods_Property()->Vector<Int_t>(); }

    void N_Toggle_Member_Value(Int_t value) { N_Toggle_Member_Value_Property()->Int(value); }
    void N_Toggle_Move_Value(Int_t value) { N_Toggle_Move_Value_Property()->Int(value); }
    void N_Move_Nearer_Value(Int_t value) { N_Move_Nearer_Value_Property()->Int(value); }
    void N_Move_Farther_Value(Int_t value) { N_Move_Farther_Value_Property()->Int(value); }
    void N_Move_Rotate_Left_Value(Int_t value) { N_Move_Rotate_Left_Value_Property()->Int(value); }
    void N_Move_Rotate_Right_Value(Int_t value) { N_Move_Rotate_Right_Value_Property()->Int(value); }
    void N_Has_Base_Value(Int_t value) { N_Has_Base_Value_Property()->Int(value); }
    void N_Count_Base_Value(Int_t value) { N_Count_Base_Value_Property()->Int(value); }
    void N_Has_Head_Value(Int_t value) { N_Has_Head_Value_Property()->Int(value); }
    void N_Count_Heads_Value(Int_t value) { N_Count_Heads_Value_Property()->Int(value); }

    void N_Toggle_Member_Mods(Vector_t<Int_t> value) { N_Toggle_Member_Mods_Property()->Pack(value); }
    void N_Toggle_Move_Mods(Vector_t<Int_t> value) { N_Toggle_Move_Mods_Property()->Pack(value); }
    void N_Move_Nearer_Mods(Vector_t<Int_t> value) { N_Move_Nearer_Mods_Property()->Pack(value); }
    void N_Move_Farther_Mods(Vector_t<Int_t> value) { N_Move_Farther_Mods_Property()->Pack(value); }
    void N_Move_Rotate_Left_Mods(Vector_t<Int_t> value) { N_Move_Rotate_Left_Mods_Property()->Pack(value); }
    void N_Move_Rotate_Right_Mods(Vector_t<Int_t> value) { N_Move_Rotate_Right_Mods_Property()->Pack(value); }
    void N_Has_Base_Mods(Vector_t<Int_t> value) { N_Has_Base_Mods_Property()->Pack(value); }
    void N_Count_Base_Mods(Vector_t<Int_t> value) { N_Count_Base_Mods_Property()->Pack(value); }
    void N_Has_Head_Mods(Vector_t<Int_t> value) { N_Has_Head_Mods_Property()->Pack(value); }
    void N_Count_Heads_Mods(Vector_t<Int_t> value) { N_Count_Heads_Mods_Property()->Pack(value); }

    // Member Keys
    Variable_t* M_Toggle_Clone_Value_Property() { DEFINE_PROPERTY("key_m_toggle_clone"); }
    Variable_t* M_Toggle_Settler_Value_Property() { DEFINE_PROPERTY("key_m_toggle_settler"); }
    Variable_t* M_Toggle_Thrall_Value_Property() { DEFINE_PROPERTY("key_m_toggle_thrall"); }
    Variable_t* M_Toggle_Immobile_Value_Property() { DEFINE_PROPERTY("key_m_toggle_immobile"); }
    Variable_t* M_Toggle_Paralyzed_Value_Property() { DEFINE_PROPERTY("key_m_toggle_paralyzed"); }
    Variable_t* M_Toggle_Follower_Value_Property() { DEFINE_PROPERTY("key_m_toggle_follower"); }

    Variable_t* M_Toggle_Clone_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_clone_mods"); }
    Variable_t* M_Toggle_Settler_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_settler_mods"); }
    Variable_t* M_Toggle_Thrall_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_thrall_mods"); }
    Variable_t* M_Toggle_Immobile_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_immobile_mods"); }
    Variable_t* M_Toggle_Paralyzed_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_paralyzed_mods"); }
    Variable_t* M_Toggle_Follower_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_follower_mods"); }

    Int_t M_Toggle_Clone_Value() { return M_Toggle_Clone_Value_Property()->Int(); }
    Int_t M_Toggle_Settler_Value() { return M_Toggle_Settler_Value_Property()->Int(); }
    Int_t M_Toggle_Thrall_Value() { return M_Toggle_Thrall_Value_Property()->Int(); }
    Int_t M_Toggle_Immobile_Value() { return M_Toggle_Immobile_Value_Property()->Int(); }
    Int_t M_Toggle_Paralyzed_Value() { return M_Toggle_Paralyzed_Value_Property()->Int(); }
    Int_t M_Toggle_Follower_Value() { return M_Toggle_Follower_Value_Property()->Int(); }

    Vector_t<Int_t> M_Toggle_Clone_Mods() { return M_Toggle_Clone_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> M_Toggle_Settler_Mods() { return M_Toggle_Settler_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> M_Toggle_Thrall_Mods() { return M_Toggle_Thrall_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> M_Toggle_Immobile_Mods() { return M_Toggle_Immobile_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> M_Toggle_Paralyzed_Mods() { return M_Toggle_Paralyzed_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> M_Toggle_Follower_Mods() { return M_Toggle_Follower_Mods_Property()->Vector<Int_t>(); }

    void M_Toggle_Clone_Value(Int_t value) { M_Toggle_Clone_Value_Property()->Int(value); }
    void M_Toggle_Settler_Value(Int_t value) { M_Toggle_Settler_Value_Property()->Int(value); }
    void M_Toggle_Thrall_Value(Int_t value) { M_Toggle_Thrall_Value_Property()->Int(value); }
    void M_Toggle_Immobile_Value(Int_t value) { M_Toggle_Immobile_Value_Property()->Int(value); }
    void M_Toggle_Paralyzed_Value(Int_t value) { M_Toggle_Paralyzed_Value_Property()->Int(value); }
    void M_Toggle_Follower_Value(Int_t value) { M_Toggle_Follower_Value_Property()->Int(value); }

    void M_Toggle_Clone_Mods(Vector_t<Int_t> value) { M_Toggle_Clone_Mods_Property()->Pack(value); }
    void M_Toggle_Settler_Mods(Vector_t<Int_t> value) { M_Toggle_Settler_Mods_Property()->Pack(value); }
    void M_Toggle_Thrall_Mods(Vector_t<Int_t> value) { M_Toggle_Thrall_Mods_Property()->Pack(value); }
    void M_Toggle_Immobile_Mods(Vector_t<Int_t> value) { M_Toggle_Immobile_Mods_Property()->Pack(value); }
    void M_Toggle_Paralyzed_Mods(Vector_t<Int_t> value) { M_Toggle_Paralyzed_Mods_Property()->Pack(value); }
    void M_Toggle_Follower_Mods(Vector_t<Int_t> value) { M_Toggle_Follower_Mods_Property()->Pack(value); }

    // Follower Keys
    Variable_t* F_Toggle_Sneak_Value_Property() { DEFINE_PROPERTY("key_f_toggle_sneak"); }
    Variable_t* F_Toggle_Saddler_Value_Property() { DEFINE_PROPERTY("key_f_toggle_saddler"); }

    Variable_t* F_Toggle_Sneak_Mods_Property() { DEFINE_PROPERTY("key_f_toggle_sneak_mods"); }
    Variable_t* F_Toggle_Saddler_Mods_Property() { DEFINE_PROPERTY("key_f_toggle_saddler_mods"); }

    Int_t F_Toggle_Sneak_Value() { return F_Toggle_Sneak_Value_Property()->Int(); }
    Int_t F_Toggle_Saddler_Value() { return F_Toggle_Saddler_Value_Property()->Int(); }

    Vector_t<Int_t> F_Toggle_Sneak_Mods() { return F_Toggle_Sneak_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> F_Toggle_Saddler_Mods() { return F_Toggle_Saddler_Mods_Property()->Vector<Int_t>(); }

    void F_Toggle_Sneak_Value(Int_t value) { F_Toggle_Sneak_Value_Property()->Int(value); }
    void F_Toggle_Saddler_Value(Int_t value) { F_Toggle_Saddler_Value_Property()->Int(value); }

    void F_Toggle_Sneak_Mods(Vector_t<Int_t> value) { F_Toggle_Sneak_Mods_Property()->Pack(value); }
    void F_Toggle_Saddler_Mods(Vector_t<Int_t> value) { F_Toggle_Saddler_Mods_Property()->Pack(value); }

    // Members Keys
    Variable_t* MS_Toggle_Display_Value_Property() { DEFINE_PROPERTY("key_ms_toggle_display"); }
    Variable_t* MS_Display_Previous_Value_Property() { DEFINE_PROPERTY("key_ms_display_previous"); }
    Variable_t* MS_Display_Next_Value_Property() { DEFINE_PROPERTY("key_ms_display_next"); }

    Variable_t* MS_Toggle_Display_Mods_Property() { DEFINE_PROPERTY("key_ms_toggle_display_mods"); }
    Variable_t* MS_Display_Previous_Mods_Property() { DEFINE_PROPERTY("key_ms_display_previous_mods"); }
    Variable_t* MS_Display_Next_Mods_Property() { DEFINE_PROPERTY("key_ms_display_next_mods"); }

    Int_t MS_Toggle_Display_Value() { return MS_Toggle_Display_Value_Property()->Int(); }
    Int_t MS_Display_Previous_Value() { return MS_Display_Previous_Value_Property()->Int(); }
    Int_t MS_Display_Next_Value() { return MS_Display_Next_Value_Property()->Int(); }

    Vector_t<Int_t> MS_Toggle_Display_Mods() { return MS_Toggle_Display_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> MS_Display_Previous_Mods() { return MS_Display_Previous_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> MS_Display_Next_Mods() { return MS_Display_Next_Mods_Property()->Vector<Int_t>(); }

    void MS_Toggle_Display_Value(Int_t value) { MS_Toggle_Display_Value_Property()->Int(value); }
    void MS_Display_Previous_Value(Int_t value) { MS_Display_Previous_Value_Property()->Int(value); }
    void MS_Display_Next_Value(Int_t value) { MS_Display_Next_Value_Property()->Int(value); }

    void MS_Toggle_Display_Mods(Vector_t<Int_t> value) { MS_Toggle_Display_Mods_Property()->Pack(value); }
    void MS_Display_Previous_Mods(Vector_t<Int_t> value) { MS_Display_Previous_Mods_Property()->Pack(value); }
    void MS_Display_Next_Mods(Vector_t<Int_t> value) { MS_Display_Next_Mods_Property()->Pack(value); }

    // Followers Keys
    Variable_t* FS_Summon_All_Value_Property() { DEFINE_PROPERTY("key_fs_summon_all"); }
    Variable_t* FS_Summon_Mobile_Value_Property() { DEFINE_PROPERTY("key_fs_summon_mobile"); }
    Variable_t* FS_Summon_Immobile_Value_Property() { DEFINE_PROPERTY("key_fs_summon_immobile"); }
    Variable_t* FS_Settle_Value_Property() { DEFINE_PROPERTY("key_fs_settle"); }
    Variable_t* FS_Unsettle_Value_Property() { DEFINE_PROPERTY("key_fs_unsettle"); }
    Variable_t* FS_Mobilize_Value_Property() { DEFINE_PROPERTY("key_fs_mobilize"); }
    Variable_t* FS_Immobilize_Value_Property() { DEFINE_PROPERTY("key_fs_immobilize"); }
    Variable_t* FS_Sneak_Value_Property() { DEFINE_PROPERTY("key_fs_sneak"); }
    Variable_t* FS_Unsneak_Value_Property() { DEFINE_PROPERTY("key_fs_unsneak"); }
    Variable_t* FS_Saddle_Value_Property() { DEFINE_PROPERTY("key_fs_saddle"); }
    Variable_t* FS_Unsaddle_Value_Property() { DEFINE_PROPERTY("key_fs_unsaddle"); }
    Variable_t* FS_Resurrect_Value_Property() { DEFINE_PROPERTY("key_fs_resurrect"); }

    Variable_t* FS_Summon_All_Mods_Property() { DEFINE_PROPERTY("key_fs_summon_all_mods"); }
    Variable_t* FS_Summon_Mobile_Mods_Property() { DEFINE_PROPERTY("key_fs_summon_mobile_mods"); }
    Variable_t* FS_Summon_Immobile_Mods_Property() { DEFINE_PROPERTY("key_fs_summon_immobile_mods"); }
    Variable_t* FS_Settle_Mods_Property() { DEFINE_PROPERTY("key_fs_settle_mods"); }
    Variable_t* FS_Unsettle_Mods_Property() { DEFINE_PROPERTY("key_fs_unsettle_mods"); }
    Variable_t* FS_Mobilize_Mods_Property() { DEFINE_PROPERTY("key_fs_mobilize_mods"); }
    Variable_t* FS_Immobilize_Mods_Property() { DEFINE_PROPERTY("key_fs_immobilize_mods"); }
    Variable_t* FS_Sneak_Mods_Property() { DEFINE_PROPERTY("key_fs_sneak_mods"); }
    Variable_t* FS_Unsneak_Mods_Property() { DEFINE_PROPERTY("key_fs_unsneak_mods"); }
    Variable_t* FS_Saddle_Mods_Property() { DEFINE_PROPERTY("key_fs_saddle_mods"); }
    Variable_t* FS_Unsaddle_Mods_Property() { DEFINE_PROPERTY("key_fs_unsaddle_mods"); }
    Variable_t* FS_Resurrect_Mods_Property() { DEFINE_PROPERTY("key_fs_resurrect_mods"); }

    Int_t FS_Summon_All_Value() { return FS_Summon_All_Value_Property()->Int(); }
    Int_t FS_Summon_Mobile_Value() { return FS_Summon_Mobile_Value_Property()->Int(); }
    Int_t FS_Summon_Immobile_Value() { return FS_Summon_Immobile_Value_Property()->Int(); }
    Int_t FS_Settle_Value() { return FS_Settle_Value_Property()->Int(); }
    Int_t FS_Unsettle_Value() { return FS_Unsettle_Value_Property()->Int(); }
    Int_t FS_Mobilize_Value() { return FS_Mobilize_Value_Property()->Int(); }
    Int_t FS_Immobilize_Value() { return FS_Immobilize_Value_Property()->Int(); }
    Int_t FS_Sneak_Value() { return FS_Sneak_Value_Property()->Int(); }
    Int_t FS_Unsneak_Value() { return FS_Unsneak_Value_Property()->Int(); }
    Int_t FS_Saddle_Value() { return FS_Saddle_Value_Property()->Int(); }
    Int_t FS_Unsaddle_Value() { return FS_Unsaddle_Value_Property()->Int(); }
    Int_t FS_Resurrect_Value() { return FS_Resurrect_Value_Property()->Int(); }

    Vector_t<Int_t> FS_Summon_All_Mods() { return FS_Summon_All_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Summon_Mobile_Mods() { return FS_Summon_Mobile_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Summon_Immobile_Mods() { return FS_Summon_Immobile_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Settle_Mods() { return FS_Settle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Unsettle_Mods() { return FS_Unsettle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Mobilize_Mods() { return FS_Mobilize_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Immobilize_Mods() { return FS_Immobilize_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Sneak_Mods() { return FS_Sneak_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Unsneak_Mods() { return FS_Unsneak_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Saddle_Mods() { return FS_Saddle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Unsaddle_Mods() { return FS_Unsaddle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> FS_Resurrect_Mods() { return FS_Resurrect_Mods_Property()->Vector<Int_t>(); }

    void FS_Summon_All_Value(Int_t value) { FS_Summon_All_Value_Property()->Int(value); }
    void FS_Summon_Mobile_Value(Int_t value) { FS_Summon_Mobile_Value_Property()->Int(value); }
    void FS_Summon_Immobile_Value(Int_t value) { FS_Summon_Immobile_Value_Property()->Int(value); }
    void FS_Settle_Value(Int_t value) { FS_Settle_Value_Property()->Int(value); }
    void FS_Unsettle_Value(Int_t value) { FS_Unsettle_Value_Property()->Int(value); }
    void FS_Mobilize_Value(Int_t value) { FS_Mobilize_Value_Property()->Int(value); }
    void FS_Immobilize_Value(Int_t value) { FS_Immobilize_Value_Property()->Int(value); }
    void FS_Sneak_Value(Int_t value) { FS_Sneak_Value_Property()->Int(value); }
    void FS_Unsneak_Value(Int_t value) { FS_Unsneak_Value_Property()->Int(value); }
    void FS_Saddle_Value(Int_t value) { FS_Saddle_Value_Property()->Int(value); }
    void FS_Unsaddle_Value(Int_t value) { FS_Unsaddle_Value_Property()->Int(value); }
    void FS_Resurrect_Value(Int_t value) { FS_Resurrect_Value_Property()->Int(value); }

    void FS_Summon_All_Mods(Vector_t<Int_t> value) { FS_Summon_All_Mods_Property()->Pack(value); }
    void FS_Summon_Mobile_Mods(Vector_t<Int_t> value) { FS_Summon_Mobile_Mods_Property()->Pack(value); }
    void FS_Summon_Immobile_Mods(Vector_t<Int_t> value) { FS_Summon_Immobile_Mods_Property()->Pack(value); }
    void FS_Settle_Mods(Vector_t<Int_t> value) { FS_Settle_Mods_Property()->Pack(value); }
    void FS_Unsettle_Mods(Vector_t<Int_t> value) { FS_Unsettle_Mods_Property()->Pack(value); }
    void FS_Mobilize_Mods(Vector_t<Int_t> value) { FS_Mobilize_Mods_Property()->Pack(value); }
    void FS_Immobilize_Mods(Vector_t<Int_t> value) { FS_Immobilize_Mods_Property()->Pack(value); }
    void FS_Sneak_Mods(Vector_t<Int_t> value) { FS_Sneak_Mods_Property()->Pack(value); }
    void FS_Unsneak_Mods(Vector_t<Int_t> value) { FS_Unsneak_Mods_Property()->Pack(value); }
    void FS_Saddle_Mods(Vector_t<Int_t> value) { FS_Saddle_Mods_Property()->Pack(value); }
    void FS_Unsaddle_Mods(Vector_t<Int_t> value) { FS_Unsaddle_Mods_Property()->Pack(value); }
    void FS_Resurrect_Mods(Vector_t<Int_t> value) { FS_Resurrect_Mods_Property()->Pack(value); }

    #define VAR(TYPE_, NAME_)                                   \
    M                                                           \
        static const String_t variable_name = String_t(NAME_);  \
        NPCP_ASSERT(variable_name);                             \
        Variable_t* variable = Variable(variable_name);         \
        NPCP_ASSERT(variable);                                  \
        return variable->TYPE_();                               \
    W

    #define BOOL_VAR(NAME_) VAR(Bool, NAME_)

    Bool_t Do_Force_Clone_Unique() { BOOL_VAR("p_force_clone_unique"); }
    Bool_t Do_Force_Clone_Generic() { BOOL_VAR("p_force_clone_generic"); }
    Bool_t Do_Force_Unclone_Unique() { BOOL_VAR("p_force_unclone_unique"); }
    Bool_t Do_Force_Unclone_Generic() { BOOL_VAR("p_force_unclone_generic"); }
    Bool_t Do_Fill_Outfit2s() { BOOL_VAR("p_fill_outfits"); }
    Bool_t Do_Auto_Outfit2s() { BOOL_VAR("p_auto_outfit"); }
    Bool_t Do_Auto_Immobile_Outfit2() { BOOL_VAR("p_auto_immobile_outfit"); }

    #undef BOOL_VAR

    #define INT_VAR(NAME_) VAR(Int, NAME_)

    Int_t Member_Limit() { INT_VAR("p_max_members"); }
    Int_t Display_Count() { INT_VAR("p_num_display"); }
    Int_t Clone_Outfit() { INT_VAR("p_clone_outfit"); }
    Int_t Default_Style() { INT_VAR("p_auto_style"); }
    Int_t Default_Vitality() { INT_VAR("p_auto_vitality"); }

    #undef INT_VAR

    #define STRING_VAR(NAME_) VAR(String, NAME_)

    String_t Members_Sort_Algorithm() { STRING_VAR("p_str_sort_members"); }
    String_t Followers_Sort_Algorithm() { STRING_VAR("p_str_sort_followers"); }

    #undef STRING_VAR

    #undef VAR

    // temp
    Bool_t Is_Leveling_Enabled(Vars_t* self) { return Is_Leveling_Enabled(); }
    void Enable_Leveling(Vars_t* self) { return Enable_Leveling(); }
    void Disable_Leveling(Vars_t* self) { return Disable_Leveling(); }

}}

namespace doticu_npcp { namespace Vars { namespace Exports {

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_vars", Vars_t,                \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Vars::METHOD_, __VA_ARGS__);      \
        W

        ADD_METHOD("Is_Leveling_Enabled", 0, Bool_t, Is_Leveling_Enabled);
        ADD_METHOD("Enable_Leveling", 0, void, Enable_Leveling);
        ADD_METHOD("Disable_Leveling", 0, void, Disable_Leveling);

        #undef ADD_METHOD

        return true;
    }

}}}
