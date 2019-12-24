Scriptname doticu_npcp_followers extends Quest

; Private Constants
doticu_npcp_consts  p_CONSTS    = none
doticu_npcp_codes   p_CODES     = none
doticu_npcp_aliases p_ALIASES   = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_ALIASES = (self as Quest) as doticu_npcp_aliases

    p_ALIASES.f_Link(DATA)

    int idx_alias = 0
    int max_aliases = p_ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npcp_follower).f_Link(DATA)
        idx_alias += 1
    endWhile
endFunction

function f_Initialize()
    p_ALIASES.f_Initialize()

    int idx_alias = 0
    int max_aliases = p_ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npcp_follower).f_Initialize(idx_alias)
        idx_alias += 1
    endWhile
endFunction

function f_Register()
    p_ALIASES.f_Register()

    int idx_alias = 0
    int max_aliases = p_ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npcp_follower).f_Register()
        idx_alias += 1
    endWhile
endFunction

int function f_Create_Follower(Actor ref_actor)
    int code_return

    code_return = p_ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        if code_return == p_CODES.HAS_ACTOR || code_return == p_CODES.HAS_ALIAS
            return p_CODES.HAS_FOLLOWER
        elseIf code_return == p_CODES.HASNT_SPACE
            return p_CODES.HASNT_SPACE_FOLLOWER
        else
            return code_return
        endIf
    endIf
    int id_alias = code_return

    code_return = p_Get_Follower(id_alias).f_Create()
    if code_return < 0
        p_ALIASES.Destroy_Alias(id_alias, ref_actor)
        return code_return
    endIf

    ; this value needs to be 1 whenever there is a follower
    ; because the engine won't update player teammates when 0
    p_CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)

    return p_CODES.SUCCESS
endFunction

int function f_Destroy_Follower(Actor ref_actor)
    int code_return

    int id_alias = p_Get_Alias_ID(ref_actor)
    if !p_ALIASES.Has_Alias(id_alias, ref_actor)
        return p_CODES.HASNT_FOLLOWER
    endIf

    code_return = p_Get_Follower(id_alias).f_Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = p_ALIASES.Destroy_Alias(id_alias, ref_actor)
    if code_return < 0
        return code_return
    endIf

    if Get_Count() == 0
        ; this would conflict with the vanilla system
        ; and any other mods that use it, except that we
        ; modify the vanilla system to force use of ours
        p_CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(0)
    endIf

    return p_CODES.SUCCESS
endFunction

; Private Methods
int function p_Get_Alias_ID(Actor ref_actor)
    return ref_actor.GetItemCount(p_CONSTS.TOKEN_FOLLOWER) - 1
endFunction

doticu_npcp_follower function p_Get_Follower(int id_alias)
    return p_ALIASES.f_Get_Alias(id_alias) as doticu_npcp_follower
endFunction

; Public Methods
int function Get_Count()
    return p_ALIASES.Get_Count()
endFunction

int function Get_Max()
    return p_ALIASES.Get_Max()
endFunction

bool function Has_Follower(Actor ref_actor)
    return p_ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

doticu_npcp_follower function Get_Follower(Actor ref_actor)
    return p_ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_follower
endFunction

Alias[] function Get_Aliases_Sorted(int idx_from = 0, int idx_to_ex = -1)
    return p_ALIASES.Get_Aliases_Sorted(idx_from, idx_to_ex)
endFunction

function Enforce()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Get_Member().Enforce()
        idx_arr += 1
    endWhile
endFunction

function Summon()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    int angle_even = 0
    int angle_odd = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        if idx_arr % 2 == 0
            angle_even += 12
            ref_follower.Summon(120, angle_even)
        else
            angle_odd -= 12
            ref_follower.Summon(120, angle_odd)
        endIf
        idx_arr += 1
    endWhile
endFunction

function Summon_Mobile()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    int angle_even = 0
    int angle_odd = 0
    bool do_even = true
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        if !ref_follower.Is_Immobile()
            if do_even
                angle_even += 12
                ref_follower.Summon(120, angle_even)
            else
                angle_odd -= 12
                ref_follower.Summon(120, angle_odd)
            endIf
            do_even = !do_even
        endIf
        idx_arr += 1
    endWhile
endFunction

function Summon_Immobile()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    int angle_even = 0
    int angle_odd = 0
    bool do_even = true
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        if ref_follower.Is_Immobile()
            if do_even
                angle_even += 12
                ref_follower.Summon(120, angle_even)
            else
                angle_odd -= 12
                ref_follower.Summon(120, angle_odd)
            endIf
            do_even = !do_even
        endIf
        idx_arr += 1
    endWhile
endFunction

function Settle()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        if ref_follower.Is_Settler()
            ref_follower.Get_Settler().Resettle()
        else
            ref_follower.Settle()
        endIf
        idx_arr += 1
    endWhile
endFunction

function Unsettle()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Unsettle()
        idx_arr += 1
    endWhile
endFunction

function Immobilize()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Immobilize()
        idx_arr += 1
    endWhile
endFunction

function Mobilize()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Mobilize()
        idx_arr += 1
    endWhile
endFunction

function Sneak()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Sneak()
        idx_arr += 1
    endWhile
endFunction

function Unsneak()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Unsneak()
        idx_arr += 1
    endWhile
endFunction

function Unfollow()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Unfollow()
        idx_arr += 1
    endWhile
endFunction

function Unmember()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Unmember()
        idx_arr += 1
    endWhile
endFunction

function Resurrect()
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        if ref_follower.Is_Dead()
            ref_follower.Resurrect()
        endIf
        idx_arr += 1
    endWhile
endFunction

; Update Methods
function u_0_1_0()
    p_ALIASES.u_0_1_0()

    int idx_alias = 0
    int max_aliases = p_ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npcp_follower).u_0_1_0()
        idx_alias += 1
    endWhile
endFunction
