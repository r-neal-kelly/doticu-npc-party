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

function p_Update_Actors(Form[] arr_actors, Outfit outfit_)
    ; can't have an array with length 0, so we check
    if arr_actors.length == 1 && arr_actors[0] == none
        return
    endIf

    int idx_actors = arr_actors.length
    Actor ref_actor
    
    while idx_actors > 0
        idx_actors -= 1
        ref_actor = arr_actors[idx_actors] as Actor
        if ACTORS.Is_Alive(ref_actor) && !MEMBERS.Has_Member(ref_actor)
            ref_actor.SetOutfit(CONSTS.OUTFIT_EMPTY)
            ref_actor.SetOutfit(outfit_)
        endIf
    endWhile
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
    endIf
endFunction

ObjectReference function Get_Default_Cache(Actor ref_actor, Outfit outfit_default)
    ; the point of this function is to have a goto container that
    ; has most of the loose outfit items on an npc. it's intended
    ; to be created the first time they are added into the system.
    ; part of the reason we are doing this is because some npcs
    ; don't have default outfits, especially follower mods.
    ; sometimes they have unplayable equipment, and this is removed
    ; in unvanilla outfits because the player can't manipulate them

    int idx_forms
    int num_forms
    Form form_item
    int num_items
    ObjectReference ref_item
    ObjectReference ref_outfit = CONTAINERS.Create_Temp()
    ObjectReference ref_cache = CONTAINERS.Create_Temp()

    if outfit_default
        ; we cache because if anything in actor inventory is in here, we can
        ; ignore it as we use the outfit_default itself in the outfit algorithm
        idx_forms = 0
        num_forms = outfit_default.GetNumParts()
        while idx_forms < num_forms
            form_item = outfit_default.GetNthPart(idx_forms)
            ref_outfit.AddItem(form_item, 1, true); will expand LeveledItems!
            idx_forms += 1
        endWhile
    endIf

    ; we basically want every item in the inventory that is not an outfit item yet equips
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item
            num_items = ref_actor.GetItemCount(form_item)
            ref_item = form_item as ObjectReference
            if ref_item
                ; we cannot risk removing a quest item, etc.
                form_item = ref_item.GetBaseObject()
            endIf
            if ref_outfit.GetItemCount(form_item) < 1
                if (form_item as Armor) || (form_item as Weapon) || (form_item as Ammo)
                    ; we don't bother with Light, or other possible equips
                    ref_cache.AddItem(form_item, num_items, true)
                endIf
            endIf
        endIf
        idx_forms += 1
    endWhile

    return ref_cache
endFunction

function Outfit_Clone(Actor ref_clone, Actor ref_original)
    ; sometimes a crash occurs when a clone receives two of the same weapon
    ; and then a call to SetOutfit??? e.g. Sinmir. probably has something
    ; to do with outfits that contain weapons. setting base outfit before
    ; cloning does't seem to stop it.
    ObjectReference ref_temp = CONTAINERS.Create_Temp()
    ref_clone.RemoveAllItems(ref_temp, false, false)

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_original)
    if !ref_member || VARS.clone_outfit == CODES.OUTFIT_BASE
        ; it helps to clear the outfit before trying to normalize items
        ; *without* this, sometimes a clone will appear totally naked
        ref_clone.SetOutfit(CONSTS.OUTFIT_EMPTY)

        Outfit outfit_base = NPCS.Get_Base_Outfit(ref_clone)
        if outfit_base
            ; this correctly sets their inventory so they won't lack anything
            ref_temp.RemoveAllItems(ref_clone, false, false); hopefully this won't cause a crash down the line

            ; actually sets the outfit
            ref_clone.SetOutfit(outfit_base)

            ; sometimes they won't equip their gear
            ACTORS.Update_Equipment(ref_clone)

            ; sometimes we get duped weapons
        endIf
    elseIf VARS.clone_outfit == CODES.OUTFIT_REFERENCE
        ; we don't reset inventory, because we want exactly what
        ; is in the outfit, which may or may not have weapons
        ref_member.Get_Current_Outfit2().Set(ref_clone)

        ; we are still getting duped weapons atm, but would have to loop
    endIf

    ; we do both just in case, because they may not share the same outfit base
    ACTORS.Set_Base_Outfit(ref_original, NPCS.Get_Default_Outfit(ref_original))
    ACTORS.Set_Base_Outfit(ref_clone, NPCS.Get_Default_Outfit(ref_clone))
endFunction

function Outfit_Clone_Default(Actor ref_clone, Outfit outfit_default)
    if !ref_clone || !outfit_default
        return
    endIf

    ; can help to prevent crash with clones
    ObjectReference ref_temp = CONTAINERS.Create_Temp()
    ref_clone.RemoveAllItems(ref_temp, false, false)
    ;ref_temp.RemoveAllItems(ref_clone, false, false)

    ref_clone.SetOutfit(CONSTS.OUTFIT_EMPTY)
    ref_clone.SetOutfit(outfit_default)

    ACTORS.Update_Equipment(ref_clone)
endFunction

function Update_Base(Actor ref_actor)
    ; this is to ensure that npcs who have been cloned are putting on their outfits. there
    ; is a bug in the engine which sticks and causes cloned npcs to be naked when they
    ; are given a new outfit form that has any of the same items as the previous one.
    ; also, this allows us to dress non-members with their default outfits

    Outfit base_outfit = NPCS.Get_Base_Outfit(ref_actor)
    if base_outfit
        Form[] arr_origs = NPCS.Get_Originals(ref_actor)
        Form[] arr_clones = NPCS.Get_Clones(ref_actor)

        ; in here, we may be able to opt for updating with cached base or current vanilla

        NPCS.Cleanup_Base(ref_actor)
        p_Update_Actors(arr_origs, base_outfit)
        p_Update_Actors(arr_clones, base_outfit)

        ACTORS.Set_Base_Outfit(ref_actor, NPCS.Get_Default_Outfit(ref_actor))
    endIf
endFunction

function Restore_Actor(Actor ref_actor)
    if ACTORS.Is_Alive(ref_actor)
        Outfit outfit_default = NPCS.Get_Base_Outfit(ref_actor)
        if outfit_default
            ref_actor.SetOutfit(CONSTS.OUTFIT_EMPTY)
            ref_actor.SetOutfit(outfit_default)
            ACTORS.Set_Base_Outfit(ref_actor, NPCS.Get_Default_Outfit(ref_actor))
        endIf
    endIf
endFunction
