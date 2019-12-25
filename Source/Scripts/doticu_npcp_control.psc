Scriptname doticu_npcp_control extends Quest

; Private Constants
doticu_npcp_commands    p_COMMANDS  = none
doticu_npcp_keys        p_KEYS      = none
doticu_npcp_mcm         p_MCM       = none

; Public Constants
doticu_npcp_commands property COMMANDS
    doticu_npcp_commands function Get()
        return p_COMMANDS
    endFunction
endProperty

doticu_npcp_keys property KEYS
    doticu_npcp_keys function Get()
        return p_KEYS
    endFunction
endProperty

doticu_npcp_mcm property MCM
    doticu_npcp_mcm function Get()
        return p_MCM
    endFunction
endProperty

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_COMMANDS = (self as Quest) as doticu_npcp_commands
    p_KEYS = (self as Quest) as doticu_npcp_keys
    p_MCM = (self as Quest) as doticu_npcp_mcm

    p_COMMANDS.f_Link(DATA)
    p_KEYS.f_Link(DATA)
    p_MCM.f_Link(DATA)
endFunction

function f_Initialize()
    p_COMMANDS.f_Initialize()
    p_KEYS.f_Initialize()
    p_MCM.f_Initialize()
endFunction

function f_Register()
    p_COMMANDS.f_Register()
    p_KEYS.f_Register()
    p_MCM.f_Register()
endFunction
