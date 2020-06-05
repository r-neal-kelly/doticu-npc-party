;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_aliases extends Quest

; Modules
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
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none
int                 p_MAX_ALIASES   =    -1

; Private Variables
bool                p_is_created    = false
bool                p_is_locked     = false
bool                p_can_sort      = false
bool                p_should_sort   = false

int                 p_num_free      =    -1
int[]               p_arr_free      =  none

int                 p_num_aliases   =    -1
Alias[]             p_arr_aliases   =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA
    p_MAX_ALIASES = GetNumAliases()

    p_is_created = true
    p_is_locked = false
    p_can_sort = true
    p_should_sort = false

    p_Create_Arrays()
endFunction

function f_Destroy()
    p_Destroy_Arrays()

    p_should_sort = false
    p_can_sort = true
    p_is_locked = false
    p_is_created = false
endFunction

function f_Register()
p_Lock()
    p_MAX_ALIASES = GetNumAliases()

    p_num_aliases = doticu_npcp.Quest_Count_Used_Aliases(self)
    p_arr_aliases = doticu_npcp.Quest_Get_Used_Aliases(self)

    p_num_free = doticu_npcp.Quest_Count_Free_Aliases(self)
    p_arr_free = doticu_npcp.Quest_Get_Free_Alias_IDs(self)
p_Unlock()

    Request_Sort()
    Sort()
endFunction

int function f_ID_To_Idx(int id_alias)
    if id_alias < 0 || id_alias >= p_MAX_ALIASES
        return -1
    endIf

    p_Sort(); this might be temp and we can make a func in here for Display Start

    ; we must keep aliases numbered correctly in .esp for this to work,
    ; else we could use GetAliasByID. we can't skip any numbers, use SSEEdit!
    Alias base_alias = GetNthAlias(id_alias)
    int idx_alias = p_arr_aliases.Find(base_alias)

    if idx_alias > -1
        return idx_alias
    else
        return -1
    endIf
endFunction

int function f_To_Relative_Idx(int idx_alias)
    if idx_alias < 0
        idx_alias = p_num_aliases + idx_alias
    elseIf idx_alias >= p_num_aliases
        idx_alias = idx_alias - p_num_aliases
    endIf

    return idx_alias
endFunction

ReferenceAlias function f_Get_Alias(int id_alias); can this be removed?
    if id_alias > -1 && id_alias < p_MAX_ALIASES
p_Lock()
        ReferenceAlias ref_alias = GetNthAlias(id_alias) as ReferenceAlias
p_Unlock()
        return ref_alias
    else
        return none
    endIf
endFunction

; Private Methods
function p_Lock(float timeout = 15.0)
    float time_waited = 0.0

    while p_is_locked && time_waited < timeout
        FUNCS.Wait(0.01)
        time_waited += 0.01
    endWhile
    
    p_is_locked = true
endFunction

function p_Unlock()
    p_is_locked = false
endFunction

int function p_Unlock_Return_Int(int val)
    p_Unlock()
    return val
endFunction

function p_Create_Arrays()
    p_num_free = p_MAX_ALIASES
    p_arr_free = Utility.CreateIntArray(p_MAX_ALIASES, -1)

    p_num_aliases = 0
    p_arr_aliases = Utility.CreateAliasArray(p_MAX_ALIASES, none)
    
    int idx_free = 0
    int idx_alias = p_MAX_ALIASES
    while idx_free < p_MAX_ALIASES
        idx_alias -= 1
        p_arr_free[idx_free] = idx_alias
        idx_free += 1
    endWhile
endFunction

function p_Destroy_Arrays()
    p_arr_aliases = Utility.CreateAliasArray(1, none)
    p_num_aliases = -1

    p_arr_free = Utility.CreateIntArray(1, 0)
    p_num_free = -1
endFunction

int function p_Create_ID(Actor ref_actor)
    if p_num_free <= 0 || p_num_aliases >= p_MAX_ALIASES
        return CODES.HASNT_SPACE
    endIf

    p_num_free -= 1
    int id_alias = p_arr_free[p_num_free]

    p_arr_aliases[p_num_aliases] = GetNthAlias(id_alias)
    p_num_aliases += 1

    return id_alias
endFunction

