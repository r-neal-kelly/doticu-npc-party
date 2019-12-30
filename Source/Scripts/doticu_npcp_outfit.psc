Scriptname doticu_npcp_outfit extends ObjectReference

; Private Constants
doticu_npcp_consts      p_CONSTS        = none
doticu_npcp_actors      p_ACTORS        = none
doticu_npcp_containers  p_CONTAINERS    = none
doticu_npcp_outfits     p_OUTFITS       = none
doticu_npcp_logs        p_LOGS          = none

Outfit                  p_OUTFIT        = none
LeveledItem             p_LEVELED       = none
int                     p_MAX_ITEMS     =   64

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_CONTAINERS = DATA.MODS.FUNCS.CONTAINERS
    p_OUTFITS = DATA.MODS.FUNCS.OUTFITS
    p_LOGS = DATA.MODS.FUNCS.LOGS
endFunction

function f_Initialize(Outfit form_outfit)
    p_OUTFIT = form_outfit
    p_LEVELED = form_outfit.GetNthPart(0) as LeveledItem
endFunction

function f_Register()
endFunction

function f_Create(string str_name)
    self.SetDisplayName(str_name, true)
    self.SetActorOwner(p_CONSTS.ACTOR_PLAYER.GetActorBase())
endFunction

function f_Destroy()
    self.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)
    self.Disable()
    self.Delete()
endFunction

; Public Methods
string function Get_Name()
    return self.GetDisplayName()
endFunction

function Set_Name(string str_name)
    self.SetDisplayName(str_name, true)
endFunction

int function Count_Items()
    return self.Count_Items()
endFunction

int function Count_Item(Form form_item)
    return self.Count_Item(form_item)
endFunction

function Put()
    self.Activate(p_CONSTS.ACTOR_PLAYER)
endFunction

function Get(Actor ref_actor)
    int num_forms
    int idx_forms
    Form ref_form
    int num_items

    ; we refresh the cache
    self.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)
    p_LEVELED.Revert()

    ; then copy what is valid and equipped, which is how we define outfit, instead of using GetOutfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if p_OUTFITS.Is_Valid_Item(ref_form) && ref_actor.IsEquipped(ref_form)
            num_items = ref_actor.GetItemCount(ref_form)
            self.AddItem(ref_form, num_items, true)
            p_LEVELED.AddForm(ref_form, 1, num_items)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Set(Actor ref_actor, bool keep_inventory = false)
    ObjectReference ref_container_temp
    Form[] arr_leveled
    int num_forms
    int idx_forms
    Form ref_form
    int num_items
    bool do_bail

    ; check to make sure outfit is now different, else bail
    if p_LEVELED.GetNumForms() == self.GetNumItems()
        num_forms = p_LEVELED.GetNumForms()
        idx_forms = 0
        do_bail = true
        while do_bail && idx_forms < num_forms
            ref_form = p_LEVELED.GetNthForm(idx_forms)
            num_items = p_LEVELED.GetNthCount(idx_forms)
            if num_items != self.GetItemCount(ref_form)
                do_bail = false
            elseIf num_items != ref_actor.GetItemCount(ref_form)
                do_bail = false
            endIf
            idx_forms += 1
        endWhile

        if do_bail
            ; make sure everything is equipped and rendered
            p_ACTORS.Update_Equipment(ref_actor)
            return
        endIf
    endIf

    ; So we can determine what items are in the currently equipped outfit
    num_forms = p_LEVELED.GetNumForms()
    arr_leveled = Utility.CreateFormArray(num_forms, none)
    idx_forms = 0
    while idx_forms < num_forms
        arr_leveled[idx_forms] = p_LEVELED.GetNthForm(idx_forms)
        idx_forms += 1
    endWhile

    ; the choice is here for the future, but in this mod, the pack and outfits replace the actor's inventory
    if keep_inventory
        ref_container_temp = p_CONTAINERS.Create_Temp()
    else
        ref_container_temp = none
    endIf

    ; backup playable inventory minus current outfit, so we can clear new items added, and without adding dupes
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if !ref_form.IsPlayable()
            idx_forms += 1
        elseIf arr_leveled.Find(ref_form) > -1
            ; we can't fully remove at this point, because the engine adds back 1 of every outfit item automatically afterward.
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form) - 1, true, ref_container_temp); no 1, do leveled count
            idx_forms += 1
        else
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, ref_container_temp)
            num_forms -= 1
        endIf
    endWhile

    ; updating the leveled list, which is attached to Outfit form, is what gives the engine the actual items
    p_LEVELED.Revert()
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        p_LEVELED.AddForm(ref_form, 1, self.GetItemCount(ref_form))
        idx_forms += 1
    endWhile

    ; the engine will ignore this call if it's the same outfit already equipped, so we use a different one
    ref_actor.SetOutfit(p_CONSTS.OUTFIT_EMPTY)

    ; the engine will actually apply the outfit in the correct way now, which we cannot do manually
    ref_actor.SetOutfit(p_OUTFIT)

    ; without this, the next step has a high chance of crashing or freezing the game. so let the engine render first
    Utility.Wait(0.1)

    ; we remove everything playable, then one of each outfit item is reapplied by engine, thus removing any possible dupes
    ref_actor.RemoveAllItems(none, false, true)

    ; add back any discrepencies because the engine only automatically adds back one of each item
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        num_items = self.GetItemCount(ref_form)
        if num_items > 1
            ref_actor.AddItem(ref_form, num_items - 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; if keeping inventory, we add back the original from backup
    p_CONTAINERS.Take_All(ref_actor, ref_container_temp)

    ; make sure everything is equipped and rendered
    p_ACTORS.Update_Equipment(ref_actor)
endFunction

function Remove_Inventory(Actor ref_actor, ObjectReference ref_container = none)
    Form[] arr_leveled
    int num_forms
    int idx_forms
    Form ref_form
    int num_items

    ; So we can determine what items are in the currently equipped outfit
    num_forms = p_LEVELED.GetNumForms()
    arr_leveled = Utility.CreateFormArray(num_forms, none)
    idx_forms = 0
    while idx_forms < num_forms
        arr_leveled[idx_forms] = p_LEVELED.GetNthForm(idx_forms)
        idx_forms += 1
    endWhile

    ; remove inventory minus current outfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if !ref_form.IsPlayable()
            idx_forms += 1
        elseIf arr_leveled.Find(ref_form) > -1
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form) - 1, true, ref_container); no 1, do leveled count
            idx_forms += 1
        else
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, ref_container)
            num_forms -= 1
        endIf
    endWhile

    ; because stacked items stick, we get the engine to automatically add back only one. removes only playable
    ref_actor.RemoveAllItems(none, false, true)

    ; and then we add back any discrepencies in the outfit
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        num_items = self.GetItemCount(ref_form)
        if num_items > 1
            ref_actor.AddItem(ref_form, num_items - 1, true)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Unset(Actor ref_actor)
    ObjectReference ref_container_temp = p_CONTAINERS.Create_Temp()

    self.RemoveAllItems(ref_container_temp, false, true)
    Set(ref_actor)
    ref_container_temp.RemoveAllItems(self, false, true)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if self.GetNumItems() >= p_MAX_ITEMS
        p_LOGS.Create_Note("Can only have upto "+ p_MAX_ITEMS +" items in an outfit.")
    elseIf !p_OUTFITS.Is_Valid_Item(form_item)
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        p_LOGS.Create_Note("Can only add armor or weapons to an outfit.")
    endIf
endEvent
