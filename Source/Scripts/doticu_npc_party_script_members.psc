Scriptname doticu_npc_party_script_members extends Quest

; Private Constants
doticu_npc_party_script_consts  CONSTS  = none
doticu_npc_party_script_codes   CODES   = none
doticu_npc_party_script_vars    VARS    = none
doticu_npc_party_script_mods    MODS    = none
doticu_npc_party_script_actor   ACTOR2  = none
doticu_npc_party_script_aliases ALIASES = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = MODS.FUNCS.ACTOR2
    ALIASES = (self as Quest) as doticu_npc_party_script_aliases

    ALIASES.f_Initialize(DATA)

    int idx_alias = 0
    int max_aliases = ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npc_party_script_member).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npc_party_script_settler).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npc_party_script_immobile).f_Initialize(DATA, idx_alias)
        idx_alias += 1
    endWhile
endFunction

; Public Methods
int function Create_Member(Actor ref_actor, bool make_clone = false)
    int code_return

    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    if ALIASES.Has_Actor(ref_actor)
        return CODES.IS_DUPLICATE
    endIf
    if ALIASES.Is_Full()
        return CODES.OUT_OF_SPACE
    endIf
    if ACTOR2.Is_Dead(ref_actor)
        ACTOR2.Resurrect(ref_actor)
        if ACTOR2.Is_Dead(ref_actor)
            return CODES.NO_RESURRECT
        endIf
    endIf

    code_return = ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_member = code_return

    Get_Member_By_ID(id_member).Create(make_clone)
    Get_Settler_By_ID(id_member).Create()
    Get_Immobile_By_ID(id_member).Create()

    return id_member
endFunction

int function Destroy_Member(Actor ref_actor)
    int code_return

    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    if !ALIASES.Has_Actor(ref_actor)
        return CODES.NO_MEMBER
    endIf

    Get_Member_By_ID(id_member).Destroy()
    Get_Settler_By_ID(id_member).Destroy()
    Get_Immobile_By_ID(id_member).Destroy()

    code_return = ALIASES.Destroy_Alias(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_member = code_return

    return id_member
endFunction

int function Get_ID(Actor ref_actor)
    return ALIASES.Get_ID(ref_actor)
endFunction

bool function Has_ID(int id_alias)
    return ALIASES.Has_ID(id_alias)
endFunction

bool function Has_Actor(Actor ref_actor)
    return ALIASES.Has_Actor(ref_actor)
endFunction

doticu_npc_party_script_member function Get_Member_By_ID(int id_member)
    return ALIASES.Get_Alias_By_ID(id_member) as doticu_npc_party_script_member
endFunction

doticu_npc_party_script_member function Get_Member_By_Ref(Actor ref_actor)
    return ALIASES.Get_Alias_By_Ref(ref_actor) as doticu_npc_party_script_member
endFunction

doticu_npc_party_script_settler function Get_Settler_By_ID(int id_member)
    return ALIASES.Get_Alias_By_ID(id_member) as doticu_npc_party_script_settler
endFunction

doticu_npc_party_script_settler function Get_Settler_By_Ref(Actor ref_actor)
    return ALIASES.Get_Alias_By_Ref(ref_actor) as doticu_npc_party_script_settler
endFunction

doticu_npc_party_script_immobile function Get_Immobile_By_ID(int id_member)
    return ALIASES.Get_Alias_By_ID(id_member) as doticu_npc_party_script_immobile
endFunction

doticu_npc_party_script_immobile function Get_Immobile_By_Ref(Actor ref_actor)
    return ALIASES.Get_Alias_By_Ref(ref_actor) as doticu_npc_party_script_immobile
endFunction
