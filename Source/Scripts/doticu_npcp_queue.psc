Scriptname doticu_npcp_queue extends ObjectReference

; Private Constants
doticu_npcp_data    p_DATA              =  none
int                 p_BUFFER_MAX        =    -1
float               p_INTERVAL_DEFAULT  =  -1.0
string              p_EVENT_DEFAULT     =    ""
string[]            p_MESSAGES          =  none
float[]             p_INTERVALS         =  none
string[]            p_EVENTS            =  none
Form[]              p_FORMS             =  none
bool[]              p_BOOLS             =  none

; Private Variables
bool                p_is_created        = false
int                 p_buffer_write      =     0
int                 p_buffer_read       =     0
int                 p_buffer_used       =     0
int                 p_backup_used       =    -1
string              p_str_message       =    ""
string              p_str_event         =    ""
Form                p_event_form        =  none
bool                p_event_bool        = false
string              p_str_rush          =    ""
string              p_str_rush_event    =    ""
bool                p_will_update       = false
bool                p_will_rush         = false

; Friend Methods
function f_Create(doticu_npcp_data DATA, string str_namespace, int message_max = 64, float interval_default = 0.1)
    p_DATA = DATA
    p_BUFFER_MAX = message_max
    p_INTERVAL_DEFAULT = interval_default
    p_MESSAGES = Utility.CreateStringArray(p_BUFFER_MAX, "")
    p_INTERVALS = Utility.CreateFloatArray(p_BUFFER_MAX, 0.0)
    p_EVENTS = Utility.CreateStringArray(p_BUFFER_MAX, "")

    p_EVENT_DEFAULT = "doticu_npcp_queue"
    if str_namespace
        p_EVENT_DEFAULT = p_EVENT_DEFAULT + "_" + str_namespace
    endIf
    
    p_is_created = true
endFunction

function f_Destroy()
    self.Unpause()
    self.Flush()
    self.Disable()
    self.Delete()

    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
string function p_Get_Event(string str_namespace = "_default_")
    if str_namespace == "_default_" || !str_namespace
        return p_EVENT_DEFAULT
    else
        return p_EVENT_DEFAULT + "_" + str_namespace
    endIf
endFunction

int function p_Write(string str_message, float float_wait_before = -1.0, string str_namespace = "_default_")
    if Is_Full()
        return -1
    endIf

    int idx_buffer = p_buffer_write

    p_MESSAGES[p_buffer_write] = str_message
    p_INTERVALS[p_buffer_write] = float_wait_before
    p_EVENTS[p_buffer_write] = p_Get_Event(str_namespace)

    p_buffer_write += 1
    if p_buffer_write == p_BUFFER_MAX
        p_buffer_write = 0
    endIf

    p_buffer_used += 1

    return idx_buffer
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

    ; should we check p_str_rush?

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

bool function p_Send_Queue()
    int handle = ModEvent.Create(p_str_event)

    if !handle
        return false
    endIf

    ModEvent.PushString(handle, p_str_message)
    if p_FORMS
        ModEvent.PushForm(handle, p_event_form)
    endIf
    if p_BOOLS
        ModEvent.PushBool(handle, p_event_bool)
    endIf

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Public Methods
bool function Exists()
    return p_is_created
endFunction

bool function Is_Empty()
    return p_buffer_used == 0
endFunction

bool function Is_Full()
    return p_buffer_used == p_buffer_max
endFunction

bool function Is_Paused()
    return p_backup_used != -1
endFunction

bool function Should_Cancel()
    return p_str_message == ""
endFunction

; for the registers, if we keep track of the objects, we can unregister for them on Destroy()
function Register_Form(Form ref_form, string str_handler, string str_namespace = "_default_")
    if Exists() && ref_form && str_handler
        ref_form.RegisterForModEvent(p_Get_Event(str_namespace), str_handler)
    endIf
endFunction

function Register_Alias(ReferenceAlias ref_alias, string str_handler, string str_namespace = "_default_")
    if Exists() && ref_alias && str_handler
        ref_alias.RegisterForModEvent(p_Get_Event(str_namespace), str_handler)
    endIf
endFunction

