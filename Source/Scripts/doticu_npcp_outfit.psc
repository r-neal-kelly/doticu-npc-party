Scriptname doticu_npcp_outfit extends ObjectReference

; Private Constants
doticu_npcp_consts      p_CONSTS        = none
doticu_npcp_actors      p_ACTORS        = none
doticu_npcp_containers  p_CONTAINERS    = none
doticu_npcp_logs        p_LOGS          = none

Outfit                  p_OUTFIT        = none
LeveledItem             p_LEVELED       = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA, Outfit FORM_OUTFIT)
    p_CONSTS = DATA.CONSTS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_CONTAINERS = DATA.MODS.FUNCS.CONTAINERS
    p_LOGS = DATA.MODS.FUNCS.LOGS

    p_OUTFIT = FORM_OUTFIT
    p_LEVELED = p_OUTFIT.GetNthPart(0) as LeveledItem
endFunction

function f_Register()
endFunction

function f_Create(string str_name)
    self.SetDisplayName(str_name)
endFunction

function f_Destroy()
    self.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)
    self.Disable()
    self.Delete()
endFunction

; Public Methods
function Get(Actor ref_actor)
    int num_forms
    int idx_forms
    Form ref_form

    self.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)

    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form as Armor && ref_actor.IsEquipped(ref_form)
            self.AddItem(ref_form, 1, true)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Set(Actor ref_actor)
    ObjectReference ref_container_temp = p_CONTAINERS.Create(p_CONSTS.CONTAINER_EMPTY, false)
    int num_forms
    int idx_forms
    Form ref_form

    ; Backup Actor Inventory, Except Old Outfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form as Armor && self.GetItemCount(ref_form) > 0
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form) - 1, true, ref_container_temp)
            idx_forms += 1
        else
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, ref_container_temp)
            num_forms -= 1
        endIf
    endWhile

    ; Accept User Input
    self.Activate(p_CONSTS.ACTOR_PLAYER)
    Utility.Wait(0.1)

    ; Store User Input into Outfit
    p_LEVELED.Revert()
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        p_LEVELED.AddForm(ref_form, 1, 1)
        idx_forms += 1
    endWhile

    ; Set New Outfit
    ref_actor.SetOutfit(p_CONSTS.OUTFIT_EMPTY)
    ref_actor.SetOutfit(p_OUTFIT)
    Utility.Wait(0.1)

    ; Clear Actor Inventory, Except New Outfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if self.GetItemCount(ref_form) < 1
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, none)
            num_forms -= 1
        else
            idx_forms += 1
        endIf
    endWhile

    ; Restore Old Actor Inventory
    p_CONTAINERS.Take_All(ref_actor, ref_container_temp)

    ; Ensure New Outfit is Equipped
    p_ACTORS.Update_Equipment(ref_actor)
endFunction

function Unset(Actor ref_actor)
    ObjectReference ref_container_temp = p_CONTAINERS.Create(p_CONSTS.CONTAINER_EMPTY, false)

    self.RemoveAllItems(ref_container_temp, false, true)
    Set(ref_actor)
    ref_container_temp.RemoveAllItems(self, false, true)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if form_item as Armor == none
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        p_LOGS.Create_Note("Can only add apparel to an outfit.")
    endIf
endEvent
