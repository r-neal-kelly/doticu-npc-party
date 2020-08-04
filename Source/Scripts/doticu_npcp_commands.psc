;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_commands extends Quest

; Modules
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return doticu_npcp.Funcs().LOGS
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return doticu_npcp.Funcs().MANNEQUINS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return doticu_npcp.Members()
    endFunction
endProperty
doticu_npcp_commands_p property PRIVATE hidden
    doticu_npcp_commands_p function Get()
        return (self as Quest) as doticu_npcp_commands_p
    endFunction
endProperty

; Private Variables
bool                p_is_created        = false

; Friend Methods
function f_Create()
    PRIVATE.f_Create()

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false

    PRIVATE.f_Destroy()
endFunction

function f_Register()
    PRIVATE.f_Register()
endFunction

; Private Methods
function p_Busy()
    GotoState("p_STATE_BUSY")
endFunction

function p_Ready()
    GotoState("")
endFunction

; Public Methods
function Cycle_Style(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Cycle_Style(ref_actor, auto_create)
p_Ready()
endFunction

function Cycle_Vitality(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Cycle_Vitality(ref_actor, auto_create)
p_Ready()
endFunction

function Members_Display_Start()
    GotoState("p_STATE_BUSY")
    PRIVATE.Members_Display_Start()
    GotoState("")
endFunction

function Members_Display_Stop()
    GotoState("p_STATE_BUSY")
    PRIVATE.Members_Display_Stop()
    GotoState("")
endFunction

function Members_Display_Next()
    GotoState("p_STATE_BUSY")
    PRIVATE.Members_Display_Next()
    GotoState("")
endFunction

function Members_Display_Previous()
    GotoState("p_STATE_BUSY")
    PRIVATE.Members_Display_Previous()
    GotoState("")
endFunction

function Toggle_Members_Display()
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Members_Display()
    GotoState("")
endFunction

; Followers
function Followers_Resurrect()
p_Busy()
    PRIVATE.Followers_Resurrect()
p_Ready()
endFunction

function Followers_Mobilize()
p_Busy()
    PRIVATE.Followers_Mobilize()
p_Ready()
endFunction

function Followers_Immobilize()
p_Busy()
    PRIVATE.Followers_Immobilize()
p_Ready()
endFunction

function Followers_Settle()
p_Busy()
    PRIVATE.Followers_Settle()
p_Ready()
endFunction

function Followers_Unsettle()
p_Busy()
    PRIVATE.Followers_Unsettle()
p_Ready()
endFunction

function Followers_Sneak()
p_Busy()
    PRIVATE.Followers_Sneak()
p_Ready()
endFunction

function Followers_Unsneak()
p_Busy()
    PRIVATE.Followers_Unsneak()
p_Ready()
endFunction

function Followers_Saddle()
p_Busy()
    PRIVATE.Followers_Saddle()
p_Ready()
endFunction

function Followers_Unsaddle()
p_Busy()
    PRIVATE.Followers_Unsaddle()
p_Ready()
endFunction

function Followers_Unfollow()
p_Busy()
    PRIVATE.Followers_Unfollow()
p_Ready()
endFunction

function Followers_Unmember()
p_Busy()
    PRIVATE.Followers_Unmember()
p_Ready()
endFunction

function Followers_Summon_All()
p_Busy()
    PRIVATE.Followers_Summon_All()
p_Ready()
endFunction

function Followers_Summon_Mobile()
p_Busy()
    PRIVATE.Followers_Summon_Mobile()
p_Ready()
endFunction

function Followers_Summon_Immobile()
p_Busy()
    PRIVATE.Followers_Summon_Immobile()
p_Ready()
endFunction

function Followers_Stash()
p_Busy()
    PRIVATE.Followers_Stash()
p_Ready()
endFunction

function Toggle_Followers_Settle()
p_Busy()
    PRIVATE.Toggle_Followers_Settle()
p_Ready()
endFunction

function Toggle_Followers_Immobilize()
p_Busy()
    PRIVATE.Toggle_Followers_Immobilize()
p_Ready()
endFunction

function Toggle_Followers_Sneak()
p_Busy()
    PRIVATE.Toggle_Followers_Sneak()
p_Ready()
endFunction

; Member
function Outfit_Show(Actor ref_actor)
    PRIVATE.Outfit_Show(ref_actor)
endFunction

function Style_Show(Actor ref_actor)
    PRIVATE.Style_Show(ref_actor)
endFunction

function Vitality_Show(Actor ref_actor)
    PRIVATE.Vitality_Show(ref_actor)
endFunction

; Public Methods (Sync)
function Member_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Member(ref_actor)
p_Ready()
endFunction

function Unmember_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Unmember(ref_actor)
p_Ready()
endFunction

function Clone_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Clone(ref_actor)
p_Ready()
endFunction

function Unclone_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Unclone(ref_actor)
p_Ready()
endFunction

function Settle(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Settle(ref_actor, auto_create)
p_Ready()
endFunction

function Resettle(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Resettle(ref_actor, auto_create)
p_Ready()
endFunction

function Unsettle(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Unsettle(ref_actor, auto_create)
p_Ready()
endFunction

function Enthrall(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Enthrall(ref_actor, auto_create)
p_Ready()
endFunction

function Unthrall(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Unthrall(ref_actor, auto_create)
p_Ready()
endFunction

function Mobilize(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Mobilize(ref_actor, auto_create)
p_Ready()
endFunction

function Immobilize(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Immobilize(ref_actor, auto_create)
p_Ready()
endFunction

function Paralyze(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Paralyze(ref_actor, auto_create)
p_Ready()
endFunction

function Unparalyze(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Unparalyze(ref_actor, auto_create)
p_Ready()
endFunction

function Follow_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Follow(ref_actor, auto_create)
p_Ready()
endFunction

function Unfollow_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Unfollow(ref_actor, auto_create)
p_Ready()
endFunction

function Sneak_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Sneak(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Unsneak_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Unsneak(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Saddle_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Saddle(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Unsaddle_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Unsaddle(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Pack_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Pack(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Stash(Actor ref_actor)
p_Busy()
    PRIVATE.Stash(ref_actor)
p_Ready()
endFunction

function Outfit_Current_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Current(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Outfit_Member_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Member(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Outfit_Settler_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Settler(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Outfit_Thrall_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Thrall(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Outfit_Follower_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Follower(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Outfit_Immobile_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Immobile(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Outfit_Vanilla_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Vanilla(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Outfit_Default_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Outfit_Default(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Stylize_Default(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Stylize_Default(ref_actor, auto_create)
p_Ready()
endFunction

function Stylize_Warrior(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Stylize_Warrior(ref_actor, auto_create)
p_Ready()
endFunction

function Stylize_Mage(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Stylize_Mage(ref_actor, auto_create)
p_Ready()
endFunction

function Stylize_Archer(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Stylize_Archer(ref_actor, auto_create)
p_Ready()
endFunction

function Stylize_Coward(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Stylize_Coward(ref_actor, auto_create)
p_Ready()
endFunction

function Vitalize_Mortal(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Vitalize_Mortal(ref_actor, auto_create)
p_Ready()
endFunction

function Vitalize_Protected(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Vitalize_Protected(ref_actor, auto_create)
p_Ready()
endFunction

function Vitalize_Essential(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Vitalize_Essential(ref_actor, auto_create)
p_Ready()
endFunction

function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Vitalize_Invulnerable(ref_actor, auto_create)
p_Ready()
endFunction

function Move_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Move(ref_actor)
p_Ready()
endFunction

function Summon_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Summon(ref_actor)
p_Ready()
endFunction

function Goto_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Goto(ref_actor)
p_Ready()
endFunction

function Resurrect_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Resurrect(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Reanimate_Sync(Actor ref_actor, bool auto_create)
p_Busy()
    PRIVATE.Reanimate(doticu_npcp_codes.SYNC(), ref_actor, auto_create)
p_Ready()
endFunction

function Mannequinize(Actor ref_actor, ObjectReference ref_marker, bool auto_create)
p_Busy()
    PRIVATE.Mannequinize(ref_actor, ref_marker, auto_create)
p_Ready()
endFunction

function Unmannequinize(Actor ref_actor)
p_Busy()
    PRIVATE.Unmannequinize(ref_actor)
p_Ready()
endFunction

function Expo(int id_expoee, ObjectReference ref_marker, bool auto_create)
p_Busy()
    MANNEQUINS.Expo(id_expoee, ref_marker, auto_create)
p_Ready()
endFunction

function Unexpo(int id_expoee)
p_Busy()
    MANNEQUINS.Unexpo(id_expoee)
p_Ready()
endFunction

function Toggle_Member_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Member(ref_actor)
p_Ready()
endFunction

function Toggle_Clone_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Clone(ref_actor)
p_Ready()
endFunction

function Toggle_Settler(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Settler(ref_actor)
p_Ready()
endFunction

function Toggle_Thrall(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Thrall(ref_actor)
p_Ready()
endFunction

function Toggle_Immobile(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Immobile(ref_actor)
p_Ready()
endFunction

function Toggle_Paralyzed(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Paralyzed(ref_actor)
p_Ready()
endFunction

function Toggle_Follower_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Follower(ref_actor)
p_Ready()
endFunction

function Toggle_Sneak_Sync(Actor ref_actor)
p_Busy()
    PRIVATE.Toggle_Sneak(doticu_npcp_codes.SYNC(), ref_actor)
p_Ready()
endFunction

function Toggle_Mannequin(Actor ref_actor, ObjectReference ref_marker)
p_Busy()
    PRIVATE.Toggle_Mannequin(ref_actor, ref_marker)
p_Ready()
endFunction

function Toggle_Expoee(int id_expoee, ObjectReference ref_marker)
p_Busy()
    if MANNEQUINS.Is_ID_Free(id_expoee)
        MANNEQUINS.Expo(id_expoee, ref_marker, true)
    else
        MANNEQUINS.Unexpo(id_expoee)
    endIf
p_Ready()
endFunction

; Public Methods (Async)
function Member_Async(Actor ref_actor)
    PRIVATE.Member(ref_actor)
endFunction

function Unmember_Async(Actor ref_actor)
    PRIVATE.Unmember(ref_actor)
endFunction

function Clone_Async(Actor ref_actor)
    PRIVATE.Clone(ref_actor)
endFunction

function Unclone_Async(Actor ref_actor)
    PRIVATE.Unclone(ref_actor)
endFunction

function Sneak_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Sneak(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Unsneak_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Unsneak(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Pack_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Pack(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Outfit_Current_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Current(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Outfit_Member_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Member(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Outfit_Settler_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Settler(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Outfit_Thrall_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Thrall(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Outfit_Follower_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Follower(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Outfit_Immobile_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Immobile(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Summon_Async(Actor ref_actor)
    PRIVATE.Summon(ref_actor)
endFunction

function Resurrect_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Resurrect(doticu_npcp_codes.ASYNC(), ref_actor, auto_create)
endFunction

function Toggle_Sneak_Async(Actor ref_actor)
    PRIVATE.Toggle_Sneak(doticu_npcp_codes.ASYNC(), ref_actor)
endFunction

function Toggle_Saddler_Async(Actor ref_actor)
    PRIVATE.Toggle_Saddle(doticu_npcp_codes.ASYNC(), ref_actor)
endFunction

; "all", "mobile", "immobile", follower cycle, etc, such that they each summon one after another

; Private States
state p_STATE_BUSY
    function Member_Sync(Actor ref_actor)
    endFunction
    function Unmember_Sync(Actor ref_actor)
    endFunction
    function Clone_Sync(Actor ref_actor)
    endFunction
    function Unclone_Sync(Actor ref_actor)
    endFunction
    function Mobilize(Actor ref_actor, bool auto_create)
    endFunction
    function Immobilize(Actor ref_actor, bool auto_create)
    endFunction
    function Settle(Actor ref_actor, bool auto_create)
    endFunction
    function Resettle(Actor ref_actor, bool auto_create)
    endFunction
    function Unsettle(Actor ref_actor, bool auto_create)
    endFunction
    function Enthrall(Actor ref_actor, bool auto_create)
    endFunction
    function Unthrall(Actor ref_actor, bool auto_create)
    endFunction
    function Paralyze(Actor ref_actor, bool auto_create)
    endFunction
    function Unparalyze(Actor ref_actor, bool auto_create)
    endFunction
    function Follow_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Unfollow_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Sneak_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Unsneak_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Saddle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Unsaddle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Pack_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Stash(Actor ref_actor)
    endFunction
    function Outfit_Member_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Settler_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Thrall_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Follower_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Immobile_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Vanilla_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Default_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Stylize_Default(Actor ref_actor, bool auto_create)
    endFunction
    function Stylize_Warrior(Actor ref_actor, bool auto_create)
    endFunction
    function Stylize_Mage(Actor ref_actor, bool auto_create)
    endFunction
    function Stylize_Archer(Actor ref_actor, bool auto_create)
    endFunction
    function Stylize_Coward(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Mortal(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Protected(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Essential(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    endFunction

    function Move_Sync(Actor ref_actor)
    endFunction
    function Summon_Sync(Actor ref_actor)
    endFunction
    function Goto_Sync(Actor ref_actor)
    endFunction
    function Resurrect_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Reanimate_Sync(Actor ref_actor, bool auto_create)
    endFunction

    function Mannequinize(Actor ref_actor, ObjectReference ref_marker, bool auto_create)
    endFunction
    function Unmannequinize(Actor ref_actor)
    endFunction
    function Expo(int id_mannequin, ObjectReference ref_marker, bool auto_create)
    endFunction
    function Unexpo(int id_mannequin)
    endFunction

    function Toggle_Member_Sync(Actor ref_actor)
    endFunction
    function Toggle_Clone_Sync(Actor ref_actor)
    endFunction
    function Toggle_Settler(Actor ref_actor)
    endFunction
    function Toggle_Thrall(Actor ref_actor)
    endFunction
    function Toggle_Immobile(Actor ref_actor)
    endFunction
    function Toggle_Paralyzed(Actor ref_actor)
    endFunction
    function Toggle_Follower_Sync(Actor ref_actor)
    endFunction
    function Toggle_Sneak_Sync(Actor ref_actor)
    endFunction
    function Toggle_Mannequin(Actor ref_actor, ObjectReference ref_marker)
    endFunction
    function Toggle_Expoee(int id_expoee, ObjectReference ref_marker)
    endFunction
    
    function Cycle_Style(Actor ref_actor, bool auto_create)
    endFunction
    function Cycle_Vitality(Actor ref_actor, bool auto_create)
    endFunction

    function Members_Display_Start()
    endFunction
    function Members_Display_Stop()
    endFunction
    function Members_Display_Next()
    endFunction
    function Members_Display_Previous()
    endFunction

    function Toggle_Members_Display()
    endFunction
    
    function Followers_Summon_All()
    endFunction
    function Followers_Summon_Mobile()
    endFunction
    function Followers_Summon_Immobile()
    endFunction
    function Followers_Settle()
    endFunction
    function Followers_Unsettle()
    endFunction
    function Followers_Immobilize()
    endFunction
    function Followers_Mobilize()
    endFunction
    function Followers_Sneak()
    endFunction
    function Followers_Unsneak()
    endFunction
    function Followers_Saddle()
    endFunction
    function Followers_Unsaddle()
    endFunction
    function Followers_Stash()
    endFunction
    function Followers_Resurrect()
    endFunction
    function Followers_Unfollow()
    endFunction
    function Followers_Unmember()
    endFunction
    
    function Toggle_Followers_Settle()
    endFunction
    function Toggle_Followers_Immobilize()
    endFunction
    function Toggle_Followers_Sneak()
    endFunction
endState

state f_STATE_UPDATING
    function Cycle_Style(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Cycle_Vitality(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Members_Display_Start()
        LOGS.Notify_Is_Updating()
    endFunction
    function Members_Display_Stop()
        LOGS.Notify_Is_Updating()
    endFunction
    function Members_Display_Next()
        LOGS.Notify_Is_Updating()
    endFunction
    function Members_Display_Previous()
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Members_Display()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Summon_All()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Summon_Mobile()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Summon_Immobile()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Settle()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Unsettle()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Immobilize()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Mobilize()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Sneak()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Unsneak()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Saddle()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Unsaddle()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Stash()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Resurrect()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Unfollow()
        LOGS.Notify_Is_Updating()
    endFunction
    function Followers_Unmember()
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Followers_Settle()
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Followers_Immobilize()
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Followers_Sneak()
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Show(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Show(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitality_Show(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Member_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unmember_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Clone_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unclone_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Settle(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unsettle(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Resettle(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Enthrall(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unthrall(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Immobilize(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Mobilize(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Paralyze(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unparalyze(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Mannequinize(Actor ref_actor, ObjectReference ref_marker, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unmannequinize(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Follow_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unfollow_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Sneak_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unsneak_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Saddle_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unsaddle_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Pack_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Stash(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Current_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Member_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Settler_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Thrall_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Follower_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Immobile_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Vanilla_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Default_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Stylize_Default(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Stylize_Warrior(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Stylize_Mage(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Stylize_Archer(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Stylize_Coward(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Mortal(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Protected(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Essential(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Move_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Summon_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Goto_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Resurrect_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Reanimate_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Expo(int id_mannequin, ObjectReference ref_marker, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unexpo(int id_mannequin)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Member_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Clone_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Settler(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Thrall(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Immobile(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Paralyzed(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Follower_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Sneak_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Mannequin(Actor ref_actor, ObjectReference ref_marker)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Expoee(int id_expoee, ObjectReference ref_marker)
        LOGS.Notify_Is_Updating()
    endFunction
    function Member_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unmember_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Clone_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unclone_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Sneak_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unsneak_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Pack_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Current_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Member_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Settler_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Thrall_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Follower_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Outfit_Immobile_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Summon_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Resurrect_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Sneak_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Saddler_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
endState
