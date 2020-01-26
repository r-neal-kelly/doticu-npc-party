;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm extends SKI_ConfigBase

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_keys property KEYS hidden
    doticu_npcp_keys function Get()
        return p_DATA.MODS.CONTROL.KEYS
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
doticu_npcp_mcm_member property MCM_MEMBER
    doticu_npcp_mcm_member function Get()
        return (self as Quest) as doticu_npcp_mcm_member
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

; Public Constants
string property PAGE_FOLLOWERS hidden
    string function Get()
        return " Followers "
    endFunction
endProperty
string property PAGE_MEMBERS hidden
    string function Get()
        return " Members "
    endFunction
endProperty
string property PAGE_FILTER hidden
    string function Get()
        return " Filter "
    endFunction
endProperty
string property PAGE_SETTINGS hidden
    string function Get()
        return " Settings "
    endFunction
endProperty
string property PAGE_LOG hidden
    string function Get()
        return " Log "
    endFunction
endProperty
bool property DO_UPDATE hidden
    bool function Get()
        return false
    endFunction
endProperty
bool property DONT_UPDATE hidden
    bool function Get()
        return true
    endFunction
endProperty
int property FLAG_ENABLE hidden
    int function Get()
        return OPTION_FLAG_NONE
    endFunction
endProperty
int property FLAG_DISABLE hidden
    int function Get()
        return OPTION_FLAG_DISABLED
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA              =  none

; Private Variables
bool                p_is_created        = false
bool                p_is_custom_page    = false
string              p_str_def_page      =    ""
string              p_str_curr_page     =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_is_custom_page = false
    p_str_def_page = PAGE_SETTINGS; or a help page? or global stats page?
    p_str_curr_page = p_str_def_page

    MCM_FOLLOWERS.f_Create(DATA)
    MCM_MEMBERS.f_Create(DATA)
    MCM_MEMBER.f_Create(DATA)
    MCM_FILTER.f_Create(DATA)
    MCM_SETTINGS.f_Create(DATA)
    MCM_LOG.f_Create(DATA)
endFunction

function f_Destroy()
    MCM_LOG.f_Destroy()
    MCM_SETTINGS.f_Destroy()
    MCM_FILTER.f_Destroy()
    MCM_MEMBER.f_Destroy()
    MCM_MEMBERS.f_Destroy()
    MCM_FOLLOWERS.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    MCM_FOLLOWERS.f_Register()
    MCM_MEMBERS.f_Register()
    MCM_MEMBER.f_Register()
    MCM_FILTER.f_Register()
    MCM_SETTINGS.f_Register()
    MCM_LOG.f_Register()
endFunction

function f_Unregister()
    MCM_LOG.f_Unregister()
    MCM_SETTINGS.f_Unregister()
    MCM_FILTER.f_Unregister()
    MCM_MEMBER.f_Unregister()
    MCM_MEMBERS.f_Unregister()
    MCM_FOLLOWERS.f_Unregister()
endFunction

function f_Change_Page(string str_page)
    p_str_curr_page = str_page
    p_is_custom_page = true
    ForcePageReset()
endFunction

string function f_Get_Current_Page()
    return p_str_curr_page
endFunction

function f_Enable(int id_option, bool bool_update)
    SetOptionFlags(id_option, FLAG_ENABLE, bool_update)
endFunction

function f_Disable(int id_option, bool bool_update)
    SetOptionFlags(id_option, FLAG_DISABLE, bool_update)
endFunction

; Public Methods
string function GetCustomControl(int code_key)
    ; even though this is overridden, MCM will still return lower conflicts
    return KEYS.Get_Control(code_key)
endFunction

; Events
event OnConfigInit()
    ModName = " NPC Party"
endEvent

event OnConfigOpen()
    VARS.is_mcm_open = true

    Pages = Utility.CreateStringArray(4, "")
    Pages[0] = PAGE_FOLLOWERS
    Pages[1] = PAGE_MEMBERS
    ;Pages[2] = PAGE_FILTER
    Pages[2] = PAGE_SETTINGS
    Pages[3] = PAGE_LOG
endEvent

event OnConfigClose()
    VARS.is_mcm_open = false
endEvent

event OnPageReset(string str_page)
    if str_page == ""
        ; open the last viewed page rather than a blank one
        str_page = p_str_curr_page
    endIf

    if p_is_custom_page
        str_page = p_str_curr_page
        p_is_custom_page = false
    endIf

    if str_page == PAGE_FOLLOWERS
        p_str_curr_page = str_page
        MCM_FOLLOWERS.f_Build_Page()
    elseIf str_page == PAGE_MEMBERS
        p_str_curr_page = str_page
        MCM_MEMBERS.f_Build_Page()
    elseIf str_page == PAGE_FILTER
        p_str_curr_page = str_page
        MCM_FILTER.f_Build_Page()
    elseIf str_page == PAGE_SETTINGS
        p_str_curr_page = str_page
        MCM_SETTINGS.f_Build_Page()
    elseIf str_page == PAGE_LOG
        p_str_curr_page = str_page
        MCM_LOG.f_Build_Page()
    else
        p_str_curr_page = p_str_def_page
        ForcePageReset()
    endIf
endEvent

event OnOptionSelect(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Select(id_option)
    endIf
endEvent

event OnOptionMenuOpen(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Menu_Open(id_option)
    endIf
endEvent

event OnOptionMenuAccept(int id_option, int idx_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endEvent

event OnOptionSliderOpen(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Slider_Open(id_option)
    endIf
endEvent

event OnOptionSliderAccept(int id_option, float float_value)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endEvent

event OnOptionInputAccept(int id_option, string str_input)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endEvent

event OnOptionKeymapChange(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endEvent

event OnOptionDefault(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Default(id_option)
    endIf
endEvent

event OnOptionHighlight(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Highlight(id_option)
    endIf
endEvent
