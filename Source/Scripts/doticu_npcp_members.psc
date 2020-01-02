Scriptname doticu_npcp_members extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_tasklists property TASKLISTS hidden
    doticu_npcp_tasklists function Get()
        return p_DATA.MODS.FUNCS.TASKLISTS
    endFunction
endProperty
doticu_npcp_aliases property ALIASES hidden
    doticu_npcp_aliases function Get()
        return (self as Quest) as doticu_npcp_aliases
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA          =  none

; Private Variables
bool                    p_is_created    = false
doticu_npcp_tasklist    p_tasklist      =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_tasklist = TASKLISTS.Create()

    ALIASES.f_Create(DATA)
endFunction

function f_Destroy()
    ALIASES.f_Destroy()

    TASKLISTS.Destroy(p_tasklist)
    p_is_created = false
endFunction

function f_Register()
    ALIASES.f_Register()

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
        return ref_actor.GetItemCount(CONSTS.TOKEN_MEMBER) - 1
    endIf
endFunction

doticu_npcp_member function p_Get_Member(int id_alias)
    return ALIASES.f_Get_Alias(id_alias) as doticu_npcp_member
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

int function p_Create_Member(Actor ref_actor, bool do_clone = false)
    int code_return

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    if ALIASES.Is_Full()
        ; cloning can be slow, so check first
        return CODES.HASNT_SPACE_MEMBER
    endIf

    if Should_Clone_Actor(ref_actor)
        do_clone = true
    endIf

    if do_clone
        ref_actor = ACTORS.Clone(ref_actor)
        if !ref_actor
            return CODES.CANT_CLONE
        endIf
    else
        if ACTORS.Is_Dead(ref_actor)
            ACTORS.Resurrect(ref_actor)
            if ACTORS.Is_Dead(ref_actor)
                return CODES.CANT_RESURRECT
            endIf
        endIf
    endIf

    code_return = ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        if do_clone
            ACTORS.Delete(ref_actor)
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

    p_Get_Member(id_alias).f_Create(p_DATA, id_alias, do_clone)

    return CODES.SUCCESS
endFunction

int function p_Destroy_Member(Actor ref_actor, bool destroy_clone = false)
    int code_return

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf
    
    int id_alias = p_Get_Alias_ID(ref_actor)
    if !ALIASES.Has_Alias(id_alias, ref_actor)
        return CODES.HASNT_MEMBER
    endIf

    doticu_npcp_member ref_member = p_Get_Member(id_alias)
    bool is_clone = ref_member.Is_Clone()

    ref_member.f_Destroy()

    code_return = ALIASES.Destroy_Alias(id_alias, ref_actor)
    if code_return < 0
        return code_return
    endIf

    if Should_Unclone_Actor(ref_actor)
        destroy_clone = true
    endIf

    if destroy_clone
        ACTORS.Delete(ref_actor)
    endIf

    return CODES.SUCCESS
endFunction

; Public Methods
int function Create_Member(Actor ref_actor, bool do_clone = false)
    GotoState("p_STATE_BUSY")
    int code_return = p_Create_Member(ref_actor, do_clone)
    GotoState("")
    return code_return
endFunction

int function Destroy_Member(Actor ref_actor, bool destroy_clone = false)
    GotoState("p_STATE_BUSY")
    int code_return = p_Destroy_Member(ref_actor, destroy_clone)
    GotoState("")
    return code_return
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

doticu_npcp_member function Get_Member(Actor ref_actor)
    return ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_member
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
    return ALIASES.Get_Aliases_Sorted(idx_from, idx_to_ex)
endFunction

function Enforce()
    doticu_npcp_member ref_member
    Alias[] arr_aliases = ALIASES.Get_Aliases()
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
    elseIf VARS.force_clone_unique && ACTORS.Is_Unique(ref_actor)
        return true
    elseIf VARS.force_clone_generic && ACTORS.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Actor(Actor ref_actor)
    if !ref_actor
        return false
    elseIf VARS.force_unclone_unique && ACTORS.Is_Unique(ref_actor)
        return true
    elseIf VARS.force_unclone_generic && ACTORS.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Member(doticu_npcp_member ref_member)
    return ref_member && ref_member.Is_Clone() && Should_Unclone_Actor(ref_member.Get_Actor())
endFunction

; Update Methods
function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
    p_tasklist = TASKLISTS.Create()
    while !p_Send_Members("doticu_npcp_members_u_0_1_4")
        Utility.Wait(0.25)
    endWhile
endFunction

function u_0_1_5(doticu_npcp_data DATA)
    while !p_Send_Members("doticu_npcp_members_u_0_1_5")
        Utility.Wait(0.25)
    endWhile
endFunction

; Private States
state p_STATE_BUSY
    int function Create_Member(Actor ref_actor, bool do_clone = false)
        return CODES.BUSY
    endFunction
    int function Destroy_Member(Actor ref_actor, bool destroy_clone = false)
        return CODES.BUSY
    endFunction
endState
