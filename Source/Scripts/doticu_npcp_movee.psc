;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_movee extends ReferenceAlias

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
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_keys property KEYS hidden
    doticu_npcp_keys function Get()
        return p_DATA.MODS.CONTROL.KEYS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA                  =  none

float property p_DISTANCE_MIN hidden
    float function Get()
        return 25.0
    endFunction
endProperty
float property p_DISTANCE_MAX hidden
    float function Get()
        return 400.0
    endFunction
endProperty
float property p_DISTANCE_DEFAULT hidden
    float function Get()
        return 150.0
    endFunction
endProperty
float property p_DISTANCE_UNIT hidden
    float function Get()
        return 20.0
    endFunction
endProperty
float property p_ROTATE_UNIT hidden
    float function Get()
        return 12.0
    endFunction
endProperty
float property p_SPEED hidden
    float function Get()
        return 600.0
    endFunction
endProperty
float property p_UPDATE_INTERVAL hidden
    float function Get()
        return 0.001
    endFunction
endProperty

; Private Variable
bool                p_is_created            = false
bool                p_is_executing          = false
Actor               p_ref_actor             =  none
Actor               p_ref_player            =  none
bool                p_is_airborne           = false
bool                p_do_distance_farther   = false
bool                p_do_distance_nearer    = false
bool                p_do_rotate_right       = false
bool                p_do_rotate_left        = false
float               p_movee_pos             =   0.0
float               p_movee_ang             =   0.0

; Friend Methods
function f_Create(doticu_npcp_data DATA, Actor ref_actor)
    p_DATA = DATA

    p_is_created = true
    p_is_executing = false
    p_ref_actor = ref_actor
    p_ref_player = CONSTS.ACTOR_PLAYER
    p_is_airborne = false
    p_do_distance_farther = false
    p_do_distance_nearer = false
    p_do_rotate_right = false
    p_do_rotate_left = false
    p_movee_pos = p_DISTANCE_DEFAULT
    p_movee_ang = p_ref_actor.GetAngleZ()

    ForceRefTo(p_ref_actor)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_MOVEE)
    p_ref_actor.EvaluatePackage()
    ;/p_ref_actor.Disable()
    p_ref_actor.Enable()
    while !p_ref_actor.Is3DLoaded()
        Utility.Wait(0.1)
    endWhile/;
    p_ref_actor.SetActorValue("Paralysis", 1)

    RegisterForSingleUpdate(0.0)
endFunction

function f_Destroy()
    p_is_created = false

    p_Lock_Script()

    p_ref_actor.StopTranslation()
    if p_is_airborne
        p_ref_player.PushActorAway(p_ref_actor, 0.0)
    else
        p_ref_actor.ApplyHavokImpulse(0.0, 0.0, 0.001, 0.001)
    endIf
    p_ref_actor.SetActorValue("Paralysis", 0)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_MOVEE)
    Clear()
    p_ref_actor.EvaluatePackage()

    p_do_rotate_left = false
    p_do_rotate_right = false
    p_do_distance_nearer = false
    p_do_distance_farther = false
    p_is_airborne = false
    p_movee_ang = 0.0
    p_movee_pos = 0.0
    p_ref_player = none
    p_ref_actor = none
    p_is_executing = false
    p_is_created = false

    p_Unlock_Script()
endFunction

function f_Register()
    RegisterForModEvent("doticu_npcp_cell_change", "On_Cell_Change")
    RegisterForModEvent("doticu_npcp_movee_distance_farther", "On_Distance_Farther")
    RegisterForModEvent("doticu_npcp_movee_distance_nearer", "On_Distance_Nearer")
    RegisterForModEvent("doticu_npcp_movee_rotate_left", "On_Rotate_Left")
    RegisterForModEvent("doticu_npcp_movee_rotate_right", "On_Rotate_Right")
    Update_Keys()
endFunction

function f_Unregister()
    UnregisterForAllKeys()
    UnregisterForAllModEvents()
endFunction

; Private Methods
function p_Lock_Script()
    while p_is_executing
        Utility.Wait(0.01)
    endWhile
    p_is_executing = true
endFunction

function p_Unlock_Script()
    p_is_executing = false
endFunction

bool function p_Send(string str_event)
    int handle = ModEvent.Create(str_event)

    if !handle
        return false
    endIf

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

