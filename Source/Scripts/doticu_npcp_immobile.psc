Scriptname doticu_npcp_immobile extends ReferenceAlias

; Private Constants
doticu_npcp_consts  p_CONSTS            =  none
doticu_npcp_codes   p_CODES             =  none
doticu_npcp_actors  p_ACTORS            =  none
doticu_npcp_queues  p_QUEUES            =  none
doticu_npcp_members p_MEMBERS           =  none
doticu_npcp_member  p_MEMBER            =  none

int                 p_ID_ALIAS          =    -1

; Private Variables
bool                p_is_created        = false
Actor               p_ref_actor         =  none
bool                p_is_paralyzed      = false

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_QUEUES = DATA.MODS.FUNCS.QUEUES
    p_MEMBERS = DATA.MODS.MEMBERS
    p_MEMBER = (self as ReferenceAlias) as doticu_npcp_member
endFunction

function f_Initialize(int ID_ALIAS)
    p_ID_ALIAS = ID_ALIAS
endFunction

function f_Register()
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
    if !p_MEMBER.Exists()
        return p_CODES.ISNT_MEMBER
    endIf
    p_is_created = true

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return p_CODES.ISNT_IMMOBILE
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    if p_is_paralyzed
        f_Unparalyze()
    endIf
    f_Untoken()

    p_is_paralyzed = false
    p_ref_actor = none
    p_is_created = false

    return p_CODES.SUCCESS
endFunction

; Private Methods
function f_Token()
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)

    if Is_Paralyzed()
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_PARALYZED)
    else
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_PARALYZED)
    endIf

    p_ref_actor.EvaluatePackage()
endFunction

function f_Untoken()
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_PARALYZED)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)

    p_ref_actor.EvaluatePackage()
endFunction

function f_Paralyze()
    if !Is_Paralyzed()
        return
    endIf

    p_ref_actor.EnableAI(false)
endFunction

function f_Unparalyze()
    p_ref_actor.EnableAI(true)
    Debug.SendAnimationEvent(p_ref_actor, "IdleForceDefaultState"); go to cached current animation
endFunction

; Public Methods
int function Enforce()
    return p_MEMBER.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction

bool function Is_Paralyzed()
    return p_is_paralyzed
endFunction

int function Paralyze()
    int code_return

    if !Exists()
        return p_CODES.ISNT_IMMOBILE
    endIf

    if p_is_paralyzed
        return p_CODES.IS_PARALYZED
    endIf

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_PARALYZED)
    p_ref_actor.EvaluatePackage()

    p_is_paralyzed = true

    f_Paralyze()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unparalyze()
    int code_return

    if !Exists()
        return p_CODES.ISNT_IMMOBILE
    endIf

    if !p_is_paralyzed
        return p_CODES.ISNT_PARALYZED
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_PARALYZED)
    p_ref_actor.EvaluatePackage()

    f_Unparalyze()

    p_is_paralyzed = false

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

; maybe a ragdoll func?

; Events
event On_Load_Mod()
    if Exists() && Is_Paralyzed()
        f_Unparalyze()
        f_Paralyze()
    endIf
endEvent

event OnLoad()
    if Exists() && Is_Paralyzed()
        f_Unparalyze()
        f_Paralyze()
    endIf
endEvent
