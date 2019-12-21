Scriptname doticu_npcp_immobile extends ReferenceAlias

; Private Constants
doticu_npcp_consts  p_CONSTS        =  none
doticu_npcp_codes   p_CODES         =  none
doticu_npcp_actors  p_ACTORS        =  none
doticu_npcp_members p_MEMBERS       =  none
int                 p_ID_ALIAS      =    -1

; Private Variables
bool                p_is_created    = false
Actor               p_ref_actor     =  none
doticu_npcp_member  p_ref_member    =  none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA, int ID_ALIAS)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_MEMBERS = DATA.MODS.MEMBERS

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
    p_ref_member = p_MEMBERS.Get_Member(p_ref_actor)
    if !p_ref_member
        return p_CODES.ISNT_MEMBER
    endIf
    p_is_created = true

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return p_CODES.ISNT_IMMOBILE
    endIf

    p_Untoken()

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

    p_Token()

    return p_CODES.SUCCESS
endFunction

; Private Methods
function p_Token()
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)
endFunction

function p_Untoken()
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_IMMOBILE)
endFunction

; Public Methods
int function Enforce()
    return p_ref_member.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction
