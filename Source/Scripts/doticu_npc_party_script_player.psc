Scriptname doticu_npc_party_script_player extends ReferenceAlias

; Private Constants
doticu_npc_party_script_followers   p_FOLLOWERS     = none
Actor                               p_REF_PLAYER    = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_REF_PLAYER = GetActorReference()
endFunction

; Events
event OnPlayerLoadGame()
endEvent

event OnCombatStateChange()
endEvent
