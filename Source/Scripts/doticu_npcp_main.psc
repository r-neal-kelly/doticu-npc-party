;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

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
function f_Init_Mod()
    Utility.Wait(1); just in case of any engine bugs, like AddItem

    if !p_Has_Requires()
        return
    endIf

    DATA.Start()
    VARS.Start()
    FUNCS.Start()
    MEMBERS.Start()
    FOLLOWERS.Start()
    CONTROL.Start()

    p_Create()
    p_Register()

    DATA.CONSTS.GLOBAL_IS_INSTALLED.SetValue(1)
    FUNCS.LOGS.Create_Note("Thank you for installing!")

    while !p_Send("doticu_npcp_init_mod")
        Utility.Wait(0.25)
    endWhile
endFunction

function f_Load_Mod()
    Utility.Wait(1); just in case of any engine bugs, like AddItem

    if !p_Has_Requires()
        return
    endIf

    DATA.Stop()
    DATA.Start()

    p_Register()
    p_Version()

    while !p_Send("doticu_npcp_load_mod")
        Utility.Wait(0.25)
    endWhile
endFunction

; Private Methods
bool function p_Has_Requires()
    if !SKSE.GetVersion()
        Debug.MessageBox("NPC Party: SKSE is not installed. This mod will not function. Please install SKSE 2.0.17 or higher.")
        return false
    endIf

    if Is_SKSE_Less_Than(2, 0, 17)
        Debug.MessageBox("NPC Party: Running a version of SKSE older than 2.0.17. This mod may not function. Please update SKSE.")
    elseIf SKSE.GetScriptVersionRelease() < 64
        Debug.MessageBox("NPC Party: SKSE scripts are older than version 2.0.17. This mod may not function. Try to reinstall SKSE.")
    endIf

    if !PapyrusUtil.GetVersion()
        Debug.MessageBox("NPC Party: PapyrusUtil is not installed. This mod will not function. Please install PapyrusUtil 3.8 or higher.")
        return false
    endIf

    if PapyrusUtil.GetVersion() < 38
        Debug.MessageBox("NPC Party: Running a version of PapyrusUtil older than 3.8. This mod may not function. Please update PapyrusUtil.")
    elseIf PapyrusUtil.GetScriptVersion() < 38
        Debug.MessageBox("NPC Party: PapyrusUtil scripts are older than version 3.8. This mod may not function. Try to reinstall PapyrusUtil.")
    endIf

    return true
endFunction

function p_Create()
    DATA.f_Create(DATA)
    VARS.f_Create(DATA)
    FUNCS.f_Create(DATA)
    MEMBERS.f_Create(DATA)
    FOLLOWERS.f_Create(DATA)
    CONTROL.f_Create(DATA)
endFunction

function p_Register()
    DATA.f_Register()
    VARS.f_Register()
    FUNCS.f_Register()
    MEMBERS.f_Register()
    FOLLOWERS.f_Register()
    CONTROL.f_Register()
endFunction

function p_Version()
    if Is_NPC_Party_Less_Than(CONSTS.VERSION_MAJOR, CONSTS.VERSION_MINOR, CONSTS.VERSION_PATCH)
        p_Start_Updating()

        if Is_NPC_Party_Less_Than(0, 8, 0)
            u_0_8_0()
        endIf

        VARS.version_major = CONSTS.VERSION_MAJOR
        VARS.version_minor = CONSTS.VERSION_MINOR
        VARS.version_patch = CONSTS.VERSION_PATCH

        FUNCS.LOGS.Create_Note("Running version " + Get_Version_String())

        p_Stop_Updating()
    endIf
endFunction

function p_Start_Updating()
    VARS.is_updating = true
    CONTROL.f_Start_Updating()
endFunction

function p_Stop_Updating()
    CONTROL.f_Stop_Updating()
    VARS.is_updating = false
endFunction

bool function p_Send(string str_event)
    int handle = ModEvent.Create(str_event)

    if !handle
        return false
    endIf

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Public Methods
int[] function Get_Version_Array()
    int[] arr_version = new int[3]

    arr_version[0] = CONSTS.VERSION_MAJOR
    arr_version[1] = CONSTS.VERSION_MINOR
    arr_version[2] = CONSTS.VERSION_PATCH

    return arr_version
endFunction

string function Get_Version_String()
    return CONSTS.VERSION_MAJOR + "." + CONSTS.VERSION_MINOR + "." + CONSTS.VERSION_PATCH
endFunction

int function Get_Version_Major()
    return CONSTS.VERSION_MAJOR
endFunction

int function Get_Version_Minor()
    return CONSTS.VERSION_MINOR
endFunction

int function Get_Version_Patch()
    return CONSTS.VERSION_PATCH
endFunction

bool function Is_Version_Less_Than(int major, int minor, int patch, int min_major, int min_minor, int min_patch)
    if major != min_major
        return major < min_major
    elseIf minor != min_minor
        return minor < min_minor
    elseIf patch != min_patch
        return patch < min_patch
    else
        return false
    endIf
endFunction

bool function Is_SKSE_Less_Than(int min_major, int min_minor, int min_patch)
    return Is_Version_Less_Than(SKSE.GetVersion(), SKSE.GetVersionMinor(), SKSE.GetVersionBeta(), min_major, min_minor, min_patch)
endFunction

bool function Is_NPC_Party_Less_Than(int min_major, int min_minor, int min_patch)
    return Is_Version_Less_Than(VARS.version_major, VARS.version_minor, VARS.version_patch, min_major, min_minor, min_patch)
endFunction

; Update Methods
function u_0_8_0()
    DATA.MODS.FUNCS.NPCS.u_0_8_0()
endFunction

function u_0_8_1()
    DATA.MODS.FUNCS.PERKS.u_0_8_1()
endFunction

; Events
event OnInit()
    ; we don't want to init in this thread because
    ; it won't wait for properties to be filled
    RegisterForSingleUpdate(0.01)
endEvent

event OnUpdate()
    f_Init_Mod()
endEvent
