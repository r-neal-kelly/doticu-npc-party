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

string function Get_Base_Name(Actor ref_actor)
    if ref_actor
        return ref_actor.GetName()
    else
        return ""
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
