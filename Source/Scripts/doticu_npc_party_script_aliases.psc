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

ReferenceAlias function f_Get_Alias(int id_alias)
    if -1 < id_alias && id_alias < MAX_ALIASES
        return GetNthAlias(id_alias) as ReferenceAlias
    else
        return none
    endIf
endFunction

; Private Methods
int function p_Create_ID()
    if size_ids_free <= 0 || size_ids_used >= arr_ids_used.length
        ; no ids are free
        return CODES.FAILURE
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
    while idx_ids_used < size_ids_used
        idx_alias = arr_ids_used[idx_ids_used]
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

bool function Is_Full()
    return size_ids_free <= 0
endFunction

int function Get_Count()
    return size_ids_used
endFunction

int function Get_Max()
    return MAX_ALIASES
endFunction
