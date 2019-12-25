Scriptname doticu_npcp_perk_resurrect extends Perk hidden

; Private Constants
doticu_npcp_consts  p_CONSTS        = none
doticu_npcp_actors  p_ACTORS        = none
doticu_npcp_perks   p_PERKS         = none

Actor               p_REF_PLAYER    = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_PERKS = DATA.MODS.FUNCS.PERKS
endFunction

function f_Initialize()
    p_REF_PLAYER = p_CONSTS.ACTOR_PLAYER
endFunction

function f_Register()
endFunction

; Public Methods
function Resurrect_Member(ObjectReference ref_target, Actor _)
    Actor ref_actor = ref_target as Actor

    if !ref_actor
        return
    endIf

    p_ACTORS.Resurrect(ref_actor)
endFunction
