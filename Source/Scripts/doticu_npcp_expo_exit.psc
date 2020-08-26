;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_expo_exit extends ObjectReference

; Modules
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return doticu_npcp.Funcs().MANNEQUINS
    endFunction
endProperty

; Events
event OnInit()
    SetDisplayName("Exit Expo")
endEvent

event OnLoad()
    SetDisplayName("Exit Expo")
endEvent

event OnOpen(ObjectReference ref_activator)
    if ref_activator == doticu_npcp_consts.Player_Actor()
        GotoState("STATE_BUSY")
        MANNEQUINS.Remove_Player()
        SetOpen(false)
        GotoState("")
    endIf
endEvent

; States
state STATE_BUSY
    event OnOpen(ObjectReference ref_activator)
    endEvent
endState
