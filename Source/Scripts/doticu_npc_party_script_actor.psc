Scriptname doticu_npc_party_script_actor extends Quest

; Private Constants
doticu_npc_party_script_consts  CONSTS  = none
doticu_npc_party_script_codes   CODES   = none
doticu_npc_party_script_vars    VARS    = none
doticu_npc_party_script_mods    MODS    = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
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
bool function Is_Dead(Actor ref_actor)
    return ref_actor.IsDead()
endFunction

bool function Is_Unique(Actor ref_actor)
    return ref_actor.GetActorBase().IsUnique()
endFunction

bool function Is_Generic(Actor ref_actor)
    return !ref_actor.GetActorBase().IsUnique()
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

function Resurrect(Actor ref_actor)
    ref_actor.SetActorValue("Aggression", 0)
    ref_actor.Disable()
    ref_actor.Resurrect()
    ref_actor.Enable()
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
    Actor ref_clone = CONSTS.ACTOR_PLAYER.PlaceAtMe(ref_form, 1, true, true) as Actor; persist, disabled

    if Is_Generic(ref_actor)
        while !p_Has_Same_Head(ref_actor, ref_clone)
            ;ref_clone.SetCriticalStage(ref_clone.CritStage_DisintegrateEnd)
            ref_clone.Delete()
            ref_clone = CONSTS.ACTOR_PLAYER.PlaceAtMe(ref_form, 1, true, true) as Actor; persist, disabled
        endWhile
    endIf

    ref_clone.SetActorValue("Aggression", 0)
    ref_clone.Enable()
    Set_Name(ref_clone, "Clone of " + Get_Name(ref_actor))
    
    return ref_clone
endFunction

function Delete(Actor ref_actor)
    if Is_Generic(ref_actor)
        ;ref_actor.SetCriticalStage(ref_actor.CritStage_DisintegrateEnd)
        ref_actor.Disable()
        ref_actor.Delete()
    else
        ref_actor.Disable()
        ref_actor.Delete()
    endIf
endFunction

function Move_To(ObjectReference ref_subject, ObjectReference ref_object, int distance = 60, int angle = 0)
    ; angle 0 == front of ref_object
    float object_angle_z = ref_object.GetAngleZ()
    ref_subject.MoveTo(ref_object, distance * Math.Sin(object_angle_z - angle), distance * Math.Cos(object_angle_z - angle), 0.0)
    ref_subject.SetAngle(0.0, 0.0, object_angle_z - 180 + angle)
endFunction
