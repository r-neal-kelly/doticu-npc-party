Scriptname doticu_npcp_funcs extends Quest

; Modules
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return (self as Quest) as doticu_npcp_logs
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
doticu_npcp_perks property PERKS hidden
    doticu_npcp_perks function Get()
        return (self as Quest) as doticu_npcp_perks
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
    QUEUES.f_Create(p_DATA)
    TASKLISTS.f_Create(p_DATA)
    CONTAINERS.f_Create(p_DATA)
    OUTFITS.f_Create(p_DATA)
    ACTORS.f_Create(p_DATA)
    PERKS.f_Create(p_DATA)
endFunction

function f_Destroy()
    PERKS.f_Destroy()
    ACTORS.f_Destroy()
    OUTFITS.f_Destroy()
    CONTAINERS.f_Destroy()
    TASKLISTS.f_Destroy()
    QUEUES.f_Destroy()
    LOGS.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    LOGS.f_Register()
    QUEUES.f_Register()
    TASKLISTS.f_Register()
    CONTAINERS.f_Register()
    OUTFITS.f_Register()
    ACTORS.f_Register()
    PERKS.f_Register()
endFunction

; Public Methods
function Close_Menus()
    int key_menu = Input.GetMappedKey("Tween Menu")
    
    while Utility.IsInMenuMode()
        Input.TapKey(key_menu)
    endWhile
endFunction

bool function Is_Mod_Installed(string name_mod)
    return Game.GetModByName(name_mod) != 255
endFunction
