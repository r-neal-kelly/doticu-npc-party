Scriptname doticu_npc_party_script_funcs extends Quest

; Private Constants
doticu_npc_party_script_consts      p_CONSTS        = none
doticu_npc_party_script_actor       p_ACTOR2        = none
doticu_npcp_outfit                  p_OUTFIT2       = none
doticu_npc_party_script_container   p_CONTAINER2    = none
doticu_npc_party_script_logs        p_LOGS          = none

; Public Constants
doticu_npc_party_script_actor property ACTOR2
    doticu_npc_party_script_actor function Get()
        return p_ACTOR2
    endFunction
endProperty

doticu_npcp_outfit property OUTFIT2
    doticu_npcp_outfit function Get()
        return p_OUTFIT2
    endFunction
endProperty

doticu_npc_party_script_container property CONTAINER2
    doticu_npc_party_script_container function Get()
        return p_CONTAINER2
    endFunction
endProperty

doticu_npc_party_script_logs property LOGS
    doticu_npc_party_script_logs function Get()
        return p_LOGS
    endFunction
endProperty

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CONSTS = DATA.CONSTS
    p_ACTOR2 = (self as Quest) as doticu_npc_party_script_actor
    p_OUTFIT2 = (self as Quest) as doticu_npcp_outfit
    p_CONTAINER2 = (self as Quest) as doticu_npc_party_script_container
    p_LOGS = (self as Quest) as doticu_npc_party_script_logs

    p_ACTOR2.f_Initialize(DATA)
    p_OUTFIT2.f_Initialize(DATA)
    p_CONTAINER2.f_Initialize(DATA)
    p_LOGS.f_Initialize(DATA)
endFunction

function f_Register()
    p_ACTOR2.f_Register()
    p_OUTFIT2.f_Register()
    p_CONTAINER2.f_Register()
    p_LOGS.f_Register()
endFunction

; Public Methods
function Close_Menus()
    int key_menu = Input.GetMappedKey("Tween Menu")
    
    while Utility.IsInMenuMode()
        Input.TapKey(key_menu)
    endWhile
endFunction

function Open_MCM()
    ; I have no good idea how to get this to happen!
endFunction

bool function Is_Mod_Installed(string name_mod)
    return Game.GetModByName(name_mod) != 255
endFunction
