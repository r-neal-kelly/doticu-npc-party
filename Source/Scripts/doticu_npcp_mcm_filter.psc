Scriptname doticu_npcp_mcm_filter extends Quest

; Private Constants
doticu_npcp_mcm p_MCM   = none

; Private Variables

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_MCM = DATA.MODS.CONTROL.MCM
endFunction

function f_Initialize()
endFunction

function f_Register()
endFunction

function f_Build_Page()
endFunction

function f_On_Option_Select(int id_option)
endFunction

function f_On_Option_Menu_Open(int id_option)
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

function f_On_Option_Highlight(int id_option)
endFunction

; Private Methods
int function p_Get_Idx_Entity(int id_option)
endFunction

int function p_Get_Idx_Command(int id_option, int idx_entity)
endFunction

; Private States
auto state p_STATE_FILTER
    ; should be able to request an array with filter variables
    ; and maybe should cache it, but it gets complicated at that point
    ; but it's slow without it. there are options, but this will wait
endState
