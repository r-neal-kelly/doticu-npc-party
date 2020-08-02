;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_effect_retreat extends ActiveMagicEffect

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
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

; Private Variables
Actor p_ref_actor =  none

; Events
event OnEffectStart(Actor ref_target, Actor ref_caster)
    p_ref_actor = ref_target
    ACTORS.Pacify(p_ref_actor)
endEvent

event OnEffectFinish(Actor ref_target, Actor ref_caster)
    ; just in case there is a false finish
    if !doticu_npcp_consts.Player_Actor().IsSneaking()
        FOLLOWERS.Get_Follower(ref_target).Unretreat()
    else
        FOLLOWERS.Get_Follower(ref_target).Retreat()
    endIf

    p_ref_actor = none
endEvent

event OnCombatStateChanged(Actor ref_target, int code_combat)
    p_ref_actor.StopCombatAlarm()
endEvent
