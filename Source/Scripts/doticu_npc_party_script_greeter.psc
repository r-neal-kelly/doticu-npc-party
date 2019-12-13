Scriptname doticu_npc_party_script_greeter extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts  p_CONSTS    = none
doticu_npc_party_script_actor   p_ACTOR2    = none

; Private Variable
Actor                           p_ref_actor = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CONSTS = DATA.CONSTS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
endFunction

function f_Create(Actor ref_actor)
    ForceRefTo(ref_actor)
    p_ref_actor = ref_actor
    p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_GREETER)
    ; token not even necessary? this is the only package that will run on this alias.
    RegisterForCrosshairRef()
endFunction

function f_Destroy()
    UnregisterForCrosshairRef()
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_GREETER)
    p_ref_actor = none
    Clear()
endFunction

; Events
event OnCrosshairRefChange(ObjectReference ref_target)
    if ref_target == p_ref_actor
        f_Destroy()
    endIf
endEvent
