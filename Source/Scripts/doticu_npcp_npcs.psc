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
doticu_npcp_vector_form p_vec_bases         =  none
doticu_npcp_vector_form p_vec_outfits       =  none
doticu_npcp_vector_form p_vec_defaults      =  none
doticu_npcp_vector_form p_vec_vec_origs     =  none
doticu_npcp_vector_form p_vec_vec_clones    =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_vec_bases = VECTORS.Create_Form_Vector(8, none, 1.5)
    p_vec_outfits = VECTORS.Create_Form_Vector(8, none, 1.5)
    p_vec_defaults = VECTORS.Create_Form_Vector(8, none, 1.5)
    p_vec_vec_origs = VECTORS.Create_Form_Vector(8, none, 1.5)
    p_vec_vec_clones = VECTORS.Create_Form_Vector(8, none, 1.5)
endFunction

function f_Destroy()
    VECTORS.Destroy_Form_Vector(p_vec_vec_clones)
    VECTORS.Destroy_Form_Vector(p_vec_vec_origs)
    VECTORS.Destroy_Form_Vector(p_vec_defaults)
    VECTORS.Destroy_Form_Vector(p_vec_outfits)
    VECTORS.Destroy_Form_Vector(p_vec_bases)
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

; Private Methods
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

bool function p_Add_Base(Actor ref_actor, Outfit outfit_default)
    ;/
        either the real base or the leveled base carries the outfit.
        if a leveled ref is outfitted, the dynamic, not static, leveled base gets the outfit.
        so a template clone of a leveled does not have a connection with the leveled any longer
        however a clone of an unleveled does, so the original must be added in this case,
        except if the original was never spawned in the world, like all leveled actors.
        if a leveled itself is added into the system, then we need to store the leveled base
        to counteract against the bug, however, it is not apparent with such dynamic bases.
        because it appears that dynamic bases are not reused, or reused very rarely.
    /;

    if !p_Has_Base(ref_actor)
        ActorBase base_actor = ACTORS.Get_Real_Base(ref_actor); get's the actual actor base, nothing leveled
        ObjectReference default_cache = OUTFITS.Get_Default_Cache(ref_actor, outfit_default)

        p_vec_bases.Push(base_actor as Form)
        p_vec_outfits.Push(outfit_default as Form)
        p_vec_defaults.Push(default_cache as Form)
        p_vec_vec_origs.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
        p_vec_vec_clones.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
        return true
    else
        return false
    endIf
endFunction

bool function p_Remove_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        p_vec_bases.Remove_At_Unstable(idx_bases)
        p_vec_outfits.Remove_At_Unstable(idx_bases)
        p_vec_defaults.Remove_At_Unstable(idx_bases)
        p_vec_vec_origs.Remove_At_Unstable(idx_bases)
        p_vec_vec_clones.Remove_At_Unstable(idx_bases)
        return true
    else
        return false
    endIf
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
    return p_is_created
endFunction

function Register(Actor ref_actor)
    if !ref_actor || Is_Clone(ref_actor)
        return
    endIf

    p_Add_Base(ref_actor, ACTORS.Get_Base_Outfit(ref_actor))
    p_Add_Original(ref_actor)
endFunction

function Unregister(Actor ref_actor); unused atm
    if !Is_Original(ref_actor)
        return
    endIf

    p_Remove_Original(ref_actor)
    Cleanup_Base(ref_actor)
endFunction

Actor function Clone(Actor ref_actor)
    if !ref_actor
        return none
    endIf

    Actor ref_clone = p_Clone(ref_actor)
    if !ref_clone
        return none
    endIf

    ; we don't want to add a leveled or its base to the system, it doesn't share outfit with clone
    ; however we want to make sure the clone gets the leveled outfit and not a template outfit
    p_Add_Base(ref_clone, ACTORS.Get_Base_Outfit(ref_actor))

    if ACTORS.Is_Unleveled(ref_actor)
        p_Add_Original(ref_actor)
    endIf

    p_Add_Clone(ref_clone)

    ; we wait to outfit until we know that the base is registered
    OUTFITS.Outfit_Clone(ref_clone, ref_actor)

    return ref_clone
