Scriptname doticu_npcp_actor extends Quest

; doticu_npcp_actors ?

; Private Constants
doticu_npcp_consts      p_CONSTS        = none
doticu_npcp_codes       p_CODES         = none
doticu_npcp_funcs       p_FUNCS         = none
doticu_npcp_container   p_CONTAINER2    = none
doticu_npcp_outfits     p_OUTFITS       = none
doticu_npcp_greeter     p_GREETER       = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_FUNCS = DATA.MODS.FUNCS
    p_CONTAINER2 = DATA.MODS.FUNCS.CONTAINER2
    p_OUTFITS = DATA.MODS.FUNCS.OUTFITS
    p_GREETER = GetAliasByName("greeter") as doticu_npcp_greeter

    p_Greeter.f_Initialize(DATA)
endFunction

function f_Register()
endFunction

; Private Methods
bool function p_Has_Same_Head(Actor ref_actor_1, Actor ref_actor_2)
    ActorBase ref_base_1 = ref_actor_1.GetLeveledActorBase(); returns unleveled base too
    ActorBase ref_base_2 = ref_actor_2.GetLeveledActorBase()
    int int_slots_1 = ref_base_1.GetNumHeadParts()
    int int_slots_2 = ref_base_2.GetNumHeadParts()

    if int_slots_1 != int_slots_2
        return false
    endIf

    int int_slot_idx = 0
    while int_slot_idx < int_slots_1
        if ref_base_1.GetNthHeadPart(int_slot_idx) != ref_base_2.GetNthHeadPart(int_slot_idx)
            return false
        endIf
        int_slot_idx += 1
    endWhile

    return true
endFunction

; Public Methods
bool function Is_Alive(Actor ref_actor)
    return !ref_actor.IsDead()
endFunction

bool function Is_Dead(Actor ref_actor)
    return ref_actor.IsDead()
endFunction

bool function Is_Sleeping(Actor ref_actor)
    ; 0 Not Sleeping
    ; 2 Not Sleeping, Wants to Sleep
    ; 3 Sleeping
    ; 4 Sleeping, Wants to Wake
    return ref_actor.GetSleepState() == 3
endFunction

bool function Is_Unique(Actor ref_actor)
    return ref_actor.GetActorBase().IsUnique()
endFunction

bool function Is_Generic(Actor ref_actor)
    return !ref_actor.GetActorBase().IsUnique()
endFunction

bool function Is_Vampire(Actor ref_actor)
    return ref_actor.HasKeyword(p_CONSTS.KEYWORD_VAMPIRE)
endFunction

ActorBase function Get_Base(Actor ref_actor)
    return ref_actor.GetActorBase()
endFunction

string function Get_Name(Actor ref_actor)
    if ref_actor
        return ref_actor.GetDisplayName()
    else
        return ""
    endIf
endFunction

function Set_Name(Actor ref_actor, string str_name)
    if ref_actor && str_name != ""
        ref_actor.SetDisplayName(str_name, true)
    endIf
endFunction

string function Get_Base_Name(Actor ref_actor)
    if ref_actor
        return ref_actor.GetName()
    else
        return ""
    endIf
endFunction

function Set_Base_Name(Actor ref_actor, string str_name)
    if ref_actor && str_name != ""
        ref_actor.SetDisplayName(str_name, true)
        ref_actor.SetName(str_name)
    endIf
endFunction

int function Get_Vitality(Actor ref_actor)
    ActorBase p_base_actor

    if Is_Unique(ref_actor)
        p_base_actor = ref_actor.GetActorBase()
    else
        p_base_actor = ref_actor.GetLeveledActorBAse()
    endIf

    if p_base_actor.IsProtected()
        return p_CODES.IS_PROTECTED
    elseIf p_base_actor.IsEssential()
        return p_CODES.IS_ESSENTIAL
    elseIf p_base_actor.IsInvulnerable()
        return p_CODES.IS_INVULNERABLE
    else
        return p_CODES.IS_MORTAL
    endIf
endFunction

function Vitalize(Actor ref_actor, int code_vitality)
    ; maybe we can do more to make this affect only instances, instead of base

    ActorBase p_base_actor = Get_Base(ref_actor)

    if code_vitality == p_CODES.IS_MORTAL
        p_base_actor.SetProtected(false)
        p_base_actor.SetEssential(false)
        p_base_actor.SetInvulnerable(false)
    elseIf code_vitality == p_CODES.IS_PROTECTED
        p_base_actor.SetProtected(true)
        p_base_actor.SetEssential(false)
        p_base_actor.SetInvulnerable(false)
    elseIf code_vitality == p_CODES.IS_ESSENTIAL
        p_base_actor.SetProtected(false)
        p_base_actor.SetEssential(true)
        p_base_actor.SetInvulnerable(false)
    elseIf code_vitality == p_CODES.IS_INVULNERABLE
        p_base_actor.SetProtected(false)
        p_base_actor.SetEssential(false)
        p_base_actor.SetInvulnerable(true)
    endIf
