Scriptname doticu_npc_party_script_data extends Quest

; Private Constants
doticu_npc_party_script_consts  p_CONSTS    = none
doticu_npc_party_script_codes   p_CODES     = none
doticu_npc_party_script_vars    p_VARS      = none
doticu_npc_party_script_mods    p_MODS      = none

; Public Constants
doticu_npc_party_script_consts property CONSTS
    doticu_npc_party_script_consts function Get()
        return p_CONSTS
    endFunction
endProperty

doticu_npc_party_script_codes property CODES
    doticu_npc_party_script_codes function Get()
        return p_CODES
    endFunction
endProperty

doticu_npc_party_script_vars property VARS
    doticu_npc_party_script_vars function Get()
        return p_VARS
    endFunction
endProperty

doticu_npc_party_script_mods property MODS
    doticu_npc_party_script_mods function Get()
        return p_MODS
    endFunction
endProperty

; Friend Methods
function f_Initialize()
    p_CONSTS = (self as Quest) as doticu_npc_party_script_consts
    p_CODES = (self as Quest) as doticu_npc_party_script_codes
    p_VARS = (self as Quest) as doticu_npc_party_script_vars
    p_MODS = (self as Quest) as doticu_npc_party_script_mods

    p_VARS.f_Initialize(self)
endFunction

function f_Register()
endFunction
