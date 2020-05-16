;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_outfits extends Quest

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
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
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
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA          =  none

; Private Variables
bool                    p_is_created    = false

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

function f_Unregister()
endFunction

; Private Methods
doticu_npcp_outfit function p_Create(Container form_container, string str_name, int code_create = 0)
    doticu_npcp_outfit ref_outfit = CONSTS.MARKER_STORAGE.PlaceAtMe(CONSTS.CONTAINER_OUTFIT, 1, false, false) as doticu_npcp_outfit
    
    ; this can prevent a ctd
    Utility.Wait(0.1)

    if VARS.fill_outfits && form_container != CONSTS.CONTAINER_OUTFIT
        ; there is a horrible bug where a container that spawns with a leveled list inside
        ; miscounts GetItemCount when the player is not in the same cell it spawned in. so
        ; we spawn items in variant outfits in a temp container and move them to the outfit
        ObjectReference ref_temp = CONSTS.ACTOR_PLAYER.PlaceAtMe(form_container, 1, false, false)
        Utility.Wait(0.1); trying this to see if it spawns all items now
        ref_temp.RemoveAllItems(ref_outfit, false, true)
    endIf

    ref_outfit.f_Create(p_DATA, str_name, code_create)
    ref_outfit.f_Register()

    return ref_outfit
endFunction

; Public Methods
doticu_npcp_outfit function Create(string str_name = "Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name)
endFunction

doticu_npcp_outfit function Create_Settler(string str_name = "Settler Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_SETTLER, str_name)
endFunction

doticu_npcp_outfit function Create_Thrall(string str_name = "Thrall Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_THRALL, str_name)
endFunction

doticu_npcp_outfit function Create_Immobile(string str_name = "Immobile Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_IMMOBILE, str_name)
endFunction

doticu_npcp_outfit function Create_Follower(string str_name = "Follower Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_FOLLOWER, str_name)
endFunction

doticu_npcp_outfit function Create_Vanilla(string str_name = "Vanilla Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name, CODES.OUTFIT_VANILLA)
endFunction

doticu_npcp_outfit function Create_Default(string str_name = "Default Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name, CODES.OUTFIT_DEFAULT)
endFunction

function Destroy(doticu_npcp_outfit ref_outfit)
    if ref_outfit
        ref_outfit.f_Destroy()
        ref_outfit.Disable()
        ref_outfit.Delete()
    endIf
endFunction

ObjectReference function Get_Default_Cache(Actor ref_actor, Outfit outfit_default)
    ; TODO:
    ; wait. can't we just have an skse function tell us what the default base container items are? we can certainly
    ; add those back without having to cache in that case. that means we could delete default cache array from NPCS
    ; make sure to skip leveled items I think, but look into it more? in any case, we prob. can't leave them as they
    ; are in NPCS, because they were made with CONTAINER.Create_Temp() upto this point, and that did not appear to be safe


    ; the point of this function is to have a goto container that
    ; has most of the loose outfit items on an npc. it's intended
    ; to be created the first time they are added into the system.
    ; part of the reason we are doing this is because some npcs
    ; don't have default outfits, especially follower mods.
    ; sometimes they have unplayable equipment, and this is removed
    ; in unvanilla outfits because the player can't manipulate them

    int idx_forms
    Form form_item
    int num_items
    ObjectReference ref_item
    ObjectReference ref_outfit = CONTAINERS.Create_Temp()
    ObjectReference ref_cache = CONTAINERS.Create_Persistent()

    if outfit_default
        ; we cache because if anything in actor inventory is in here, we can
        ; ignore it as we use the outfit_default itself in the outfit algorithm
        idx_forms = outfit_default.GetNumParts()
        while idx_forms > 0
            idx_forms -= 1
            form_item = outfit_default.GetNthPart(idx_forms)
            ref_outfit.AddItem(form_item, 1, true); will expand LeveledItems!
        endWhile
    endIf

    ; we basically want every item in the inventory that is not an outfit item yet equips
    idx_forms = ref_actor.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item
            ; we need to work with this form before it might be changed
            num_items = ref_actor.GetItemCount(form_item)
            ref_item = form_item as ObjectReference
            if ref_item
                ; we cannot risk removing a quest item, etc.
                form_item = ref_item.GetBaseObject()
            endIf
            if ref_outfit.GetItemCount(form_item) < 1 && form_item != CONSTS.ARMOR_BLANK as Form
                if form_item as Armor || form_item as Weapon || form_item as Ammo
                    ; we don't bother with Light, or other possible equips
                    ref_cache.AddItem(form_item, num_items, true)
                endIf
            endIf
        endIf
    endWhile

    ref_outfit.Disable()
    ref_outfit.Delete()
    ref_outfit = none

    return ref_cache
endFunction

function Outfit_Clone(Actor ref_clone, Actor ref_orig)
    if !ref_clone || !ref_orig
        return
    endIf

    ; this may prevent crashing, when the engine copies a ptr on orig and frees it
    ; RemoveAllItems does not remove unplayable items, so tokens are copied and left
    ; until member funcs clear it.
    ObjectReference ref_junk = CONTAINERS.Create_Temp()
    ref_clone.RemoveAllItems(ref_junk, false, false)

    ; this ensures that our modded outfit is worn, including the blank armor.
    ; this also fufills VARS.clone_outfit == CODES.OUTFIT_BASE
NPCS.Lock_Base(ref_clone)
    Outfit outfit_default = NPCS.Get_Default_Outfit(ref_clone)
    doticu_npcp.Outfit_Add_Item(outfit_default, CONSTS.ARMOR_BLANK)
    ref_clone.SetOutfit(outfit_default)
NPCS.Unlock_Base(ref_clone)

    ; to make sure certain fields in c++ have been allocated
    ref_clone.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_clone.RemoveItem(CONSTS.WEAPON_BLANK, 1, true)

    if VARS.clone_outfit == CODES.OUTFIT_REFERENCE
        ; this will stop the actor from rendering while we manage its inventory
        bool is_teammate = ref_clone.IsPlayerTeammate()
        ref_clone.SetPlayerTeammate(false, false)

        ; does all the heavy lifting of removing unfit items and adding outfit items
        ObjectReference ref_transfer = CONTAINERS.Create_Temp()
        doticu_npcp.Actor_Set_Outfit2(ref_clone, CONSTS.ARMOR_BLANK, none, ref_orig, ref_junk, ref_transfer)
        CONTAINERS.Destroy_Temp(ref_transfer)

        ; doing this allows us to render all at once, which is far more efficient
        ref_clone.SetPlayerTeammate(true, true)
        ref_clone.AddItem(CONSTS.WEAPON_BLANK, 1, true)
        ref_clone.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)

        ; make sure to restore render status
        if !is_teammate
            ref_clone.SetPlayerTeammate(false, false)
        endIf
    endIf

    ; it doesn't hurt to cleanup manually
    CONTAINERS.Destroy_Temp(ref_junk)
endFunction
