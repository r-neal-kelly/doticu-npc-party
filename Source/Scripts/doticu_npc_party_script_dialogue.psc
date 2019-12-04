Scriptname doticu_npc_party_script_dialogue extends Quest

; Private Constants
doticu_npc_party_script_members p_MEMBERS = none

; Public Constants
doticu_npc_party_script_members property MEMBERS
    doticu_npc_party_script_members function Get()
        return p_MEMBERS
    endFunction
endProperty

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_MEMBERS = DATA.MODS.MEMBERS
endFunction
