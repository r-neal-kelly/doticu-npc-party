Scriptname doticu_npcp_followers extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_tasklists property TASKLISTS hidden
    doticu_npcp_tasklists function Get()
        return p_DATA.MODS.FUNCS.TASKLISTS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_aliases property ALIASES hidden
    doticu_npcp_aliases function Get()
        return (self as Quest) as doticu_npcp_aliases
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA          =  none

; Private Variables
bool                    p_is_created    = false
doticu_npcp_tasklist    p_tasklist      =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_tasklist = TASKLISTS.Create()

    ALIASES.f_Create(DATA)
endFunction

function f_Destroy()
    ALIASES.f_Destroy()
    
    TASKLISTS.Destroy(p_tasklist)
    p_is_created = false
endFunction

function f_Register()
    ALIASES.f_Register()

    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    while idx_aliases < num_aliases
        (arr_aliases[idx_aliases] as doticu_npcp_follower).f_Register()
        idx_aliases += 1
    endWhile
endFunction

int function f_Create_Follower(Actor ref_actor)
    int code_return

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    if ALIASES.Is_Full()
        return CODES.HASNT_SPACE_FOLLOWER
    endIf

    if !MEMBERS.Has_Member(ref_actor)
        return CODES.ISNT_MEMBER
    endIf

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

    doticu_npcp_follower ref_follower = p_Get_Follower(id_alias)
    ref_follower.f_Create(p_DATA, id_alias)
    ref_follower.f_Register()

    ; this value needs to be 1 whenever there is a follower
    ; because the engine won't update player teammates when 0
    CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)

    return CODES.SUCCESS
endFunction

int function f_Destroy_Follower(Actor ref_actor)
    int code_return

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    int id_alias = p_Get_Alias_ID(ref_actor)
    if !ALIASES.Has_Alias(id_alias, ref_actor)
        return CODES.HASNT_FOLLOWER
    endIf

    doticu_npcp_follower ref_follower = p_Get_Follower(id_alias)
    ref_follower.f_Unregister()
    ref_follower.f_Destroy()

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

; Private Methods
int function p_Get_Alias_ID(Actor ref_actor)
    if !ref_actor
        return -1
    else
        return ref_actor.GetItemCount(CONSTS.TOKEN_FOLLOWER) - 1
    endIf
endFunction

doticu_npcp_follower function p_Get_Follower(int id_alias)
    return ALIASES.f_Get_Alias(id_alias) as doticu_npcp_follower
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
        return CODES.HASNT_FOLLOWER
    endIf

    if !p_tasklist.Execute(num_followers, "doticu_npcp_followers_enforce")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Settle()
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    if !p_tasklist.Execute(num_followers, "doticu_npcp_followers_settle")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Unsettle()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_settlers = Get_Count_Settler()
    if num_settlers < 1
        return CODES.HASNT_SETTLER
    endIf

    if !p_tasklist.Execute(num_settlers, "doticu_npcp_followers_unsettle")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Immobilize()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_mobile = Get_Count_Mobile()
    if num_mobile < 1
        return CODES.HASNT_MOBILE
    endIf

    if !p_tasklist.Execute(num_mobile, "doticu_npcp_followers_immobilize")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Mobilize()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_immobile = Get_Count_Immobile()
    if num_immobile < 1
        return CODES.HASNT_IMMOBILE
    endIf

    if !p_tasklist.Execute(num_immobile, "doticu_npcp_followers_mobilize")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Sneak()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_unsneaks = Get_Count_Unsneak()
    if num_unsneaks < 1
        return CODES.HASNT_UNSNEAK
    endIf

    if !p_tasklist.Execute(num_unsneaks, "doticu_npcp_followers_sneak")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Unsneak()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_sneaks = Get_Count_Sneak()
    if num_sneaks < 1
        return CODES.HASNT_SNEAK
    endIf

    if !p_tasklist.Execute(num_sneaks, "doticu_npcp_followers_unsneak")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Resurrect()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_dead = Get_Count_Dead()
    if num_dead < 1
        return CODES.HASNT_DEAD
    endIf

    if !p_tasklist.Execute(num_dead, "doticu_npcp_followers_resurrect")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Unfollow()
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    if !p_tasklist.Execute(num_followers, "doticu_npcp_followers_unfollow")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Unmember()
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    if !p_tasklist.Execute(num_followers, "doticu_npcp_followers_unmember")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Catch_Up()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_mobile = Get_Count_Mobile()
    if num_mobile < 1
        return CODES.HASNT_MOBILE
    endIf

    if !p_tasklist.Execute(num_mobile, "doticu_npcp_followers_catch_up")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

