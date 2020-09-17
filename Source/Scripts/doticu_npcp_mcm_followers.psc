; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm_followers extends Quest

int                     p_code_view                 =     0

Alias[]                 p_arr_aliases               =  none
doticu_npcp_follower    p_ref_follower              =  none

bool                    p_do_prev_follower          = false
bool                    p_do_next_follower          = false

int                     p_options_offset            =    -1
int                     p_option_menu               =    -1

function View_Followers() native

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
