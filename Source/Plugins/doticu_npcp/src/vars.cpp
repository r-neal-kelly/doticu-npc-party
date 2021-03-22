/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/global.h"

#include "doticu_skylib/virtual_macros.h"

#include "consts.h"
#include "party_members.h"
#include "vars.h"

#define VAR DEFINE_VARIABLE_REFERENCE
#define PROP DEFINE_PROPERTY_REFERENCE

namespace doticu_npcp {

    some<Vars_t*>       Vars_t::Self()          { return Consts_t::NPCP::Quest::Vars(); }
    String_t            Vars_t::Class_Name()    { DEFINE_CLASS_NAME("doticu_npcp_vars"); }
    some<V::Class_t*>   Vars_t::Class()         { DEFINE_CLASS(); }
    some<V::Object_t*>  Vars_t::Object()        { DEFINE_OBJECT_STATIC(); }

    void Vars_t::Register_Me(V::Machine_t* machine)
    {
    }

    V::Variable_tt<Int_t>&              Vars_t::Major_Version()                         { VAR(Int_t, "p_version_major"); }
    V::Variable_tt<Int_t>&              Vars_t::Minor_Version()                         { VAR(Int_t, "p_version_minor"); }
    V::Variable_tt<Int_t>&              Vars_t::Patch_Version()                         { VAR(Int_t, "p_version_patch"); }

    V::Variable_tt<Int_t>&              Vars_t::Member_Limit()                          { VAR(Int_t, "p_max_members"); }
    V::Variable_tt<Int_t>&              Vars_t::Member_Display_Limit()                  { VAR(Int_t, "p_num_display"); }
    V::Variable_tt<String_t>&           Vars_t::Default_Member_Style()                  { VAR(String_t, "p_auto_style"); }
    V::Variable_tt<String_t>&           Vars_t::Default_Member_Vitality()               { VAR(String_t, "p_auto_vitality"); }
    V::Variable_tt<String_t>&           Vars_t::Member_Sort_Algorithm()                 { VAR(String_t, "p_str_sort_members"); }

    V::Variable_tt<Bool_t>&             Vars_t::Do_Auto_Resurrect_Followers()           { VAR(Bool_t, "p_auto_resurrect"); }
    V::Variable_tt<Bool_t>&             Vars_t::Do_Auto_Sojourn_Followers()             { VAR(Bool_t, "p_auto_sojourn"); }
    V::Variable_tt<String_t>&           Vars_t::Follower_Sort_Algorithm()               { VAR(String_t, "p_str_sort_followers"); }

