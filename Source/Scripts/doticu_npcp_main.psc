;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_main extends Quest

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return doticu_npcp.Vars()
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return doticu_npcp.Members()
    endFunction
endProperty
doticu_npcp_control property CONTROL hidden
    doticu_npcp_control function Get()
        return doticu_npcp.Control()
    endFunction
endProperty

; Native Methods
function p_Init_Mod() native

; Private Methods
bool function p_Has_Requires();;;
    if !SKSE.GetVersion()
        Debug.MessageBox("NPC Party: SKSE is not installed. " + \
                         "This mod will not function correctly. " + \
                         "Exit without saving, install SKSE 2.0.17 or higher, and try again.")
        return false
    endIf
    
    if Is_SKSE_Version_Less_Than(2, 0, 17)
        Debug.MessageBox("NPC Party: Running a version of SKSE older than 2.0.17. " + \
                         "This mod will not function correctly. " + \
                         "Exit without saving, update SKSE to 2.0.17 or higher, and try again.")
        return false
    elseIf SKSE.GetScriptVersionRelease() < 64
        Debug.MessageBox("NPC Party: SKSE scripts are older than version 2.0.17. " + \
                         "This mod will not function correctly. " + \
                         "Exit without saving, reinstall SKSE, and try again.")
        return false
    endIf

    if doticu_npcp_consts.Is_Installed_Global().GetValue() > 0 && Is_NPC_Party_Version_Less_Than(0, 9, 1)
        Debug.MessageBox("NPC Party: This save has a version of NPC Party older than 0.9.1. " + \
                         "The new version you are running will not work on this save yet. " + \
                         "Exit without saving, and then update to version 0.9.1 before trying again.")
        return false
    endIf

    return true
endFunction

function p_Create();;;
    VARS.f_Create()
    FUNCS.f_Create()
    MEMBERS.f_Create()
    CONTROL.f_Create()

    FUNCS.f_Register()
    MEMBERS.f_Register()
    CONTROL.f_Register()
endFunction

function p_Register();;;
    FUNCS.f_Register()
    MEMBERS.f_Register()
    CONTROL.f_Register()
endFunction

; Public Methods
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

bool function Is_SKSE_Version_Less_Than(int min_major, int min_minor, int min_patch)
    return Is_Version_Less_Than(SKSE.GetVersion(), SKSE.GetVersionMinor(), SKSE.GetVersionBeta(), min_major, min_minor, min_patch)
endFunction

bool function Is_NPC_Party_Version_Less_Than(int min_major, int min_minor, int min_patch)
    return Is_Version_Less_Than(VARS.version_major, VARS.version_minor, VARS.version_patch, min_major, min_minor, min_patch)
endFunction

; Events
event OnInit()
    RegisterForSingleUpdate(0.01); we don't init in this thread because it will not wait
endEvent

event OnUpdate()
    p_Init_Mod()
endEvent
