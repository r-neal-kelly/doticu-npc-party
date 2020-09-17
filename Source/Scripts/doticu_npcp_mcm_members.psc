; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm_members extends Quest

int                 p_code_view                         =     0

Alias[]             p_arr_aliases                       =  none
int                 p_num_pages                         =    -1
int                 p_idx_page                          =     0
doticu_npcp_member  p_ref_member                        =  none

int                 p_idx_page_members                  =    -1
doticu_npcp_member  p_ref_member_members                =  none

int                 p_idx_page_filter_members           =    -1
doticu_npcp_member  p_ref_member_filter_members         =  none

bool                p_do_prev_member                    = false
bool                p_do_next_member                    = false

int                 p_options_offset                    =    -1
int                 p_option_title                      =    -1
int                 p_option_back                       =    -1
int                 p_option_prev                       =    -1
int                 p_option_next                       =    -1

function View_Members() native
string function Member_Info_String(Alias member) native

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
