;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

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

    if Get_Count() >= Get_Max()
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
function p_Summon(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Summon_Mobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Summon_Immobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native

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

    int num_settlers = Get_Settler_Count()
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

    int num_mobile = Get_Mobile_Count()
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

    int num_immobile = Get_Immobile_Count()
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

    int num_non_sneaks = Get_Non_Sneak_Count()
    if num_non_sneaks < 1
        return CODES.HASNT_NON_SNEAK
    endIf

    if !p_tasklist.Execute(num_non_sneaks, "doticu_npcp_followers_sneak")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Unsneak()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_sneaks = Get_Sneak_Count()
    if num_sneaks < 1
        return CODES.HASNT_SNEAK
    endIf

    if !p_tasklist.Execute(num_sneaks, "doticu_npcp_followers_unsneak")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Saddle()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_non_saddlers = Get_Non_Saddler_Count()
    if num_non_saddlers < 1
        return CODES.HASNT_NON_SADDLER
    endIf

    if !p_tasklist.Execute(num_non_saddlers, "doticu_npcp_followers_saddle")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Unsaddle()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_saddlers = Get_Saddler_Count()
    if num_saddlers < 1
        return CODES.HASNT_SADDLER
    endIf

    if !p_tasklist.Execute(num_saddlers, "doticu_npcp_followers_unsaddle")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Stash()
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    doticu_npcp.Followers_Stash(self)

    return CODES.SUCCESS
endFunction

int function p_Unretreat()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_retreaters = Get_Retreater_Count()
    if num_retreaters < 1
        return CODES.HASNT_RETREATER
    endIf

    if !p_tasklist.Execute(num_retreaters, "doticu_npcp_followers_unretreat")
        return CODES.FAILURE
    endIf

    return CODES.SUCCESS
endFunction

int function p_Resurrect()
    if Get_Count() < 1
        return CODES.HASNT_FOLLOWER
    endIf

    int num_dead = Get_Dead_Count()
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

; Public Methods
int function Get_Count() native
int function Get_Alive_Count() native
int function Get_Dead_Count() native
int function Get_Mobile_Count() native
int function Get_Immobile_Count() native
int function Get_Settler_Count() native
int function Get_Non_Settler_Count() native
int function Get_Sneak_Count() native
int function Get_Non_Sneak_Count() native
int function Get_Saddler_Count() native
int function Get_Non_Saddler_Count() native
int function Get_Retreater_Count() native
int function Get_Non_Retreater_Count() native

bool function Are_In_Combat() native

int function Get_Max()
    return ALIASES.Get_Max()
endFunction

bool function Will_Sort()
    return ALIASES.Will_Sort()
endFunction

bool function Has_Follower(Actor ref_actor)
    return ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

doticu_npcp_follower function Get_Follower(Actor ref_actor)
    return ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_follower
endFunction

doticu_npcp_follower function Get_Next_Follower(doticu_npcp_follower ref_follower)
    Actor ref_actor = ref_follower.Get_Actor()
    return ALIASES.Get_Next_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_follower
endFunction

doticu_npcp_follower function Get_Prev_Follower(doticu_npcp_follower ref_follower)
    Actor ref_actor = ref_follower.Get_Actor()
    return ALIASES.Get_Prev_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_follower
endFunction

Alias[] function Get_Followers(int idx_from = 0, int idx_to_ex = -1)
    return ALIASES.Get_Aliases(idx_from, idx_to_ex)
endFunction

function Request_Sort()
    ALIASES.Request_Sort()
endFunction

function Sort()
    ALIASES.Sort()
endFunction

int function Summon(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    p_Summon(distance, angle_degree, interval_degree)

    return CODES.SUCCESS
endFunction

int function Summon_Mobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    p_Summon_Mobile(distance, angle_degree, interval_degree)

    return CODES.SUCCESS
endFunction

int function Summon_Immobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
    int num_followers = Get_Count()
    if num_followers < 1
        return CODES.HASNT_FOLLOWER
    endIf

    p_Summon_Immobile(distance, angle_degree, interval_degree)

    return CODES.SUCCESS
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

int function Saddle()
    GotoState("p_STATE_BUSY")
    int code_return = p_Saddle()
    GotoState("")
    return code_return
endFunction

int function Unsaddle()
    GotoState("p_STATE_BUSY")
    int code_return = p_Unsaddle()
    GotoState("")
    return code_return
endFunction

int function Stash()
    GotoState("p_STATE_BUSY")
    int code_return = p_Stash()
    GotoState("")
    return code_return
endFunction

int function Unretreat()
    GotoState("p_STATE_BUSY")
    int code_return = p_Unretreat()
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

; State
state p_STATE_BUSY
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
    int function Saddle()
    endFunction
    int function Unsaddle()
    endFunction
    int function Stash()
    endFunction
    int function Unretreat()
    endFunction
    int function Resurrect()
    endFunction
    int function Unfollow()
    endFunction
    int function Unmember()
    endFunction
endState
