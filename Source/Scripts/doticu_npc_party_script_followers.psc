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
        if code_return == CODES.HAS_ACTOR || code_return == CODES.HAS_ALIAS
            return CODES.HAS_FOLLOWER
        elseIf code_return == CODES.HASNT_SPACE
            return CODES.HASNT_SPACE_FOLLOWER
        else
            return code_return
        endIf
    endIf
    int id_alias = code_return

    code_return = p_Get_Follower(id_alias).Create()
    if code_return < 0
        ALIASES.Destroy_Alias(id_alias, ref_actor)
        return code_return
    endIf

    ; this value needs to be 1 whenever there is a follower
    ; because the engine won't update player teammates when 0
    CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)

    return CODES.SUCCESS
endFunction

int function Destroy_Follower(Actor ref_actor)
    int code_return

    int id_alias = p_Get_Alias_ID(ref_actor)
    if !ALIASES.Has_Alias(id_alias, ref_actor)
        return CODES.HASNT_FOLLOWER
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
        ; this would conflict with the vanilla system
        ; and any other mods that use it, except that we
        ; modify the vanilla system to force use of ours
        CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(0)
    endIf

    return CODES.SUCCESS
endFunction

int function Get_Count()
    return ALIASES.Get_Count()
endFunction

int function Get_Max()
    return ALIASES.Get_Max()
endFunction

bool function Has_Follower(Actor ref_actor)
    return ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

doticu_npc_party_script_follower function Get_Follower(Actor ref_actor)
    return ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npc_party_script_follower
endFunction

Alias[] function Get_Aliases_Sorted(int idx_from = 0, int idx_to_ex = -1)
    return ALIASES.Get_Aliases_Sorted(idx_from, idx_to_ex)
endFunction

function Summon()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    int angle_even = 0
    int angle_odd = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        if idx_arr % 2 == 0
            angle_even += 12
            ref_follower.Summon(120, angle_even)
        else
            angle_odd += 12
            ref_follower.Summon(120, angle_odd)
        endIf
        idx_arr += 1
    endWhile
endFunction

function Summon_Mobile()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    int angle_even = 0
    int angle_odd = 0
    bool do_even = true
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        if !ref_follower.Is_Immobile()
            if do_even
                angle_even += 12
                ref_follower.Summon(120, angle_even)
            else
                angle_odd += 12
                ref_follower.Summon(120, angle_odd)
            endIf
            do_even = !do_even
        endIf
        idx_arr += 1
    endWhile
endFunction

function Summon_Immobile()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    int angle_even = 0
    int angle_odd = 0
    bool do_even = true
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        if ref_follower.Is_Immobile()
            if do_even
                angle_even += 12
                ref_follower.Summon(120, angle_even)
            else
                angle_odd += 12
                ref_follower.Summon(120, angle_odd)
            endIf
            do_even = !do_even
        endIf
        idx_arr += 1
    endWhile
endFunction

function Settle()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        if ref_follower.Is_Settler()
            ref_follower.Get_Settler().Resettle()
        else
            ref_follower.Settle()
        endIf
        idx_arr += 1
    endWhile
endFunction

function Unsettle()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        ref_follower.Unsettle()
        idx_arr += 1
    endWhile
endFunction

function Immobilize()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        ref_follower.Immobilize()
        idx_arr += 1
    endWhile
endFunction

function Mobilize()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        ref_follower.Mobilize()
        idx_arr += 1
    endWhile
endFunction

function Sneak()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        ref_follower.Sneak()
        idx_arr += 1
    endWhile
endFunction

function Unsneak()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        ref_follower.Unsneak()
        idx_arr += 1
    endWhile
endFunction

function Unmember()
    doticu_npc_party_script_follower ref_follower
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npc_party_script_follower
        ref_follower.Unmember()
        idx_arr += 1
    endWhile
endFunction
