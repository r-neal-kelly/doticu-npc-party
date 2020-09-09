/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Vars {

    using namespace Papyrus;

    String_t Class_Name();
    Class_Info_t* Class_Info();
    Vars_t* Self();
    Object_t* Object();

    Variable_t* Variable(String_t variable_name);
    Variable_t* Property(String_t property_name);

    Variable_t* NPCP_Major_Variable();
    Variable_t* NPCP_Minor_Variable();
    Variable_t* NPCP_Patch_Variable();

    Int_t NPCP_Major();
    Int_t NPCP_Minor();
    Int_t NPCP_Patch();

    void NPCP_Major(Int_t npcp_major);
    void NPCP_Minor(Int_t npcp_minor);
    void NPCP_Patch(Int_t npcp_patch);

    Bool_t Is_Leveling_Enabled();
    void Enable_Leveling();
    void Disable_Leveling();

    Bool_t Does_Allow_Chatter();
    void Do_Allow_Chatter();
    void Dont_Allow_Chatter();

    // Global Keys
    Variable_t* G_Dialogue_Menu_Value_Property();

    Variable_t* G_Dialogue_Menu_Mods_Property();

    Int_t G_Dialogue_Menu_Value();

    Vector_t<Int_t> G_Dialogue_Menu_Mods();

    void G_Dialogue_Menu_Value(Int_t value);

    void G_Dialogue_Menu_Mods(Vector_t<Int_t> value);

    // NPC Keys
    Variable_t* N_Toggle_Member_Value_Property();
    Variable_t* N_Toggle_Move_Value_Property();
    Variable_t* N_Move_Nearer_Value_Property();
    Variable_t* N_Move_Farther_Value_Property();
    Variable_t* N_Move_Rotate_Left_Value_Property();
    Variable_t* N_Move_Rotate_Right_Value_Property();
    Variable_t* N_Has_Base_Value_Property();
    Variable_t* N_Count_Base_Value_Property();
    Variable_t* N_Has_Head_Value_Property();
    Variable_t* N_Count_Heads_Value_Property();

    Variable_t* N_Toggle_Member_Mods_Property();
    Variable_t* N_Toggle_Move_Mods_Property();
    Variable_t* N_Move_Nearer_Mods_Property();
    Variable_t* N_Move_Farther_Mods_Property();
    Variable_t* N_Move_Rotate_Left_Mods_Property();
    Variable_t* N_Move_Rotate_Right_Mods_Property();
    Variable_t* N_Has_Base_Mods_Property();
    Variable_t* N_Count_Base_Mods_Property();
    Variable_t* N_Has_Head_Mods_Property();
    Variable_t* N_Count_Heads_Mods_Property();

    Int_t N_Toggle_Member_Value();
    Int_t N_Toggle_Move_Value();
    Int_t N_Move_Nearer_Value();
    Int_t N_Move_Farther_Value();
    Int_t N_Move_Rotate_Left_Value();
    Int_t N_Move_Rotate_Right_Value();
    Int_t N_Has_Base_Value();
    Int_t N_Count_Base_Value();
    Int_t N_Has_Head_Value();
    Int_t N_Count_Heads_Value();

    Vector_t<Int_t> N_Toggle_Member_Mods();
    Vector_t<Int_t> N_Toggle_Move_Mods();
    Vector_t<Int_t> N_Move_Nearer_Mods();
    Vector_t<Int_t> N_Move_Farther_Mods();
    Vector_t<Int_t> N_Move_Rotate_Left_Mods();
    Vector_t<Int_t> N_Move_Rotate_Right_Mods();
    Vector_t<Int_t> N_Has_Base_Mods();
    Vector_t<Int_t> N_Count_Base_Mods();
    Vector_t<Int_t> N_Has_Head_Mods();
    Vector_t<Int_t> N_Count_Heads_Mods();

    void N_Toggle_Member_Value(Int_t value);
    void N_Toggle_Move_Value(Int_t value);
    void N_Move_Nearer_Value(Int_t value);
    void N_Move_Farther_Value(Int_t value);
    void N_Move_Rotate_Left_Value(Int_t value);
    void N_Move_Rotate_Right_Value(Int_t value);
    void N_Has_Base_Value(Int_t value);
    void N_Count_Base_Value(Int_t value);
    void N_Has_Head_Value(Int_t value);
    void N_Count_Heads_Value(Int_t value);

    void N_Toggle_Member_Mods(Vector_t<Int_t> value);
    void N_Toggle_Move_Mods(Vector_t<Int_t> value);
    void N_Move_Nearer_Mods(Vector_t<Int_t> value);
    void N_Move_Farther_Mods(Vector_t<Int_t> value);
    void N_Move_Rotate_Left_Mods(Vector_t<Int_t> value);
    void N_Move_Rotate_Right_Mods(Vector_t<Int_t> value);
    void N_Has_Base_Mods(Vector_t<Int_t> value);
    void N_Count_Base_Mods(Vector_t<Int_t> value);
    void N_Has_Head_Mods(Vector_t<Int_t> value);
    void N_Count_Heads_Mods(Vector_t<Int_t> value);

    // Member Keys
    Variable_t* M_Toggle_Clone_Value_Property();
    Variable_t* M_Toggle_Settler_Value_Property();
    Variable_t* M_Toggle_Thrall_Value_Property();
    Variable_t* M_Toggle_Immobile_Value_Property();
    Variable_t* M_Toggle_Paralyzed_Value_Property();
    Variable_t* M_Toggle_Follower_Value_Property();

    Variable_t* M_Toggle_Clone_Mods_Property();
    Variable_t* M_Toggle_Settler_Mods_Property();
    Variable_t* M_Toggle_Thrall_Mods_Property();
    Variable_t* M_Toggle_Immobile_Mods_Property();
    Variable_t* M_Toggle_Paralyzed_Mods_Property();
    Variable_t* M_Toggle_Follower_Mods_Property();

    Int_t M_Toggle_Clone_Value();
    Int_t M_Toggle_Settler_Value();
    Int_t M_Toggle_Thrall_Value();
    Int_t M_Toggle_Immobile_Value();
    Int_t M_Toggle_Paralyzed_Value();
    Int_t M_Toggle_Follower_Value();

    Vector_t<Int_t> M_Toggle_Clone_Mods();
    Vector_t<Int_t> M_Toggle_Settler_Mods();
    Vector_t<Int_t> M_Toggle_Thrall_Mods();
    Vector_t<Int_t> M_Toggle_Immobile_Mods();
    Vector_t<Int_t> M_Toggle_Paralyzed_Mods();
    Vector_t<Int_t> M_Toggle_Follower_Mods();

    void M_Toggle_Clone_Value(Int_t value);
    void M_Toggle_Settler_Value(Int_t value);
    void M_Toggle_Thrall_Value(Int_t value);
    void M_Toggle_Immobile_Value(Int_t value);
    void M_Toggle_Paralyzed_Value(Int_t value);
    void M_Toggle_Follower_Value(Int_t value);

    void M_Toggle_Clone_Mods(Vector_t<Int_t> value);
    void M_Toggle_Settler_Mods(Vector_t<Int_t> value);
    void M_Toggle_Thrall_Mods(Vector_t<Int_t> value);
    void M_Toggle_Immobile_Mods(Vector_t<Int_t> value);
    void M_Toggle_Paralyzed_Mods(Vector_t<Int_t> value);
    void M_Toggle_Follower_Mods(Vector_t<Int_t> value);

    // Follower Keys
    Variable_t* F_Toggle_Sneak_Value_Property();
    Variable_t* F_Toggle_Saddler_Value_Property();

    Variable_t* F_Toggle_Sneak_Mods_Property();
    Variable_t* F_Toggle_Saddler_Mods_Property();

    Int_t F_Toggle_Sneak_Value();
    Int_t F_Toggle_Saddler_Value();

    Vector_t<Int_t> F_Toggle_Sneak_Mods();
    Vector_t<Int_t> F_Toggle_Saddler_Mods();

    void F_Toggle_Sneak_Value(Int_t value);
    void F_Toggle_Saddler_Value(Int_t value);

    void F_Toggle_Sneak_Mods(Vector_t<Int_t> value);
    void F_Toggle_Saddler_Mods(Vector_t<Int_t> value);

    // Members Keys
    Variable_t* MS_Toggle_Display_Value_Property();
    Variable_t* MS_Display_Previous_Value_Property();
    Variable_t* MS_Display_Next_Value_Property();

    Variable_t* MS_Toggle_Display_Mods_Property();
    Variable_t* MS_Display_Previous_Mods_Property();
    Variable_t* MS_Display_Next_Mods_Property();

    Int_t MS_Toggle_Display_Value();
    Int_t MS_Display_Previous_Value();
    Int_t MS_Display_Next_Value();

    Vector_t<Int_t> MS_Toggle_Display_Mods();
    Vector_t<Int_t> MS_Display_Previous_Mods();
    Vector_t<Int_t> MS_Display_Next_Mods();

    void MS_Toggle_Display_Value(Int_t value);
    void MS_Display_Previous_Value(Int_t value);
    void MS_Display_Next_Value(Int_t value);

    void MS_Toggle_Display_Mods(Vector_t<Int_t> value);
    void MS_Display_Previous_Mods(Vector_t<Int_t> value);
    void MS_Display_Next_Mods(Vector_t<Int_t> value);

    // Followers Keys
    Variable_t* FS_Summon_All_Value_Property();
    Variable_t* FS_Summon_Mobile_Value_Property();
    Variable_t* FS_Summon_Immobile_Value_Property();
    Variable_t* FS_Settle_Value_Property();
    Variable_t* FS_Unsettle_Value_Property();
    Variable_t* FS_Mobilize_Value_Property();
    Variable_t* FS_Immobilize_Value_Property();
    Variable_t* FS_Sneak_Value_Property();
    Variable_t* FS_Unsneak_Value_Property();
    Variable_t* FS_Saddle_Value_Property();
    Variable_t* FS_Unsaddle_Value_Property();
    Variable_t* FS_Resurrect_Value_Property();

    Variable_t* FS_Summon_All_Mods_Property();
    Variable_t* FS_Summon_Mobile_Mods_Property();
    Variable_t* FS_Summon_Immobile_Mods_Property();
    Variable_t* FS_Settle_Mods_Property();
    Variable_t* FS_Unsettle_Mods_Property();
    Variable_t* FS_Mobilize_Mods_Property();
    Variable_t* FS_Immobilize_Mods_Property();
    Variable_t* FS_Sneak_Mods_Property();
    Variable_t* FS_Unsneak_Mods_Property();
    Variable_t* FS_Saddle_Mods_Property();
    Variable_t* FS_Unsaddle_Mods_Property();
    Variable_t* FS_Resurrect_Mods_Property();

    Int_t FS_Summon_All_Value();
    Int_t FS_Summon_Mobile_Value();
    Int_t FS_Summon_Immobile_Value();
    Int_t FS_Settle_Value();
    Int_t FS_Unsettle_Value();
    Int_t FS_Mobilize_Value();
    Int_t FS_Immobilize_Value();
    Int_t FS_Sneak_Value();
    Int_t FS_Unsneak_Value();
    Int_t FS_Saddle_Value();
    Int_t FS_Unsaddle_Value();
    Int_t FS_Resurrect_Value();

    Vector_t<Int_t> FS_Summon_All_Mods();
    Vector_t<Int_t> FS_Summon_Mobile_Mods();
    Vector_t<Int_t> FS_Summon_Immobile_Mods();
    Vector_t<Int_t> FS_Settle_Mods();
    Vector_t<Int_t> FS_Unsettle_Mods();
    Vector_t<Int_t> FS_Mobilize_Mods();
    Vector_t<Int_t> FS_Immobilize_Mods();
    Vector_t<Int_t> FS_Sneak_Mods();
    Vector_t<Int_t> FS_Unsneak_Mods();
    Vector_t<Int_t> FS_Saddle_Mods();
    Vector_t<Int_t> FS_Unsaddle_Mods();
    Vector_t<Int_t> FS_Resurrect_Mods();

    void FS_Summon_All_Value(Int_t value);
    void FS_Summon_Mobile_Value(Int_t value);
    void FS_Summon_Immobile_Value(Int_t value);
    void FS_Settle_Value(Int_t value);
    void FS_Unsettle_Value(Int_t value);
    void FS_Mobilize_Value(Int_t value);
    void FS_Immobilize_Value(Int_t value);
    void FS_Sneak_Value(Int_t value);
    void FS_Unsneak_Value(Int_t value);
    void FS_Saddle_Value(Int_t value);
    void FS_Unsaddle_Value(Int_t value);
    void FS_Resurrect_Value(Int_t value);

    void FS_Summon_All_Mods(Vector_t<Int_t> value);
    void FS_Summon_Mobile_Mods(Vector_t<Int_t> value);
    void FS_Summon_Immobile_Mods(Vector_t<Int_t> value);
    void FS_Settle_Mods(Vector_t<Int_t> value);
    void FS_Unsettle_Mods(Vector_t<Int_t> value);
    void FS_Mobilize_Mods(Vector_t<Int_t> value);
    void FS_Immobilize_Mods(Vector_t<Int_t> value);
    void FS_Sneak_Mods(Vector_t<Int_t> value);
    void FS_Unsneak_Mods(Vector_t<Int_t> value);
    void FS_Saddle_Mods(Vector_t<Int_t> value);
    void FS_Unsaddle_Mods(Vector_t<Int_t> value);
    void FS_Resurrect_Mods(Vector_t<Int_t> value);

    // Bools
    Bool_t Do_Force_Clone_Unique();
    Bool_t Do_Force_Clone_Generic();
    Bool_t Do_Force_Unclone_Unique();
    Bool_t Do_Force_Unclone_Generic();
    Bool_t Do_Fill_Outfit2s();
    Bool_t Do_Auto_Outfit2s();
    Bool_t Do_Auto_Immobile_Outfit2();
    Bool_t Do_Auto_Resurrect();

    Int_t Member_Limit();
    Int_t Display_Count();
    Int_t Clone_Outfit();
    Int_t Default_Style();
    Int_t Default_Vitality();

    String_t Members_Sort_Algorithm();
    String_t Followers_Sort_Algorithm();

}}

namespace doticu_npcp { namespace Vars { namespace Exports {

    bool Register(Papyrus::Registry_t* registry);

}}}
