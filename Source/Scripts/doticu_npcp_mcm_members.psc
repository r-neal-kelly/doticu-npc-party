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
        if p_code_view == CODES.VIEW_FILTER_MEMBERS 
            return 6
        else
            return 4
        endIf
    endFunction
endProperty
int property p_MEMBERS_PER_PAGE hidden
    int function Get()
        if p_code_view == CODES.VIEW_FILTER_MEMBERS 
            return 18
        else
            return 20
        endIf
    endFunction
endProperty

; Private Variables
bool                p_is_created                        = false
int                 p_code_view                         =     0

doticu_npcp_member  p_ref_member                        =  none
Alias[]             p_arr_aliases                       =  none
Alias[]             p_arr_aliases_slice                 =  none
int                 p_idx_page                          =     0
int                 p_num_pages                         =    -1

doticu_npcp_member  p_ref_member_members                =  none
int                 p_idx_page_members                  =    -1

doticu_npcp_member  p_ref_member_filter_members         =  none
int                 p_idx_page_filter_members           =    -1

bool                p_do_prev_member                    = false
bool                p_do_next_member                    = false

int                 p_options_offset                    =    -1
int                 p_option_title                      =    -1
int                 p_option_back                       =    -1
int                 p_option_prev                       =    -1
int                 p_option_next                       =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_code_view = 0
    p_ref_member = none
endFunction

function f_Destroy()
    p_is_created = false
    p_code_view = 0
    p_ref_member = none
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_View_Members(Alias[] arr_aliases)
    if p_ref_member_members
        p_code_view = CODES.VIEW_MEMBERS_MEMBER
    else
        p_code_view = CODES.VIEW_MEMBERS
    endIf

    p_View(arr_aliases, p_idx_page_members, p_ref_member_members)
    p_idx_page_members = p_idx_page
endFunction

function f_View_Filter_Members(Alias[] arr_aliases)
    if p_ref_member_filter_members
        p_code_view = CODES.VIEW_FILTER_MEMBERS_MEMBER
    else
        p_code_view = CODES.VIEW_FILTER_MEMBERS
    endIf

    p_View(arr_aliases, p_idx_page_filter_members, p_ref_member_filter_members)
    p_idx_page_filter_members = p_idx_page
endFunction

function f_Review_Members()
    p_code_view = CODES.VIEW_MEMBERS
    p_ref_member_members = none
endFunction

function f_Review_Filter_Members()
    p_code_view = CODES.VIEW_FILTER_MEMBERS
    p_ref_member_filter_members = none
endFunction

function f_Request_Prev_Member()
    p_do_prev_member = true
endFunction

function f_Request_Next_Member()
    p_do_next_member = true
endFunction

bool function f_Is_Valid_Member(doticu_npcp_member ref_member)
    if !ref_member || !ref_member.Exists() || p_arr_aliases.Find(ref_member) < 0
        return false
    else
        return true
    endIf
endFunction

function f_Build_Page()
    if p_do_prev_member
        p_ref_member = p_Get_Prev_Member(p_ref_member)
        p_do_prev_member = false
    elseIf p_do_next_member
        p_ref_member = p_Get_Next_Member(p_ref_member)
        p_do_next_member = false
    endIf

    if p_code_view == CODES.VIEW_MEMBERS_MEMBER
        if f_Is_Valid_Member(p_ref_member)
            return p_Build_Members_Member()
        else
            f_Review_Members()
        endIf
    elseIf p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        if f_Is_Valid_Member(p_ref_member)
            return p_Build_Filter_Members_Member()
        else
            f_Review_Filter_Members()
        endIf
    endIf

    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    if !p_arr_aliases
        MCM.SetTitleText(p_Format_Title(0, 0, 1))

        if p_code_view == CODES.VIEW_FILTER_MEMBERS
            p_option_title = MCM.AddTextOption(MCM.MCM_FILTER.f_Get_Filter_String(), "")
            p_option_back = MCM.AddTextOption("                            Go Back", "")
        endIf

        MCM.AddHeaderOption(" No Members ")

        return
    endIf

    MCM.SetTitleText(p_Format_Title(p_arr_aliases.length, p_idx_page, p_num_pages))

    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        p_option_title = MCM.AddTextOption(MCM.MCM_FILTER.f_Get_Filter_String(), "")
        p_option_back = MCM.AddTextOption("                            Go Back", "")
    endIf

    if p_arr_aliases.length > p_MEMBERS_PER_PAGE
        p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "")
        p_option_next = MCM.AddTextOption("                       Go to Next Page", "")
    else
        p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "", MCM.FLAG_DISABLE)
        p_option_next = MCM.AddTextOption("                       Go to Next Page", "", MCM.FLAG_DISABLE)
    endIf

    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        p_options_offset = p_option_title
    else
        p_options_offset = p_option_prev
    endIf

    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")

    int idx_slice = 0
    while idx_slice < p_arr_aliases_slice.length
        doticu_npcp_member ref_member = p_arr_aliases_slice[idx_slice] as doticu_npcp_member
        MCM.AddTextOption(ref_member.Get_Name(), "...")
        idx_slice += 1
    endWhile
endFunction

