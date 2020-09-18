/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "codes.h"
#include "consts.h"
#include "game.h"
#include "papyrus.inl"
#include "utils.h"
#include "vars.h"

#include "party/party_members.h"

namespace doticu_npcp { namespace Modules {

    String_t Vars_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_vars");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Vars_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Vars_t* Vars_t::Self()
    {
        return static_cast<Vars_t*>(Consts::Vars_Quest());
    }

    Object_t* Vars_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Vars_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Vars_t::Property(String_t property_name)
    {
        return Object()->Property(property_name);
    }

    Variable_t* Vars_t::NPCP_Major_Variable() { DEFINE_VARIABLE("p_version_major"); }
    Variable_t* Vars_t::NPCP_Minor_Variable() { DEFINE_VARIABLE("p_version_minor"); }
    Variable_t* Vars_t::NPCP_Patch_Variable() { DEFINE_VARIABLE("p_version_patch"); }

    Variable_t* Vars_t::Member_Limit_Variable() { DEFINE_VARIABLE("p_max_members"); }
    Variable_t* Vars_t::Member_Display_Limit_Variable() { DEFINE_VARIABLE("p_num_display"); }
    Variable_t* Vars_t::Default_Member_Style_Variable() { DEFINE_VARIABLE("p_auto_style"); }
    Variable_t* Vars_t::Default_Member_Vitality_Variable() { DEFINE_VARIABLE("p_auto_vitality"); }

    Variable_t* Vars_t::Clone_Outfit_Algorithm_Variable() { DEFINE_VARIABLE("p_clone_outfit"); }

    Variable_t* Vars_t::Do_Auto_Resurrect_Followers_Variable() { DEFINE_VARIABLE("p_auto_resurrect"); }

    Variable_t* Vars_t::Do_Auto_Change_Outfits_Variable() { DEFINE_VARIABLE("p_auto_outfit"); }
    Variable_t* Vars_t::Do_Auto_Change_Immobile_Outfit_Variable() { DEFINE_VARIABLE("p_auto_immobile_outfit"); }
    Variable_t* Vars_t::Do_Auto_Fill_Outfits_Variable() { DEFINE_VARIABLE("p_fill_outfits"); }

    Variable_t* Vars_t::Member_Sort_Algorithm_Variable() { DEFINE_VARIABLE("p_str_sort_members"); }
    Variable_t* Vars_t::Follower_Sort_Algorithm_Variable() { DEFINE_VARIABLE("p_str_sort_followers"); }

    Variable_t* Vars_t::G_Dialogue_Menu_Value_Property() { DEFINE_PROPERTY("key_g_dialogue_menu"); }
    Variable_t* Vars_t::G_Dialogue_Menu_Mods_Property() { DEFINE_PROPERTY("key_g_dialogue_menu_mods"); }

    Variable_t* Vars_t::N_Toggle_Member_Value_Property() { DEFINE_PROPERTY("key_n_toggle_member"); }
    Variable_t* Vars_t::N_Toggle_Move_Value_Property() { DEFINE_PROPERTY("key_n_toggle_move"); }
    Variable_t* Vars_t::N_Move_Nearer_Value_Property() { DEFINE_PROPERTY("key_n_move_nearer"); }
    Variable_t* Vars_t::N_Move_Farther_Value_Property() { DEFINE_PROPERTY("key_n_move_farther"); }
    Variable_t* Vars_t::N_Move_Rotate_Left_Value_Property() { DEFINE_PROPERTY("key_n_move_rotate_left"); }
    Variable_t* Vars_t::N_Move_Rotate_Right_Value_Property() { DEFINE_PROPERTY("key_n_move_rotate_right"); }
    Variable_t* Vars_t::N_Has_Base_Value_Property() { DEFINE_PROPERTY("key_n_has_base"); }
    Variable_t* Vars_t::N_Count_Base_Value_Property() { DEFINE_PROPERTY("key_n_count_base"); }
    Variable_t* Vars_t::N_Has_Head_Value_Property() { DEFINE_PROPERTY("key_n_has_head"); }
    Variable_t* Vars_t::N_Count_Heads_Value_Property() { DEFINE_PROPERTY("key_n_count_heads"); }
    Variable_t* Vars_t::N_Toggle_Member_Mods_Property() { DEFINE_PROPERTY("key_n_toggle_member_mods"); }
    Variable_t* Vars_t::N_Toggle_Move_Mods_Property() { DEFINE_PROPERTY("key_n_toggle_move_mods"); }
    Variable_t* Vars_t::N_Move_Nearer_Mods_Property() { DEFINE_PROPERTY("key_n_move_nearer_mods"); }
    Variable_t* Vars_t::N_Move_Farther_Mods_Property() { DEFINE_PROPERTY("key_n_move_farther_mods"); }
    Variable_t* Vars_t::N_Move_Rotate_Left_Mods_Property() { DEFINE_PROPERTY("key_n_move_rotate_left_mods"); }
    Variable_t* Vars_t::N_Move_Rotate_Right_Mods_Property() { DEFINE_PROPERTY("key_n_move_rotate_right_mods"); }
    Variable_t* Vars_t::N_Has_Base_Mods_Property() { DEFINE_PROPERTY("key_n_has_base_mods"); }
    Variable_t* Vars_t::N_Count_Base_Mods_Property() { DEFINE_PROPERTY("key_n_count_base_mods"); }
    Variable_t* Vars_t::N_Has_Head_Mods_Property() { DEFINE_PROPERTY("key_n_has_head_mods"); }
    Variable_t* Vars_t::N_Count_Heads_Mods_Property() { DEFINE_PROPERTY("key_n_count_heads_mods"); }

