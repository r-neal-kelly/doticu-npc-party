Scriptname doticu_npcp_player extends ReferenceAlias

; Private Constants
doticu_npcp_data        p_DATA          = none
doticu_npcp_consts      p_CONSTS        = none
doticu_npcp_codes       p_CODES         = none
doticu_npcp_vars        p_VARS          = none
doticu_npcp_funcs       p_FUNCS         = none
doticu_npcp_actors      p_ACTORS        = none
doticu_npcp_queues      p_QUEUES        = none
doticu_npcp_followers   p_FOLLOWERS     = none
doticu_npcp_main        p_MAIN          = none

Actor                   p_REF_PLAYER    = none
doticu_npcp_queue       p_QUEUE_PLAYER  = none

; Private Variables
bool p_is_in_combat = false

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_DATA = DATA
    p_REF_PLAYER = p_CONSTS.ACTOR_PLAYER

    p_Create_Queues()
endFunction

function f_Register()
    RegisterForModEvent("doticu_npcp_queue_" + "player", "On_Queue_Player")
endFunction

function f_Begin_Combat()
    if !p_is_in_combat
        p_is_in_combat = true
        p_QUEUE_PLAYER.Enqueue("f_Try_End_Combat()", 5.0)
    endIf
endFunction

function f_End_Combat()
    if p_is_in_combat
        p_is_in_combat = false
        p_QUEUE_PLAYER.Flush()
        if p_VARS.auto_resurrect
            p_FOLLOWERS.Resurrect()
        endIf
    endIf
endFunction

function f_Try_End_Combat()
    if p_REF_PLAYER.IsInCombat()
        p_QUEUE_PLAYER.Enqueue("f_Try_End_Combat()", 5.0)
    else
        f_End_Combat()
    endIf
endFunction

; Private Methods
function p_Create_Queues()
    p_QUEUE_PLAYER = p_QUEUES.Create("player", 32, 5.0)
endFunction

function p_Destroy_Queues()
    p_QUEUES.Destroy(p_QUEUE_PLAYER)
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    p_REF_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    p_REF_PLAYER.RemovePerk(perk_to_remove)
endFunction

; Update Methods
function u_0_1_1()
    p_Create_Queues()
endFunction

function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
    p_QUEUE_PLAYER.u_0_1_4(p_DATA)
endFunction

; Events
event OnPlayerLoadGame()
    p_MAIN.f_Load_Mod()
endEvent

event On_Queue_Player(string str_message)
    if str_message == "f_Try_End_Combat()"
        f_Try_End_Combat()
    endIf

    p_QUEUE_PLAYER.Dequeue()
endEvent

event OnActorAction(int code_action, Actor ref_activator, Form form_source, int slot)
endEvent
