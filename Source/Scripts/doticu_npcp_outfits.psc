Scriptname doticu_npcp_outfits extends Quest

; Private Constants
doticu_npcp_data        p_DATA              = none
doticu_npcp_containers  p_CONTAINERS        = none

Container               p_CONTAINER_OUTFIT  = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONTAINERS = DATA.MODS.FUNCS.CONTAINERS

    p_CONTAINER_OUTFIT = DATA.CONSTS.CONTAINER_OUTFIT
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_outfit function Create(string str_name = "Outfit")
    doticu_npcp_outfit ref_outfit = p_CONTAINERS.Create(p_CONTAINER_OUTFIT, true) as doticu_npcp_outfit

    ref_outfit.f_Initialize(p_DATA)
    ref_outfit.f_Register()
    ref_outfit.f_Create(str_name)

    return ref_outfit
endFunction

function Destroy(doticu_npcp_outfit ref_outfit)
    ref_outfit.f_Destroy()
endFunction
