Scriptname doticu_npc_party_script_member extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
doticu_npc_party_script_member      MEMBER      = none
doticu_npc_party_script_settler     SETTLER     = none
doticu_npc_party_script_immobile    IMMOBILE    = none
int                                 ID_ALIAS    =   -1

; Private Variables
Actor ref_actor = none
bool is_clone = false
bool is_generic = false

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int int_ID_ALIAS)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = MODS.FUNCS.ACTOR2
    MEMBER = (self as ReferenceAlias) as doticu_npc_party_script_member
    SETTLER = (self as ReferenceAlias) as doticu_npc_party_script_settler
    IMMOBILE = (self as ReferenceAlias) as doticu_npc_party_script_immobile
    ID_ALIAS = int_ID_ALIAS
endFunction

; Public Methods
int function Create(bool make_clone)
    ref_actor = MEMBER.GetActorReference()
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

    Token()
    ; here we can do whatever else we need to do

    return CODES.SUCCESS
endFunction

int function Destroy()
    ; here we can do whatever else we need to do
    Untoken()

    is_generic = false
    is_clone = false
    ref_actor = none

    return CODES.SUCCESS
endFunction

function Token()
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

function Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_GENERIC)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_CLONE)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_MEMBER)
endFunction

function Enforce()
    Token()
endFunction
