Scriptname doticu_npc_party_script_funcs extends Quest

; Private Constants
doticu_npc_party_script_actor p_ACTOR2 = none

; Public Constants
doticu_npc_party_script_actor property ACTOR2
    doticu_npc_party_script_actor function Get()
        return p_ACTOR2
    endFunction
endProperty

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_ACTOR2 = (self as Quest) as doticu_npc_party_script_actor

    p_ACTOR2.f_Initialize(DATA)
endFunction

; Public Methods
function Close_Menus()
    int key_menu = Input.GetMappedKey("Tween Menu")
    
    while Utility.IsInMenuMode()
        Input.TapKey(key_menu)
    endWhile
endFunction
