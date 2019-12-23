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
function f_Register()
    DATA.f_Register()
    DATA.MODS.FUNCS.f_Register()
    DATA.MODS.MEMBERS.f_Register()
    DATA.MODS.FOLLOWERS.f_Register()
    DATA.MODS.CONTROL.f_Register()

    RegisterForModEvent("doticu_npcp_load_game", "On_NPCP_Load_Game")
    RegisterForModEvent("doticu_npcp_version_1_0_0", "On_NPCP_Version_1_0_0")
    RegisterForModEvent("doticu_npcp_version_1_0_1", "On_NPCP_Version_1_0_1")
    RegisterForModEvent("doticu_npcp_version_1_1_0", "On_NPCP_Version_1_1_0")
    RegisterForModEvent("doticu_npcp_version_2_0_0", "On_NPCP_Version_2_0_0")
endFunction

function f_Version()
    int version_old = p_VARS.version_large + p_VARS.version_small + p_VARS.version_bug
    int version_new = p_CONSTS.VERSION_LARGE + p_CONSTS.VERSION_SMALL + p_CONSTS.VERSION_BUG
    string str_version_new

    if version_old < version_new
        if version_new >= 1 + 0 + 0
            while !p_Send_NPCP_Version("1_0_0")
                Utility.Wait(0.25)
            endWhile
        endIf
        if version_new >= 1 + 0 + 1
            while !p_Send_NPCP_Version("1_0_1")
                Utility.Wait(0.25)
            endWhile
        endIf
        if version_new >= 1 + 1 + 0
            while !p_Send_NPCP_Version("1_1_0")
                Utility.Wait(0.25)
            endWhile
        endIf
        if version_new >= 2 + 0 + 0
            while !p_Send_NPCP_Version("2_0_0")
                Utility.Wait(0.25)
            endWhile
        endIf

        p_VARS.version_large = p_CONSTS.VERSION_LARGE
        p_VARS.version_small = p_CONSTS.VERSION_SMALL
        p_VARS.version_bug = p_CONSTS.VERSION_BUG

        str_version_new = p_CONSTS.VERSION_LARGE + "." + p_CONSTS.VERSION_SMALL + "." + p_CONSTS.VERSION_BUG
        p_FUNCS.LOGS.Create_Note("Running version " + str_version_new)
    endIf
endFunction

; Private Methods
function p_Initialize()
    DATA.f_Initialize()
    DATA.MODS.FUNCS.f_Initialize(DATA)
    DATA.MODS.MEMBERS.f_Initialize(DATA)
    DATA.MODS.FOLLOWERS.f_Initialize(DATA)
    DATA.MODS.CONTROL.f_Initialize(DATA)

    p_CONSTS = DATA.CONSTS
    p_VARS = DATA.VARS
    p_FUNCS = DATA.MODS.FUNCS

    f_Register()

    f_Version()

    p_FUNCS.LOGS.Create_Note("Thank you for installing!")
endFunction

bool function p_Send_NPCP_Version(string str_version)
    int handle = ModEvent.Create("doticu_npcp_version_" + str_version)

    if !handle
        return false
    endIf

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Events
event OnInit()
    Utility.Wait(3)
    p_Initialize()
endEvent

event On_NPCP_Version_1_0_0()
endEvent

event On_NPCP_Version_1_0_1()
endEvent

event On_NPCP_Version_1_1_0()
endEvent

event On_NPCP_Version_2_0_0()
endEvent

event On_NPCP_Load_Game()
endEvent
