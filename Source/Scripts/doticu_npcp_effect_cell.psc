;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_effect_cell extends ActiveMagicEffect

; Modules
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
doticu_npcp_data p_DATA = none

; Private Methods
function p_Create()
    Cell cell_new = doticu_npcp_consts.Player_Actor().GetParentCell()
    Cell cell_old = doticu_npcp_consts.Cell_Marker().GetParentCell()

    FUNCS.Wait(0.01)
    doticu_npcp_consts.Cell_Marker().MoveTo(doticu_npcp_consts.Player_Actor())

    p_Send_Cell_Change(cell_new, cell_old)
endFunction

function p_Destroy()
endFunction

function p_Send_Cell_Change(Cell cell_new, Cell cell_old)
    int handle = FUNCS.Get_Event_Handle("doticu_npcp_cell_change")
    if !handle
        return
    endIf

    ModEvent.PushForm(handle, cell_new as Form)
    ModEvent.PushForm(handle, cell_old as Form)

    FUNCS.Send_Event_Handle(handle)
endFunction

; Events
event OnEffectStart(Actor ref_target, Actor ref_caster)
    p_Create()
endEvent

event OnEffectFinish(Actor ref_target, Actor ref_caster)
    p_Destroy()
endEvent