function f_On_Option_Select(int id_option)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Select(id_option)
    endIf

    if false

    elseIf id_option == p_option_back && p_code_view == CODES.VIEW_FILTER_MEMBERS
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_Go_Back()

    elseIf id_option == p_option_prev
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        if p_idx_page == 0
            p_idx_page = p_num_pages - 1
        else
            p_idx_page -= 1
        endIf
        if p_code_view == CODES.VIEW_MEMBERS
            p_idx_page_members = p_idx_page
        elseIf p_code_view == CODES.VIEW_FILTER_MEMBERS
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
        if p_code_view == CODES.VIEW_MEMBERS
            p_idx_page_members = p_idx_page
        elseIf p_code_view == CODES.VIEW_FILTER_MEMBERS
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
        if p_code_view == CODES.VIEW_MEMBERS
            p_code_view = CODES.VIEW_MEMBERS_MEMBER
            p_ref_member_members = p_ref_member
        elseIf p_code_view == CODES.VIEW_FILTER_MEMBERS
            p_code_view = CODES.VIEW_FILTER_MEMBERS_MEMBER
            p_ref_member_filter_members = p_ref_member
        endIf
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Highlight(id_option)
    endIf

    if false

    elseIf id_option == p_option_back && p_code_view == CODES.VIEW_FILTER_MEMBERS
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
        
        MCM.SetInfoText("Opens the member menu for " + ref_member.Get_Name() + ".\n" + Get_Info_String(ref_member))

    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Menu_Open(id_option)
    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Slider_Open(id_option)
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endFunction

function f_On_Option_Default(int id_option)
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        return MCM.MCM_MEMBER.f_On_Option_Default(id_option)
    endIf
endFunction

; Public Methdos
string function Get_Info_String(doticu_npcp_member ref_member)
    if !ref_member
        return ""
    endIf

    Actor ref_actor = ref_member.Get_Actor()
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

    if ref_member.Get_Rating() > 0
        str_info += "Rating: " + ref_member.Get_Rating_Stars()
    endIf

    ; this should show more about the member, style, and stats!!!
    ; whether is dead, healthly, etc.

    return str_info
endFunction

; Private Methods
doticu_npcp_member function p_Get_Prev_Member(doticu_npcp_member ref_member)
    int idx_alias = p_arr_aliases.Find(ref_member as Alias)
    if idx_alias > -1
        if idx_alias == 0
            return p_arr_aliases[p_arr_aliases.length - 1] as doticu_npcp_member
        else
            return p_arr_aliases[idx_alias - 1] as doticu_npcp_member
        endIf
    else
        return p_arr_aliases[0] as doticu_npcp_member
    endIf
endFunction

doticu_npcp_member function p_Get_Next_Member(doticu_npcp_member ref_member)
    int idx_alias = p_arr_aliases.Find(ref_member as Alias)
    if idx_alias > -1
        if idx_alias == p_arr_aliases.length - 1
            return p_arr_aliases[0] as doticu_npcp_member
        else
            return p_arr_aliases[idx_alias + 1] as doticu_npcp_member
        endIf
    else
        return p_arr_aliases[p_arr_aliases.length - 1] as doticu_npcp_member
    endIf
endFunction

function p_Build_Members_Member()
    p_ref_member_members = p_ref_member
    MCM.MCM_MEMBER.f_View_Members_Member(p_ref_member)
    MCM.MCM_MEMBER.f_Build_Page()
endFunction

function p_Build_Filter_Members_Member()
    p_ref_member_filter_members = p_ref_member
    MCM.MCM_MEMBER.f_View_Filter_Members_Member(p_ref_member)
    MCM.MCM_MEMBER.f_Build_Page()
endFunction

function p_Go_Back()
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        MCM.MCM_FILTER.f_Review_Filter()
        MCM.ForcePageReset()
    endIf
endFunction

function p_View(Alias[] arr_aliases, int idx_page, doticu_npcp_member ref_member)
    p_arr_aliases = arr_aliases

    if !p_arr_aliases
        p_num_pages = 0
    else
        p_num_pages = Math.Ceiling(p_arr_aliases.length / (p_MEMBERS_PER_PAGE as float))
    endIf

    if idx_page >= p_num_pages || idx_page < 0
        p_idx_page = 0
    else
        p_idx_page = idx_page
    endIf
    
    if !p_arr_aliases
        p_arr_aliases_slice = p_arr_aliases
    else
        int idx_from = p_MEMBERS_PER_PAGE * p_idx_page
        int idx_to_ex = idx_from + p_MEMBERS_PER_PAGE
        p_arr_aliases_slice = doticu_npcp.Aliases_Slice(p_arr_aliases, idx_from, idx_to_ex)
    endIf

    p_ref_member = ref_member
endFunction

string function p_Format_Title(int num_members, int idx_page, int num_pages)
    string str_members = "Members: " + num_members + "/" + MEMBERS.Get_Limit()
    string str_pages = "Page: " + (idx_page + 1) + "/" + num_pages

    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        str_members = "Filtered " + str_members
    endIf

    return str_members + "               " + str_pages
endFunction

int function p_Get_Idx_Entity(int id_option)
    return id_option - p_options_offset - p_HEADERS_PER_PAGE
endFunction
