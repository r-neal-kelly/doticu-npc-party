;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_greeter extends ReferenceAlias

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
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

; Private Constants
doticu_npcp_data    p_DATA          =  none
float property p_WAIT_TIME hidden
    float function Get()
        return 0.5
    endFunction
endProperty
float property p_MAX_WAIT_TIME hidden
    float function Get()
        return 10.0; 60.0
    endFunction
endProperty

; Private Variable
bool                p_is_created    = false
Actor               p_ref_actor     =  none
float               p_time_waited   =   0.0

; Friend Methods
function f_Create(doticu_npcp_data DATA, Actor ref_actor)
    p_DATA = DATA

    p_is_created = true
    p_ref_actor = ref_actor
    p_time_waited = 0.0

    ForceRefTo(p_ref_actor)
    ACTORS.Token(p_ref_actor, doticu_npcp_consts.Greeter_Token())
    ACTORS.Pacify(p_ref_actor)

    RegisterForSingleUpdate(0.0)
endFunction

function f_Destroy()
    ACTORS.Pacify(p_ref_actor)
    ACTORS.Untoken(p_ref_actor, doticu_npcp_consts.Greeter_Token())
    Clear()

    if p_ref_actor
        p_ref_actor.EvaluatePackage()
    endIf

    p_time_waited = 0.0
    p_ref_actor = none
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

; Public Methods
bool function Exists()
    return p_is_created
endFunction

; Events
event OnUpdate()
    while Exists() && !p_ref_actor.IsInDialogueWithPlayer()
        if p_time_waited >= p_MAX_WAIT_TIME
            f_Destroy()
        endIf
        FUNCS.Wait(p_WAIT_TIME)
        p_time_waited += p_WAIT_TIME
    endWhile
    if Exists()
        f_Destroy()
    endIf
endEvent
