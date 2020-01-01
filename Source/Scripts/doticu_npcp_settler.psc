Scriptname doticu_npcp_settler extends ReferenceAlias

; Private Constants
doticu_npcp_data    p_DATA          =  none
int                 p_ID_ALIAS      =    -1
ObjectReference     p_REF_MARKER    =  none

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
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_member property MEMBER hidden
    doticu_npcp_member function Get()
        return (self as ReferenceAlias) as doticu_npcp_member
    endFunction
endProperty

; Private Variables
bool                p_is_created    = false
Actor               p_ref_actor     =  none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA, int ID_ALIAS)
    p_DATA = DATA
    p_ID_ALIAS = ID_ALIAS
    p_REF_MARKER = CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(ID_ALIAS) as ObjectReference
endFunction

int function f_Create()
    int code_return

    if Exists()
        return CODES.IS_SETTLER
    endIf
    p_ref_actor = GetActorReference()
    if !p_ref_actor
        return CODES.ISNT_ACTOR
    endIf
    if !MEMBER.Exists()
        return CODES.ISNT_MEMBER
    endIf
    p_is_created = true

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_SETTLER)
    p_ref_actor.EvaluatePackage()

    p_Settle()

    return CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return CODES.ISNT_SETTLER
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_SETTLER)
    p_ref_actor.EvaluatePackage()

    p_Unsettle()
    f_Untoken()

    p_ref_actor = none
    p_is_created = false

    return CODES.SUCCESS
endFunction

; Private Methods
function f_Token()
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_SETTLER)

    p_ref_actor.EvaluatePackage()
endFunction

function f_Untoken()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_SETTLER)

    p_ref_actor.EvaluatePackage()
endFunction

function p_Settle()
    p_REF_MARKER.MoveTo(p_ref_actor)
endFunction

function p_Unsettle()
    p_REF_MARKER.MoveToMyEditorLocation()
endFunction

; Public Methods
int function Enforce()
    return MEMBER.Enforce()
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
