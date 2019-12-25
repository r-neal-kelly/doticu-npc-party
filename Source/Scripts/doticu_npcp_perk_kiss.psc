Scriptname doticu_npcp_perk_kiss extends Perk hidden

; Private Constants
doticu_npcp_consts  p_CONSTS        = none
doticu_npcp_funcs   p_FUNCS         = none
doticu_npcp_actors  p_ACTORS        = none
doticu_npcp_perks   p_PERKS         = none

Actor               p_REF_PLAYER    = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_FUNCS = DATA.MODS.FUNCS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_PERKS = DATA.MODS.FUNCS.PERKS
endFunction

function f_Initialize()
    p_REF_PLAYER = p_CONSTS.ACTOR_PLAYER
endFunction

function f_Register()
endFunction

; Public Methods
function Kiss_Thrall(ObjectReference ref_target, Actor _)
    Actor ref_thrall = ref_target as Actor

    if !ref_thrall || !p_ACTORS.Is_Vampire(p_REF_PLAYER)
        return
    endIf

    Game.ForceThirdPerson()

    p_PERKS.Remove_Perk(p_CONSTS.PERK_KISS_THRALL)
    ref_thrall.AddToFaction(p_CONSTS.FACTION_DLC1_THRALL)

    if p_FUNCS.Is_Mod_Installed("Better Vampires.esp")
        ref_thrall.SetGhost(true); stops further dialogs
        ref_thrall.SetActorValue("Variable08", 8); cancels limit
        (p_CONSTS.PERK_VAMPIRE_FEED as PRKF_VampireFeedBeds_000CF02C).Fragment_15(ref_thrall, none)
        ref_thrall.SetActorValue("Variable08", 8)
        ref_thrall.SetGhost(false)
    elseIf p_ACTORS.Is_Dead(ref_thrall)
        ; do cannibal instead, or make another perk
    else
        p_REF_PLAYER.StartVampireFeed(ref_thrall)
        p_CONSTS.SCRIPT_PLAYER_VAMPIRE_QUEST.VampireFeed()
    endIf

    ref_thrall.RemoveFromFaction(p_CONSTS.FACTION_DLC1_THRALL)
    p_PERKS.Add_Perk(p_CONSTS.PERK_KISS_THRALL)
endFunction
