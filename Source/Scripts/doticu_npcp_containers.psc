Scriptname doticu_npcp_containers extends Quest

; Private Constants
doticu_npcp_data    p_DATA              = none
doticu_npcp_consts  p_CONSTS            = none
doticu_npcp_codes   p_CODES             = none
doticu_npcp_funcs   p_FUNCS             = none

ObjectReference     p_STORAGE           = none
Actor               p_ACTOR_PLAYER      = none
Container           p_CONTAINER_EMPTY   = none
Container           p_CONTAINER_TEMP    = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_FUNCS = DATA.MODS.FUNCS
endFunction

function f_Initialize()
    p_STORAGE = p_CONSTS.MARKER_STORAGE
    p_ACTOR_PLAYER = p_CONSTS.ACTOR_PLAYER
    p_CONTAINER_EMPTY = p_CONSTS.CONTAINER_EMPTY
    p_CONTAINER_TEMP = p_CONSTS.CONTAINER_TEMP
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_container function Create(string str_name = "Container")
    doticu_npcp_container ref_container = p_STORAGE.PlaceAtMe(p_CONTAINER_EMPTY, 1, true, false) as doticu_npcp_container

    ref_container.f_Link(p_DATA)
    ref_container.f_Initialize()
    ref_container.f_Register()
    ref_container.f_Create(str_name)

    return ref_container
endFunction

function Destroy(doticu_npcp_container ref_container)
    ref_container.f_Destroy()
endFunction

ObjectReference function Create_Temp()
    ObjectReference ref_container = p_ACTOR_PLAYER.PlaceAtMe(p_CONTAINER_TEMP, 1, false, false)
    ref_container.SetActorOwner(p_ACTOR_PLAYER.GetActorBase())
    return ref_container
endFunction

function Open(ObjectReference ref_container)
    ref_container.Activate(p_ACTOR_PLAYER)
endFunction

string function Get_Name(ObjectReference ref_container)
    return ref_container.GetDisplayName()
endFunction

function Set_Name(ObjectReference ref_container, string str_name)
    ref_container.SetDisplayName(str_name, true)
endFunction

function Take_All(ObjectReference ref_subject, ObjectReference ref_object)
    int num_forms
    int idx_forms
    Form ref_form

    ref_object.RemoveAllItems(ref_subject, false, true)

    num_forms = ref_object.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_object.GetNthForm(idx_forms)
        ref_subject.AddItem(ref_form, ref_object.GetItemCount(ref_form), true)
        idx_forms += 1
    endWhile
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
