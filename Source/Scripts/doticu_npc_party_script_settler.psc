Scriptname doticu_npc_party_script_settler extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
int                                 ID_ALIAS    =   -1
ObjectReference                     REF_MARKER  = none

; Private Variables
bool                            is_created  = false
Actor                           ref_actor   =  none
doticu_npc_party_script_member  ref_member  =  none

; Private Methods
function p_Token()
    ACTOR2.Token(ref_actor, CONSTS.TOKEN_SETTLER)
endFunction

function p_Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_SETTLER)
endFunction

function p_Settle()
    REF_MARKER.MoveTo(ref_actor)
endFunction

function p_Unsettle()
    REF_MARKER.MoveToMyEditorLocation()
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int idx_alias)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    ID_ALIAS = idx_alias
    REF_MARKER = DATA.CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(idx_alias) as ObjectReference
endFunction

int function f_Create()
    int code_return

    if Exists()
        return CODES.IS_SETTLER
    endIf
    ref_actor = GetActorReference()
    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf
    ref_member = MODS.MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return CODES.ISNT_MEMBER
    endIf
    is_created = true

    p_Settle()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return CODES.ISNT_SETTLER
    endIf

    p_Unsettle()
    p_Untoken()

    ref_member = none
    ref_actor = none
    is_created = false

    return CODES.SUCCESS
endFunction

int function f_Enforce()
    int code_return
    
    if !Exists()
        return CODES.ISNT_SETTLER
    endIf

    p_Token()
    ; p_Settle() is not enforced

    return CODES.SUCCESS
endFunction

; Public Methods
int function Enforce()
    return ref_member.Enforce()
endFunction

bool function Exists()
    return is_created
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
