Scriptname doticu_npcp_settler extends ReferenceAlias

; Private Constants
doticu_npcp_consts  p_CONSTS        =  none
doticu_npcp_codes   p_CODES         =  none
doticu_npcp_actors  p_ACTORS        =  none
doticu_npcp_members p_MEMBERS       =  none

int                 p_ID_ALIAS      =    -1
ObjectReference     p_REF_MARKER    =  none

; Private Variables
bool                p_is_created    = false
Actor               p_ref_actor     =  none
doticu_npcp_member  p_ref_member    =  none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_MEMBERS = DATA.MODS.MEMBERS
endFunction

function f_Initialize(int ID_ALIAS)
    p_ID_ALIAS = ID_ALIAS
    p_REF_MARKER = p_CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(ID_ALIAS) as ObjectReference
endFunction

function f_Register()
endFunction

int function f_Create()
    int code_return

    if Exists()
        return p_CODES.IS_SETTLER
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

    p_Settle()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return p_CODES.ISNT_SETTLER
    endIf

    p_Unsettle()
    p_Untoken()

    p_ref_member = none
    p_ref_actor = none
    p_is_created = false

    return p_CODES.SUCCESS
endFunction

int function f_Enforce()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_SETTLER
    endIf

    p_Token()
    ; p_Settle() is not enforced

    return p_CODES.SUCCESS
endFunction

; Private Methods
function p_Token()
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_SETTLER)
endFunction

function p_Untoken()
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_SETTLER)
endFunction

function p_Settle()
    p_REF_MARKER.MoveTo(p_ref_actor)
endFunction

function p_Unsettle()
    p_REF_MARKER.MoveToMyEditorLocation()
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
        return p_CODES.ISNT_SETTLER
    endIf

    p_Settle()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

; Update Methods
function u_0_1_0()
endFunction
