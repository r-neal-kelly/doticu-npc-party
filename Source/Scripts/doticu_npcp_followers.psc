Scriptname doticu_npcp_followers extends Quest

; Private Constants
doticu_npcp_data        p_DATA      = none
doticu_npcp_consts      p_CONSTS    = none
doticu_npcp_codes       p_CODES     = none
doticu_npcp_tasklists   p_TASKLISTS = none
doticu_npcp_aliases     p_ALIASES   = none

doticu_npcp_tasklist    p_TASKLIST  = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_TASKLISTS = DATA.MODS.FUNCS.TASKLISTS
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

    p_TASKLIST = p_TASKLISTS.Create()

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

    ModEvent.PushForm(handle, p_DATA as Form)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

int function p_Enforce()
    int num_followers = Get_Count()
    if num_followers < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if !p_TASKLIST.Execute(num_followers, "doticu_npcp_followers_enforce")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Settle()
    int num_followers = Get_Count()
    if num_followers < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if !p_TASKLIST.Execute(num_followers, "doticu_npcp_followers_settle")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Unsettle()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int num_settlers = Get_Count_Settler()
    if num_settlers < 1
        return p_CODES.HASNT_SETTLER
    endIf

    if !p_TASKLIST.Execute(num_settlers, "doticu_npcp_followers_unsettle")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Immobilize()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int num_mobile = Get_Count_Mobile()
    if num_mobile < 1
        return p_CODES.HASNT_MOBILE
    endIf

    if !p_TASKLIST.Execute(num_mobile, "doticu_npcp_followers_immobilize")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Mobilize()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int num_immobile = Get_Count_Immobile()
    if num_immobile < 1
        return p_CODES.HASNT_IMMOBILE
    endIf

    if !p_TASKLIST.Execute(num_immobile, "doticu_npcp_followers_mobilize")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Sneak()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int num_unsneaks = Get_Count_Unsneak()
    if num_unsneaks < 1
        return p_CODES.HASNT_UNSNEAK
    endIf

    if !p_TASKLIST.Execute(num_unsneaks, "doticu_npcp_followers_sneak")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Unsneak()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int num_sneaks = Get_Count_Sneak()
    if num_sneaks < 1
        return p_CODES.HASNT_SNEAK
    endIf

    if !p_TASKLIST.Execute(num_sneaks, "doticu_npcp_followers_unsneak")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Resurrect()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int num_dead = Get_Count_Dead()
    if num_dead < 1
        return p_CODES.HASNT_DEAD
    endIf

    if !p_TASKLIST.Execute(num_dead, "doticu_npcp_followers_resurrect")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Unfollow()
    int num_followers = Get_Count()
    if num_followers < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if !p_TASKLIST.Execute(num_followers, "doticu_npcp_followers_unfollow")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function p_Unmember()
    int num_followers = Get_Count()
    if num_followers < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if !p_TASKLIST.Execute(num_followers, "doticu_npcp_followers_unmember")
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

; Public Methods
int function Get_Max()
    return p_ALIASES.Get_Max()
endFunction

int function Get_Count()
    return p_ALIASES.Get_Count()
endFunction

int function Get_Count_Alive()
    int count = 0
    int max_aliases = Get_Max()
    int idx_aliases = 0
    doticu_npcp_follower ref_follower

    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Alive()
            count += 1
        endIf
        idx_aliases += 1
    endWhile

    return count
endFunction

int function Get_Count_Dead()
    int count = 0
    int max_aliases = Get_Max()
    int idx_aliases = 0
    doticu_npcp_follower ref_follower

    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Dead()
            count += 1
        endIf
        idx_aliases += 1
    endWhile

    return count
endFunction

int function Get_Count_Settler()
    int count = 0
    int max_aliases = Get_Max()
    int idx_aliases = 0
    doticu_npcp_follower ref_follower

    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Settler()
            count += 1
        endIf
        idx_aliases += 1
    endWhile

    return count
endFunction

int function Get_Count_Mobile()
    int count = 0
    int max_aliases = Get_Max()
    int idx_aliases = 0
    doticu_npcp_follower ref_follower

    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Mobile()
            count += 1
        endIf
        idx_aliases += 1
    endWhile

    return count
endFunction

int function Get_Count_Immobile()
    int count = 0
    int max_aliases = Get_Max()
    int idx_aliases = 0
    doticu_npcp_follower ref_follower

    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Immobile()
            count += 1
        endIf
        idx_aliases += 1
    endWhile

    return count
endFunction

int function Get_Count_Sneak()
    int count = 0
    int max_aliases = Get_Max()
    int idx_aliases = 0
    doticu_npcp_follower ref_follower

    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Sneak()
            count += 1
        endIf
        idx_aliases += 1
    endWhile

    return count
endFunction

int function Get_Count_Unsneak()
    int count = 0
    int max_aliases = Get_Max()
    int idx_aliases = 0
    doticu_npcp_follower ref_follower

    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Unsneak()
            count += 1
        endIf
        idx_aliases += 1
    endWhile

    return count
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

