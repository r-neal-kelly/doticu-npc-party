Scriptname doticu_npcp_funcs extends Quest

; Private Constants
doticu_npcp_consts      p_CONSTS        = none
doticu_npcp_actors      p_ACTORS        = none
doticu_npcp_perks       p_PERKS         = none
doticu_npcp_outfits     p_OUTFITS       = none
doticu_npcp_containers  p_CONTAINERS    = none
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
function f_Initialize(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_ACTORS = (self as Quest) as doticu_npcp_actors
    p_PERKS = (self as Quest) as doticu_npcp_perks
    p_OUTFITS = (self as Quest) as doticu_npcp_outfits
    p_CONTAINERS = (self as Quest) as doticu_npcp_containers
    p_LOGS = (self as Quest) as doticu_npcp_logs
    p_PLAYER = GetAliasByName("player") as doticu_npcp_player

    p_ACTORS.f_Initialize(DATA)
    p_PERKS.f_Initialize(DATA)
    p_OUTFITS.f_Initialize(DATA)
    p_CONTAINERS.f_Initialize(DATA)
    p_LOGS.f_Initialize(DATA)
    p_PLAYER.f_Initialize(DATA)
endFunction

function f_Register()
    p_ACTORS.f_Register()
    p_PERKS.f_Register()
    p_OUTFITS.f_Register()
    p_CONTAINERS.f_Register()
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

function Open_MCM()
    ; I have no good idea how to get this to happen!
endFunction

bool function Is_Mod_Installed(string name_mod)
    return Game.GetModByName(name_mod) != 255
endFunction
