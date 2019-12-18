Scriptname doticu_npc_party_script_alias_async extends ReferenceAlias

; Private Constants
string[]    p_BUFFER        =  none
int         p_BUFFER_MAX    =    64
float       p_INTERVAL      =   0.5

; Private Variables
int         p_buffer_write  =     0
int         p_buffer_read   =     0
int         p_buffer_used   =     0
bool        p_will_update   = false

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int ID_ALIAS)
    p_BUFFER = Utility.CreateStringArray(p_BUFFER_MAX, "")
endFunction

function f_Register()
endFunction

; Private Methods
function p_Enqueue(string str_message)
    if Is_Full()
        return
    endIf

    p_BUFFER[p_buffer_write] = str_message

    p_buffer_write += 1
    if p_buffer_write == p_BUFFER_MAX
        p_buffer_write = 0
    endIf

    p_buffer_used += 1
endFunction

string function p_Dequeue()
    if Is_Empty()
        return ""
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

; Public Methods
function Enqueue(string str_message)
    p_Enqueue(str_message)

    if !p_will_update
        p_will_update = true
        RegisterForSingleUpdate(p_INTERVAL)
    endIf
endFunction

string function Dequeue()
    if Is_Empty()
        p_will_update = false
        return ""
    else 
        p_will_update = true
        RegisterForSingleUpdate(p_INTERVAL)
        return p_Dequeue()
    endIf
endFunction

bool function Is_Empty()
    return p_buffer_used == 0
endFunction

bool function Is_Full()
    return p_buffer_used == p_buffer_max
endFunction
