;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_keys extends Quest

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
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty

; Public Constants
string property KEY_G_DIALOGUE_MENU         = "Global: Open Dialogue Menu"  autoReadOnly hidden

string property KEY_N_TOGGLE_MEMBER         = "NPC: Toggle Member"          autoReadOnly hidden
string property KEY_N_TOGGLE_MOVE           = "NPC: Toggle Move"            autoReadOnly hidden
string property KEY_N_MOVE_FARTHER          = "NPC: Move Farther"           autoReadOnly hidden
string property KEY_N_MOVE_NEARER           = "NPC: Move Nearer"            autoReadOnly hidden
string property KEY_N_MOVE_ROTATE_LEFT      = "NPC: Rotate Left"            autoReadOnly hidden
string property KEY_N_MOVE_ROTATE_RIGHT     = "NPC: Rotate Right"           autoReadOnly hidden
string property KEY_N_HAS_BASE              = "NPC: Has Base"               autoReadOnly hidden
string property KEY_N_COUNT_BASE            = "NPC: Count Base"             autoReadOnly hidden
string property KEY_N_HAS_HEAD              = "NPC: Has Head"               autoReadOnly hidden
string property KEY_N_COUNT_HEADS           = "NPC: Count Heads"            autoReadOnly hidden

string property KEY_M_TOGGLE_CLONE          = "Member: Toggle Clone"        autoReadOnly hidden
string property KEY_M_TOGGLE_SETTLER        = "Member: Toggle Settler"      autoReadOnly hidden
string property KEY_M_TOGGLE_THRALL         = "Member: Toggle Thrall"       autoReadOnly hidden
string property KEY_M_TOGGLE_IMMOBILE       = "Member: Toggle Immobile"     autoReadOnly hidden
string property KEY_M_TOGGLE_PARALYZED      = "Member: Toggle Paralyzed"    autoReadOnly hidden
string property KEY_M_TOGGLE_FOLLOWER       = "Member: Toggle Follower"     autoReadOnly hidden

string property KEY_F_TOGGLE_SNEAK          = "Follower: Toggle Sneak"      autoReadOnly hidden
string property KEY_F_TOGGLE_SADDLER        = "Follower: Toggle Saddler"    autoReadOnly hidden

string property KEY_MS_TOGGLE_DISPLAY       = "Members: Toggle Display"     autoReadOnly hidden
string property KEY_MS_DISPLAY_PREVIOUS     = "Members: Display Previous"   autoReadOnly hidden
string property KEY_MS_DISPLAY_NEXT         = "Members: Display Next"       autoReadOnly hidden

string property KEY_FS_SUMMON_ALL           = "Followers: Summon All"       autoReadOnly hidden
string property KEY_FS_SUMMON_MOBILE        = "Followers: Summon Mobile"    autoReadOnly hidden
string property KEY_FS_SUMMON_IMMOBILE      = "Followers: Summon Immobile"  autoReadOnly hidden
string property KEY_FS_SETTLE               = "Followers: Settle"           autoReadOnly hidden
string property KEY_FS_UNSETTLE             = "Followers: Unsettle"         autoReadOnly hidden
string property KEY_FS_MOBILIZE             = "Followers: Mobilize"         autoReadOnly hidden
string property KEY_FS_IMMOBILIZE           = "Followers: Immobilize"       autoReadOnly hidden
string property KEY_FS_SNEAK                = "Followers: Sneak"            autoReadOnly hidden
string property KEY_FS_UNSNEAK              = "Followers: Unsneak"          autoReadOnly hidden
string property KEY_FS_SADDLE               = "Followers: Saddle"           autoReadOnly hidden
string property KEY_FS_UNSADDLE             = "Followers: Unsaddle"         autoReadOnly hidden
string property KEY_FS_RESURRECT            = "Followers: Resurrect"        autoReadOnly hidden

; Private Variables
string              p_pressed_hotkey    =    ""

; Friend Methods
function f_Register()
    Update_Keys()
endFunction

; Native Methods
int function Default_Value(string key) native
int function Current_Value(string key) native
int[] function Default_Mods(string key) native
int[] function Current_Mods(string key) native
function Change_Current_Mods(string key, int mod_1, int mod_2, int mod_3) native
string function Default_Mods_To_String(string key) native
string function Current_Mods_To_String(string key) native
string function Conflicting_Hotkey(string key, int value, int mod_1, int mod_2, int mod_3) native
string function Pressed_Hotkey(int value \
                              ,int pressed_1 = -1, int pressed_2 = -1, int pressed_3 = -1, int pressed_4 = -1 \
                              ,int pressed_5 = -1, int pressed_6 = -1, int pressed_7 = -1, int pressed_8 = -1) native

