Scriptname doticu_npc_party_script_aliases extends Quest

; Private Constants
doticu_npc_party_script_consts  CONSTS      = none
doticu_npc_party_script_codes   CODES       = none
doticu_npc_party_script_vars    VARS        = none
doticu_npc_party_script_mods    MODS        = none
int                             MAX_ALIASES =   -1

; Private Variables
int     size_ids_used   =   -1
int     size_ids_free   =   -1
int[]   arr_ids_used    = none
int[]   arr_ids_free    = none

; Private Methods
int function p_Create_ID()
    if size_ids_free <= 0 || size_ids_used >= arr_ids_used.length
        return CODES.OUT_OF_SPACE
    endIf

    size_ids_free -= 1
    int id = arr_ids_free[size_ids_free]

    arr_ids_used[size_ids_used] = id
    size_ids_used += 1

    return id
endFunction

int function p_Destroy_ID(int id)
    if size_ids_free >= arr_ids_free.length
        ; all ids are free
        return CODES.FAILURE
    endIf

    int idx_id_used = arr_ids_used.RFind(id, size_ids_used - 1)
    if idx_id_used < 0
        ; id was not in use
        return CODES.FAILURE
    endIf

    size_ids_used -= 1
    if idx_id_used != size_ids_used
        ; id found was not last element, so defrag array
        arr_ids_used[idx_id_used] = arr_ids_used[size_ids_used]
    endIf
    arr_ids_used[size_ids_used] = -1
    
    arr_ids_free[size_ids_free] = id
    size_ids_free += 1

    return CODES.SUCCESS
endFunction

int function p_Get_ID(Actor ref_actor)
    ; it would be awesome to just pull this from a ref_actor value. "LastFlattered" might be a good one. make sure to check it, and use this as a fall back
    if !ref_actor
        return CODES.NO_ACTOR
    endIf

    ; id_alias > -1 && id_alias < MAX_ALIASES ; for when we check cached id on ref_actor

    int idx_ids_used = 0
    int idx_alias
    ReferenceAlias ref_alias
    while idx_ids_used < size_ids_used
        idx_alias = arr_ids_used[idx_ids_used]
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        if !ref_alias
            ; something must be wrong with our code
            return CODES.FATAL_ERROR
        endIf
        if ref_alias.GetActorReference() == ref_actor
            return idx_alias
        endIf
        idx_ids_used += 1
    endWhile

    return CODES.NO_MEMBER
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    MAX_ALIASES = GetNumAliases()

    size_ids_used = 0
    size_ids_free = MAX_ALIASES
    arr_ids_used = Utility.CreateIntArray(MAX_ALIASES, -1)
    arr_ids_free = Utility.CreateIntArray(MAX_ALIASES, -1)
    
    int idx_ids_free = 0
    int val_ids_free = MAX_ALIASES - 1
    while idx_ids_free < MAX_ALIASES
        arr_ids_free[idx_ids_free] = val_ids_free
        idx_ids_free += 1
        val_ids_free -= 1
    endWhile
endFunction

; Public Methods
int function Create_Alias(Actor ref_actor)
    int code_return

    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    if Has_Alias(ref_actor)
        return CODES.IS_DUPLICATE
    endIf
    if Is_Full()
        return CODES.OUT_OF_SPACE
    endIf

    code_return = p_Create_ID()
    if code_return < 0
        return code_return
    endIf
    int id_alias = code_return

    ; need to add id_alias to ref_actor values. but we need to pass in the string...

    (GetNthAlias(id_alias) as ReferenceAlias).ForceRefTo(ref_actor)

    return CODES.SUCCESS
endFunction

int function Destroy_Alias(Actor ref_actor)
    int code_return

    code_return = p_Get_ID(ref_actor)
    if code_return < 0
        return code_return
    endIf
    int id_alias = code_return

    code_return = p_Destroy_ID(id_alias)
    if code_return < 0
        return code_return
    endIf

    (GetNthAlias(id_alias) as ReferenceAlias).Clear()

    ; need to remove id_alias from ref_actor values. but we need to pass in the string...

    return CODES.SUCCESS
endFunction

ReferenceAlias function Get_Alias(Actor ref_actor)
    int id_alias = p_Get_ID(ref_actor)
    if id_alias < 0
        return none
    else
        return GetNthAlias(id_alias) as ReferenceAlias
    endIf
endFunction

bool function Has_Alias(Actor ref_actor)
    return p_Get_ID(ref_actor) > -1
endFunction

bool function Is_Full()
    return size_ids_free <= 0
endFunction

int function Get_Count()
    return size_ids_used
endFunction

int function Get_Max()
    return MAX_ALIASES
endFunction
