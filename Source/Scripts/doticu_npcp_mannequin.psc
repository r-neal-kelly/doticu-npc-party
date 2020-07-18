;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mannequin extends ObjectReference

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return p_DATA.MODS.FUNCS.MANNEQUINS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA      = none
ObjectReference     p_MARKER    = none
int                 p_ID        =   -1

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
    if ref_activator != CONSTS.ACTOR_PLAYER
        return
    endIf

    GotoState("STATE_BUSY")
    COMMANDS.Toggle_Expoee(ID, MARKER)
    GotoState("")
endEvent

event OnLoad()
    MANNEQUINS.Refresh_Mannequin(ID, MARKER)
endEvent

; States
state STATE_BUSY
    event OnActivate(ObjectReference ref_activator)
    endEvent
endState
