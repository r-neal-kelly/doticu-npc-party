Scriptname doticu_npcp_aliases extends Quest

; Modules
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none
int                 p_MAX_ALIASES   =    -1

; Private Variables
bool                p_is_created    = false
bool                p_should_sort   = false

int                 p_num_used      =    -1
int[]               p_arr_used      =  none

int                 p_num_free      =    -1
int[]               p_arr_free      =  none

int                 p_num_aliases   =    -1
Alias[]             p_arr_aliases   =  none

int                 p_num_actors    =    -1
Form[]              p_arr_actors    =  none

int                 p_num_names     =    -1
string[]            p_arr_names     =  none

; to be deleted.
int                 p_size_ids_used =    -1
int                 p_size_ids_free =    -1
int[]               p_arr_ids_used  =  none
int[]               p_arr_ids_free  =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA
    p_MAX_ALIASES = GetNumAliases()

    p_is_created = true

    p_Create_Arrays()
endFunction

function f_Destroy()
    p_Destroy_Arrays()

    p_is_created = false
endFunction

function f_Register()
endFunction

int function f_ID_To_Idx(int id_alias)
    if id_alias < 0 || id_alias >= p_MAX_ALIASES
        return -1
    endIf

    p_Sort(); this might be temp and we can make a func in here for Display Start

    int idx_id_alias = p_arr_used.Find(id_alias)

    if idx_id_alias > -1
        return idx_id_alias
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

ReferenceAlias function f_Get_Alias(int id_alias); can this be removed somehow?
    if -1 < id_alias && id_alias < p_MAX_ALIASES
        return GetNthAlias(id_alias) as ReferenceAlias
    else
        return none
    endIf
endFunction

; Private Methods
function p_Create_Arrays()
    p_num_used = 0
    p_arr_used = Utility.CreateIntArray(p_MAX_ALIASES, -1)

    p_num_free = p_MAX_ALIASES
    p_arr_free = Utility.CreateIntArray(p_MAX_ALIASES, -1)

    p_num_aliases = 0
    p_arr_aliases = Utility.CreateAliasArray(p_MAX_ALIASES, none)

    p_num_actors = 0
    p_arr_actors = Utility.CreateFormArray(p_MAX_ALIASES, none)

    p_num_names = 0
    p_arr_names = Utility.CreateStringArray(p_MAX_ALIASES, "")
    
    int idx_free = 0
    int idx_alias = p_MAX_ALIASES
    while idx_free < p_MAX_ALIASES
        idx_alias -= 1
        p_arr_free[idx_free] = idx_alias
        idx_free += 1
    endWhile
endFunction

function p_Destroy_Arrays()
    p_arr_names = none
    p_num_names = -1

    p_arr_actors = none
    p_num_actors = -1

    p_arr_aliases = none
    p_num_aliases = -1

    p_arr_free = none
    p_num_free = -1

    p_arr_used = none
    p_num_used = -1
endFunction

string function p_Stringify_ID(int id_alias, Actor ref_actor)
    string str_id_alias = id_alias as string
    int len_id_alias = StringUtil.GetLength(str_id_alias)

    if len_id_alias == 1
        str_id_alias = "000" + str_id_alias
    elseIf len_id_alias == 2
        str_id_alias = "00" + str_id_alias
    elseIf len_id_alias == 3
        str_id_alias = "0" + str_id_alias
    endIf

    return ref_actor.GetDisplayName() + str_id_alias
endFunction

int function p_Unstringify_ID(string str_id_alias)
    int len_id_alias = StringUtil.GetLength(str_id_alias)
    return StringUtil.Substring(str_id_alias, len_id_alias - 4, 4) as int
endFunction

int function p_Create_ID(Actor ref_actor)
    if p_num_free <= 0 || p_num_used >= p_MAX_ALIASES
        return CODES.HASNT_SPACE
    endIf

    p_num_free -= 1
    int id_alias = p_arr_free[p_num_free]

    p_arr_used[p_num_used] = id_alias
    p_num_used += 1

    p_arr_aliases[p_num_aliases] = GetNthAlias(id_alias)
    p_num_aliases += 1

    p_arr_actors[p_num_actors] = ref_actor
    p_num_actors += 1

    p_arr_names[p_num_names] = p_Stringify_ID(id_alias, ref_actor)
    p_num_names += 1

    return id_alias
endFunction

