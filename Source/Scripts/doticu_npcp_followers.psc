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
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_tasklists property TASKLISTS hidden
    doticu_npcp_tasklists function Get()
        return p_DATA.MODS.FUNCS.TASKLISTS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA          =  none

; Private Variables
bool                    p_is_created    = false
doticu_npcp_tasklist    p_tasklist      =  none

; Native Methods
function p_Register() native
function p_Summon(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Summon_Mobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Summon_Immobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0) native
function p_Catch_Up() native
function p_Stash() native
function p_Enforce(Form tasklist) native
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

Alias function p_ID_To_Follower(int id) native
Alias function p_Actor_To_Follower(Actor ref_actor) native
int function p_Actor_To_ID(Actor ref_actor) native

Alias function p_Unused_Follower() native
int function p_Unused_ID() native

Alias[] function p_Sort_All(int from = 0, int to_exclusive = -1, string algorithm = "") native

int function Max() native
int function Count_All() native
int function Count_Alive() native
int function Count_Dead() native
int function Count_Mobile() native
int function Count_Immobile() native
int function Count_Settlers() native
int function Count_Non_Settlers() native
int function Count_Sneaks() native
int function Count_Non_Sneaks() native
int function Count_Saddlers() native
int function Count_Non_Saddlers() native
int function Count_Retreaters() native
int function Count_Non_Retreaters() native

bool function Has_Space() native
bool function Hasnt_Space() native
bool function Are_In_Combat() native
bool function Has_Actor(Actor ref_actor) native

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_tasklist = TASKLISTS.Create()
endFunction

function f_Destroy()
    TASKLISTS.Destroy(p_tasklist)
    p_is_created = false
endFunction

function f_Register()
    p_Register()
endFunction

int function f_Create_Follower(Actor ref_actor)
    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    if Hasnt_Space()
        return CODES.HASNT_SPACE_FOLLOWER
    endIf

    if !MEMBERS.Has_Member(ref_actor)
        return CODES.ISNT_MEMBER
    endIf

    if Has_Actor(ref_actor)
        return CODES.HAS_FOLLOWER
    endIf

    int id_alias = p_Unused_ID()
    if id_alias < 0
        return CODES.FAILURE
    endIf

    doticu_npcp_follower ref_follower = p_ID_To_Follower(id_alias) as doticu_npcp_follower
    ref_follower.f_Create(p_DATA, id_alias, ref_actor)
    ref_follower.f_Register()

    ; this value needs to be 1 whenever there is a follower
    ; because the engine won't update player teammates when 0
    CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)

    return CODES.SUCCESS
endFunction

int function f_Destroy_Follower(Actor ref_actor)
    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    int id_alias = p_Actor_To_ID(ref_actor)
    if id_alias < 0
        return CODES.HASNT_FOLLOWER
    endIf

    doticu_npcp_follower ref_follower = p_ID_To_Follower(id_alias) as doticu_npcp_follower
    ref_follower.f_Unregister()
    ref_follower.f_Destroy()

    if Count_All() == 0
        ; this would conflict with the vanilla system
        ; and any other mods that use it, except that we
        ; modify the vanilla system to force use of ours
        CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(0)
    endIf

    return CODES.SUCCESS
endFunction

; Private Methods
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

; Public Methods
doticu_npcp_follower function Get_Follower(Actor ref_actor)
    return p_Actor_To_Follower(ref_actor) as doticu_npcp_follower
endFunction

Alias[] function Get_Followers(int idx_from = 0, int idx_to_ex = -1)
    return p_Sort_All(idx_from, idx_to_ex, VARS.str_sort_followers)
endFunction

int function Summon(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
p_Busy()

    int num_followers = Count_All()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Summon(distance, angle_degree, interval_degree)

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Summon_Mobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
p_Busy()

    int num_followers = Count_All()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Summon_Mobile(distance, angle_degree, interval_degree)

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Summon_Immobile(float distance = 140.0, float angle_degree = 0.0, float interval_degree = 19.0)
p_Busy()

    int num_followers = Count_All()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Summon_Immobile(distance, angle_degree, interval_degree)

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Catch_Up()
p_Busy()

    int num_followers = Count_All()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Catch_Up()

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Stash()
p_Busy()

    int num_followers = Count_All()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Stash()

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Enforce()
p_Busy()

    int num_followers = Count_All()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Enforce(none)

    return p_Ready_Int(CODES.SUCCESS)

p_Ready()
endFunction

int function Resurrect()
p_Busy()

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_dead = Count_Dead()
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

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_immobile = Count_Immobile()
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

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_mobile = Count_Mobile()
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

    int num_followers = Count_All()
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

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_settlers = Count_Settlers()
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

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_non_sneaks = Count_Non_Sneaks()
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

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_sneaks = Count_Sneaks()
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

    if CONSTS.ACTOR_PLAYER.GetParentCell().IsInterior()
        return p_Ready_Int(CODES.IS_INTERIOR)
    endIf

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_non_saddlers = Count_Non_Saddlers()
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

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_saddlers = Count_Saddlers()
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
    
    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    
    int num_non_retreaters = Count_Non_Retreaters()
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

    if Count_All() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_retreaters = Count_Retreaters()
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

    int num_followers = Count_All()
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

    int num_followers = Count_All()
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

; should have an update func that destroys aliases?
