; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_funcs extends Quest

; replace these with direct callbacks in c++

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

function Stop_If_Playing_Music(Actor ref_actor);;;
    BardSongsScript script = doticu_npcp_consts.Bard_Songs_Quest() as BardSongsScript

    if script.BardSongs_Bard.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongs_Bard.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
    elseIf script.BardSongs_Bard2.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongs_Bard2.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
    elseIf script.BardSongsInstrumental_Bard.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongsInstrumental_Bard.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
    elseIf script.BardSongsInstrumental_Bard2.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongsInstrumental_Bard2.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
    endIf
endFunction
