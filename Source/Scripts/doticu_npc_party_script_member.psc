Scriptname doticu_npc_party_script_member extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
doticu_npc_party_script_settler     SETTLER     = none
doticu_npc_party_script_immobile    IMMOBILE    = none
doticu_npc_party_script_followers   FOLLOWERS   = none
int                                 ID_ALIAS    =   -1

; Private Variables
bool    is_created  = false
Actor   ref_actor   =  none
bool    is_clone    = false
bool    is_generic  = false
bool    is_thrall   = false

; Private Methods
function p_Token()
    ACTOR2.Token(ref_actor, CONSTS.TOKEN_MEMBER, ID_ALIAS + 1)
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
    if is_thrall
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_THRALL)
    else
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_THRALL)
    endIf
endFunction

function p_Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_THRALL)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_GENERIC)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_CLONE)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_MEMBER)
endFunction

function p_Enthrall()
    ; add factions
endFunction

function p_Unthrall()
    ; remove factions
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int IDX_ALIAS)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = MODS.FUNCS.ACTOR2
    SETTLER = (self as ReferenceAlias) as doticu_npc_party_script_settler
    IMMOBILE = (self as ReferenceAlias) as doticu_npc_party_script_immobile
    FOLLOWERS = MODS.FOLLOWERS
    ID_ALIAS = IDX_ALIAS
endFunction

int function f_Enforce()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Token()
    if is_thrall
        p_Enthrall()
    endIf

    if SETTLER.Exists()
        code_return = SETTLER.f_Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf
    if IMMOBILE.Exists()
        code_return = IMMOBILE.f_Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf

    ref_actor.EvaluatePackage()

    return CODES.SUCCESS
endFunction

; Public Methods
int function Create(bool make_clone)
    int code_return

    if Exists()
        return CODES.IS_MEMBER
    endIf
    ref_actor = GetActorReference()
    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf
    if ACTOR2.Is_Dead(ref_actor)
        ACTOR2.Resurrect(ref_actor)
        if ACTOR2.Is_Dead(ref_actor)
            return CODES.CANT_RESURRECT
        endIf
    endIf

    is_created = true
    if make_clone
        is_clone = true
        ; need to add this function, but probably in MEMBERS.Create_Member()
    else
        is_clone = false
    endIf
    if ACTOR2.Is_Generic(ref_actor)
        is_generic = true
    else
        is_generic = false
    endIf

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Destroy()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if MODS.FOLLOWERS.Has_Follower(ref_actor)
        code_return = MODS.FOLLOWERS.Destroy_Follower(ref_actor)
        if code_return < 0
            return code_return
        endIf
    endIf
    if IMMOBILE.Exists()
        code_return = Mobilize()
        if code_return < 0
            return code_return
        endIf
    endIf
    if SETTLER.Exists()
        code_return = Unsettle()
        if code_return < 0
            return code_return
        endIf
    endIf

    if is_thrall
        p_Unthrall()
    endIf
    p_Untoken()

    is_thrall = false
    is_generic = false
    is_clone = false
    ref_actor = none
    is_created = false

    return CODES.SUCCESS
endFunction

bool function Exists()
    return is_created
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

int function Settle()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    code_return = SETTLER.Create()
    if code_return < 0
        return code_return
    endIf

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unsettle()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    code_return = SETTLER.Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Immobilize()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    code_return = IMMOBILE.Create()
    if code_return < 0
        return code_return
    endIf

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Mobilize()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    code_return = IMMOBILE.Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Follow()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    code_return = FOLLOWERS.Create_Follower(ref_actor)
    if code_return < 0
        return code_return
    endIf

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unfollow()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    code_return = FOLLOWERS.Destroy_Follower(ref_actor)
    if code_return < 0
        return code_return
    endIf

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Enthrall()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if is_thrall
        return CODES.IS_THRALL
    endIf

    is_thrall = true

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unthrall()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !is_thrall
        return CODES.ISNT_THRALL
    endIf

    is_thrall = false

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Access()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf
    
    ACTOR2.Open_Inventory(ref_actor)

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

bool function Is_Member()
    return Exists()
endFunction

bool function Is_Settler()
    return SETTLER.Exists()
endFunction

bool function Is_Immobile()
    return IMMOBILE.Exists()
endFunction

bool function Is_Follower()
    return FOLLOWERS.Has_Follower(ref_actor)
endFunction

bool function Is_Thrall()
    return is_thrall
endFunction

; Events
event OnActivate(ObjectReference ref_activator)
    f_Enforce()
endEvent
