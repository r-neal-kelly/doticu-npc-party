;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_containers extends Quest

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

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

; Public Methods
ObjectReference function Create_Temp()
    ObjectReference ref_container = CONSTS.ACTOR_PLAYER.PlaceAtMe(CONSTS.CONTAINER_EMPTY, 1, false, false)

    ; this can prevent a ctd
    FUNCS.Wait(0.1)

    ref_container.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())
    
    return ref_container
endFunction

function Destroy_Temp(ObjectReference ref_container)
    ref_container.Disable()
    ref_container.Delete()
endFunction

ObjectReference function Create_Perm()
    ObjectReference ref_container = CONSTS.MARKER_STORAGE.PlaceAtMe(CONSTS.CONTAINER_EMPTY, 1, true, false)
    
    ; this can prevent a ctd
    FUNCS.Wait(0.1)

    ref_container.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())
    
    return ref_container
endFunction

function Destroy_Perm(ObjectReference ref_container)
    ref_container.Disable()
    ref_container.Delete()
endFunction

function Open(ObjectReference ref_container)
    ref_container.Activate(CONSTS.ACTOR_PLAYER)
    FUNCS.Wait(0.1)
endFunction

string function Name(ObjectReference ref_container)
    return ref_container.GetDisplayName()
endFunction

function Rename(ObjectReference ref_container, string str_name)
    ref_container.SetDisplayName(str_name, true)
endFunction

; Take_All and Empty should be deleted and replaced with C++ funcs. their usage seems to be in ACTORS.Resurrect only.
; Object_Ref_Remove_All, Object_Ref_Remove_All_Playable
function Take_All(ObjectReference ref_subject, ObjectReference ref_object)
    int num_forms
    int idx_forms
    Form ref_form

    if !ref_object
        return
    endIf

    ref_object.RemoveAllItems(ref_subject, false, true)

    num_forms = ref_object.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_object.GetNthForm(idx_forms)
        ref_subject.AddItem(ref_form, ref_object.GetItemCount(ref_form), true)
        idx_forms += 1
    endWhile
endFunction

function Empty(ObjectReference ref_container)
    int num_forms
    int idx_forms
    Form ref_form

    ref_container.RemoveAllItems(none, false, true)

    num_forms = ref_container.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_container.GetNthForm(idx_forms)
        ref_container.RemoveItem(ref_form, ref_container.GetItemCount(ref_form), true, none)
        idx_forms += 1
    endWhile
endFunction
