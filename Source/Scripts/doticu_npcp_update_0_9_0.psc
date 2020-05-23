;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_update_0_9_0 extends Quest

; Modules
doticu_npcp_main property MAIN hidden
    doticu_npcp_main function Get()
        return p_DATA.MODS.MAIN
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_player property PLAYER hidden
    doticu_npcp_player function Get()
        return p_DATA.MODS.FUNCS.ACTORS.PLAYER
    endFunction
endProperty

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

; Private Constants
doticu_npcp_data p_DATA =  none

; Events
event OnInit()
    ; we don't want to init in this thread because
    ; it may not complete the procedures.
    RegisterForSingleUpdate(0.01)
endEvent

event OnUpdate()
    FUNCS.Wait(5)

    if !MAIN.WILL_INIT_OR_LOAD_0_9_0 && MAIN.Is_NPC_Party_Version_Less_Than(0, 9, 0)
        PLAYER.OnPlayerLoadGame()
    endIf
endEvent
