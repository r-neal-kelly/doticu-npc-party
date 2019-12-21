Scriptname doticu_npcp_outfits extends Quest

; Private Constants
doticu_npcp_data        p_DATA              = none
doticu_npcp_consts      p_CONSTS            = none
doticu_npcp_actor       p_ACTOR2            = none
doticu_npcp_container   p_CONTAINER2        = none

Container               p_CONTAINER_OUTFIT  = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_CONTAINER2 = DATA.MODS.FUNCS.CONTAINER2

    p_CONTAINER_OUTFIT = DATA.CONSTS.CONTAINER_OUTFIT
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_outfit function Create(Outfit form_outfit, string str_name = "Outfit")
    doticu_npcp_outfit ref_outfit = p_CONTAINER2.Create(p_CONTAINER_OUTFIT, true) as doticu_npcp_outfit

    ref_outfit.f_Initialize(p_DATA, form_outfit)
    ref_outfit.f_Register()
    ref_outfit.f_Create(str_name)

    return ref_outfit
endFunction

function Destroy(doticu_npcp_outfit ref_outfit)
    ref_outfit.f_Destroy()
endFunction
