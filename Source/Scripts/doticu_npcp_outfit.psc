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
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
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
Form                    p_form_linchpin     =  none

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
    int idx_forms
    Form form_item

    ; we need to make sure that the default outfit is equipped, because a mod may have changed it
    if ACTORS.Get_Base_Outfit(ref_actor) != NPCS.Get_Default_Outfit(ref_actor)
        return true
    elseIf ref_actor.GetItemCount(CONSTS.ARMOR_BLANK as Form) < 1
        return true
    endIf

    ; ref_actor may have items that aren't in the oufit
    idx_forms = ref_actor.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item && !(form_item as ObjectReference) && form_item != CONSTS.ARMOR_BLANK as Form
            ; we completely avoid any references and leave them alone.
            ; we need to keep the linchpin to avoid engine refreshing outfit.
            if form_item.IsPlayable() || ref_actor.IsEquipped(form_item)
                ; any playable item is fair game, but only equipped unplayables are accounted for
                if p_cache_outfit.GetItemCount(form_item) < 1 && p_cache_self.GetItemCount(form_item) < 1
                    ;/MiscUtil.PrintConsole("ref actor has items not in outfit")
                    MiscUtil.PrintConsole(form_item.GetName())
                    MiscUtil.PrintConsole("Actor Cache: ")
                    FUNCS.Print_Contents(ref_actor)
                    MiscUtil.PrintConsole("Outfit Cache: ")
                    FUNCS.Print_Contents(p_cache_outfit)
                    MiscUtil.PrintConsole("Self Cache: ")
                    FUNCS.Print_Contents(p_cache_self)/;

                    return true
                endIf
            endIf
        endIf
    endWhile

    ; ref_actor may be missing items that are in the outfit
    idx_forms = p_cache_outfit.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = p_cache_outfit.GetNthForm(idx_forms)
        if ref_actor.GetItemCount(form_item) != p_cache_outfit.GetItemCount(form_item) + p_cache_self.GetItemCount(form_item)
            ;/MiscUtil.PrintConsole("ref actor and outfit cache mismatch")
            MiscUtil.PrintConsole(form_item.GetName())
            MiscUtil.PrintConsole("actor: " + ref_actor.GetItemCount(form_item) + ", outfit: " + p_cache_outfit.GetItemCount(form_item))
            MiscUtil.PrintConsole("Actor Cache: ")
            FUNCS.Print_Contents(ref_actor)
            MiscUtil.PrintConsole("Outfit Cache: ")
            FUNCS.Print_Contents(p_cache_outfit)/;

            return true
        endIf
    endWhile

    idx_forms = p_cache_self.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = p_cache_self.GetNthForm(idx_forms)
        if ref_actor.GetItemCount(form_item) != p_cache_outfit.GetItemCount(form_item) + p_cache_self.GetItemCount(form_item)
            ;/MiscUtil.PrintConsole("ref actor and self cache mismatch")
            MiscUtil.PrintConsole(form_item.GetName())
            MiscUtil.PrintConsole("actor: " + ref_actor.GetItemCount(form_item) + ", self: " + p_cache_self.GetItemCount(form_item))
            MiscUtil.PrintConsole("Actor Cache: ")
            FUNCS.Print_Contents(ref_actor)
            MiscUtil.PrintConsole("Self Cache: ")
            FUNCS.Print_Contents(p_cache_self)/;

            return true
        endIf
    endWhile

    return false
endFunction

function p_Set(Actor ref_actor, bool do_force = false)
    ; just in case
    if !p_cache_outfit
        Cache_Outfit(none)
    endIf
    if !p_cache_self
        Cache_Self()
    endIf

    if ACTORS.Is_Dead(ref_actor)
        p_Set_Dead(ref_actor)
        return
    endIf

    if !do_force && !p_Has_Changed(ref_actor)
        ACTORS.Update_Equipment(ref_actor)
        return
    endIf

    int idx_forms
    Form form_item
    bool is_teammate = ref_actor.IsPlayerTeammate()

NPCS.Lock_Base(ref_actor)
    ; this ensures that our modded outfit is worn. we need that blank armor.
    ; we can speed up this check by looking for blank armor on the base outfit 
    Outfit outfit_vanilla = ACTORS.Get_Base_Outfit(ref_actor)
    Outfit outfit_default = NPCS.Get_Default_Outfit(ref_actor)
    if outfit_vanilla != outfit_default || !ref_actor.IsEquipped(CONSTS.ARMOR_BLANK)
        ; IsEquipped might be too harsh, but I think it might be necessary,
        ; instead of just check to see if they have the blank armor at all
        ref_actor.SetOutfit(CONSTS.OUTFIT_TEMP)
        doticu_npcp.Outfit_Add_Item(outfit_default, CONSTS.ARMOR_BLANK as Form)
        ref_actor.SetOutfit(outfit_default)
    endIf
