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
Alias function p_From_ID(int unique_id) native
Alias function p_From_Actor(Actor ref_actor) native
Alias function p_From_Unfilled() native
Alias function p_From_Horse_Actor(Actor ref_actor) native

bool function Has_Space() native
bool function Hasnt_Space() native
bool function Has_Actor(Actor ref_actor) native
bool function Hasnt_Actor(Actor ref_actor) native
bool function Are_In_Combat() native

int function Max() native
int function Count_Filled() native
int function Count_Unfilled() native
int function Count_Loaded() native
int function Count_Unloaded() native
int function Count_Unique() native
int function Count_Generic() native
int function Count_Alive() native
int function Count_Dead() native
int function Count_Originals() native
int function Count_Clones() native
int function Count_Mobile() native
int function Count_Immobile() native
int function Count_Settlers() native
int function Count_Non_Settlers() native
int function Count_Thralls() native
int function Count_Non_Thralls() native
int function Count_Paralyzed() native
int function Count_Non_Paralyzed() native
int function Count_Mannequins() native
int function Count_Non_Mannequins() native
int function Count_Reanimated() native
int function Count_Non_Reanimated() native
int function Count_Followers() native
int function Count_Non_Followers() native
int function Count_Sneaks() native
int function Count_Non_Sneaks() native
int function Count_Saddlers() native
int function Count_Non_Saddlers() native
int function Count_Retreaters() native
int function Count_Non_Retreaters() native

Alias[] function All() native
Alias[] function Filled() native
Alias[] function Unfilled() native
Alias[] function Loaded() native
Alias[] function Unloaded() native

Alias[] function Sort_Filled(int begin, int end) native

Alias[] function Slice(Alias[] followers, int begin, int end) native

function p_Register() native
function p_Enforce() native
function p_Resurrect() native
function p_Mobilize() native
function p_Immobilize() native
function p_Settle() native
function p_Unsettle() native
function p_Enthrall() native
function p_Unthrall() native
function p_Paralyze() native
function p_Unparalyze() native
function p_Sneak() native
function p_Unsneak() native
function p_Saddle() native
function p_Unsaddle() native
function p_Retreat() native
function p_Unretreat() native
function p_Unfollow() native
function p_Unmember() native

function p_Summon_Filled(float radius = 140.0, float degree = 0.0, float interval = 19.0) native
function p_Summon_Mobile(float radius = 140.0, float degree = 0.0, float interval = 19.0) native
function p_Summon_Immobile(float radius = 140.0, float degree = 0.0, float interval = 19.0) native

function p_Catch_Up() native
function p_Stash() native

string[] function Filter_Strings(string sex = "", string race = "", string search = "") native
int[] function Filter_Ints(int style = 0, int vitality = 0, int outfit2 = 0, int rating = -1) native
int function Add_Filter_Flag_1(int flags_1, string flag_1) native
int function Add_Filter_Flag_2(int flags_2, string flag_2) native
Alias[] function Filter(string[] strings, int[] ints, int flags_1, int flags_2) native

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
        return doticu_npcp_codes.ISNT_ACTOR()
    endIf

    if Hasnt_Space()
        return doticu_npcp_codes.HASNT_FOLLOWER_SPACE()
    endIf

    if !MEMBERS.Has_Member(ref_actor)
        return doticu_npcp_codes.ISNT_MEMBER()
    endIf

    if Has_Actor(ref_actor)
        return CODES.HAS_FOLLOWER
    endIf

    doticu_npcp_follower ref_follower = p_From_Unfilled() as doticu_npcp_follower
    if ref_follower == none
        return doticu_npcp_codes.FAILURE()
    endIf

    ref_follower.f_Create(p_DATA, ref_actor)
    ref_follower.f_Register()

    ; this value needs to be 1 whenever there is a follower
    ; because the engine won't update player teammates when 0
    CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)

    return doticu_npcp_codes.SUCCESS()
endFunction

int function f_Destroy_Follower(Actor ref_actor)
    if !ref_actor
        return doticu_npcp_codes.ISNT_ACTOR()
    endIf

    doticu_npcp_follower ref_follower = p_From_Actor(ref_actor) as doticu_npcp_follower
    if ref_follower == none
        return CODES.HASNT_FOLLOWER
    endIf

    ref_follower.f_Unregister()
    ref_follower.f_Destroy()

    if Count_Filled() == 0
        ; this would conflict with the vanilla system
        ; and any other mods that use it, except that we
        ; modify the vanilla system to force use of ours
        CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(0)
    endIf

    return doticu_npcp_codes.SUCCESS()
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
    return p_From_Actor(ref_actor) as doticu_npcp_follower
endFunction

Alias[] function Get_Followers(int begin = 0, int end = -1)
    return Sort_Filled(begin, end)
endFunction

doticu_npcp_follower function From_Horse_Actor(Actor ref_actor)
    return p_From_Horse_Actor(ref_actor) as doticu_npcp_follower
endFunction

