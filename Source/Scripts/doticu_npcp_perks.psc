;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_perks extends Quest hidden

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_perk_kiss property KISS
    doticu_npcp_perk_kiss function Get()
        return p_DATA.CONSTS.PERK_KISS_THRALL as doticu_npcp_perk_kiss
    endFunction
endProperty
doticu_npcp_perk_kill property KILL
    doticu_npcp_perk_kill function Get()
        return p_DATA.CONSTS.PERK_KILL_ESSENTIAL as doticu_npcp_perk_kill
    endFunction
endProperty
doticu_npcp_perk_resurrect property RESURRECT
    doticu_npcp_perk_resurrect function Get()
        return p_DATA.CONSTS.PERK_RESURRECT_MEMBER as doticu_npcp_perk_resurrect
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true

    Add_Perk(CONSTS.PERK_KISS_THRALL)
    Add_Perk(CONSTS.PERK_KILL_ESSENTIAL)
    Add_Perk(CONSTS.PERK_RESURRECT_MEMBER)

    KISS.f_Create(DATA)
    KILL.f_Create(DATA)
    RESURRECT.f_Create(DATA)
endFunction

function f_Destroy()
    Remove_Perk(CONSTS.PERK_RESURRECT_MEMBER)
    Remove_Perk(CONSTS.PERK_KILL_ESSENTIAL)
    Remove_Perk(CONSTS.PERK_KISS_THRALL)

    p_is_created = false
endFunction

function f_Register()
    KISS.f_Register()
    KILL.f_Register()
    RESURRECT.f_Register()
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    CONSTS.ACTOR_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    CONSTS.ACTOR_PLAYER.RemovePerk(perk_to_remove)
endFunction
