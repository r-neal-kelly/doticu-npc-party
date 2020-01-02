Scriptname doticu_npcp_player extends ReferenceAlias

; Modules
doticu_npcp_main property MAIN hidden
    doticu_npcp_main function Get()
        return p_DATA.MODS.MAIN
    endFunction
endProperty
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_queues property QUEUES hidden
    doticu_npcp_queues function Get()
        return p_DATA.MODS.FUNCS.QUEUES
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false
Actor               p_ref_player    =  none
bool                p_is_in_combat  = false
doticu_npcp_queue   p_queue_player  =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_ref_player = CONSTS.ACTOR_PLAYER
    p_is_in_combat = false
    p_queue_player = QUEUES.Create("player", 32, 5.0)
endFunction

function f_Destroy()
    QUEUES.Destroy(p_queue_player)
    p_is_in_combat = false
    p_ref_player = none
    p_is_created = false
endFunction

function f_Register()
    RegisterForModEvent("doticu_npcp_queue_" + "player", "On_Queue_Player")
endFunction

function f_Begin_Combat()
    if !p_is_in_combat
        p_is_in_combat = true
        p_queue_player.Enqueue("f_Try_End_Combat()", 5.0)
    endIf
endFunction

function f_End_Combat()
    if p_is_in_combat
        p_is_in_combat = false
        p_queue_player.Flush()
        if VARS.auto_resurrect
            FOLLOWERS.Resurrect()
        endIf
    endIf
endFunction

function f_Try_End_Combat()
    if p_ref_player.IsInCombat()
        p_queue_player.Enqueue("f_Try_End_Combat()", 5.0)
    else
        f_End_Combat()
    endIf
endFunction

; Private Methods
function p_Create_Queues()
    
endFunction

function p_Destroy_Queues()
    QUEUES.Destroy(p_queue_player)
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    p_ref_player.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    p_ref_player.RemovePerk(perk_to_remove)
endFunction

; Update Methods
function u_0_1_1()
    p_Create_Queues()
endFunction

function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
    p_queue_player.u_0_1_4(p_DATA)
endFunction

; Events
event OnPlayerLoadGame()
    MAIN.f_Load_Mod()
endEvent

event On_Queue_Player(string str_message)
    if str_message == "f_Try_End_Combat()"
        f_Try_End_Combat()
    endIf

    p_queue_player.Dequeue()
endEvent

event OnActorAction(int code_action, Actor ref_activator, Form form_source, int slot)
endEvent
