Scriptname doticu_npc_party_script_mcm_settings extends Quest

; Private Constants
doticu_npc_Party_script_mcm p_MCM = none

; Private Variables

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_MCM = DATA.MODS.CONTROL.MCM
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
auto state p_STATE_SETTINGS
    ; should have a way to bind all keys
    ; should have toggles for global vars
    ; confer with doticu_npc_party_script_vars
endState
