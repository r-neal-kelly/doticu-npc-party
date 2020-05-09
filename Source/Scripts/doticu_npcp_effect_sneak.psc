;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_effect_sneak extends ActiveMagicEffect

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

; Events
event OnEffectStart(Actor ref_target, Actor ref_caster)
    ; this effect is only called once upon magic effect condition, even though its spell is always on the alias
    FOLLOWERS.Get_Follower(ref_target).Retreat()
endEvent

; see OnEffectFinish in doticu_npcp_effect_retreat
