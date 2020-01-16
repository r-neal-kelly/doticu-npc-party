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
    Utility.Wait(0.01); is this really necessary? test.
    CONSTS.MARKER_CELL.MoveTo(CONSTS.ACTOR_PLAYER)
    PLAYER.On_Cell_Change(CONSTS.MARKER_CELL.GetParentCell())
endFunction

function p_Destroy()
endFunction

; Events
event OnEffectStart(Actor ref_target, Actor ref_caster)
    p_Create()
endEvent

event OnEffectFinish(Actor ref_target, Actor ref_caster)
    p_Destroy()
endEvent
