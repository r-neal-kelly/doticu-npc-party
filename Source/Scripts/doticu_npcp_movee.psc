;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

; how hard would it be to move the loop and math to c++?

Scriptname doticu_npcp_movee extends ReferenceAlias

; Modules
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
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return doticu_npcp.Control().COMMANDS
    endFunction
endProperty
doticu_npcp_keys property KEYS hidden
    doticu_npcp_keys function Get()
        return doticu_npcp.Control().KEYS
    endFunction
endProperty

; Private Constants
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

; Native Methods
function p_Reload() native

; Friend Methods
function f_Create(Actor ref_actor);;;
    p_is_created = true
    p_is_executing = false
    p_ref_actor = ref_actor
    p_ref_player = doticu_npcp_consts.Player_Actor()
    p_is_airborne = false
    p_do_distance_farther = false
    p_do_distance_nearer = false
    p_do_rotate_right = false
    p_do_rotate_left = false
    p_movee_pos = p_DISTANCE_DEFAULT
    p_movee_ang = p_ref_actor.GetAngleZ()

    ForceRefTo(p_ref_actor)
    ACTORS.Token(p_ref_actor, doticu_npcp_consts.Movee_Token())
    p_ref_actor.EvaluatePackage()
    p_ref_actor.SetActorValue("Paralysis", 1)

    RegisterForSingleUpdate(0.0)
endFunction

function f_Destroy();;;
    if !Exists()
        return
    endIf

    p_is_created = false

p_Lock()

    if !p_ref_actor.Is3DLoaded()
        p_Reload()
    endIf

    p_ref_actor.StopTranslation()
    if p_is_airborne
        p_ref_player.PushActorAway(p_ref_actor, 0.0)
    else
        p_ref_actor.ApplyHavokImpulse(0.0, 0.0, 0.001, 0.001)
    endIf
    p_ref_actor.SetActorValue("Paralysis", 0)
    ACTORS.Untoken(p_ref_actor, doticu_npcp_consts.Movee_Token())
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

p_Unlock()
endFunction

function f_Register();;;
    RegisterForModEvent("doticu_npcp_movee_distance_farther", "On_Distance_Farther")
    RegisterForModEvent("doticu_npcp_movee_distance_nearer", "On_Distance_Nearer")
    RegisterForModEvent("doticu_npcp_movee_rotate_left", "On_Rotate_Left")
    RegisterForModEvent("doticu_npcp_movee_rotate_right", "On_Rotate_Right")
    Update_Keys()
endFunction

function f_Unregister();;;
    UnregisterForAllKeys()
    UnregisterForAllModEvents()
endFunction

; Private Methods
function p_Lock(float timeout = 15.0)
    float time_waited = 0.0

    while p_is_executing && time_waited < timeout
        FUNCS.Wait_Out_Of_Menu(0.01)
        time_waited += 0.01
    endWhile

    p_is_executing = true
endFunction

function p_Unlock()
    p_is_executing = false
endFunction

function p_Move()
    if !Exists()
        return
    endIf

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
        p_movee_ang += p_ROTATE_UNIT
        if p_movee_ang > 360.0
            p_movee_ang = 0.0
        endIf
    elseIf p_do_rotate_right && !p_do_rotate_left
        p_movee_ang -= p_ROTATE_UNIT
        if p_movee_ang < 0.0
            p_movee_ang = 360.0
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

    if p_ref_actor.Is3DLoaded()
        p_ref_actor.StopTranslation()
        p_ref_actor.TranslateTo(movee_pos_x, movee_pos_y, movee_pos_z, 0.0, 0.0, p_movee_ang, p_SPEED, p_SPEED)
    endif
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

    if VARS.key_n_move_farther
        RegisterForKey(VARS.key_n_move_farther)
    endIf
    if VARS.key_n_move_nearer
        RegisterForKey(VARS.key_n_move_nearer)
    endIf
    if VARS.key_n_move_rotate_left
        RegisterForKey(VARS.key_n_move_rotate_left)
    endIf
    if VARS.key_n_move_rotate_right
        RegisterForKey(VARS.key_n_move_rotate_right)
    endIf
endFunction

; Events
event OnUpdate()
p_Lock()

    while Exists()
        if p_ref_actor.Is3DLoaded()
            p_Move()
        else
            p_Reload()
        endIf
        FUNCS.Wait_Out_Of_Menu(p_UPDATE_INTERVAL)
    endWhile

p_Unlock()
endEvent

event OnKeyDown(int code_key)
    if !FUNCS.Can_Use_Keys()
        return
    endIf

    if code_key == VARS.key_n_move_farther
        p_do_distance_farther = true
    elseIf code_key == VARS.key_n_move_nearer
        p_do_distance_nearer = true
    elseIf code_key == VARS.key_n_move_rotate_left
        p_do_rotate_left = true
    elseIf code_key == VARS.key_n_move_rotate_right
        p_do_rotate_right = true
    endIf
endEvent

event OnKeyUp(int value, float hold_time)
    if !FUNCS.Can_Use_Keys()
        return
    endIf

    string pressed_key = KEYS.Pressed_Hotkey(value)
    if pressed_key == KEYS.KEY_N_TOGGLE_MOVE
        COMMANDS.Toggle_Move(p_ref_actor)
    elseIf pressed_key == KEYS.KEY_N_MOVE_FARTHER
        p_do_distance_farther = false
    elseIf pressed_key == KEYS.KEY_N_MOVE_NEARER
        p_do_distance_nearer = false
    elseIf pressed_key == KEYS.KEY_N_MOVE_ROTATE_LEFT
        p_do_rotate_left = false
    elseIf pressed_key == KEYS.KEY_N_MOVE_ROTATE_RIGHT
        p_do_rotate_right = false

    endIf
endEvent
