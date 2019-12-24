Scriptname doticu_npcp_main extends Quest

; Private Constants
doticu_npcp_data    p_DATA      = none
doticu_npcp_consts  p_CONSTS    = none
doticu_npcp_vars    p_VARS      = none
doticu_npcp_funcs   p_FUNCS     = none

; Public Constants
doticu_npcp_data property DATA
    doticu_npcp_data function Get()
        return p_DATA
    endFunction
    function Set(doticu_npcp_data val)
        if p_DATA == none
            p_DATA = val
        endIf
    endFunction
endProperty

; Friend Methods
function f_Link()
    DATA.f_Link(DATA)
    DATA.MODS.FUNCS.f_Link(DATA)
    DATA.MODS.MEMBERS.f_Link(DATA)
    DATA.MODS.FOLLOWERS.f_Link(DATA)
    DATA.MODS.CONTROL.f_Link(DATA)

    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_VARS = DATA.VARS
    p_FUNCS = DATA.MODS.FUNCS
endFunction

function f_Initialize()
    DATA.f_Initialize()
    DATA.MODS.FUNCS.f_Initialize()
    DATA.MODS.MEMBERS.f_Initialize()
    DATA.MODS.FOLLOWERS.f_Initialize()
    DATA.MODS.CONTROL.f_Initialize()
endFunction

function f_Register()
    DATA.f_Register()
    DATA.MODS.FUNCS.f_Register()
    DATA.MODS.MEMBERS.f_Register()
    DATA.MODS.FOLLOWERS.f_Register()
    DATA.MODS.CONTROL.f_Register()

    RegisterForModEvent("doticu_npcp_load_mod", "On_NPCP_Load_Mod")
endFunction

function f_Version()
    int version_old = p_VARS.version_large + p_VARS.version_small + p_VARS.version_bug
    int version_new = p_CONSTS.VERSION_LARGE + p_CONSTS.VERSION_SMALL + p_CONSTS.VERSION_BUG
    string str_version_new

    if version_old < version_new
        if version_new >= 0 + 1 + 0
            u_0_1_0()
        endIf
        if version_new >= 1 + 0 + 0
            u_1_0_0()
        endIf
        if version_new >= 1 + 0 + 1
            u_1_0_1()
        endIf
        if version_new >= 1 + 1 + 0
            u_1_1_0()
        endIf
        if version_new >= 2 + 0 + 0
            u_2_0_0()
        endIf

        p_VARS.version_large = p_CONSTS.VERSION_LARGE
        p_VARS.version_small = p_CONSTS.VERSION_SMALL
        p_VARS.version_bug = p_CONSTS.VERSION_BUG

        str_version_new = p_CONSTS.VERSION_LARGE + "." + p_CONSTS.VERSION_SMALL + "." + p_CONSTS.VERSION_BUG
        p_FUNCS.LOGS.Create_Note("Running version " + str_version_new)
    endIf
endFunction

function f_Load_Mod()
    Utility.Wait(0.5)

    DATA.Reset(); resets doticu_npcp_quest_data_static
    ; DATA.MODS.CONTROL.MCM.Reset(); not sure yet. would need to set an OnInit on MCM or call its setup funcs

    f_Link()
    f_Register()
    f_Version()

    while !p_Send_NPCP_Load_Mod()
        Utility.Wait(0.25)
    endWhile
endFunction

; Private Methods
bool function p_Send_NPCP_Load_Mod()
    int handle = ModEvent.Create("doticu_npcp_load_mod")

    if !handle
        return false
    endIf

    ; push any args here

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Update Methods
function u_0_1_0()
    DATA.u_0_1_0()
    DATA.MODS.FUNCS.u_0_1_0()
    DATA.MODS.MEMBERS.u_0_1_0()
    DATA.MODS.FOLLOWERS.u_0_1_0()
    DATA.MODS.CONTROL.u_0_1_0()
endFunction

function u_1_0_0()
endFunction

function u_1_0_1()
endFunction

function u_1_1_0()
endFunction

function u_2_0_0()
endFunction

; Events
event OnInit()
    Utility.Wait(3)

    f_Link()
    f_Initialize()
    f_Register()

    p_FUNCS.LOGS.Create_Note("Thank you for installing!")
endEvent

event On_NPCP_Load_Mod()
endEvent
