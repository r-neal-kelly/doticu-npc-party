Scriptname doticu_npc_party_script_main extends Quest

; Private Constants
doticu_npc_party_script_data p_DATA = none

; Public Constants
doticu_npc_party_script_data property DATA
    doticu_npc_party_script_data function Get()
        return p_DATA
    endFunction
    function Set(doticu_npc_party_script_data val)
        if p_DATA == none
            p_DATA = val
        endIf
    endFunction
endProperty

; Events
event OnInit()
    Utility.Wait(3)
    
    DATA.f_Initialize()
    DATA.MODS.FUNCS.f_Initialize(DATA)
    DATA.MODS.MEMBERS.f_Initialize(DATA)
    DATA.MODS.FOLLOWERS.f_Initialize(DATA)
    DATA.MODS.CONTROL.f_Initialize(DATA)
    
    DATA.MODS.FUNCS.LOGS.Create_Note("Thank you for installing!")
endEvent