int function Summon_All(int distance = 120, int angle_start = 0, int angle_offset = 15)
    int count_followers = Get_Count()
    if count_followers < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int idx_aliases = 0
    int max_aliases = Get_Max()
    doticu_npcp_follower ref_follower

    if count_followers == 1
        while idx_aliases < max_aliases
            ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
            if ref_follower.Exists()
                ref_follower.Summon(distance, angle_start)
                return p_CODES.SUCCESS
            endIf
            idx_aliases += 1
        endWhile
    endIf

    int angle_even = angle_start
    int angle_odd = angle_start
    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Exists()
            if idx_aliases % 2 == 0
                angle_even += angle_offset
                ref_follower.Summon(distance, angle_even)
            else
                angle_odd -= angle_offset
                ref_follower.Summon(distance, angle_odd)
            endIf
        endIf
        idx_aliases += 1
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Summon_Mobile(int distance = 120, int angle_start = 0, int angle_offset = 15)
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int count_mobile = Get_Count_Mobile()
    if count_mobile < 1
        return p_CODES.HASNT_MOBILE
    endIf

    int idx_aliases = 0
    int max_aliases = Get_Max()
    doticu_npcp_follower ref_follower

    if count_mobile == 1
        while idx_aliases < max_aliases
            ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
            if ref_follower.Is_Mobile()
                ref_follower.Summon(distance, angle_start)
                return p_CODES.SUCCESS
            endIf
            idx_aliases += 1
        endWhile
    endIf

    int angle_even = angle_start
    int angle_odd = angle_start
    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Mobile()
            if idx_aliases % 2 == 0
                angle_even += angle_offset
                ref_follower.Summon(distance, angle_even)
            else
                angle_odd -= angle_offset
                ref_follower.Summon(distance, angle_odd)
            endIf
        endIf
        idx_aliases += 1
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Summon_Immobile(int distance = 120, int angle_start = 0, int angle_offset = 15)
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int count_immobile = Get_Count_Immobile()
    if count_immobile < 1
        return p_CODES.HASNT_IMMOBILE
    endIf

    int idx_aliases = 0
    int max_aliases = Get_Max()
    doticu_npcp_follower ref_follower

    if count_immobile == 1
        while idx_aliases < max_aliases
            ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
            if ref_follower.Is_Immobile()
                ref_follower.Summon(distance, angle_start)
                return p_CODES.SUCCESS
            endIf
            idx_aliases += 1
        endWhile
    endIf

    int angle_even = angle_start
    int angle_odd = angle_start
    while idx_aliases < max_aliases
        ref_follower = GetNthAlias(idx_aliases) as doticu_npcp_follower
        if ref_follower.Is_Immobile()
            if idx_aliases % 2 == 0
                angle_even += angle_offset
                ref_follower.Summon(distance, angle_even)
            else
                angle_odd -= angle_offset
                ref_follower.Summon(distance, angle_odd)
            endIf
        endIf
        idx_aliases += 1
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Summon_All_Behind()
    Summon_All(120, 180)
endFunction

int function Summon_Mobile_Behind()
    Summon_Mobile(120, 180)
endFunction

int function Summon_Immobile_Behind()
    Summon_Immobile(120, 180)
endFunction

int function Enforce()
    GotoState("p_STATE_BUSY")
    int code_return = p_Enforce()
    GotoState("")
    return code_return
endFunction

int function Settle()
    GotoState("p_STATE_BUSY")
    int code_return = p_Settle()
    GotoState("")
    return code_return
endFunction

int function Unsettle()
    GotoState("p_STATE_BUSY")
    int code_return = p_Unsettle()
    GotoState("")
    return code_return
endFunction

int function Immobilize()
    GotoState("p_STATE_BUSY")
    int code_return = p_Immobilize()
    GotoState("")
    return code_return
endFunction

int function Mobilize()
    GotoState("p_STATE_BUSY")
    int code_return = p_Mobilize()
    GotoState("")
    return code_return
endFunction

int function Sneak()
    GotoState("p_STATE_BUSY")
    int code_return = p_Sneak()
    GotoState("")
    return code_return
endFunction

int function Unsneak()
    GotoState("p_STATE_BUSY")
    int code_return = p_Unsneak()
    GotoState("")
    return code_return
endFunction

int function Resurrect()
    GotoState("p_STATE_BUSY")
    int code_return = p_Resurrect()
    GotoState("")
    return code_return
endFunction

int function Unfollow()
    GotoState("p_STATE_BUSY")
    int code_return = p_Unfollow()
    GotoState("")
    return code_return
endFunction

int function Unmember()
    GotoState("p_STATE_BUSY")
    int code_return = p_Unmember()
    GotoState("")
    return code_return
endFunction

; Update Methods
function u_0_1_1()
    while !p_Send_Followers("doticu_npcp_members_u_0_1_1")
        Utility.Wait(0.25)
    endWhile
endFunction

function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
    p_TASKLIST = p_TASKLISTS.Create()
    while !p_Send_Followers("doticu_npcp_members_u_0_1_4")
        Utility.Wait(0.25)
    endWhile
endFunction

; State
state p_STATE_BUSY
    int function Enforce()
    endFunction
    int function Settle()
    endFunction
    int function Unsettle()
    endFunction
    int function Immobilize()
    endFunction
    int function Mobilize()
    endFunction
    int function Sneak()
    endFunction
    int function Unsneak()
    endFunction
    int function Resurrect()
    endFunction
    int function Unfollow()
    endFunction
    int function Unmember()
    endFunction
endState