    Variable_t* Vars_t::M_Toggle_Clone_Value_Property() { DEFINE_PROPERTY("key_m_toggle_clone"); }
    Variable_t* Vars_t::M_Toggle_Settler_Value_Property() { DEFINE_PROPERTY("key_m_toggle_settler"); }
    Variable_t* Vars_t::M_Toggle_Thrall_Value_Property() { DEFINE_PROPERTY("key_m_toggle_thrall"); }
    Variable_t* Vars_t::M_Toggle_Immobile_Value_Property() { DEFINE_PROPERTY("key_m_toggle_immobile"); }
    Variable_t* Vars_t::M_Toggle_Paralyzed_Value_Property() { DEFINE_PROPERTY("key_m_toggle_paralyzed"); }
    Variable_t* Vars_t::M_Toggle_Follower_Value_Property() { DEFINE_PROPERTY("key_m_toggle_follower"); }
    Variable_t* Vars_t::M_Toggle_Clone_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_clone_mods"); }
    Variable_t* Vars_t::M_Toggle_Settler_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_settler_mods"); }
    Variable_t* Vars_t::M_Toggle_Thrall_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_thrall_mods"); }
    Variable_t* Vars_t::M_Toggle_Immobile_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_immobile_mods"); }
    Variable_t* Vars_t::M_Toggle_Paralyzed_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_paralyzed_mods"); }
    Variable_t* Vars_t::M_Toggle_Follower_Mods_Property() { DEFINE_PROPERTY("key_m_toggle_follower_mods"); }

    Variable_t* Vars_t::F_Toggle_Sneak_Value_Property() { DEFINE_PROPERTY("key_f_toggle_sneak"); }
    Variable_t* Vars_t::F_Toggle_Saddler_Value_Property() { DEFINE_PROPERTY("key_f_toggle_saddler"); }
    Variable_t* Vars_t::F_Toggle_Sneak_Mods_Property() { DEFINE_PROPERTY("key_f_toggle_sneak_mods"); }
    Variable_t* Vars_t::F_Toggle_Saddler_Mods_Property() { DEFINE_PROPERTY("key_f_toggle_saddler_mods"); }

    Variable_t* Vars_t::MS_Toggle_Display_Value_Property() { DEFINE_PROPERTY("key_ms_toggle_display"); }
    Variable_t* Vars_t::MS_Display_Previous_Value_Property() { DEFINE_PROPERTY("key_ms_display_previous"); }
    Variable_t* Vars_t::MS_Display_Next_Value_Property() { DEFINE_PROPERTY("key_ms_display_next"); }
    Variable_t* Vars_t::MS_Toggle_Display_Mods_Property() { DEFINE_PROPERTY("key_ms_toggle_display_mods"); }
    Variable_t* Vars_t::MS_Display_Previous_Mods_Property() { DEFINE_PROPERTY("key_ms_display_previous_mods"); }
    Variable_t* Vars_t::MS_Display_Next_Mods_Property() { DEFINE_PROPERTY("key_ms_display_next_mods"); }

