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
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return doticu_npcp.Followers()
    endFunction
endProperty
doticu_npcp_control property CONTROL hidden
    doticu_npcp_control function Get()
        return doticu_npcp.Control()
    endFunction
endProperty

; Friend Methods
function f_Init_Mod()
    ; just in case of any engine bugs, like AddItem, which may not work
    ; during the first second of the game, see wiki
    FUNCS.Wait_Out_Of_Menu(1)

    if !p_Has_Requires()
        return
    endIf

    VARS.Start()
    FUNCS.Start()
    MEMBERS.Start()
    FOLLOWERS.Start()
    CONTROL.Start()

    doticu_npcp_consts.Reanimated_Dialogue_Quest().Start()
    doticu_npcp_consts.Thrall_Dialogue_Quest().Start()

    p_Create()
    p_Register()

    doticu_npcp_consts.Is_Installed_Global().SetValue(1)
    FUNCS.LOGS.Create_Note("Thank you for installing!")

    FUNCS.Send_Event("doticu_npcp_init_mod")
endFunction

function f_Load_Mod()
    FUNCS.Wait_Out_Of_Menu(1); just in case of any engine bugs
    
    if p_Has_Requires()
        p_Register()
        p_Version()

        FUNCS.Send_Event("doticu_npcp_load_mod")
        doticu_npcp.Print("NPC Party has loaded.")
    endIf
endFunction

; Private Methods
bool function p_Has_Requires()
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

    if doticu_npcp_consts.Is_Installed_Global().GetValue() > 0 && Is_NPC_Party_Version_Less_Than(0, 9, 0)
        Debug.MessageBox("NPC Party: This save has a version of NPC Party older than 0.9.0. " + \
                         "The new version you are running will not work on this save yet. " + \
                         "Exit without saving, and then update to version 0.9.0 before trying again.")
        return false
    endIf

    return true
endFunction

function p_Create()
    VARS.f_Create()
    FUNCS.f_Create()
    MEMBERS.f_Create()
    FOLLOWERS.f_Create()
    CONTROL.f_Create()
endFunction

function p_Register()
    ; registering mod events is global for each script on an object, and
    ; further, works for handlers labeled as function as well as event.
    VARS.f_Register()
    FUNCS.f_Register()
    MEMBERS.f_Register()
    FOLLOWERS.f_Register()
    CONTROL.f_Register()
endFunction

function p_Version()
    if Is_NPC_Party_Version_Less_Than(doticu_npcp_consts.NPCP_Major(), \
                                      doticu_npcp_consts.NPCP_Minor(), \
                                      doticu_npcp_consts.NPCP_Patch())
        p_Start_Updating()

        if Is_NPC_Party_Version_Less_Than(0, 9, 1)
            u_0_9_1()
        endIf

        VARS.version_major = doticu_npcp_consts.NPCP_Major()
        VARS.version_minor = doticu_npcp_consts.NPCP_Minor()
        VARS.version_patch = doticu_npcp_consts.NPCP_Patch()

        FUNCS.LOGS.Create_Note("Running version " + \
                               doticu_npcp_consts.NPCP_Major() + "." + \
                               doticu_npcp_consts.NPCP_Minor() + "." + \
                               doticu_npcp_consts.NPCP_Patch())

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

bool function Is_NPC_Party_Version(int major, int minor, int patch)
    return VARS.version_major == major && VARS.version_minor == minor && VARS.version_patch == patch
endFunction

bool function Is_Ready()
    return  VARS.version_major == doticu_npcp_consts.NPCP_Major() && \
            VARS.version_minor == doticu_npcp_consts.NPCP_Minor() && \
            VARS.version_patch == doticu_npcp_consts.NPCP_Patch()
endFunction

; Update Methods
function u_0_9_1()
    CONTROL.MCM.u_0_9_1()
endFunction

; Events
event OnInit()
    ; we don't init in this thread because it will not wait
    RegisterForSingleUpdate(0.01)
endEvent

event OnUpdate()
    f_Init_Mod()
endEvent
