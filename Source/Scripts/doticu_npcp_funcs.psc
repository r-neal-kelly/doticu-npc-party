; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_funcs extends Quest

; Modules
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return (self as Quest) as doticu_npcp_logs
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return (self as Quest) as doticu_npcp_actors
    endFunction
endProperty
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return (self as Quest) as doticu_npcp_npcs
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return (self as Quest) as doticu_npcp_mannequins
    endFunction
endProperty

; Friend Methods
function f_Create()
    LOGS.f_Create()
    NPCS.f_Initialize()
endFunction

function f_Destroy()
    NPCS.f_Uninitialize()
    LOGS.f_Destroy()
endFunction

function f_Register()
    LOGS.f_Register()
    ACTORS.f_Register()
endFunction

; Public Methods
function Close_Menus();;;
    while Utility.IsInMenuMode()
        Input.TapKey(Input.GetMappedKey("Tween Menu"))
    endWhile
endFunction

bool function Can_Use_Keys();;;
    return !Utility.IsInMenuMode() && !UI.IsMenuOpen("Dialogue Menu")
endFunction

function Wait(float seconds);;;
    Utility.WaitMenuMode(seconds)
endFunction

function Wait_Out_Of_Menu(float seconds);;;
    Utility.Wait(seconds)
endFunction

function Open_Container(ObjectReference ref_container);;;
    if ref_container
        ref_container.Activate(doticu_npcp_consts.Player_Actor())
        Wait_Out_Of_Menu(0.1)
    endIf
endFunction

function Essentialize(ActorBase base_actor);;;
    Wait(1); is this necessary?
    base_actor.SetEssential(true)
endFunction

function Protect(ActorBase base_actor);;;
    Wait(1); is this necessary?
    base_actor.SetProtected(true)
endFunction

Actor function Find_Closest_Actor_From(ObjectReference ref, float radius);;;
    return Game.FindClosestActorFromRef(ref, radius)
endFunction

ObjectReference function Current_Crosshair_Reference();;;
    return Game.GetCurrentCrosshairRef()
endFunction
