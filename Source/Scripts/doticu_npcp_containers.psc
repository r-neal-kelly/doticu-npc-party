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

; Public Constants
ObjectReference property OBJECT_STORAGE hidden
    ObjectReference function Get()
        return CONSTS.MARKER_STORAGE
    endFunction
endProperty
Actor property ACTOR_PLAYER hidden
    Actor function Get()
        return CONSTS.ACTOR_PLAYER
    endFunction
endProperty
Container property CONTAINER_EMPTY hidden
    Container function Get()
        return CONSTS.CONTAINER_EMPTY
    endFunction
endProperty
Container property CONTAINER_TEMP hidden
    Container function Get()
        return CONSTS.CONTAINER_TEMP
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
doticu_npcp_container function Create(string str_name = "Container")
    doticu_npcp_container ref_container = OBJECT_STORAGE.PlaceAtMe(CONTAINER_EMPTY, 1, true, false) as doticu_npcp_container

    ; this can prevent a ctd
    Utility.Wait(0.1)

    ref_container.f_Create(p_DATA, str_name)
    ref_container.f_Register()

    return ref_container
endFunction

function Destroy(doticu_npcp_container ref_container)
    ref_container.f_Destroy()
endFunction

ObjectReference function Create_Temp()
    ObjectReference ref_container = ACTOR_PLAYER.PlaceAtMe(CONTAINER_TEMP, 1, false, false)

    ; this may prevent a ctd like the others
    Utility.Wait(0.1)

    ref_container.SetActorOwner(ACTOR_PLAYER.GetActorBase())
    
    return ref_container
endFunction

ObjectReference function Create_Persistent()
    ObjectReference ref_container = ACTOR_PLAYER.PlaceAtMe(CONTAINER_TEMP, 1, true, false)
    
    ; this may prevent a ctd like the others
    Utility.Wait(0.1)

    ref_container.SetActorOwner(ACTOR_PLAYER.GetActorBase())
    
    return ref_container
endFunction

function Open(ObjectReference ref_container)
    ref_container.Activate(ACTOR_PLAYER)
endFunction

string function Get_Name(ObjectReference ref_container)
    return ref_container.GetDisplayName()
endFunction

function Set_Name(ObjectReference ref_container, string str_name)
    ref_container.SetDisplayName(str_name, true)
endFunction

int function Count_Items(ObjectReference ref_container)
    return ref_container.GetNumItems()
endFunction

int function Count_Item(ObjectReference ref_container, Form form_item)
    return ref_container.GetItemCount(form_item)
endFunction

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

function Take_All_Playable(ObjectReference ref_subject, ObjectReference ref_object)
    ref_object.RemoveAllItems(ref_subject, false, true)
endFunction

function Copy(ObjectReference ref_subject, ObjectReference ref_object)
    int num_forms
    int idx_forms
    Form ref_form

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
