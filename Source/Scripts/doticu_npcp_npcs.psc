;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

; we can do a lookup of the base/face of a potential member, to see if we already have them

Scriptname doticu_npcp_npcs extends Quest

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
doticu_npcp_vectors property VECTORS hidden
    doticu_npcp_vectors function Get()
        return p_DATA.MODS.FUNCS.VECTORS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_outfits property OUTFITS hidden
    doticu_npcp_outfits function Get()
        return p_DATA.MODS.FUNCS.OUTFITS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA              =  none

; Private Variable
bool                    p_is_created        = false
bool                    p_is_locked         = false
doticu_npcp_vector_form p_vec_bases         =  none; the real base of a npc, our key
doticu_npcp_vector_form p_vec_locks         =  none; for parallel processing
doticu_npcp_vector_form p_vec_vec_origs     =  none; vecs of original members
doticu_npcp_vector_form p_vec_vec_clones    =  none; vecs of cloned npcs, members or not
doticu_npcp_vector_form p_vec_caches_def    =  none; caches of extra default stuff
doticu_npcp_vector_form p_vec_outfits_def   =  none; default vanilla outfits
doticu_npcp_vector_form p_vec_outfits_curr  =  none; current vanilla outfits which can be modified

doticu_npcp_vector_form p_vec_outfits_pool  =  none; a pool of current vanilla outfits not in use (not a part of the system)

; to be deleted in a future release
doticu_npcp_vector_form p_vec_outfits       =  none; default vanilla outfits --> p_vec_outfits_def
doticu_npcp_vector_form p_vec_defaults      =  none; caches of extra default stuff --> p_vec_caches_def

; Friend Methods
function f_Create(doticu_npcp_data DATA, int init_max = 8)
    p_DATA = DATA

    p_is_created = true
    p_is_locked = false
    p_vec_bases = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_locks = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_vec_origs = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_vec_clones = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_caches_def = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_outfits_def = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_outfits_curr = VECTORS.Create_Form_Vector(init_max, none, 1.5)

    p_Create_Outfits_Pool()
endFunction

function f_Destroy()
    p_Destroy_Outfits_Pool()
    VECTORS.Destroy_Form_Vector(p_vec_outfits_curr)
    VECTORS.Destroy_Form_Vector(p_vec_outfits_def)
    p_Destroy_Default_Caches()
    p_Destroy_Clone_Vectors()
    p_Destroy_Original_Vectors()
    VECTORS.Destroy_Form_Vector(p_vec_locks)
    VECTORS.Destroy_Form_Vector(p_vec_bases)

    p_vec_outfits_pool = none
    p_vec_outfits_curr = none
    p_vec_outfits_def = none
    p_vec_caches_def = none
    p_vec_vec_clones = none
    p_vec_vec_origs = none
    p_vec_locks = none
    p_vec_bases = none
    p_is_locked = false
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

; Private Methods
function p_Lock()
    while p_is_locked
        Utility.Wait(0.01)
    endWhile
    p_is_locked = true
endFunction

function p_Unlock()
    p_is_locked = false
endFunction

bool function p_Unlock_Pass_Bool(bool val)
    p_Unlock()
    return val
endFunction

Form[] function p_Unlock_Pass_Form_Array(Form[] val)
    p_Unlock()
    return val
endFunction

Outfit function p_Unlock_Pass_Outfit(Outfit val)
    p_Unlock()
    return val
endFunction

ObjectReference function p_Unlock_Pass_Object_Ref(ObjectReference val)
    p_Unlock()
    return val
endFunction

function p_Destroy_Original_Vectors()
    ; it doesn't hurt to make sure each vector is deleted.
    int idx_vec_vecs = p_vec_vec_origs.num
    doticu_npcp_vector_form vec_origs
    while idx_vec_vecs > 0
        idx_vec_vecs -= 1
        vec_origs = p_vec_vec_origs.At(idx_vec_vecs) as doticu_npcp_vector_form
        VECTORS.Destroy_Form_Vector(vec_origs)
    endWhile

    VECTORS.Destroy_Form_Vector(p_vec_vec_origs)
