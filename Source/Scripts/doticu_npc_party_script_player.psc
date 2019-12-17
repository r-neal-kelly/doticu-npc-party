Scriptname doticu_npc_party_script_player extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      p_CONSTS        = none
doticu_npc_party_script_funcs       p_FUNCS         = none
doticu_npc_party_script_actor       p_ACTOR2        = none
doticu_npc_party_script_followers   p_FOLLOWERS     = none
Actor                               p_REF_PLAYER    = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CONSTS = DATA.CONSTS
    p_FUNCS = DATA.MODS.FUNCS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_REF_PLAYER = DATA.CONSTS.ACTOR_PLAYER

    Add_Perk(p_CONSTS.PERK_KISS_THRALL); should this be added here?
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    p_REF_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    p_REF_PLAYER.RemovePerk(perk_to_remove)
endFunction

function Kiss_Thrall(Actor ref_thrall)
    if !p_ACTOR2.Is_Vampire(p_REF_PLAYER)
        return
    endIf

    Remove_Perk(p_CONSTS.PERK_KISS_THRALL)

    if p_FUNCS.Is_Mod_Installed("Better Vampires.esp")
        ref_thrall.SetGhost(true); stops further dialogs
        ref_thrall.AddToFaction(p_CONSTS.FACTION_DLC1_THRALL); enables functionality
        ref_thrall.SetActorValue("Variable08", 8); cancels limit
        (p_CONSTS.PERK_VAMPIRE_FEED as PRKF_VampireFeedBeds_000CF02C).Fragment_15(ref_thrall, none)
        ref_thrall.SetActorValue("Variable08", 8)
        ref_thrall.RemoveFromFaction(p_CONSTS.FACTION_DLC1_THRALL)
        ref_thrall.SetGhost(false)
    elseIf p_ACTOR2.Is_Dead(ref_thrall)
        ; do cannibal instead
    else
        p_REF_PLAYER.StartVampireFeed(ref_thrall)
        p_CONSTS.SCRIPT_PLAYER_VAMPIRE_QUEST.VampireFeed()
    endIf

    Add_Perk(p_CONSTS.PERK_KISS_THRALL)
endFunction

; Events
event OnPlayerLoadGame()
    Utility.Wait(0.5)
    ; Send ModEvent
endEvent

event OnCombatStateChange()
endEvent
