; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_actors extends Quest

function f_Register()
    (GetAliasByName("player") as doticu_npcp_player).On_Register()
    (GetAliasByName("movee") as doticu_npcp_movee).Register()
endFunction

bool function Is_Vampire(Actor ref_actor)
    return ref_actor && ref_actor.HasKeyword(doticu_npcp_consts.Vampire_Keyword())
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

function Pacify(Actor ref_actor)
    if !ref_actor
        return
    endIf

    ref_actor.SetActorValue("Aggression", 0)
    ref_actor.StopCombat()
    ref_actor.StopCombatAlarm()
    ref_actor.EvaluatePackage()
endFunction