endFunction

function p_Destroy_Clone_Vectors()
    ; it doesn't hurt to make sure each vector is deleted.
    int idx_vec_vecs = p_vec_vec_clones.num
    doticu_npcp_vector_form vec_clones
    while idx_vec_vecs > 0
        idx_vec_vecs -= 1
        vec_clones = p_vec_vec_clones.At(idx_vec_vecs) as doticu_npcp_vector_form
        VECTORS.Destroy_Form_Vector(vec_clones)
    endWhile

    VECTORS.Destroy_Form_Vector(p_vec_vec_clones)
endFunction

function p_Destroy_Default_Caches()
    ; it doesn't hurt to make sure the each cache is deleted.
    int idx_caches_def = p_vec_caches_def.num
    ObjectReference ref_cache_def
    while idx_caches_def > 0
        idx_caches_def -= 1
        ref_cache_def = p_vec_caches_def.At(idx_caches_def) as ObjectReference
        ref_cache_def.Disable()
        ref_cache_def.Delete()
    endWhile

    VECTORS.Destroy_Form_Vector(p_vec_caches_def)
endFunction

function p_Create_Outfits_Pool()
    ; so every base actor in the system gets an outfit. this means that
    ; most of them will not be used at one time. if we remove the curr
    ; outfit from an unmembered clone, then we should be guarenteed to
    ; always have enough for actual members. It's an edge case as most
    ; of these will probably not be used. however it needs to be minded
    Formlist formlist_outfits_member = CONSTS.FORMLIST_OUTFITS_MEMBER
    p_vec_outfits_pool = VECTORS.Create_Form_Vector(512, none, 1.0)

    int idx_formlist = formlist_outfits_member.GetSize()
    Outfit outfit_pool
    while idx_formlist > 0
        idx_formlist -= 1
        outfit_pool = formlist_outfits_member.GetAt(idx_formlist) as Outfit
        p_vec_outfits_pool.Push(outfit_pool as Form)
    endWhile
endFunction

function p_Destroy_Outfits_Pool()
    ; we go ahead and revert all leveleditems in outfits_member
    Formlist formlist_outfits_member = CONSTS.FORMLIST_OUTFITS_MEMBER

    int idx_formlist = formlist_outfits_member.GetSize()
    Outfit outfit_pool
    while idx_formlist > 0
        idx_formlist -= 1
        outfit_pool = formlist_outfits_member.GetAt(idx_formlist) as Outfit
        (outfit_pool.GetNthPart(1) as LeveledItem).Revert()
    endWhile

    VECTORS.Destroy_Form_Vector(p_vec_outfits_pool)
endFunction

Outfit function p_Create_Current_Outfit(Outfit outfit_default)
    if !outfit_default
        return none
    endIf

    Outfit outfit_current = p_vec_outfits_pool.Pop() as Outfit
    if !outfit_current
        return none
    endIf

    p_Fill_Current_Outfit(outfit_current, outfit_default)

    return outfit_current
endFunction

function p_Destroy_Current_Outfit(Outfit outfit_current)
    if !outfit_current
        return
    endIf

    LeveledItem leveled_outfit = outfit_current.GetNthPart(1) as LeveledItem
    if !leveled_outfit
        return
    endIf

    leveled_outfit.Revert()

    p_vec_outfits_pool.Push(outfit_current)
endFunction

function p_Fill_Current_Outfit(Outfit outfit_current, Outfit outfit_vanilla)
    if !outfit_current || !outfit_vanilla
        return
    endIf

    LeveledItem leveled_outfit = outfit_current.GetNthPart(1) as LeveledItem
    if !leveled_outfit
        return
    endIf

    leveled_outfit.Revert()

    int idx_forms = outfit_vanilla.GetNumParts()
    Form form_item
    while idx_forms > 0
        idx_forms -= 1
        form_item = outfit_vanilla.GetNthPart(idx_forms)
        leveled_outfit.AddForm(form_item, 1, 1)
    endWhile
