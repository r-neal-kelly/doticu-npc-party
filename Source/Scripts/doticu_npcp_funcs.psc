;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_funcs extends Quest

; Modules
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return (self as Quest) as doticu_npcp_logs
    endFunction
endProperty
doticu_npcp_vectors property VECTORS hidden
    doticu_npcp_vectors function Get()
        return (self as Quest) as doticu_npcp_vectors
    endFunction
endProperty
doticu_npcp_queues property QUEUES hidden
    doticu_npcp_queues function Get()
        return (self as Quest) as doticu_npcp_queues
    endFunction
endProperty
doticu_npcp_tasklists property TASKLISTS hidden
    doticu_npcp_tasklists function Get()
        return (self as Quest) as doticu_npcp_tasklists
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return (self as Quest) as doticu_npcp_containers
    endFunction
endProperty
doticu_npcp_outfits property OUTFITS hidden
    doticu_npcp_outfits function Get()
        return (self as Quest) as doticu_npcp_outfits
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return (self as Quest) as doticu_npcp_actors
    endFunction
endProperty
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return (self as Quest) as doticu_npcp_npcs
    endFunction
endProperty
doticu_npcp_perks property PERKS hidden
    doticu_npcp_perks function Get()
        return (self as Quest) as doticu_npcp_perks
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return (self as Quest) as doticu_npcp_mannequins
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

    LOGS.f_Create(p_DATA)
    VECTORS.f_Create(p_DATA)
    QUEUES.f_Create(p_DATA)
    TASKLISTS.f_Create(p_DATA)
    CONTAINERS.f_Create(p_DATA)
    OUTFITS.f_Create(p_DATA)
    ACTORS.f_Create(p_DATA)
    NPCS.f_Create(p_DATA)
    PERKS.f_Create(p_DATA)
    MANNEQUINS.f_Create(p_DATA)
endFunction

function f_Destroy()
    MANNEQUINS.f_Destroy()
    PERKS.f_Destroy()
    NPCS.f_Destroy()
    ACTORS.f_Destroy()
    OUTFITS.f_Destroy()
    CONTAINERS.f_Destroy()
    TASKLISTS.f_Destroy()
    QUEUES.f_Destroy()
    VECTORS.f_Destroy()
    LOGS.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    LOGS.f_Register()
    VECTORS.f_Register()
    QUEUES.f_Register()
    TASKLISTS.f_Register()
    CONTAINERS.f_Register()
    OUTFITS.f_Register()
    ACTORS.f_Register()
    NPCS.f_Register()
    PERKS.f_Register()
    MANNEQUINS.f_Register()
endFunction

; Public Methods
function Close_Menus()
    int key_menu = Input.GetMappedKey("Tween Menu")
    
    while Utility.IsInMenuMode()
        Input.TapKey(key_menu)
    endWhile
endFunction

bool function Can_Use_Keys()
    return !Utility.IsInMenuMode() && !UI.IsMenuOpen("Dialogue Menu")
endFunction

bool function Can_Render()
    return !Utility.IsInMenuMode()
endFunction

bool function Is_Mod_Installed(string name_mod)
    return Game.GetModByName(name_mod) != 255
endFunction

bool function Maybe_Quest_Item(Form form_item)
    ObjectReference ref_item = form_item as ObjectReference
    if ref_item && ref_item.GetNumReferenceAliases() > 0
        return true
    else
        return false
    endIf
endFunction

function Print_Contents(ObjectReference ref_object)
    string str_contents = ""
    int idx_forms = 0
    int num_forms = ref_object.GetNumItems()
    Form form_form
    int num_form

    str_contents += "[ "

    while idx_forms < num_forms
        form_form = ref_object.GetNthForm(idx_forms)
        if form_form
            num_form = ref_object.GetItemCount(form_form)
            str_contents += form_form.GetName() + " (" + num_form + "),"
        else
            str_contents += "none (0),"
        endIf
        idx_forms += 1
    endWhile

    str_contents += " ]\n"

    MiscUtil.PrintConsole(str_contents)
endFunction

; Update Methods
function u_0_8_3()
    MANNEQUINS.f_Create(p_DATA)
    MANNEQUINS.f_Register()
endFunction
