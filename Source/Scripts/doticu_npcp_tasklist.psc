;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_tasklist extends ObjectReference

; Private Constants
doticu_npcp_data    p_DATA                  =  none

; Private Variables
bool                p_is_created            = false
float               p_default_wait_interval =  -1.0
float               p_default_wait_timeout  =  -1.0
int                 p_num_tasks_total       =    -1
int                 p_num_tasks_complete    =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA, float wait_interval, float wait_timeout)
    p_DATA = DATA

    p_is_created = true
    p_default_wait_interval = wait_interval
    p_default_wait_timeout = wait_timeout
    p_num_tasks_total = -1
    p_num_tasks_complete = -1
endFunction

function f_Destroy()
    self.Disable()
    self.Delete()

    p_num_tasks_complete = -1
    p_num_tasks_total = -1
    p_default_wait_timeout = -1.0
    p_default_wait_interval = -1.0
    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
bool function p_Start(int num_tasks)
    if p_num_tasks_total > 0
        return false
    endIf

    if num_tasks < 1
        return false
    endIf

    p_num_tasks_total = num_tasks
    p_num_tasks_complete = 0

    return true
endFunction

bool function p_Send(string str_event)
    int handle = ModEvent.Create(str_event)

    if !handle
        return false
    endIf

    ModEvent.PushForm(handle, self as Form)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

bool function p_Send_Int(string str_event, int int_val)
    int handle = ModEvent.Create(str_event)

    if !handle
        return false
    endIf

    ModEvent.PushForm(handle, self as Form)
    ModEvent.PushInt(handle, int_val)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

bool function p_Wait(float wait_interval, float wait_timeout)
    if p_num_tasks_total < 1
        return false
    endIf

    float wait_total = 0.0
    while wait_total < wait_timeout && p_num_tasks_complete != p_num_tasks_total
        Utility.Wait(wait_interval)
        wait_total += wait_interval
    endWhile

    p_num_tasks_total = -1
    p_num_tasks_complete = -1

    if wait_total >= wait_timeout
        return false
    else
        return true
    endIf
endFunction

; Public Methods
bool function Execute(int num_tasks, string str_event, float wait_interval = -1.0, float wait_timeout = -1.0)
    if wait_interval < 0
        wait_interval = p_default_wait_interval
    endIf
    if wait_timeout < 0
        wait_timeout = p_default_wait_timeout
    endIf

    if !p_Start(num_tasks)
        return false
    endIf

    while !p_Send(str_event)
        Utility.Wait(wait_interval)
    endWhile

    if !p_Wait(wait_interval, wait_timeout)
        return false
    endIf

    return true
endFunction

bool function Loop(int num_tasks, string str_event, float wait_interval = -1.0, float wait_timeout = -1.0)
    if wait_interval < 0
        wait_interval = p_default_wait_interval
    endIf
    if wait_timeout < 0
        wait_timeout = p_default_wait_timeout
    endIf

    if !p_Start(num_tasks)
        return false
    endIf

    int int_task = 0
    while int_task < num_tasks
        while !p_Send_Int(str_event, int_task)
            Utility.Wait(wait_interval)
        endWhile
        int_task += 1
    endWhile

    if !p_Wait(wait_interval, wait_timeout)
        return false
    endIf

    return true
endFunction

function Detask()
    p_num_tasks_complete += 1
endFunction
