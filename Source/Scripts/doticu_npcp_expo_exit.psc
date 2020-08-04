;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_expo_exit extends ObjectReference

; Modules
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return p_DATA.MODS.FUNCS.MANNEQUINS
    endFunction
endProperty

; Private Constants
doticu_npcp_data p_DATA = none

; Public Constants
doticu_npcp_data property DATA
    doticu_npcp_data function Get()
        return p_DATA
    endFunction
    function Set(doticu_npcp_data val)
        if p_DATA == none
            p_DATA = val
        endIf
    endFunction
endProperty

; Events
event OnInit()
    SetDisplayName("Exit Expo")
endEvent

event OnOpen(ObjectReference ref_activator)
    if ref_activator != doticu_npcp_consts.Player_Actor()
        return
    endIf

    GotoState("STATE_BUSY")
    MANNEQUINS.Remove_Player()
    SetOpen(false)
    GotoState("")
endEvent

; States
state STATE_BUSY
    event OnOpen(ObjectReference ref_activator)
    endEvent
endState
