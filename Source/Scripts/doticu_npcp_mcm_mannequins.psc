; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm_mannequins extends Quest

int                 p_code_view                 =     0

int                 p_idx_page                  =     0
int                 p_num_pages                 =     0

int                 p_curr_column               =     0
int                 p_curr_row                  =     0

Alias[]             p_curr_members              =  none
doticu_npcp_member  p_ref_member                =  none

int                 p_options_offset            =    -1
int                 p_option_enter              =    -1
int                 p_option_exit               =    -1
int                 p_option_prev               =    -1
int                 p_option_next               =    -1
int                 p_option_name               =    -1
int                 p_option_back               =    -1
int                 p_option_north_1            =    -1
int                 p_option_north_2            =    -1
int                 p_option_west               =    -1
int                 p_option_east               =    -1
int                 p_option_south_1            =    -1
int                 p_option_south_2            =    -1

function View_Mannequins() native

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
