;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mannequin extends ObjectReference

; Modules
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return doticu_npcp.Funcs().MANNEQUINS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return doticu_npcp.Control().COMMANDS
    endFunction
endProperty

; Private Constants
ObjectReference     p_MARKER    = none
int                 p_ID        =   -1

; Public Constants
ObjectReference property MARKER
    ObjectReference function Get()
        return p_MARKER
    endFunction
    function Set(ObjectReference val)
        if p_MARKER == none
            p_MARKER = val
        endIf
    endFunction
endProperty

int property ID
    int function Get()
        return p_ID
    endFunction
    function Set(int val)
        if p_ID < 0
            p_ID = val
        endIf
    endFunction
endProperty

; Events
event OnActivate(ObjectReference ref_activator)
    if ref_activator != doticu_npcp_consts.Player_Actor()
        return
    endIf

    GotoState("STATE_BUSY")
    COMMANDS.Toggle_Expoee(ID, MARKER)
    GotoState("")
endEvent

; States
state STATE_BUSY
    event OnActivate(ObjectReference ref_activator)
    endEvent
endState