; Public Methods
int function Get_Max()
    return ALIASES.Get_Max()
endFunction

int function Get_Count()
    return ALIASES.Get_Count()
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

bool function Are_In_Combat()
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length

    while idx_aliases < num_aliases
        if (arr_aliases[idx_aliases] as doticu_npcp_follower).Is_In_Combat()
            return true
        endIf
        idx_aliases += 1
    endWhile

    return false
endFunction

bool function Has_Follower(Actor ref_actor)
    return ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

doticu_npcp_follower function Get_Follower(Actor ref_actor)
    return ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_follower
endFunction

Alias[] function Get_Followers(int idx_from = 0, int idx_to_ex = -1)
    return ALIASES.Get_Aliases(idx_from, idx_to_ex)
endFunction

function Sort_Followers()
    ALIASES.Sort_Aliases()
endFunction

int function Summon_All(int distance = 120, int angle_start = 0, int angle_offset = 17)
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    doticu_npcp_follower ref_follower

    if num_followers == 1
        (arr_aliases[0] as doticu_npcp_follower).Summon(distance, angle_start)
        return CODES.SUCCESS
    endIf

    int angle_even = angle_start
    int angle_odd = angle_start
    while idx_aliases < num_aliases
        ref_follower = arr_aliases[idx_aliases] as doticu_npcp_follower
        if idx_aliases % 2 == 0
            angle_even += angle_offset
            ref_follower.Summon(distance, angle_even)
        else
            angle_odd -= angle_offset
            ref_follower.Summon(distance, angle_odd)
        endIf
        idx_aliases += 1
    endWhile

    return CODES.SUCCESS
endFunction

int function Summon_Mobile(int distance = 120, int angle_start = 0, int angle_offset = 17)
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int count_mobile = Get_Count_Mobile()
    if count_mobile < 1
        return CODES.HASNT_MOBILE
    endIf

    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    doticu_npcp_follower ref_follower

    if count_mobile == 1
        (arr_aliases[0] as doticu_npcp_follower).Summon(distance, angle_start)
        return CODES.SUCCESS
    endIf

    int angle_even = angle_start
    int angle_odd = angle_start
    int count_summon = 0
    while idx_aliases < num_aliases
        ref_follower = arr_aliases[idx_aliases] as doticu_npcp_follower
        if ref_follower.Is_Mobile()
            if count_summon % 2 == 0
                angle_even += angle_offset
                ref_follower.Summon(distance, angle_even)
            else
                angle_odd -= angle_offset
                ref_follower.Summon(distance, angle_odd)
            endIf
            count_summon += 1
        endIf
        idx_aliases += 1
    endWhile

    return CODES.SUCCESS
endFunction

int function Summon_Immobile(int distance = 120, int angle_start = 0, int angle_offset = 17)
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int count_immobile = Get_Count_Immobile()
    if count_immobile < 1
        return CODES.HASNT_IMMOBILE
    endIf

    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    doticu_npcp_follower ref_follower

    if count_immobile == 1
        (arr_aliases[0] as doticu_npcp_follower).Summon(distance, angle_start)
        return CODES.SUCCESS
    endIf

    int angle_even = angle_start
    int angle_odd = angle_start
    int count_summon = 0
    while idx_aliases < num_aliases
        ref_follower = arr_aliases[idx_aliases] as doticu_npcp_follower
        if ref_follower.Is_Immobile()
            if count_summon % 2 == 0
                angle_even += angle_offset
                ref_follower.Summon(distance, angle_even)
            else
                angle_odd -= angle_offset
                ref_follower.Summon(distance, angle_odd)
            endIf
            count_summon += 1
        endIf
        idx_aliases += 1
    endWhile

    return CODES.SUCCESS
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

int function Catch_Up()
    GotoState("p_STATE_BUSY")
    int code_return = p_Catch_Up()
    GotoState("")
    return code_return
endFunction

; Update Methods
function u_0_2_1(doticu_npcp_data DATA)
    ; as slow as it may be, use a loop so that loading the game is quicker
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
    int function Catch_Up()
    endFunction
endState
