; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm_settings extends Quest

int     p_option_allow_dialogue_for_all         =    -1
int     p_option_allow_chatter                  =    -1

int     p_option_member_limit                   =    -1
int     p_option_member_display_limit           =    -1
int     p_option_default_member_style           =    -1
int     p_option_default_member_vitality        =    -1

int     p_option_force_clone_uniques            =    -1
int     p_option_force_clone_generics           =    -1
int     p_option_force_unclone_uniques          =    -1
int     p_option_force_unclone_generics         =    -1
int     p_option_clone_outfit_algorithm         =    -1

int     p_option_do_auto_resurrect_followers    =    -1
int     p_option_do_level_followers             =    -1

int     p_option_do_auto_change_outfits         =    -1
int     p_option_do_auto_change_immobile_outfit =    -1
int     p_option_do_auto_fill_outfits           =    -1
int     p_option_fill_outfit_body_chance        =    -1
int     p_option_fill_outfit_head_chance        =    -1
int     p_option_fill_outfit_hands_chance       =    -1
int     p_option_fill_outfit_feet_chance        =    -1

int     p_option_member_sort_algorithm          =    -1
int     p_option_follower_sort_algorithm        =    -1

function On_Build_Page() native
function On_Option_Select(int option) native
function On_Option_Menu_Open(int option) native
function On_Option_Menu_Accept(int option, int idx) native
function On_Option_Slider_Open(int option) native
function On_Option_Slider_Accept(int option, float value) native
function On_Option_Input_Accept(int option, string value) native
function On_Option_Keymap_Change(int option, int key_code, string conflict, string conflicting_mod) native
function On_Option_Default(int option) native
function On_Option_Highlight(int option) native
