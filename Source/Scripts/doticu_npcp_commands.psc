;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_commands extends Quest

; Modules
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_queues property QUEUES hidden
    doticu_npcp_queues function Get()
        return p_DATA.MODS.FUNCS.QUEUES
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return p_DATA.MODS.FUNCS.MANNEQUINS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_commands_p property PRIVATE hidden
    doticu_npcp_commands_p function Get()
        return (self as Quest) as doticu_npcp_commands_p
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA              =  none

; Private Variables
bool                p_is_created        = false
doticu_npcp_queue   p_queue_commands    =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    PRIVATE.f_Create(DATA)

    p_is_created = true
    p_queue_commands = QUEUES.Create("commands", 64, 0.1)
    p_queue_commands.Use_Forms()
    p_queue_commands.Use_Bools()
endFunction

function f_Destroy()
    QUEUES.Destroy(p_queue_commands)

    p_queue_commands = none
    p_is_created = false

    PRIVATE.f_Destroy()
endFunction

function f_Register()
    PRIVATE.f_Register()

    p_queue_commands.Register_Form(self as form, "On_Queue_Commands")
endFunction

; Private Methods
function p_Enqueue(string str_message, Actor ref_actor, bool opt_bool = false)
    p_queue_commands.Enqueue_Form_Bool(str_message, ref_actor as Form, opt_bool, 0.1)
endFunction

