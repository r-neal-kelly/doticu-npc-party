Scriptname doticu_npcp_container_outfit extends ObjectReference

; Private Constants
doticu_npc_party_script_logs    p_LOGS      = none

Outfit                          p_OUTFIT    = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, Outfit FORM_OUTFIT)
    p_LOGS = DATA.MODS.FUNCS.LOGS

    p_OUTFIT = FORM_OUTFIT
endFunction

function f_Register()
endFunction

; Public Methods
Outfit function Get_Outfit()
    return p_OUTFIT
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if form_item as Armor == none
        RemoveItem(form_item, count_item, true, ref_container_source)
        p_LOGS.Create_Note("Can only add apparel to an outfit.")
    endIf
endEvent
