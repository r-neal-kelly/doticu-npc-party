;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_outfit extends ObjectReference

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
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return p_DATA.MODS.FUNCS.NPCS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA          =  none

int property p_MAX_ITEMS hidden
    int function Get()
        return 16
    endFunction
endProperty

; Private Variables
bool                    p_is_created        = false
string                  p_str_name          =    ""
int                     p_code_create       =     0; OUTFIT_VANILLA, OUTFIT_DEFAULT
ObjectReference         p_cache_outfit      =  none
ObjectReference         p_cache_self        =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA, string str_name, int code_create = 0)
    p_DATA = DATA

    p_is_created = true
    p_str_name = str_name
    p_code_create = code_create
    p_cache_outfit = none
    p_cache_self = none
    
    self.SetDisplayName(p_str_name, true)
    self.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())
endFunction

function f_Destroy()
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true); this needs to be set to an optional place
    self.Disable()
    self.Delete()

    p_cache_self = none
    p_cache_outfit = none
    p_code_create = 0
    p_str_name = ""
    p_is_created = false

    p_DATA = none
endFunction

function f_Register()
endFunction

; Private Methods
bool function p_Has_Changed(Actor ref_actor)
    int num_forms
    int idx_forms
    Form form_item
    int num_items

    if !p_cache_outfit || !p_cache_self
        Cache_Outfit(ref_actor)
        Cache_Self()
    endIf

    ; ref_actor may have items that aren't in the oufit
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item && !(form_item as ObjectReference)
            ; we completely avoid any references and leave them alone.
            if form_item.IsPlayable() || ref_actor.IsEquipped(form_item)
                ; any playable item is fair game, but only equipped unplayables are accounted for
                if p_cache_outfit.GetItemCount(form_item) < 1 && p_cache_self.GetItemCount(form_item) < 1
                    return true
                endIf
            endIf
        endIf
        idx_forms += 1
    endWhile

    ; ref_actor may be missing items that are in the outfit
    idx_forms = 0
    num_forms = p_cache_outfit.GetNumItems()
    while idx_forms < num_forms
        form_item = p_cache_outfit.GetNthForm(idx_forms)
        if ref_actor.GetItemCount(form_item) != p_cache_outfit.GetItemCount(form_item)
            return true
        endIf
        idx_forms += 1
    endWhile

    idx_forms = 0
    num_forms = p_cache_self.GetNumItems()
    while idx_forms < num_forms
        form_item = p_cache_self.GetNthForm(idx_forms)
        if ref_actor.GetItemCount(form_item) != p_cache_self.GetItemCount(form_item)
            return true
        endIf
        idx_forms += 1
    endWhile

    return false
endFunction

function p_Set(Actor ref_actor, bool do_force = false)
    ; we still need to handle Set_Dead case!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    bool is_teammate = ref_actor.IsPlayerTeammate()
    int idx_forms
    int num_forms
    Form form_item
    int num_items
    ObjectReference ref_junk = CONTAINERS.Create_Temp()

    if ACTORS.Is_Dead(ref_actor) || !do_force && !p_Has_Changed(ref_actor)
        MiscUtil.PrintConsole("will not outfit")
        return
    endIf
    MiscUtil.PrintConsole("will outfit")

    ; this will stop the actor from rendering while we manage its inventory
    ref_actor.SetPlayerTeammate(false)

    ; this way no items will automatically be added back when we remove them
    ref_actor.SetOutfit(CONSTS.OUTFIT_EMPTY)

    ; it's error prone to remove items from actor unless they are cached
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item && !(form_item as ObjectReference)
            ; we completely avoid any references and leave them alone.
            if form_item.IsPlayable() || ref_actor.IsEquipped(form_item)
                ; any playable item is fair game, but only equipped unplayables are accounted for
                ref_junk.AddItem(form_item, ref_actor.GetItemCount(form_item), true)
            endIf
        endIf
        idx_forms += 1
    endWhile

    ; cleaning up the inventory of any junk is essential to controlling the outfit
    idx_forms = 0
    num_forms = ref_junk.GetNumItems()
    while idx_forms < num_forms
        form_item = ref_junk.GetNthForm(idx_forms)
        num_items = ref_junk.GetItemCount(form_item)
        ref_actor.RemoveItem(form_item, num_items, true, ref_junk)
        idx_forms += 1
    endWhile

    ; and now we can cleanly add all the outfit items
    idx_forms = 0
    num_forms = p_cache_outfit.GetNumItems()
    while idx_forms < num_forms
        form_item = p_cache_outfit.GetNthForm(idx_forms)
        num_items = p_cache_outfit.GetItemCount(form_item)
        ref_actor.AddItem(form_item, num_items, true)
        idx_forms += 1
    endWhile

    idx_forms = 0
    num_forms = p_cache_self.GetNumItems()
    while idx_forms < num_forms
        form_item = p_cache_self.GetNthForm(idx_forms)
        num_items = p_cache_self.GetItemCount(form_item)
        ref_actor.AddItem(form_item, num_items, true)
        idx_forms += 1
    endWhile

    ; doing this allows us to render all at once, which is far more efficient
    ref_actor.SetPlayerTeammate(true, true)
    ref_actor.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_actor.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)

    ; make sure to restore render status
    if !is_teammate
        ref_actor.SetPlayerTeammate(false)
    endIf
