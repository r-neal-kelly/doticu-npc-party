;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_player extends ReferenceAlias

; Modules
doticu_npcp_main property MAIN hidden
    doticu_npcp_main function Get()
        return doticu_npcp.Main()
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return doticu_npcp.Vars()
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return doticu_npcp.Members()
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return doticu_npcp.Followers()
    endFunction
endProperty

; Public Constants
Actor property ACTOR_PLAYER hidden
    Actor function Get()
        return doticu_npcp_consts.Player_Actor()
    endFunction
endProperty

; Private Variables
bool                p_is_created    = false
bool                p_is_locked     = false
bool                p_is_in_combat  = false

; Friend Methods
function f_Create()
    p_is_created = true
    p_is_locked = false
    p_is_in_combat = false
endFunction

function f_Destroy()
    p_is_in_combat = false
    p_is_locked = false
    p_is_created = false
endFunction

function f_Register()
    RegisterForModEvent("doticu_npcp_init_mod", "On_Init_Mod")
    RegisterForModEvent("doticu_npcp_load_mod", "On_Load_Mod")
    RegisterForModEvent("doticu_npcp_cell_change", "On_Cell_Change")
    RegisterForControl("Sneak")
    RegisterForActorAction(doticu_npcp_codes.ACTION_DRAW_END())
endFunction

function f_Unregister()
endFunction

function f_Begin_Combat()
    ; there is no way for PLAYER to know when they are
    ; in combat! so we have followers tell PLAYER to begin
    if p_is_in_combat == false
        p_is_in_combat = true

        FOLLOWERS.Catch_Up()
        if ACTOR_PLAYER.IsSneaking()
            FOLLOWERS.Retreat()
        endIf
        
        FUNCS.Wait(5.0)
        p_Async("p_Try_End_Combat")
    endIf
endFunction

; Private Methods
function p_Lock(float interval = 0.2, float timeout = 5.0)
    float time_waited = 0.0

    while p_is_locked && time_waited < timeout
        FUNCS.Wait(interval)
        time_waited += interval
    endWhile

    p_is_locked = true
endFunction

function p_Unlock()
    p_is_locked = false
endFunction

function p_Async(string str_func)
    string str_event = "doticu_npcp_player_async"

p_Lock()
    RegisterForModEvent(str_event, str_func)
    FUNCS.Send_Event(str_event, 0.25, 1.0)
    UnregisterForModEvent(str_event)
p_Unlock()
endFunction

function p_Try_End_Combat()
    if ACTOR_PLAYER.IsInCombat() || FOLLOWERS.Are_In_Combat()
        FUNCS.Wait(5.0)
        p_Async("p_Try_End_Combat")
    else
        p_End_Combat()
    endIf
endFunction

function p_End_Combat()
    if p_is_in_combat == true
        p_is_in_combat = false
        
        if !ACTOR_PLAYER.IsSneaking()
            FOLLOWERS.Unretreat()
        endIf
        if VARS.auto_resurrect
            FOLLOWERS.Resurrect()
        endIf
    endIf
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    ACTOR_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    ACTOR_PLAYER.RemovePerk(perk_to_remove)
endFunction

bool function Is_Party_In_Combat() native

; Events
event On_Init_Mod()
    ACTORS.Apply_Ability(ACTOR_PLAYER, doticu_npcp_consts.Cell_Ability_Spell())
endEvent

event On_Load_Mod()
    ; just in case it somehow gets stuck, which has happened before
    ACTORS.Apply_Ability(ACTOR_PLAYER, doticu_npcp_consts.Cell_Ability_Spell())

    if !Is_Party_In_Combat()
        ; for some reason, p_is_in_combat sometimes gets stuck to true
        ; and so we never get auto resurrect, but this resets it.
        p_End_Combat()
    endIf
endEvent

event OnControlDown(string str_control)
    if str_control == "Sneak"
        if ACTOR_PLAYER.IsSneaking() && Is_Party_In_Combat()
            FOLLOWERS.Retreat()
        else
            FOLLOWERS.Unretreat()
        endIf
    endIf
endEvent

event OnActorAction(int code_action, Actor ref_actor, Form form_source, int slot)
    if ref_actor == ACTOR_PLAYER
        if code_action == doticu_npcp_codes.ACTION_DRAW_END()
            if !Is_Party_In_Combat()
                FOLLOWERS.Catch_Up()
            endIf
        endIf
    endIf
endEvent

event On_Cell_Change(Form cell_new, Form cell_old)
    ACTORS.Apply_Ability(ACTOR_PLAYER, doticu_npcp_consts.Cell_Ability_Spell())
    FOLLOWERS.Catch_Up()
    FOLLOWERS.Enforce()
endEvent
