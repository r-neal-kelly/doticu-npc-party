Scriptname doticu_npcp_funcs extends Quest

; Private Constants
doticu_npcp_data        p_DATA          = none
doticu_npcp_actors      p_ACTORS        = none
doticu_npcp_perks       p_PERKS         = none
doticu_npcp_outfits     p_OUTFITS       = none
doticu_npcp_containers  p_CONTAINERS    = none
doticu_npcp_queues      p_QUEUES        = none
doticu_npcp_tasklists   p_TASKLISTS     = none
doticu_npcp_logs        p_LOGS          = none
doticu_npcp_player      p_PLAYER        = none

; Public Constants
doticu_npcp_actors property ACTORS
    doticu_npcp_actors function Get()
        return p_ACTORS
    endFunction
endProperty

doticu_npcp_perks property PERKS
    doticu_npcp_perks function Get()
        return p_PERKS
    endFunction
endProperty

doticu_npcp_outfits property OUTFITS
    doticu_npcp_outfits function Get()
        return p_OUTFITS
    endFunction
endProperty

doticu_npcp_containers property CONTAINERS
    doticu_npcp_containers function Get()
        return p_CONTAINERS
    endFunction
endProperty

doticu_npcp_queues property QUEUES
    doticu_npcp_queues function Get()
        return p_QUEUES
    endFunction
endProperty

doticu_npcp_tasklists property TASKLISTS
    doticu_npcp_tasklists function Get()
        return p_TASKLISTS
    endFunction
endProperty

doticu_npcp_logs property LOGS
    doticu_npcp_logs function Get()
        return p_LOGS
    endFunction
endProperty

doticu_npcp_player property PLAYER
    doticu_npcp_player function Get()
        return p_PLAYER
    endFunction
endProperty

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_ACTORS = (self as Quest) as doticu_npcp_actors
    p_PERKS = (self as Quest) as doticu_npcp_perks
    p_OUTFITS = (self as Quest) as doticu_npcp_outfits
    p_CONTAINERS = (self as Quest) as doticu_npcp_containers
    p_QUEUES = (self as Quest) as doticu_npcp_queues
    p_TASKLISTS = (self as Quest) as doticu_npcp_tasklists
    p_LOGS = (self as Quest) as doticu_npcp_logs
    p_PLAYER = GetAliasByName("player") as doticu_npcp_player
    ; add greeter sometime probably

    p_ACTORS.f_Link(DATA)
    p_PERKS.f_Link(DATA)
    p_OUTFITS.f_Link(DATA)
    p_CONTAINERS.f_Link(DATA)
    p_QUEUES.f_Link(DATA)
    p_TASKLISTS.f_Link(DATA)
    p_LOGS.f_Link(DATA)
endFunction

function f_Initialize()
    p_ACTORS.f_Initialize()
    p_PERKS.f_Initialize()
    p_OUTFITS.f_Initialize()
    p_CONTAINERS.f_Initialize()
    p_QUEUES.f_Initialize()
    p_TASKLISTS.f_Initialize()
    p_LOGS.f_Initialize()
    p_PLAYER.f_Initialize(p_DATA)
endFunction

function f_Register()
    p_ACTORS.f_Register()
    p_PERKS.f_Register()
    p_OUTFITS.f_Register()
    p_CONTAINERS.f_Register()
    p_QUEUES.f_Register()
    p_TASKLISTS.f_Register()
    p_LOGS.f_Register()
    p_PLAYER.f_Register()
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

; Update Methods
function u_0_1_1()
    p_QUEUES.f_Initialize()
    p_PLAYER.u_0_1_1()
endFunction

function u_0_1_4(doticu_npcp_data DATA)
    p_TASKLISTS.f_Initialize()
    p_PLAYER.u_0_1_4(DATA)
endFunction
