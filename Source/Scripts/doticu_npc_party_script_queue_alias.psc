Scriptname doticu_npc_party_script_queue_alias extends ReferenceAlias

; Private Constants
string[]    p_BUFFER        =  none
int         p_BUFFER_MAX    =    64
float       p_INTERVAL      =   0.5

; Private Variables
int         p_buffer_write  =     0
int         p_buffer_read   =     0
int         p_buffer_used   =     0
bool        p_is_executing  = false
string      p_str_message   =    ""

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int ID_ALIAS)
    p_BUFFER = Utility.CreateStringArray(p_BUFFER_MAX, "")
endFunction

; Public Methods
function Enqueue(string str_message)
    if Is_Full()
        return
    endIf

    p_BUFFER[p_buffer_write] = str_message

    p_buffer_write += 1
    if p_buffer_write == p_BUFFER_MAX
        p_buffer_write = 0
    endIf

    p_buffer_used += 1

    if !p_is_executing
        RegisterForSingleUpdate(p_INTERVAL)
    endIf
endFunction

string function Dequeue()
    if Is_Empty()
        return 0
    endIf

    string str_message = p_BUFFER[p_buffer_read]
    
    p_BUFFER[p_buffer_read] = 0

    p_buffer_read += 1
    if p_buffer_read == p_BUFFER_MAX
        p_buffer_read = 0
    endIf

    p_buffer_used -= 1

    return str_message
endFunction

bool function Is_Empty()
    return p_buffer_used == 0
endFunction

bool function Is_Full()
    return p_buffer_used == p_buffer_max
endFunction

string function Get_Message()
    return p_str_message
endFunction

; Events
event OnUpdate()
    if Is_Empty()
        p_is_executing = false
        p_str_message = ""
    else
        p_is_executing = true
        p_str_message = Dequeue()
        RegisterForSingleUpdate(p_INTERVAL)
    endIf
endEvent
