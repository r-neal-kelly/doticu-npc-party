Scriptname doticu_npc_party_script_follower extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
int                                 ID_ALIAS    =   -1

; Private Variables
bool is_created = false
Actor ref_actor = none
bool is_sneak = false

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
        return CODES.CREATED
    endIf
    ref_actor = GetActorReference()
    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    if !MODS.MEMBERS.Get_Member(ref_actor).Exists()
        return CODES.NO_MEMBER
    endIf
    is_created = true

    p_Token()
    ; here we can do whatever else we need to do

    return CODES.SUCCESS
endFunction

int function Destroy()
    if !Exists()
        return CODES.DESTROYED
    endIf

    ; here we can do whatever else we need to do
    p_Untoken()

    ref_actor = none

    return CODES.SUCCESS
endFunction

bool function Exists()
    return is_created
endFunction

function Enforce()
    if Exists()
        p_Token()
    endIf
endFunction

function Sneak()
    if Exists()
        is_sneak = true
        Enforce()
    endIf
endFunction

function Unsneak()
    if Exists()
        is_sneak = false
        Enforce()
    endIf
endFunction
