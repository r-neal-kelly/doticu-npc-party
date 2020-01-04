Scriptname doticu_npcp_aliases extends Quest

; Modules
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty

; Public Constants
int property MAX_ALIASES hidden
    int function Get()
        return GetNumAliases()
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none
int                 p_MAX_ALIASES   =    -1

; Private Variables
bool                p_is_created    = false
int                 p_size_ids_used =    -1
int                 p_size_ids_free =    -1
int[]               p_arr_ids_used  =  none
int[]               p_arr_ids_free  =  none
bool                p_is_used_dirty = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA
    p_MAX_ALIASES = GetNumAliases()

    p_is_created = true
    p_Create_ID_Arrays()
endFunction

function f_Destroy()
    p_Destroy_ID_Arrays()
    p_is_created = false
endFunction

function f_Register()
endFunction

ReferenceAlias function f_Get_Alias(int id_alias)
    if -1 < id_alias && id_alias < p_MAX_ALIASES
        return GetNthAlias(id_alias) as ReferenceAlias
    else
        return none
    endIf
endFunction

; Private Methods
function p_Create_ID_Arrays()
    p_size_ids_used = 0
    p_size_ids_free = p_MAX_ALIASES
    p_arr_ids_used = Utility.CreateIntArray(p_MAX_ALIASES, -1)
    p_arr_ids_free = Utility.CreateIntArray(p_MAX_ALIASES, -1)
    
    int idx_ids_free = 0
    int val_ids_free = p_MAX_ALIASES - 1
    while idx_ids_free < p_MAX_ALIASES
        p_arr_ids_free[idx_ids_free] = val_ids_free
        idx_ids_free += 1
        val_ids_free -= 1
    endWhile
endFunction

function p_Destroy_ID_Arrays()
    p_arr_ids_free = none
    p_arr_ids_used = none
    p_size_ids_free = -1
    p_size_ids_used = -1
endFunction

int function p_Create_ID()
    if p_size_ids_free <= 0 || p_size_ids_used >= p_arr_ids_used.length
        ; no ids are free
        return CODES.HASNT_SPACE
    endIf

    p_size_ids_free -= 1
    int id = p_arr_ids_free[p_size_ids_free]

    p_arr_ids_used[p_size_ids_used] = id
    p_size_ids_used += 1

    p_is_used_dirty = true

    return id
endFunction

int function p_Destroy_ID(int id)
    if p_size_ids_free >= p_arr_ids_free.length
        ; all ids are free
        return CODES.SUCCESS
    endIf

    int idx_id_used = p_arr_ids_used.RFind(id, p_size_ids_used - 1)
    if idx_id_used < 0
        ; id was not in use
        return CODES.HASNT_ID
    endIf

    p_size_ids_used -= 1
    if idx_id_used != p_size_ids_used
        ; id found was not last element, so defrag array
        p_arr_ids_used[idx_id_used] = p_arr_ids_used[p_size_ids_used]
        p_is_used_dirty = true
    endIf
    p_arr_ids_used[p_size_ids_used] = -1
    
    p_arr_ids_free[p_size_ids_free] = id
    p_size_ids_free += 1

    if p_size_ids_used < 1; this may be temp
        p_Create_ID_Arrays()
        p_is_used_dirty = false
    endIf

    return CODES.SUCCESS
endFunction

function p_Sort_Used(bool do_force = false)
    if !do_force && !p_is_used_dirty
        ; already sorted
        return
    endIf

    ; we should do the sorting in another thread, but only one thread.
    
    string[] arr_names = p_Get_Used_Names_IDs(); we could use an if chain with sorting algorithm
    int [] arr_ids = Utility.CreateIntArray(p_MAX_ALIASES, -1)
    string str_name
    int len_str_name
    int idx_alias

    PapyrusUtil.SortStringArray(arr_names)

    int idx_names = 0
    while idx_names < arr_names.length
        str_name = arr_names[idx_names]
        len_str_name = StringUtil.GetLength(str_name)
        idx_alias = StringUtil.Substring(str_name, len_str_name - 3, 3) as int

        arr_ids[idx_names] = idx_alias

        idx_names += 1
    endWhile

    p_arr_ids_used = arr_ids
    p_is_used_dirty = false
