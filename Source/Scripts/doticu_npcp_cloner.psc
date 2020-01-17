Scriptname doticu_npcp_cloner extends Quest

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
doticu_npcp_vector_form p_vec_vec_origs     =  none
doticu_npcp_vector_form p_vec_vec_clones    =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_vec_bases = VECTORS.Create_Form_Vector(8, none, 1.5)
    p_vec_vec_origs = VECTORS.Create_Form_Vector(8, none, 1.5)
    p_vec_vec_clones = VECTORS.Create_Form_Vector(8, none, 1.5)
endFunction

function f_Destroy()
    VECTORS.Destroy_Form_Vector(p_vec_vec_clones)
    VECTORS.Destroy_Form_Vector(p_vec_vec_origs)
    VECTORS.Destroy_Form_Vector(p_vec_bases)
    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
function p_Print(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Base(ref_actor) as Form)
    if idx_bases < 0
        LOGS.Create_Error("CLONER.f_Print() failed to find base_actor")
        return
    endIf

    MiscUtil.PrintConsole(" \n")
    MiscUtil.PrintConsole("Vec_Bases: " + p_vec_bases.Get_Array())
    MiscUtil.PrintConsole("Vec_Vec_Origs: " + p_vec_vec_origs.Get_Array())
    MiscUtil.PrintConsole("Vec_Vec_Clones: " + p_vec_vec_clones.Get_Array())
    MiscUtil.PrintConsole("Vec_Origs: " + (p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form).Get_Array())
    MiscUtil.PrintConsole("Vec_Clones: " + (p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form).Get_Array())
endFunction

bool function p_Has_Base(Actor ref_actor)
    return p_vec_bases.Find(ACTORS.Get_Base(ref_actor) as Form) > -1
endFunction

bool function p_Has_Original(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Base(ref_actor) as Form)
    if idx_bases > -1
        return (p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form).Has(ref_actor)
    else
        return false
    endIf
endFunction

bool function p_Has_Clone(Actor ref_clone)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Base(ref_clone) as Form)
    if idx_bases > -1
        return (p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form).Has(ref_clone)
    else
        return false
    endIf
endFunction

bool function p_Add_Base(Actor ref_actor)
    if !p_Has_Base(ref_actor)
        p_vec_bases.Push(ACTORS.Get_Base(ref_actor) as Form)
        p_vec_vec_origs.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
        p_vec_vec_clones.Push(VECTORS.Create_Form_Vector(1, none, 1.5) as Form)
        return true
    else
        return false
    endIf
endFunction

bool function p_Remove_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Base(ref_actor) as Form)
    if idx_bases > -1
        p_vec_bases.Remove_At_Unstable(idx_bases)
        p_vec_vec_origs.Remove_At_Unstable(idx_bases)
        p_vec_vec_clones.Remove_At_Unstable(idx_bases)
        return true
    else
        return false
    endIf
endFunction

function p_Cleanup_Base(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Base(ref_actor) as Form)
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

bool function p_Add_Original(Actor ref_actor)
    Form form_base = ACTORS.Get_Base(ref_actor) as Form
    Form form_ref = ref_actor as Form
    doticu_npcp_vector_form vec_origs

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("CLONER.f_Add_Original() failed to find base_actor")
        return false
    endIf

    vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("CLONER.f_Add_Original() failed to find vec_origs")
        return false
    endIf

    if !vec_origs.Has(form_ref)
        vec_origs.Push(form_ref)
        return true
    else
        return false
    endIf
endFunction

bool function p_Add_Clone(Actor ref_clone)
    Form form_base = ACTORS.Get_Base(ref_clone) as Form
    Form form_ref = ref_clone as Form
    doticu_npcp_vector_form vec_clones

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("CLONER.f_Add_Clone() failed to find base_actor")
        return false
    endIf

    vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("CLONER.f_Add_Clone() failed to find vec_clones")
        return false
    endIf

    if !vec_clones.Has(form_ref)
        vec_clones.Push(form_ref)
        return true
    else
        return false
    endIf
endFunction

bool function p_Remove_Original(Actor ref_actor)
    Form form_base = ACTORS.Get_Base(ref_actor) as Form
    Form form_ref = ref_actor as Form
    doticu_npcp_vector_form vec_origs

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("CLONER.f_Remove_Original() failed to find base_actor")
        return false
    endIf

    vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("CLONER.f_Remove_Original() failed to find vec_origs")
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
    Form form_base = ACTORS.Get_Base(ref_clone) as Form
    Form form_ref = ref_clone as Form
    doticu_npcp_vector_form vec_clones

    int idx_bases = p_vec_bases.Find(form_base)
    if idx_bases < 0
        LOGS.Create_Error("CLONER.f_Remove_Clone() failed to find base_actor")
        return false
    endIf

    vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("CLONER.f_Remove_Clone() failed to find vec_clones")
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

bool function p_Has_Same_Head(Actor ref_actor_1, Actor ref_actor_2)
    ActorBase ref_base_1 = ref_actor_1.GetLeveledActorBase(); returns unleveled base too
    ActorBase ref_base_2 = ref_actor_2.GetLeveledActorBase()
    int int_slots_1 = ref_base_1.GetNumHeadParts()
    int int_slots_2 = ref_base_2.GetNumHeadParts()

    if int_slots_1 != int_slots_2
        return false
    endIf

    int int_slot_idx = 0
    while int_slot_idx < int_slots_1
        if ref_base_1.GetNthHeadPart(int_slot_idx) != ref_base_2.GetNthHeadPart(int_slot_idx)
            return false
        endIf
        int_slot_idx += 1
    endWhile

    return true