; Public Methods
function Cycle_Style(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Cycle_Style", ref_actor, auto_create)
    GotoState("")
endFunction

function Cycle_Vitality(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Cycle_Vitality", ref_actor, auto_create)
    GotoState("")
endFunction


function Members_Display_Start(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Members_Display_Start", ref_actor)
    GotoState("")
endFunction

function Members_Display_Stop()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Members_Display_Stop", none)
    GotoState("")
endFunction

function Members_Display_Next()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Members_Display_Next", none)
    GotoState("")
endFunction

function Members_Display_Previous()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Members_Display_Previous", none)
    GotoState("")
endFunction


function Toggle_Members_Display(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Members_Display", ref_actor)
    GotoState("")
endFunction


function Followers_Summon_All()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Summon_All", none)
    GotoState("")
endFunction

function Followers_Summon_Mobile()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Summon_Mobile", none)
    GotoState("")
endFunction

function Followers_Summon_Immobile()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Summon_Immobile", none)
    GotoState("")
endFunction

function Followers_Settle()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Settle", none)
    GotoState("")
endFunction

function Followers_Unsettle()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Unsettle", none)
    GotoState("")
endFunction

function Followers_Immobilize()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Immobilize", none)
    GotoState("")
endFunction

function Followers_Mobilize()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Mobilize", none)
    GotoState("")
endFunction

function Followers_Sneak()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Sneak", none)
    GotoState("")
endFunction

function Followers_Unsneak()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Unsneak", none)
    GotoState("")
endFunction

function Followers_Saddle()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Saddle", none)
    GotoState("")
endFunction

function Followers_Unsaddle()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Unsaddle", none)
    GotoState("")
endFunction

function Followers_Stash()
    GotoState("p_STATE_BUSY")
    PRIVATE.Followers_Stash()
    GotoState("")
endFunction

function Followers_Resurrect()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Resurrect", none)
    GotoState("")
endFunction

function Followers_Unfollow()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Unfollow", none)
    GotoState("")
endFunction

function Followers_Unmember()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Unmember", none)
    GotoState("")
endFunction


function Toggle_Followers_Settle()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Followers_Settle", none)
    GotoState("")
endFunction

function Toggle_Followers_Immobilize()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Followers_Immobilize", none)
    GotoState("")
endFunction

function Toggle_Followers_Sneak()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Followers_Sneak", none)
    GotoState("")
endFunction

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
    GotoState("p_STATE_BUSY")
    PRIVATE.Member(ref_actor)
    GotoState("")
endFunction

function Unmember_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unmember(ref_actor)
    GotoState("")
endFunction

function Clone_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Clone(ref_actor)
    GotoState("")
endFunction

function Unclone_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unclone(ref_actor)
    GotoState("")
endFunction

function Settle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Settle(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Unsettle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unsettle(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Resettle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Resettle(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Enthrall_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Enthrall(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Unthrall_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unthrall(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Immobilize_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Immobilize(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Mobilize_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Mobilize(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Paralyze_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Paralyze(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Unparalyze_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unparalyze(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Follow_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Follow(ref_actor, auto_create)
    GotoState("")
endFunction

function Unfollow_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unfollow(ref_actor, auto_create)
    GotoState("")
endFunction

function Sneak_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Sneak(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Unsneak_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unsneak(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Saddle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Saddle(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Unsaddle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unsaddle(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Pack_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Pack(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Stash(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Stash(ref_actor)
    GotoState("")
endFunction

function Outfit_Current_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Current(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Member_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Member(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Settler_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Settler(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Thrall_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Thrall(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Follower_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Follower(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Immobile_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Immobile(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Vanilla_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Vanilla(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Default_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Outfit_Default(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Default_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Style_Default(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Warrior_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Style_Warrior(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Mage_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Style_Mage(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Archer_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Style_Archer(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Coward_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Style_Coward(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Mortal_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Vitalize_Mortal(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Protected_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Vitalize_Protected(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Essential_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Vitalize_Essential(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Invulnerable_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Vitalize_Invulnerable(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Move_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Move(ref_actor)
    GotoState("")
endFunction

function Summon_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Summon(ref_actor)
    GotoState("")
endFunction

function Goto_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Goto(ref_actor)
    GotoState("")
endFunction

function Resurrect_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Resurrect(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Reanimate_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Reanimate(CODES.DO_SYNC, ref_actor, auto_create)
    GotoState("")
endFunction

function Mannequinize_Sync(Actor ref_actor, ObjectReference ref_marker, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Mannequinize(CODES.DO_SYNC, ref_actor, ref_marker, auto_create)
    GotoState("")
endFunction

function Unmannequinize_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unmannequinize(CODES.DO_SYNC, ref_actor)
    GotoState("")
endFunction

function Expo_Sync(int id_expoee, ObjectReference ref_marker, bool auto_create)
    GotoState("p_STATE_BUSY")
    MANNEQUINS.Expo(CODES.DO_SYNC, id_expoee, ref_marker, auto_create)
    GotoState("")
endFunction

function Unexpo_Sync(int id_expoee)
    GotoState("p_STATE_BUSY")
    MANNEQUINS.Unexpo(CODES.DO_SYNC, id_expoee)
    GotoState("")
endFunction

function Toggle_Member_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Member(ref_actor)
    GotoState("")
endFunction

function Toggle_Clone_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Clone(ref_actor)
    GotoState("")
endFunction

function Toggle_Settler_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Settler(CODES.DO_SYNC, ref_actor)
    GotoState("")
endFunction

function Toggle_Thrall_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Thrall(CODES.DO_SYNC, ref_actor)
    GotoState("")
endFunction

function Toggle_Immobile_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Immobile(CODES.DO_SYNC, ref_actor)
    GotoState("")
endFunction

function Toggle_Paralyzed_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Paralyzed(CODES.DO_SYNC, ref_actor)
    GotoState("")
endFunction

function Toggle_Follower_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Follower(ref_actor)
    GotoState("")
endFunction

function Toggle_Sneak_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Sneak(CODES.DO_SYNC, ref_actor)
    GotoState("")
endFunction

function Toggle_Mannequin_Sync(Actor ref_actor, ObjectReference ref_marker)
    GotoState("p_STATE_BUSY")
    PRIVATE.Toggle_Mannequin(CODES.DO_SYNC, ref_actor, ref_marker)
    GotoState("")
endFunction

function Toggle_Expoee_Sync(int id_expoee, ObjectReference ref_marker)
    GotoState("p_STATE_BUSY")
    if MANNEQUINS.Is_ID_Free(id_expoee)
        MANNEQUINS.Expo(CODES.DO_SYNC, id_expoee, ref_marker, true)
    else
        MANNEQUINS.Unexpo(CODES.DO_SYNC, id_expoee)
    endIf
    GotoState("")
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

function Settle_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Settle(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Unsettle_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Unsettle(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Resettle_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Resettle(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Enthrall_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Enthrall(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Unthrall_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Unthrall(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Immobilize_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Immobilize(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Mobilize_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Mobilize(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Paralyze_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Paralyze(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Unparalyze_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Unparalyze(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Sneak_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Sneak(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Unsneak_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Unsneak(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Pack_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Pack(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Outfit_Current_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Current(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Outfit_Member_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Member(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Outfit_Settler_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Settler(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Outfit_Thrall_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Thrall(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Outfit_Follower_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Follower(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Outfit_Immobile_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Outfit_Immobile(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Style_Default_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Style_Default(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Style_Warrior_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Style_Warrior(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Style_Mage_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Style_Mage(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Style_Archer_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Style_Archer(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Style_Coward_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Style_Coward(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Vitalize_Mortal_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Vitalize_Mortal(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Vitalize_Protected_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Vitalize_Protected(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Vitalize_Essential_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Vitalize_Essential(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction

function Vitalize_Invulnerable_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Vitalize_Invulnerable(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction



function Summon_Async(Actor ref_actor)
    PRIVATE.Summon(ref_actor)
endFunction

function Resurrect_Async(Actor ref_actor, bool auto_create)
    PRIVATE.Resurrect(CODES.DO_ASYNC, ref_actor, auto_create)
endFunction



function Toggle_Settler_Async(Actor ref_actor)
    PRIVATE.Toggle_Settler(CODES.DO_ASYNC, ref_actor)
endFunction

function Toggle_Thrall_Async(Actor ref_actor)
    PRIVATE.Toggle_Thrall(CODES.DO_ASYNC, ref_actor)
endFunction

function Toggle_Immobile_Async(Actor ref_actor)
    PRIVATE.Toggle_Immobile(CODES.DO_ASYNC, ref_actor)
endFunction

function Toggle_Paralyzed_Async(Actor ref_actor)
    PRIVATE.Toggle_Paralyzed(CODES.DO_ASYNC, ref_actor)
endFunction

function Toggle_Sneak_Async(Actor ref_actor)
    PRIVATE.Toggle_Sneak(CODES.DO_ASYNC, ref_actor)
endFunction

function Toggle_Saddler_Async(Actor ref_actor)
    PRIVATE.Toggle_Saddle(CODES.DO_ASYNC, ref_actor)
endFunction

; "all", "mobile", "immobile", follower cycle, etc, such that they each summon one after another

; Events
event On_Queue_Commands(string str_message, Form form_actor, bool auto_create)
    ; this queue should be separated into two, one for members, one for followers,
    ; and removed from this module
    Actor ref_actor = form_actor as Actor

    if p_queue_commands.Should_Cancel()
    
    elseIf str_message == "Cycle_Style"
        PRIVATE.Cycle_Style(ref_actor, auto_create)
    elseIf str_message == "Cycle_Vitality"
        PRIVATE.Cycle_Vitality(ref_actor, auto_create)

    elseIf str_message == "Members_Display_Start"
        PRIVATE.Members_Display_Start(ref_actor)
    elseIf str_message == "Members_Display_Stop"
        PRIVATE.Members_Display_Stop()
    elseIf str_message == "Members_Display_Next"
        PRIVATE.Members_Display_Next()
    elseIf str_message == "Members_Display_Previous"
        PRIVATE.Members_Display_Previous()

    elseIf str_message == "Toggle_Members_Display"
        PRIVATE.Toggle_Members_Display(ref_actor)
    
    elseIf str_message == "Followers_Summon_All"
        PRIVATE.Followers_Summon_All()
    elseIf str_message == "Followers_Summon_Mobile"
        PRIVATE.Followers_Summon_Mobile()
    elseIf str_message == "Followers_Summon_Immobile"
        PRIVATE.Followers_Summon_Immobile()
    elseIf str_message == "Followers_Settle"
        PRIVATE.Followers_Settle()
    elseIf str_message == "Followers_Unsettle"
        PRIVATE.Followers_Unsettle()
    elseIf str_message == "Followers_Immobilize"
        PRIVATE.Followers_Immobilize()
    elseIf str_message == "Followers_Mobilize"
        PRIVATE.Followers_Mobilize()
    elseIf str_message == "Followers_Sneak"
        PRIVATE.Followers_Sneak()
    elseIf str_message == "Followers_Unsneak"
        PRIVATE.Followers_Unsneak()
    elseIf str_message == "Followers_Saddle"
        PRIVATE.Followers_Saddle()
    elseIf str_message == "Followers_Unsaddle"
        PRIVATE.Followers_Unsaddle()
    elseIf str_message == "Followers_Resurrect"
        PRIVATE.Followers_Resurrect()
    elseIf str_message == "Followers_Unfollow"
        PRIVATE.Followers_Unfollow()
    elseIf str_message == "Followers_Unmember"
        PRIVATE.Followers_Unmember()
    
    elseIf str_message == "Toggle_Followers_Settle"
        PRIVATE.Toggle_Followers_Settle()
    elseIf str_message == "Toggle_Followers_Immobilize"
        PRIVATE.Toggle_Followers_Immobilize()
    elseIf str_message == "Toggle_Followers_Sneak"
        PRIVATE.Toggle_Followers_Sneak()
    
    endIf

    p_queue_commands.Dequeue()
endEvent

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
    function Settle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Unsettle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Resettle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Enthrall_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Unthrall_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Immobilize_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Mobilize_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Paralyze_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Unparalyze_Sync(Actor ref_actor, bool auto_create)
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
    function Style_Default_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Warrior_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Mage_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Archer_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Coward_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Mortal_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Protected_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Essential_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Invulnerable_Sync(Actor ref_actor, bool auto_create)
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

    function Mannequinize_Sync(Actor ref_actor, ObjectReference ref_marker, bool auto_create)
    endFunction
    function Unmannequinize_Sync(Actor ref_actor)
    endFunction
    function Expo_Sync(int id_mannequin, ObjectReference ref_marker, bool auto_create)
    endFunction
    function Unexpo_Sync(int id_mannequin)
    endFunction

    function Toggle_Member_Sync(Actor ref_actor)
    endFunction
    function Toggle_Clone_Sync(Actor ref_actor)
    endFunction
    function Toggle_Settler_Sync(Actor ref_actor)
    endFunction
    function Toggle_Thrall_Sync(Actor ref_actor)
    endFunction
    function Toggle_Immobile_Sync(Actor ref_actor)
    endFunction
    function Toggle_Paralyzed_Sync(Actor ref_actor)
    endFunction
    function Toggle_Follower_Sync(Actor ref_actor)
    endFunction
    function Toggle_Sneak_Sync(Actor ref_actor)
    endFunction
    function Toggle_Mannequin_Sync(Actor ref_actor, ObjectReference ref_marker)
    endFunction
    function Toggle_Expoee_Sync(int id_expoee, ObjectReference ref_marker)
    endFunction
    
    function Cycle_Style(Actor ref_actor, bool auto_create)
    endFunction
    function Cycle_Vitality(Actor ref_actor, bool auto_create)
    endFunction

    function Members_Display_Start(Actor ref_actor)
    endFunction
    function Members_Display_Stop()
    endFunction
    function Members_Display_Next()
    endFunction
    function Members_Display_Previous()
    endFunction

    function Toggle_Members_Display(Actor ref_actor)
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
    function Members_Display_Start(Actor ref_actor)
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
    function Toggle_Members_Display(Actor ref_actor)
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
    function Settle_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unsettle_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Resettle_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Enthrall_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unthrall_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Immobilize_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Mobilize_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Paralyze_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unparalyze_Sync(Actor ref_actor, bool auto_create)
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
    function Style_Default_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Warrior_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Mage_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Archer_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Coward_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Mortal_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Protected_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Essential_Sync(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Invulnerable_Sync(Actor ref_actor, bool auto_create)
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
    function Mannequinize_Sync(Actor ref_actor, ObjectReference ref_marker, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unmannequinize_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Expo_Sync(int id_mannequin, ObjectReference ref_marker, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unexpo_Sync(int id_mannequin)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Member_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Clone_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Settler_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Thrall_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Immobile_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Paralyzed_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Follower_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Sneak_Sync(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Mannequin_Sync(Actor ref_actor, ObjectReference ref_marker)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Expoee_Sync(int id_expoee, ObjectReference ref_marker)
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
    function Settle_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unsettle_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Resettle_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Enthrall_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unthrall_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Immobilize_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Mobilize_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Paralyze_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Unparalyze_Async(Actor ref_actor, bool auto_create)
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
    function Style_Default_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Warrior_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Mage_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Archer_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Style_Coward_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Mortal_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Protected_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Essential_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Vitalize_Invulnerable_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Summon_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Resurrect_Async(Actor ref_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Settler_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Thrall_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Immobile_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Paralyzed_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Sneak_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    function Toggle_Saddler_Async(Actor ref_actor)
        LOGS.Notify_Is_Updating()
    endFunction
    event On_Queue_Commands(string str_message, Form form_actor, bool auto_create)
        LOGS.Notify_Is_Updating()
    endEvent
endState
