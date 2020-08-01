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
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

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
    doticu_npcp_outfit ref_outfit = CONSTS.MARKER_STORAGE.PlaceAtMe(CONSTS.CONTAINER_OUTFIT, 1, true, false) as doticu_npcp_outfit

    ; this can prevent a ctd
    FUNCS.Wait(0.1)

    if VARS.fill_outfits && form_container != CONSTS.CONTAINER_OUTFIT
        ; there is a horrible bug where a container that spawns with a leveled list inside
        ; miscounts GetItemCount when the player is not in the same cell it spawned in. so
        ; we spawn items in variant outfits in a temp container and move them to the outfit
        ObjectReference ref_temp = CONSTS.ACTOR_PLAYER.PlaceAtMe(form_container, 1, false, false)
        FUNCS.Wait(0.1)
        ref_temp.RemoveAllItems(ref_outfit, false, true); we should make a c++ call to make sure that all items are removed?
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
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name, doticu_npcp_codes.OUTFIT2_VANILLA())
endFunction

doticu_npcp_outfit function Create_Default(string str_name = "Default Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name, doticu_npcp_codes.OUTFIT2_DEFAULT())
endFunction

function Destroy(doticu_npcp_outfit ref_outfit)
    if ref_outfit
        ref_outfit.f_Destroy()
        ref_outfit.Disable()
        ref_outfit.Delete()
    endIf
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

    ; this also fufills VARS.clone_outfit == doticu_npcp_codes.OUTFIT_BASE()
    NPCS.Apply_Default_Outfit(ref_clone)

    if VARS.clone_outfit == doticu_npcp_codes.OUTFIT_REFERENCE()
        ; this will stop the actor from rendering while we manage its inventory
        bool is_teammate = ref_clone.IsPlayerTeammate()
        ref_clone.SetPlayerTeammate(false, false)

        ; does all the heavy lifting of removing unfit items and adding outfit items
        doticu_npcp.Actor_Set_Outfit2(ref_clone, CONSTS.ARMOR_BLANK, none, ref_orig, ref_junk)

        ; doing this allows us to render all at once, which is far more efficient
        ref_clone.SetPlayerTeammate(true, true)
        ref_clone.AddItem(CONSTS.WEAPON_BLANK, 1, true)
        ref_clone.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)

        ; make sure to restore render status
        if !is_teammate
            ref_clone.SetPlayerTeammate(false, false)
        endIf
    endIf

    CONTAINERS.Destroy_Temp(ref_junk)
endFunction
