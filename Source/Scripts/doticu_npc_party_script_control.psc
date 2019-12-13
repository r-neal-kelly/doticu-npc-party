Scriptname doticu_npc_party_script_control extends Quest

; Private Constants
doticu_npc_party_script_commands    p_COMMANDS  = none
doticu_npc_party_script_keys        p_KEYS      = none
doticu_npc_party_script_mcm         p_MCM       = none
doticu_npc_party_script_greeter     p_GREETER   = none

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

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_COMMANDS = (self as Quest) as doticu_npc_party_script_commands
    p_KEYS = (self as Quest) as doticu_npc_party_script_keys
    p_MCM = (self as Quest) as doticu_npc_party_script_mcm
    p_GREETER = GetAliasByName("Greeter") as doticu_npc_party_script_greeter

    p_COMMANDS.f_Initialize(DATA)
    p_KEYS.f_Initialize(DATA)
    p_MCM.f_Initialize(DATA)
    p_Greeter.f_Initialize(DATA)
endFunction

; Public Methods
function Greet_Player(Actor ref_actor)
    p_GREETER.f_Create(ref_actor)
endFunction
