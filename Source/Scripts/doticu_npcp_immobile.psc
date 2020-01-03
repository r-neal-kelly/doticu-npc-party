Scriptname doticu_npcp_immobile extends ReferenceAlias

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
string              p_str_namespace =    ""
bool                p_is_paralyzed  = false

; Friend Methods
function f_Create(doticu_npcp_data DATA, int id_alias)
    p_DATA = DATA

    p_is_created = true
    p_id_alias = id_alias
    p_ref_actor = GetActorReference()
    p_ref_member = (self as ReferenceAlias) as doticu_npcp_member
    p_str_namespace = "immobile_" + p_id_alias
    p_is_paralyzed = false
    
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    p_Register_Queues()
endFunction

function f_Destroy()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    if p_is_paralyzed
        p_Unparalyze()
    endIf
    p_Untoken()

    p_is_paralyzed = false
    p_str_namespace = ""
    p_ref_member = none
    p_ref_actor = none
    p_id_alias = -1
    p_is_created = false
endFunction

function f_Register()
    p_Register_Queues()
endFunction

function f_Unregister()
    UnregisterForAllModEvents()
endFunction

function f_Enforce()
    p_Enqueue("Immobile.Token", 0.1)
    if Is_Paralyzed()
        p_Enqueue("Immobile.Paralyze", 0.1)
    endIf
endFunction

; Private Methods
function p_Register_Queues()
    f_QUEUE.Register_Alias(self, "On_Queue_Immobile", p_str_namespace)
endFunction

function p_Enqueue(string str_message, float float_interval = -1.0, bool allow_repeat = false)
    f_QUEUE.Enqueue(str_message, float_interval, p_str_namespace, allow_repeat)
endFunction

function p_Rush(string str_message)
    f_QUEUE.Rush(str_message, p_str_namespace)
endFunction

function p_Token()
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_IMMOBILE)

    if Is_Paralyzed()
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    endIf

    p_ref_actor.EvaluatePackage()
endFunction

function p_Untoken()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_IMMOBILE)

    p_ref_actor.EvaluatePackage()
endFunction

function p_Paralyze()
    p_ref_actor.EnableAI(false)
endFunction

function p_Unparalyze()
    p_ref_actor.EnableAI(true)
endFunction

function p_Reparalyze()
    p_Unparalyze()
    Debug.SendAnimationEvent(p_ref_actor, "IdleForceDefaultState"); go to cached current animation
    p_Paralyze()
endFunction

; Public Methods
int function Enforce()
    return p_ref_member.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction

bool function Is_Paralyzed()
    return Exists() && p_is_paralyzed
endFunction

bool function Is_Unparalyzed()
    return Exists() && !p_is_paralyzed
endFunction

int function Paralyze()
    int code_return

    if !Exists()
        return CODES.ISNT_IMMOBILE
    endIf

    if p_is_paralyzed
        return CODES.IS_PARALYZED
    endIf

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    p_ref_actor.EnableAI(false)
    p_ref_actor.EvaluatePackage()

    p_is_paralyzed = true
    p_Rush("Immobile.Paralyze")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unparalyze()
    int code_return

    if !Exists()
        return CODES.ISNT_IMMOBILE
    endIf

    if !p_is_paralyzed
        return CODES.ISNT_PARALYZED
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    p_ref_actor.EnableAI(true)
    p_ref_actor.EvaluatePackage()

    p_is_paralyzed = false
    p_Rush("Immobile.Unparalyze")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

; maybe a ragdoll func?

; Update Methods
function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
endFunction

function u_0_1_5(doticu_npcp_data DATA)
    p_ref_member = (self as ReferenceAlias) as doticu_npcp_member
endFunction

; Events
event On_Queue_Immobile(string str_message)
    if false

    elseIf str_message == "Immobile.Token"
        p_Token()
    elseIf str_message == "Immobile.Paralyze"
        If Is_Paralyzed()
            p_Paralyze()
        endIf
    elseIf str_message == "Immobile.Unparalyze"
        if Is_Unparalyzed()
            p_Unparalyze()
        endIf
    
    endIf

    f_QUEUE.Dequeue()
endEvent

event On_Load_Mod()
    if Exists() && Is_Paralyzed()
        p_Reparalyze()
    endIf
endEvent

event OnLoad()
    if Exists() && Is_Paralyzed()
        p_Reparalyze()
    endIf
endEvent
