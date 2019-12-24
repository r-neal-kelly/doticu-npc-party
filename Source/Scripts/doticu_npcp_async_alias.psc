Scriptname doticu_npcp_async_alias extends ReferenceAlias

; Private Constants
string[]    p_MESSAGES      =  none
float[]     p_INTERVALS     =  none
int         p_BUFFER_MAX    =    64

; Private Variables
int         p_buffer_write  =     0
int         p_buffer_read   =     0
int         p_buffer_used   =     0
bool        p_will_update   = false

; Friend Methods
function f_Link(doticu_npcp_data DATA)
endFunction

function f_Initialize()
    p_MESSAGES = Utility.CreateStringArray(p_BUFFER_MAX, "")
    p_INTERVALS = Utility.CreateFloatArray(p_BUFFER_MAX, 0.0)
endFunction

function f_Register()
endFunction

; Private Methods
function p_Enqueue(string str_message, float float_interval = 0.5)
    if Is_Full()
        return
    endIf

    p_MESSAGES[p_buffer_write] = str_message
    p_INTERVALS[p_buffer_write] = float_interval

    p_buffer_write += 1
    if p_buffer_write == p_BUFFER_MAX
        p_buffer_write = 0
    endIf

    p_buffer_used += 1
endFunction

int function p_Dequeue()
    if Is_Empty()
        return -1
    endIf

    int idx_buffer = p_buffer_read

    p_buffer_read += 1
    if p_buffer_read == p_BUFFER_MAX
        p_buffer_read = 0
    endIf

    p_buffer_used -= 1

    return idx_buffer
endFunction

; Public Methods
function Enqueue(string str_message, float float_interval = 0.5)
    if str_message == ""
        return
    endIf

    p_Enqueue(str_message, float_interval)

    if !p_will_update
        p_will_update = true
        RegisterForSingleUpdate(float_interval)
    endIf
endFunction

string function Dequeue()
    if Is_Empty()
        p_will_update = false
        return ""
    else
        int idx_buffer = p_Dequeue()
        p_will_update = true
        RegisterForSingleUpdate(p_INTERVALS[idx_buffer])
        return p_MESSAGES[idx_buffer]
    endIf
endFunction

function Flush()
    UnregisterForUpdate()
    p_buffer_write = 0
    p_buffer_read = 0
    p_buffer_used = 0
    p_will_update = false
endFunction

bool function Is_Empty()
    return p_buffer_used == 0
endFunction

bool function Is_Full()
    return p_buffer_used == p_buffer_max
endFunction

; Update Methods
function u_0_1_0()
endFunction
