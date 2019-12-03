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

    ACTOR2.Token(ref_actor, CONSTS.TOKEN_MEMBER)
    if make_clone
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_CLONE)
    endIf
    if !ACTOR2.Is_Unique(ref_actor)
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_GENERIC)
    endIf
    ; here we can do whatever else we need to do

    return CODES.SUCCESS
endFunction

int function Destroy()
    ; here we can do whatever else we need to do
    if ACTOR2.Has_Token(ref_actor, CONSTS.TOKEN_GENERIC)
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_GENERIC)
    endIf
    if ACTOR2.Has_Token(ref_actor, CONSTS.TOKEN_CLONE)
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_CLONE)
    endIf
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_MEMBER)

    ref_actor = none

    return CODES.SUCCESS
endFunction
