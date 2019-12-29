Scriptname doticu_npcp_mcm extends SKI_ConfigBase

; Private Constants
doticu_npcp_vars            p_VARS          = none
doticu_npcp_mcm_followers   p_MCM_FOLLOWERS = none
doticu_npcp_mcm_members     p_MCM_MEMBERS   = none
doticu_npcp_mcm_filter      p_MCM_FILTER    = none
doticu_npcp_mcm_settings    p_MCM_SETTINGS  = none
doticu_npcp_mcm_log         p_MCM_LOG       = none

string                      p_STR_FOLLOWERS =   ""
string                      p_STR_MEMBERS   =   ""
string                      p_STR_FILTER    =   ""
string                      p_STR_SETTINGS  =   ""
string                      p_STR_LOG       =   ""

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_VARS = DATA.VARS
    p_MCM_FOLLOWERS = (self as Quest) as doticu_npcp_mcm_followers
    p_MCM_MEMBERS = (self as Quest) as doticu_npcp_mcm_members
    p_MCM_FILTER = (self as Quest) as doticu_npcp_mcm_filter
    p_MCM_SETTINGS = (self as Quest) as doticu_npcp_mcm_settings
    p_MCM_LOG = (self as Quest) as doticu_npcp_mcm_log

    p_MCM_FOLLOWERS.f_Link(DATA)
    p_MCM_MEMBERS.f_Link(DATA)
    p_MCM_FILTER.f_Link(DATA)
    p_MCM_SETTINGS.f_Link(DATA)
    p_MCM_LOG.f_Link(DATA)
endFunction

function f_Initialize()
    p_STR_FOLLOWERS = "   Followers"
    p_STR_MEMBERS   = "     Members"
    p_STR_FILTER    = "      Filter"
    p_STR_SETTINGS  = "    Settings"
    p_STR_LOG       = "         Log"

    p_MCM_FOLLOWERS.f_Initialize()
    p_MCM_MEMBERS.f_Initialize()
    p_MCM_FILTER.f_Initialize()
    p_MCM_SETTINGS.f_Initialize()
    p_MCM_LOG.f_Initialize()
endFunction

function f_Register()
    p_MCM_FOLLOWERS.f_Register()
    p_MCM_MEMBERS.f_Register()
    p_MCM_FILTER.f_Register()
    p_MCM_SETTINGS.f_Register()
    p_MCM_LOG.f_Register()
endFunction

; Events
event OnConfigOpen()
    p_VARS.is_mcm_open = true

    Pages = Utility.CreateStringArray(5, "")
    Pages[0] = p_STR_FOLLOWERS
    Pages[1] = p_STR_MEMBERS
    Pages[2] = p_STR_FILTER
    Pages[3] = p_STR_SETTINGS
    Pages[4] = p_STR_LOG
endEvent

event OnConfigClose()
    p_VARS.is_mcm_open = false
endEvent

event OnPageReset(string str_page)
    if str_page == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_Build_Page()
    elseIf str_page == p_STR_MEMBERS
        p_MCM_MEMBERS.f_Build_Page()
    elseIf str_page == p_STR_FILTER
        p_MCM_FILTER.f_Build_Page()
    elseIf str_page == p_STR_SETTINGS
        p_MCM_SETTINGS.f_Build_Page()
    elseIf str_page == p_STR_LOG
        p_MCM_LOG.f_Build_Page()
    endIf
endEvent

event OnOptionSelect(int id_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Select(id_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Select(id_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Select(id_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Select(id_option)
    elseIf CurrentPage == p_STR_LOG
        p_MCM_LOG.f_On_Option_Select(id_option)
    endIf
endEvent

event OnOptionMenuOpen(int id_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Menu_Open(id_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Menu_Open(id_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Menu_Open(id_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Menu_Open(id_option)
    elseIf CurrentPage == p_STR_LOG
        p_MCM_LOG.f_On_Option_Menu_Open(id_option)
    endIf
endEvent

event OnOptionMenuAccept(int id_option, int idx_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf CurrentPage == p_STR_LOG
        p_MCM_LOG.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endEvent

event OnOptionInputAccept(int id_option, string str_input)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Input_Accept(id_option, str_input)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf CurrentPage == p_STR_LOG
        p_MCM_LOG.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endEvent

event OnOptionKeymapChange(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf CurrentPage == p_STR_LOG
        p_MCM_LOG.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endEvent

event OnOptionHighlight(int id_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Highlight(id_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Highlight(id_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Highlight(id_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Highlight(id_option)
    elseIf CurrentPage == p_STR_LOG
        p_MCM_LOG.f_On_Option_Highlight(id_option)
    endIf
endEvent
