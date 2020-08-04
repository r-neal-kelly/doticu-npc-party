;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_horse extends ReferenceAlias

; Modules
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

; Private Constants
doticu_npcp_data        p_DATA          =  none

; Private Variables
bool                    p_is_locked     = false
bool                    p_is_created    = false
int                     p_id_alias      =    -1
Actor                   p_ref_actor     =  none
doticu_npcp_follower    p_ref_follower  =  none

; Native Method
Actor function Actor() native

string function Name() native

; Friend Methods
function f_Create(doticu_npcp_data DATA, int id_alias, doticu_npcp_follower ref_follower)
p_Lock()

    p_DATA = DATA

    p_ref_actor = doticu_npcp_consts.Storage_Marker().PlaceAtMe(doticu_npcp_consts.Horse_Leveled_Actor(), 1, true, true) as Actor
    ForceRefTo(p_ref_actor)

    p_is_created = true
    p_id_alias = id_alias
    p_ref_follower = ref_follower

p_Unlock()
endFunction

function f_Destroy()
p_Lock()

    Clear()
    p_ref_actor.Disable()
    p_ref_actor.Delete()

    p_ref_follower = none
    p_ref_actor = none
    p_id_alias = -1
    p_is_created = false

p_Unlock()
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

; Private Methods
function p_Lock(float interval = 0.2, float timeout = 6.0)
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

; Public Methods
bool function Exists()
    return p_is_created
endFunction

doticu_npcp_follower function Get_Follower()
    if Exists() && p_ref_follower
        return p_ref_follower
    else
        return none
    endIf
endFunction

function Rename(string str_name)
    ACTORS.Rename(p_ref_actor, str_name)
endFunction

;/int function Pack(int code_exec)
    return p_ref_member.Pack(code_exec)
endFunction

int function Stash()
    return p_ref_member.Stash()
endFunction/;

; Events
event OnActivate(ObjectReference activator_obj)
    Actor activator_actor = activator_obj as Actor
    if activator_actor && p_ref_follower.Actor() == activator_actor
        (doticu_npcp_consts.Is_Saddler_Sitting_Globals_Formlist().GetAt(p_ref_follower.ID()) as GlobalVariable).SetValue(1)
        activator_actor.EvaluatePackage()
    endIf
endEvent
