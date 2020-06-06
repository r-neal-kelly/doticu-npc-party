;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_npcs extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
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
doticu_npcp_vector_form p_vec_outfits_def   =  none; default vanilla outfits

; Friend Methods
function f_Create(doticu_npcp_data DATA, int init_max = 8)
    p_DATA = DATA

    p_is_created = true
    p_is_locked = false
    p_vec_bases = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_locks = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_vec_origs = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_vec_clones = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_outfits_def = VECTORS.Create_Form_Vector(init_max, none, 1.5)
endFunction

function f_Destroy()
    VECTORS.Destroy_Form_Vector(p_vec_outfits_def)
    p_Destroy_NPC_Vectors()
    VECTORS.Destroy_Form_Vector(p_vec_locks)
    VECTORS.Destroy_Form_Vector(p_vec_bases)

    p_vec_outfits_def = none
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

function p_Destroy_NPC_Vectors()
    ; it doesn't hurt to make sure each vector is deleted
    int idx_bases = p_vec_bases.num
    doticu_npcp_vector_form vec_origs
    doticu_npcp_vector_form vec_clones
    while idx_bases > 0
        idx_bases -= 1
        vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
        vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
        if vec_origs
            VECTORS.Destroy_Form_Vector(vec_origs)
        endIf
        if vec_clones
            VECTORS.Destroy_Form_Vector(vec_clones)
        endIf
    endWhile

    VECTORS.Destroy_Form_Vector(p_vec_vec_origs)
    VECTORS.Destroy_Form_Vector(p_vec_vec_clones)
endFunction

bool function p_Has_Base(Actor ref_actor)
    return p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form) > -1
endFunction

bool function p_Has_Original(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
        if vec_origs
            return vec_origs.Has(ref_actor as Form)
        else
            return false
        endIf
    else
        return false
    endIf
endFunction

bool function p_Has_Clone(Actor ref_clone)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_clone) as Form)
    if idx_bases > -1
        doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
        if vec_clones
            return vec_clones.Has(ref_clone as Form)
        else
            return false
        endIf
    else
        return false
    endIf
endFunction

bool function p_Add_Base(Actor ref_actor, Outfit outfit_default)
    ; either the real base or the leveled base carries the outfit. we track the real base.
    ; the real base is used by unleveled npcs, and the dynamic leveled base by leveled npcs.
    ; so a template clone of a leveled becomes unleveled and no longer has the dynamic base.

    if !p_Has_Base(ref_actor)
        ; we accept only the real base, not the static or dynamic leveled base
        ActorBase base_actor = ACTORS.Get_Real_Base(ref_actor)

        ; we use an SKSE plugin to avoid triggering a horrible bug that happens when an npc is
        ; outfitted with a new outfit form that contains any of the same items in the previous
        ; outfit form. It can go unnoticed when there are no clones of the npc, but if there
        ; are clones it becomes readily apparent there is a problem, because other refs of the same
        ; base become naked. both of my favorite outfitting mods also contain this bug, and there
        ; is no good work-around in Papyrus alone. So we modify the default outfit to achieve
        ; our algorithm.
        doticu_npcp.Outfit_Add_Item(outfit_default, CONSTS.ARMOR_BLANK as Form)

        p_vec_bases.Push(base_actor as Form)
        p_vec_locks.Push(none); none means it's unlocked
        p_vec_vec_origs.Push(none); set when adding original
        p_vec_vec_clones.Push(none); set when adding clone
        p_vec_outfits_def.Push(outfit_default as Form)
        return true
    else
        return false
    endIf
endFunction

function p_Remove_Base(int idx_bases)
    if idx_bases < 0 || idx_bases >= p_vec_bases.num
        return
    endIf

    ; we should remove our token item from the outfit so that it goes back to vanilla.
    ; even if another base is using this outfit, it it readded each time a reference is outfitted
    Outfit outfit_default = p_vec_outfits_def.At(idx_bases) as Outfit
    doticu_npcp.Outfit_Remove_Item(outfit_default, CONSTS.ARMOR_BLANK as Form)
    
    ; help the garbage collecter
    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if vec_clones
        VECTORS.Destroy_Form_Vector(vec_clones)
    endIf
    if vec_origs
        VECTORS.Destroy_Form_Vector(vec_origs)
    endIf
    
    p_vec_outfits_def.Remove_At_Unstable(idx_bases)
    p_vec_vec_clones.Remove_At_Unstable(idx_bases)
    p_vec_vec_origs.Remove_At_Unstable(idx_bases)
    p_vec_locks.Remove_At_Unstable(idx_bases)
    p_vec_bases.Remove_At_Unstable(idx_bases)

    return
