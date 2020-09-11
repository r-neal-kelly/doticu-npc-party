;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_actors extends Quest

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_player property PLAYER
    doticu_npcp_player function Get()
        return GetAliasByName("player") as doticu_npcp_player
    endFunction
endProperty
doticu_npcp_greeter property GREETER
    doticu_npcp_greeter function Get()
        return GetAliasByName("greeter") as doticu_npcp_greeter
    endFunction
endProperty
doticu_npcp_movee property MOVEE
    doticu_npcp_movee function Get()
        return GetAliasByName("movee") as doticu_npcp_movee
    endFunction
endProperty

; Private Variables
Actor   p_ref_menu  =  none

; Friend Methods
function f_Register()
    PLAYER.On_Register()
    if GREETER.Exists()
        GREETER.f_Register()
    endIf
    MOVEE.Register()
endFunction

; Public Methods
bool function Is_Vampire(Actor ref_actor)
    return ref_actor && ref_actor.HasKeyword(doticu_npcp_consts.Vampire_Keyword())
endFunction

function Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    if !ref_actor || !misc_token
        return
    endIf

    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token != count_token
        if curr_count_token > 0
            ref_actor.RemoveItem(misc_token, curr_count_token, true)
        endIf
        ref_actor.AddItem(misc_token, count_token, true)            
    endIf
endFunction

function Untoken(Actor ref_actor, MiscObject misc_token)
    if !ref_actor || !misc_token
        return
    endIf
    
    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token > 0
        ref_actor.RemoveItem(misc_token, curr_count_token, true)
    endIf
endFunction

function Move_To(ObjectReference ref_subject, ObjectReference ref_object, int distance = 120, int angle = 0)
    Actor ref_actor = ref_subject as Actor
    bool has_enabled_ai = ref_actor && ref_actor.IsAIEnabled()
    float object_angle_z = ref_object.GetAngleZ()

    if !has_enabled_ai
        ref_actor.EnableAI(true)
    endIf

    ref_subject.MoveTo(ref_object, distance * Math.Sin(object_angle_z - angle), distance * Math.Cos(object_angle_z - angle), 0.0)
    ref_subject.SetAngle(0.0, 0.0, object_angle_z - 180 - angle)

    if !has_enabled_ai
        ref_actor.EnableAI(false)
    endIf
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

function Greet_Player(Actor ref_actor);;;
    if !ref_actor
        return
    endIf

    if GREETER.Exists()
        GREETER.f_Destroy()
    endIf

    GREETER.f_Create(ref_actor)
endFunction

function Create_Menu();;;
    if p_ref_menu
        Destroy_Menu()
    endIf

    p_ref_menu = doticu_npcp_consts.Player_Actor().PlaceAtMe(doticu_npcp_consts.Menu_Actor_Base(), 1, false, true) as Actor
    FUNCS.ACTORS.Move_To(p_ref_menu, doticu_npcp_consts.Player_Actor())
    p_ref_menu.Enable()
endFunction

function Destroy_Menu()
    if !p_ref_menu
        return
    endIf

    p_ref_menu.Disable()
    p_ref_menu.Delete()
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
