Scriptname doticu_npcp_settler extends ReferenceAlias

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty

; Friend Constants
doticu_npcp_queue property f_QUEUE hidden
    doticu_npcp_queue function Get()
        return p_ref_member.f_QUEUE
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false
int                 p_id_alias      =    -1
Actor               p_ref_actor     =  none
doticu_npcp_member  p_ref_member    =  none
ObjectReference     p_ref_marker    =  none
string              p_str_namespace =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA, int id_alias)
    p_DATA = DATA

    p_is_created = true
    p_id_alias = id_alias
    p_ref_actor = GetActorReference()
    p_ref_member = (self as ReferenceAlias) as doticu_npcp_member
    p_ref_marker = CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(p_id_alias) as ObjectReference
    p_str_namespace = "settler_" + p_id_alias

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_SETTLER)
    p_Settle()
    p_ref_actor.EvaluatePackage()

    p_Register_Queues()
endFunction

function f_Destroy()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_SETTLER)
    p_ref_actor.EvaluatePackage()

    p_Unsettle()
    p_Untoken()

    p_str_namespace = ""
    p_ref_marker = none
    p_ref_member = none
    p_ref_actor = none
    p_id_alias = -1
    p_is_created = false
endFunction

function f_Register()
    p_Register_Queues()
endFunction

function f_Enforce()
    p_Enqueue("Settler.Token", 0.1)
endFunction

; Private Methods
function p_Register_Queues()
    f_QUEUE.Register_Alias(self, "On_Queue_Settler", p_str_namespace)
endFunction

function p_Enqueue(string str_message, float float_interval = -1.0, bool allow_repeat = false)
    f_QUEUE.Enqueue(str_message, float_interval, p_str_namespace, allow_repeat)
endFunction

function p_Rush(string str_message)
    f_QUEUE.Rush(str_message, p_str_namespace)
endFunction

function p_Token()
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_SETTLER)

    p_ref_actor.EvaluatePackage()
endFunction

function p_Untoken()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_SETTLER)

    p_ref_actor.EvaluatePackage()
endFunction

function p_Settle()
    p_ref_marker.MoveTo(p_ref_actor)
endFunction

function p_Unsettle()
    p_ref_marker.MoveToMyEditorLocation()
endFunction

; Public Methods
int function Enforce()
    return p_ref_member.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction

int function Resettle()
    int code_return

    if !Exists()
        return CODES.ISNT_SETTLER
    endIf

    p_Settle()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

; Update Methods
function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
endFunction

function u_0_1_5(doticu_npcp_data DATA)
    p_ref_member = (self as ReferenceAlias) as doticu_npcp_member
    p_ref_marker = CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(p_id_alias) as ObjectReference
endFunction

; Events
event On_Queue_Settler(string str_message)
    if false
        
    elseIf str_message == "Settler.Token"
        p_Token()
    
    endIf

    f_QUEUE.Dequeue()
endEvent
