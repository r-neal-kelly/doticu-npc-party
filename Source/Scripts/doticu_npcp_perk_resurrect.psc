Scriptname doticu_npcp_perk_resurrect extends Perk hidden

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
doticu_npcp_perks property PERKS hidden
    doticu_npcp_perks function Get()
        return p_DATA.MODS.FUNCS.PERKS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          = none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

; Public Methods
function Resurrect_Member(ObjectReference ref_target, Actor _)
    Actor ref_actor = ref_target as Actor

    if !ref_actor
        return
    endIf

    ACTORS.Resurrect(ref_actor)
endFunction
