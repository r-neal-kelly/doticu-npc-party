Scriptname doticu_npcp_tasklists extends Quest

; Private Constants
doticu_npcp_data        p_DATA              = none
doticu_npcp_consts      p_CONSTS            = none

ObjectReference         p_STORAGE           = none
MiscObject              p_MISC_TASKLIST     = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
endFunction

function f_Initialize()
    p_STORAGE = p_CONSTS.MARKER_STORAGE
    p_MISC_TASKLIST = p_CONSTS.MISC_TASKLIST
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_tasklist function Create(float wait_interval = 0.25, float wait_timeout = 24.0)
    doticu_npcp_tasklist ref_tasklist = p_STORAGE.PlaceAtMe(p_MISC_TASKLIST, 1, false, false) as doticu_npcp_tasklist
    
    ref_tasklist.f_Create(p_DATA, wait_interval, wait_timeout)

    return ref_tasklist
endFunction

function Destroy(doticu_npcp_tasklist ref_tasklist)
    ref_tasklist.f_Destroy()
endFunction
