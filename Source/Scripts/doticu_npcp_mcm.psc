Scriptname doticu_npcp_mcm extends SKI_ConfigBase

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_mcm_followers property MCM_FOLLOWERS
    doticu_npcp_mcm_followers function Get()
        return (self as Quest) as doticu_npcp_mcm_followers
    endFunction
endProperty
doticu_npcp_mcm_members property MCM_MEMBERS
    doticu_npcp_mcm_members function Get()
        return (self as Quest) as doticu_npcp_mcm_members
    endFunction
endProperty
doticu_npcp_mcm_filter property MCM_FILTER
    doticu_npcp_mcm_filter function Get()
        return (self as Quest) as doticu_npcp_mcm_filter
    endFunction
endProperty
doticu_npcp_mcm_settings property MCM_SETTINGS
    doticu_npcp_mcm_settings function Get()
        return (self as Quest) as doticu_npcp_mcm_settings
    endFunction
endProperty
doticu_npcp_mcm_log property MCM_LOG
    doticu_npcp_mcm_log function Get()
        return (self as Quest) as doticu_npcp_mcm_log
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

string              p_STR_DEFAULT   =    ""
string              p_STR_FOLLOWERS =    ""
string              p_STR_MEMBERS   =    ""
string              p_STR_FILTER    =    ""
string              p_STR_SETTINGS  =    ""
string              p_STR_LOG       =    ""

; Private Variables
bool                p_is_created    = false
string              p_str_curr_page =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_STR_DEFAULT   =             ""
    p_STR_FOLLOWERS = "   Followers"
    p_STR_MEMBERS   = "     Members"
    p_STR_FILTER    = "      Filter"
    p_STR_SETTINGS  = "    Settings"
    p_STR_LOG       = "         Log"

    p_is_created = true
    p_str_curr_page = p_STR_SETTINGS; or a help page? or a stats page?

    MCM_FOLLOWERS.f_Create(DATA)
    MCM_MEMBERS.f_Create(DATA)
    MCM_FILTER.f_Create(DATA)
    MCM_SETTINGS.f_Create(DATA)
    MCM_LOG.f_Create(DATA)
endFunction

function f_Destroy()
    MCM_LOG.f_Destroy()
    MCM_SETTINGS.f_Destroy()
    MCM_FILTER.f_Destroy()
    MCM_MEMBERS.f_Destroy()
    MCM_FOLLOWERS.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    MCM_FOLLOWERS.f_Register()
    MCM_MEMBERS.f_Register()
    MCM_FILTER.f_Register()
    MCM_SETTINGS.f_Register()
    MCM_LOG.f_Register()
endFunction

; Events
event OnConfigInit()
    ModName = " NPC Party"
endEvent

event OnConfigOpen()
    VARS.is_mcm_open = true

    Pages = Utility.CreateStringArray(5, "")
    Pages[0] = p_STR_FOLLOWERS
    Pages[1] = p_STR_MEMBERS
    Pages[2] = p_STR_FILTER
    Pages[3] = p_STR_SETTINGS
    Pages[4] = p_STR_LOG
endEvent

event OnConfigClose()
    VARS.is_mcm_open = false
endEvent

event OnPageReset(string str_page)
    string str_curr_page = str_page
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        p_str_curr_page = p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_Build_Page()
    elseIf str_curr_page == p_STR_MEMBERS
        p_str_curr_page = p_STR_MEMBERS
        MCM_MEMBERS.f_Build_Page()
    elseIf str_curr_page == p_STR_FILTER
        p_str_curr_page = p_STR_FILTER
        MCM_FILTER.f_Build_Page()
    elseIf str_curr_page == p_STR_SETTINGS
        p_str_curr_page = p_STR_SETTINGS
        MCM_SETTINGS.f_Build_Page()
    elseIf str_curr_page == p_STR_LOG
        p_str_curr_page = p_STR_LOG
        MCM_LOG.f_Build_Page()
    endIf
endEvent

event OnOptionSelect(int id_option)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Select(id_option)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Select(id_option)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Select(id_option)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Select(id_option)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Select(id_option)
    endIf
endEvent

event OnOptionMenuOpen(int id_option)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Menu_Open(id_option)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Menu_Open(id_option)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Menu_Open(id_option)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Menu_Open(id_option)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Menu_Open(id_option)
    endIf
endEvent

event OnOptionMenuAccept(int id_option, int idx_option)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endEvent

event OnOptionSliderOpen(int id_option)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Slider_Open(id_option)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Slider_Open(id_option)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Slider_Open(id_option)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Slider_Open(id_option)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Slider_Open(id_option)
    endIf
endEvent

event OnOptionSliderAccept(int id_option, float float_value)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endEvent

event OnOptionInputAccept(int id_option, string str_input)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf
    
    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Input_Accept(id_option, str_input)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endEvent

event OnOptionKeymapChange(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endEvent

event OnOptionHighlight(int id_option)
    string str_curr_page = CurrentPage
    if str_curr_page == p_STR_DEFAULT
        str_curr_page = p_str_curr_page
    endIf

    if str_curr_page == p_STR_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Highlight(id_option)
    elseIf str_curr_page == p_STR_MEMBERS
        MCM_MEMBERS.f_On_Option_Highlight(id_option)
    elseIf str_curr_page == p_STR_FILTER
        MCM_FILTER.f_On_Option_Highlight(id_option)
    elseIf str_curr_page == p_STR_SETTINGS
        MCM_SETTINGS.f_On_Option_Highlight(id_option)
    elseIf str_curr_page == p_STR_LOG
        MCM_LOG.f_On_Option_Highlight(id_option)
    endIf
endEvent
