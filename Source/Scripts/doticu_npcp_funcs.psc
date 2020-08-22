;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_funcs extends Quest

; Modules
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return (self as Quest) as doticu_npcp_logs
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return (self as Quest) as doticu_npcp_actors
    endFunction
endProperty
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return (self as Quest) as doticu_npcp_npcs
    endFunction
endProperty
doticu_npcp_perks property PERKS hidden
    doticu_npcp_perks function Get()
        return (self as Quest) as doticu_npcp_perks
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return (self as Quest) as doticu_npcp_mannequins
    endFunction
endProperty

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create()
    p_is_created = true

    LOGS.f_Create()
    ACTORS.f_Create()
    NPCS.f_Initialize()
    PERKS.f_Create()
    MANNEQUINS.f_Create()
endFunction

function f_Destroy()
    MANNEQUINS.f_Destroy()
    PERKS.f_Destroy()
    NPCS.f_Uninitialize()
    ACTORS.f_Destroy()
    LOGS.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    LOGS.f_Register()
    ACTORS.f_Register()
    PERKS.f_Register()
    MANNEQUINS.f_Register()
endFunction

; Public Methods
function Close_Menus()
    int key_menu = Input.GetMappedKey("Tween Menu")
    
    while Utility.IsInMenuMode()
        Input.TapKey(key_menu)
    endWhile
endFunction

bool function Can_Use_Keys()
    return !Utility.IsInMenuMode() && !UI.IsMenuOpen("Dialogue Menu")
endFunction

bool function Is_Mod_Installed(string name_mod)
    return Game.GetModByName(name_mod) != 255
endFunction

function Send_Event(string str_event, float interval = 0.25, float timeout = 5.0)
    float time_waited = 0.0
    while time_waited < timeout
        int handle = ModEvent.Create(str_event)
        if handle
            if ModEvent.Send(handle)
                return
            else
                ModEvent.Release(handle)
            endIf
        endIf

        Wait(interval)
        time_waited += interval
    endWhile
endFunction

int function Get_Event_Handle(string str_event, float interval = 0.25, float timeout = 5.0)
    float time_waited = 0.0
    while time_waited < timeout
        int handle = ModEvent.Create(str_event)
        if handle
            return handle
        endIf

        Wait(interval)
        time_waited += interval
    endWhile

    return 0
endFunction

bool function Send_Event_Handle(int handle, float interval = 0.25, float timeout = 5.0)
    float time_waited = 0.0
    while time_waited < timeout
        if ModEvent.Send(handle)
            return true
        endIf

        Wait(interval)
        time_waited += interval
    endWhile

    ModEvent.Release(handle)

    return false
endFunction

function Wait(float seconds)
    Utility.WaitMenuMode(seconds)
endFunction

function Wait_Out_Of_Menu(float seconds)
    Utility.Wait(seconds)
endFunction

function Rename(ObjectReference ref_container, string str_name)
    ref_container.SetDisplayName(str_name, true)
endFunction

function Open_Container(ObjectReference ref_container)
    ref_container.Activate(doticu_npcp_consts.Player_Actor())
    Wait_Out_Of_Menu(0.1)
endFunction

function Move_To_Orbit(ObjectReference ref, ObjectReference origin, float radius, float degree)
    bool has_disabled_ai = false
    Actor ref_actor = ref as Actor
    if ref_actor && !ref_actor.IsAIEnabled()
        has_disabled_ai = true
    endIf

    if has_disabled_ai
        ref_actor.EnableAI(true)
    endIf

    float origin_degree = origin.GetAngleZ()
    ref.MoveTo(origin, radius * Math.Sin(origin_degree - degree), radius * Math.Cos(origin_degree - degree), 0.0)
    ref.SetAngle(0.0, 0.0, origin_degree - 180 - degree)

    if has_disabled_ai
        ref_actor.EnableAI(false)
    endIf
endFunction