    V::Variable_tt<Bool_t>&             Vars_t::Do_Auto_Change_Outfits()                { VAR(Bool_t, "p_auto_outfit"); }
    V::Variable_tt<Bool_t>&             Vars_t::Do_Auto_Change_Immobile_Outfit()        { VAR(Bool_t, "p_auto_immobile_outfit"); }
    V::Variable_tt<Bool_t>&             Vars_t::Do_Fill_Outfits()                       { VAR(Bool_t, "p_fill_outfits"); }
    V::Variable_tt<String_t>&           Vars_t::Clone_Outfit_Algorithm()                { VAR(String_t, "p_clone_outfit"); }

    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Global::Dialogue_Menu()      { PROP(Int_t, "key_g_dialogue_menu"); }

    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Toggle_Member()         { PROP(Int_t, "key_n_toggle_member"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Toggle_Move()           { PROP(Int_t, "key_n_toggle_move"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Move_Nearer()           { PROP(Int_t, "key_n_move_nearer"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Move_Farther()          { PROP(Int_t, "key_n_move_farther"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Move_Rotate_Left()      { PROP(Int_t, "key_n_move_rotate_left"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Move_Rotate_Right()     { PROP(Int_t, "key_n_move_rotate_right"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Has_Base()              { PROP(Int_t, "key_n_has_base"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Count_Base()            { PROP(Int_t, "key_n_count_base"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Has_Head()              { PROP(Int_t, "key_n_has_head"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::NPC::Count_Heads()           { PROP(Int_t, "key_n_count_heads"); }

    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Member::Toggle_Clone()       { PROP(Int_t, "key_m_toggle_clone"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Member::Toggle_Settler()     { PROP(Int_t, "key_m_toggle_settler"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Member::Toggle_Thrall()      { PROP(Int_t, "key_m_toggle_thrall"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Member::Toggle_Immobile()    { PROP(Int_t, "key_m_toggle_immobile"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Member::Toggle_Paralyzed()   { PROP(Int_t, "key_m_toggle_paralyzed"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Member::Toggle_Follower()    { PROP(Int_t, "key_m_toggle_follower"); }

    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Follower::Toggle_Sneak()     { PROP(Int_t, "key_f_toggle_sneak"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Follower::Toggle_Saddler()   { PROP(Int_t, "key_f_toggle_saddler"); }

    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Members::Toggle_Display()    { PROP(Int_t, "key_ms_toggle_display"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Members::Display_Previous()  { PROP(Int_t, "key_ms_display_previous"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Members::Display_Next()      { PROP(Int_t, "key_ms_display_next"); }

    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Summon_All()      { PROP(Int_t, "key_fs_summon_all"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Summon_Mobile()   { PROP(Int_t, "key_fs_summon_mobile"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Summon_Immobile() { PROP(Int_t, "key_fs_summon_immobile"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Settle()          { PROP(Int_t, "key_fs_settle"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Unsettle()        { PROP(Int_t, "key_fs_unsettle"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Mobilize()        { PROP(Int_t, "key_fs_mobilize"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Immobilize()      { PROP(Int_t, "key_fs_immobilize"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Sneak()           { PROP(Int_t, "key_fs_sneak"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Unsneak()         { PROP(Int_t, "key_fs_unsneak"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Saddle()          { PROP(Int_t, "key_fs_saddle"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Unsaddle()        { PROP(Int_t, "key_fs_unsaddle"); }
    V::Variable_tt<Int_t>&              Vars_t::Key::Base::Followers::Resurrect()       { PROP(Int_t, "key_fs_resurrect"); }

    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Global::Dialogue_Menu()      { PROP(Vector_t<Int_t>, "key_g_dialogue_menu_mods"); }

    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Toggle_Member()         { PROP(Vector_t<Int_t>, "key_n_toggle_member_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Toggle_Move()           { PROP(Vector_t<Int_t>, "key_n_toggle_move_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Move_Nearer()           { PROP(Vector_t<Int_t>, "key_n_move_nearer_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Move_Farther()          { PROP(Vector_t<Int_t>, "key_n_move_farther_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Move_Rotate_Left()      { PROP(Vector_t<Int_t>, "key_n_move_rotate_left_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Move_Rotate_Right()     { PROP(Vector_t<Int_t>, "key_n_move_rotate_right_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Has_Base()              { PROP(Vector_t<Int_t>, "key_n_has_base_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Count_Base()            { PROP(Vector_t<Int_t>, "key_n_count_base_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Has_Head()              { PROP(Vector_t<Int_t>, "key_n_has_head_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::NPC::Count_Heads()           { PROP(Vector_t<Int_t>, "key_n_count_heads_mods"); }

    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Member::Toggle_Clone()       { PROP(Vector_t<Int_t>, "key_m_toggle_clone_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Member::Toggle_Settler()     { PROP(Vector_t<Int_t>, "key_m_toggle_settler_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Member::Toggle_Thrall()      { PROP(Vector_t<Int_t>, "key_m_toggle_thrall_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Member::Toggle_Immobile()    { PROP(Vector_t<Int_t>, "key_m_toggle_immobile_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Member::Toggle_Paralyzed()   { PROP(Vector_t<Int_t>, "key_m_toggle_paralyzed_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Member::Toggle_Follower()    { PROP(Vector_t<Int_t>, "key_m_toggle_follower_mods"); }

    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Follower::Toggle_Sneak()     { PROP(Vector_t<Int_t>, "key_f_toggle_sneak_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Follower::Toggle_Saddler()   { PROP(Vector_t<Int_t>, "key_f_toggle_saddler_mods"); }

    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Members::Toggle_Display()    { PROP(Vector_t<Int_t>, "key_ms_toggle_display_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Members::Display_Previous()  { PROP(Vector_t<Int_t>, "key_ms_display_previous_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Members::Display_Next()      { PROP(Vector_t<Int_t>, "key_ms_display_next_mods"); }

    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Summon_All()      { PROP(Vector_t<Int_t>, "key_fs_summon_all_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Summon_Mobile()   { PROP(Vector_t<Int_t>, "key_fs_summon_mobile_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Summon_Immobile() { PROP(Vector_t<Int_t>, "key_fs_summon_immobile_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Settle()          { PROP(Vector_t<Int_t>, "key_fs_settle_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Unsettle()        { PROP(Vector_t<Int_t>, "key_fs_unsettle_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Mobilize()        { PROP(Vector_t<Int_t>, "key_fs_mobilize_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Immobilize()      { PROP(Vector_t<Int_t>, "key_fs_immobilize_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Sneak()           { PROP(Vector_t<Int_t>, "key_fs_sneak_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Unsneak()         { PROP(Vector_t<Int_t>, "key_fs_unsneak_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Saddle()          { PROP(Vector_t<Int_t>, "key_fs_saddle_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Unsaddle()        { PROP(Vector_t<Int_t>, "key_fs_unsaddle_mods"); }
    V::Variable_tt<Vector_t<Int_t>>&    Vars_t::Key::Mods::Followers::Resurrect()       { PROP(Vector_t<Int_t>, "key_fs_resurrect_mods"); }

    Bool_t  Vars_t::Do_Allow_Dialogue_For_All()             { return Consts_t::NPCP::Global::Do_Allow_Dialogue_For_All()->Bool(); }
    void    Vars_t::Do_Allow_Dialogue_For_All(Bool_t value) { Consts_t::NPCP::Global::Do_Allow_Dialogue_For_All()->Bool(value); }
    Bool_t  Vars_t::Do_Allow_Chatter()                      { return Consts_t::NPCP::Global::Do_Allow_Chatter()->Bool(); }
    void    Vars_t::Do_Allow_Chatter(Bool_t value)          { Consts_t::NPCP::Global::Do_Allow_Chatter()->Bool(value); }
    Bool_t  Vars_t::Do_Force_Clone_Uniques()                { return Consts_t::NPCP::Global::Do_Force_Clone_Uniques()->Bool(); }
    void    Vars_t::Do_Force_Clone_Uniques(Bool_t value)    { Consts_t::NPCP::Global::Do_Force_Clone_Uniques()->Bool(value); }
    Bool_t  Vars_t::Do_Force_Clone_Generics()               { return Consts_t::NPCP::Global::Do_Force_Clone_Generics()->Bool(); }
    void    Vars_t::Do_Force_Clone_Generics(Bool_t value)   { Consts_t::NPCP::Global::Do_Force_Clone_Generics()->Bool(value); }
    Bool_t  Vars_t::Do_Force_Unclone_Uniques()              { return Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()->Bool(); }
    void    Vars_t::Do_Force_Unclone_Uniques(Bool_t value)  { Consts_t::NPCP::Global::Do_Force_Unclone_Uniques()->Bool(value); }
    Bool_t  Vars_t::Do_Force_Unclone_Generics()             { return Consts_t::NPCP::Global::Do_Force_Unclone_Generics()->Bool(); }
    void    Vars_t::Do_Force_Unclone_Generics(Bool_t value) { Consts_t::NPCP::Global::Do_Force_Unclone_Generics()->Bool(value); }
    Bool_t  Vars_t::Do_Level_Followers()                    { return Consts_t::NPCP::Global::Do_Level_Followers()->Bool(); }
    void    Vars_t::Do_Level_Followers(Bool_t value)        { Consts_t::NPCP::Global::Do_Level_Followers()->Bool(value); }

    Int_t   Vars_t::Fill_Outfit_Body_Percent()              { return 100 - Consts_t::NPCP::Global::Empty_Outfit_Body_Percent()->Percent(); }
    void    Vars_t::Fill_Outfit_Body_Percent(Int_t value)   { Consts_t::NPCP::Global::Empty_Outfit_Body_Percent()->Percent(100 - value); }
    Int_t   Vars_t::Fill_Outfit_Feet_Percent()              { return 100 - Consts_t::NPCP::Global::Empty_Outfit_Feet_Percent()->Percent(); }
    void    Vars_t::Fill_Outfit_Feet_Percent(Int_t value)   { Consts_t::NPCP::Global::Empty_Outfit_Feet_Percent()->Percent(100 - value); }
    Int_t   Vars_t::Fill_Outfit_Hands_Percent()             { return 100 - Consts_t::NPCP::Global::Empty_Outfit_Hands_Percent()->Percent(); }
    void    Vars_t::Fill_Outfit_Hands_Percent(Int_t value)  { Consts_t::NPCP::Global::Empty_Outfit_Hands_Percent()->Percent(100 - value); }
    Int_t   Vars_t::Fill_Outfit_Head_Percent()              { return 100 - Consts_t::NPCP::Global::Empty_Outfit_Head_Percent()->Percent(); }
    void    Vars_t::Fill_Outfit_Head_Percent(Int_t value)   { Consts_t::NPCP::Global::Empty_Outfit_Head_Percent()->Percent(100 - value); }

    const Version_t<u16> Vars_t::Version()
    {
        return Version_t<u16>(Major_Version(), Minor_Version(), Patch_Version());
    }

    void Vars_t::Version(const Version_t<u16> value)
    {
        Major_Version() = static_cast<Int_t>(value.major);
        Minor_Version() = static_cast<Int_t>(value.minor);
        Patch_Version() = static_cast<Int_t>(value.patch);
    }

    void Vars_t::Initialize()
    {
        Version(Consts_t::NPCP::Version::Current());

        Member_Limit() = static_cast<Int_t>(Party::Members_t::MAX_MEMBERS);
        Member_Display_Limit() = static_cast<Int_t>(5);                         // Party::Members_t::DEFAULT_DISPLAY_LIMIT
        Default_Member_Style() = "DEFAULT";                                     // CODES::STYLE::DEFAULT
        Default_Member_Vitality() = "PROTECTED";                                // CODES::VITALITY::PROTECTED
        Member_Sort_Algorithm() = "NAME";

        Do_Auto_Resurrect_Followers() = true;
        Do_Auto_Sojourn_Followers() = false;
        Follower_Sort_Algorithm() = "NAME";

        Do_Auto_Change_Outfits() = false;
        Do_Auto_Change_Immobile_Outfit() = false;
        Do_Fill_Outfits() = true;
        Clone_Outfit_Algorithm() = "REFERENCE";                                 // CODES::OUTFIT::REFERENCE
        
        Do_Allow_Dialogue_For_All(true);
        Do_Allow_Chatter(true);
        Do_Force_Clone_Uniques(false);
        Do_Force_Clone_Generics(false);
        Do_Force_Unclone_Uniques(false);
        Do_Force_Unclone_Generics(false);
        Do_Level_Followers(true);

        Fill_Outfit_Body_Percent(100);                                          // Party::Members_t::DEFAULT_OUTFIT_BODY_CHANCE
        Fill_Outfit_Feet_Percent(67);                                           // Party::Members_t::DEFAULT_OUTFIT_FEET_CHANCE
        Fill_Outfit_Hands_Percent(67);                                          // Party::Members_t::DEFAULT_OUTFIT_HANDS_CHANCE
        Fill_Outfit_Head_Percent(50);                                           // Party::Members_t::DEFAULT_OUTFIT_HEAD_CHANCE
    }

}

#undef VAR
#undef PROP
