Scriptname doticu_npcp_containers extends Quest

; Private Constants
doticu_npcp_consts  p_CONSTS    = none
doticu_npcp_codes   p_CODES     = none
doticu_npcp_funcs   p_FUNCS     = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_FUNCS = DATA.MODS.FUNCS
endFunction

function f_Initialize()
endFunction

function f_Register()
endFunction

; Public Methods
ObjectReference function Create(Container form_container, bool do_persist = false)
    ObjectReference ref_container = p_CONSTS.ACTOR_PLAYER.PlaceAtMe(form_container, 1, do_persist, false)
    ref_container.SetActorOwner(p_CONSTS.ACTOR_PLAYER.GetActorBase())
    return ref_container
endFunction

function Destroy(ObjectReference ref_container)
    ref_container.Disable()
    ref_container.Delete()
endFunction

function Take_All(ObjectReference ref_container_subject, ObjectReference ref_container_object)
    int num_forms
    int idx_forms
    Form ref_form

    ref_container_object.RemoveAllItems(ref_container_subject, false, true)

    num_forms = ref_container_object.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_container_object.GetNthForm(idx_forms)
        ref_container_subject.AddItem(ref_form, ref_container_object.GetItemCount(ref_form), true)
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

function Copy(ObjectReference ref_container_subject, ObjectReference ref_container_object)
    int num_forms
    int idx_forms
    Form ref_form

    num_forms = ref_container_object.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_container_object.GetNthForm(idx_forms)
        ref_container_subject.AddItem(ref_form, ref_container_object.GetItemCount(ref_form), true)
        idx_forms += 1
    endWhile
endFunction

; Update Methods
function u_0_1_0()
endFunction
