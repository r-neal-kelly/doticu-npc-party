Scriptname doticu_npcp_immobile extends ReferenceAlias

; Private Constants
doticu_npcp_data    p_DATA              =  none
int                 p_ID_ALIAS          =    -1

; Public Constants
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
doticu_npcp_member property MEMBER hidden
    doticu_npcp_member function Get()
        return (self as ReferenceAlias) as doticu_npcp_member
    endFunction
endProperty

; Private Variables
bool                p_is_created        = false
Actor               p_ref_actor         =  none
bool                p_is_paralyzed      = false

; Friend Methods
function f_Initialize(doticu_npcp_data DATA, int ID_ALIAS)
    p_DATA = DATA
    p_ID_ALIAS = ID_ALIAS
endFunction

int function f_Create()
    int code_return

    if Exists()
        return CODES.IS_IMMOBILE
    endIf
    p_ref_actor = GetActorReference()
    if !p_ref_actor
        return CODES.ISNT_ACTOR
    endIf
    if !MEMBER.Exists()
        return CODES.ISNT_MEMBER
    endIf
    p_is_created = true

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    return CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return CODES.ISNT_IMMOBILE
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_IMMOBILE)
    p_ref_actor.EvaluatePackage()

    if p_is_paralyzed
        f_Unparalyze()
    endIf
    f_Untoken()

    p_is_paralyzed = false
    p_ref_actor = none
    p_is_created = false

    return CODES.SUCCESS
endFunction

; Private Methods
function f_Token()
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_IMMOBILE)

    if Is_Paralyzed()
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    endIf

    p_ref_actor.EvaluatePackage()
endFunction

function f_Untoken()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_PARALYZED)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_IMMOBILE)

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
    return MEMBER.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction

bool function Is_Paralyzed()
    return Exists() && p_is_paralyzed
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
    p_ref_actor.EvaluatePackage()

    p_is_paralyzed = true

    f_Paralyze()

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
    p_ref_actor.EvaluatePackage()

    f_Unparalyze()

    p_is_paralyzed = false

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