int function Summon(float radius = 140.0, float degree = 0.0, float interval = 19.0)
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Summon_Filled(radius, degree, interval)

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Summon_Mobile(float radius = 140.0, float degree = 0.0, float interval = 19.0)
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_mobile = Count_Mobile()
    if num_mobile < 1
        return p_Ready_Int(CODES.HASNT_MOBILE)
    endIf

    p_Summon_Mobile(radius, degree, interval)

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Summon_Immobile(float radius = 140.0, float degree = 0.0, float interval = 19.0)
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_immobile = Count_Immobile()
    if num_immobile < 1
        return p_Ready_Int(CODES.HASNT_IMMOBILE)
    endIf

    p_Summon_Immobile(radius, degree, interval)

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Catch_Up()
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Catch_Up()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Stash()
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Stash()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Enforce()
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    
    p_Enforce()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Resurrect()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_dead = Count_Dead()
    if num_dead < 1
        return p_Ready_Int(CODES.HASNT_DEAD)
    endIf

    p_tasklist.Init(num_dead)

    p_Resurrect()

    if !p_tasklist.Await(num_dead, 0.5, 10.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Mobilize()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    if Count_Immobile() < 1
        return p_Ready_Int(CODES.HASNT_IMMOBILE)
    endIf

    p_Mobilize()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Immobilize()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    if Count_Mobile() < 1
        return p_Ready_Int(CODES.HASNT_MOBILE)
    endIf

    p_Immobilize()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Settle()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_Settle()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Unsettle()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    if Count_Settlers() < 1
        return p_Ready_Int(CODES.HASNT_SETTLER)
    endIf

    p_Unsettle()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Enthrall()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    if Count_Non_Thralls() < 1
        return p_Ready_Int(CODES.HASNT_NON_THRALL)
    endIf

    p_Enthrall()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Unthrall()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    if Count_Thralls() < 1
        return p_Ready_Int(CODES.HASNT_THRALL)
    endIf

    p_Unthrall()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Paralyze()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    if Count_Non_Paralyzed() < 1
        return p_Ready_Int(CODES.HASNT_NON_PARALYZED)
    endIf

    p_Paralyze()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Unparalyze()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    if Count_Paralyzed() < 1
        return p_Ready_Int(CODES.HASNT_PARALYZED)
    endIf

    p_Unparalyze()

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Sneak()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_non_sneaks = Count_Non_Sneaks()
    if num_non_sneaks < 1
        return p_Ready_Int(CODES.HASNT_NON_SNEAK)
    endIf

    p_tasklist.Init(num_non_sneaks)

    p_Sneak()

    if !p_tasklist.Await(num_non_sneaks, 0.5, 10.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Unsneak()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_sneaks = Count_Sneaks()
    if num_sneaks < 1
        return p_Ready_Int(CODES.HASNT_SNEAK)
    endIf

    p_tasklist.Init(num_sneaks)

    p_Unsneak()

    if !p_tasklist.Await(num_sneaks, 0.5, 10.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Saddle()
p_Busy()

    if CONSTS.ACTOR_PLAYER.GetParentCell().IsInterior()
        return p_Ready_Int(CODES.IS_INTERIOR)
    endIf

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_non_saddlers = Count_Non_Saddlers()
    if num_non_saddlers < 1
        return p_Ready_Int(CODES.HASNT_NON_SADDLER)
    endIf

    p_tasklist.Init(num_non_saddlers)

    p_Saddle()

    if !p_tasklist.Await(num_non_saddlers, 0.5, 10.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Unsaddle()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_saddlers = Count_Saddlers()
    if num_saddlers < 1
        return p_Ready_Int(CODES.HASNT_SADDLER)
    endIf

    p_tasklist.Init(num_saddlers)

    p_Unsaddle()

    if !p_tasklist.Await(num_saddlers, 0.5, 10.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Retreat()
p_Busy()
    
    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf
    
    int num_non_retreaters = Count_Non_Retreaters()
    if num_non_retreaters < 1
        return p_Ready_Int(CODES.HASNT_NON_RETREATER)
    endIf
    
    p_tasklist.Init(num_non_retreaters)
    
    p_Retreat()
    
    if !p_tasklist.Await(num_non_retreaters, 0.5, 10.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf
    
    return p_Ready_Int(doticu_npcp_codes.SUCCESS())
    
p_Ready()
endFunction

int function Unretreat()
p_Busy()

    if Count_Filled() < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    int num_retreaters = Count_Retreaters()
    if num_retreaters < 1
        return p_Ready_Int(CODES.HASNT_RETREATER)
    endIf

    p_tasklist.Init(num_retreaters)

    p_Unretreat()

    if !p_tasklist.Await(num_retreaters, 0.5, 10.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Unfollow()
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_tasklist.Init(num_followers)

    p_Unfollow()

    if !p_tasklist.Await(num_followers, 0.5, 15.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

p_Ready()
endFunction

int function Unmember()
p_Busy()

    int num_followers = Count_Filled()
    if num_followers < 1
        return p_Ready_Int(CODES.HASNT_FOLLOWER)
    endIf

    p_tasklist.Init(num_followers)

    p_Unmember()

    if !p_tasklist.Await(num_followers, 0.5, 15.0)
        return p_Ready_Int(doticu_npcp_codes.FAILURE())
    endIf

    return p_Ready_Int(doticu_npcp_codes.SUCCESS())

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
    int function Enthrall()
    endFunction
    int function Unthrall()
    endFunction
    int function Paralyze()
    endFunction
    int function Unparalyze()
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