endFunction

function p_Set_Base_Outfit(int idx_bases, Outfit outfit_vanilla)
    if idx_bases < 0 || idx_bases >= p_vec_bases.num || !outfit_vanilla
        return
    endIf

    ; because we need to set the real base and any leveled bases, we just do all npcs under base
    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form

    int idx_origs = vec_origs.num
    while idx_origs > 0
        idx_origs -= 1
        ACTORS.Set_Base_Outfit(vec_origs.At(idx_origs) as Actor, outfit_vanilla)
    endWhile

    int idx_clones = vec_clones.num
    while idx_clones > 0
        idx_clones -= 1
        ACTORS.Set_Base_Outfit(vec_clones.At(idx_clones) as Actor, outfit_vanilla)
    endWhile
endFunction

bool function p_Has_Base(Actor ref_actor)
    return p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form) > -1
endFunction

bool function p_Has_Original(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        return (p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form).Has(ref_actor)
    else
        return false
    endIf
endFunction

bool function p_Has_Clone(Actor ref_clone)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_clone) as Form)
    if idx_bases > -1
        return (p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form).Has(ref_clone)
    else
        return false
    endIf
endFunction

bool function p_Is_Base_Locked(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        return (p_vec_locks.At(idx_bases) as Key) != none
    else
        return false
    endIf
endFunction

bool function p_Add_Base(Actor ref_actor, Outfit outfit_default)
    ; either the real base or the leveled base carries the outfit. we track the real base.
    ; the real base is used by unleveled npcs, and the dynamic leveled base by leveled npcs.
    ; so a template clone of a leveled becomes unleveled and no longer has the dynamic base.
    ; we set the outfit_current for a real base once and all dynamic bases individually.

    if !p_Has_Base(ref_actor)
        ; we accept only the real base, not the static or dynamic leveled base
        ActorBase base_actor = ACTORS.Get_Real_Base(ref_actor)

        ; this is useful for when a npc has default equipment not found in their vanilla outfit
        ObjectReference cache_default = OUTFITS.Get_Default_Cache(ref_actor, outfit_default)

        p_vec_bases.Push(base_actor as Form)
        p_vec_locks.Push(none); none means it's unlocked
        p_vec_vec_origs.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
        p_vec_vec_clones.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
        p_vec_caches_def.Push(cache_default as Form)
        p_vec_outfits_def.Push(outfit_default as Form)
        p_vec_outfits_curr.Push(none); this will be set when adding members
        return true
    else
        return false
    endIf
endFunction

bool function p_Remove_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        ; we need to make sure to return the outfit_current to the pool
        p_Destroy_Current_Outfit(p_vec_outfits_curr.At(idx_bases) as Outfit)
        
        ; we can't leave untracked actors with our custom vanilla outfits, because they are reused
        p_Set_Base_Outfit(idx_bases, p_vec_outfits_def.At(idx_bases) as Outfit)
        
        ; just in case the garbage collector doesn't feel like doing its job
        ObjectReference cache_default = p_vec_caches_def.At(idx_bases) as ObjectReference
        cache_default.Disable()
        cache_default.Delete()
        
        ; if it's not obvious, I don't trust the garbage collector
        VECTORS.Destroy_Form_Vector(p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form)
        VECTORS.Destroy_Form_Vector(p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form)
        
        p_vec_outfits_curr.Remove_At_Unstable(idx_bases)
        p_vec_outfits_def.Remove_At_Unstable(idx_bases)
        p_vec_caches_def.Remove_At_Unstable(idx_bases)
        p_vec_vec_clones.Remove_At_Unstable(idx_bases)
        p_vec_vec_origs.Remove_At_Unstable(idx_bases)
        p_vec_locks.Remove_At_Unstable(idx_bases)
        p_vec_bases.Remove_At_Unstable(idx_bases)
        return true
    else
        return false
    endIf
endFunction

function p_Try_Remove_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    doticu_npcp_vector_form vec_origs
    doticu_npcp_vector_form vec_clones

    if idx_bases > -1
        vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
        vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
        if vec_origs.num == 0 && vec_clones.num == 0
            p_Remove_Base(ref_actor)
        endIf
    endIf
endFunction

function p_Try_Create_Current_Outfit(int idx_bases)
    if idx_bases < 0 || idx_bases >= p_vec_bases.num
        return
    endIf

    if p_vec_outfits_curr.At(idx_bases) != none
        ; already created previously
        return
    endIf

    ; this allows us to utilitize our outfitting algorithm with any member tagged with this base in the system
    Outfit outfit_current = p_Create_Current_Outfit(p_vec_outfits_def.At(idx_bases) as Outfit)
    if outfit_current == none
        ; this should never be able to happen as long as we have as many outfits as there are members
        ; we make sure by using the try methods, that any outfit not used by a base is freed.
        ; that is to say, no loose clones get to use the outfit nor need to
        return
    endIf

    ; don't forget to actually set the current outfit on base
    p_vec_outfits_curr.Set(idx_bases, outfit_current)
endFunction

function p_Try_Destroy_Current_Outfit(int idx_bases)
    ; we need to try and free any base doesn't have a member so that the base can be reused.
    ; a base in the system can have free standing clones, which we continue to track, so we have to do this

    if idx_bases < 0 || idx_bases >= p_vec_bases.num
        return
    endIf

    ; if there are any originals in the system, it's because they are members, so we can't delete
    if (p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form).num > 0
        return
    endIf

    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    int idx_clones = vec_clones.num
    while idx_clones > 0
        idx_clones -= 1
        ; if there is a single member, we need to keep the current outfit on this base
        if MEMBERS.Has_Member(vec_clones.At(idx_clones) as Actor)
            return
        endIf
    endWhile

    ; at this point we can destroy, and we need to make sure we remove current from vec
    p_Destroy_Current_Outfit(p_vec_outfits_curr.At(idx_bases) as Outfit)
    p_vec_outfits_curr.Set(idx_bases, none)

    ; we should set the default for this base.
    p_Set_Base_Outfit(idx_bases, p_vec_outfits_def.At(idx_bases) as Outfit)
endFunction

bool function p_Add_Original(Actor ref_actor)
    Form form_base = ACTORS.Get_Real_Base(ref_actor) as Form
    Form form_ref = ref_actor as Form
    doticu_npcp_vector_form vec_origs
    doticu_npcp_vector_form vec_clones

    if !p_Has_Base(ref_actor)
        LOGS.Create_Error("NPCS.f_Add_Original() failed to find base")
        return false
    endIf

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Add_Original() failed to find base_actor")
        return false
    endIf

    vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("NPCS.f_Add_Original() failed to find vec_origs")
        return false
    endIf

    vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("NPCS.f_Add_Original() failed to find vec_clones")
        return false
    endIf

    ; a clone made in our system cannot be an original
    if !vec_origs.Has(form_ref) && !vec_clones.Has(form_ref)
        ; we dynamically allocate current outfits and need to make sure none are leaked
        p_Try_Create_Current_Outfit(idx_bases)

        ; it's better not to set it unless we have to. this will catch leveled npcs also
        Outfit outfit_current = p_vec_outfits_curr.At(idx_bases) as Outfit
        if ACTORS.Get_Base_Outfit(ref_actor) != outfit_current
            ACTORS.Set_Base_Outfit(ref_actor, outfit_current)
        endIf

        vec_origs.Push(form_ref)
        return true
    else
        return false
    endIf
endFunction

bool function p_Add_Clone(Actor ref_clone)
    Form form_base = ACTORS.Get_Real_Base(ref_clone) as Form
    Form form_ref = ref_clone as Form
    doticu_npcp_vector_form vec_clones
    doticu_npcp_vector_form vec_origs

    if !p_Has_Base(ref_clone)
        LOGS.Create_Error("NPCS.f_Add_Clone() failed to find base")
        return false
    endIf

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Add_Clone() failed to find base_actor")
        return false
    endIf

    vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("NPCS.f_Add_Clone() failed to find vec_clones")
        return false
    endIf

    vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("NPCS.f_Add_Clone() failed to find vec_origs")
        return false
    endIf

    ; just in case!
    if !vec_clones.Has(form_ref) && !vec_origs.Has(form_ref)
        ; we dynamically allocate current outfits and need to make sure none are leaked
        p_Try_Create_Current_Outfit(idx_bases)

        ; it's better not to set it unless we have to
        Outfit outfit_current = p_vec_outfits_curr.At(idx_bases) as Outfit
        if ACTORS.Get_Base_Outfit(ref_clone) != outfit_current
            ACTORS.Set_Base_Outfit(ref_clone, outfit_current)
        endIf

        vec_clones.Push(form_ref)
        return true
    else
        return false
    endIf
endFunction

bool function p_Remove_Original(Actor ref_actor)
    Form form_base = ACTORS.Get_Real_Base(ref_actor) as Form
    Form form_ref = ref_actor as Form
    doticu_npcp_vector_form vec_origs

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Remove_Original() failed to find base_actor")
        return false
    endIf

    vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("NPCS.f_Remove_Original() failed to find vec_origs")
        return false
    endIf

    int idx_origs = vec_origs.Find(form_ref)
    if idx_origs > -1
        ; we dynamically allocate current outfits and need to make sure none are leaked
        p_Try_Destroy_Current_Outfit(idx_bases)

        ; leveled actors have a different outfit base than what we store, so we can't unset it later
        if ACTORS.Is_Leveled(ref_actor)
            ACTORS.Set_Base_Outfit(ref_actor, p_vec_outfits_def.At(idx_bases) as Outfit)
        endIf

        vec_origs.Remove_At_Unstable(idx_origs)
        return true
    else
        return false
    endIf
endFunction

bool function p_Remove_Clone(Actor ref_clone)
    Form form_base = ACTORS.Get_Real_Base(ref_clone) as Form
    Form form_ref = ref_clone as Form
    doticu_npcp_vector_form vec_clones

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Remove_Clone() failed to find base_actor")
        return false
    endIf

    vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("NPCS.f_Remove_Clone() failed to find vec_clones")
        return false
    endIf

    int idx_clones = vec_clones.Find(form_ref)
    if idx_clones > -1
        ; we dynamically allocate current outfits and need to make sure none are leaked
        p_Try_Destroy_Current_Outfit(idx_bases)

        ; leveled actors have a different outfit base than what we store, so we can't unset it later
        if ACTORS.Is_Leveled(ref_clone)
            ACTORS.Set_Base_Outfit(ref_clone, p_vec_outfits_def.At(idx_bases) as Outfit)
        endIf

        vec_clones.Remove_At_Unstable(idx_clones)
        return true
    else
        return false
    endIf
endFunction

Actor function p_Clone(Actor ref_actor)
    CONSTS.MARKER_CLONER.MoveTo(ref_actor, 0.0, 0.0, 0.0)
    Actor ref_clone = ACTORS.Clone(ref_actor, CONSTS.MARKER_CLONER)
    CONSTS.MARKER_CLONER.MoveTo(CONSTS.MARKER_STORAGE)

    return ref_clone
endFunction

; Public Methods
bool function Exists()
p_Lock()
    return p_Unlock_Pass_Bool(p_is_created)
p_Unlock()
endFunction

bool function Register(Actor ref_actor)
    if !ref_actor
        return false
    endIf

    Outfit base_outfit = ACTORS.Get_Base_Outfit(ref_actor)
    if !base_outfit
        base_outfit = CONSTS.OUTFIT_EMPTY
    endIf

p_Lock()
    p_Add_Base(ref_actor, base_outfit)
    bool did_register = p_Add_Original(ref_actor)
p_Unlock()

    return did_register
endFunction

bool function Unregister(Actor ref_actor)
    if !ref_actor
        return false
    endIf

p_Lock()
    bool did_unregister = p_Remove_Original(ref_actor)
    p_Try_Remove_Base(ref_actor)
p_Unlock()

    return did_unregister
endFunction

Actor function Clone(Actor ref_actor)
    if !ref_actor
        return none
    endIf

    Actor ref_clone = p_Clone(ref_actor)
    if !ref_clone
        return none
    endIf

    ; we want the clone to get the leveled and not template outfit, so use ref_actor.
    ; if the ref is a member, getting default can assure we don't get the temp outfit
    Outfit outfit_base = Get_Default_Outfit(ref_actor)
    if !outfit_base
        outfit_base = ACTORS.Get_Base_Outfit(ref_actor)
    endIf
    if !outfit_base
        outfit_base = CONSTS.OUTFIT_EMPTY
    endIf

p_Lock()
    p_Add_Base(ref_clone, outfit_base)
    bool did_register = p_Add_Clone(ref_clone)
p_Unlock()

    ; I don't think this should ever happen, but just in case
    if !did_register
        ref_clone.Disable()
        ref_clone.Delete()
        return none
    endIf

    OUTFITS.Outfit_Clone(ref_clone, ref_actor)

    return ref_clone
endFunction

bool function Unclone(Actor ref_clone)
    if !ref_clone
        return false
    endIf

p_Lock()
    bool did_unregister = p_Remove_Clone(ref_clone)
    p_Try_Remove_Base(ref_clone)
p_Unlock()

    if did_unregister
        ; we don't remove a clone unless we also delete them and vice versa
        ref_clone.Disable()
        ref_clone.Delete()
    endIf

    return did_unregister
endFunction

bool function Has_Base(Actor ref_actor)
p_Lock()
    return p_Unlock_Pass_Bool(p_Has_Base(ref_actor))
p_Unlock()
endFunction

bool function Is_Original(Actor ref_actor)
p_Lock()
    return p_Unlock_Pass_Bool(ref_actor && p_Has_Original(ref_actor))
p_Unlock()
endFunction

bool function Is_Clone(Actor ref_actor)
p_Lock()
    return p_Unlock_Pass_Bool(ref_actor && p_Has_Clone(ref_actor))
p_Unlock()
endFunction

Form[] function Get_Originals(Actor ref_actor)
p_Lock()
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases < 0
        return p_Unlock_Pass_Form_Array(Utility.CreateFormArray(1, none))
    endIf

    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("NPCS.Get_Originals() failed to find vec_origs")
        return p_Unlock_Pass_Form_Array(Utility.CreateFormArray(1, none))
    endIf

    return p_Unlock_Pass_Form_Array(vec_origs.Get_Array())
p_Unlock()
endFunction

Form[] function Get_Clones(Actor ref_actor)
p_Lock()
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases < 0
        return p_Unlock_Pass_Form_Array(Utility.CreateFormArray(1, none))
    endIf

    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("NPCS.Get_Clones() failed to find vec_clones")
        return p_Unlock_Pass_Form_Array(Utility.CreateFormArray(1, none))
    endIf

    return p_Unlock_Pass_Form_Array(vec_clones.Get_Array())
p_Unlock()
endFunction

Outfit function Get_Default_Outfit(Actor ref_actor)
    Form form_base_actor = ACTORS.Get_Real_Base(ref_actor) as Form
p_Lock()
    int idx_bases = p_vec_bases.Find(form_base_actor)
    if idx_bases > -1
        return p_Unlock_Pass_Outfit(p_vec_outfits_def.At(idx_bases) as Outfit)
    else
        return p_Unlock_Pass_Outfit(none)
    endIf
p_Unlock()
endFunction

function Set_Default_Outfit(Actor ref_actor, Outfit val_outfit)
    Form form_base_actor = ACTORS.Get_Real_Base(ref_actor) as Form
p_Lock()
    int idx_bases = p_vec_bases.Find(form_base_actor)
    if idx_bases > -1
        p_vec_outfits_def.Set(idx_bases, val_outfit as Form)
    endIf
p_Unlock()
endFunction

Outfit function Get_Current_Outfit(Actor ref_actor)
    Form form_base = ACTORS.Get_Real_Base(ref_actor) as Form
p_Lock()
    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases > -1
        return p_Unlock_Pass_Outfit(p_vec_outfits_curr.At(idx_bases) as Outfit)
    else
        return p_Unlock_Pass_Outfit(none)
    endIf
p_Unlock()
endFunction

function Set_Current_Outfit(Actor ref_actor, Outfit outfit_vanilla)
    Form form_base = ACTORS.Get_Real_Base(ref_actor) as Form
p_Lock()
    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases > -1
        p_Fill_Current_Outfit(p_vec_outfits_curr.At(idx_bases) as Outfit, outfit_vanilla)
    endIf
p_Unlock()
endFunction

ObjectReference function Get_Default_Cache(Actor ref_actor)
    Form form_base_actor = ACTORS.Get_Real_Base(ref_actor) as Form
p_Lock()
    int idx_bases = p_vec_bases.Find(form_base_actor)
    if idx_bases > -1
        return p_Unlock_Pass_Object_Ref(p_vec_caches_def.At(idx_bases) as ObjectReference)
    else
        return p_Unlock_Pass_Object_Ref(none)
    endIf
p_Unlock()
endFunction

function Lock_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        while (p_vec_locks.At(idx_bases) as Key) != none
            Utility.Wait(0.01)
        endWhile
        p_vec_locks.Set(idx_bases, CONSTS.KEY_LOCK as Form)
    endIf
endFunction

function Unlock_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        p_vec_locks.Set(idx_bases, none)
    endIf
endFunction

; Update Methods
function u_0_8_0()
    ; 1. recreate system with more accurate bases
    ; 2. create a default cache for each base
    ; 3. create a current oufit for each base
    ; 4. remove any clones that leaked into originals
    ; 5. remove any non-member originals from the system
    ; 6. set the vanilla outfit for each member

; make sure there are no public calls to doticu_npcp_npcs while Locked
p_Lock()

    doticu_npcp_vector_form old_vec_bases       = p_vec_bases
    doticu_npcp_vector_form old_vec_outfits     = p_vec_outfits
    doticu_npcp_vector_form old_vec_vec_origs   = p_vec_vec_origs
    doticu_npcp_vector_form old_vec_vec_clones  = p_vec_vec_clones
    Form[]                  arr_bases           = p_vec_bases.Get_Array()
    Form[]                  arr_outfits         = p_vec_outfits.Get_Array()
    Form[]                  arr_vec_origs       = p_vec_vec_origs.Get_Array()
    Form[]                  arr_vec_clones      = p_vec_vec_clones.Get_Array()

    int                     idx_bases           = 0
    int                     num_bases           = p_vec_bases.num
    int                     idx_actors          = 0
    int                     num_actors          = 0

    ; we need to create new vectors to fill
    f_Create(p_DATA, old_vec_bases.max)

    LOGS.Print("initializing update...")
    idx_bases = 0
    while idx_bases < num_bases
        num_actors += (arr_vec_origs[idx_bases] as doticu_npcp_vector_form).num
        num_actors += (arr_vec_clones[idx_bases] as doticu_npcp_vector_form).num
        idx_bases += 1
    endWhile

    string str_message = "NPC Party: This update may take several minutes. "
    str_message += "Open the console to monitor progress!\n"
    str_message += "Estimate: " + ((num_actors / 35 + 1) as int) + " minutes."
    Debug.MessageBox(str_message)

    idx_bases = 0
    while idx_bases < num_bases
        Outfit base_outfit = arr_outfits[idx_bases] as Outfit
        if !base_outfit
            base_outfit = CONSTS.OUTFIT_EMPTY
        endIf

        doticu_npcp_vector_form vec_origs = arr_vec_origs[idx_bases] as doticu_npcp_vector_form
        Form[] arr_origs = vec_origs.Get_Array()
        int idx_origs = 0
        int num_origs = vec_origs.num
        while idx_origs < num_origs
            Actor orig_ref = arr_origs[idx_origs] as Actor
            doticu_npcp_member orig_member = MEMBERS.Get_Member(orig_ref)

            ; we now only keep originals that are members, because we no longer need originals to work around an engine bug
            if orig_member
                orig_member.Set_Vanilla_Outfit(base_outfit)

                ActorBase orig_base = ACTORS.Get_Real_Base(orig_ref)

                if !p_vec_bases.Has(orig_base as Form)
                    ; we are use a clone because it will get more accurate default items.
                    ; a disabled clone can still have their inventory checked and accouted for.
                    Actor orig_clone = ACTORS.Clone(orig_ref, CONSTS.ACTOR_PLAYER, false, true)
                    OUTFITS.Outfit_Vanilla(orig_clone, base_outfit)
                    p_Add_Base(orig_clone, base_outfit)
                    orig_clone.Delete()
                endIf

                ; we need to use ACTORS.Get_Base() because that's how we stored them previously
                int old_idx_bases_orig = old_vec_bases.Find(ACTORS.Get_Base(orig_ref) as Form)
                if old_idx_bases_orig > -1 && (old_vec_vec_clones.At(old_idx_bases_orig) as doticu_npcp_vector_form).Has(orig_ref)
                    ; we need to weed out any potential duplicate clones due to an oversight in the previous version
                    ; also p_Add_Clone will only add ref if it doesn't already have it, so no duplicates will be added below
                    p_Add_Clone(orig_ref)
                else
                    p_Add_Original(orig_ref)
                endIf
            endIf

            idx_actors += 1
            idx_origs += 1
        endWhile
        if num_origs > 0
            LOGS.Print(((idx_actors * 100 / num_actors) as int) + "%% updated...")
        endIf

        ; we always keep all clones so that we can track what clones were made with our mod
        doticu_npcp_vector_form vec_clones = arr_vec_clones[idx_bases] as doticu_npcp_vector_form
        Form[] arr_clones = vec_clones.Get_Array()
        int idx_clones = 0
        int num_clones = vec_clones.num
        while idx_clones < num_clones
            Actor clone_ref = arr_clones[idx_clones] as Actor
            ActorBase clone_base = ACTORS.Get_Real_Base(clone_ref)

            doticu_npcp_member clone_member = MEMBERS.Get_Member(clone_ref)
            if clone_member
                clone_member.Set_Vanilla_Outfit(base_outfit)
            endIf

            if !p_vec_bases.Has(clone_base as Form)
                ; we are use a clone because it will get more accurate default items.
                ; a disabled clone can still have their inventory checked and accouted for.
                Actor clone_clone = ACTORS.Clone(clone_ref, CONSTS.ACTOR_PLAYER, false, true)
                OUTFITS.Outfit_Vanilla(clone_clone, base_outfit)
                p_Add_Base(clone_clone, base_outfit)
                clone_clone.Delete()
            endIf

            p_Add_Clone(clone_ref)

            idx_actors += 1
            idx_clones += 1
        endWhile
        if num_clones > 0
            LOGS.Print(((idx_actors * 100 / num_actors) as int) + "%% updated...")
        endIf

        idx_bases += 1
    endWhile

    LOGS.Print("finalizing update...")
    idx_bases = 0
    while idx_bases < num_bases
        VECTORS.Destroy_Form_Vector(arr_vec_origs[idx_bases] as doticu_npcp_vector_form)
        VECTORS.Destroy_Form_Vector(arr_vec_clones[idx_bases] as doticu_npcp_vector_form)
        idx_bases += 1
    endWhile
    VECTORS.Destroy_Form_Vector(old_vec_bases)
    VECTORS.Destroy_Form_Vector(old_vec_outfits)
    VECTORS.Destroy_Form_Vector(old_vec_vec_origs)
    VECTORS.Destroy_Form_Vector(old_vec_vec_clones)

    p_vec_outfits = none; --> p_vec_outfits_def
    p_vec_defaults = none; --> p_vec_caches_def

    LOGS.Print("completed update.")
    Debug.MessageBox("NPC Party: The update has been completed. You should save your game. Thank you for waiting!")

p_Unlock()
endFunction
