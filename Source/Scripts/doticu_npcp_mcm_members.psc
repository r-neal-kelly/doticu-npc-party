;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_members extends Quest

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return doticu_npcp.Vars()
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return doticu_npcp.Members()
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return doticu_npcp.Control().COMMANDS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return doticu_npcp.Control().MCM
    endFunction
endProperty

; Private Constants
int property p_HEADERS_PER_PAGE hidden
    int function Get()
        if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS() 
            return 6
        else
            return 4
        endIf
    endFunction
endProperty
int property p_MEMBERS_PER_PAGE hidden
    int function Get()
        if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS() 
            return 18
        else
            return 20
        endIf
    endFunction
endProperty

; Private Variables
int                 p_code_view                         =     0

Alias[]             p_arr_aliases                       =  none
int                 p_num_pages                         =    -1
int                 p_idx_page                          =     0
Alias[]             p_arr_aliases_slice                 =  none
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

function f_Review_Members()
    p_code_view = doticu_npcp_codes.VIEW_MEMBERS()
    p_ref_member_members = none
endFunction

function f_Review_Filter_Members()
    p_code_view = doticu_npcp_codes.VIEW_FILTER_MEMBERS()
    p_ref_member_filter_members = none
endFunction

function f_Request_Prev_Member()
    p_do_prev_member = true
endFunction

function f_Request_Next_Member()
    p_do_next_member = true
endFunction

function f_On_Option_Select(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Select(id_option)
    endIf

    if false

    elseIf id_option == p_option_back && p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_Go_Back()

    elseIf id_option == p_option_prev
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        if p_idx_page == 0
            p_idx_page = p_num_pages - 1
        else
            p_idx_page -= 1
        endIf
        if p_code_view == doticu_npcp_codes.VIEW_MEMBERS()
            p_idx_page_members = p_idx_page
        elseIf p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
            p_idx_page_filter_members = p_idx_page
        endIf
        MCM.ForcePageReset()
    elseIf id_option == p_option_next
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        if p_idx_page == p_num_pages - 1
            p_idx_page = 0
        else
            p_idx_page += 1
        endIf
        if p_code_view == doticu_npcp_codes.VIEW_MEMBERS()
            p_idx_page_members = p_idx_page
        elseIf p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
            p_idx_page_filter_members = p_idx_page
        endIf
        MCM.ForcePageReset()

    elseIf id_option >= p_options_offset + p_HEADERS_PER_PAGE
        int idx_entity = p_Get_Idx_Entity(id_option)
        if idx_entity < 0 || idx_entity >= p_arr_aliases_slice.length
            return
        endIf

        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_ref_member = p_arr_aliases_slice[idx_entity] as doticu_npcp_member
        if p_code_view == doticu_npcp_codes.VIEW_MEMBERS()
            p_code_view = doticu_npcp_codes.VIEW_MEMBERS_MEMBER()
            p_ref_member_members = p_ref_member
        elseIf p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
            p_code_view = doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
            p_ref_member_filter_members = p_ref_member
        endIf
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Highlight(id_option)
    endIf

    if false

    elseIf id_option == p_option_back && p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        MCM.SetInfoText("Got back to the filter menu.")
    elseIf id_option == p_option_prev
        MCM.SetInfoText("Go to the Previous Page")
    elseIf id_option == p_option_next
        MCM.SetInfoText("Go to the Next Page")
    else
        int idx_entity = p_Get_Idx_Entity(id_option)
        if idx_entity < 0 || idx_entity >= p_arr_aliases_slice.length
            return
        endIf

        doticu_npcp_member ref_member = p_arr_aliases_slice[idx_entity] as doticu_npcp_member
        if !ref_member
            return
        endIf
        
        MCM.SetInfoText("Opens the member menu for " + ref_member.Name() + ".\n" + Get_Info_String(ref_member))

    endIf
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

; Public Methdos
string function Get_Info_String(doticu_npcp_member ref_member)
    if !ref_member
        return ""
    endIf

    Actor ref_actor = ref_member.Actor()
    if !ref_actor
        return ""
    endIf

    string str_sex = "Sex:"
    if ACTORS.Is_Male(ref_actor)
        str_sex += " Male"
    elseIf ACTORS.Is_Female(ref_actor)
        str_sex += " Female"
    else
        str_sex += " None"
    endIf

    string str_race = "Race: " + ref_actor.GetRace().GetName()

    string str_info = str_sex + ", " + str_race + "\n"

    if ref_member.Rating() > 0
        str_info += "Rating: " + ref_member.Rating_Stars()
    endIf

    ; this should show more about the member, style, and stats!!!
    ; whether is dead, healthly, etc.

    return str_info
endFunction

; Private Methods
function p_Go_Back()
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        MCM.MCM_FILTER.f_Review_Filter()
        MCM.ForcePageReset()
    endIf
endFunction

int function p_Get_Idx_Entity(int id_option)
    return id_option - p_options_offset - p_HEADERS_PER_PAGE
endFunction
