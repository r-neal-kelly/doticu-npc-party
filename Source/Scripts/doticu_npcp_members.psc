Scriptname doticu_npcp_members extends Quest

; Private Constants
doticu_npcp_data        p_DATA      = none
doticu_npcp_consts      p_CONSTS    = none
doticu_npcp_codes       p_CODES     = none
doticu_npcp_vars        p_VARS      = none
doticu_npcp_actors      p_ACTORS    = none
doticu_npcp_tasklists   p_TASKLISTS = none
doticu_npcp_aliases     p_ALIASES   = none

doticu_npcp_tasklist    p_TASKLIST  = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_TASKLISTS = DATA.MODS.FUNCS.TASKLISTS
    p_ALIASES = (self as Quest) as doticu_npcp_aliases

    p_ALIASES.f_Link(DATA)
endFunction

function f_Initialize()
    p_ALIASES.f_Initialize()

    p_TASKLIST = p_TASKLISTS.Create()

    int idx_alias = 0
    int max_aliases = GetNumAliases()
    while idx_alias < max_aliases
        (GetNthAlias(idx_alias) as doticu_npcp_member).f_Initialize(p_DATA, idx_alias)
        idx_alias += 1
    endWhile
endFunction

function f_Register()
    p_ALIASES.f_Register()

    int idx_alias = 0
    int max_aliases = GetNumAliases()
    while idx_alias < max_aliases
        (GetNthAlias(idx_alias) as doticu_npcp_member).f_Register()
        idx_alias += 1
    endWhile
endFunction

; Private Methods
int function p_Get_Alias_ID(Actor ref_actor)
    if !ref_actor
        return -1
    else
        return ref_actor.GetItemCount(p_CONSTS.TOKEN_MEMBER) - 1
    endIf
endFunction

doticu_npcp_member function p_Get_Member(int id_alias)
    return p_ALIASES.f_Get_Alias(id_alias) as doticu_npcp_member
endFunction

bool function p_Send_Members(string str_event)
    int handle = ModEvent.Create(str_event)

    if !handle
        return false
    endIf

    ModEvent.PushForm(handle, p_DATA as Form)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
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

doticu_npcp_settler function Get_Settler(Actor ref_actor)
    if Has_Member(ref_actor)
        return Get_Member(ref_actor).Get_Settler()
    else
        return none
    endIf
endFunction

doticu_npcp_immobile function Get_Immobile(Actor ref_actor)
    if Has_Member(ref_actor)
        return Get_Member(ref_actor).Get_Immobile()
    else
        return none
    endIf
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
    while !p_Send_Members("doticu_npcp_members_unmember")
        Utility.Wait(0.25)
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

; Update Methods
function u_0_1_0()
    while !p_Send_Members("doticu_npcp_members_u_0_1_0")
        Utility.Wait(0.25)
    endWhile
endFunction

function u_0_1_1()
    while !p_Send_Members("doticu_npcp_members_u_0_1_1")
        Utility.Wait(0.25)
    endWhile
endFunction

function u_0_1_2()
    while !p_Send_Members("doticu_npcp_members_u_0_1_2")
        Utility.Wait(0.25)
    endWhile
endFunction

function u_0_1_3()
    while !p_Send_Members("doticu_npcp_members_u_0_1_3")
        Utility.Wait(0.25)
    endWhile
endFunction

function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
    p_TASKLIST = p_TASKLISTS.Create()
    while !p_Send_Members("doticu_npcp_members_u_0_1_4")
        Utility.Wait(0.25)
    endWhile
endFunction
