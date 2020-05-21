;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_queue extends ObjectReference

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty

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
string              p_str_message       =    ""
string              p_str_event         =    ""
Form                p_event_form        =  none
bool                p_event_bool        = false
bool                p_will_update       = false

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
    self.Flush()
    
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

    int idx = p_buffer_read
    while idx < p_buffer_write
        if p_MESSAGES[idx] == str_message
            return true
        endIf
        idx += 1
    endWhile

    return false
endFunction

function p_Send_Queue()
    int handle = FUNCS.Get_Event_Handle(p_str_event, p_INTERVAL_DEFAULT)
    if !handle
        return
    endIf

    ModEvent.PushString(handle, p_str_message)
    if p_FORMS
        ModEvent.PushForm(handle, p_event_form)
    endIf
    if p_BOOLS
        ModEvent.PushBool(handle, p_event_bool)
    endIf

    FUNCS.Send_Event_Handle(handle, p_INTERVAL_DEFAULT)
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

    if float_wait_before < 0.0
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

    if float_wait_before < 0.0
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
    ; this function can never unlock the instance,
    ; so only allows functions on this object (self)
    if Is_Empty()
        p_will_update = false
        p_str_message = ""
        p_str_event = ""
    else
        int idx_buffer = p_Read()
        while !p_MESSAGES[idx_buffer] && !Is_Empty()
            idx_buffer = p_Read()
        endWhile
        if !p_MESSAGES[idx_buffer]
            return
        endIf
        p_will_update = true
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

    int idx = p_buffer_read
    while idx < p_buffer_write
        if p_MESSAGES[idx] == str_message
            p_MESSAGES[idx] = ""
        endIf
        idx += 1
    endWhile
endFunction

function Flush()
    ; blocking Enqueue and Dequeue makes sure any messages are not skipped.
    GotoState("p_STATE_FLUSH")

    p_buffer_used = 0; this empties the queue
    p_buffer_read = 0
    p_buffer_write = 0

    p_will_update = false
    p_str_event = ""
    p_str_message = ""

    GotoState("")
endFunction

; I think the problem with many of these is that once a thread enters the stack frame of a recursive wait,
; it can't leave it even when the state of the function is changed to something else. It will just always
; recurse infinitely.

; Private States
state p_STATE_FLUSH
    function Enqueue(string str_message, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
    endFunction

    function Enqueue_Form_Bool(string str_message, Form form_form, bool bool_bool, float float_wait_before = -1.0, string str_namespace = "_default_", bool allow_repeat = false)
    endFunction

    function Flush()
    endFunction
endState

; Events
event OnUpdate()
    p_Send_Queue()
endEvent
