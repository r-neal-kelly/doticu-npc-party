;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_vars extends Quest

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
int                 p_clone_outfit          =    -1

string              p_str_sort_members      =    ""
String              p_str_sort_followers    =    ""

bool                p_auto_resurrect        = false

bool                p_auto_outfit           = false
bool                p_fill_outfits          = false
bool                p_auto_immobile_outfit  = false
int                 p_percent_body          =    -1
int                 p_percent_feet          =    -1
int                 p_percent_hands         =    -1
int                 p_percent_head          =    -1

int                 p_auto_style            =    -1
int                 p_auto_vitality         =    -1

int                 p_num_display           =    -1
int                 p_max_members           =    -1

bool                p_is_updating           = false
bool                p_is_mcm_open           = false

; Keys
int property key_g_dialogue_menu = -1 auto hidden

int[] property key_g_dialogue_menu_mods = none auto hidden

int property key_n_toggle_member = -1 auto hidden
int property key_n_toggle_move = -1 auto hidden
int property key_n_move_farther = -1 auto hidden
int property key_n_move_nearer = -1 auto hidden
int property key_n_move_rotate_left = -1 auto hidden
int property key_n_move_rotate_right = -1 auto hidden
int property key_n_has_base = -1 auto hidden
int property key_n_count_base = -1 auto hidden
int property key_n_has_head = -1 auto hidden
int property key_n_count_heads = -1 auto hidden

int[] property key_n_toggle_member_mods = none auto hidden
int[] property key_n_toggle_move_mods = none auto hidden
int[] property key_n_move_farther_mods = none auto hidden
int[] property key_n_move_nearer_mods = none auto hidden
int[] property key_n_move_rotate_left_mods = none auto hidden
int[] property key_n_move_rotate_right_mods = none auto hidden
int[] property key_n_has_base_mods = none auto hidden
int[] property key_n_count_base_mods = none auto hidden
int[] property key_n_has_head_mods = none auto hidden
int[] property key_n_count_heads_mods = none auto hidden

int property key_m_toggle_clone = -1 auto hidden
int property key_m_toggle_settler = -1 auto hidden
int property key_m_toggle_thrall = -1 auto hidden
int property key_m_toggle_immobile = -1 auto hidden
int property key_m_toggle_paralyzed = -1 auto hidden
int property key_m_toggle_follower = -1 auto hidden

int[] property key_m_toggle_clone_mods = none auto hidden
int[] property key_m_toggle_settler_mods = none auto hidden
int[] property key_m_toggle_thrall_mods = none auto hidden
int[] property key_m_toggle_immobile_mods = none auto hidden
int[] property key_m_toggle_paralyzed_mods = none auto hidden
int[] property key_m_toggle_follower_mods = none auto hidden

int property key_f_toggle_sneak = -1 auto hidden
int property key_f_toggle_saddler = -1 auto hidden

int[] property key_f_toggle_sneak_mods = none auto hidden
int[] property key_f_toggle_saddler_mods = none auto hidden

int property key_ms_toggle_display = -1 auto hidden
int property key_ms_display_previous = -1 auto hidden
int property key_ms_display_next = -1 auto hidden

int[] property key_ms_toggle_display_mods = none auto hidden
int[] property key_ms_display_previous_mods = none auto hidden
int[] property key_ms_display_next_mods = none auto hidden

int property key_fs_summon_all = -1 auto hidden
int property key_fs_summon_mobile = -1 auto hidden
int property key_fs_summon_immobile = -1 auto hidden
int property key_fs_settle = -1 auto hidden
int property key_fs_unsettle = -1 auto hidden
int property key_fs_mobilize = -1 auto hidden
int property key_fs_immobilize = -1 auto hidden
int property key_fs_sneak = -1 auto hidden
int property key_fs_unsneak = -1 auto hidden
int property key_fs_saddle = -1 auto hidden
int property key_fs_unsaddle = -1 auto hidden
int property key_fs_resurrect = -1 auto hidden

int[] property key_fs_summon_all_mods = none auto hidden
int[] property key_fs_summon_mobile_mods = none auto hidden
int[] property key_fs_summon_immobile_mods = none auto hidden
int[] property key_fs_settle_mods = none auto hidden
int[] property key_fs_unsettle_mods = none auto hidden
int[] property key_fs_mobilize_mods = none auto hidden
int[] property key_fs_immobilize_mods = none auto hidden
int[] property key_fs_sneak_mods = none auto hidden
int[] property key_fs_unsneak_mods = none auto hidden
int[] property key_fs_saddle_mods = none auto hidden
int[] property key_fs_unsaddle_mods = none auto hidden
int[] property key_fs_resurrect_mods = none auto hidden

; Unused
int property key_fs_unfollow                =    -1 auto hidden
int property key_fs_unmember                =    -1 auto hidden
int property key_resurrect                  =    -1 auto hidden
int property key_pack                       =    -1 auto hidden
int property key_outfit                     =    -1 auto hidden
int property key_cycle_outfit               =    -1 auto hidden
int property key_cycle_style                =    -1 auto hidden
int property key_cycle_vitality             =    -1 auto hidden

int property version_major hidden
    int function Get()
        return p_version_major
    endFunction
    function Set(int val)
        if val > -1
            p_version_major = val
        endIf
    endFunction
endProperty

