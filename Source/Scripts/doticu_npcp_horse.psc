;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_horse extends ReferenceAlias

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty

; Private Variables
Actor                   p_ref_actor     =  none
doticu_npcp_follower    p_ref_follower  =  none

; Native Method
Actor function Actor() native
string function Name() native

; Private Methods
function p_Enable();;;
    p_ref_actor.Enable()

    ; we need to support leveled bases (members) as opposed to real bases (clones) only
    ; because this takes an actor base, we can't specify a reference clone in this manner.
    ; so anything we can do to avoid the follower not being on the right horse is advisable
    p_ref_actor.SetActorOwner(ACTORS.Get_Leveled_Base(p_ref_follower.Actor()))
endFunction

function p_Disable();;;
    while doticu_npcp.Actor_Get_Mounted_Actor(p_ref_actor)
        FUNCS.Wait_Out_Of_Menu(1)
    endWhile
    p_ref_actor.Disable()
endFunction

; Public Methods
doticu_npcp_follower function Get_Follower()
    if p_ref_follower
        return p_ref_follower
    else
        return none
    endIf
endFunction

function Rename(string str_name)
    doticu_npcp.Funcs().Rename(p_ref_actor, str_name)
endFunction

; Events
event OnActivate(ObjectReference activator_obj)
    Actor activator_actor = activator_obj as Actor
    if activator_actor && p_ref_follower.Actor() == activator_actor
        (doticu_npcp_consts.Is_Saddler_Sitting_Globals_Formlist().GetAt(p_ref_follower.ID()) as GlobalVariable).SetValue(1)
        activator_actor.EvaluatePackage()
    endIf
endEvent
