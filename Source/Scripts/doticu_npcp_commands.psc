Scriptname doticu_npcp_commands extends Quest

; Modules
doticu_npcp_queues property QUEUES hidden
    doticu_npcp_queues function Get()
        return p_DATA.MODS.FUNCS.QUEUES
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

function p_Excise(string str_message)
    p_queue_commands.Excise(str_message)
endFunction

; Public Methods




function Unmember(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Unmember", ref_actor)
    GotoState("")
    ; I would like this one to wait before returning, because of how dialogue menus work.
endFunction

function Clone(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Clone", ref_actor)
    GotoState("")
endFunction

function Unclone(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Unclone", ref_actor)
    GotoState("")
    ; I would like this one to wait before returning, because of how dialogue menus work.
endFunction

function Pack(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Pack", ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Current(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Outfit_Current", ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Member(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Outfit_Member", ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Settler(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Outfit_Settler", ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Thrall(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Outfit_Thrall", ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Follower(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Outfit_Follower", ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Immobile(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Outfit_Immobile", ref_actor, auto_create)
    GotoState("")
endFunction

function Unoutfit(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Unoutfit", ref_actor, auto_create)
    GotoState("")
endFunction

function Resurrect(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Resurrect", ref_actor, auto_create)
    GotoState("")
endFunction



function Enthrall(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Enthrall", ref_actor, auto_create)
    GotoState("")
endFunction

function Unthrall(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Unthrall", ref_actor, auto_create)
    GotoState("")
endFunction

function Immobilize_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Immobilize(ref_actor, auto_create)
    GotoState("")
endFunction

function Immobilize_Async(Actor ref_actor, bool auto_create)
    p_Enqueue("Immobilize", ref_actor, auto_create)
    p_queue_commands.Excise("Mobilize")
endFunction

function Mobilize_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Mobilize(ref_actor, auto_create)
    GotoState("")
endFunction

function Mobilize_Async(Actor ref_actor, bool auto_create)
    p_Enqueue("Mobilize", ref_actor, auto_create)
    p_queue_commands.Excise("Immobilize")
endFunction

function Paralyze(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Paralyze", ref_actor, auto_create)
    GotoState("")
endFunction

function Unparalyze(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Unparalyze", ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Default(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Style_Default", ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Warrior(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Style_Warrior", ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Mage(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Style_Mage", ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Archer(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Style_Archer", ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Mortal(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Vitalize_Mortal", ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Protected(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Vitalize_Protected", ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Essential(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Vitalize_Essential", ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Vitalize_Invulnerable", ref_actor, auto_create)
    GotoState("")
endFunction

function Follow(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Follow", ref_actor, auto_create)
    GotoState("")
endFunction

function Unfollow(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Unfollow", ref_actor, auto_create)
    GotoState("")
endFunction

function Sneak(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Sneak", ref_actor, auto_create)
    GotoState("")
endFunction

function Unsneak(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Unsneak", ref_actor, auto_create)
    GotoState("")
endFunction






function Toggle_Member(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Member", ref_actor)
    GotoState("")
endFunction

function Toggle_Settler(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Settler", ref_actor)
    GotoState("")
endFunction

function Toggle_Thrall(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Thrall", ref_actor)
    GotoState("")
endFunction

function Toggle_Immobile(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Immobile", ref_actor)
    GotoState("")
endFunction

function Toggle_Paralyzed(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Paralyzed", ref_actor)
    GotoState("")
endFunction

function Toggle_Follower(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Follower", ref_actor)
    GotoState("")
endFunction

function Toggle_Sneak(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Enqueue("Toggle_Sneak", ref_actor)
    GotoState("")
endFunction


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

function Followers_Summon_Mobile_Behind()
    GotoState("p_STATE_BUSY")
    p_Enqueue("Followers_Summon_Mobile_Behind", none)
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





; Public Methods (Sync)
function Member_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Member(ref_actor)
    GotoState("")
endFunction

function Summon_Sync(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    PRIVATE.Summon(ref_actor)
    GotoState("")
endFunction

function Settle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Settle(ref_actor, auto_create)
    GotoState("")
endFunction

function Resettle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Resettle(ref_actor, auto_create)
    GotoState("")
endFunction

function Unsettle_Sync(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    PRIVATE.Unsettle(ref_actor, auto_create)
    GotoState("")
endFunction

; Public Methods (Async)
function Member_Async(Actor ref_actor)
    p_Enqueue("Member", ref_actor)
    p_Excise("Unmember")
endFunction

function Summon_Async(Actor ref_actor)
    p_Enqueue("Summon", ref_actor)
    p_Excise("Banish"); not used currently
endFunction

function Settle_Async(Actor ref_actor, bool auto_create)
    p_Enqueue("Settle", ref_actor, auto_create)
    p_Excise("Unsettle")
    p_Excise("Resettle")
endFunction

function Resettle_Async(Actor ref_actor, bool auto_create)
    p_Enqueue("Resettle", ref_actor, auto_create)
    p_Excise("Settle")
    p_Excise("Unsettle")
endFunction

function Unsettle_Async(Actor ref_actor, bool auto_create)
    p_Enqueue("Unsettle", ref_actor, auto_create)
    p_Excise("Settle")
    p_Excise("Resettle")
endFunction

; should have a "Member" and "Follower" summon cycle. Very mush desired, so it's easy to pick them out of all the names.

; "all", "mobile", "immobile", follower cycle, etc, such that they each summon one after another

; States
state p_STATE_BUSY
    function Member_Sync(Actor ref_actor)
    endFunction
    function Unmember(Actor ref_actor)
    endFunction
    function Clone(Actor ref_actor)
    endFunction
    function Unclone(Actor ref_actor)
    endFunction
    function Pack(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Member(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Settler(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Thrall(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Follower(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Immobile(Actor ref_actor, bool auto_create)
    endFunction
    function Unoutfit(Actor ref_actor, bool auto_create)
    endFunction
    function Resurrect(Actor ref_actor, bool auto_create)
    endFunction
    function Settle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Resettle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Unsettle_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Enthrall(Actor ref_actor, bool auto_create)
    endFunction
    function Unthrall(Actor ref_actor, bool auto_create)
    endFunction
    function Immobilize_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Mobilize_Sync(Actor ref_actor, bool auto_create)
    endFunction
    function Paralyze(Actor ref_actor, bool auto_create)
    endFunction
    function Unparalyze(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Default(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Warrior(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Mage(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Archer(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Mortal(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Protected(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Essential(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    endFunction
    function Follow(Actor ref_actor, bool auto_create)
    endFunction
    function Unfollow(Actor ref_actor, bool auto_create)
    endFunction
    function Sneak(Actor ref_actor, bool auto_create)
    endFunction
    function Unsneak(Actor ref_actor, bool auto_create)
    endFunction
    function Summon_Sync(Actor ref_actor)
    endFunction
    
    function Toggle_Member(Actor ref_actor)
    endFunction
    function Toggle_Settler(Actor ref_actor)
    endFunction
    function Toggle_Thrall(Actor ref_actor)
    endFunction
    function Toggle_Immobile(Actor ref_actor)
    endFunction
    function Toggle_Paralyzed(Actor ref_actor)
    endFunction
    function Toggle_Follower(Actor ref_actor)
    endFunction
    function Toggle_Sneak(Actor ref_actor)
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
    function Followers_Summon_Mobile_Behind()
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

; Events
event On_Queue_Commands(string str_message, Form form_actor, bool auto_create)
    Actor ref_actor = form_actor as Actor

    if p_queue_commands.Should_Cancel()

    elseIf str_message == "Member"
        PRIVATE.Member(ref_actor)
    elseIf str_message == "Unmember"
        PRIVATE.Unmember(ref_actor)
    elseIf str_message == "Clone"
        PRIVATE.Clone(ref_actor)
    elseIf str_message == "Unclone"
        PRIVATE.Unclone(ref_actor)
    elseIf str_message == "Pack"
        PRIVATE.Pack(ref_actor, auto_create)
    elseIf str_message == "Outfit_Current"
        PRIVATE.Outfit_Current(ref_actor, auto_create)
    elseIf str_message == "Outfit_Member"
        PRIVATE.Outfit_Member(ref_actor, auto_create)
    elseIf str_message == "Outfit_Settler"
        PRIVATE.Outfit_Settler(ref_actor, auto_create)
    elseIf str_message == "Outfit_Thrall"
        PRIVATE.Outfit_Thrall(ref_actor, auto_create)
    elseIf str_message == "Outfit_Follower"
        PRIVATE.Outfit_Follower(ref_actor, auto_create)
    elseIf str_message == "Outfit_Immobile"
        PRIVATE.Outfit_Immobile(ref_actor, auto_create)
    elseIf str_message == "Unoutfit"
        PRIVATE.Unoutfit(ref_actor, auto_create)
    elseIf str_message == "Resurrect"
        PRIVATE.Resurrect(ref_actor, auto_create)
    elseIf str_message == "Settle"
        PRIVATE.Settle(ref_actor, auto_create)
    elseIf str_message == "Resettle"
        PRIVATE.Resettle(ref_actor, auto_create)
    elseIf str_message == "Unsettle"
        PRIVATE.Unsettle(ref_actor, auto_create)
    elseIf str_message == "Enthrall"
        PRIVATE.Enthrall(ref_actor, auto_create)
    elseIf str_message == "Unthrall"
        PRIVATE.Unthrall(ref_actor, auto_create)
    elseIf str_message == "Immobilize"
        PRIVATE.Immobilize(ref_actor, auto_create)
    elseIf str_message == "Mobilize"
        PRIVATE.Mobilize(ref_actor, auto_create)
    elseIf str_message == "Paralyze"
        PRIVATE.Paralyze(ref_actor, auto_create)
    elseIf str_message == "Unparalyze"
        PRIVATE.Unparalyze(ref_actor, auto_create)
    elseIf str_message == "Style_Default"
        PRIVATE.Style_Default(ref_actor, auto_create)
    elseIf str_message == "Style_Warrior"
        PRIVATE.Style_Warrior(ref_actor, auto_create)
    elseIf str_message == "Style_Mage"
        PRIVATE.Style_Mage(ref_actor, auto_create)
    elseIf str_message == "Style_Archer"
        PRIVATE.Style_Archer(ref_actor, auto_create)
    elseIf str_message == "Vitalize_Mortal"
        PRIVATE.Vitalize_Mortal(ref_actor, auto_create)
    elseIf str_message == "Vitalize_Protected"
        PRIVATE.Vitalize_Protected(ref_actor, auto_create)
    elseIf str_message == "Vitalize_Essential"
        PRIVATE.Vitalize_Essential(ref_actor, auto_create)
    elseIf str_message == "Vitalize_Invulnerable"
        PRIVATE.Vitalize_Invulnerable(ref_actor, auto_create)
    elseIf str_message == "Follow"
        PRIVATE.Follow(ref_actor, auto_create)
    elseIf str_message == "Unfollow"
        PRIVATE.Unfollow(ref_actor, auto_create)
    elseIf str_message == "Sneak"
        PRIVATE.Sneak(ref_actor, auto_create)
    elseIf str_message == "Unsneak"
        PRIVATE.Unsneak(ref_actor, auto_create)
    elseIf str_message == "Summon"
        PRIVATE.Summon(ref_actor)

    elseIf str_message == "Toggle_Member"
        PRIVATE.Toggle_Member(ref_actor)
    elseIf str_message == "Toggle_Settler"
        PRIVATE.Toggle_Settler(ref_actor)
    elseIf str_message == "Toggle_Thrall"
        PRIVATE.Toggle_Thrall(ref_actor)
    elseIf str_message == "Toggle_Immobile"
        PRIVATE.Toggle_Immobile(ref_actor)
    elseIf str_message == "Toggle_Paralyzed"
        PRIVATE.Toggle_Paralyzed(ref_actor)
    elseIf str_message == "Toggle_Follower"
        PRIVATE.Toggle_Follower(ref_actor)
    elseIf str_message == "Toggle_Sneak"
        PRIVATE.Toggle_Sneak(ref_actor)
    
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
    elseIf str_message == "Followers_Summon_Mobile_Behind"
        PRIVATE.Followers_Summon_Mobile_Behind()
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