endFunction

string[] function p_Get_Used_Names_IDs()
    string[] arr_names = Utility.CreateStringArray(p_size_ids_used, "")
    int idx_alias
    string str_idx
    int len_str_idx
    Actor ref_actor

    int idx_used = 0
    while idx_used < p_size_ids_used
        idx_alias = p_arr_ids_used[idx_used]
        str_idx = idx_alias as string
        len_str_idx = StringUtil.GetLength(str_idx)

        if len_str_idx == 1
            str_idx = "00" + str_idx
        elseIf len_str_idx == 2
            str_idx = "0" + str_idx
        endIf

        ref_actor = (GetNthAlias(idx_alias) as ReferenceAlias).GetActorReference()
        arr_names[idx_used] = ref_actor.GetDisplayName() + str_idx

        idx_used += 1
    endWhile

    return arr_names
endFunction

Actor function p_Get_Actor(int id_alias)
    ReferenceAlias ref_alias = f_Get_Alias(id_alias)
    if !ref_alias
        return none
    else
        return ref_alias.GetActorReference()
    endIf
endFunction

bool function p_Has_Actor(Actor ref_actor)
    if !ref_actor
        return false
    endIf

    int idx_ids_used = 0
    int idx_alias
    ReferenceAlias ref_alias
    while idx_ids_used < p_size_ids_used
        idx_alias = p_arr_ids_used[idx_ids_used]
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        if ref_alias && ref_alias.GetActorReference() == ref_actor
            return true
        endIf
        idx_ids_used += 1
    endWhile

    return false
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

    code_return = p_Create_ID()
    if code_return < 0
        return code_return
    endIf
    int id_alias = code_return

    f_Get_Alias(id_alias).ForceRefTo(ref_actor)

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

    return CODES.SUCCESS
endFunction

bool function Has_Alias(int id_alias, Actor ref_actor)
    return ref_actor != none && p_Get_Actor(id_alias) == ref_actor
endFunction

ReferenceAlias function Get_Alias(int id_alias, Actor ref_actor)
    if Has_Alias(id_alias, ref_actor)
        return f_Get_Alias(id_alias)
    else
        return none
    endIf
endFunction

Alias[] function Get_Used(int idx_from = 0, int idx_to_ex = -1)
    if idx_from < 0
        idx_from = 0
    endIf
    if idx_to_ex > p_size_ids_used || idx_to_ex < 0
        idx_to_ex = p_size_ids_used
    endIf
    int size_arr_aliases = idx_to_ex - idx_from
    if size_arr_aliases <= 0
        return Utility.CreateAliasArray(0, none)
    endIf

    ; should probably used PapyrusUtil's funcs to copy, it's native and thus faster

    Alias[] arr_aliases = Utility.CreateAliasArray(size_arr_aliases, none)
    
    int idx_orig = idx_from
    int idx_copy = 0
    while idx_orig < idx_to_ex
        arr_aliases[idx_copy] = GetNthAlias(p_arr_ids_used[idx_orig])
        idx_orig += 1
        idx_copy += 1
    endWhile

    return arr_aliases
endFunction

Alias[] function Get_Used_Sorted(int idx_from = 0, int idx_to_ex = -1)
    p_Sort_Used(false)
    return Get_Used(idx_from, idx_to_ex)
endFunction

function Sort_Used()
    ; the idea here is that the user of the aliases knows better when to sort than this module does
    ; we could pass an alogrithm argument.
    ; also, we could just set the flag as dirty
    p_Sort_Used(true)
endFunction

bool function Is_Full()
    return p_size_ids_free <= 0
endFunction

int function Get_Count()
    return p_size_ids_used
endFunction

int function Get_Max()
    return p_MAX_ALIASES
endFunction

state p_STATE_BUSY
    ; I think we will need to protect operations like sorting, just in case
endState