    Variable_t* Vars_t::FS_Summon_All_Value_Property() { DEFINE_PROPERTY("key_fs_summon_all"); }
    Variable_t* Vars_t::FS_Summon_Mobile_Value_Property() { DEFINE_PROPERTY("key_fs_summon_mobile"); }
    Variable_t* Vars_t::FS_Summon_Immobile_Value_Property() { DEFINE_PROPERTY("key_fs_summon_immobile"); }
    Variable_t* Vars_t::FS_Settle_Value_Property() { DEFINE_PROPERTY("key_fs_settle"); }
    Variable_t* Vars_t::FS_Unsettle_Value_Property() { DEFINE_PROPERTY("key_fs_unsettle"); }
    Variable_t* Vars_t::FS_Mobilize_Value_Property() { DEFINE_PROPERTY("key_fs_mobilize"); }
    Variable_t* Vars_t::FS_Immobilize_Value_Property() { DEFINE_PROPERTY("key_fs_immobilize"); }
    Variable_t* Vars_t::FS_Sneak_Value_Property() { DEFINE_PROPERTY("key_fs_sneak"); }
    Variable_t* Vars_t::FS_Unsneak_Value_Property() { DEFINE_PROPERTY("key_fs_unsneak"); }
    Variable_t* Vars_t::FS_Saddle_Value_Property() { DEFINE_PROPERTY("key_fs_saddle"); }
    Variable_t* Vars_t::FS_Unsaddle_Value_Property() { DEFINE_PROPERTY("key_fs_unsaddle"); }
    Variable_t* Vars_t::FS_Resurrect_Value_Property() { DEFINE_PROPERTY("key_fs_resurrect"); }
    Variable_t* Vars_t::FS_Summon_All_Mods_Property() { DEFINE_PROPERTY("key_fs_summon_all_mods"); }
    Variable_t* Vars_t::FS_Summon_Mobile_Mods_Property() { DEFINE_PROPERTY("key_fs_summon_mobile_mods"); }
    Variable_t* Vars_t::FS_Summon_Immobile_Mods_Property() { DEFINE_PROPERTY("key_fs_summon_immobile_mods"); }
    Variable_t* Vars_t::FS_Settle_Mods_Property() { DEFINE_PROPERTY("key_fs_settle_mods"); }
    Variable_t* Vars_t::FS_Unsettle_Mods_Property() { DEFINE_PROPERTY("key_fs_unsettle_mods"); }
    Variable_t* Vars_t::FS_Mobilize_Mods_Property() { DEFINE_PROPERTY("key_fs_mobilize_mods"); }
    Variable_t* Vars_t::FS_Immobilize_Mods_Property() { DEFINE_PROPERTY("key_fs_immobilize_mods"); }
    Variable_t* Vars_t::FS_Sneak_Mods_Property() { DEFINE_PROPERTY("key_fs_sneak_mods"); }
    Variable_t* Vars_t::FS_Unsneak_Mods_Property() { DEFINE_PROPERTY("key_fs_unsneak_mods"); }
    Variable_t* Vars_t::FS_Saddle_Mods_Property() { DEFINE_PROPERTY("key_fs_saddle_mods"); }
    Variable_t* Vars_t::FS_Unsaddle_Mods_Property() { DEFINE_PROPERTY("key_fs_unsaddle_mods"); }
    Variable_t* Vars_t::FS_Resurrect_Mods_Property() { DEFINE_PROPERTY("key_fs_resurrect_mods"); }

    Int_t Vars_t::NPCP_Major() { return NPCP_Major_Variable()->Int(); }
    Int_t Vars_t::NPCP_Minor() { return NPCP_Minor_Variable()->Int(); }
    Int_t Vars_t::NPCP_Patch() { return NPCP_Patch_Variable()->Int(); }
    void Vars_t::NPCP_Major(Int_t npcp_major) { NPCP_Major_Variable()->Int(npcp_major); }
    void Vars_t::NPCP_Minor(Int_t npcp_minor) { NPCP_Minor_Variable()->Int(npcp_minor); }
    void Vars_t::NPCP_Patch(Int_t npcp_patch) { NPCP_Patch_Variable()->Int(npcp_patch); }

    Bool_t Vars_t::Allow_Dialogue_For_All() { return Consts::Allow_Dialogue_For_All_Global()->value > 0.0f; }
    Bool_t Vars_t::Allow_Chatter() { return Consts::Allow_Chatter_Global()->value > 0.0f; }
    void Vars_t::Allow_Dialogue_For_All(Bool_t value) { Consts::Allow_Dialogue_For_All_Global()->value = value ? 1.0f : 0.0f; }
    void Vars_t::Allow_Chatter(Bool_t value) { Consts::Allow_Chatter_Global()->value = value ? 1.0f : 0.0f; }

    Int_t Vars_t::Member_Limit() { return Member_Limit_Variable()->Int(); }
    Int_t Vars_t::Member_Display_Limit() { return Member_Display_Limit_Variable()->Int(); }
    Int_t Vars_t::Default_Member_Style() { return Default_Member_Style_Variable()->Int(); }
    Int_t Vars_t::Default_Member_Vitality() { return Default_Member_Vitality_Variable()->Int(); }
    void Vars_t::Member_Limit(Int_t value) { Member_Limit_Variable()->Int(value); }
    void Vars_t::Member_Display_Limit(Int_t value) { Member_Display_Limit_Variable()->Int(value); }
    void Vars_t::Default_Member_Style(Int_t value) { Default_Member_Style_Variable()->Int(value); }
    void Vars_t::Default_Member_Vitality(Int_t value) { Default_Member_Vitality_Variable()->Int(value); }

