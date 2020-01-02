Scriptname doticu_npcp_perk_kiss extends Perk hidden

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_perks property PERKS hidden
    doticu_npcp_perks function Get()
        return p_DATA.MODS.FUNCS.PERKS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          = none

; Private Variables
bool                p_is_created    = false

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
function Kiss_Thrall(ObjectReference ref_target, Actor _)
    Actor ref_thrall = ref_target as Actor

    if !ref_thrall || !ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
        return
    endIf

    Game.ForceThirdPerson()

    PERKS.Remove_Perk(CONSTS.PERK_KISS_THRALL)
    ref_thrall.AddToFaction(CONSTS.FACTION_DLC1_THRALL)

    if FUNCS.Is_Mod_Installed("Better Vampires.esp")
        ref_thrall.SetGhost(true); stops further dialogs
        ref_thrall.SetActorValue("Variable08", 8); cancels limit
        (CONSTS.PERK_VAMPIRE_FEED as PRKF_VampireFeedBeds_000CF02C).Fragment_15(ref_thrall, none)
        ref_thrall.SetActorValue("Variable08", 8)
        ref_thrall.SetGhost(false)
    elseIf ACTORS.Is_Dead(ref_thrall)
        ; do cannibal instead, or make another perk
    else
        CONSTS.ACTOR_PLAYER.StartVampireFeed(ref_thrall)
        CONSTS.SCRIPT_PLAYER_VAMPIRE_QUEST.VampireFeed()
    endIf

    ref_thrall.RemoveFromFaction(CONSTS.FACTION_DLC1_THRALL)
    PERKS.Add_Perk(CONSTS.PERK_KISS_THRALL)
endFunction
