;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_perk_unparalyze extends Perk hidden

; Modules
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
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

function f_Unregister()
endFunction

; Public Methods
function Unparalyze(ObjectReference ref_target, Actor _)
    Actor ref_actor = ref_target as Actor

    if !ref_actor
        return
    endIf

    if !MEMBERS.Has_Member(ref_actor)
        return
    endIf

    COMMANDS.Unparalyze(ref_actor, false)
endFunction
