;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_queues extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty

; Public Constants
ObjectReference property OBJECT_STORAGE hidden
    ObjectReference function Get()
        return p_DATA.CONSTS.MARKER_STORAGE
    endFunction
endProperty
MiscObject property MISC_QUEUE hidden
    MiscObject function Get()
        return p_DATA.CONSTS.MISC_QUEUE
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
doticu_npcp_queue function Create(string str_namespace, int max_message = 64, float interval_default = 0.1)
    doticu_npcp_queue ref_queue = OBJECT_STORAGE.PlaceAtMe(MISC_QUEUE as Form, 1, false, false) as doticu_npcp_queue

    ref_queue.f_Create(p_DATA, str_namespace, max_message, interval_default)
    ref_queue.f_Register()

    return ref_queue
endFunction

function Destroy(doticu_npcp_queue ref_queue)
    ref_queue.f_Destroy()

    ref_queue.Disable()
    ref_queue.Delete()
endFunction
