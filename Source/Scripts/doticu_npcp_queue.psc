Scriptname doticu_npcp_queue extends ObjectReference

; Private Constants
doticu_npcp_data    p_DATA              =  none
string              p_STR_NAMESPACE     =    ""
int                 p_BUFFER_MAX        =    -1
float               p_INTERVAL_DEFAULT  =  -1.0
string[]            p_MESSAGES          =  none
float[]             p_INTERVALS         =  none
string              p_STR_EVENT         =    ""

; Private Variables
int                 p_buffer_write      =     0
int                 p_buffer_read       =     0
int                 p_buffer_used       =     0
bool                p_will_update       = false
string              p_str_message       =    ""
string              p_str_rush          =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA, string str_namespace, int message_max = 32, float interval_default = 0.15)
    p_DATA = DATA
    p_STR_NAMESPACE = str_namespace
    p_BUFFER_MAX = message_max
    p_INTERVAL_DEFAULT = interval_default
    
    p_MESSAGES = Utility.CreateStringArray(p_BUFFER_MAX, "")
    p_INTERVALS = Utility.CreateFloatArray(p_BUFFER_MAX, 0.0)

    p_STR_EVENT = "doticu_npcp_queue"
    if p_STR_NAMESPACE != ""
        p_STR_EVENT = p_STR_EVENT + "_" + p_STR_NAMESPACE
    endIf
endFunction

function f_Destroy()
    self.Disable()
    self.Delete()
endFunction

; Private Methods
function p_Write(string str_message, float float_wait_before = -1.0, bool allow_repeat = false)
    if Is_Full()
        return
    endIf

    p_MESSAGES[p_buffer_write] = str_message
    p_INTERVALS[p_buffer_write] = float_wait_before

    p_buffer_write += 1
    if p_buffer_write == p_BUFFER_MAX
        p_buffer_write = 0
    endIf

    p_buffer_used += 1
endFunction

int function p_Read()
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

bool function p_Has_Message(string str_message)
    if Is_Empty()
        return false
    endIf

    int idx = p_buffer_read
    while idx < p_buffer_write
        if p_MESSAGES[idx] == str_message
            return true
        endIf
        idx += 1
    endWhile

    return false
endFunction

bool function p_Has_Rush()
    return p_str_rush != ""
endFunction

bool function p_Put_Rush(string str_rush)
    if str_rush == ""
        return false
    endIf

    if p_Has_Rush()
        ; could have a separate buffer that stores rushed messages instead
        return false
    endIf

    p_str_rush = str_rush

    return true
endFunction

bool function p_Send_Queue()
    int handle = ModEvent.Create(p_STR_EVENT)

    if !handle
        return false
    endIf

    ModEvent.PushString(handle, p_str_message)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Public Methods
function Enqueue(string str_message, float float_wait_before = -1.0, bool allow_repeat = false)
    if Is_Full()
        return
    endIf

    if str_message == ""
        return
    endIf

    if !allow_repeat && p_Has_Message(str_message)
        return
    endIf

    if float_wait_before <= 0.0
        float_wait_before = p_INTERVAL_DEFAULT
    endIf

    p_Write(str_message, float_wait_before, allow_repeat)

    MiscUtil.PrintConsole("count: " + p_buffer_used)

    if !p_will_update
        p_will_update = true
        p_str_message = str_message
        RegisterForSingleUpdate(float_wait_before)
    endIf
endFunction

function Dequeue()
    if Is_Empty()
        p_will_update = false
        p_str_message = ""
    elseIf p_Has_Rush()
        p_str_message = p_str_rush
        p_str_rush = ""
        RegisterForSingleUpdate(0.0)
    else
        int idx_buffer = p_Read()
        p_will_update = true
        p_str_message = p_MESSAGES[idx_buffer]
        RegisterForSingleUpdate(p_INTERVALS[idx_buffer])
    endIf
endFunction

bool function Rush(string str_rush)
    while !p_Put_Rush(str_rush)
        Utility.Wait(0.01)
    endWhile
endFunction

function Flush()
    UnregisterForUpdate()
    p_buffer_write = 0
    p_buffer_read = 0
    p_buffer_used = 0
    p_will_update = false
    p_str_message = ""
endFunction

bool function Is_Empty()
    return p_buffer_used == 0
endFunction

bool function Is_Full()
    return p_buffer_used == p_buffer_max
endFunction

; Update Methods
function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
endFunction

; Events
event OnUpdate()
    while !p_Send_Queue()
        Utility.Wait(p_INTERVAL_DEFAULT)
    endWhile
endEvent
