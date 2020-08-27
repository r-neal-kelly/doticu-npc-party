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
bool                p_is_created    = false
Actor               p_ref_menu      =  none

; Friend Methods
function f_Create()
    p_is_created = true

    PLAYER.f_Create()
endFunction

function f_Destroy()
    if MOVEE.Exists()
        MOVEE.f_Destroy()
    endIf
    if GREETER.Exists()
        GREETER.f_Destroy()
    endIf
    PLAYER.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    PLAYER.f_Register()
    if GREETER.Exists()
        GREETER.f_Register()
    endIf
    if MOVEE.Exists()
        MOVEE.f_Register()
    endIf
endFunction

function f_Unregister()
    if MOVEE.Exists()
        MOVEE.f_Unregister()
    endIf
    if GREETER.Exists()
        GREETER.f_Unregister()
    endIf
    PLAYER.f_Unregister()
endFunction

; Public Methods
bool function Is_Alive(Actor ref_actor)
    return ref_actor && !ref_actor.IsDead()
endFunction

bool function Is_Dead(Actor ref_actor)
    return ref_actor && ref_actor.IsDead()
endFunction

bool function Is_Sleeping(Actor ref_actor)
    ; 0 Not Sleeping
    ; 2 Not Sleeping, Wants to Sleep
    ; 3 Sleeping
    ; 4 Sleeping, Wants to Wake
    return ref_actor && ref_actor.GetSleepState() == 3
endFunction

bool function Is_Leveled(Actor ref_actor)
    return ref_actor && ref_actor.GetLeveledActorBase() != ref_actor.GetActorBase()
endFunction

bool function Is_Vampire(Actor ref_actor)
    return ref_actor && ref_actor.HasKeyword(doticu_npcp_consts.Vampire_Keyword())
endFunction

bool function Is_Male(Actor ref_actor)
    return Get_Sex(ref_actor) == doticu_npcp_codes.SEX_MALE()
endFunction

bool function Is_Female(Actor ref_actor)
    return Get_Sex(ref_actor) == doticu_npcp_codes.SEX_FEMALE()
endFunction

bool function Is_Essential(Actor ref_actor)
    if Is_Leveled(ref_actor)
        return Get_Base(ref_actor).IsEssential() || Get_Leveled_Base(ref_actor).IsEssential()
    else
        return ref_actor.IsEssential()
    endIf
endFunction

ActorBase function Get_Base(Actor ref_actor); Get_Static_Base
    if ref_actor
        ; only returns a real or static leveled base, never a dynamic leveled base
        return ref_actor.GetActorBase()
    else
        return none
    endIf
endFunction

ActorBase function Get_Leveled_Base(Actor ref_actor); Get_Dynamic_Base
    if ref_actor
        ; only returns a real or dynamic leveled base, never a static leveled base
        return ref_actor.GetLeveledActorBase()
    else
        return none
    endIf
endFunction

string function Name(Actor ref_actor)
    if ref_actor
        return ref_actor.GetDisplayName()
    else
        return ""
    endIf
endFunction

int function Get_Sex(Actor ref_actor)
    if ref_actor
        return Get_Base(ref_actor).GetSex()
    else
        return 1234567
    endIf
endFunction

function Essentialize(Actor ref_actor)
    Get_Base(ref_actor).SetEssential(true)

    if Is_Leveled(ref_actor)
        Get_Leveled_Base(ref_actor).SetEssential(true)
    endIf
endFunction

function Unessentialize(Actor ref_actor)
    Get_Base(ref_actor).SetEssential(false)

    if Is_Leveled(ref_actor)
        Get_Leveled_Base(ref_actor).SetEssential(false)
    endIf
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

bool function Has_Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    return ref_actor && ref_actor.GetItemCount(misc_token) == count_token
endFunction

function Delete(Actor ref_actor)
    ref_actor.Disable()
    ref_actor.Delete()
endFunction

function Apply_Ability(Actor ref_actor, Spell ability)
    ; it's necessary to remove it before adding it back, because
    ; the engine simply will not do everything correctly otherwise
    ref_actor.RemoveSpell(ability)
    ref_actor.AddSpell(ability, false)
endFunction

function Unapply_Ability(Actor ref_actor, Spell ability)
    ref_actor.RemoveSpell(ability)
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