int function p_Destroy_ID(int id_alias)
    if p_num_free >= p_MAX_ALIASES
        return CODES.SUCCESS
    endIf

    int idx_alias = p_arr_aliases.Find(GetNthAlias(id_alias))
    if idx_alias < 0
        return CODES.HASNT_ID
    endIf

    p_num_aliases -= 1
    if idx_alias != p_num_aliases
        ; idx_alias was not last idx, so defrag array
        p_arr_aliases[idx_alias] = p_arr_aliases[p_num_aliases]
    endIf
    p_arr_aliases[p_num_aliases] = none
    
    p_arr_free[p_num_free] = id_alias
    p_num_free += 1

    return CODES.SUCCESS
endFunction

function p_Sort()
    if !Will_Sort()
        return
    endIf

    if (self as Quest) as doticu_npcp_members
        p_arr_aliases = doticu_npcp.Aliases_Sort(p_arr_aliases, VARS.str_sort_members)
    else
        p_arr_aliases = doticu_npcp.Aliases_Sort(p_arr_aliases, VARS.str_sort_followers)
    endIf
    
    p_should_sort = false
endFunction

ReferenceAlias function p_Actor_To_Alias(Actor ref_actor)
    if ref_actor
        ReferenceAlias[] arr_aliases = ref_actor.GetReferenceAliases()
        int idx_aliases = arr_aliases.length
        while idx_aliases > 0
            idx_aliases -= 1
            if arr_aliases[idx_aliases].GetOwningQuest() == self as Quest
                return arr_aliases[idx_aliases]
            endIf
        endWhile
        
        return none
    else
        return none
    endIf
endFunction

bool function p_Has_Actor(Actor ref_actor)
    return p_Actor_To_Alias(ref_actor) != none
endFunction

Actor function p_Get_Actor(int id_alias)
    int idx_alias = f_ID_To_Idx(id_alias)
    if idx_alias > -1
        return (p_arr_aliases[idx_alias] as ReferenceAlias).GetActorReference()
    else
        return none
    endIf
endFunction

ReferenceAlias function p_Get_Alias(int id_alias)
    int idx_alias = f_ID_To_Idx(id_alias)
    if idx_alias > -1
        return p_arr_aliases[idx_alias] as ReferenceAlias
    else
        return none
    endIf
endFunction

bool function p_Is_Full()
    return p_num_free <= 0
endFunction

bool function p_Has_Alias(int id_alias, Actor ref_actor)
    return ref_actor && p_Get_Actor(id_alias) == ref_actor
endFunction

int function p_Get_Count()
    return p_num_aliases
endFunction

; Public Methods
int function Create_Alias(Actor ref_actor)
    p_Lock()

        int code_return

        if !ref_actor
            return p_Unlock_Return_Int(CODES.ISNT_ACTOR)
        endIf

        if p_Has_Actor(ref_actor)
            return p_Unlock_Return_Int(CODES.HAS_ACTOR)
        endIf

        if p_Is_Full()
            return p_Unlock_Return_Int(CODES.HASNT_SPACE)
        endIf

        code_return = p_Create_ID(ref_actor)
        if code_return < 0
            return p_Unlock_Return_Int(code_return)
        endIf
        int id_alias = code_return

        (GetNthAlias(id_alias) as ReferenceAlias).ForceRefTo(ref_actor)

        p_should_sort = true

    p_Unlock()
    
    return id_alias
endFunction

int function Destroy_Alias(int id_alias, Actor ref_actor)
    p_Lock()

        int code_return

        if !ref_actor
            return p_Unlock_Return_Int(CODES.ISNT_ACTOR)
        endIf

        if !p_Has_Alias(id_alias, ref_actor)
            return p_Unlock_Return_Int(CODES.HASNT_ALIAS)
        endIf

        (GetNthAlias(id_alias) as ReferenceAlias).Clear()

        code_return = p_Destroy_ID(id_alias)
        if code_return < 0
            return p_Unlock_Return_Int(code_return)
        endIf

        p_should_sort = true

    p_Unlock()

    return CODES.SUCCESS
endFunction

function Sort()
    p_Sort()
endFunction

bool function Will_Sort()
    return p_can_sort && p_should_sort && p_num_aliases > 1
endFunction

function Enable_Sort()
    p_can_sort = true
endFunction

function Disable_Sort()
    p_can_sort = false
endFunction

function Request_Sort()
    p_should_sort = true