int function p_Destroy_ID(int id_alias)
    if p_num_free >= p_MAX_ALIASES
        return CODES.SUCCESS
    endIf

    int idx_id = p_arr_used.RFind(id_alias, p_num_used - 1)
    if idx_id < 0
        return CODES.HASNT_ID
    endIf

    p_num_used -= 1
    p_num_aliases -= 1
    p_num_actors -= 1
    p_num_names -= 1

    if idx_id != p_num_used
        ; idx_id was not last idx, so defrag arrays
        p_arr_used[idx_id] = p_arr_used[p_num_used]
        p_arr_aliases[idx_id] = p_arr_aliases[p_num_aliases]
        p_arr_actors[idx_id] = p_arr_actors[p_num_actors]
        p_arr_names[idx_id] = p_arr_names[p_num_names]
    endIf

    p_arr_used[p_num_used] = -1
    p_arr_aliases[p_num_aliases] = none
    p_arr_actors[p_num_actors] = none
    p_arr_names[p_num_names] = ""
    
    p_arr_free[p_num_free] = id_alias
    p_num_free += 1

    return CODES.SUCCESS
endFunction

function p_Sort()
    if !p_should_sort
        return
    endIf

    int idx_id = 0
    string str_id
    int id_alias
    Alias base_alias
    Actor ref_actor

    ; PapyrusUtil crashes if we send it a string array that has any "" in it
    ; else we could just sort p_arr_names directly and save some cycles
    string[] arr_names_copy = PapyrusUtil.SliceStringArray(p_arr_names, 0, p_num_names - 1)
    PapyrusUtil.SortStringArray(arr_names_copy)

    while idx_id < p_num_names
        str_id = arr_names_copy[idx_id]
        id_alias = p_Unstringify_ID(str_id); may need to inline
        base_alias = GetNthAlias(id_alias)
        ref_actor = (base_alias as ReferenceAlias).GetActorReference()

        p_arr_used[idx_id] = id_alias
        p_arr_aliases[idx_id] = base_alias
        p_arr_actors[idx_id] = ref_actor
        p_arr_names[idx_id] = str_id

        idx_id += 1
    endWhile

    p_should_sort = false
endFunction

bool function p_Has_Actor(Actor ref_actor)
    if ref_actor
        return p_arr_actors.Find(ref_actor as Form) > -1
    else
        return false
    endIf
endFunction

Actor function p_Get_Actor(int id_alias)
    int idx_id = f_ID_To_Idx(id_alias)
    if idx_id > -1
        return p_arr_actors[idx_id] as Actor
    else
        return none
    endIf
endFunction

ReferenceAlias function p_Get_Alias(int id_alias)
    int idx_id = f_ID_To_Idx(id_alias)
    if idx_id > -1
        return p_arr_aliases[idx_id] as ReferenceAlias
    else
        return none
    endIf
endFunction

