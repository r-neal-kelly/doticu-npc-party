Scriptname doticu_npcp_outfit extends ObjectReference

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_cloner property CLONER hidden
    doticu_npcp_cloner function Get()
        return p_DATA.MODS.FUNCS.CLONER
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
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
doticu_npcp_data    p_DATA          =  none
Outfit              p_OUTFIT        =  none
LeveledItem         p_LEVELED       =  none
int                 p_MAX_ITEMS     =    -1

; Private Variables
bool                p_is_created    = false
string              p_str_name      =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA, Outfit outfit_outfit, string str_name)
    p_DATA = DATA
    p_OUTFIT = outfit_outfit
    p_LEVELED = outfit_outfit.GetNthPart(0) as LeveledItem
    p_MAX_ITEMS = 64

    p_is_created = true
    p_str_name = ""
    
    self.SetDisplayName(str_name, true)
    self.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())
endFunction

function f_Destroy()
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)
    self.Disable()
    self.Delete()

    p_str_name = ""
    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
bool function p_Has_Changed(Actor ref_actor)
    int num_forms
    int idx_forms
    Form ref_form
    int num_items

    if p_LEVELED.GetNumForms() != self.GetNumItems()
        return true
    endIf

    idx_forms = 0
    num_forms = p_LEVELED.GetNumForms()
    while idx_forms < num_forms
        ref_form = p_LEVELED.GetNthForm(idx_forms)
        num_items = p_LEVELED.GetNthCount(idx_forms)
        if num_items != self.GetItemCount(ref_form)
            return true
        endIf
        idx_forms += 1
    endWhile

    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if !ref_form
            return true
        endIf
        num_items = ref_actor.GetItemCount(ref_form)
        if ref_form.IsPlayable() && num_items != self.GetItemCount(ref_form)
            return true
        elseIf !ref_form.IsPlayable() && ref_actor.IsEquipped(ref_form)
            return true
        endIf
        idx_forms += 1
    endWhile

    return false
endFunction

; Public Methods
string function Get_Name()
    return p_str_name
endFunction

function Set_Name(string str_name)
    p_str_name = str_name
    self.SetDisplayName(p_str_name, true)
endFunction

int function Get_Items_Count()
    return self.GetNumItems()
endFunction

int function Get_Item_Count(Form form_item)
    return self.GetItemCount(form_item)
endFunction

function Copy(doticu_npcp_outfit ref_outfit)
    CONTAINERS.Copy(self, ref_outfit)
endFunction

function Put()
    self.SetDisplayName(p_str_name, true)
    self.Activate(CONSTS.ACTOR_PLAYER)
    Utility.Wait(0.1)
endFunction

function Get(Actor ref_actor)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items

    ; we refresh the cache
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)
    p_LEVELED.Revert()

    ; then copy what is valid and equipped, which is how we define outfit, instead of using GetOutfit
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if OUTFITS.Is_Valid_Item(ref_form) && ref_actor.IsEquipped(ref_form)
            num_items = ref_actor.GetItemCount(ref_form)
            self.AddItem(ref_form, num_items, true)
            p_LEVELED.AddForm(ref_form, 1, num_items)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Set(Actor ref_actor, bool do_force = false)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items
    ObjectReference ref_trash

    if !do_force && !p_Has_Changed(ref_actor)
        return
    endIf

    ; updating the leveled list, which is attached to Outfit form, is what gives the engine the actual items
    p_LEVELED.Revert()
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        p_LEVELED.AddForm(ref_form, 1, self.GetItemCount(ref_form))
        idx_forms += 1
    endWhile
    
    ; the engine may ignore this call if it's the same outfit form already equipped, so we use a different one
    ;ref_actor.SetOutfit(CONSTS.OUTFIT_EMPTY)

    ; the engine will actually apply the outfit in the correct way now, which we cannot do manually
    ref_actor.SetOutfit(p_OUTFIT)

    ; the trash container is necessary because it keeps the engine from crashing or freezing when removing actor's items!
    ref_trash = CONTAINERS.Create_Temp()

    ; some items may be duplicates and not match the container's count. we can't remove one manually, so we remove all.
    ref_actor.RemoveAllItems(ref_trash, false, true)

    ; we have to manually delete any non-playable items that are equipped. we leave everything else because they may be tokens
    Delete_Unplayable_Equipment(ref_actor)

    ; add back any discrepencies because the engine only automatically adds back one of each item
    idx_forms = 0
    num_forms = self.GetNumItems()
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        num_items = self.GetItemCount(ref_form)
        if num_items > 1
            ref_actor.AddItem(ref_form, num_items - 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; make sure everything is equipped and rendered.
    ACTORS.Update_Equipment(ref_actor)

    ; need to make sure that a clone doesn't get the same outfit, so send through until it gets its own
    Set(ref_actor)
endFunction

function Transfer_Inventory(Actor ref_actor, ObjectReference ref_container = none)
    Form[] arr_leveled
    int idx_forms
    int num_forms
    Form ref_form
    int num_items

    ; copy inventory minus current outfit
    if ref_container
        idx_forms = 0
        num_forms = ref_actor.GetNumItems()
        while idx_forms < num_forms
            ref_form = ref_actor.GetNthForm(idx_forms)
            if ref_form && ref_form.IsPlayable() && !self.GetItemCount(ref_form)
                ref_container.AddItem(ref_form, ref_actor.GetItemCount(ref_form), true)
            endIf
            idx_forms += 1
        endWhile
    endIf
endFunction

function Delete_Unplayable_Equipment(Actor ref_actor)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items
    ObjectReference ref_trash = CONTAINERS.Create_Temp()

    ; we have to copy one of each unplayable equipped item, because when one is removed, they are all uneqipped
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form && !ref_form.IsPlayable() && ref_actor.IsEquipped(ref_form)
            ref_trash.AddItem(ref_form, 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; then we can actually remove them
    idx_forms = 0
    num_forms = ref_trash.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_trash.GetNthForm(idx_forms)
        num_items = ref_actor.GetItemCount(ref_form)
        ref_actor.RemoveItem(ref_form, num_items, true, ref_trash)
        idx_forms += 1
    endWhile
endFunction

function Update_Base(Actor ref_actor)
    ; this is to ensure that npcs who have been cloned are putting on their outfits. there
    ; is a bug in the engine which sticks and causes cloned npcs to be naked when they
    ; are given a new outfit form that has any of the same items as the previous one.
    CLONER.Update_Outfit(ref_actor, p_OUTFIT)
endFunction

function Unset(Actor ref_actor)
    ObjectReference ref_container_temp = CONTAINERS.Create_Temp()

    self.RemoveAllItems(ref_container_temp, false, true)
    Set(ref_actor)
    ref_container_temp.RemoveAllItems(self, false, true)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if self.GetNumItems() >= p_MAX_ITEMS
        LOGS.Create_Note("Can only have upto "+ p_MAX_ITEMS +" items in an outfit.")
    elseIf !OUTFITS.Is_Valid_Item(form_item)
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Can only add armor or weapons to an outfit.")
    endIf
endEvent
