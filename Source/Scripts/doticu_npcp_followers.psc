Scriptname doticu_npcp_followers extends Quest

; Private Constants
doticu_npcp_consts  p_CONSTS            = none
doticu_npcp_codes   p_CODES             = none
doticu_npcp_aliases p_ALIASES           = none

; Private Variables
int                 p_num_jobs_total    =   -1
int                 p_num_jobs_complete =   -1

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

function f_Complete_Job()
    p_num_jobs_complete += 1
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
        if ref_follower && ref_follower.Is_Alive()
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
        if ref_follower && ref_follower.Is_Dead()
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
        if ref_follower && ref_follower.Is_Settler()
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
        if ref_follower && ref_follower.Is_Mobile()
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
        if ref_follower && ref_follower.Is_Immobile()
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
        if ref_follower && ref_follower.Is_Sneak()
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
        if ref_follower && ref_follower.Is_Unsneak()
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

int function Enforce()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    while !p_Send_Followers("doticu_npcp_followers_enforce")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
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
            if ref_follower.Exists() && ref_follower.Is_Mobile()
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
        if ref_follower.Exists() && ref_follower.Is_Mobile()
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
            if ref_follower.Exists() && ref_follower.Is_Immobile()
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
        if ref_follower.Exists() && ref_follower.Is_Immobile()
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

int function Settle()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    while !p_Send_Followers("doticu_npcp_followers_settle")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Unsettle()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if Get_Count_Settler() < 1
        return p_CODES.HASNT_SETTLER
    endIf

    while !p_Send_Followers("doticu_npcp_followers_unsettle")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Immobilize()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int count_mobile = Get_Count_Mobile()
    if count_mobile < 1
        return p_CODES.HASNT_MOBILE
    endIf

    p_num_jobs_total = count_mobile
    p_num_jobs_complete = 0

    while !p_Send_Followers("doticu_npcp_followers_immobilize")
        Utility.Wait(0.25)
    endWhile

    float time_wait = 0.0
    while time_wait < 100.0 && p_num_jobs_complete != p_num_jobs_total
        Utility.Wait(0.1)
        time_wait += 0.1
    endWhile

    if time_wait >= 100.0
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Mobilize()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    int count_immobile = Get_Count_Immobile()
    if count_immobile < 1
        return p_CODES.HASNT_IMMOBILE
    endIf

    p_num_jobs_total = count_immobile
    p_num_jobs_complete = 0

    while !p_Send_Followers("doticu_npcp_followers_mobilize")
        Utility.Wait(0.25)
    endWhile

    float time_wait = 0.0
    while time_wait < 100.0 && p_num_jobs_complete != p_num_jobs_total
        Utility.Wait(0.1)
        time_wait += 0.1
    endWhile

    if time_wait >= 100.0
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Sneak()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if Get_Count_Unsneak() < 1
        return p_CODES.HASNT_UNSNEAK
    endIf

    while !p_Send_Followers("doticu_npcp_followers_sneak")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Unsneak()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if Get_Count_Sneak() < 1
        return p_CODES.HASNT_SNEAK
    endIf

    while !p_Send_Followers("doticu_npcp_followers_unsneak")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Resurrect()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    if Get_Count_Dead() < 1
        return p_CODES.HASNT_DEAD
    endIf

    while !p_Send_Followers("doticu_npcp_followers_resurrect")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Unfollow()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    while !p_Send_Followers("doticu_npcp_followers_unfollow")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
endFunction

int function Unmember()
    if Get_Count() < 1
        return p_CODES.HASNT_FOLLOWER
    endIf

    while !p_Send_Followers("doticu_npcp_followers_unmember")
        Utility.Wait(0.25)
    endWhile

    return p_CODES.SUCCESS
endFunction

; Update Methods
function u_0_1_1()
    while !p_Send_Followers("doticu_npcp_members_u_0_1_1")
        Utility.Wait(0.25)
    endWhile
endFunction
