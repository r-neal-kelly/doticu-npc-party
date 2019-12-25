Scriptname doticu_npcp_immobile extends ReferenceAlias

; Private Constants
doticu_npcp_consts  p_CONSTS            =  none
doticu_npcp_codes   p_CODES             =  none
doticu_npcp_actors  p_ACTORS            =  none
doticu_npcp_queues  p_QUEUES            =  none
doticu_npcp_members p_MEMBERS           =  none

int                 p_ID_ALIAS          =    -1

; Private Variables
bool                p_is_created        = false
Actor               p_ref_actor         =  none
doticu_npcp_member  p_ref_member        =  none
doticu_npcp_queue   p_queue_immobile    =  none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_MEMBERS = DATA.MODS.MEMBERS

    p_Link_Queues(DATA)
endFunction

function f_Initialize(int ID_ALIAS)
    p_ID_ALIAS = ID_ALIAS
endFunction

function f_Register()
    RegisterForModEvent("doticu_npcp_queue_" + "immobile_" + p_ID_ALIAS, "On_Queue_Immobile")

    p_Register_Queues()
endFunction

int function f_Create()
    int code_return

    if Exists()
        return p_CODES.IS_IMMOBILE
    endIf
    p_ref_actor = GetActorReference()
    if !p_ref_actor
        return p_CODES.ISNT_ACTOR
    endIf
    p_ref_member = p_MEMBERS.Get_Member(p_ref_actor)
    if !p_ref_member
        return p_CODES.ISNT_MEMBER
    endIf
    p_is_created = true

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    p_Create_Queues()

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return p_CODES.ISNT_IMMOBILE
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    p_Untoken()

    p_Destroy_Queues()

    p_queue_immobile = none
    p_ref_member = none
    p_ref_actor = none
    p_is_created = false

    return p_CODES.SUCCESS
endFunction

int function f_Enforce()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_IMMOBILE
    endIf

    p_queue_immobile.Enqueue("p_Token")

    return p_CODES.SUCCESS
endFunction

; Private Methods
function p_Link_Queues(doticu_npcp_data DATA)
    if p_queue_immobile
        p_queue_immobile.f_Link(DATA)
    endIf
endFunction

function p_Register_Queues()
    if p_queue_immobile
        p_queue_immobile.f_Register()
    endIf
endFunction

function p_Create_Queues()
    p_queue_immobile = p_QUEUES.Create("immobile_" + p_ID_ALIAS, 32, 0.5)
endFunction

function p_Destroy_Queues()
    p_QUEUES.Destroy(p_queue_immobile)
endFunction

function p_Token()
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)

    p_ref_actor.EvaluatePackage()
endFunction

function p_Untoken()
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)

    p_ref_actor.EvaluatePackage()
endFunction

; Public Methods
int function Enforce()
    return p_ref_member.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction

; Update Methods
function u_0_1_1()
    p_Create_Queues()
endFunction

; Events
event On_Queue_Immobile()
    string str_message = p_queue_immobile.Dequeue()

    if str_message == "p_Token"
        p_Token()
    endIf
endEvent

