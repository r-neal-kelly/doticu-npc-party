Scriptname doticu_npcp_aliases extends Quest

; Private Constants
doticu_npcp_codes   p_CODES         = none

int                 p_MAX_ALIASES   =   -1

; Private Variables
int                 p_size_ids_used =   -1
int                 p_size_ids_free =   -1
int[]               p_arr_ids_used  = none
int[]               p_arr_ids_free  = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_CODES = DATA.CODES

    p_MAX_ALIASES = GetNumAliases()

    p_Create_ID_Arrays()
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

int function p_Create_ID()
    if p_size_ids_free <= 0 || p_size_ids_used >= p_arr_ids_used.length
        ; no ids are free
        return p_CODES.FAILURE
    endIf

    p_size_ids_free -= 1
    int id = p_arr_ids_free[p_size_ids_free]

    p_arr_ids_used[p_size_ids_used] = id
    p_size_ids_used += 1

    return id
endFunction

int function p_Destroy_ID(int id)
    if p_size_ids_free >= p_arr_ids_free.length
        ; all ids are free
        return p_CODES.FAILURE
    endIf

    int idx_id_used = p_arr_ids_used.RFind(id, p_size_ids_used - 1)
    if idx_id_used < 0
        ; id was not in use
        return p_CODES.FAILURE
    endIf

    p_size_ids_used -= 1
    if idx_id_used != p_size_ids_used
        ; id found was not last element, so defrag array
        p_arr_ids_used[idx_id_used] = p_arr_ids_used[p_size_ids_used]
    endIf
    p_arr_ids_used[p_size_ids_used] = -1
    
    p_arr_ids_free[p_size_ids_free] = id
    p_size_ids_free += 1

    if p_size_ids_used < 1
        p_Create_ID_Arrays(); this may be temp
    endIf

    return p_CODES.SUCCESS
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

function p_Sort_IDs_Used()
    ; this can be checked against a private bool to see
    ; if p_arr_ids_used is dirty, which it is whenever
    ; a new member is added. This would be called
    ; everytime before using Get_Aliases(), so it should
    ; be in that func or in an update after adding a member.
    ; there may be problems with syncronizing things in the
    ; latter, so need to read up on papyrus multi-threading.
    ; either way, this func will completely replace
    ; p_arr_ids_used with an entirely new array if dirty

    ; it may sort the arr using one of two algoritms:
    ; either papryusutil or an in house quicksort,
    ; which if we actually do the latter, it will be
    ; super slow in papyrus.
endFunction

; Public Methods
int function Create_Alias(Actor ref_actor)
    int code_return

    if !ref_actor
        return p_CODES.ISNT_ACTOR
    endIf
    if p_Has_Actor(ref_actor)
        return p_CODES.HAS_ACTOR
    endIf
    if Is_Full()
        return p_CODES.HASNT_SPACE
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
        return p_CODES.ISNT_ACTOR
    endIf
    if !Has_Alias(id_alias, ref_actor)
        return p_CODES.HASNT_ALIAS
    endIf

    f_Get_Alias(id_alias).Clear()

    code_return = p_Destroy_ID(id_alias)
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
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

Alias[] function Get_Aliases(int idx_from = 0, int idx_to_ex = -1)
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

Alias[] function Get_Aliases_Sorted(int idx_from = 0, int idx_to_ex = -1)
    p_Sort_IDs_Used()
    return Get_Aliases(idx_from, idx_to_ex)
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
