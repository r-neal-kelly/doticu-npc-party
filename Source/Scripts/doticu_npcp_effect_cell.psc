;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_effect_cell extends ActiveMagicEffect

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty

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
