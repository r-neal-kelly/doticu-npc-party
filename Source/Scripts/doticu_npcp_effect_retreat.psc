;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_effect_retreat extends ActiveMagicEffect

; Modules
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return doticu_npcp.Followers()
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
