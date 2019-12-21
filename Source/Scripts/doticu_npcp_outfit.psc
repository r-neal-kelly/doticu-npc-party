Scriptname doticu_npcp_outfit extends Quest

; Private Constants
doticu_npc_party_script_data        p_DATA          = none
doticu_npc_party_script_consts      p_CONSTS        = none
doticu_npc_party_script_actor       p_ACTOR2        = none
doticu_npc_party_script_container   p_CONTAINER2    = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_CONTAINER2 = DATA.MODS.FUNCS.CONTAINER2
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_container_outfit function Create(Container form_container, Outfit form_outfit)
    ObjectReference ref_container = p_CONTAINER2.Create(form_container, true)
    (ref_container as doticu_npcp_container_outfit).f_Initialize(p_DATA, form_outfit)
    (ref_container as doticu_npcp_container_outfit).f_Register()
    return ref_container as doticu_npcp_container_outfit
endFunction

function Destroy(doticu_npcp_container_outfit ref_container)
    ref_container.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)
    ref_container.Disable()
    ref_container.Delete()
endFunction

function Get(doticu_npcp_container_outfit ref_container, Actor ref_actor)
    int num_forms
    int idx_forms
    Form ref_form

    ref_container.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)

    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form as Armor && ref_actor.IsEquipped(ref_form)
            ref_container.AddItem(ref_form, 1, true)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Set(doticu_npcp_container_outfit ref_container, Actor ref_actor)
    ObjectReference ref_container_temp = p_CONTAINER2.Create(p_DATA.CONSTS.CONTAINER_EMPTY, false)
    Outfit form_outfit = ref_container.Get_Outfit()
    LeveledItem leveled_outfit = form_outfit.GetNthPart(0) as LeveledItem
    int num_forms
    int idx_forms
    Form ref_form

    ; Clear Actor Inventory, Except Old Outfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form as Armor && ref_container.GetItemCount(ref_form) > 0
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form) - 1, true, ref_container_temp)
            idx_forms += 1
        else
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, ref_container_temp)
            num_forms -= 1
        endIf
    endWhile

    ; Accept User Input
    ref_container.Activate(p_DATA.CONSTS.ACTOR_PLAYER)
    Utility.Wait(0.1)

    ; Store User Input into Outfit
    leveled_outfit.Revert()
    num_forms = ref_container.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_container.GetNthForm(idx_forms)
        leveled_outfit.AddForm(ref_form, 1, 1)
        idx_forms += 1
    endWhile

    ; Set New Outfit
    ref_actor.SetOutfit(p_DATA.CONSTS.OUTFIT_EMPTY)
    ref_actor.SetOutfit(form_outfit)
    Utility.Wait(0.1)

    ; Clear Actor Inventory, Except New Outfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_container.GetItemCount(ref_form) < 1
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, none)
            num_forms -= 1
        else
            idx_forms += 1
        endIf
    endWhile

    ; Restore Old Actor Inventory
    p_CONTAINER2.Take_All(ref_actor, ref_container_temp)

    ; Ensure New Outfit is Equipped
    p_ACTOR2.Update_Equipment(ref_actor)
endFunction

function Unset(doticu_npcp_container_outfit ref_container, Actor ref_actor)
    ObjectReference ref_container_temp = p_CONTAINER2.Create(p_DATA.CONSTS.CONTAINER_EMPTY, false)

    ref_container.RemoveAllItems(ref_container_temp, false, true)
    Set(ref_container, ref_actor)
    ref_container_temp.RemoveAllItems(ref_container, false, true)
endFunction
