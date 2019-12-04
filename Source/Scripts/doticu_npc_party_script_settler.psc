Scriptname doticu_npc_party_script_settler extends ReferenceAlias

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

; Private Methods
function p_Token()
    ACTOR2.Token(ref_actor, CONSTS.TOKEN_SETTLER)
endFunction

function p_Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_SETTLER)
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
    is_created = false

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
