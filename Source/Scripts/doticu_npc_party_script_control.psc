Scriptname doticu_npc_party_script_control extends Quest

; Private Constants
doticu_npc_party_script_commands    p_COMMANDS  = none
doticu_npc_party_script_keys        p_KEYS      = none
doticu_npc_party_script_mcm         p_MCM       = none
doticu_npc_party_script_player      p_PLAYER    = none

; Public Constants
doticu_npc_party_script_commands property COMMANDS
    doticu_npc_party_script_commands function Get()
        return p_COMMANDS
    endFunction
endProperty

doticu_npc_party_script_keys property KEYS
    doticu_npc_party_script_keys function Get()
        return p_KEYS
    endFunction
endProperty

doticu_npc_party_script_mcm property MCM
    doticu_npc_party_script_mcm function Get()
        return p_MCM
    endFunction
endProperty

doticu_npc_party_script_player property PLAYER
    doticu_npc_party_script_player function Get()
        return p_PLAYER
    endFunction
endProperty

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_COMMANDS = (self as Quest) as doticu_npc_party_script_commands
    p_KEYS = (self as Quest) as doticu_npc_party_script_keys
    p_MCM = (self as Quest) as doticu_npc_party_script_mcm
    p_PLAYER = GetAliasByName("PlayerAlias") as doticu_npc_party_script_player

    p_COMMANDS.f_Initialize(DATA)
    p_KEYS.f_Initialize(DATA)
    p_MCM.f_Initialize(DATA)
    p_PLAYER.f_Initialize(DATA)
endFunction