; Public Methods
int function Create_Alias(Actor ref_actor)
    int code_return

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    if p_Has_Actor(ref_actor)
        return CODES.HAS_ACTOR
    endIf

    if Is_Full()
        return CODES.HASNT_SPACE
    endIf

    code_return = p_Create_ID(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_alias = code_return

    f_Get_Alias(id_alias).ForceRefTo(ref_actor)

    p_should_sort = true
    
    return id_alias
endFunction

int function Destroy_Alias(int id_alias, Actor ref_actor)
    int code_return

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    if !Has_Alias(id_alias, ref_actor)
        return CODES.HASNT_ALIAS
    endIf

    f_Get_Alias(id_alias).Clear()

    code_return = p_Destroy_ID(id_alias)
    if code_return < 0
        return code_return
    endIf

    p_should_sort = true

    return CODES.SUCCESS
endFunction

int function Update_Name(int id_alias)
    int idx_id = f_ID_To_Idx(id_alias)

    if idx_id < 0
        return CODES.HASNT_ID
    endIf

    p_arr_names[idx_id] = p_Stringify_ID(id_alias, p_arr_actors[idx_id] as Actor)

    p_should_sort = true

    return CODES.SUCCESS
endFunction

bool function Is_Full()
    return p_num_free <= 0
endFunction

int function Get_Count()
    return p_num_used
endFunction

int function Get_Max()
    return p_MAX_ALIASES
endFunction

bool function Has_Alias(int id_alias, Actor ref_actor)
    return ref_actor && p_Get_Actor(id_alias) == ref_actor
endFunction

ReferenceAlias function Get_Alias(int id_alias, Actor ref_actor)
    if Has_Alias(id_alias, ref_actor)
        return f_Get_Alias(id_alias)
    else
        return none
    endIf
endFunction

ReferenceAlias function Get_Next_Alias(int id_alias, Actor ref_actor)
    if !Has_Alias(id_alias, ref_actor)
        return none
    endIf

    p_Sort()

    int idx_alias_next = f_To_Relative_Idx(f_ID_To_Idx(id_alias) + 1)

    return p_arr_aliases[idx_alias_next] as ReferenceAlias
endFunction

ReferenceAlias function Get_Prev_Alias(int id_alias, Actor ref_actor)
    if !Has_Alias(id_alias, ref_actor)
        return none
    endIf

    p_Sort()

    int idx_alias_prev = f_To_Relative_Idx(f_ID_To_Idx(id_alias) - 1)

    return p_arr_aliases[idx_alias_prev] as ReferenceAlias
endFunction

Alias[] function Get_Aliases(int idx_from = 0, int idx_to_ex = -1)
    if idx_from < 0
        idx_from = 0
    endIf

    if idx_to_ex > p_num_aliases || idx_to_ex < 0
        idx_to_ex = p_num_aliases
    endIf

    if idx_to_ex - idx_from < 1
        return Utility.CreateAliasArray(0, none)
    endIf

    int idx_to_in = idx_to_ex - 1
    if idx_to_in < 0
        idx_to_in = 0
    endIf

    p_Sort()

    return PapyrusUtil.SliceAliasArray(p_arr_aliases, idx_from, idx_to_in)
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
function u_0_3_0()
    p_Create_Arrays()

    p_num_used = p_size_ids_used
    p_num_free = p_size_ids_free
    p_num_aliases = p_num_used
    p_num_actors = p_num_used
    p_num_names = p_num_used

    int idx_id
    int id_alias
    Alias base_alias
    Actor ref_actor

    idx_id = 0
    while idx_id < p_size_ids_used
        id_alias = p_arr_ids_used[idx_id]
        base_alias = GetNthAlias(id_alias)
        ref_actor = (base_alias as ReferenceAlias).GetActorReference()

        p_arr_used[idx_id] = id_alias
        p_arr_aliases[idx_id] = base_alias
        p_arr_actors[idx_id] = ref_actor
        p_arr_names[idx_id] = p_Stringify_ID(id_alias, ref_actor)

        idx_id += 1
    endWhile

    idx_id = 0
    while idx_id < p_size_ids_free
        p_arr_free[idx_id] = p_arr_ids_free[idx_id]

        idx_id += 1
    endWhile

    ;p_size_ids_used = -1
    ;p_arr_ids_used = none

    ;p_size_ids_free = -1
    ;p_arr_ids_free = none
endFunction

function u_0_4_0()
    ; backup old cache
    int max_aliases_old = p_MAX_ALIASES

    int num_used_old = p_num_used
    int[] arr_used_old = p_arr_used

    int num_free_old = p_num_free
    int[] arr_free_old = p_arr_free

    int num_aliases_old = p_num_aliases
    Alias[] arr_aliases_old = p_arr_aliases

    int num_actors_old = p_num_actors
    Form[] arr_actors_old = p_arr_actors

    int num_names_old = p_num_names
    string[] arr_names_old = p_arr_names

    ; re-init cache
    p_MAX_ALIASES = GetNumAliases()
    p_Create_Arrays()

    ; fill in the used arrays
    int idx_id = 0
    while idx_id < num_used_old
        p_arr_used[idx_id] = arr_used_old[idx_id]
        p_arr_aliases[idx_id] = arr_aliases_old[idx_id]
        p_arr_actors[idx_id] = arr_actors_old[idx_id]
        p_arr_names[idx_id] = arr_names_old[idx_id]
        idx_id += 1
    endWhile

    ; set correct nums
    p_num_used = num_used_old
    p_num_aliases = num_aliases_old
    p_num_actors = num_actors_old
    p_num_names = num_names_old

    ; because free array has ids backwards...
    p_num_free = p_MAX_ALIASES - max_aliases_old; the num of new aliases

    int idx_free_old = 0
    int idx_free_new = p_num_free
    while idx_free_old < arr_free_old.length
        p_arr_free[idx_free_new] = arr_free_old[idx_free_old]
        idx_free_old += 1
        idx_free_new += 1
    endWhile

    p_num_free += num_free_old
endFunction
