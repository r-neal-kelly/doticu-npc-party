Scriptname doticu_npcp_perk_kill extends Perk hidden

; Private Constants
doticu_npcp_data    p_DATA          = none
doticu_npcp_perks   p_PERKS         = none

Actor               p_REF_PLAYER    = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_DATA = DATA
    p_PERKS = DATA.MODS.FUNCS.PERKS

    p_REF_PLAYER = DATA.CONSTS.ACTOR_PLAYER
endFunction

function f_Register()
endFunction

; Public Methods
function Kill_Essential(ObjectReference ref_target, Actor ref_actor)
    Debug.Notification("In Kill_Essential: " + (p_DATA != none))
endFunction
