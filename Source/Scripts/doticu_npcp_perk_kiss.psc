;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_perk_kiss extends Perk hidden

; Modules
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

function f_Unregister()
endFunction

; Public Methods
function Kiss_Thrall(ObjectReference ref_target, Actor _)
    Actor ref_thrall = ref_target as Actor

    if !ref_thrall || !ACTORS.Is_Vampire(doticu_npcp_consts.Player_Actor())
        return
    endIf

    Game.ForceThirdPerson()

    PERKS.Remove_Perk(doticu_npcp_consts.Kiss_Thrall_Perk())
    ref_thrall.AddToFaction(doticu_npcp_consts.DLC1_Thrall_Faction())

    if FUNCS.Is_Mod_Installed("Better Vampires.esp")
        ref_thrall.SetGhost(true); stops further dialogs
        ref_thrall.SetActorValue("Variable08", 8); cancels limit
        (doticu_npcp_consts.Vampire_Feed_Perk() as PRKF_VampireFeedBeds_000CF02C).Fragment_15(ref_thrall, none)
        ref_thrall.SetActorValue("Variable08", 8)
        ref_thrall.SetGhost(false)
    elseIf ACTORS.Is_Dead(ref_thrall)
        ; do cannibal instead, or make another perk
    else
        doticu_npcp_consts.Player_Actor().StartVampireFeed(ref_thrall)
        (doticu_npcp_consts.Player_Vampire_Quest() as PlayerVampireQuestScript).VampireFeed()
    endIf

    ref_thrall.RemoveFromFaction(doticu_npcp_consts.DLC1_Thrall_Faction())
    PERKS.Add_Perk(doticu_npcp_consts.Kiss_Thrall_Perk())
endFunction
