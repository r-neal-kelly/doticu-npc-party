Scriptname doticu_npc_party_script_follower extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
int                                 ID_ALIAS    =   -1

; Private Variables
bool                            is_created  = false
Actor                           ref_actor   =  none
doticu_npc_party_script_member  ref_member  =  none
bool                            is_sneak    = false

; Private Methods
function p_Token()
    if is_sneak
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER)
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)
    else
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_FOLLOWER)
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)
    endIf
endFunction

function p_Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER)
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int int_ID_ALIAS)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    ID_ALIAS = int_ID_ALIAS
endFunction

; Public Methods
int function Create()
    if Exists()
        return CODES.EXISTS
    endIf
    ref_actor = GetActorReference()
    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    ref_member = MODS.MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return CODES.NO_MEMBER
    endIf
    is_created = true

    p_Token()
    ; here we can do whatever else we need to do

    return CODES.SUCCESS
endFunction

int function Destroy()
    if !Exists()
        return CODES.NO_FOLLOWER
    endIf

    ; here we can do whatever else we need to do
    p_Untoken()

    is_sneak = false
    ref_member = none
    ref_actor = none
    is_created = false

    return CODES.SUCCESS
endFunction

bool function Exists()
    return is_created
endFunction

int function Enforce()
    int code_return

    if !Exists()
        return CODES.NO_FOLLOWER
    endIf

    code_return = ref_member.Enforce()
    if code_return < 0
        return code_return
    endIf

    p_Token()

    return CODES.SUCCESS
endFunction

int function Sneak()
    int code_return

    if !Exists()
        return CODES.NO_FOLLOWER
    endIf

    is_sneak = true

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unsneak()
    int code_return

    if !Exists()
        return CODES.NO_FOLLOWER
    endIf

    is_sneak = false

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

doticu_npc_party_script_member function Get_Member()
    if !Exists() || !ref_member.Exists()
        return none
    else
        return ref_member
    endIf
endFunction
