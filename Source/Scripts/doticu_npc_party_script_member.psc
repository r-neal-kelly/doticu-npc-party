Scriptname doticu_npc_party_script_member extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
doticu_npc_party_script_settler     SETTLER     = none
doticu_npc_party_script_immobile    IMMOBILE    = none
int                                 ID_ALIAS    =   -1

; Private Variables
bool    is_created  = false
Actor   ref_actor   =  none
bool    is_clone    = false
bool    is_generic  = false

; Private Methods
function p_Token()
    ACTOR2.Token(ref_actor, CONSTS.TOKEN_MEMBER)
    if is_clone
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_CLONE)
    else
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_CLONE)
    endIf
    if is_generic
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_GENERIC)
    else
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_GENERIC)
    endIf
endFunction

function p_Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_GENERIC)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_CLONE)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_MEMBER)
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int int_ID_ALIAS)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = MODS.FUNCS.ACTOR2
    SETTLER = (self as ReferenceAlias) as doticu_npc_party_script_settler
    IMMOBILE = (self as ReferenceAlias) as doticu_npc_party_script_immobile
    ID_ALIAS = int_ID_ALIAS
endFunction

; Public Methods
int function Create(bool make_clone)
    if Exists()
        return CODES.EXISTS
    endIf
    ref_actor = GetActorReference()
    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    if ACTOR2.Is_Dead(ref_actor)
        ACTOR2.Resurrect(ref_actor)
        if ACTOR2.Is_Dead(ref_actor)
            return CODES.NO_RESURRECT
        endIf
    endIf
    is_created = true

    if make_clone
        is_clone = true
    else
        is_clone = false
    endIf
    if ACTOR2.Is_Generic(ref_actor)
        is_generic = true
    else
        is_generic = false
    endIf

    p_Token()
    ; here we can do whatever else we need to do

    return CODES.SUCCESS
endFunction

int function Destroy()
    int code_return

    if !Exists()
        return CODES.NO_MEMBER
    endIf

    if MODS.FOLLOWERS.Has_Follower(ref_actor)
        code_return = MODS.FOLLOWERS.Destroy_Follower(ref_actor)
        if code_return < 0
            return code_return
        endIf
    endIf
    if IMMOBILE.Exists()
        code_return = Unsettle()
        if code_return < 0
            return code_return
        endIf
    endIf
    if SETTLER.Exists()
        code_return = Mobilize()
        if code_return < 0
            return code_return
        endIf
    endIf

    ; here we can do whatever else we need to do
    p_Untoken()

    is_generic = false
    is_clone = false
    ref_actor = none
    is_created = false

    return CODES.SUCCESS
endFunction

bool function Exists()
    return is_created
endFunction

int function Settle()
    int code_return

    if !Exists()
        return CODES.NO_MEMBER
    endIf

    code_return = SETTLER.Create()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unsettle()
    int code_return

    if !Exists()
        return CODES.NO_MEMBER
    endIf

    code_return = SETTLER.Destroy()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Immobilize()
    int code_return

    if !Exists()
        return CODES.NO_MEMBER
    endIf

    code_return = IMMOBILE.Create()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Mobilize()
    int code_return

    if !Exists()
        return CODES.NO_MEMBER
    endIf

    code_return = IMMOBILE.Destroy()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Enforce()
    int code_return

    if !Exists()
        return CODES.NO_MEMBER
    endIf

    p_Token()

    if SETTLER.Exists()
        code_return = SETTLER.Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf
    if IMMOBILE.Exists()
        code_return = IMMOBILE.Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf

    return CODES.SUCCESS
endFunction

doticu_npc_party_script_settler function Get_Settler()
    if !Exists() || !SETTLER.Exists()
        return none
    else
        return SETTLER
    endIf
endFunction

doticu_npc_party_script_immobile function Get_Immobile()
    if !Exists() || !IMMOBILE.Exists()
        return none
    else
        return IMMOBILE
    endIf
endFunction
