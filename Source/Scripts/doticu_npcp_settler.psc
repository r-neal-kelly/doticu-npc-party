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

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false
int                 p_id_alias      =    -1
Actor               p_ref_actor     =  none
doticu_npcp_member  p_ref_member    =  none
ObjectReference     p_ref_marker    =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA, int id_alias)
    p_DATA = DATA

    p_is_created = true
    p_id_alias = id_alias
    p_ref_actor = GetActorReference()
    p_ref_member = (self as ReferenceAlias) as doticu_npcp_member
    p_ref_marker = CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(p_id_alias) as ObjectReference

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_SETTLER)
    p_ref_actor.EvaluatePackage()

    p_Settle()
endFunction

function f_Destroy()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_SETTLER)
    p_ref_actor.EvaluatePackage()

    p_Unsettle()
    f_Untoken()

    p_ref_marker = none
    p_ref_member = none
    p_ref_actor = none
    p_id_alias = -1
    p_is_created = false
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
