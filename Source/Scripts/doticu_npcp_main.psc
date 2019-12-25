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

    RegisterForModEvent("doticu_npcp_load_mod", "On_Load_Mod")
endFunction

function f_Version()
    int version_old = p_VARS.version_major + p_VARS.version_minor + p_VARS.version_patch
    int version_new = p_CONSTS.VERSION_MAJOR + p_CONSTS.VERSION_MINOR + p_CONSTS.VERSION_PATCH
    string str_version_new

    if version_old < version_new
        if version_old < 0 + 1 + 0
            u_0_1_0()
        endIf
        if version_old < 0 + 1 + 1
            u_0_1_1()
        endIf

        p_VARS.version_major = p_CONSTS.VERSION_MAJOR
        p_VARS.version_minor = p_CONSTS.VERSION_MINOR
        p_VARS.version_patch = p_CONSTS.VERSION_PATCH

        str_version_new = p_CONSTS.VERSION_MAJOR + "." + p_CONSTS.VERSION_MINOR + "." + p_CONSTS.VERSION_PATCH
        p_FUNCS.LOGS.Create_Note("Running version " + str_version_new)
    endIf
endFunction

function f_Load_Mod()
    DATA.Stop()
    while !DATA.Start()
        Utility.Wait(0.5)
    endWhile

    ;/DATA.MODS.CONTROL.Stop()
    while !DATA.MODS.CONTROL.Start()
        Utility.Wait(0.5)
    endWhile/;

    f_Link()
    f_Register()
    f_Version()

    while !p_Send_Load_Mod()
        Utility.Wait(0.25)
    endWhile
endFunction

; Private Methods
bool function p_Send_Load_Mod()
    int handle = ModEvent.Create("doticu_npcp_load_mod")

    if !handle
        return false
    endIf

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Update Methods
function u_0_1_0()
    DATA.MODS.MEMBERS.u_0_1_0()
endFunction

function u_0_1_1()
    DATA.MODS.FUNCS.u_0_1_1()
    DATA.MODS.MEMBERS.u_0_1_1()
    DATA.MODS.FOLLOWERS.u_0_1_1()
endFunction

; Events
event OnInit()
    while !DATA.Start()
        Utility.Wait(1)
    endWhile

    while !DATA.VARS.Start()
        Utility.Wait(1)
    endWhile

    while !DATA.MODS.FUNCS.Start()
        Utility.Wait(1)
    endWhile

    while !DATA.MODS.MEMBERS.Start()
        Utility.Wait(1)
    endWhile

    while !DATA.MODS.FOLLOWERS.Start()
        Utility.Wait(1)
    endWhile

    while !DATA.MODS.CONTROL.Start()
        Utility.Wait(1)
    endWhile

    f_Link()
    f_Initialize()
    f_Register()

    p_FUNCS.LOGS.Create_Note("Thank you for installing!")
endEvent

event On_Load_Mod()
endEvent
