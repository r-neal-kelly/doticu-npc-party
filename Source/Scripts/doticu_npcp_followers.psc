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

    p_Register()
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
function p_Register() native
function p_Summon(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Summon_Mobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Summon_Immobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Stash() native
function p_Resurrect(Form tasklist) native
function p_Mobilize(Form tasklist) native
function p_Immobilize(Form tasklist) native
function p_Settle(Form tasklist) native
function p_Unsettle(Form tasklist) native
function p_Sneak(Form tasklist) native
function p_Unsneak(Form tasklist) native
function p_Saddle(Form tasklist) native
function p_Unsaddle(Form tasklist) native
function p_Retreat(Form tasklist) native
function p_Unretreat(Form tasklist) native
function p_Unfollow(Form tasklist) native
function p_Unmember(Form tasklist) native

function p_Busy()
    GotoState("p_STATE_BUSY")
endFunction

function p_Ready()
    GotoState("")
endFunction

int function p_Ready_Int(int val)
    GotoState("")
    return val
endFunction

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
p_Busy()

    int num_followers = Get_Count()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Summon(distance, angle_degree, interval_degree)

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Summon_Mobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
p_Busy()

    int num_followers = Get_Count()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Summon_Mobile(distance, angle_degree, interval_degree)

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Summon_Immobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
p_Busy()

    int num_followers = Get_Count()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Summon_Immobile(distance, angle_degree, interval_degree)

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Stash()
p_Busy()

    int num_followers = Get_Count()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Stash()

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Resurrect()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_dead = Get_Dead_Count()
    if num_dead < 1
        return p_Ready_Int(CODES.HASNT_DEAD)
    endIf

    p_tasklist.Init(num_dead)

    p_Resurrect(p_tasklist)

    if !p_tasklist.Await(num_dead, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Mobilize()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_immobile = Get_Immobile_Count()
    if num_immobile < 1
        return p_Ready_Int(CODES.HASNT_IMMOBILE)
    endIf

    p_tasklist.Init(num_immobile)

    p_Mobilize(p_tasklist)

    if !p_tasklist.Await(num_immobile, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Immobilize()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_mobile = Get_Mobile_Count()
    if num_mobile < 1
        return p_Ready_Int(CODES.HASNT_MOBILE)
    endIf

    p_tasklist.Init(num_mobile)

    p_Immobilize(p_tasklist)
    
    if !p_tasklist.Await(num_mobile, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Settle()
p_Busy()

    int num_followers = Get_Count()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_tasklist.Init(num_followers)

    p_Settle(p_tasklist)

    if !p_tasklist.Await(num_followers, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Unsettle()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_settlers = Get_Settler_Count()
    if num_settlers < 1
        return p_Ready_Int(CODES.HASNT_SETTLER)
    endIf

    p_tasklist.Init(num_settlers)

    p_Unsettle(p_tasklist)

    if !p_tasklist.Await(num_settlers, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Sneak()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_non_sneaks = Get_Non_Sneak_Count()
    if num_non_sneaks < 1
        return p_Ready_Int(CODES.HASNT_NON_SNEAK)
    endIf

    p_tasklist.Init(num_non_sneaks)

    p_Sneak(p_tasklist)

    if !p_tasklist.Await(num_non_sneaks, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Unsneak()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_sneaks = Get_Sneak_Count()
    if num_sneaks < 1
        return p_Ready_Int(CODES.HASNT_SNEAK)
    endIf

    p_tasklist.Init(num_sneaks)

    p_Unsneak(p_tasklist)

    if !p_tasklist.Await(num_sneaks, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Saddle()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_non_saddlers = Get_Non_Saddler_Count()
    if num_non_saddlers < 1
        return p_Ready_Int(CODES.HASNT_NON_SADDLER)
    endIf

    p_tasklist.Init(num_non_saddlers)

    p_Saddle(p_tasklist)

    if !p_tasklist.Await(num_non_saddlers, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Unsaddle()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_saddlers = Get_Saddler_Count()
    if num_saddlers < 1
        return p_Ready_Int(CODES.HASNT_SADDLER)
    endIf

    p_tasklist.Init(num_saddlers)

    p_Unsaddle(p_tasklist)

    if !p_tasklist.Await(num_saddlers, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Retreat()
p_Busy()
    
    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    
    int num_non_retreaters = Get_Non_Retreater_Count()
    if num_non_retreaters < 1
        return p_Ready_Int(CODES.HASNT_NON_RETREATER)
    endIf
    
    p_tasklist.Init(num_non_retreaters)
    
    p_Retreat(p_tasklist)
    
    if !p_tasklist.Await(num_non_retreaters, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf
    
    return p_Ready_Int(CODES.SUCCESS)
    
p_Ready()
endFunction

int function Unretreat()
p_Busy()

    if Get_Count() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_retreaters = Get_Retreater_Count()
    if num_retreaters < 1
        return p_Ready_Int(CODES.HASNT_RETREATER)
    endIf

    p_tasklist.Init(num_retreaters)

    p_Unretreat(p_tasklist)

    if !p_tasklist.Await(num_retreaters, 0.5, 10.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Unfollow()
p_Busy()

    int num_followers = Get_Count()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_tasklist.Init(num_followers)

    p_Unfollow(p_tasklist)

    if !p_tasklist.Await(num_followers, 0.5, 15.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Unmember()
p_Busy()

    int num_followers = Get_Count()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_tasklist.Init(num_followers)

    p_Unmember(p_tasklist)

    if !p_tasklist.Await(num_followers, 0.5, 15.0)
        return p_Ready_Int(CODES.FAILURE)
    endIf

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

; State
state p_STATE_BUSY
    int function Summon(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
    endFunction
    int function Summon_Mobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
    endFunction
    int function Summon_Immobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
    endFunction
    int function Stash()
    endFunction
    int function Mobilize()
    endFunction
    int function Immobilize()
    endFunction
    int function Settle()
    endFunction
    int function Unsettle()
    endFunction
    int function Sneak()
    endFunction
    int function Unsneak()
    endFunction
    int function Saddle()
    endFunction
    int function Unsaddle()
    endFunction
    int function Retreat()
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