endFunction

function Resurrect(Actor ref_actor)
    ObjectReference ref_container = p_CONTAINER2.Create(p_CONSTS.CONTAINER_EMPTY, false)

    p_CONTAINER2.Take_All(ref_container, ref_actor)
    ref_actor.Disable()
    ref_actor.Resurrect()
    Pacify(ref_actor)
    ref_actor.Enable()
    p_CONTAINER2.Empty(ref_actor)
    p_CONTAINER2.Take_All(ref_actor, ref_container)
    Update_Equipment(ref_actor)
endFunction

function Open_Inventory(Actor ref_actor)
    ref_actor.OpenInventory(true)
endFunction

function Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token != count_token
        if curr_count_token > 0
            ref_actor.RemoveItem(misc_token, curr_count_token, true)
        endIf
        ref_actor.AddItem(misc_token, count_token, true)            
    endIf
endFunction

function Untoken(Actor ref_actor, MiscObject misc_token)
    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token > 0
        ref_actor.RemoveItem(misc_token, curr_count_token, true)
    endIf
endFunction

bool function Has_Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    return ref_actor.GetItemCount(misc_token) == count_token
endFunction

Actor function Clone(Actor ref_actor)
    Form ref_form = ref_actor.GetBaseObject() as Form
    Actor ref_clone = p_CONSTS.ACTOR_PLAYER.PlaceAtMe(ref_form, 1, true, false) as Actor; persist, disable

    if Is_Generic(ref_actor)
        while !p_Has_Same_Head(ref_actor, ref_clone); we may need to limit this to a couple hundred tries, because I ran into an infinite somehow. an unclonable?
            ref_clone.Disable()
            ref_clone.Delete()
            ref_clone = p_CONSTS.ACTOR_PLAYER.PlaceAtMe(ref_form, 1, true, false) as Actor; persist, disable
        endWhile
    endIf

    Pacify(ref_clone)
    Set_Name(ref_clone, "Clone of " + Get_Name(ref_actor))
    
    return ref_clone
endFunction

function Delete(Actor ref_actor)
    ref_actor.Disable()
    ref_actor.Delete()
endFunction

function Move_To(ObjectReference ref_subject, ObjectReference ref_object, int distance = 60, int angle = 0)
    ; angle 0 == front of ref_object
    float object_angle_z = ref_object.GetAngleZ()
    ref_subject.MoveTo(ref_object, distance * Math.Sin(object_angle_z - angle), distance * Math.Cos(object_angle_z - angle), 0.0)
    ref_subject.SetAngle(0.0, 0.0, object_angle_z - 180 + angle)
endFunction

function Greet_Player(Actor ref_actor)
    p_GREETER.f_Destroy()
    p_GREETER.f_Create(ref_actor)
endFunction

function Pacify(Actor ref_actor)
    ref_actor.SetActorValue("Aggression", 0)
    ref_actor.StopCombat()
    ref_actor.StopCombatAlarm()
    ref_actor.EvaluatePackage()
endFunction

function Ragdoll(Actor ref_actor)
    ; maybe should accept a timer, which can be done async or parallel
    ref_actor.SetActorValue("Paralysis", 1)
    p_CONSTS.ACTOR_PLAYER.PushActorAway(ref_actor, 0.0)
endFunction

function Unragdoll(Actor ref_actor)
    while ref_actor.GetActorValue("Paralysis") != 0
        ref_actor.SetActorValue("Paralysis", 0)
    endwhile
    ref_actor.EvaluatePackage()
endFunction

function Update_Equipment(Actor ref_actor)
    bool is_player_teammate = ref_actor.IsPlayerTeammate()
    
    if !is_player_teammate
        ref_actor.SetPlayerTeammate(true, true)
    endIf

    ref_actor.AddItem(p_CONSTS.WEAPON_BLANK, 1, true)
    ref_actor.RemoveItem(p_CONSTS.WEAPON_BLANK, 1, true, none)

    if !is_player_teammate
        ref_actor.SetPlayerTeammate(false, false)
    endIf
endFunction