endFunction

function p_Try_Remove_Base(int idx_bases)
    if idx_bases < 0 || idx_bases >= p_vec_bases.num
        return
    endIf

    ; we can only remove if the base exists and there isn't a single actor in origs or clones
    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if (!vec_origs || vec_origs.num == 0) && (!vec_clones || vec_clones.num == 0)
        p_Remove_Base(idx_bases)
    endIf
endFunction

bool function p_Add_Original(Actor ref_actor)
    Form form_actor = ref_actor as Form

    ; base must be added outside this function, because it requires more args than we have here
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Add_Original() failed to find base")
        return false; can't register
    endIf

    ; a clone made by us cannot be an original, and we keep them in the system when unregistered
    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if vec_clones && vec_clones.Has(form_actor)
        return true; already registered as clone
    endIf

    ; we dynamically create vec_origs, so make sure it exists
    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        vec_origs = VECTORS.Create_Form_Vector(1, none, 1.5)
        p_vec_vec_origs.Set(idx_bases, vec_origs as Form)
    endIf

    ; we never allow duplicates
    if !vec_origs.Has(form_actor)
        vec_origs.Push(form_actor)

        return true; now registered
    else
        return true; already registered
    endIf
endFunction

bool function p_Add_Clone(Actor ref_clone)
    Form form_clone = ref_clone as Form
    
    ; base must be added outside this function, because it requires more args than we have here
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_clone) as Form)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Add_Clone() failed to find base")
        return false; can't register
    endIf

    ; a clone made in our system cannot be an original. this should never happen, but just in case
    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if vec_origs && vec_origs.Has(form_clone)
        return true; registered as original
    endIf

    ; we dynamically create vec_clones, so make sure it exists
    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        vec_clones = VECTORS.Create_Form_Vector(1, none, 1.5)
        p_vec_vec_clones.Set(idx_bases, vec_clones as Form)
    endIf

    ; we never allow duplicates
    if !vec_clones.Has(form_clone)
        vec_clones.Push(form_clone)

        return true; now registered
    else
        return false; already registered
    endIf
endFunction

bool function p_Unregister(Actor ref_actor)
    Form form_actor = ref_actor as Form

    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Remove_Original() failed to find base_actor")
        return false; could not unregister
    endIf

    ; it is possible that a clone will be passed as ref_actor. but we cannot remove them
    ; because they are not being uncloned. we will keep track of all clones that we make
    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if vec_clones && vec_clones.Has(form_actor)
        return true; unregistered clone
    endIf

    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("NPCS.f_Remove_Original() failed to find vec_origs")
        return false; no originals to unregister
    endIf

    int idx_origs = vec_origs.Find(form_actor)
    if idx_origs > -1
        vec_origs.Remove_At_Unstable(idx_origs)

        ; we dynamically allocate vectors, so we need to try and free
        if vec_origs.num < 1
            VECTORS.Destroy_Form_Vector(vec_origs)
            p_vec_vec_origs.Set(idx_bases, none)
        endIf

        ; no reason to keep it around if it's not being used
        p_Try_Remove_Base(idx_bases)

        return true; now unregistered
    else
        return true; already unregistered
    endIf
endFunction

bool function p_Unclone(Actor ref_clone)
    Form form_clone = ref_clone as Form

    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_clone) as Form)
    if idx_bases < 0
        LOGS.Create_Error("NPCS.f_Remove_Clone() failed to find base_actor")
        return false; could not unclone
    endIf

    ; this should never happen, but just in case, we don't unregister, and just return
    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if vec_origs && vec_origs.Has(form_clone)
        return false; did not unclone original
    endIf

    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("NPCS.f_Remove_Clone() failed to find vec_clones")
        return false; no clones to unclone
    endIf

    int idx_clones = vec_clones.Find(form_clone)
    if idx_clones > -1
        ; we don't remove a clone unless we also delete them and vice versa
        vec_clones.Remove_At_Unstable(idx_clones)
        ref_clone.Disable()
        ref_clone.Delete()

        ; we dynamically allocate vectors, so we need to try and free
        if vec_clones.num < 1
            VECTORS.Destroy_Form_Vector(vec_clones)
            p_vec_vec_clones.Set(idx_bases, none)
        endIf

        ; no reason to keep it around if it's not being used
        p_Try_Remove_Base(idx_bases)

        return true; now uncloned
    else
        return false; not registered as a clone, could not unclone
    endIf
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

    ; it may be excessive to check default first, but just in case
    Outfit outfit_base = Get_Default_Outfit(ref_actor)
    if !outfit_base
        outfit_base = ACTORS.Get_Base_Outfit(ref_actor)
    endIf
    if !outfit_base
        outfit_base = CONSTS.OUTFIT_EMPTY
    endIf

