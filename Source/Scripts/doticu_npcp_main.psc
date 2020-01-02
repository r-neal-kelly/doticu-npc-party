Scriptname doticu_npcp_main extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
    endFunction
endProperty
doticu_npcp_control property CONTROL hidden
    doticu_npcp_control function Get()
        return p_DATA.MODS.CONTROL
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA  = none

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
function f_Create()
    DATA.f_Create(DATA)
    VARS.f_Create(DATA)
    FUNCS.f_Create(DATA)
    MEMBERS.f_Create(DATA)
    FOLLOWERS.f_Create(DATA)
    CONTROL.f_Create(DATA)
endFunction

function f_Register()
    DATA.f_Register()
    VARS.f_Register()
    FUNCS.f_Register()
    MEMBERS.f_Register()
    FOLLOWERS.f_Register()
    CONTROL.f_Register()
endFunction

function f_Version()
    if p_Is_Version_Less_Than(CONSTS.VERSION_MAJOR, CONSTS.VERSION_MINOR, CONSTS.VERSION_PATCH)
        if p_Is_Version_Less_Than(0, 1, 4)
            u_0_1_4()
        endIf
        if p_Is_Version_Less_Than(0, 1, 5)
            u_0_1_5()
        endIf

        VARS.version_major = CONSTS.VERSION_MAJOR
        VARS.version_minor = CONSTS.VERSION_MINOR
        VARS.version_patch = CONSTS.VERSION_PATCH

        string str_version = CONSTS.VERSION_MAJOR + "." + CONSTS.VERSION_MINOR + "." + CONSTS.VERSION_PATCH
        FUNCS.LOGS.Create_Note("Running version " + str_version)
    endIf
endFunction

function f_Init_Mod()
    ; do checks to make sure SKSE and PapyrusUtil are running

    DATA.Start()
    VARS.Start()
    FUNCS.Start()
    MEMBERS.Start()
    FOLLOWERS.Start()
    CONTROL.Start()

    f_Create()
    f_Register()

    FUNCS.LOGS.Create_Note("Thank you for installing!")
endFunction

function f_Load_Mod()
    ; do checks to make sure SKSE and PapyrusUtil are running

    DATA.Stop()
    DATA.Start()

    ;/CONTROL.Stop()
    CONTROL.Start()/;

    f_Register()
    f_Version()

    ;Debug.Notification("LOADED (temp)")

    while !p_Send_Load_Mod()
        Utility.Wait(0.25)
    endWhile
endFunction

; Private Methods
bool function p_Is_Version_Less_Than(int major, int minor, int patch)
    if VARS.version_major != major
        return VARS.version_major < major
    elseIf VARS.version_minor != minor
        return VARS.version_minor < minor
    elseIf VARS.version_patch != patch
        return VARS.version_patch < patch
    else
        return false
    endIf
endFunction

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
function u_0_1_4()
    FUNCS.u_0_1_4(DATA)
    MEMBERS.u_0_1_4(DATA)
    FOLLOWERS.u_0_1_4(DATA)
endFunction

function u_0_1_5()
    MEMBERS.u_0_1_5(DATA)
endFunction

; Events
event OnInit()
    ; we don't want to init in this thread because
    ; it won't wait for props to be filled
    RegisterForSingleUpdate(0.01)
endEvent

event OnUpdate()
    f_Init_Mod()
endEvent
