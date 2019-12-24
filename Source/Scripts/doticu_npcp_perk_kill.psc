Scriptname doticu_npcp_perk_kill extends Perk hidden

; Private Constants
doticu_npcp_consts  p_CONSTS        = none
doticu_npcp_perks   p_PERKS         = none

Actor               p_REF_PLAYER    = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_PERKS = DATA.MODS.FUNCS.PERKS
endFunction

function f_Initialize()
    p_REF_PLAYER = p_CONSTS.ACTOR_PLAYER
endFunction

function f_Register()
endFunction

; Public Methods
function Kill_Essential(ObjectReference ref_target, Actor _)
endFunction

; Update Methods
function u_0_1_0()
endFunction