endFunction

int function Get_Count()
    p_Lock()
        int res = p_Get_Count()
    p_Unlock()
    
    return res
endFunction

int function Get_Max()
    return p_MAX_ALIASES
endFunction

bool function Has_Alias(int id_alias, Actor ref_actor)
p_Lock()
    bool res = p_Has_Alias(id_alias, ref_actor)
p_Unlock()

    return res
endFunction

ReferenceAlias function Get_Alias(int id_alias, Actor ref_actor)
    if !ref_actor
        return none
    endIf

    ReferenceAlias ref_alias = p_Actor_To_Alias(ref_actor)
    if ref_alias == GetNthAlias(id_alias)
        return ref_alias
    else
        return none
    endIf
endFunction

ReferenceAlias function Get_Next_Alias(int id_alias, Actor ref_actor)
    if !p_Has_Alias(id_alias, ref_actor)
        return none
    endIf

    p_Sort()

    int idx_alias_next = f_To_Relative_Idx(f_ID_To_Idx(id_alias) + 1)

    return p_arr_aliases[idx_alias_next] as ReferenceAlias
endFunction

ReferenceAlias function Get_Prev_Alias(int id_alias, Actor ref_actor)
    if !p_Has_Alias(id_alias, ref_actor)
        return none
    endIf

    p_Sort()

    int idx_alias_prev = f_To_Relative_Idx(f_ID_To_Idx(id_alias) - 1)

    return p_arr_aliases[idx_alias_prev] as ReferenceAlias
endFunction

Alias[] function Get_Aliases(int idx_from = 0, int idx_to_ex = -1)
    if idx_to_ex > p_num_aliases || idx_to_ex < 0
        idx_to_ex = p_num_aliases
    endIf

    p_Sort()
    
    return doticu_npcp.Aliases_Slice(p_arr_aliases, idx_from, idx_to_ex)
endFunction

Alias[] function Get_Next_Aliases(int idx_in, int num_next)
    ; returns the next number of aliases, from low to high, including the idx_start

    if idx_in < 0
        idx_in = 0
    elseIf idx_in >= p_num_aliases
        idx_in = p_num_aliases - 1
    endIf

    if num_next > p_num_aliases
        num_next = p_num_aliases
    endIf

    int idx_aliases = idx_in

    p_Sort()

    Alias[] arr_copy = Utility.CreateAliasArray(num_next, none)
    int idx_copy = 0

    while idx_copy < num_next
        arr_copy[idx_copy] = p_arr_aliases[idx_aliases]

        idx_aliases += 1
        if idx_aliases >= p_num_aliases
            idx_aliases = 0
        endIf

        idx_copy += 1
    endWhile

    return arr_copy
endFunction

Alias[] function Get_Prev_Aliases(int idx_ex, int num_prev)
    ; returns the previous number of aliases, from low to high, excluding end

    if idx_ex < 0
        idx_ex = 0
    elseIf idx_ex > p_num_aliases
        idx_ex = p_num_aliases
    endIf

    if num_prev > p_num_aliases
        num_prev = p_num_aliases
    endIf

    int idx_aliases = idx_ex - num_prev
    if idx_aliases < 0
        idx_aliases = idx_aliases + p_num_aliases
    endIf

    p_Sort()

    Alias[] arr_copy = Utility.CreateAliasArray(num_prev, none)
    int idx_copy = 0

    while idx_copy < num_prev
        arr_copy[idx_copy] = p_arr_aliases[idx_aliases]

        idx_aliases += 1
        if idx_aliases >= p_num_aliases
            idx_aliases = 0
        endIf

        idx_copy += 1
    endWhile

    return arr_copy
endFunction

; Update Methods
int                 p_num_used      =    -1
int                 p_num_actors    =    -1
int                 p_num_names     =    -1
int[]               p_arr_used      =  none
Form[]              p_arr_actors    =  none
string[]            p_arr_names     =  none
function u_0_9_0()
    ; these variables are no longer needed, and should be
    ; truncated to save space in the save file.
    p_num_used = -1
    p_num_actors = -1
    p_num_names = -1
    p_arr_used = Utility.CreateIntArray(1, 0)
    p_arr_actors = Utility.CreateFormArray(1, none)
    p_arr_names = Utility.CreateStringArray(1, "")
endFunction