endFunction

function Unclone(Actor ref_clone)
    if !Is_Clone(ref_clone)
        return
    endIf

    ref_clone.Disable()
    ref_clone.Delete()

    Cleanup_Base(ref_clone); automatically removes deleted actors
endFunction

bool function Is_Original(Actor ref_actor)
    return ref_actor && p_Has_Original(ref_actor)
endFunction

bool function Is_Clone(Actor ref_actor)
    return ref_actor && p_Has_Clone(ref_actor)
endFunction

Form[] function Get_Originals(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases < 0
        return Utility.CreateFormArray(1, none)
    endIf

    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("NPCS.Get_Originals() failed to find vec_origs")
        return Utility.CreateFormArray(1, none)
    endIf

    return vec_origs.Get_Array()
endFunction

Form[] function Get_Clones(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases < 0
        return Utility.CreateFormArray(1, none)
    endIf

    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("NPCS.Get_Clones() failed to find vec_clones")
        return Utility.CreateFormArray(1, none)
    endIf

    return vec_clones.Get_Array()
endFunction

Outfit function Get_Base_Outfit(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        return p_vec_outfits.At(idx_bases) as Outfit
    else
        return none
    endIf
endFunction

function Set_Base_Outfit(Actor ref_actor, Outfit val_outfit)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        p_vec_outfits.Set(idx_bases, val_outfit as Form)
    endIf
endFunction

ObjectReference function Get_Default_Cache(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    if idx_bases > -1
        return p_vec_defaults.At(idx_bases) as ObjectReference
    else
        return none
    endIf
endFunction

function Cleanup_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Real_Base(ref_actor) as Form)
    doticu_npcp_vector_form vec_origs
    doticu_npcp_vector_form vec_clones

    if idx_bases > -1
        vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
        vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form

        int idx_origs = 0
        while idx_origs < vec_origs.num
            if (vec_origs.At(idx_origs) as Actor).IsDeleted()
                vec_origs.Remove_At_Unstable(idx_origs)
            else
                idx_origs += 1
            endIf
        endWhile

        int idx_clones = 0
        while idx_clones < vec_clones.num
            if (vec_clones.At(idx_clones) as Actor).IsDeleted()
                vec_clones.Remove_At_Unstable(idx_clones)
            else
                idx_clones += 1
            endIf
        endWhile

        if vec_origs.num == 0 && vec_clones.num == 0
            p_Remove_Base(ref_actor)
        endIf
    endIf
endFunction

; Update Methods
function u_0_7_5()
    ; 1. set the outfit of every npc to their default outfit, so vanilla outfit is ready
    ; 2. recache with more accurate base
    ; 3. create a default for each npc base we store
    ; 4. remove any clones that leaked into original slots

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

    p_vec_bases = VECTORS.Create_Form_Vector(p_vec_bases.max, none, 1.5)
    p_vec_outfits = VECTORS.Create_Form_Vector(p_vec_bases.max, none, 1.5)
    p_vec_defaults = VECTORS.Create_Form_Vector(p_vec_bases.max, none, 1.5)
    p_vec_vec_origs = VECTORS.Create_Form_Vector(p_vec_bases.max, none, 1.5)
    p_vec_vec_clones = VECTORS.Create_Form_Vector(p_vec_bases.max, none, 1.5)

    LOGS.Print("initializing update...")
    idx_bases = 0
    while idx_bases < num_bases
        num_actors += (arr_vec_origs[idx_bases] as doticu_npcp_vector_form).num
        num_actors += (arr_vec_clones[idx_bases] as doticu_npcp_vector_form).num
        idx_bases += 1
    endWhile

    string str_message = "NPC Party: This update may take several minutes. "
    str_message += "Open the console to monitor progress!\n"
    str_message += "Estimate: " + ((num_actors / 60 + 1) as int) + " minutes."
    Debug.MessageBox(str_message)

    idx_bases = 0
    while idx_bases < num_bases
        Outfit base_outfit = arr_outfits[idx_bases] as Outfit

        doticu_npcp_vector_form vec_origs = arr_vec_origs[idx_bases] as doticu_npcp_vector_form
        Form[] arr_origs = vec_origs.Get_Array()
        int idx_origs = 0
        int num_origs = vec_origs.num
        while idx_origs < num_origs
            Actor orig_ref = arr_origs[idx_origs] as Actor
            ActorBase orig_base = ACTORS.Get_Real_Base(orig_ref)

            ; so we can start off on the right foot in the new outfit algorithm.
            ; without this, any base actor with one of our outfits will not
            ; immediately change if the "vanilla" outfit is selected
            ACTORS.Set_Base_Outfit(orig_ref, base_outfit)

            ; we add base in each loop, because there is no other way to know if each orig and clone has the same real base.
            ; we do this manually because we want the clone to help define default
            if !p_vec_bases.Has(orig_base as Form)
                ; a disabled clone can still have their inventory checked and accouted for
                Actor orig_clone = ACTORS.Clone(orig_ref, CONSTS.ACTOR_PLAYER, false, true)
                ObjectReference orig_default = OUTFITS.Get_Default_Cache(orig_clone, base_outfit)

                orig_clone.Delete()
                p_vec_bases.Push(orig_base as Form)
                p_vec_outfits.Push(base_outfit as Form)
                p_vec_defaults.Push(orig_default as Form)
                p_vec_vec_origs.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
                p_vec_vec_clones.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
            endIf

            ; we need to weed out any potential clones due to an oversight in the previous version
            int old_idx_bases_orig = old_vec_bases.Find(ACTORS.Get_Base(orig_ref) as Form)
            if old_idx_bases_orig > -1 && (old_vec_vec_clones.At(old_idx_bases_orig) as doticu_npcp_vector_form).Has(orig_ref)
                ; below, when the same ref is passed from the clones array, it won't add it to system again
                p_Add_Clone(orig_ref)
            else
                p_Add_Original(orig_ref)
            endIf

            idx_actors += 1
            idx_origs += 1
        endWhile
        if num_origs > 0
            LOGS.Print(((idx_actors * 100 / num_actors) as int) + "%% updated...")
        endIf

        doticu_npcp_vector_form vec_clones = arr_vec_clones[idx_bases] as doticu_npcp_vector_form
        Form[] arr_clones = vec_clones.Get_Array()
        int idx_clones = 0
        int num_clones = vec_clones.num
        while idx_clones < num_clones
            Actor clone_ref = arr_clones[idx_clones] as Actor
            ActorBase clone_base = ACTORS.Get_Real_Base(clone_ref)

            ; so we can start off on the right foot in the new outfit algorithm.
            ; without this, any base actor with one of our outfits will not
            ; immediately change if the "vanilla" outfit is selected
            ACTORS.Set_Base_Outfit(clone_ref, base_outfit)

            ; we add base in each loop, because there is no other way to know if each orig and clone has the same real base.
            ; we do this manually because we want the clone to help define default
            if !p_vec_bases.Has(clone_base as Form)
                ; a disabled clone can still have their inventory checked and accouted for
                Actor clone_clone = ACTORS.Clone(clone_ref, CONSTS.ACTOR_PLAYER, false, true)
                ObjectReference clone_default = OUTFITS.Get_Default_Cache(clone_clone, base_outfit)

                clone_clone.Delete()
                p_vec_bases.Push(clone_base as Form)
                p_vec_outfits.Push(base_outfit as Form)
                p_vec_defaults.Push(clone_default as Form)
                p_vec_vec_origs.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
                p_vec_vec_clones.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
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

    LOGS.Print("completed update.")
    Debug.MessageBox("NPC Party: The update has been completed. You should save your game. Thank you for waiting!")
endFunction
