Scriptname doticu_npcp_outfits extends Quest

; Private Constants
doticu_npcp_data        p_DATA              = none
doticu_npcp_consts      p_CONSTS            = none

Container               p_CONTAINER_OUTFIT  = none
ObjectReference         p_STORAGE           = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
endFunction

function f_Initialize()
    p_CONTAINER_OUTFIT = p_CONSTS.CONTAINER_OUTFIT
    p_STORAGE = p_CONSTS.MARKER_STORAGE
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_outfit function Create(Outfit form_outfit, string str_name = "Outfit")
    doticu_npcp_outfit ref_outfit = p_STORAGE.PlaceAtMe(p_CONTAINER_OUTFIT, 1, true, false) as doticu_npcp_outfit

    ref_outfit.f_Create(p_DATA, form_outfit, str_name)

    return ref_outfit
endFunction

function Destroy(doticu_npcp_outfit ref_outfit)
    ref_outfit.f_Destroy()
endFunction

bool function Is_Valid_Item(Form form_item)
    ;return form_item.IsPlayable() && (form_item as Armor || form_item as Weapon)
    return form_item.IsPlayable(); allows arrows and torches, but maybe allows to many other things
endFunction
