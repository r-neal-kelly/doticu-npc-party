;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_outfit extends ObjectReference

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return doticu_npcp.Funcs().NPCS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return doticu_npcp.Funcs().CONTAINERS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return doticu_npcp.Funcs().LOGS
    endFunction
endProperty

; Private Constants
int property p_MAX_ITEMS hidden
    int function Get()
        return 16; might be able to increase this, now that we have moved outfitting to c++
    endFunction
endProperty

; Private Variables
string                  p_str_name          =    ""
int                     p_code_create       =     0; OUTFIT2_VANILLA, OUTFIT2_DEFAULT
ObjectReference         p_cache_base        =  none

; Native Methods
function Apply_To(Actor ref_actor, ObjectReference ref_pack) native

; Friend Methods
function f_Create(int code_create = 0)
    p_code_create = code_create
    p_cache_base = none
endFunction

function f_Destroy()
    doticu_npcp.Object_Ref_Categorize(self)

    if p_cache_base
        p_cache_base.Disable()
        p_cache_base.Delete()
    endIf
endFunction

; Public Methods
string function Name()
    return p_str_name
endFunction

function Rename(string str_name)
    p_str_name = str_name
    self.SetDisplayName(p_str_name, true)
endFunction

function Put()
    self.SetDisplayName(p_str_name, true)
    self.Activate(doticu_npcp_consts.Player_Actor())
    FUNCS.Wait_Out_Of_Menu(0.1)
endFunction

function Cache_Vanilla_Static(Outfit outfit_vanilla)
    ; this should just copy what the actor has equipped at this point, because our Set_Outfit improves the original.
    ; this way it won't relevel the outfit items and the user will get what they saw the first time
    if !outfit_vanilla
        return
    endIf

    ; make sure this container is persistent from now on.
    if p_cache_base
        p_cache_base.Disable()
        p_cache_base.Delete()
    endIf
    p_cache_base = CONTAINERS.Create_Perm()

    ; it's nice to have vanilla leveled items cached so they remain unchanged
    ; this is also an avenue to getting unplayable items into the outfit
    int idx_forms = outfit_vanilla.GetNumParts()
    Form form_item
    while idx_forms > 0
        idx_forms -= 1
        form_item = outfit_vanilla.GetNthPart(idx_forms)
        if form_item != doticu_npcp_consts.Blank_Armor() as Form
            p_cache_base.AddItem(form_item, 1, true); will expand LeveledItems!
        endIf
    endWhile
endFunction

function Cache_Vanilla_Dynamic(Actor ref_actor)
    if !ref_actor
        return
    endIf

    ; make sure this container is persistent from now on.
    if p_cache_base
        p_cache_base.Disable()
        p_cache_base.Delete()
    endIf
    p_cache_base = CONTAINERS.Create_Perm()

    ; not only does this do the heavy lifting, but it caches what the actor is wearing
    ; so that when a vanilla outfit change happens, leveled items wont be calc'd twice.
    ; also, we can trust more in our override of Actor.SetOutfit, and we won't get non-outfit items
    doticu_npcp.Actor_Cache_Worn(ref_actor, doticu_npcp_consts.Blank_Armor(), p_cache_base)
endFunction

function Try_Cache_Vanilla(Outfit outfit_vanilla)
    ; this is just a way to do asyncronous updating for 0.9.0
    if !p_cache_base && (p_code_create == doticu_npcp_codes.OUTFIT2_VANILLA() || p_code_create == doticu_npcp_codes.OUTFIT2_DEFAULT())
        p_cache_base = CONTAINERS.Create_Perm()
        Cache_Vanilla_Static(outfit_vanilla)
    endIf
endFunction

function Get(Actor ref_actor, ObjectReference ref_pack)
    doticu_npcp.Object_Ref_Categorize(self)
    doticu_npcp.Actor_Cache_Inventory(ref_actor, doticu_npcp_consts.Blank_Armor(), self, ref_pack); maybe buffer with ref_transfer
endFunction

function Get_Default(Actor ref_actor)
    ObjectReference ref_default = CONTAINERS.Create_Temp()
    ObjectReference ref_trash = CONTAINERS.Create_Temp()

    doticu_npcp.Actor_Cache_Static_Inventory(ref_actor, doticu_npcp_consts.Blank_Armor(), ref_default)
    doticu_npcp.Object_Ref_Remove_Unwearable(ref_default, ref_trash)
    ref_default.RemoveAllItems(self, false, true)

    CONTAINERS.Destroy_Temp(ref_default)
    CONTAINERS.Destroy_Temp(ref_trash)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if self.GetNumItems() >= p_MAX_ITEMS
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Can only have so many items in an outfit.")
    elseIf !form_item || p_code_create != doticu_npcp_codes.OUTFIT2_DEFAULT() && !form_item.IsPlayable()
        ; now we let unplayables into default outfit's self container
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Cannot add that item to an outfit.")
    endIf
endEvent
