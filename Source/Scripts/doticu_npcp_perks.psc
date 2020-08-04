;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_perks extends Quest hidden

; Modules
doticu_npcp_perk_kiss property KISS
    doticu_npcp_perk_kiss function Get()
        return doticu_npcp_consts.Kiss_Thrall_Perk() as doticu_npcp_perk_kiss
    endFunction
endProperty
doticu_npcp_perk_resurrect property RESURRECT
    doticu_npcp_perk_resurrect function Get()
        return doticu_npcp_consts.Resurrect_Perk() as doticu_npcp_perk_resurrect
    endFunction
endProperty
doticu_npcp_perk_reanimate property REANIMATE
    doticu_npcp_perk_reanimate function Get()
        return doticu_npcp_consts.Reanimate_Perk() as doticu_npcp_perk_reanimate
    endFunction
endProperty
doticu_npcp_perk_unparalyze property UNPARALYZE
    doticu_npcp_perk_unparalyze function Get()
        return doticu_npcp_consts.Unparalyze_Perk() as doticu_npcp_perk_unparalyze
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

    Add_Perk(doticu_npcp_consts.Kiss_Thrall_Perk())
    Add_Perk(doticu_npcp_consts.Resurrect_Perk())
    Add_Perk(doticu_npcp_consts.Reanimate_Perk())
    Add_Perk(doticu_npcp_consts.Unparalyze_Perk())

    KISS.f_Create(p_DATA)
    RESURRECT.f_Create(p_DATA)
    REANIMATE.f_Create(p_DATA)
    UNPARALYZE.f_Create(p_DATA)
endFunction

function f_Destroy()
    UNPARALYZE.f_Destroy()
    REANIMATE.f_Destroy()
    RESURRECT.f_Destroy()
    KISS.f_Destroy()

    Remove_Perk(doticu_npcp_consts.Unparalyze_Perk())
    Remove_Perk(doticu_npcp_consts.Reanimate_Perk())
    Remove_Perk(doticu_npcp_consts.Resurrect_Perk())
    Remove_Perk(doticu_npcp_consts.Kiss_Thrall_Perk())

    p_is_created = false
endFunction

function f_Register()
    KISS.f_Register()
    RESURRECT.f_Register()
    REANIMATE.f_Register()
    UNPARALYZE.f_Register()
endFunction

function f_Unregister()
    UNPARALYZE.f_Unregister()
    REANIMATE.f_Unregister()
    RESURRECT.f_Unregister()
    KISS.f_Unregister()
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    doticu_npcp_consts.Player_Actor().AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    doticu_npcp_consts.Player_Actor().RemovePerk(perk_to_remove)
endFunction

; Update Methods
function u_0_8_2()
    Add_Perk(doticu_npcp_consts.Reanimate_Perk())
    REANIMATE.f_Create(p_DATA)
    REANIMATE.f_Register()
endFunction
