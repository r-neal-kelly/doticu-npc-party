Scriptname doticu_npcp_queue extends ObjectReference

; Private Constants
string      p_STR_NAMESPACE     =    ""
int         p_BUFFER_MAX        =    -1
float       p_INTERVAL_DEFAULT  =  -1.0
string[]    p_MESSAGES          =  none
float[]     p_INTERVALS         =  none
string      p_STR_EVENT         =    ""

; Private Variables
int         p_buffer_write      =     0
int         p_buffer_read       =     0
int         p_buffer_used       =     0
bool        p_will_update       = false

; Friend Methods
function f_Link(doticu_npcp_data DATA)
endFunction

function f_Initialize()
endFunction

function f_Register()
endFunction

function f_Create(string str_namespace, int message_max = 32, float interval_default = 0.15)
    p_STR_NAMESPACE = str_namespace
    p_BUFFER_MAX = message_max
    p_INTERVAL_DEFAULT = interval_default
    
    p_MESSAGES = Utility.CreateStringArray(p_BUFFER_MAX, "")
    p_INTERVALS = Utility.CreateFloatArray(p_BUFFER_MAX, 0.0)

    p_STR_EVENT = "doticu_npcp_queue"
    if p_STR_NAMESPACE != ""
        p_STR_EVENT = p_STR_EVENT + "_"
    endIf
    p_STR_EVENT = p_STR_EVENT + p_STR_NAMESPACE
endFunction

function f_Destroy()
    self.Disable()
    self.Delete()
endFunction

; Private Methods
function p_Write(string str_message, float float_interval = -1.0)
    if Is_Full()
        return
    endIf

    if float_interval <= 0.0
        float_interval = p_INTERVAL_DEFAULT
    endIf

    p_MESSAGES[p_buffer_write] = str_message
    p_INTERVALS[p_buffer_write] = float_interval

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

bool function p_Send_Queue()
    int handle = ModEvent.Create(p_STR_EVENT)

    if !handle
        return false
    endIf

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Public Methods
function Enqueue(string str_message, float float_interval = -1.0)
    if str_message == ""
        return
    endIf

    p_Write(str_message, float_interval)

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
        int idx_buffer = p_Read()
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

; Events
event OnUpdate()
    while !p_Send_Queue()
        Utility.Wait(p_INTERVAL_DEFAULT)
    endWhile
endEvent