; Public Methods
function Update_Keys();;;
    UnregisterForAllKeys()

    ; General
    if VARS.key_g_dialogue_menu > -1
        RegisterForKey(VARS.key_g_dialogue_menu)
    endIf

    ; NPC
    if VARS.key_n_toggle_member > -1
        RegisterForKey(VARS.key_n_toggle_member)
    endIf
    if VARS.key_n_toggle_move > -1
        RegisterForKey(VARS.key_n_toggle_move)
    endIf
    ACTORS.MOVEE.Update_Keys()
    if VARS.key_n_has_base > -1
        RegisterForKey(VARS.key_n_has_base)
    endIf
    if VARS.key_n_count_base > -1
        RegisterForKey(VARS.key_n_count_base)
    endIf
    if VARS.key_n_has_head > -1
        RegisterForKey(VARS.key_n_has_head)
    endIf
    if VARS.key_n_count_heads > -1
        RegisterForKey(VARS.key_n_count_heads)
    endIf

    ; Member
    if VARS.key_m_toggle_clone > -1
        RegisterForKey(VARS.key_m_toggle_clone)
    endIf
    if VARS.key_m_toggle_settler > -1
        RegisterForKey(VARS.key_m_toggle_settler)
    endIf
    if VARS.key_m_toggle_thrall > -1
        RegisterForKey(VARS.key_m_toggle_thrall)
    endIf
    if VARS.key_m_toggle_immobile > -1
        RegisterForKey(VARS.key_m_toggle_immobile)
    endIf
    if VARS.key_m_toggle_paralyzed > -1
        RegisterForKey(VARS.key_m_toggle_paralyzed)
    endIf
    if VARS.key_m_toggle_follower > -1
        RegisterForKey(VARS.key_m_toggle_follower)
    endIf

    ; Follower
    if VARS.key_f_toggle_sneak > -1
        RegisterForKey(VARS.key_f_toggle_sneak)
    endIf
    if VARS.key_f_toggle_saddler > -1
        RegisterForKey(VARS.key_f_toggle_saddler)
    endIf

    ; Members
    if VARS.key_ms_toggle_display > -1
        RegisterForKey(VARS.key_ms_toggle_display)
    endIf
    if VARS.key_ms_display_previous > -1
        RegisterForKey(VARS.key_ms_display_previous)
    endIf
    if VARS.key_ms_display_next > -1
        RegisterForKey(VARS.key_ms_display_next)
    endIf

    ; Followers
    if VARS.key_fs_summon_all > -1
        RegisterForKey(VARS.key_fs_summon_all)
    endIf
    if VARS.key_fs_summon_mobile > -1
        RegisterForKey(VARS.key_fs_summon_mobile)
    endIf
    if VARS.key_fs_summon_immobile > -1
        RegisterForKey(VARS.key_fs_summon_immobile)
    endIf
    if VARS.key_fs_settle > -1
        RegisterForKey(VARS.key_fs_settle)
    endIf
    if VARS.key_fs_unsettle > -1
        RegisterForKey(VARS.key_fs_unsettle)
    endIf
    if VARS.key_fs_mobilize > -1
        RegisterForKey(VARS.key_fs_mobilize)
    endIf
    if VARS.key_fs_immobilize > -1
        RegisterForKey(VARS.key_fs_immobilize)
    endIf
    if VARS.key_fs_sneak > -1
        RegisterForKey(VARS.key_fs_sneak)
    endIf
    if VARS.key_fs_unsneak > -1
        RegisterForKey(VARS.key_fs_unsneak)
    endIf
    if VARS.key_fs_saddle > -1
        RegisterForKey(VARS.key_fs_saddle)
    endIf
    if VARS.key_fs_unsaddle > -1
        RegisterForKey(VARS.key_fs_unsaddle)
    endIf
    if VARS.key_fs_resurrect > -1
        RegisterForKey(VARS.key_fs_resurrect)
    endIf
    if VARS.key_fs_unfollow > -1
        RegisterForKey(VARS.key_fs_unfollow)
    endIf
    if VARS.key_fs_unmember > -1
        RegisterForKey(VARS.key_fs_unmember)
    endIf
endFunction

; Events
event OnKeyDown(int value) native
event OnKeyUp(int key_code, float time_held) native
