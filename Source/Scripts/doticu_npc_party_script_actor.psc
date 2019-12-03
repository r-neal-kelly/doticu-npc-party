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

function Resurrect(Actor ref_actor)
    ref_actor.SetActorValue("Aggression", 0)
    ref_actor.Disable()
    ref_actor.Resurrect()
    ref_actor.Enable()
endFunction

function Token(Actor ref_actor, MiscObject misc_token)
    int count_token = ref_actor.GetItemCount(misc_token)
    if count_token < 1
        ref_actor.AddItem(misc_token, 1, true)            
    endIf
endFunction

function Untoken(Actor ref_actor, MiscObject misc_token)
    int count_token = ref_actor.GetItemCount(misc_token)
    if count_token > 0
        ref_actor.RemoveItem(misc_token, count_token, true)
    endIf
endFunction

bool function Has_Token(Actor ref_actor, MiscObject misc_token)
    return ref_actor.GetItemCount(misc_token) > 0
endFunction
