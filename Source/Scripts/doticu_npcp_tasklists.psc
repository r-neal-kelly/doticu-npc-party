;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_tasklists extends Quest

; Publice Constants
ObjectReference property OBJECT_STORAGE hidden
    ObjectReference function Get()
        return doticu_npcp_consts.Storage_Marker()
    endFunction
endProperty
MiscObject property MISC_TASKLIST hidden
    MiscObject function Get()
        return doticu_npcp_consts.Tasklist()
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA          =  none

; Private Variables
bool                    p_is_created    = false

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
doticu_npcp_tasklist function Create(float wait_interval = 0.5, float wait_timeout = 5.0)
    doticu_npcp_tasklist ref_tasklist = OBJECT_STORAGE.PlaceAtMe(MISC_TASKLIST, 1, true, false) as doticu_npcp_tasklist
    
    ref_tasklist.f_Create(p_DATA, wait_interval, wait_timeout)
    ref_tasklist.f_Register()

    return ref_tasklist
endFunction

function Destroy(doticu_npcp_tasklist ref_tasklist)
    if ref_tasklist
        ref_tasklist.f_Destroy()
        ref_tasklist.Disable()
        ref_tasklist.Delete()
    endIf
endFunction
