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
doticu_npcp_perk_resurrect property RESURRECT
    doticu_npcp_perk_resurrect function Get()
        return p_DATA.CONSTS.PERK_RESURRECT as doticu_npcp_perk_resurrect
    endFunction
endProperty
doticu_npcp_perk_reanimate property REANIMATE
    doticu_npcp_perk_reanimate function Get()
        return p_DATA.CONSTS.PERK_REANIMATE as doticu_npcp_perk_reanimate
    endFunction
endProperty
doticu_npcp_perk_unparalyze property UNPARALYZE
    doticu_npcp_perk_unparalyze function Get()
        return p_DATA.CONSTS.PERK_UNPARALYZE as doticu_npcp_perk_unparalyze
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
    Add_Perk(CONSTS.PERK_RESURRECT)
    ;Add_Perk(CONSTS.PERK_REANIMATE)
    Add_Perk(CONSTS.PERK_UNPARALYZE)

    KISS.f_Create(p_DATA)
    RESURRECT.f_Create(p_DATA)
    ;REANIMATE.f_Create(p_DATA)
    UNPARALYZE.f_Create(p_DATA)
endFunction

function f_Destroy()
    UNPARALYZE.f_Destroy()
    ;REANIMATE.f_Destroy()
    RESURRECT.f_Destroy()
    KISS.f_Destroy()

    Remove_Perk(CONSTS.PERK_UNPARALYZE)
    ;Remove_Perk(CONSTS.PERK_REANIMATE)
    Remove_Perk(CONSTS.PERK_RESURRECT)
    Remove_Perk(CONSTS.PERK_KISS_THRALL)

    p_is_created = false
endFunction

function f_Register()
    KISS.f_Register()
    RESURRECT.f_Register()
    ;REANIMATE.f_Register()
    UNPARALYZE.f_Register()
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    CONSTS.ACTOR_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    CONSTS.ACTOR_PLAYER.RemovePerk(perk_to_remove)
endFunction

; Update Methods
function u_0_8_2()
    ; don't forget to uncomment REANIMATE above
    Add_Perk(CONSTS.PERK_REANIMATE)
    REANIMATE.f_Create(p_DATA)
    REANIMATE.f_Register()
endFunction