endFunction

Actor function p_Clone(Actor ref_actor)
    ActorBase base_actor = ref_actor.GetBaseObject() as ActorBase
    Form base_form = base_actor as Form
    Actor ref_clone = none

    CONSTS.MARKER_CLONER.MoveTo(ref_actor, 0.0, 0.0, 0.0)

    if ACTORS.Is_Unique(ref_actor)
        ref_clone = CONSTS.MARKER_CLONER.PlaceAtMe(base_form, 1, true, false) as Actor; persist, disable
        ref_clone.MoveTo(CONSTS.MARKER_CLONER)
        ref_clone.EnableAI(false)
    else
        ; can prob make this parallel with the jobs pattern
        int code_mode = 4
        int num_tries = 0
        int max_tries = 300
        while num_tries < max_tries
            if code_mode == 4
                ref_clone = CONSTS.MARKER_CLONER.PlaceAtMe(base_form, 1, true, false) as Actor; persist, disable
                ref_clone.MoveTo(CONSTS.MARKER_CLONER)
                ref_clone.EnableAI(false)
            else
                ref_clone = CONSTS.MARKER_CLONER.PlaceActorAtMe(base_actor, code_mode, none); can't persist!
                ref_clone.MoveTo(CONSTS.MARKER_CLONER)
                ref_clone.EnableAI(false)
            endIf

            if p_Has_Same_Head(ref_actor, ref_clone)
                num_tries = max_tries; break
            else
                ref_clone.Disable()
                ref_clone.Delete()
                ref_clone = none

                code_mode -= 1
                if code_mode < 0
                    code_mode = 4
                endIf

                num_tries += 1
            endIf
        endWhile
        ; maybe we should try to make the clone persistent with a quest object or something.
        ; we would have to make a quest that contains refs to quest tokens, and according to
        ; the wiki, putting that in any container makes it so that the engine will not delete
        ; that container, which means actors too. this can be done retroactively
    endIf

    CONSTS.MARKER_CLONER.MoveTo(CONSTS.MARKER_STORAGE)

    if !ref_clone
        return none
    else
        ref_clone.EnableAI(true)
        ACTORS.Pacify(ref_clone)
        ACTORS.Set_Name(ref_clone, "Clone of " + ACTORS.Get_Name(ref_actor))

        return ref_clone
    endIf
endFunction

; Public Methods
Actor function Create(Actor ref_actor)
    Actor ref_clone = p_Clone(ref_actor)
    if !ref_clone
        return none
    endIf

    p_Add_Base(ref_actor)
    p_Add_Original(ref_actor)
    p_Add_Clone(ref_clone)

    return ref_clone
endFunction

function Destroy(Actor ref_clone, bool do_delete)
    p_Remove_Clone(ref_clone)

    if do_delete
        ref_clone.Disable()
        ref_clone.Delete()
    else
        p_Add_Original(ref_clone)
    endIf

    p_Cleanup_Base(ref_clone)
endFunction

bool function Is_Original(Actor ref_actor)
    return p_Has_Original(ref_actor)
endFunction

bool function Is_Clone(Actor ref_actor)
    return p_Has_Clone(ref_actor)
endFunction

Form[] function Get_Originals(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Base(ref_actor) as Form)
    if idx_bases < 0
        LOGS.Create_Error("CLONER.Get_Originals() failed to find base_actor")
        return Utility.CreateFormArray(0, none)
    endIf

    doticu_npcp_vector_form vec_origs = p_vec_vec_origs.At(idx_bases) as doticu_npcp_vector_form
    if !vec_origs
        LOGS.Create_Error("CLONER.Get_Originals() failed to find vec_origs")
        return Utility.CreateFormArray(0, none)
    endIf

    Form[] arr_origs = vec_origs.Get_Array()
    if !arr_origs
        LOGS.Create_Error("CLONER.Get_Originals() failed to vec_origs.Get_Array()")
        return Utility.CreateFormArray(0, none)
    endIf

    return arr_origs
endFunction

Form[] function Get_Clones(Actor ref_actor)
    int idx_bases = p_vec_bases.Find(ACTORS.Get_Base(ref_actor) as Form)
    if idx_bases < 0
        LOGS.Create_Error("CLONER.Get_Clones() failed to find base_actor")
        return Utility.CreateFormArray(0, none)
    endIf

    doticu_npcp_vector_form vec_clones = p_vec_vec_clones.At(idx_bases) as doticu_npcp_vector_form
    if !vec_clones
        LOGS.Create_Error("CLONER.Get_Clones() failed to find vec_clones")
        return Utility.CreateFormArray(0, none)
    endIf

    Form[] arr_clones = vec_clones.Get_Array()
    if !arr_clones
        LOGS.Create_Error("CLONER.Get_Clones() failed to vec_origs.Get_Array()")
        return Utility.CreateFormArray(0, none)
    endIf

    return arr_clones
endFunction

function Update_Outfit(Actor ref_actor, Outfit form_outfit)
    Form[] arr_origs = Get_Originals(ref_actor)
    int idx_origs = arr_origs.length
    while idx_origs > 0
        idx_origs -= 1
        ref_actor = arr_origs[idx_origs] as Actor
        if ref_actor.IsDeleted()
            p_Remove_Original(ref_actor)
        elseIf ACTORS.Is_Alive(ref_actor) && !MEMBERS.Has_Member(ref_actor)
            ref_actor.SetOutfit(CONSTS.OUTFIT_EMPTY)
            ref_actor.SetOutfit(form_outfit)
        endIf
    endWhile
endFunction
