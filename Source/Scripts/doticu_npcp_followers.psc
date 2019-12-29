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

    p_ALIASES.f_Link(DATA); p_ALIASES is not init'd!

    int idx_alias = 0
    int max_aliases = GetNumAliases()
    while idx_alias < max_aliases
        (GetNthAlias(idx_alias) as doticu_npcp_follower).f_Link(DATA)
        idx_alias += 1
    endWhile
endFunction

function f_Initialize()
    p_ALIASES.f_Initialize()

    int idx_alias = 0
    int max_aliases = GetNumAliases()
    while idx_alias < max_aliases
        (GetNthAlias(idx_alias) as doticu_npcp_follower).f_Initialize(idx_alias)
        idx_alias += 1
    endWhile
endFunction

function f_Register()
    p_ALIASES.f_Register()

    int idx_alias = 0
    int max_aliases = GetNumAliases()
    while idx_alias < max_aliases
        (GetNthAlias(idx_alias) as doticu_npcp_follower).f_Register()
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
    if !ref_actor
        return -1
    else
        return ref_actor.GetItemCount(p_CONSTS.TOKEN_FOLLOWER) - 1
    endIf
endFunction

doticu_npcp_follower function p_Get_Follower(int id_alias)
    return p_ALIASES.f_Get_Alias(id_alias) as doticu_npcp_follower
endFunction

bool function p_Send_Followers(string str_event)
    int handle = ModEvent.Create(str_event)

    if !handle
        return false
    endIf

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
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

bool function Has_One_Mobile()
    if Get_Count() < 1
        return false
    endIf

    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        if ref_follower.Is_Mobile()
            return true
        endIf
        idx_arr += 1
    endWhile

    return false
endFunction

bool function Has_One_Immobile()
    if Get_Count() < 1
        return false
    endIf

    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        if ref_follower.Is_Immobile()
            return true
        endIf
        idx_arr += 1
    endWhile

    return false
endFunction

doticu_npcp_follower function Get_Follower(Actor ref_actor)
    return p_ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_follower
endFunction

Alias[] function Get_Aliases_Sorted(int idx_from = 0, int idx_to_ex = -1)
    return p_ALIASES.Get_Aliases_Sorted(idx_from, idx_to_ex)
endFunction

function Enforce()
    ; this needs to be parallel
    doticu_npcp_follower ref_follower
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_follower = arr_aliases[idx_arr] as doticu_npcp_follower
        ref_follower.Get_Member().Enforce()
        idx_arr += 1
    endWhile
endFunction

int function Summon_All()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

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

    return p_CODES.SUCCESS
endFunction

int function Summon_Mobile()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if !Has_One_Mobile()
        return p_CODES.HASNT_MOBILE
    endIf

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

    return p_CODES.SUCCESS
endFunction

int function Summon_Immobile()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if !Has_One_Immobile()
        return p_CODES.HASNT_IMMOBILE
    endIf

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

    return p_CODES.SUCCESS
endFunction

function Settle()
    while !p_Send_Followers("doticu_npcp_followers_settle")
        Utility.Wait(0.25)
    endWhile
endFunction

function Unsettle()
    while !p_Send_Followers("doticu_npcp_followers_unsettle")
        Utility.Wait(0.25)
    endWhile
endFunction

function Immobilize()
    while !p_Send_Followers("doticu_npcp_followers_immobilize")
        Utility.Wait(0.25)
    endWhile
endFunction

function Mobilize()
    while !p_Send_Followers("doticu_npcp_followers_mobilize")
        Utility.Wait(0.25)
    endWhile
endFunction

function Sneak()
    while !p_Send_Followers("doticu_npcp_followers_sneak")
        Utility.Wait(0.25)
    endWhile
endFunction

function Unsneak()
    while !p_Send_Followers("doticu_npcp_followers_unsneak")
        Utility.Wait(0.25)
    endWhile
endFunction

function Unfollow()
    while !p_Send_Followers("doticu_npcp_followers_unfollow")
        Utility.Wait(0.25)
    endWhile
endFunction

function Unmember()
    while !p_Send_Followers("doticu_npcp_followers_unmember")
        Utility.Wait(0.25)
    endWhile
endFunction

function Resurrect()
    while !p_Send_Followers("doticu_npcp_followers_resurrect")
        Utility.Wait(0.25)
    endWhile
endFunction

; Update Methods
function u_0_1_1()
    while !p_Send_Followers("doticu_npcp_members_u_0_1_1")
        Utility.Wait(0.25)
    endWhile
endFunction
