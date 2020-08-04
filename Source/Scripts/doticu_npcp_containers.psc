;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_containers extends Quest

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

; Public Methods
ObjectReference function Create_Temp()
    ObjectReference ref_container = doticu_npcp_consts.Player_Actor().PlaceAtMe(doticu_npcp_consts.Empty_Container(), 1, false, false)

    ; this can prevent a ctd
    FUNCS.Wait(0.1)

    ref_container.SetActorOwner(doticu_npcp_consts.Player_Actor().GetActorBase())
    
    return ref_container
endFunction

function Destroy_Temp(ObjectReference ref_container)
    ref_container.Disable()
    ref_container.Delete()
endFunction

ObjectReference function Create_Perm()
    ObjectReference ref_container = doticu_npcp_consts.Storage_Marker().PlaceAtMe(doticu_npcp_consts.Empty_Container(), 1, true, false)
    
    ; this can prevent a ctd
    FUNCS.Wait(0.1)

    ref_container.SetActorOwner(doticu_npcp_consts.Player_Actor().GetActorBase())
    
    return ref_container
endFunction

function Destroy_Perm(ObjectReference ref_container)
    ref_container.Disable()
    ref_container.Delete()
endFunction

function Open(ObjectReference ref_container)
    ref_container.Activate(doticu_npcp_consts.Player_Actor())
    FUNCS.Wait(0.1)
endFunction

string function Name(ObjectReference ref_container)
    return ref_container.GetDisplayName()
endFunction

function Rename(ObjectReference ref_container, string str_name)
    ref_container.SetDisplayName(str_name, true)
endFunction