function p_Move()
    float p_player_pos_x = p_ref_player.GetPositionX()
    float p_player_pos_y = p_ref_player.GetPositionY()
    float p_player_pos_z = p_ref_player.GetPositionZ()
    float p_player_ang_x = p_ref_player.GetAngleX()
    float p_player_ang_z = p_ref_player.GetAngleZ()
    float movee_pos_x
    float movee_pos_y
    float movee_pos_z

    if p_do_distance_farther && !p_do_distance_nearer
        p_movee_pos += p_DISTANCE_UNIT
        if p_movee_pos > p_DISTANCE_MAX
            p_movee_pos = p_DISTANCE_MAX
        endIf
    elseIf p_do_distance_nearer && !p_do_distance_farther
        p_movee_pos -= p_DISTANCE_UNIT
        if p_movee_pos < p_DISTANCE_MIN
            p_movee_pos = p_DISTANCE_MIN
        endIf
    endIf

    if p_do_rotate_left && !p_do_rotate_right
        p_movee_ang -= p_ROTATE_UNIT
        if p_movee_ang < 0.0
            p_movee_ang = 360.0
        endIf
    elseIf p_do_rotate_right && !p_do_rotate_left
        p_movee_ang += p_ROTATE_UNIT
        if p_movee_ang > 360.0
            p_movee_ang = 0.0
        endIf
    endIf

    if p_player_ang_x < 0 && p_player_ang_x > -91
        float player_ang_x_cos = Math.Cos(p_player_ang_x)

        p_is_airborne = true
        movee_pos_x = p_player_pos_x + p_movee_pos * Math.Sin(p_player_ang_z) * player_ang_x_cos
        movee_pos_y = p_player_pos_y + p_movee_pos * Math.Cos(p_player_ang_z) * player_ang_x_cos
        movee_pos_z = p_player_pos_z + p_movee_pos * Math.Abs(Math.Sin(p_player_ang_x))
    else
        p_is_airborne = false
        movee_pos_x = p_player_pos_x + p_movee_pos * Math.Sin(p_player_ang_z)
        movee_pos_y = p_player_pos_y + p_movee_pos * Math.Cos(p_player_ang_z)
        movee_pos_z = p_player_pos_z
    endIf

    p_ref_actor.StopTranslation()
    p_ref_actor.TranslateTo(movee_pos_x, movee_pos_y, movee_pos_z, 0.0, 0.0, p_movee_ang, p_SPEED, p_SPEED)
endFunction

; Public Methods
bool function Exists()
    return p_is_created
endFunction

function Update_Keys()
    UnregisterForAllKeys()

    if !Exists()
        return
    endIf

    if VARS.key_move_farther
        RegisterForKey(VARS.key_move_farther)
    endIf
    if VARS.key_move_nearer
        RegisterForKey(VARS.key_move_nearer)
    endIf
    if VARS.key_move_rotate_right
        RegisterForKey(VARS.key_move_rotate_right)
    endIf
    if VARS.key_move_rotate_left
        RegisterForKey(VARS.key_move_rotate_left)
    endIf
endFunction

; Events
event OnUpdate()
    p_Lock_Script()

        while Exists()
            if p_ref_actor.Is3DLoaded()
                p_Move()
            endIf
            Utility.Wait(p_UPDATE_INTERVAL)
        endWhile

    p_Unlock_Script()
endEvent

event OnKeyDown(int code_key)
    if !FUNCS.Can_Use_Keys()
        return
    endIf

    if code_key == VARS.key_move_farther
        p_do_distance_farther = true
    elseIf code_key == VARS.key_move_nearer
        p_do_distance_nearer = true
    elseIf code_key == VARS.key_move_rotate_right
        p_do_rotate_right = true
    elseIf code_key == VARS.key_move_rotate_left
        p_do_rotate_left = true
    endIf
endEvent

event OnKeyUp(int code_key, float hold_time)
    if !FUNCS.Can_Use_Keys()
        return
    endIf

    if code_key == VARS.key_move_farther
        p_do_distance_farther = false
    elseIf code_key == VARS.key_move_nearer
        p_do_distance_nearer = false
    elseIf code_key == VARS.key_move_rotate_right
        p_do_rotate_right = false
    elseIf code_key == VARS.key_move_rotate_left
        p_do_rotate_left = false
    endIf
endEvent

event On_Cell_Change(Form cell_new, Form cell_old)
    p_ref_actor.MoveTo(p_ref_player)
    p_movee_ang = p_ref_actor.GetAngleZ()
endEvent
