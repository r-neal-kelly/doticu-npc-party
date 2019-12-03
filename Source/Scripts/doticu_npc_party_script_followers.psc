Scriptname doticu_npc_party_script_followers extends Quest

; Private Constants
doticu_npc_party_script_consts  CONSTS  = none
doticu_npc_party_script_codes   CODES   = none
doticu_npc_party_script_vars    VARS    = none
doticu_npc_party_script_mods    MODS    = none
doticu_npc_party_script_aliases ALIASES = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ALIASES = (self as Quest) as doticu_npc_party_script_aliases

    ALIASES.f_Initialize(DATA)

    int idx_alias = 0
    int max_aliases = ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npc_party_script_follower).f_Initialize(DATA, idx_alias)
        idx_alias += 1
    endWhile
endFunction

; Public Methods
int function Create_Follower(Actor ref_actor)
    int code_return

    if !ref_actor
        return CODES.BAD_PARAM
    endIf
    if !MODS.MEMBERS.Has_Actor(ref_actor)
        return CODES.NO_MEMBER
    endIf
    if ALIASES.Has_Actor(ref_actor)
        return CODES.IS_DUPLICATE
    endIf
    if ALIASES.Is_Full()
        return CODES.OUT_OF_SPACE
    endIf

    code_return = ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_follower = code_return

    Get_Follower_By_ID(id_follower).Create()

    return id_follower
endFunction

int function Destroy_Follower(Actor ref_actor)
    int code_return
    
    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    if !ALIASES.Has_Actor(ref_actor)
        return CODES.NO_MEMBER; INVALID_PARAM, NO_COUNTERPART
    endIf

    Get_Follower_By_Ref(ref_actor).Destroy()

    code_return = ALIASES.Destroy_Alias(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_follower = code_return

    return id_follower
endFunction

int function Get_ID(Actor ref_actor)
    return ALIASES.Get_ID(ref_actor)
endFunction

bool function Has_ID(int id_follower)
    return ALIASES.Has_ID(id_follower)
endFunction

doticu_npc_party_script_follower function Get_Follower_By_ID(int id_member)
    return ALIASES.Get_Alias_By_ID(id_member) as doticu_npc_party_script_follower
endFunction

doticu_npc_party_script_follower function Get_Follower_By_Ref(Actor ref_actor)
    return ALIASES.Get_Alias_By_Ref(ref_actor) as doticu_npc_party_script_follower
endFunction

int function Enforce_Follower_By_Ref(Actor ref_actor)
    int code_return

    code_return = Get_ID(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_follower = code_return

    code_return = Enforce_Follower_By_ID(id_follower)
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Enforce_Follower_By_ID(int id_follower)
    int code_return

    if !Has_ID(id_follower)
        return CODES.NO_FOLLOWER
    endIf

    Actor ref_actor = ALIASES.Get_Actor(id_follower)
    code_return = MODS.MEMBERS.Enforce_Member_By_Ref(ref_actor)
    if code_return < 0
        return code_return
    endIf

    Get_Follower_By_ID(id_follower).Enforce()

    return CODES.SUCCESS
endFunction
