Scriptname doticu_npcp_members extends Quest

; Private Constants
doticu_npcp_consts  p_CONSTS    = none
doticu_npcp_codes   p_CODES     = none
doticu_npcp_vars    p_VARS      = none
doticu_npcp_actors  p_ACTORS    = none

doticu_npcp_aliases p_ALIASES   = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS

    p_ALIASES = (self as Quest) as doticu_npcp_aliases

    p_ALIASES.f_Initialize(DATA)

    int idx_alias = 0
    int max_aliases = p_ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = p_ALIASES.f_Get_Alias(idx_alias)
        (ref_alias as doticu_npcp_member).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npcp_settler).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npcp_immobile).f_Initialize(DATA, idx_alias)
        idx_alias += 1
    endWhile
endFunction

function f_Register()
endFunction

; Private Methods
int function p_Get_Alias_ID(Actor ref_actor)
    return ref_actor.GetItemCount(p_CONSTS.TOKEN_MEMBER) - 1
endFunction

doticu_npcp_member function p_Get_Member(int id_alias)
    return p_ALIASES.f_Get_Alias(id_alias) as doticu_npcp_member
endFunction

; Public Methods
int function Create_Member(Actor ref_actor, bool do_clone = false)
    int code_return

    if p_ALIASES.Is_Full()
        ; cloning can be slow, so check first
        return p_CODES.HASNT_SPACE_MEMBER
    endIf

    if Should_Clone_Actor(ref_actor)
        do_clone = true
    endIf
    if do_clone
        ref_actor = p_ACTORS.Clone(ref_actor)
    endIf

    code_return = p_ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        if do_clone
            p_ACTORS.Delete(ref_actor)
        endIf

        if code_return == p_CODES.HAS_ACTOR || code_return == p_CODES.HAS_ALIAS
            return p_CODES.HAS_MEMBER
        elseIf code_return == p_CODES.HASNT_SPACE
            return p_CODES.HASNT_SPACE_MEMBER
        else
            return code_return
        endIf
    endIf
    int id_alias = code_return

    code_return = p_Get_Member(id_alias).f_Create(do_clone)
    if code_return < 0
        p_ALIASES.Destroy_Alias(id_alias, ref_actor)

        if do_clone
            p_ACTORS.Delete(ref_actor)
        endIf

        return code_return
    endIf

    if do_clone
        p_ACTORS.Move_To(ref_actor, p_CONSTS.ACTOR_PLAYER, 60, 180)
        p_ACTORS.Greet_Player(ref_actor)
    endIf

    return p_CODES.SUCCESS
endFunction

int function Destroy_Member(Actor ref_actor, bool destroy_clone = false)
    int code_return
    
    int id_alias = p_Get_Alias_ID(ref_actor)
    if !p_ALIASES.Has_Alias(id_alias, ref_actor)
        return p_CODES.HASNT_MEMBER
    endIf

    doticu_npcp_member ref_member = p_Get_Member(id_alias)
    bool is_clone = ref_member.Is_Clone()

    code_return = ref_member.f_Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = p_ALIASES.Destroy_Alias(id_alias, ref_actor)
    if code_return < 0
        return code_return
    endIf

    if Should_Unclone_Actor(ref_actor)
        destroy_clone = true
    endIf
    if destroy_clone
        p_ACTORS.Delete(ref_actor)
    endIf

    return p_CODES.SUCCESS
endFunction

int function Get_Count()
    return p_ALIASES.Get_Count()
endFunction

int function Get_Max()
    return p_ALIASES.Get_Max()
endFunction

bool function Has_Member(Actor ref_actor)
    return p_ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

doticu_npcp_member function Get_Member(Actor ref_actor)
    return p_ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_member
endFunction

Alias[] function Get_Aliases_Sorted(int idx_from = 0, int idx_to_ex = -1)
    return p_ALIASES.Get_Aliases_Sorted(idx_from, idx_to_ex)
endFunction

function Enforce()
    doticu_npcp_member ref_member
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_member = arr_aliases[idx_arr] as doticu_npcp_member
        ref_member.Enforce()
        idx_arr += 1
    endWhile
endFunction

function Unmember()
    doticu_npcp_member ref_member
    Alias[] arr_aliases = p_ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_member = arr_aliases[idx_arr] as doticu_npcp_member
        ref_member.Unmember()
        idx_arr += 1
    endWhile
endFunction

bool function Should_Clone_Actor(Actor ref_actor)
    if !ref_actor
        return false
    elseIf p_VARS.force_clone_unique && p_ACTORS.Is_Unique(ref_actor)
        return true
    elseIf p_VARS.force_clone_generic && p_ACTORS.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Actor(Actor ref_actor)
    if !ref_actor
        return false
    elseIf p_VARS.force_unclone_unique && p_ACTORS.Is_Unique(ref_actor)
        return true
    elseIf p_VARS.force_unclone_generic && p_ACTORS.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Member(doticu_npcp_member ref_member)
    return ref_member && ref_member.Is_Clone() && Should_Unclone_Actor(ref_member.Get_Actor())
endFunction