int property version_minor hidden
    int function Get()
        return p_version_minor
    endFunction
    function Set(int val)
        if val > -1
            p_version_minor = val
        endIf
    endFunction
endProperty

int property version_patch hidden
    int function Get()
        return p_version_patch
    endFunction
    function Set(int val)
        if val > -1
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
            doticu_npcp_consts.Force_Clone_Uniques_Global().SetValue(1)
        else
            doticu_npcp_consts.Force_Clone_Uniques_Global().SetValue(0)
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
            doticu_npcp_consts.Force_Clone_Generics_Global().SetValue(1)
        else
            doticu_npcp_consts.Force_Clone_Generics_Global().SetValue(0)
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
            doticu_npcp_consts.Force_Unclone_Uniques_Global().SetValue(1)
        else
            doticu_npcp_consts.Force_Unclone_Uniques_Global().SetValue(0)
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
            doticu_npcp_consts.Force_Unclone_Generics_Global().SetValue(1)
        else
            doticu_npcp_consts.Force_Unclone_Generics_Global().SetValue(0)
        endIf
    endFunction
endProperty

int property clone_outfit hidden
    int function Get()
        return p_clone_outfit
    endFunction
    function Set(int val)
        p_clone_outfit = val
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

bool property fill_outfits hidden
    bool function Get()
        return p_fill_outfits
    endFunction
    function Set(bool val)
        p_fill_outfits = val
    endFunction
endProperty

bool property auto_immobile_outfit hidden
    bool function Get()
        return p_auto_immobile_outfit
    endFunction
    function Set(bool val)
        p_auto_immobile_outfit = val
    endFunction
endProperty

int property percent_body hidden
    int function Get()
        return p_percent_body
    endFunction
    function Set(int val)
        if val < 0
            val = 0
        elseIf val > 100
            val = 100
        endIf
        p_percent_body = val
        doticu_npcp_consts.No_Body_Percent_Global().SetValue(100 - val)
    endFunction
endProperty

int property percent_feet hidden
    int function Get()
        return p_percent_feet
    endFunction
    function Set(int val)
        if val < 0
            val = 0
        elseIf val > 100
            val = 100
        endIf
        p_percent_feet = val
        doticu_npcp_consts.No_Feet_Percent_Global().SetValue(100 - val)
    endFunction
endProperty

int property percent_hands hidden
    int function Get()
        return p_percent_hands
    endFunction
    function Set(int val)
        if val < 0
            val = 0
        elseIf val > 100
            val = 100
        endIf
        p_percent_hands = val
        doticu_npcp_consts.No_Hands_Percent_Global().SetValue(100 - val)
    endFunction
endProperty

int property percent_head hidden
    int function Get()
        return p_percent_head
    endFunction
    function Set(int val)
        if val < 0
            val = 0
        elseIf val > 100
            val = 100
        endIf
        p_percent_head = val
        doticu_npcp_consts.No_Head_Percent_Global().SetValue(100 - val)
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

int property max_members hidden
    int function Get()
        return p_max_members
    endFunction
    function Set(int val)
        p_max_members = val
    endFunction
endProperty

bool property is_updating hidden
    bool function Get()
        return p_is_updating
    endFunction
    function Set(bool val)
        p_is_updating = val
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

string property str_sort_members hidden
    string function Get()
        return p_str_sort_members
    endFunction
    function Set(string val)
        p_str_sort_members = val
    endFunction
endProperty

string property str_sort_followers hidden
    string function Get()
        return p_str_sort_followers
    endFunction
    function Set(string val)
        p_str_sort_followers = val
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

function f_Unregister()
endFunction

; Public Methods
function Log_Variables() native
function Log_Properties() native

function Set_Defaults()
    version_major = doticu_npcp_consts.NPCP_Major()
    version_minor = doticu_npcp_consts.NPCP_Minor()
    version_patch = doticu_npcp_consts.NPCP_Patch()

    auto_style = doticu_npcp_codes.STYLE_DEFAULT(); DEFAULT, WARRIOR, MAGE, ARCHER, COWARD
    auto_vitality = doticu_npcp_codes.VITALITY_PROTECTED(); MORTAL, PROTECTED, ESSENTIAL, INVULNERABLE
    auto_resurrect = true

    force_clone_unique = false
    force_clone_generic = false
    force_unclone_unique = false
    force_unclone_generic = false
    clone_outfit = doticu_npcp_codes.OUTFIT_BASE(); OUTFIT_BASE, OUTFIT_REFERENCE

    auto_outfit = false
    auto_immobile_outfit = false
    fill_outfits = true
    percent_body = p_DATA.MODS.MEMBERS.DEFAULT_PERCENT_BODY
    percent_feet = p_DATA.MODS.MEMBERS.DEFAULT_PERCENT_FEET
    percent_hands = p_DATA.MODS.MEMBERS.DEFAULT_PERCENT_HANDS
    percent_head = p_DATA.MODS.MEMBERS.DEFAULT_PERCENT_HEAD

    str_sort_members = "NAME"
    str_sort_followers = "NAME"

    num_display = p_DATA.MODS.MEMBERS.DEFAULT_DISPLAY
    max_members = p_DATA.MODS.MEMBERS.Max(); MEMBERS is not f_Create()'d yet, but this func can be called

    is_updating = false
    is_mcm_open = false
endFunction
