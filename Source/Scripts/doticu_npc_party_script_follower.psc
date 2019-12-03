Scriptname doticu_npc_party_script_follower extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
doticu_npc_party_script_follower    FOLLOWER    = none
int                                 ID_ALIAS    =   -1

; Private Variables
Actor ref_actor = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int int_ID_ALIAS)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    FOLLOWER = (self as ReferenceAlias) as doticu_npc_party_script_follower
    ID_ALIAS = int_ID_ALIAS
endFunction

; Public Methods
int function Create()
    ref_actor = FOLLOWER.GetActorReference()

    ACTOR2.Token(ref_actor, CONSTS.TOKEN_FOLLOWER)
    ; here we can do whatever else we need to do

    return CODES.SUCCESS
endFunction

int function Destroy()
    ; here we can do whatever else we need to do
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER)

    ref_actor = none

    return CODES.SUCCESS
endFunction