NPCS.Unlock_Base(ref_actor)

    ; this will stop the actor from rendering while we manage its inventory
    ref_actor.SetPlayerTeammate(false, false)

    ; this will completely wipe the inventory of everything but tokens
    ; it may be a hit on performace to call out to this function. will see
    OUTFITS.Remove_Junk(ref_actor)

    ; and now we can cleanly add all the outfit items
    idx_forms = p_cache_outfit.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = p_cache_outfit.GetNthForm(idx_forms)
        ref_actor.AddItem(form_item, p_cache_outfit.GetItemCount(form_item), true)
    endWhile

    idx_forms = p_cache_self.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = p_cache_self.GetNthForm(idx_forms)
        ref_actor.AddItem(form_item, p_cache_self.GetItemCount(form_item), true)
    endWhile

    ; doing this allows us to render all at once, which is far more efficient
    while !p_DATA.VARS.is_updating && Utility.IsInMenuMode()
        ; we wait so that the render actually happens.
        Utility.Wait(0.1)
    endWhile
    ref_actor.SetPlayerTeammate(true, true)
    ref_actor.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_actor.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)

    ; make sure to restore render status
    if !is_teammate
        ref_actor.SetPlayerTeammate(false, false)
    endIf
endFunction

function p_Set_Dead(Actor ref_actor)
    int idx_forms
    Form form_item
    ObjectReference ref_trash = CONTAINERS.Create_Temp()

    ; the engine won't equip new items, so we only remove items no longer in cache_self or cache_outfit
    idx_forms = ref_actor.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item && form_item.IsPlayable() && !(form_item as ObjectReference)
            ; the player can't remove unplayable items and we cannot risk removing a quest item, etc.
            if p_cache_self.GetItemCount(form_item) < 1 && p_cache_outfit.GetItemCount(form_item) < 1
                ref_actor.RemoveItem(form_item, ref_actor.GetItemCount(form_item), true, ref_trash)
            endIf
        endIf
    endWhile

    ref_trash.Disable()
    ref_trash.Delete()
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

function Put()
    self.SetDisplayName(p_str_name, true)
    self.Activate(CONSTS.ACTOR_PLAYER)
    Utility.Wait(0.1)
    Cache_Self()
endFunction

function Cache_Outfit(Outfit outfit_vanilla)
    int idx_forms
    Form form_item

    ; make sure this exists
    if p_cache_outfit
        p_cache_outfit.Disable()
        p_cache_outfit.Delete()
    endIf
    p_cache_outfit = CONTAINERS.Create_Temp()

    if !outfit_vanilla
        ; there is nothing to cache for pure outfit2s
        return
    endIf

    ; the idea is to form the outfit ourselves and avoid SetOutfit
    ; because it always adds items that are out of the player's control.
    ; our custom outfits will probably never have anything unplayable
    ; but we'll allow unplayable items in others' outfits
    idx_forms = outfit_vanilla.GetNumParts()
    while idx_forms > 0
        idx_forms -= 1
        form_item = outfit_vanilla.GetNthPart(idx_forms)
        if form_item != CONSTS.ARMOR_BLANK as Form
            p_cache_outfit.AddItem(form_item, 1, true); will expand LeveledItems!
        endIf
    endWhile
endFunction

function Cache_Self()
    int idx_forms
    Form form_item
    int num_items
    ObjectReference ref_item

    ; make sure this exists
    if p_cache_self
        p_cache_self.Disable()
        p_cache_self.Delete()
    endIf
    p_cache_self = CONTAINERS.Create_Temp()

    ; we don't want to combine the vanilla outfit items with outfit2's
    ; because we don't want to get different leveled items every time
    ; outfit2 changes.
    idx_forms = self.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = self.GetNthForm(idx_forms)
        if form_item
            ; we need to work with this form before it might be changed
            num_items = self.GetItemCount(form_item)
            ref_item = form_item as ObjectReference
            if ref_item
                ; we cannot risk removing a quest item, etc.
                form_item = ref_item.GetBaseObject()
            endIf
            p_cache_self.AddItem(form_item, num_items, true)
        endIf
    endWhile
endFunction

function Get(Actor ref_actor, ObjectReference ref_inventory)
    int idx_forms
    Form form_item
    int num_items
    bool is_equipped
    ObjectReference ref_item

    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)

    idx_forms = ref_actor.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item
            ; we need to work with this form before it might be changed
            num_items = ref_actor.GetItemCount(form_item)
            is_equipped = ref_actor.IsEquipped(form_item)
            ref_item = form_item as ObjectReference
            if ref_item
                ; we cannot risk removing a quest item, etc.
                form_item = ref_item.GetBaseObject()
            endIf
            if form_item.IsPlayable()
                if is_equipped
                    self.AddItem(form_item, num_items, true)
                else
                    ref_inventory.AddItem(form_item, num_items, true)
                endIf
            endIf
        endIf
    endWhile
endFunction

function Get_Default(Actor ref_actor)
    int idx_forms
    Form form_item
    int num_items

    ObjectReference ref_defaults = NPCS.Get_Default_Cache(ref_actor)
    if ref_defaults
        idx_forms = ref_defaults.GetNumItems()
        while idx_forms > 0
            idx_forms -= 1
            form_item = ref_defaults.GetNthForm(idx_forms)
            num_items = ref_defaults.GetItemCount(form_item)
            self.AddItem(form_item, num_items, true)
        endWhile
    endIf
endFunction

function Set(Actor ref_actor, bool do_force = false)
    if ref_actor
        p_Set(ref_actor, do_force)
    endIf
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if !Exists()
        return
    endIf

    if self.GetNumItems() >= p_MAX_ITEMS
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Can only have so many items in an outfit.")
    elseIf !form_item || p_code_create != CODES.OUTFIT_DEFAULT && !form_item.IsPlayable()
        ; now we let unplayables into default outfit's self container
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Cannot add that item to an outfit.")
    endIf
endEvent
