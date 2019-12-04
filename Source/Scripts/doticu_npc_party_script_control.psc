Scriptname doticu_npc_party_script_control extends Quest

; Private Constants
doticu_npc_party_script_dialogue    p_DIALOGUE  = none
doticu_npc_party_script_keys        p_KEYS      = none
doticu_npc_party_script_mcm         p_MCM       = none

; Public Constants
doticu_npc_party_script_dialogue property DIALOGUE
    doticu_npc_party_script_dialogue function Get()
        return p_DIALOGUE
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

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_DIALOGUE = (self as Quest) as doticu_npc_party_script_dialogue
    p_KEYS = (self as Quest) as doticu_npc_party_script_keys
    p_MCM = (self as Quest) as doticu_npc_party_script_mcm

    p_DIALOGUE.f_Initialize(DATA)
    p_KEYS.f_Initialize(DATA)
endFunction
