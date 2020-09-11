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
    NPCS.f_Initialize()
    PERKS.f_Create()
endFunction

function f_Destroy()
    PERKS.f_Destroy()
    NPCS.f_Uninitialize()
    LOGS.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    LOGS.f_Register()
    ACTORS.f_Register()
    PERKS.f_Register()
endFunction

; Public Methods
function Close_Menus();;;
    int key_menu = Input.GetMappedKey("Tween Menu")
    
    while Utility.IsInMenuMode()
        Input.TapKey(key_menu)
    endWhile
endFunction

bool function Can_Use_Keys();;;
    return !Utility.IsInMenuMode() && !UI.IsMenuOpen("Dialogue Menu")
endFunction

bool function Is_Mod_Installed(string name_mod)
    return Game.GetModByName(name_mod) != 255
endFunction

function Wait(float seconds);;;
    Utility.WaitMenuMode(seconds)
endFunction

function Wait_Out_Of_Menu(float seconds);;;
    Utility.Wait(seconds)
endFunction

function Rename(ObjectReference ref_container, string str_name)
    ref_container.SetDisplayName(str_name, true)
endFunction

function Open_Container(ObjectReference ref_container);;;
    ref_container.Activate(doticu_npcp_consts.Player_Actor())
    Wait_Out_Of_Menu(0.1)
endFunction

function Essentialize(ActorBase base_actor);;;
    Wait(1); is this necessary?
    base_actor.SetEssential(true)
endFunction

function Protect(ActorBase base_actor);;;
    Wait(1); is this necessary?
    base_actor.SetProtected(true)
endFunction

Actor function Find_Closest_Actor_From(ObjectReference ref, float radius);;;
    return Game.FindClosestActorFromRef(ref, radius)
endFunction

ObjectReference function Current_Crosshair_Reference();;;
    return Game.GetCurrentCrosshairRef()
endFunction
