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
doticu_npcp_data    p_DATA                      =  none
bool                p_will_init_or_load_0_9_1   = false

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

bool property WILL_INIT_OR_LOAD_0_9_1
    bool function Get()
        return p_will_init_or_load_0_9_1
    endFunction
endProperty

; Friend Methods
function f_Init_Mod()
    ; this lets a contingency update method know whether to startup or not
    ; to be removed in next update.
    p_will_init_or_load_0_9_1 = true

    ; just in case of any engine bugs, like AddItem, which may not work
    ; during the first second of the game, see wiki
    FUNCS.Wait_Out_Of_Menu(1)

    if !p_Has_Requires()
        return
    endIf

    DATA.Start()
    VARS.Start()
    FUNCS.Start()
    MEMBERS.Start()
    FOLLOWERS.Start()
    CONTROL.Start()

    DATA.CONSTS.QUEST_DIALOGUE_REANIMATED.Start()
    DATA.CONSTS.QUEST_DIALOGUE_THRALL.Start()

    p_Create()
    p_Register()

    DATA.CONSTS.GLOBAL_IS_INSTALLED.SetValue(1)
    FUNCS.LOGS.Create_Note("Thank you for installing!")

    FUNCS.Send_Event("doticu_npcp_init_mod")
endFunction

function f_Load_Mod()
    ; this lets a contingency update method know whether to startup or not
    ; to be removed in next update.
    p_will_init_or_load_0_9_1 = true

    ; just in case of any engine bugs, like AddItem, which may not work
    ; during the first second of the game, see wiki
    FUNCS.Wait_Out_Of_Menu(1)

    if !p_Has_Requires()
        return
    endIf

    DATA.Stop()
    DATA.Start()

    p_Register()
    p_Version()

    FUNCS.Send_Event("doticu_npcp_load_mod")
    doticu_npcp.Print("NPC Party has loaded.")

    ; Testing
    ;doticu_npcp.Run_Tests()
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

    if DATA.CONSTS.GLOBAL_IS_INSTALLED.GetValue() > 0 && Is_NPC_Party_Version_Less_Than(0, 8, 2)
        Debug.MessageBox("NPC Party: This save has a version of NPC Party older than 0.8.2. " + \
                         "The new version you are running will not work on this save yet. " + \
                         "Exit without saving, and then update to version 0.8.2 before trying again.")
        return false
    endIf

    int[] plugin_version = doticu_npcp.Get_Plugin_Version()
    if CONSTS.VERSION_MAJOR != plugin_version[0] || CONSTS.VERSION_MINOR != plugin_version[1] || CONSTS.VERSION_PATCH != plugin_version[2]
        Debug.MessageBox("NPC Party: The NPC Party plugin doesn't match the current version. " + \
                         "The plugin has not been correctly installed or correctly updated. " + \
                         "Exit without saving, and make sure everything is installed correctly before trying again.")
        return false
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
    ; registering mod events is global for each script on an object, and
    ; further, works for handlers labeled as function as well as event.
    DATA.f_Register()
    VARS.f_Register()
    FUNCS.f_Register()
    MEMBERS.f_Register()
    FOLLOWERS.f_Register()
    CONTROL.f_Register()
endFunction

function p_Version()
    if Is_NPC_Party_Version_Less_Than(CONSTS.VERSION_MAJOR, CONSTS.VERSION_MINOR, CONSTS.VERSION_PATCH)
        p_Start_Updating()

        if Is_NPC_Party_Version_Less_Than(0, 9, 0)
            if !Is_NPC_Party_Version(0, 8, 3); this in-house version was incrementally updated
                u_0_9_0()
            endIf
        endIf

        if Is_NPC_Party_Version_Less_Than(0, 9, 1)
            u_0_9_1()
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
    return  VARS.version_major == CONSTS.VERSION_MAJOR && \
            VARS.version_minor == CONSTS.VERSION_MINOR && \
            VARS.version_patch == CONSTS.VERSION_PATCH
endFunction

; Update Methods
function u_0_9_0()
    Debug.MessageBox(                                           \
        "NPC Party: This update may take a couple minutes, " +  \
        "depending on how many members you have. " +            \
        "Open the console to monitor progress!\n" +             \
        "(Push the '~' key to open the console.)"               \
    )

    FUNCS.LOGS.Notify_Is_Updating()

    FUNCS.LOGS.Print("Beginning update...")

    VARS.u_0_9_0()
    FUNCS.u_0_9_0()
    MEMBERS.u_0_9_0()
    CONTROL.MCM.u_0_9_0()

    FUNCS.LOGS.Print("Done updating.")

    Debug.MessageBox(                                       \
        "NPC Party: The update has been completed. " +      \
        "You should save your game. Thank you for waiting!" \
    )
endFunction

function u_0_9_1()
    FUNCS.CONTAINERS.u_0_9_1()
    CONTROL.MCM.u_0_9_1()
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