    Bool_t Vars_t::Force_Clone_Uniques() { return Consts::Force_Clone_Uniques_Global()->value > 0.0f; }
    Bool_t Vars_t::Force_Clone_Generics() { return Consts::Force_Clone_Generics_Global()->value > 0.0f; }
    Bool_t Vars_t::Force_Unclone_Uniques() { return Consts::Force_Unclone_Uniques_Global()->value > 0.0f; }
    Bool_t Vars_t::Force_Unclone_Generics() { return Consts::Force_Unclone_Generics_Global()->value > 0.0f; }
    Int_t Vars_t::Clone_Outfit_Algorithm() { return Clone_Outfit_Algorithm_Variable()->Int(); }
    void Vars_t::Force_Clone_Uniques(Bool_t value) { Consts::Force_Clone_Uniques_Global()->value = value ? 1.0f : 0.0f; }
    void Vars_t::Force_Clone_Generics(Bool_t value) { Consts::Force_Clone_Generics_Global()->value = value ? 1.0f : 0.0f; }
    void Vars_t::Force_Unclone_Uniques(Bool_t value) { Consts::Force_Unclone_Uniques_Global()->value = value ? 1.0f : 0.0f; }
    void Vars_t::Force_Unclone_Generics(Bool_t value) { Consts::Force_Unclone_Generics_Global()->value = value ? 1.0f : 0.0f; }
    void Vars_t::Clone_Outfit_Algorithm(Int_t value) { Clone_Outfit_Algorithm_Variable()->Int(value); }

    Bool_t Vars_t::Do_Auto_Resurrect_Followers() { return Do_Auto_Resurrect_Followers_Variable()->Bool(); }
    Bool_t Vars_t::Do_Level_Followers() { return Consts::Is_Leveling_Enabled_Global()->value > 0.0f; }
    void Vars_t::Do_Auto_Resurrect_Followers(Bool_t value) { Do_Auto_Resurrect_Followers_Variable()->Bool(value); }
    void Vars_t::Do_Level_Followers(Bool_t value) { Consts::Is_Leveling_Enabled_Global()->value = value ? 1.0f : 0.0f; }

    Bool_t Vars_t::Do_Auto_Change_Outfits() { return Do_Auto_Change_Outfits_Variable()->Bool(); }
    Bool_t Vars_t::Do_Auto_Change_Immobile_Outfit() { return Do_Auto_Change_Immobile_Outfit_Variable()->Bool(); }
    Bool_t Vars_t::Do_Auto_Fill_Outfits() { return Do_Auto_Fill_Outfits_Variable()->Bool(); }
    Int_t Vars_t::Fill_Outfit_Body_Chance() { return 100 - Consts::No_Body_Percent_Global()->value; }
    Int_t Vars_t::Fill_Outfit_Head_Chance() { return 100 - Consts::No_Head_Percent_Global()->value; }
    Int_t Vars_t::Fill_Outfit_Hands_Chance() { return 100 - Consts::No_Hands_Percent_Global()->value; }
    Int_t Vars_t::Fill_Outfit_Feet_Chance() { return 100 - Consts::No_Feet_Percent_Global()->value; }
    void Vars_t::Do_Auto_Change_Outfits(Bool_t value) { Do_Auto_Change_Outfits_Variable()->Bool(value); }
    void Vars_t::Do_Auto_Change_Immobile_Outfit(Bool_t value) { Do_Auto_Change_Immobile_Outfit_Variable()->Bool(value); }
    void Vars_t::Do_Auto_Fill_Outfits(Bool_t value) { Do_Auto_Fill_Outfits_Variable()->Bool(value); }
    void Vars_t::Fill_Outfit_Body_Chance(Int_t v) { Consts::No_Body_Percent_Global()->value = v < 0 ? 100 : v > 100 ? 0 : 100 - v; }
    void Vars_t::Fill_Outfit_Head_Chance(Int_t v) { Consts::No_Head_Percent_Global()->value = v < 0 ? 100 : v > 100 ? 0 : 100 - v; }
    void Vars_t::Fill_Outfit_Hands_Chance(Int_t v) { Consts::No_Hands_Percent_Global()->value = v < 0 ? 100 : v > 100 ? 0 : 100 - v; }
    void Vars_t::Fill_Outfit_Feet_Chance(Int_t v) { Consts::No_Feet_Percent_Global()->value = v < 0 ? 100 : v > 100 ? 0 : 100 - v; }

