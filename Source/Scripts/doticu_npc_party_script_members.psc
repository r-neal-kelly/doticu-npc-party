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
    ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    ALIASES = (self as Quest) as doticu_npc_party_script_aliases

    ALIASES.f_Initialize(DATA)

    int idx_alias = 0
    int max_aliases = ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = ALIASES.f_Get_Alias(idx_alias)
        (ref_alias as doticu_npc_party_script_member).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npc_party_script_settler).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npc_party_script_immobile).f_Initialize(DATA, idx_alias)
        idx_alias += 1
    endWhile
endFunction

; Private Methods
int function p_Get_Alias_ID(Actor ref_actor)
    return ref_actor.GetItemCount(CONSTS.TOKEN_MEMBER) - 1
endFunction

doticu_npc_party_script_member function p_Get_Member(int id_alias)
    return ALIASES.f_Get_Alias(id_alias) as doticu_npc_party_script_member
endFunction

; Public Methods
int function Create_Member(Actor ref_actor, bool do_clone = false)
    int code_return

    if ALIASES.Is_Full()
        ; cloning can be slow, so check first
        return CODES.HASNT_SPACE_MEMBER
    endIf

    if Should_Clone_Actor(ref_actor)
        do_clone = true
    endIf
    if do_clone
        ref_actor = ACTOR2.Clone(ref_actor)
    endIf

    code_return = ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        if do_clone
            ACTOR2.Delete(ref_actor)
        endIf

        if code_return == CODES.HAS_ACTOR || code_return == CODES.HAS_ALIAS
            return CODES.HAS_MEMBER
        elseIf code_return == CODES.HASNT_SPACE
            return CODES.HASNT_SPACE_MEMBER
        else
            return code_return
        endIf
    endIf
    int id_alias = code_return

    code_return = p_Get_Member(id_alias).f_Create(do_clone)
    if code_return < 0
        ALIASES.Destroy_Alias(id_alias, ref_actor)

        if do_clone
            ACTOR2.Delete(ref_actor)
        endIf

        return code_return
    endIf

    if do_clone
        ACTOR2.Move_To(ref_actor, CONSTS.ACTOR_PLAYER, 60, 180)
        ACTOR2.Greet_Player(ref_actor)
    endIf

    return CODES.SUCCESS
endFunction

int function Destroy_Member(Actor ref_actor, bool destroy_clone = false)
    int code_return
    
    int id_alias = p_Get_Alias_ID(ref_actor)
    if !ALIASES.Has_Alias(id_alias, ref_actor)
        return CODES.HASNT_MEMBER
    endIf

    doticu_npc_party_script_member ref_member = p_Get_Member(id_alias)
    bool is_clone = ref_member.Is_Clone()

    code_return = ref_member.f_Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = ALIASES.Destroy_Alias(id_alias, ref_actor)
    if code_return < 0
        return code_return
    endIf

    if Should_Unclone_Actor(ref_actor)
        destroy_clone = true
    endIf
    if destroy_clone
        ACTOR2.Delete(ref_actor)
    endIf

    return CODES.SUCCESS
endFunction

int function Get_Count()
    return ALIASES.Get_Count()
endFunction

int function Get_Max()
    return ALIASES.Get_Max()
endFunction

bool function Has_Member(Actor ref_actor)
    return ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

doticu_npc_party_script_member function Get_Member(Actor ref_actor)
    return ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npc_party_script_member
endFunction

Alias[] function Get_Aliases_Sorted(int idx_from = 0, int idx_to_ex = -1)
    return ALIASES.Get_Aliases_Sorted(idx_from, idx_to_ex)
endFunction

function Enforce()
    doticu_npc_party_script_member ref_member
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_member = arr_aliases[idx_arr] as doticu_npc_party_script_member
        ref_member.Enforce()
        idx_arr += 1
    endWhile
endFunction

function Unmember()
    doticu_npc_party_script_member ref_member
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_member = arr_aliases[idx_arr] as doticu_npc_party_script_member
        ref_member.Unmember()
        idx_arr += 1
    endWhile
endFunction

bool function Should_Clone_Actor(Actor ref_actor)
    if !ref_actor
        return false
    elseIf VARS.force_clone_unique && ACTOR2.Is_Unique(ref_actor)
        return true
    elseIf VARS.force_clone_generic && ACTOR2.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Actor(Actor ref_actor)
    if !ref_actor
        return false
    elseIf VARS.force_unclone_unique && ACTOR2.Is_Unique(ref_actor)
        return true
    elseIf VARS.force_unclone_generic && ACTOR2.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Member(doticu_npc_party_script_member ref_member)
    return ref_member && ref_member.Is_Clone() && Should_Unclone_Actor(ref_member.Get_Actor())
endFunction
