Scriptname doticu_npcp_vars extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA                  =  none

; Private Variables
bool                p_is_created            = false
int                 p_version_major         =    -1
int                 p_version_minor         =    -1
int                 p_version_patch         =    -1
bool                p_force_clone_unique    = false
bool                p_force_clone_generic   = false
bool                p_force_unclone_unique  = false
bool                p_force_unclone_generic = false
bool                p_auto_resurrect        = false
bool                p_auto_outfit           = false
int                 p_auto_style            =    -1
int                 p_auto_vitality         =    -1
int                 p_num_display           =    -1
bool                p_is_mcm_open           = false

; Public Variables
int property key_fs_summon_all              =    -1 auto hidden
int property key_fs_summon_mobile           =    -1 auto hidden
int property key_fs_summon_immobile         =    -1 auto hidden
int property key_fs_settle                  =    -1 auto hidden
int property key_fs_unsettle                =    -1 auto hidden
int property key_fs_immobilize              =    -1 auto hidden
int property key_fs_mobilize                =    -1 auto hidden
int property key_fs_sneak                   =    -1 auto hidden
int property key_fs_unsneak                 =    -1 auto hidden
int property key_fs_resurrect               =    -1 auto hidden
int property key_fs_unfollow                =    -1 auto hidden
int property key_fs_unmember                =    -1 auto hidden
; maybe add toggles? maybe use modified to keep things consistent in default settings

int property key_ms_display_start           =    -1 auto hidden
int property key_ms_display_stop            =    -1 auto hidden
int property key_ms_display_next            =    -1 auto hidden
int property key_ms_display_previous        =    -1 auto hidden
int property key_ms_toggle_display          =    -1 auto hidden

; also, the cool idea to cycle through members so that they are easily visible. they are sent back where they came. (settler marker, editor loc, coords if in same cell)

int property key_resurrect                  =    -1 auto hidden
int property key_pack                       =    -1 auto hidden
int property key_outfit                     =    -1 auto hidden

int property key_move_toggle                =    -1 auto hidden
int property key_move_farther               =    -1 auto hidden
int property key_move_nearer                =    -1 auto hidden
int property key_move_rotate_right          =    -1 auto hidden
int property key_move_rotate_left           =    -1 auto hidden

int property key_toggle_member              =    78 auto hidden; NUM+
int property key_toggle_clone               =    -1 auto hidden
int property key_toggle_settler             =    82 auto hidden; NUM0
int property key_toggle_enthrall            =    73 auto hidden; NUM9
int property key_toggle_immobile            =    83 auto hidden; NUM.
int property key_toggle_paralyzed           =    -1 auto hidden
int property key_toggle_follower            =    55 auto hidden; NUM*
int property key_toggle_sneak               =    74 auto hidden; NUM-

int property key_cycle_outfit               =    -1 auto hidden
int property key_cycle_style                =    -1 auto hidden
int property key_cycle_vitality             =    -1 auto hidden

int property version_major hidden
    int function Get()
        return p_version_major
    endFunction
    function Set(int val)
        if p_version_major < val
            p_version_major = val
        endIf
    endFunction
endProperty

int property version_minor hidden
    int function Get()
        return p_version_minor
    endFunction
    function Set(int val)
        if p_version_minor < val
            p_version_minor = val
        endIf
    endFunction
endProperty

int property version_patch hidden
    int function Get()
        return p_version_patch
    endFunction
    function Set(int val)
        if p_version_patch < val
            p_version_patch = val
        endIf
    endFunction
endProperty

bool property force_clone_unique hidden
    bool function Get()
        return p_force_clone_unique
    endFunction
    function Set(bool val)
        p_force_clone_unique = val
        if p_force_clone_unique
            CONSTS.GLOBAL_FORCE_CLONE_UNIQUE.SetValue(1)
        else
            CONSTS.GLOBAL_FORCE_CLONE_UNIQUE.SetValue(0)
        endIf
    endFunction
endProperty

bool property force_clone_generic hidden
    bool function Get()
        return p_force_clone_generic
    endFunction
    function Set(bool val)
        p_force_clone_generic = val
        if p_force_clone_generic
            CONSTS.GLOBAL_FORCE_CLONE_GENERIC.SetValue(1)
        else
            CONSTS.GLOBAL_FORCE_CLONE_GENERIC.SetValue(0)
        endIf
    endFunction
endProperty

bool property force_unclone_unique hidden
    bool function Get()
        return p_force_unclone_unique
    endFunction
    function Set(bool val)
        p_force_unclone_unique = val
        if p_force_unclone_unique
            CONSTS.GLOBAL_FORCE_UNCLONE_UNIQUE.SetValue(1)
        else
            CONSTS.GLOBAL_FORCE_UNCLONE_UNIQUE.SetValue(0)
        endIf
    endFunction
endProperty

bool property force_unclone_generic hidden
    bool function Get()
        return p_force_unclone_generic
    endFunction
    function Set(bool val)
        p_force_unclone_generic = val
        if p_force_unclone_generic
            CONSTS.GLOBAL_FORCE_UNCLONE_GENERIC.SetValue(1)
        else
            CONSTS.GLOBAL_FORCE_UNCLONE_GENERIC.SetValue(0)
        endIf
    endFunction
endProperty

bool property auto_resurrect hidden
    bool function Get()
        return p_auto_resurrect
    endFunction
    function Set(bool val)
        p_auto_resurrect = val
    endFunction
endProperty

bool property auto_outfit hidden
    bool function Get()
        return p_auto_outfit
    endFunction
    function Set(bool val)
        p_auto_outfit = val
    endFunction
endProperty

int property auto_style hidden
    int function Get()
        return p_auto_style
    endFunction
    function Set(int val)
        p_auto_style = val
    endFunction
endProperty

int property auto_vitality hidden
    int function Get()
        return p_auto_vitality
    endFunction
    function Set(int val)
        p_auto_vitality = val
    endFunction
endProperty

int property num_display hidden
    int function Get()
        return p_num_display
    endFunction
    function Set(int val)
        p_num_display = val
    endFunction
endProperty

bool property is_mcm_open hidden
    bool function Get()
        return p_is_mcm_open
    endFunction
    function Set(bool val)
        p_is_mcm_open = val
    endFunction
endProperty

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true

    Set_Defaults()
endFunction

function f_Destroy()
    Set_Defaults()
    p_is_created = false
endFunction

function f_Register()
endFunction

; Public Methods
function Set_Defaults()
    version_major = CONSTS.VERSION_MAJOR
    version_minor = CONSTS.VERSION_MINOR
    version_patch = CONSTS.VERSION_PATCH
    force_clone_unique = false
    force_clone_generic = true
    force_unclone_unique = false
    force_unclone_generic = true
    auto_resurrect = true
    auto_outfit = true
    auto_style = CODES.IS_DEFAULT; IS_DEFAULT, IS_WARRIOR, IS_MAGE, IS_ARCHER
    auto_vitality = CODES.IS_PROTECTED; IS_MORTAL, IS_PROTECTED, IS_ESSENTIAL, IS_INVULNERABLE
    num_display = 5
    is_mcm_open = false

    ; need to set keys here I think...
endFunction

; Update Methods
function u_0_3_1()
    num_display = CONSTS.DEFAULT_DISPLAY
endFunction