p_Lock()
    ; will only add base if it doesn't exist in system
    p_Add_Base(ref_actor, outfit_base)

    bool did_register = p_Add_Original(ref_actor)
p_Unlock()

    return did_register
endFunction

Actor function Clone(Actor ref_actor)
    if !ref_actor
        return none
    endIf

    ; if their ai is disabled, it's probable that moving the marker too close to them
    ; will cause them to move, and that may be unwanted if they are paralyzed and positioned.
    if ref_actor.IsAIEnabled() && ACTORS.Is_Near_Player(ref_actor, 1024)
        CONSTS.MARKER_CLONER.MoveTo(ref_actor, 0.0, 0.0, 0.0)
    else
        CONSTS.MARKER_CLONER.MoveTo(CONSTS.ACTOR_PLAYER, 0.0, 0.0, 0.0)
    endIf

    Actor ref_clone = ACTORS.Clone(ref_actor, CONSTS.MARKER_CLONER)
    CONSTS.MARKER_CLONER.MoveTo(CONSTS.MARKER_STORAGE)
    if !ref_clone
        return none
    endIf

    ; we want the clone to get the leveled and not template outfit, so use ref_actor.
    ; if the ref is a member, getting default can ensure we don't get the temp outfit
    Outfit outfit_base = Get_Default_Outfit(ref_actor)
    if !outfit_base
        outfit_base = ACTORS.Get_Base_Outfit(ref_actor)
    endIf
    if !outfit_base
        outfit_base = CONSTS.OUTFIT_EMPTY
    endIf

p_Lock()
    ; will only add base if it doesn't exist in system
    p_Add_Base(ref_clone, outfit_base)

    bool did_register = p_Add_Clone(ref_clone)
p_Unlock()

    ; I don't think this should ever happen under normal circumstances, but just in case
    if !did_register
        ref_clone.Disable()
        ref_clone.Delete()
        return none
    endIf

    OUTFITS.Outfit_Clone(ref_clone, ref_actor)

    return ref_clone
endFunction

bool function Unregister(Actor ref_actor)
    if !ref_actor
        return false
    endIf

    ; not sure if this is the best place
    Outfit outfit_base = Get_Default_Outfit(ref_actor)
    ref_actor.SetOutfit(outfit_base)

p_Lock()
    return p_Unlock_Pass_Bool(p_Unregister(ref_actor))
p_Unlock()
endFunction

bool function Unclone(Actor ref_clone)
    if !ref_clone
        return false
    endIf

p_Lock()
    return p_Unlock_Pass_Bool(p_Unclone(ref_clone))
p_Unlock()
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
        Outfit outfit_default = p_vec_outfits_def.At(idx_bases) as Outfit
        return p_Unlock_Pass_Outfit(outfit_default)
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
        ; we remove the blank armor just as we do when a base is unregistered. it gets added back by outfitter if needed
        doticu_npcp.Outfit_Remove_Item(p_vec_outfits_def.At(idx_bases) as Outfit, CONSTS.ARMOR_BLANK as Form)
        doticu_npcp.Outfit_Add_Item(val_outfit, CONSTS.ARMOR_BLANK as Form)
        p_vec_outfits_def.Set(idx_bases, val_outfit as Form)
        ; we DO NOT update the default outfit cache, because it only carries items that are on the npc container
    endIf
p_Unlock()
endFunction

function Lock_Base(Actor ref_actor, float timeout = 6.0, float interval = 0.5)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        float time_waited = 0.0

        while (p_vec_locks.At(idx_bases) as Key) != none && time_waited < timeout
            FUNCS.Wait(interval)
            time_waited += interval
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

function Print_System()
    LOGS.Print("p_vec_bases:")
    p_vec_bases.Print()

    LOGS.Print("p_vec_locks:")
    p_vec_locks.Print()

    LOGS.Print("p_vec_vec_origs:")
    p_vec_vec_origs.Print()

    LOGS.Print("p_vec_vec_clones:")
    p_vec_vec_clones.Print()

    LOGS.Print("p_vec_outfits_def:")
    p_vec_outfits_def.Print()
endFunction

; Update Methods
doticu_npcp_vector_form p_vec_caches_def = none
function u_0_9_0()
    if p_vec_caches_def
        ; because we removed the form from .esp that the containers were instanced from, we don't need to delete them.
        VECTORS.Destroy_Form_Vector(p_vec_caches_def)
    endIf
endFunction
