Scriptname doticu_npc_party_script_followers extends Quest

; Private Constants
doticu_npc_party_script_consts  CONSTS  = none
doticu_npc_party_script_codes   CODES   = none
doticu_npc_party_script_vars    VARS    = none
doticu_npc_party_script_mods    MODS    = none
doticu_npc_party_script_aliases ALIASES = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ALIASES = (self as Quest) as doticu_npc_party_script_aliases

    ALIASES.f_Initialize(DATA)

    int idx_alias = 0
    int max_aliases = ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npc_party_script_follower).f_Initialize(DATA, idx_alias)
        idx_alias += 1
    endWhile
endFunction

; Private Methods
int function p_Get_Alias_ID(Actor ref_actor)
    return ref_actor.GetItemCount(CONSTS.TOKEN_FOLLOWER) - 1
endFunction

doticu_npc_party_script_follower function p_Get_Follower(int id_alias)
    return ALIASES.f_Get_Alias(id_alias) as doticu_npc_party_script_follower
endFunction

; Public Methods
int function Create_Follower(Actor ref_actor)
    int code_return

    code_return = ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_alias = code_return

    code_return = p_Get_Follower(id_alias).Create()
    if code_return < 0
        ALIASES.Destroy_Alias(id_alias, ref_actor)
        return code_return
    endIf

    CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)

    return CODES.SUCCESS
endFunction

int function Destroy_Follower(Actor ref_actor)
    int code_return

    int id_alias = p_Get_Alias_ID(ref_actor)
    if !ALIASES.Has_Alias(id_alias, ref_actor)
        return CODES.NO_FOLLOWER
    endIf

    code_return = p_Get_Follower(id_alias).Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = ALIASES.Destroy_Alias(id_alias, ref_actor)
    if code_return < 0
        return code_return
    endIf

    if Get_Count() == 0
        CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(0)
    endIf

    return CODES.SUCCESS
endFunction

int function Get_Count()
    return ALIASES.Get_Count()
endFunction

bool function Has_Follower(Actor ref_actor)
    return ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

doticu_npc_party_script_follower function Get_Follower(Actor ref_actor)
    if Has_Follower(ref_actor)
        return p_Get_Follower(p_Get_Alias_ID(ref_actor))
    endIf
endFunction
