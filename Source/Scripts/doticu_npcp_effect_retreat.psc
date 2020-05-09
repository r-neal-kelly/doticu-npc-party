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
    ; it's too unstable to rely on having magic effect as a condition, so this is a must
    if !CONSTS.ACTOR_PLAYER.IsSneaking()
        FOLLOWERS.Get_Follower(ref_target).Unretreat()
    endIf

    ; make sure ABILITY_SNEAK magic effect is primed
    ACTORS.Apply_Ability(ref_target, CONSTS.ABILITY_SNEAK)

    p_ref_actor = none
endEvent

event OnHit(ObjectReference ref_attacker, Form _, Projectile __, bool ___, bool ____, bool _____, bool ______)
    ACTORS.Pacify(p_ref_actor)
endEvent

; see OnEffectStart in doticu_npcp_effect_sneak
