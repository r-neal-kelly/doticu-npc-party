;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_members extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return p_DATA.MODS.CONTROL.MCM
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA  =  none

int property p_HEADERS_PER_PAGE hidden
    int function Get()
        return 4
    endFunction
endProperty
int property p_MEMBERS_PER_PAGE hidden
    int function Get()
        return 20
    endFunction
endProperty

; Private Variables
bool                p_is_created                = false
int                 p_code_view                 =     0
doticu_npcp_member  p_ref_member                =  none

int                 p_curr_page                 =     0
int                 p_num_pages                 =    -1
Alias[]             p_arr_aliases               =  none
int                 p_options_offset            =    -1

int                 p_option_prev               =    -1
int                 p_option_next               =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_View_Members()
    p_code_view = CODES.VIEW_MEMBERS
    p_ref_member = none
endFunction

function f_View_Member(doticu_npcp_member ref_member)
    p_code_view = CODES.VIEW_MEMBER
    p_ref_member = ref_member
endFunction

function f_Build_Page()
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_Build_Page(CODES.VIEW_MEMBER, p_ref_member)
        return
    endIf

    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    int num_members = MEMBERS.Get_Count()
    string str_count_members
    string str_count_pages
    if num_members == 0
        MCM.SetTitleText(p_Format_Title(0, 0, 1))
        MCM.AddHeaderOption(" No Members ")
        return
    endIf

    p_num_pages = Math.Ceiling(num_members / (p_MEMBERS_PER_PAGE as float))
    MCM.SetTitleText(p_Format_Title(num_members, p_curr_page, p_num_pages))

    if num_members > p_MEMBERS_PER_PAGE
        p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "")
        p_option_next = MCM.AddTextOption("                       Go to Next Page", "")
    else
        p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "", MCM.OPTION_FLAG_DISABLED)
        p_option_next = MCM.AddTextOption("                       Go to Next Page", "", MCM.OPTION_FLAG_DISABLED)
    endIf
    p_options_offset = p_option_prev

    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")

    int idx_from = p_MEMBERS_PER_PAGE * p_curr_page
    int idx_to_ex = idx_from + p_MEMBERS_PER_PAGE
    int idx = 0
    p_arr_aliases = MEMBERS.Get_Members(idx_from, idx_to_ex)
    while idx < p_arr_aliases.length
        doticu_npcp_member ref_member = p_arr_aliases[idx] as doticu_npcp_member
        MCM.AddTextOption(ref_member.Get_Name(), "...")
        idx += 1
    endWhile
endFunction

function f_On_Option_Select(int id_option)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Select(id_option)
        return
    endIf

    if id_option == p_option_prev
        if p_curr_page == 0
            p_curr_page = p_num_pages - 1
        else
            p_curr_page -= 1
        endIf
        MCM.ForcePageReset()
    elseIf id_option == p_option_next
        if p_curr_page == p_num_pages - 1
            p_curr_page = 0
        else
            p_curr_page += 1
        endIf
        MCM.ForcePageReset()
    else
        f_View_Member(p_arr_aliases[p_Get_Idx_Entity(id_option)] as doticu_npcp_member)
        MCM.ForcePageReset()
    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Highlight(id_option)
        return
    endIf

    if id_option == p_option_prev
        MCM.SetInfoText("Go to the Previous Page")
    elseIf id_option == p_option_next
        MCM.SetInfoText("Go to the Next Page")
    else
        int idx_entity = p_Get_Idx_Entity(id_option)
        doticu_npcp_member ref_member = p_arr_aliases[idx_entity] as doticu_npcp_member
        Actor ref_actor = ref_member.Get_Actor()
        string str_name = ref_member.Get_Name()
        string str_race = ref_actor.GetRace().GetName()
        MCM.SetInfoText("Opens the member menu for " + str_name + ".\n" + "Race: " + str_race)
        ; this should show more about the member, like race, gender, style, and stats!!!
        ; whether is dead, healthly, etc. quick stats in other words
    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Menu_Open(id_option)
        return
    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Menu_Accept(id_option, idx_option)
        return
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Slider_Open(id_option)
        return
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Slider_Accept(id_option, float_value)
        return
    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Input_Accept(id_option, str_input)
        return
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
        return
    endIf
endFunction

function f_On_Option_Default(int id_option)
    if p_code_view == CODES.VIEW_MEMBER
        MCM.MCM_MEMBER.f_On_Option_Default(id_option)
        return
    endIf
endFunction

; Private Methods
string function p_Format_Title(int num_members, int idx_page, int num_pages)
    string str_members = "Members: " + num_members + "/" + MEMBERS.Get_Max()
    string str_pages = "Page: " + (idx_page + 1) + "/" + num_pages
    return str_members + "               " + str_pages
endFunction

int function p_Get_Idx_Entity(int id_option)
    return id_option - p_options_offset - p_HEADERS_PER_PAGE
endFunction
