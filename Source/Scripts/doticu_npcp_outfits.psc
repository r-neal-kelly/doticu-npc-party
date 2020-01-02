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

; Public Constants
ObjectReference property OBJECT_STORAGE hidden
    ObjectReference function Get()
        return CONSTS.MARKER_STORAGE
    endFunction
endProperty
Container property CONTAINER_OUTFIT hidden
    Container function Get()
        return CONSTS.CONTAINER_OUTFIT
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

; Public Methods
doticu_npcp_outfit function Create(Outfit form_outfit, string str_name = "Outfit")
    doticu_npcp_outfit ref_outfit = OBJECT_STORAGE.PlaceAtMe(CONTAINER_OUTFIT, 1, true, false) as doticu_npcp_outfit

    ref_outfit.f_Create(p_DATA, form_outfit, str_name)
    ref_outfit.f_Register()

    return ref_outfit
endFunction

function Destroy(doticu_npcp_outfit ref_outfit)
    ref_outfit.f_Destroy()
endFunction

bool function Is_Valid_Item(Form form_item)
    ;return form_item.IsPlayable() && (form_item as Armor || form_item as Weapon)
    return form_item.IsPlayable(); allows arrows and torches, but maybe allows to many other things
endFunction