endFunction

function p_Set_Dead(Actor ref_actor)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items_outfit
    int num_items_actor
    ObjectReference ref_trash = CONTAINERS.Create_Temp()

    ; we copy one of each item, because it's dangerous to remove them within a loop
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form && ref_actor.IsEquipped(ref_form)
            ref_trash.AddItem(ref_form, 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; remove any items no longer in outfit, but the engine won't equip anything new
    idx_forms = 0
    num_forms = ref_trash.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_trash.GetNthForm(idx_forms)
        num_items_outfit = self.GetItemCount(ref_form)
        num_items_actor = ref_actor.GetItemCount(ref_form)
        if num_items_actor > num_items_outfit
            ref_actor.RemoveItem(ref_form, num_items_actor - num_items_outfit, true, ref_trash)
        endIf
        idx_forms += 1
    endWhile
endFunction

; Public Methods
bool function Exists()
    return p_is_created
endFunction

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
    Cache_Self()
endFunction

function Cache_Outfit(Actor ref_actor)
    int idx_forms
    int num_forms
    Form form_item

    p_cache_outfit = CONTAINERS.Create_Temp()

    Outfit outfit_
    if p_code_create == CODES.OUTFIT_VANILLA
        outfit_ = ACTORS.Get_Base_Outfit(ref_actor)
    elseIf p_code_create == CODES.OUTFIT_DEFAULT
        outfit_ = NPCS.Get_Base_Outfit(ref_actor)
    endIf

    if !outfit_
        ; there is nothing to cache for pure outfit2s
        ; or else the actor has no outfit
        return
    endIf

    ; the idea is to form the outfit ourselves and avoid SetOutfit
    ; because it always adds items that are out of the player's control.
    ; our custom outfits will probably never have anything unplayable
    ; but we'll allow unplayable items in others' outfits
    idx_forms = 0
    num_forms = outfit_.GetNumParts()
    while idx_forms < num_forms
        form_item = outfit_.GetNthPart(idx_forms)
        p_cache_outfit.AddItem(form_item, 1, true); will expand LeveledItems!
        idx_forms += 1
    endWhile
endFunction

function Cache_Self()
    int idx_forms
    int num_forms
    Form form_item
    int num_items
    ObjectReference ref_item

    p_cache_self = CONTAINERS.Create_Temp()

    ; we don't want to combine the vanilla outfit items with outfit2's
    ; because we don't want to get different leveled items every time
    ; outfit2 changes.
    idx_forms = 0
    num_forms = self.GetNumItems()
    while idx_forms < num_forms
        form_item = self.GetNthForm(idx_forms)
        num_items = self.GetItemCount(form_item)
        ref_item = form_item as ObjectReference
        if ref_item
            ; we cannot risk removing a quest item, etc.
            form_item = ref_item.GetBaseObject()
        endIf
        p_cache_self.AddItem(form_item, num_items, true)
        idx_forms += 1
    endWhile
endFunction

function Get(Actor ref_actor, ObjectReference ref_inventory)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items

    ; should always refresh cache before defining it, but not
    ; the leveled list, because we always do it on a Set
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)

    ; instead of using GetOutfit, we get what is playable and equipped,
    ; and store non-equipment in inventory to separate it from outfit
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form && ref_form.IsPlayable()
            num_items = ref_actor.GetItemCount(ref_form)
            if ref_actor.IsEquipped(ref_form)
                self.AddItem(ref_form, num_items, true)
            else
                ref_inventory.AddItem(ref_form, num_items, true)
            endIf
        endIf
        idx_forms += 1
    endWhile
endFunction

function Get_Default(Actor ref_actor)
    int idx_forms
    int num_forms
    Form form_item
    int num_items

    ObjectReference ref_defaults = NPCS.Get_Default_Cache(ref_actor)
    if ref_defaults
        idx_forms = 0
        num_forms = ref_defaults.GetNumItems()
        while idx_forms < num_forms
            form_item = ref_defaults.GetNthForm(idx_forms)
            num_items = ref_defaults.GetItemCount(form_item)
            self.AddItem(form_item, num_items, true)
            idx_forms += 1
        endWhile
    endIf
endFunction

function Set(Actor ref_actor, bool do_force = false)
    if !ref_actor
        return
    endIf

    ; by keeping and restoring the cache, we can offer the vanilla outfit and any mod that changes it
    Outfit outfit_vanilla = ACTORS.Get_Base_Outfit(ref_actor)

    p_Set(ref_actor, do_force)
    
    ACTORS.Set_Base_Outfit(ref_actor, outfit_vanilla)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if !Exists()
        return
    endIf

    if self.GetNumItems() >= p_MAX_ITEMS
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Can only have so many items in an outfit.")
    elseIf !form_item || !form_item.IsPlayable()
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Cannot add that item to an outfit.")
    endIf
endEvent
