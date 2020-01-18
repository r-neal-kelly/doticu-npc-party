Scriptname doticu_npcp_effect_cell extends ActiveMagicEffect

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
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
doticu_npcp_data    p_DATA  =  none

; Private Methods
function p_Create()
    Cell cell_new = CONSTS.ACTOR_PLAYER.GetParentCell()
    Cell cell_old = CONSTS.MARKER_CELL.GetParentCell()

    Utility.Wait(0.01)
    CONSTS.MARKER_CELL.MoveTo(CONSTS.ACTOR_PLAYER)

    while !p_Send_Cell_Change(cell_new, cell_old)
        Utility.Wait(0.1)
    endWhile
endFunction

function p_Destroy()
endFunction

bool function p_Send_Cell_Change(Cell cell_new, Cell cell_old)
    int handle = ModEvent.Create("doticu_npcp_cell_change")

    if !handle
        return false
    endIf

    ModEvent.PushForm(handle, cell_new as Form)
    ModEvent.PushForm(handle, cell_old as Form)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Events
event OnEffectStart(Actor ref_target, Actor ref_caster)
    p_Create()
endEvent

event OnEffectFinish(Actor ref_target, Actor ref_caster)
    p_Destroy()
endEvent
