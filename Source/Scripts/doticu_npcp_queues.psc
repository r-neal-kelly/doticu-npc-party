Scriptname doticu_npcp_queues extends Quest

; Private Constants
doticu_npcp_data        p_DATA              = none
doticu_npcp_consts      p_CONSTS            = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
endFunction

function f_Initialize()
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_queue function Create(string str_namespace, int max_message = 32, float interval_default = 0.15)
    doticu_npcp_queue ref_queue = p_CONSTS.MARKER_STORAGE.PlaceAtMe(p_CONSTS.MISC_QUEUE as Form, 1, false, false) as doticu_npcp_queue

    ref_queue.f_Create(p_DATA, str_namespace, max_message, interval_default)

    return ref_queue
endFunction

function Destroy(doticu_npcp_queue ref_queue)
    ref_queue.f_Destroy()
endFunction