    String_t Vars_t::Member_Sort_Algorithm() { return Member_Sort_Algorithm_Variable()->String(); }
    String_t Vars_t::Follower_Sort_Algorithm() { return Follower_Sort_Algorithm_Variable()->String(); }
    void Vars_t::Member_Sort_Algorithm(String_t value) { Member_Sort_Algorithm_Variable()->String(value); }
    void Vars_t::Follower_Sort_Algorithm(String_t value) { Follower_Sort_Algorithm_Variable()->String(value); }

    Int_t Vars_t::G_Dialogue_Menu_Value() { return G_Dialogue_Menu_Value_Property()->Int(); }
    Vector_t<Int_t> Vars_t::G_Dialogue_Menu_Mods() { return G_Dialogue_Menu_Mods_Property()->Vector<Int_t>(); }
    void Vars_t::G_Dialogue_Menu_Value(Int_t value) { G_Dialogue_Menu_Value_Property()->Int(value); }
    void Vars_t::G_Dialogue_Menu_Mods(Vector_t<Int_t> value) { G_Dialogue_Menu_Mods_Property()->Pack(value); }

    Int_t Vars_t::N_Toggle_Member_Value() { return N_Toggle_Member_Value_Property()->Int(); }
    Int_t Vars_t::N_Toggle_Move_Value() { return N_Toggle_Move_Value_Property()->Int(); }
    Int_t Vars_t::N_Move_Nearer_Value() { return N_Move_Nearer_Value_Property()->Int(); }
    Int_t Vars_t::N_Move_Farther_Value() { return N_Move_Farther_Value_Property()->Int(); }
    Int_t Vars_t::N_Move_Rotate_Left_Value() { return N_Move_Rotate_Left_Value_Property()->Int(); }
    Int_t Vars_t::N_Move_Rotate_Right_Value() { return N_Move_Rotate_Right_Value_Property()->Int(); }
    Int_t Vars_t::N_Has_Base_Value() { return N_Has_Base_Value_Property()->Int(); }
    Int_t Vars_t::N_Count_Base_Value() { return N_Count_Base_Value_Property()->Int(); }
    Int_t Vars_t::N_Has_Head_Value() { return N_Has_Head_Value_Property()->Int(); }
    Int_t Vars_t::N_Count_Heads_Value() { return N_Count_Heads_Value_Property()->Int(); }
    Vector_t<Int_t> Vars_t::N_Toggle_Member_Mods() { return N_Toggle_Member_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Toggle_Move_Mods() { return N_Toggle_Move_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Move_Nearer_Mods() { return N_Move_Nearer_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Move_Farther_Mods() { return N_Move_Farther_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Move_Rotate_Left_Mods() { return N_Move_Rotate_Left_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Move_Rotate_Right_Mods() { return N_Move_Rotate_Right_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Has_Base_Mods() { return N_Has_Base_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Count_Base_Mods() { return N_Count_Base_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Has_Head_Mods() { return N_Has_Head_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::N_Count_Heads_Mods() { return N_Count_Heads_Mods_Property()->Vector<Int_t>(); }
    void Vars_t::N_Toggle_Member_Value(Int_t value) { N_Toggle_Member_Value_Property()->Int(value); }
    void Vars_t::N_Toggle_Move_Value(Int_t value) { N_Toggle_Move_Value_Property()->Int(value); }
    void Vars_t::N_Move_Nearer_Value(Int_t value) { N_Move_Nearer_Value_Property()->Int(value); }
    void Vars_t::N_Move_Farther_Value(Int_t value) { N_Move_Farther_Value_Property()->Int(value); }
    void Vars_t::N_Move_Rotate_Left_Value(Int_t value) { N_Move_Rotate_Left_Value_Property()->Int(value); }
    void Vars_t::N_Move_Rotate_Right_Value(Int_t value) { N_Move_Rotate_Right_Value_Property()->Int(value); }
    void Vars_t::N_Has_Base_Value(Int_t value) { N_Has_Base_Value_Property()->Int(value); }
    void Vars_t::N_Count_Base_Value(Int_t value) { N_Count_Base_Value_Property()->Int(value); }
    void Vars_t::N_Has_Head_Value(Int_t value) { N_Has_Head_Value_Property()->Int(value); }
    void Vars_t::N_Count_Heads_Value(Int_t value) { N_Count_Heads_Value_Property()->Int(value); }
    void Vars_t::N_Toggle_Member_Mods(Vector_t<Int_t> value) { N_Toggle_Member_Mods_Property()->Pack(value); }
    void Vars_t::N_Toggle_Move_Mods(Vector_t<Int_t> value) { N_Toggle_Move_Mods_Property()->Pack(value); }
    void Vars_t::N_Move_Nearer_Mods(Vector_t<Int_t> value) { N_Move_Nearer_Mods_Property()->Pack(value); }
    void Vars_t::N_Move_Farther_Mods(Vector_t<Int_t> value) { N_Move_Farther_Mods_Property()->Pack(value); }
    void Vars_t::N_Move_Rotate_Left_Mods(Vector_t<Int_t> value) { N_Move_Rotate_Left_Mods_Property()->Pack(value); }
    void Vars_t::N_Move_Rotate_Right_Mods(Vector_t<Int_t> value) { N_Move_Rotate_Right_Mods_Property()->Pack(value); }
    void Vars_t::N_Has_Base_Mods(Vector_t<Int_t> value) { N_Has_Base_Mods_Property()->Pack(value); }
    void Vars_t::N_Count_Base_Mods(Vector_t<Int_t> value) { N_Count_Base_Mods_Property()->Pack(value); }
    void Vars_t::N_Has_Head_Mods(Vector_t<Int_t> value) { N_Has_Head_Mods_Property()->Pack(value); }
    void Vars_t::N_Count_Heads_Mods(Vector_t<Int_t> value) { N_Count_Heads_Mods_Property()->Pack(value); }

    Int_t Vars_t::M_Toggle_Clone_Value() { return M_Toggle_Clone_Value_Property()->Int(); }
    Int_t Vars_t::M_Toggle_Settler_Value() { return M_Toggle_Settler_Value_Property()->Int(); }
    Int_t Vars_t::M_Toggle_Thrall_Value() { return M_Toggle_Thrall_Value_Property()->Int(); }
    Int_t Vars_t::M_Toggle_Immobile_Value() { return M_Toggle_Immobile_Value_Property()->Int(); }
    Int_t Vars_t::M_Toggle_Paralyzed_Value() { return M_Toggle_Paralyzed_Value_Property()->Int(); }
    Int_t Vars_t::M_Toggle_Follower_Value() { return M_Toggle_Follower_Value_Property()->Int(); }
    Vector_t<Int_t> Vars_t::M_Toggle_Clone_Mods() { return M_Toggle_Clone_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::M_Toggle_Settler_Mods() { return M_Toggle_Settler_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::M_Toggle_Thrall_Mods() { return M_Toggle_Thrall_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::M_Toggle_Immobile_Mods() { return M_Toggle_Immobile_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::M_Toggle_Paralyzed_Mods() { return M_Toggle_Paralyzed_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::M_Toggle_Follower_Mods() { return M_Toggle_Follower_Mods_Property()->Vector<Int_t>(); }
    void Vars_t::M_Toggle_Clone_Value(Int_t value) { M_Toggle_Clone_Value_Property()->Int(value); }
    void Vars_t::M_Toggle_Settler_Value(Int_t value) { M_Toggle_Settler_Value_Property()->Int(value); }
    void Vars_t::M_Toggle_Thrall_Value(Int_t value) { M_Toggle_Thrall_Value_Property()->Int(value); }
    void Vars_t::M_Toggle_Immobile_Value(Int_t value) { M_Toggle_Immobile_Value_Property()->Int(value); }
    void Vars_t::M_Toggle_Paralyzed_Value(Int_t value) { M_Toggle_Paralyzed_Value_Property()->Int(value); }
    void Vars_t::M_Toggle_Follower_Value(Int_t value) { M_Toggle_Follower_Value_Property()->Int(value); }
    void Vars_t::M_Toggle_Clone_Mods(Vector_t<Int_t> value) { M_Toggle_Clone_Mods_Property()->Pack(value); }
    void Vars_t::M_Toggle_Settler_Mods(Vector_t<Int_t> value) { M_Toggle_Settler_Mods_Property()->Pack(value); }
    void Vars_t::M_Toggle_Thrall_Mods(Vector_t<Int_t> value) { M_Toggle_Thrall_Mods_Property()->Pack(value); }
    void Vars_t::M_Toggle_Immobile_Mods(Vector_t<Int_t> value) { M_Toggle_Immobile_Mods_Property()->Pack(value); }
    void Vars_t::M_Toggle_Paralyzed_Mods(Vector_t<Int_t> value) { M_Toggle_Paralyzed_Mods_Property()->Pack(value); }
    void Vars_t::M_Toggle_Follower_Mods(Vector_t<Int_t> value) { M_Toggle_Follower_Mods_Property()->Pack(value); }

    Int_t Vars_t::F_Toggle_Sneak_Value() { return F_Toggle_Sneak_Value_Property()->Int(); }
    Int_t Vars_t::F_Toggle_Saddler_Value() { return F_Toggle_Saddler_Value_Property()->Int(); }
    Vector_t<Int_t> Vars_t::F_Toggle_Sneak_Mods() { return F_Toggle_Sneak_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::F_Toggle_Saddler_Mods() { return F_Toggle_Saddler_Mods_Property()->Vector<Int_t>(); }
    void Vars_t::F_Toggle_Sneak_Value(Int_t value) { F_Toggle_Sneak_Value_Property()->Int(value); }
    void Vars_t::F_Toggle_Saddler_Value(Int_t value) { F_Toggle_Saddler_Value_Property()->Int(value); }
    void Vars_t::F_Toggle_Sneak_Mods(Vector_t<Int_t> value) { F_Toggle_Sneak_Mods_Property()->Pack(value); }
    void Vars_t::F_Toggle_Saddler_Mods(Vector_t<Int_t> value) { F_Toggle_Saddler_Mods_Property()->Pack(value); }

    Int_t Vars_t::MS_Toggle_Display_Value() { return MS_Toggle_Display_Value_Property()->Int(); }
    Int_t Vars_t::MS_Display_Previous_Value() { return MS_Display_Previous_Value_Property()->Int(); }
    Int_t Vars_t::MS_Display_Next_Value() { return MS_Display_Next_Value_Property()->Int(); }
    Vector_t<Int_t> Vars_t::MS_Toggle_Display_Mods() { return MS_Toggle_Display_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::MS_Display_Previous_Mods() { return MS_Display_Previous_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::MS_Display_Next_Mods() { return MS_Display_Next_Mods_Property()->Vector<Int_t>(); }
    void Vars_t::MS_Toggle_Display_Value(Int_t value) { MS_Toggle_Display_Value_Property()->Int(value); }
    void Vars_t::MS_Display_Previous_Value(Int_t value) { MS_Display_Previous_Value_Property()->Int(value); }
    void Vars_t::MS_Display_Next_Value(Int_t value) { MS_Display_Next_Value_Property()->Int(value); }
    void Vars_t::MS_Toggle_Display_Mods(Vector_t<Int_t> value) { MS_Toggle_Display_Mods_Property()->Pack(value); }
    void Vars_t::MS_Display_Previous_Mods(Vector_t<Int_t> value) { MS_Display_Previous_Mods_Property()->Pack(value); }
    void Vars_t::MS_Display_Next_Mods(Vector_t<Int_t> value) { MS_Display_Next_Mods_Property()->Pack(value); }

    Int_t Vars_t::FS_Summon_All_Value() { return FS_Summon_All_Value_Property()->Int(); }
    Int_t Vars_t::FS_Summon_Mobile_Value() { return FS_Summon_Mobile_Value_Property()->Int(); }
    Int_t Vars_t::FS_Summon_Immobile_Value() { return FS_Summon_Immobile_Value_Property()->Int(); }
    Int_t Vars_t::FS_Settle_Value() { return FS_Settle_Value_Property()->Int(); }
    Int_t Vars_t::FS_Unsettle_Value() { return FS_Unsettle_Value_Property()->Int(); }
    Int_t Vars_t::FS_Mobilize_Value() { return FS_Mobilize_Value_Property()->Int(); }
    Int_t Vars_t::FS_Immobilize_Value() { return FS_Immobilize_Value_Property()->Int(); }
    Int_t Vars_t::FS_Sneak_Value() { return FS_Sneak_Value_Property()->Int(); }
    Int_t Vars_t::FS_Unsneak_Value() { return FS_Unsneak_Value_Property()->Int(); }
    Int_t Vars_t::FS_Saddle_Value() { return FS_Saddle_Value_Property()->Int(); }
    Int_t Vars_t::FS_Unsaddle_Value() { return FS_Unsaddle_Value_Property()->Int(); }
    Int_t Vars_t::FS_Resurrect_Value() { return FS_Resurrect_Value_Property()->Int(); }
    Vector_t<Int_t> Vars_t::FS_Summon_All_Mods() { return FS_Summon_All_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Summon_Mobile_Mods() { return FS_Summon_Mobile_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Summon_Immobile_Mods() { return FS_Summon_Immobile_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Settle_Mods() { return FS_Settle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Unsettle_Mods() { return FS_Unsettle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Mobilize_Mods() { return FS_Mobilize_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Immobilize_Mods() { return FS_Immobilize_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Sneak_Mods() { return FS_Sneak_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Unsneak_Mods() { return FS_Unsneak_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Saddle_Mods() { return FS_Saddle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Unsaddle_Mods() { return FS_Unsaddle_Mods_Property()->Vector<Int_t>(); }
    Vector_t<Int_t> Vars_t::FS_Resurrect_Mods() { return FS_Resurrect_Mods_Property()->Vector<Int_t>(); }
    void Vars_t::FS_Summon_All_Value(Int_t value) { FS_Summon_All_Value_Property()->Int(value); }
    void Vars_t::FS_Summon_Mobile_Value(Int_t value) { FS_Summon_Mobile_Value_Property()->Int(value); }
    void Vars_t::FS_Summon_Immobile_Value(Int_t value) { FS_Summon_Immobile_Value_Property()->Int(value); }
    void Vars_t::FS_Settle_Value(Int_t value) { FS_Settle_Value_Property()->Int(value); }
    void Vars_t::FS_Unsettle_Value(Int_t value) { FS_Unsettle_Value_Property()->Int(value); }
    void Vars_t::FS_Mobilize_Value(Int_t value) { FS_Mobilize_Value_Property()->Int(value); }
    void Vars_t::FS_Immobilize_Value(Int_t value) { FS_Immobilize_Value_Property()->Int(value); }
    void Vars_t::FS_Sneak_Value(Int_t value) { FS_Sneak_Value_Property()->Int(value); }
    void Vars_t::FS_Unsneak_Value(Int_t value) { FS_Unsneak_Value_Property()->Int(value); }
    void Vars_t::FS_Saddle_Value(Int_t value) { FS_Saddle_Value_Property()->Int(value); }
    void Vars_t::FS_Unsaddle_Value(Int_t value) { FS_Unsaddle_Value_Property()->Int(value); }
    void Vars_t::FS_Resurrect_Value(Int_t value) { FS_Resurrect_Value_Property()->Int(value); }
    void Vars_t::FS_Summon_All_Mods(Vector_t<Int_t> value) { FS_Summon_All_Mods_Property()->Pack(value); }
    void Vars_t::FS_Summon_Mobile_Mods(Vector_t<Int_t> value) { FS_Summon_Mobile_Mods_Property()->Pack(value); }
    void Vars_t::FS_Summon_Immobile_Mods(Vector_t<Int_t> value) { FS_Summon_Immobile_Mods_Property()->Pack(value); }
    void Vars_t::FS_Settle_Mods(Vector_t<Int_t> value) { FS_Settle_Mods_Property()->Pack(value); }
    void Vars_t::FS_Unsettle_Mods(Vector_t<Int_t> value) { FS_Unsettle_Mods_Property()->Pack(value); }
    void Vars_t::FS_Mobilize_Mods(Vector_t<Int_t> value) { FS_Mobilize_Mods_Property()->Pack(value); }
    void Vars_t::FS_Immobilize_Mods(Vector_t<Int_t> value) { FS_Immobilize_Mods_Property()->Pack(value); }
    void Vars_t::FS_Sneak_Mods(Vector_t<Int_t> value) { FS_Sneak_Mods_Property()->Pack(value); }
    void Vars_t::FS_Unsneak_Mods(Vector_t<Int_t> value) { FS_Unsneak_Mods_Property()->Pack(value); }
    void Vars_t::FS_Saddle_Mods(Vector_t<Int_t> value) { FS_Saddle_Mods_Property()->Pack(value); }
    void Vars_t::FS_Unsaddle_Mods(Vector_t<Int_t> value) { FS_Unsaddle_Mods_Property()->Pack(value); }
    void Vars_t::FS_Resurrect_Mods(Vector_t<Int_t> value) { FS_Resurrect_Mods_Property()->Pack(value); }

    void Vars_t::Initialize() // may have to queue a callback, to wait for the quest to start?
    {
        NPCP_Major(Consts::NPCP_Major());
        NPCP_Minor(Consts::NPCP_Minor());
        NPCP_Patch(Consts::NPCP_Patch());

        Allow_Dialogue_For_All(true);
        Allow_Chatter(true);

        Member_Limit(Party::Members_t::MAX);
        Member_Display_Limit(Party::Members_t::DEFAULT_DISPLAY_LIMIT);
        Default_Member_Style(CODES::STYLE::DEFAULT);
        Default_Member_Vitality(CODES::VITALITY::PROTECTED);

        Force_Clone_Uniques(false);
        Force_Clone_Generics(false);
        Force_Unclone_Uniques(false);
        Force_Unclone_Generics(false);
        Clone_Outfit_Algorithm(CODES::OUTFIT::REFERENCE);

        Do_Auto_Resurrect_Followers(true);
        Do_Level_Followers(true);

        Do_Auto_Change_Outfits(false);
        Do_Auto_Change_Immobile_Outfit(false);
        Do_Auto_Fill_Outfits(true);
        Fill_Outfit_Body_Chance(Party::Members_t::DEFAULT_OUTFIT_BODY_CHANCE);
        Fill_Outfit_Head_Chance(Party::Members_t::DEFAULT_OUTFIT_HEAD_CHANCE);
        Fill_Outfit_Hands_Chance(Party::Members_t::DEFAULT_OUTFIT_HANDS_CHANCE);
        Fill_Outfit_Feet_Chance(Party::Members_t::DEFAULT_OUTFIT_FEET_CHANCE);

        Member_Sort_Algorithm("NAME");
        Follower_Sort_Algorithm("NAME");
    }

    void Vars_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Vars_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}
