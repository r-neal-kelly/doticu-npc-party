;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_members extends Quest

; Modules
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return doticu_npcp.Control().MCM
    endFunction
endProperty

; Private Variables
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

; Native Methods
function f_View_Members() native

function f_Build_Page() native

function f_On_Option_Select         (int option) native
function f_On_Option_Highlight      (int option) native

function Review_Members() native
function Review_Filter_Members() native
string function Member_Info_String(Alias member) native

; Friend Methods
function f_Create()
    p_code_view = 0
    p_ref_member = none
endFunction

function f_Destroy()
    p_code_view = 0
    p_ref_member = none
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_On_Option_Menu_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Menu_Open(id_option)
    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Slider_Open(id_option)
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endFunction

function f_On_Option_Default(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Default(id_option)
    endIf
endFunction
