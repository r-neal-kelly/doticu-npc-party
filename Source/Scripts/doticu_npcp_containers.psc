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

    p_Init_Categories()
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
function p_Init_Categories()
    Init_Container(CONSTS.CATEGORY_SWORDS)
    Init_Container(CONSTS.CATEGORY_GREATSWORDS)
    Init_Container(CONSTS.CATEGORY_WARAXES)
    Init_Container(CONSTS.CATEGORY_BATTLEAXES)
    Init_Container(CONSTS.CATEGORY_MACES)
    Init_Container(CONSTS.CATEGORY_WARHAMMERS)
    Init_Container(CONSTS.CATEGORY_DAGGERS)
    Init_Container(CONSTS.CATEGORY_BOWS)
    Init_Container(CONSTS.CATEGORY_STAVES)
    Init_Container(CONSTS.CATEGORY_WEAPONS)

    Init_Container(CONSTS.CATEGORY_LIGHT_ARMOR)
    Init_Container(CONSTS.CATEGORY_HEAVY_ARMOR)
    Init_Container(CONSTS.CATEGORY_SHIELDS)
    Init_Container(CONSTS.CATEGORY_JEWELRY)
    Init_Container(CONSTS.CATEGORY_CLOTHES)

    Init_Container(CONSTS.CATEGORY_POTIONS)
    Init_Container(CONSTS.CATEGORY_POISONS)
    Init_Container(CONSTS.CATEGORY_FOOD)

    Init_Container(CONSTS.CATEGORY_SPELL_TOMES)
    Init_Container(CONSTS.CATEGORY_RECIPES)
    Init_Container(CONSTS.CATEGORY_BOOKS_A)
    Init_Container(CONSTS.CATEGORY_BOOKS_B)
    Init_Container(CONSTS.CATEGORY_BOOKS_C)
    Init_Container(CONSTS.CATEGORY_BOOKS_D)
    Init_Container(CONSTS.CATEGORY_BOOKS_E)
    Init_Container(CONSTS.CATEGORY_BOOKS_F)
    Init_Container(CONSTS.CATEGORY_BOOKS_G)
    Init_Container(CONSTS.CATEGORY_BOOKS_H)
    Init_Container(CONSTS.CATEGORY_BOOKS_I)
    Init_Container(CONSTS.CATEGORY_BOOKS_J)
    Init_Container(CONSTS.CATEGORY_BOOKS_K)
    Init_Container(CONSTS.CATEGORY_BOOKS_L)
    Init_Container(CONSTS.CATEGORY_BOOKS_M)
    Init_Container(CONSTS.CATEGORY_BOOKS_N)
    Init_Container(CONSTS.CATEGORY_BOOKS_O)
    Init_Container(CONSTS.CATEGORY_BOOKS_P)
    Init_Container(CONSTS.CATEGORY_BOOKS_Q)
    Init_Container(CONSTS.CATEGORY_BOOKS_R)
    Init_Container(CONSTS.CATEGORY_BOOKS_S)
    Init_Container(CONSTS.CATEGORY_BOOKS_T)
    Init_Container(CONSTS.CATEGORY_BOOKS_U)
    Init_Container(CONSTS.CATEGORY_BOOKS_V)
    Init_Container(CONSTS.CATEGORY_BOOKS_W)
    Init_Container(CONSTS.CATEGORY_BOOKS_X)
    Init_Container(CONSTS.CATEGORY_BOOKS_Y)
    Init_Container(CONSTS.CATEGORY_BOOKS_Z)
    Init_Container(CONSTS.CATEGORY_BOOKS)

    Init_Container(CONSTS.CATEGORY_METALS)
    Init_Container(CONSTS.CATEGORY_LEATHER)
    Init_Container(CONSTS.CATEGORY_GEMS)
    Init_Container(CONSTS.CATEGORY_CLUTTER)
    Init_Container(CONSTS.CATEGORY_AMMO)
    Init_Container(CONSTS.CATEGORY_INGREDIENTS)
    Init_Container(CONSTS.CATEGORY_SCROLLS)
    Init_Container(CONSTS.CATEGORY_SOULGEMS)
    Init_Container(CONSTS.CATEGORY_KEYS)
    Init_Container(CONSTS.CATEGORY_OTHERS)
endFunction

; Public Methods
ObjectReference function Create_Temp()
    ObjectReference ref_container = CONSTS.ACTOR_PLAYER.PlaceAtMe(CONSTS.CONTAINER_EMPTY, 1, false, false)

    ; this can prevent a ctd
    FUNCS.Wait(0.1)

    ref_container.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())

    ; to make sure certain fields in c++ have been allocated for our plugin
    ref_container.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_container.RemoveItem(CONSTS.WEAPON_BLANK, 1, true)
    
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

    ; to make sure certain fields in c++ have been allocated for our plugin
    ref_container.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_container.RemoveItem(CONSTS.WEAPON_BLANK, 1, true)
    
    return ref_container
endFunction

function Destroy_Perm(ObjectReference ref_container)
    ref_container.Disable()
    ref_container.Delete()
endFunction

function Init_Container(ObjectReference ref_container)
    ref_container.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_container.RemoveItem(CONSTS.WEAPON_BLANK, 1, true)
endFunction

function Open(ObjectReference ref_container)
    ref_container.Activate(CONSTS.ACTOR_PLAYER)
    FUNCS.Wait(0.1)
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

; Update Methods
function u_0_9_1()
    p_Init_Categories()
endFunction