function Register_Effect(ActiveMagicEffect ref_effect, string str_handler, string str_namespace = "_default_")
    if Exists() && ref_effect && str_handler
        ref_effect.RegisterForModEvent(p_Get_Event(str_namespace), str_handler)
    endIf
endFunction

function Unregister_Form(Form ref_form, string str_namespace = "_default_")
    if Exists() && ref_form
        ref_form.UnregisterForModEvent(p_Get_Event(str_namespace))
    endIf
endFunction

function Unregister_Alias(ReferenceAlias ref_alias, string str_namespace = "_default_")
    if Exists() && ref_alias
        ref_alias.UnregisterForModEvent(p_Get_Event(str_namespace))
    endIf
endFunction

function Unregister_Effect(ActiveMagicEffect ref_effect, string str_namespace = "_default_")
    if Exists() && ref_effect
        ref_effect.UnregisterForModEvent(p_Get_Event(str_namespace))
    endIf
endFunction

function Use_Forms()
    if !p_FORMS
        p_FORMS = Utility.CreateFormArray(p_BUFFER_MAX, none)
    endIf
endFunction

function Use_Bools()
    if !p_BOOLS
        p_BOOLS = Utility.CreateBoolArray(p_BUFFER_MAX, none)
    endIf
endFunction

function Enqueue(string str_message, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
    ; this function should never unlock the instance,
    ; so only internal functions can be allowed

    if Is_Full() || str_message == "" || (!allow_repeat && p_Has_Message(str_message))
        return
    endIf

    if float_wait_before <= 0.0
        float_wait_before = p_INTERVAL_DEFAULT
    endIf

    p_Write(str_message, float_wait_before, str_namespace)

    if !p_will_update
        Dequeue()
    endIf
endFunction

function Enqueue_Form_Bool(string str_message, Form form_form, bool bool_bool, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
    if Is_Full() || str_message == "" || (!allow_repeat && p_Has_Message(str_message))
        return
    endIf

    if !p_FORMS
        Use_Forms()
    endIf
    if !p_BOOLS
        Use_Bools()
    endIf

    if float_wait_before <= 0.0
        float_wait_before = p_INTERVAL_DEFAULT
    endIf

    int idx_write = p_Write(str_message, float_wait_before, str_namespace)
    p_FORMS[idx_write] = form_form
    p_BOOLS[idx_write] = bool_bool

    if !p_will_update
        Dequeue()
    endIf
endFunction

function Dequeue()
    ; this function should never unlock the instance,
    ; so only internal functions can be allowed

    if p_Has_Rush()
        if !p_str_rush
            return
        endIf
        p_will_update = true
        p_will_rush = true
        p_str_message = p_str_rush
        p_str_event = p_str_rush_event
        p_str_rush = ""
        p_str_rush_event = ""
        RegisterForSingleUpdate(0.0)
    elseIf Is_Empty()
        p_will_update = false
        p_will_rush = false
        p_str_message = ""
        p_str_event = ""
        p_str_rush = ""
        p_str_rush_event = ""
    else
        int idx_buffer = p_Read()
        while !p_MESSAGES[idx_buffer] && !Is_Empty()
            idx_buffer = p_Read()
        endWhile
        if !p_MESSAGES[idx_buffer]
            return
        endIf
        p_will_update = true
        p_will_rush = false
        p_str_message = p_MESSAGES[idx_buffer]
        p_str_event = p_EVENTS[idx_buffer]
        if p_FORMS
            p_event_form = p_FORMS[idx_buffer]
        endIf
        if p_BOOLS
            p_event_bool = p_BOOLS[idx_buffer]
        endIf
        RegisterForSingleUpdate(p_INTERVALS[idx_buffer])
    endIf
endFunction

function Excise(string str_message)
    if Is_Empty()
        return
    endIf

    if p_str_message == str_message
        p_str_message = ""
    endIf

    if p_str_rush == str_message
        p_str_rush = ""
    endIf

    int idx = p_buffer_read
    while idx < p_buffer_write
        if p_MESSAGES[idx] == str_message
            p_MESSAGES[idx] = ""
        endIf
        idx += 1
    endWhile
endFunction

function Rush(string str_rush, string str_namespace = "_default_")
    ; if we fully block anywhere during this, Enqueue and Dequeue may deadlock.
    ; A state waiting Enqueue called within this stack frame would loop forever.

    if str_rush == ""
        return
    endIf

    GotoState("p_STATE_RUSH")

    while p_Has_Rush()
        ; we need to wait for the old Rush to finish.
        Utility.Wait(0.01)
    endWhile

    p_will_rush = true
    p_str_rush = str_rush
    p_str_rush_event = p_Get_Event(str_namespace)

    if !p_will_update
        Dequeue()
    endIf

    while p_will_rush
        ; we need to wait for this new Rush message to finish
        Utility.Wait(0.01)
    endWhile

    GotoState("")
endFunction

function Flush()
    ; should get exclusive execution away from Rush, in case of deadlock.
    ; blocking Enqueue and Dequeue makes sure any messages are not skipped.

    GotoState("p_STATE_FLUSH")

    p_buffer_used = 0; this empties the queue
    p_buffer_read = 0
    p_buffer_write = 0

    ; ran into infinite recursion with PLAYER. I think it just wasn't dequeing one last time, which unsets will_update
    ; but I don't know how that is possible unless Dequeue was never given a chance to run
    ;/if do_wait
        while p_will_update || p_will_rush
            ; let an already dispatched message finish
            Utility.Wait(p_INTERVAL_DEFAULT)
        endWhile
    endIf/;

    p_will_rush = false
    p_will_update = false
    p_str_rush_event = ""
    p_str_rush == ""
    p_str_event = ""
    p_str_message = ""

    GotoState("")
endFunction

function Pause()
    ; so we can do sync ops without causing any deadlocks with queued funcs
    
    if Is_Paused()
        return
    endIf

    GotoState("p_STATE_PAUSE")

    p_backup_used = p_buffer_used
    p_buffer_used = 0; this empties the queue

    while p_will_update || p_will_rush
        ; let an already dispatched message finish
        Utility.Wait(p_INTERVAL_DEFAULT)
    endWhile
endFunction

function Unpause()
    if !Is_Paused()
        return
    endIf

    p_buffer_used = p_backup_used
    p_backup_used = -1

    Dequeue()

    GotoState("")
endFunction

; Private States
state p_STATE_RUSH
    function Flush()
        Utility.Wait(p_INTERVAL_DEFAULT)
        Flush()
    endFunction

    function Pause()
        Utility.Wait(p_INTERVAL_DEFAULT)
        Pause()
    endFunction
endState

state p_STATE_FLUSH
    function Enqueue(string str_message, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
        Utility.Wait(p_INTERVAL_DEFAULT)
        Enqueue(str_message, float_wait_before, str_namespace, allow_repeat)
    endFunction

    function Enqueue_Form_Bool(string str_message, Form form_form, bool bool_bool, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
        Utility.Wait(p_INTERVAL_DEFAULT)
        Enqueue_Form_Bool(str_message, form_form, bool_bool, float_wait_before, str_namespace, allow_repeat)
    endFunction

    ; always allow Dequeue()

    function Rush(string str_rush, string str_namespace = "_default_")
        Utility.Wait(p_INTERVAL_DEFAULT)
        Rush(str_rush, str_namespace)
    endFunction

    function Flush()
    endFunction

    function Pause()
        Utility.Wait(p_INTERVAL_DEFAULT)
        Pause()
    endFunction
endState

state p_STATE_PAUSE
    function Enqueue(string str_message, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
        Utility.Wait(p_INTERVAL_DEFAULT)
        Enqueue(str_message, float_wait_before, str_namespace, allow_repeat)
    endFunction

    function Enqueue_Form_Bool(string str_message, Form form_form, bool bool_bool, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
        Utility.Wait(p_INTERVAL_DEFAULT)
        Enqueue_Form_Bool(str_message, form_form, bool_bool, float_wait_before, str_namespace, allow_repeat)
    endFunction

    function Rush(string str_rush, string str_namespace = "_default_")
        Utility.Wait(p_INTERVAL_DEFAULT)
        Rush(str_rush, str_namespace)
    endFunction

    function Flush()
        Utility.Wait(p_INTERVAL_DEFAULT)
        Flush()
    endFunction
endState

; Events
event OnUpdate()
    while !p_Send_Queue()
        Utility.Wait(p_INTERVAL_DEFAULT)
    endWhile
endEvent
