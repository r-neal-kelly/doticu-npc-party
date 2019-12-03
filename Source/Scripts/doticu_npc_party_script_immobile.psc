Scriptname doticu_npc_party_script_immobile extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
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
    MEMBER = (self as ReferenceAlias) as doticu_npc_party_script_member
    SETTLER = (self as ReferenceAlias) as doticu_npc_party_script_settler
    IMMOBILE = (self as ReferenceAlias) as doticu_npc_party_script_immobile
    ID_ALIAS = int_ID_ALIAS
endFunction

; Public Methods
int function Create()
    ref_actor = MEMBER.GetActorReference()
    return CODES.SUCCESS
endFunction

int function Destroy()
    ref_actor = none
    return CODES.SUCCESS
endFunction
