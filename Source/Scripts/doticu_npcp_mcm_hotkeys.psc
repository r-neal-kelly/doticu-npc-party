;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_hotkeys extends Quest

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
doticu_npcp_keys property KEYS hidden
    doticu_npcp_keys function Get()
        return p_DATA.MODS.CONTROL.KEYS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return p_DATA.MODS.CONTROL.MCM
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA                              =  none

; Private Variables
bool                p_is_created                        = false

; Global
int                 p_option_g_dialogue_menu            =    -1

int                 p_option_g_dialogue_menu_mods       =    -1

; NPC
int                 p_option_n_toggle_member            =    -1
int                 p_option_n_toggle_move              =    -1
int                 p_option_n_move_nearer              =    -1
int                 p_option_n_move_farther             =    -1
int                 p_option_n_move_rotate_left         =    -1
int                 p_option_n_move_rotate_right        =    -1
int                 p_option_n_has_base                 =    -1
int                 p_option_n_count_base               =    -1
int                 p_option_n_has_head                 =    -1
int                 p_option_n_count_heads              =    -1

int                 p_option_n_toggle_member_mods       =    -1
int                 p_option_n_toggle_move_mods         =    -1
int                 p_option_n_move_farther_mods        =    -1
int                 p_option_n_move_nearer_mods         =    -1
int                 p_option_n_move_rotate_left_mods    =    -1
int                 p_option_n_move_rotate_right_mods   =    -1
int                 p_option_n_has_base_mods            =    -1
int                 p_option_n_count_base_mods          =    -1
int                 p_option_n_has_head_mods            =    -1
int                 p_option_n_count_heads_mods         =    -1

; Member
int                 p_option_m_toggle_clone             =    -1
int                 p_option_m_toggle_settler           =    -1
int                 p_option_m_toggle_thrall            =    -1
int                 p_option_m_toggle_immobile          =    -1
int                 p_option_m_toggle_paralyzed         =    -1
int                 p_option_m_toggle_follower          =    -1

int                 p_option_m_toggle_clone_mods        =    -1
int                 p_option_m_toggle_settler_mods      =    -1
int                 p_option_m_toggle_thrall_mods       =    -1
int                 p_option_m_toggle_immobile_mods     =    -1
int                 p_option_m_toggle_paralyzed_mods    =    -1
int                 p_option_m_toggle_follower_mods     =    -1

; Follower
int                 p_option_f_toggle_sneak             =    -1
int                 p_option_f_toggle_saddler           =    -1

int                 p_option_f_toggle_sneak_mods        =    -1
int                 p_option_f_toggle_saddler_mods      =    -1

; Members
int                 p_option_ms_toggle_display          =    -1
int                 p_option_ms_display_previous        =    -1
int                 p_option_ms_display_next            =    -1

int                 p_option_ms_toggle_display_mods     =    -1
int                 p_option_ms_display_previous_mods   =    -1
int                 p_option_ms_display_next_mods       =    -1

; Followers
int                 p_option_fs_summon_all              =    -1
int                 p_option_fs_summon_mobile           =    -1
int                 p_option_fs_summon_immobile         =    -1
int                 p_option_fs_settle                  =    -1
int                 p_option_fs_unsettle                =    -1
int                 p_option_fs_mobilize                =    -1
int                 p_option_fs_immobilize              =    -1
int                 p_option_fs_sneak                   =    -1
int                 p_option_fs_unsneak                 =    -1
int                 p_option_fs_saddle                  =    -1
int                 p_option_fs_unsaddle                =    -1
int                 p_option_fs_resurrect               =    -1

int                 p_option_fs_summon_all_mods         =    -1
int                 p_option_fs_summon_mobile_mods      =    -1
int                 p_option_fs_summon_immobile_mods    =    -1
int                 p_option_fs_settle_mods             =    -1
int                 p_option_fs_unsettle_mods           =    -1
int                 p_option_fs_mobilize_mods           =    -1
int                 p_option_fs_immobilize_mods         =    -1
int                 p_option_fs_sneak_mods              =    -1
int                 p_option_fs_unsneak_mods            =    -1
int                 p_option_fs_saddle_mods             =    -1
int                 p_option_fs_unsaddle_mods           =    -1
int                 p_option_fs_resurrect_mods          =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Build_Page()
    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    MCM.SetTitleText(" Hotkeys ")

    MCM.AddHeaderOption(" Global ")
    MCM.AddEmptyOption()
    p_option_g_dialogue_menu = MCM.AddKeymapOption(" Dialogue Menu ", VARS.key_g_dialogue_menu, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_g_dialogue_menu_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_G_DIALOGUE_MENU))
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" NPC ")
    MCM.AddEmptyOption()
    p_option_n_toggle_member = MCM.AddKeymapOption(" Toggle Member ", VARS.key_n_toggle_member, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_toggle_member_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_TOGGLE_MEMBER))

    p_option_n_toggle_move = MCM.AddKeymapOption(" Toggle Move ", VARS.key_n_toggle_move, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_toggle_move_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_TOGGLE_MOVE))

    p_option_n_move_nearer = MCM.AddKeymapOption(" Move Nearer ", VARS.key_n_move_nearer, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_nearer_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_MOVE_NEARER))

    p_option_n_move_farther = MCM.AddKeymapOption(" Move Farther ", VARS.key_n_move_farther, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_farther_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_MOVE_FARTHER))

    p_option_n_move_rotate_left = MCM.AddKeymapOption(" Move Clockwise ", VARS.key_n_move_rotate_left, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_rotate_left_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_MOVE_ROTATE_LEFT))

    p_option_n_move_rotate_right = MCM.AddKeymapOption(" Move Counter-Clockwise ", VARS.key_n_move_rotate_right, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_rotate_right_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_MOVE_ROTATE_RIGHT))

    p_option_n_has_base = MCM.AddKeymapOption(" Has Base ", VARS.key_n_has_base, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_has_base_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_HAS_BASE))

    p_option_n_count_base = MCM.AddKeymapOption(" Count Base ", VARS.key_n_count_base, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_count_base_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_COUNT_BASE))

    p_option_n_has_head = MCM.AddKeymapOption(" Has Head ", VARS.key_n_has_head, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_has_head_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_HAS_HEAD))

    p_option_n_count_heads = MCM.AddKeymapOption(" Count Heads ", VARS.key_n_count_heads, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_count_heads_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_N_COUNT_HEADS))
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Member ")
    MCM.AddEmptyOption()
    p_option_m_toggle_clone = MCM.AddKeymapOption(" Toggle Clone ", VARS.key_m_toggle_clone, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_clone_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_M_TOGGLE_CLONE))

    p_option_m_toggle_settler = MCM.AddKeymapOption(" Toggle Settler ", VARS.key_m_toggle_settler, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_settler_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_M_TOGGLE_SETTLER))

    p_option_m_toggle_thrall = MCM.AddKeymapOption(" Toggle Thrall ", VARS.key_m_toggle_thrall, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_thrall_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_M_TOGGLE_THRALL))

    p_option_m_toggle_immobile = MCM.AddKeymapOption(" Toggle Immobile ", VARS.key_m_toggle_immobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_immobile_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_M_TOGGLE_IMMOBILE))

    p_option_m_toggle_paralyzed = MCM.AddKeymapOption(" Toggle Paralyzed ", VARS.key_m_toggle_paralyzed, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_paralyzed_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_M_TOGGLE_PARALYZED))

    p_option_m_toggle_follower = MCM.AddKeymapOption(" Toggle Follower ", VARS.key_m_toggle_follower, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_follower_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_M_TOGGLE_FOLLOWER))
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Follower ")
    MCM.AddEmptyOption()
    p_option_f_toggle_sneak = MCM.AddKeymapOption(" Toggle Sneak ", VARS.key_f_toggle_sneak, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_f_toggle_sneak_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_F_TOGGLE_SNEAK))

    p_option_f_toggle_saddler = MCM.AddKeymapOption(" Toggle Saddler ", VARS.key_f_toggle_saddler, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_f_toggle_saddler_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_F_TOGGLE_SADDLER))
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Members ")
    MCM.AddEmptyOption()
    p_option_ms_toggle_display = MCM.AddKeymapOption(" Toggle Display ", VARS.key_ms_toggle_display, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_ms_toggle_display_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_MS_TOGGLE_DISPLAY))

    p_option_ms_display_previous = MCM.AddKeymapOption(" Display Previous ", VARS.key_ms_display_previous, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_ms_display_previous_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_MS_DISPLAY_PREVIOUS))

    p_option_ms_display_next = MCM.AddKeymapOption(" Display Next ", VARS.key_ms_display_next, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_ms_display_next_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_MS_DISPLAY_NEXT))
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Followers ")
    MCM.AddEmptyOption()
    p_option_fs_summon_all = MCM.AddKeymapOption(" Summon All ", VARS.key_fs_summon_all, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_summon_all_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_SUMMON_ALL))

    p_option_fs_summon_mobile = MCM.AddKeymapOption(" Summon Mobile ", VARS.key_fs_summon_mobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_summon_mobile_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_SUMMON_MOBILE))

    p_option_fs_summon_immobile = MCM.AddKeymapOption(" Summon Immobile ", VARS.key_fs_summon_immobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_summon_immobile_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_SUMMON_IMMOBILE))

    p_option_fs_settle = MCM.AddKeymapOption(" Settle ", VARS.key_fs_settle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_settle_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_SETTLE))

    p_option_fs_unsettle = MCM.AddKeymapOption(" Unsettle ", VARS.key_fs_unsettle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_unsettle_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_UNSETTLE))

    p_option_fs_mobilize = MCM.AddKeymapOption(" Mobilize ", VARS.key_fs_mobilize, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_mobilize_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_MOBILIZE))

    p_option_fs_immobilize = MCM.AddKeymapOption(" Immobilize ", VARS.key_fs_immobilize, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_immobilize_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_IMMOBILIZE))

    p_option_fs_sneak = MCM.AddKeymapOption(" Sneak ", VARS.key_fs_sneak, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_sneak_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_SNEAK))

    p_option_fs_unsneak = MCM.AddKeymapOption(" Unsneak ", VARS.key_fs_unsneak, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_unsneak_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_UNSNEAK))

    p_option_fs_saddle = MCM.AddKeymapOption(" Saddle ", VARS.key_fs_saddle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_saddle_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_SADDLE))

    p_option_fs_unsaddle = MCM.AddKeymapOption(" Unsaddle ", VARS.key_fs_unsaddle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_unsaddle_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_UNSADDLE))

    p_option_fs_resurrect = MCM.AddKeymapOption(" Resurrect ", VARS.key_fs_resurrect, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_resurrect_mods = MCM.AddTextOption(" Mods ", KEYS.Current_Mods_To_String(CONSTS.KEY_FS_RESURRECT))
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
endFunction

function f_On_Option_Keymap_Change(int id_option, int value, string conflicting_hotkey, string conflicting_mod)
    string hotkey = p_Value_Option_to_Hotkey(id_option)
    if !hotkey
        return
    endIf

    if value == KEYS.Current_Value(hotkey)
        return
    endIf

    if value > -1 && conflicting_hotkey && conflicting_mod != MCM.ModName
        string str_conflict_message = "This conflicts with '" + conflicting_hotkey + "'"
        if conflicting_mod
            str_conflict_message += " in the mod '" + conflicting_mod + "'."
        else
            str_conflict_message += " in vanilla Skyrim."
        endIf
        str_conflict_message += " Set key anyway?"
        if !MCM.ShowMessage(str_conflict_message, true)
            return
        endIf
    endIf

    int[] mods = KEYS.Current_Mods(hotkey)
    if !p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
        return
    endIf

    if false

    ; Global
    elseIf id_option == p_option_g_dialogue_menu
        VARS.key_g_dialogue_menu = value

    ; NPC
    elseIf id_option == p_option_n_toggle_member
        VARS.key_n_toggle_member = value
    elseIf id_option == p_option_n_toggle_move
        VARS.key_n_toggle_move = value
    elseIf id_option == p_option_n_move_nearer
        VARS.key_n_move_nearer = value
    elseIf id_option == p_option_n_move_farther
        VARS.key_n_move_farther = value
    elseIf id_option == p_option_n_move_rotate_left
        VARS.key_n_move_rotate_left = value
    elseIf id_option == p_option_n_move_rotate_right
        VARS.key_n_move_rotate_right = value
    elseIf id_option == p_option_n_has_base
        VARS.key_n_has_base = value
    elseIf id_option == p_option_n_count_base
        VARS.key_n_count_base = value
    elseIf id_option == p_option_n_has_head
        VARS.key_n_has_head = value
    elseIf id_option == p_option_n_count_heads
        VARS.key_n_count_heads = value

    ; Member
    elseIf id_option == p_option_m_toggle_clone
        VARS.key_m_toggle_clone = value
    elseIf id_option == p_option_m_toggle_settler
        VARS.key_m_toggle_settler = value
    elseIf id_option == p_option_m_toggle_thrall
        VARS.key_m_toggle_thrall = value
    elseIf id_option == p_option_m_toggle_immobile
        VARS.key_m_toggle_immobile = value
    elseIf id_option == p_option_m_toggle_paralyzed
        VARS.key_m_toggle_paralyzed = value
    elseIf id_option == p_option_m_toggle_follower
        VARS.key_m_toggle_follower = value

    ; Follower
    elseIf id_option == p_option_f_toggle_sneak
        VARS.key_f_toggle_sneak = value
    elseIf id_option == p_option_f_toggle_saddler
        VARS.key_f_toggle_saddler = value

    ; Members
    elseIf id_option == p_option_ms_toggle_display
        VARS.key_ms_toggle_display = value
    elseIf id_option == p_option_ms_display_previous
        VARS.key_ms_display_previous = value
    elseIf id_option == p_option_ms_display_next
        VARS.key_ms_display_next = value

    ; Followers
    elseIf id_option == p_option_fs_summon_all
        VARS.key_fs_summon_all = value
    elseIf id_option == p_option_fs_summon_mobile
        VARS.key_fs_summon_mobile = value
    elseIf id_option == p_option_fs_summon_immobile
        VARS.key_fs_summon_immobile = value
    elseIf id_option == p_option_fs_settle
        VARS.key_fs_settle = value
    elseIf id_option == p_option_fs_unsettle
        VARS.key_fs_unsettle = value
    elseIf id_option == p_option_fs_immobilize
        VARS.key_fs_immobilize = value
    elseIf id_option == p_option_fs_mobilize
        VARS.key_fs_mobilize = value
    elseIf id_option == p_option_fs_sneak
        VARS.key_fs_sneak = value
    elseIf id_option == p_option_fs_unsneak
        VARS.key_fs_unsneak = value
    elseIf id_option == p_option_fs_saddle
        VARS.key_fs_saddle = value
    elseIf id_option == p_option_fs_unsaddle
        VARS.key_fs_unsaddle = value
    elseIf id_option == p_option_fs_resurrect
        VARS.key_fs_resurrect = value

    else
        return

    endIf

    MCM.SetKeymapOptionValue(id_option, value, false)
    KEYS.Update_Keys()
endFunction

function f_On_Option_Select(int id_option)
    string hotkey = p_Mods_Option_to_Hotkey(id_option)
    if !hotkey
        return
    endIf

    int value = KEYS.Current_Value(hotkey)
    int[] mods = p_Read_Pressed_Mods()
    if !mods || !p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
        return
    endIf

    if false

    ; Global
    elseIf id_option == p_option_g_dialogue_menu_mods
        VARS.key_g_dialogue_menu_mods = mods

    ; NPC
    elseIf id_option == p_option_n_toggle_member_mods
        VARS.key_n_toggle_member_mods = mods
    elseIf id_option == p_option_n_toggle_move_mods
        VARS.key_n_toggle_move_mods = mods
    elseIf id_option == p_option_n_move_farther_mods
        VARS.key_n_move_farther_mods = mods
    elseIf id_option == p_option_n_move_nearer_mods
        VARS.key_n_move_nearer_mods = mods
    elseIf id_option == p_option_n_move_rotate_right_mods
        VARS.key_n_move_rotate_right_mods = mods
    elseIf id_option == p_option_n_move_rotate_left_mods
        VARS.key_n_move_rotate_left_mods = mods
    elseIf id_option == p_option_n_has_base_mods
        VARS.key_n_has_base_mods = mods
    elseIf id_option == p_option_n_count_base_mods
        VARS.key_n_count_base_mods = mods
    elseIf id_option == p_option_n_has_head_mods
        VARS.key_n_has_head_mods = mods
    elseIf id_option == p_option_n_count_heads_mods
        VARS.key_n_count_heads_mods = mods

    ; Member
    elseIf id_option == p_option_m_toggle_clone_mods
        VARS.key_m_toggle_clone_mods = mods
    elseIf id_option == p_option_m_toggle_settler_mods
        VARS.key_m_toggle_settler_mods = mods
    elseIf id_option == p_option_m_toggle_thrall_mods
        VARS.key_m_toggle_thrall_mods = mods
    elseIf id_option == p_option_m_toggle_immobile_mods
        VARS.key_m_toggle_immobile_mods = mods
    elseIf id_option == p_option_m_toggle_paralyzed_mods
        VARS.key_m_toggle_paralyzed_mods = mods
    elseIf id_option == p_option_m_toggle_follower_mods
        VARS.key_m_toggle_follower_mods = mods

    ; Follower
    elseIf id_option == p_option_f_toggle_sneak_mods
        VARS.key_f_toggle_sneak_mods = mods
    elseIf id_option == p_option_f_toggle_saddler_mods
        VARS.key_f_toggle_saddler_mods = mods

    ; Members
    elseIf id_option == p_option_ms_toggle_display_mods
        VARS.key_ms_toggle_display_mods = mods
    elseIf id_option == p_option_ms_display_previous_mods
        VARS.key_ms_display_previous_mods = mods
    elseIf id_option == p_option_ms_display_next_mods
        VARS.key_ms_display_next_mods = mods

    ; Followers
    elseIf id_option == p_option_fs_summon_all_mods
        VARS.key_fs_summon_all_mods = mods
    elseIf id_option == p_option_fs_summon_mobile_mods
        VARS.key_fs_summon_mobile_mods = mods
    elseIf id_option == p_option_fs_summon_immobile_mods
        VARS.key_fs_summon_immobile_mods = mods
    elseIf id_option == p_option_fs_settle_mods
        VARS.key_fs_settle_mods = mods
    elseIf id_option == p_option_fs_unsettle_mods
        VARS.key_fs_unsettle_mods = mods
    elseIf id_option == p_option_fs_immobilize_mods
        VARS.key_fs_immobilize_mods = mods
    elseIf id_option == p_option_fs_mobilize_mods
        VARS.key_fs_mobilize_mods = mods
    elseIf id_option == p_option_fs_sneak_mods
        VARS.key_fs_sneak_mods = mods
    elseIf id_option == p_option_fs_unsneak_mods
        VARS.key_fs_unsneak_mods = mods
    elseIf id_option == p_option_fs_saddle_mods
        VARS.key_fs_saddle_mods = mods
    elseIf id_option == p_option_fs_unsaddle_mods
        VARS.key_fs_unsaddle_mods = mods
    elseIf id_option == p_option_fs_resurrect_mods
        VARS.key_fs_resurrect_mods = mods

    else
        return

    endIf

    MCM.SetTextOptionValue(id_option, KEYS.Current_Mods_To_String(hotkey), false)
    KEYS.Update_Keys(); is this necessary for mods?
endFunction

function f_On_Option_Default(int id_option)
    string hotkey = p_Value_Option_To_Hotkey(id_option)
    if hotkey
        p_Set_Default_Value(id_option, hotkey)
    else
        hotkey = p_Mods_Option_to_Hotkey(id_option)
        if hotkey
            p_Set_Default_Mods(id_option, hotkey)
        endIf
    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    string hotkey_message = "Set a combination of modifier keys that must be pressed for this hotkey to work."

    if false

    ; Global
    elseIf id_option == p_option_g_dialogue_menu
        MCM.SetInfoText("Opens the global dialogue menu, which you can use to make global commands.")
    elseIf id_option == p_option_g_dialogue_menu_mods
        MCM.SetInfoText(hotkey_message)

    ; NPC
    elseIf id_option == p_option_n_toggle_member
        MCM.SetInfoText("Causes an npc to be membered or unmembered.")
    elseIf id_option == p_option_n_toggle_move
        MCM.SetInfoText("Toggles the act of moving an npc.")
    elseIf id_option == p_option_n_move_nearer
        MCM.SetInfoText("While moving an npc, this will make them come closer to you.")
    elseIf id_option == p_option_n_move_farther
        MCM.SetInfoText("While moving an npc, this will make them go farther away from you.")
    elseIf id_option == p_option_n_move_rotate_left
        MCM.SetInfoText("While moving an npc, this will make them turn clockwise.")
    elseIf id_option == p_option_n_move_rotate_right
        MCM.SetInfoText("While moving an npc, this will make them turn counter-clockwise.")
    elseIf id_option == p_option_n_has_base
        MCM.SetInfoText("Shows whether or not you have a member with the same base as this npc.")
    elseIf id_option == p_option_n_count_base
        MCM.SetInfoText("Shows how many members you have with the same base as this npc.")
    elseIf id_option == p_option_n_has_head
        MCM.SetInfoText("Shows whether or not you have a member with the same head and face.")
    elseIf id_option == p_option_n_count_heads
        MCM.SetInfoText("Show how many members you have with the same head and face.")
    elseIf id_option == p_option_n_toggle_member_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_toggle_move_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_move_nearer_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_move_farther_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_move_rotate_left_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_move_rotate_right_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_has_base_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_count_base_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_has_head_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_n_count_heads_mods
        MCM.SetInfoText(hotkey_message)

    ; Member
    elseIf id_option == p_option_m_toggle_clone
        MCM.SetInfoText("Causes an npc to be cloned or uncloned. The npc will become a member if they are not already.")
    elseIf id_option == p_option_m_toggle_settler
        MCM.SetInfoText("Causes an npc to be settled or unsettled. The npc will become a member if they are not already.")
    elseIf id_option == p_option_m_toggle_thrall
        MCM.SetInfoText("Causes an npc to be enthralled or unthralled. The npc will become a member if they are not already.")
    elseIf id_option == p_option_m_toggle_immobile
        MCM.SetInfoText("Causes an npc to be immobile or mobile. The npc will become a member if they are not already.")
    elseIf id_option == p_option_m_toggle_paralyzed
        MCM.SetInfoText("Causes an npc to be paralyzed or unparalyzed. The npc will become a member if they are not already.")
    elseIf id_option == p_option_m_toggle_follower
        MCM.SetInfoText("Causes an npc to follow or unfollow. The npc will become a member if they are not already.")
    elseIf id_option == p_option_m_toggle_clone_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_m_toggle_settler_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_m_toggle_thrall_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_m_toggle_immobile_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_m_toggle_paralyzed_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_m_toggle_follower_mods
        MCM.SetInfoText(hotkey_message)

    ; Follower
    elseIf id_option == p_option_f_toggle_sneak
        MCM.SetInfoText("Causes an npc to sneak or unsneak. The npc will become a member and a follower if they are not already.")
    elseIf id_option == p_option_f_toggle_saddler
        MCM.SetInfoText("Causes an npc to saddle or unsaddle. The npc will become a member and a follower if they are not already.")
    elseIf id_option == p_option_f_toggle_sneak_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_f_toggle_saddler_mods
        MCM.SetInfoText(hotkey_message)

    ; Members
    elseIf id_option == p_option_ms_toggle_display
        MCM.SetInfoText("Toggles a member display.")
    elseIf id_option == p_option_ms_display_previous
        MCM.SetInfoText("Will loop through the previous members on display.")
    elseIf id_option == p_option_ms_display_next
        MCM.SetInfoText("Will loop through the next members on display.")
    elseIf id_option == p_option_ms_toggle_display_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_ms_display_previous_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_ms_display_next_mods
        MCM.SetInfoText(hotkey_message)

    ; Followers
    elseIf id_option == p_option_fs_summon_all
        MCM.SetInfoText("Summons all followers before you.")
    elseIf id_option == p_option_fs_summon_mobile
        MCM.SetInfoText("Summons only mobilized followers before you.")
    elseIf id_option == p_option_fs_summon_immobile
        MCM.SetInfoText("Summons only immobilized followers before you.")
    elseIf id_option == p_option_fs_settle
        MCM.SetInfoText("Causes all followers to settle or resettle where they are currently standing.")
    elseIf id_option == p_option_fs_unsettle
        MCM.SetInfoText("Causes all followers to no longer be settlers.")
    elseIf id_option == p_option_fs_mobilize
        MCM.SetInfoText("Causes all followers to become mobile.")
    elseIf id_option == p_option_fs_immobilize
        MCM.SetInfoText("Causes all followers to become immobile.")
    elseIf id_option == p_option_fs_sneak
        MCM.SetInfoText("Causes all followers to start sneaking.")
    elseIf id_option == p_option_fs_unsneak
        MCM.SetInfoText("Causes all followers to stop sneaking.")
    elseIf id_option == p_option_fs_saddle
        MCM.SetInfoText("Causes all followers to saddle their horses.")
    elseIf id_option == p_option_fs_unsaddle
        MCM.SetInfoText("Causes all followers to unsaddle their horses.")
    elseIf id_option == p_option_fs_resurrect
        MCM.SetInfoText("Causes all dead followers to resurrect.")
    elseIf id_option == p_option_fs_summon_all_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_summon_mobile_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_summon_immobile_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_settle_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_unsettle_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_mobilize_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_immobilize_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_sneak_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_unsneak_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_saddle_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_unsaddle_mods
        MCM.SetInfoText(hotkey_message)
    elseIf id_option == p_option_fs_resurrect_mods
        MCM.SetInfoText(hotkey_message)

    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
endFunction

function f_On_Option_Menu_Open(int id_option)
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

; Private Methods
string function p_Value_Option_to_Hotkey(int id_option)
    if false

    ; Global
    elseIf id_option == p_option_g_dialogue_menu
        return CONSTS.KEY_G_DIALOGUE_MENU

    ; NPC
    elseIf id_option == p_option_n_toggle_member
        return CONSTS.KEY_N_TOGGLE_MEMBER
    elseIf id_option == p_option_n_toggle_move
        return CONSTS.KEY_N_TOGGLE_MOVE
    elseIf id_option == p_option_n_move_farther
        return CONSTS.KEY_N_MOVE_FARTHER
    elseIf id_option == p_option_n_move_nearer
        return CONSTS.KEY_N_MOVE_NEARER
    elseIf id_option == p_option_n_move_rotate_right
        return CONSTS.KEY_N_MOVE_ROTATE_RIGHT
    elseIf id_option == p_option_n_move_rotate_left
        return CONSTS.KEY_N_MOVE_ROTATE_LEFT
    elseIf id_option == p_option_n_has_base
        return CONSTS.KEY_N_HAS_BASE
    elseIf id_option == p_option_n_count_base
        return CONSTS.KEY_N_COUNT_BASE
    elseIf id_option == p_option_n_has_head
        return CONSTS.KEY_N_HAS_HEAD
    elseIf id_option == p_option_n_count_heads
        return CONSTS.KEY_N_COUNT_HEADS

    ; Member
    elseIf id_option == p_option_m_toggle_clone
        return CONSTS.KEY_M_TOGGLE_CLONE
    elseIf id_option == p_option_m_toggle_settler
        return CONSTS.KEY_M_TOGGLE_SETTLER
    elseIf id_option == p_option_m_toggle_thrall
        return CONSTS.KEY_M_TOGGLE_THRALL
    elseIf id_option == p_option_m_toggle_immobile
        return CONSTS.KEY_M_TOGGLE_IMMOBILE
    elseIf id_option == p_option_m_toggle_paralyzed
        return CONSTS.KEY_M_TOGGLE_PARALYZED
    elseIf id_option == p_option_m_toggle_follower
        return CONSTS.KEY_M_TOGGLE_FOLLOWER

    ; Follower
    elseIf id_option == p_option_f_toggle_sneak
        return CONSTS.KEY_F_TOGGLE_SNEAK
    elseIf id_option == p_option_f_toggle_saddler
        return CONSTS.KEY_F_TOGGLE_SADDLER

    ; Members
    elseIf id_option == p_option_ms_toggle_display
        return CONSTS.KEY_MS_TOGGLE_DISPLAY
    elseIf id_option == p_option_ms_display_previous
        return CONSTS.KEY_MS_DISPLAY_PREVIOUS
    elseIf id_option == p_option_ms_display_next
        return CONSTS.KEY_MS_DISPLAY_NEXT

    ; Followers
    elseIf id_option == p_option_fs_summon_all
        return CONSTS.KEY_FS_SUMMON_ALL
    elseIf id_option == p_option_fs_summon_mobile
        return CONSTS.KEY_FS_SUMMON_MOBILE
    elseIf id_option == p_option_fs_summon_immobile
        return CONSTS.KEY_FS_SUMMON_IMMOBILE
    elseIf id_option == p_option_fs_settle
        return CONSTS.KEY_FS_SETTLE
    elseIf id_option == p_option_fs_unsettle
        return CONSTS.KEY_FS_UNSETTLE
    elseIf id_option == p_option_fs_mobilize
        return CONSTS.KEY_FS_MOBILIZE
    elseIf id_option == p_option_fs_immobilize
        return CONSTS.KEY_FS_IMMOBILIZE
    elseIf id_option == p_option_fs_sneak
        return CONSTS.KEY_FS_SNEAK
    elseIf id_option == p_option_fs_unsneak
        return CONSTS.KEY_FS_UNSNEAK
    elseIf id_option == p_option_fs_saddle
        return CONSTS.KEY_FS_SADDLE
    elseIf id_option == p_option_fs_unsaddle
        return CONSTS.KEY_FS_UNSADDLE
    elseIf id_option == p_option_fs_resurrect
        return CONSTS.KEY_FS_RESURRECT

    else
        return ""

    endIf
endFunction

string function p_Mods_Option_to_Hotkey(int id_option)
    if false

    ; Global
    elseIf id_option == p_option_g_dialogue_menu_mods
        return CONSTS.KEY_G_DIALOGUE_MENU

    ; NPC
    elseIf id_option == p_option_n_toggle_member_mods
        return CONSTS.KEY_N_TOGGLE_MEMBER
    elseIf id_option == p_option_n_toggle_move_mods
        return CONSTS.KEY_N_TOGGLE_MOVE
    elseIf id_option == p_option_n_move_farther_mods
        return CONSTS.KEY_N_MOVE_FARTHER
    elseIf id_option == p_option_n_move_nearer_mods
        return CONSTS.KEY_N_MOVE_NEARER
    elseIf id_option == p_option_n_move_rotate_right_mods
        return CONSTS.KEY_N_MOVE_ROTATE_RIGHT
    elseIf id_option == p_option_n_move_rotate_left_mods
        return CONSTS.KEY_N_MOVE_ROTATE_LEFT
    elseIf id_option == p_option_n_has_base_mods
        return CONSTS.KEY_N_HAS_BASE
    elseIf id_option == p_option_n_count_base_mods
        return CONSTS.KEY_N_COUNT_BASE
    elseIf id_option == p_option_n_has_head_mods
        return CONSTS.KEY_N_HAS_HEAD
    elseIf id_option == p_option_n_count_heads_mods
        return CONSTS.KEY_N_COUNT_HEADS

    ; Member
    elseIf id_option == p_option_m_toggle_clone_mods
        return CONSTS.KEY_M_TOGGLE_CLONE
    elseIf id_option == p_option_m_toggle_settler_mods
        return CONSTS.KEY_M_TOGGLE_SETTLER
    elseIf id_option == p_option_m_toggle_thrall_mods
        return CONSTS.KEY_M_TOGGLE_THRALL
    elseIf id_option == p_option_m_toggle_immobile_mods
        return CONSTS.KEY_M_TOGGLE_IMMOBILE
    elseIf id_option == p_option_m_toggle_paralyzed_mods
        return CONSTS.KEY_M_TOGGLE_PARALYZED
    elseIf id_option == p_option_m_toggle_follower_mods
        return CONSTS.KEY_M_TOGGLE_FOLLOWER

    ; Follower
    elseIf id_option == p_option_f_toggle_sneak_mods
        return CONSTS.KEY_F_TOGGLE_SNEAK
    elseIf id_option == p_option_f_toggle_saddler_mods
        return CONSTS.KEY_F_TOGGLE_SADDLER

    ; Members
    elseIf id_option == p_option_ms_toggle_display_mods
        return CONSTS.KEY_MS_TOGGLE_DISPLAY
    elseIf id_option == p_option_ms_display_previous_mods
        return CONSTS.KEY_MS_DISPLAY_PREVIOUS
    elseIf id_option == p_option_ms_display_next_mods
        return CONSTS.KEY_MS_DISPLAY_NEXT

    ; Followers
    elseIf id_option == p_option_fs_summon_all_mods
        return CONSTS.KEY_FS_SUMMON_ALL
    elseIf id_option == p_option_fs_summon_mobile_mods
        return CONSTS.KEY_FS_SUMMON_MOBILE
    elseIf id_option == p_option_fs_summon_immobile_mods
        return CONSTS.KEY_FS_SUMMON_IMMOBILE
    elseIf id_option == p_option_fs_settle_mods
        return CONSTS.KEY_FS_SETTLE
    elseIf id_option == p_option_fs_unsettle_mods
        return CONSTS.KEY_FS_UNSETTLE
    elseIf id_option == p_option_fs_mobilize_mods
        return CONSTS.KEY_FS_MOBILIZE
    elseIf id_option == p_option_fs_immobilize_mods
        return CONSTS.KEY_FS_IMMOBILIZE
    elseIf id_option == p_option_fs_sneak_mods
        return CONSTS.KEY_FS_SNEAK
    elseIf id_option == p_option_fs_unsneak_mods
        return CONSTS.KEY_FS_UNSNEAK
    elseIf id_option == p_option_fs_saddle_mods
        return CONSTS.KEY_FS_SADDLE
    elseIf id_option == p_option_fs_unsaddle_mods
        return CONSTS.KEY_FS_UNSADDLE
    elseIf id_option == p_option_fs_resurrect_mods
        return CONSTS.KEY_FS_RESURRECT

    else
        return ""

    endIf
endFunction

int[] function p_Read_Pressed_Mods()
    if MCM.ShowMessage("Press and hold up to three keys and click enter. Cancel will leave the mods as they are.", true)
        int[] mods = new int[3]
        mods[0] = -1
        mods[1] = -1
        mods[2] = -1

        int size = Input.GetNumKeysPressed()
        if size > 0
            mods[0] = Input.GetNthKeyPressed(0)
        endIf
        if size > 1
            mods[1] = Input.GetNthKeyPressed(1)
        endIf
        if size > 2
            mods[2] = Input.GetNthKeyPressed(2)
        endIf

        return mods
    else
        return none
    endIf
endFunction

bool function p_Can_Set_Hotkey(string hotkey, int value, int mod_1, int mod_2, int mod_3)
    if value > -1
        string npcp_conflict = KEYS.Conflicting_Key(hotkey, value, mod_1, mod_2, mod_3)
        if npcp_conflict != ""
            return MCM.ShowMessage("This conflicts with '" + npcp_conflict + "'. Set anyway?", true)
        else
            string mcm_conflict = MCM.GetCustomControl(value)
            if mcm_conflict && KEYS.Current_Value(hotkey) != value
                return MCM.ShowMessage("This conflicts with '" + mcm_conflict + "'. Set key anyway?", true)
            else
                return true
            endIf
        endIf
    endIf
endFunction

function p_Set_Default_Value(int id_option, string hotkey)
    if !hotkey
        return
    endIf

    int value = KEYS.Default_Value(hotkey)
    int[] mods = KEYS.Current_Mods(hotkey)
    if !p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
        return
    endIf

    if false

    ; Global
    elseIf id_option == p_option_g_dialogue_menu
        VARS.key_g_dialogue_menu = value

    ; NPC
    elseIf id_option == p_option_n_toggle_member
        VARS.key_n_toggle_member = value
    elseIf id_option == p_option_n_toggle_move
        VARS.key_n_toggle_move = value
    elseIf id_option == p_option_n_move_farther
        VARS.key_n_move_farther = value
    elseIf id_option == p_option_n_move_nearer
        VARS.key_n_move_nearer = value
    elseIf id_option == p_option_n_move_rotate_right
        VARS.key_n_move_rotate_right = value
    elseIf id_option == p_option_n_move_rotate_left
        VARS.key_n_move_rotate_left = value
    elseIf id_option == p_option_n_has_base
        VARS.key_n_has_base = value
    elseIf id_option == p_option_n_count_base
        VARS.key_n_count_base = value
    elseIf id_option == p_option_n_has_head
        VARS.key_n_has_head = value
    elseIf id_option == p_option_n_count_heads
        VARS.key_n_count_heads = value

    ; Member
    elseIf id_option == p_option_m_toggle_clone
        VARS.key_m_toggle_clone = value
    elseIf id_option == p_option_m_toggle_settler
        VARS.key_m_toggle_settler = value
    elseIf id_option == p_option_m_toggle_thrall
        VARS.key_m_toggle_thrall = value
    elseIf id_option == p_option_m_toggle_immobile
        VARS.key_m_toggle_immobile = value
    elseIf id_option == p_option_m_toggle_paralyzed
        VARS.key_m_toggle_paralyzed = value
    elseIf id_option == p_option_m_toggle_follower
        VARS.key_m_toggle_follower = value

    ; Follower
    elseIf id_option == p_option_f_toggle_sneak
        VARS.key_f_toggle_sneak = value
    elseIf id_option == p_option_f_toggle_saddler
        VARS.key_f_toggle_saddler = value

    ; Members
    elseIf id_option == p_option_ms_toggle_display
        VARS.key_ms_toggle_display = value
    elseIf id_option == p_option_ms_display_previous
        VARS.key_ms_display_previous = value
    elseIf id_option == p_option_ms_display_next
        VARS.key_ms_display_next = value

    ; Followers
    elseIf id_option == p_option_fs_summon_all
        VARS.key_fs_summon_all = value
    elseIf id_option == p_option_fs_summon_mobile
        VARS.key_fs_summon_mobile = value
    elseIf id_option == p_option_fs_summon_immobile
        VARS.key_fs_summon_immobile = value
    elseIf id_option == p_option_fs_settle
        VARS.key_fs_settle = value
    elseIf id_option == p_option_fs_unsettle
        VARS.key_fs_unsettle = value
    elseIf id_option == p_option_fs_immobilize
        VARS.key_fs_immobilize = value
    elseIf id_option == p_option_fs_mobilize
        VARS.key_fs_mobilize = value
    elseIf id_option == p_option_fs_sneak
        VARS.key_fs_sneak = value
    elseIf id_option == p_option_fs_unsneak
        VARS.key_fs_unsneak = value
    elseIf id_option == p_option_fs_saddle
        VARS.key_fs_saddle = value
    elseIf id_option == p_option_fs_unsaddle
        VARS.key_fs_unsaddle = value
    elseIf id_option == p_option_fs_resurrect
        VARS.key_fs_resurrect = value

    else
        return

    endIf

    MCM.SetKeymapOptionValue(id_option, value, false)
    KEYS.Update_Keys()
endFunction

function p_Set_Default_Mods(int id_option, string hotkey)
    if !hotkey
        return
    endIf

    int value = KEYS.Current_Value(hotkey)
    int[] mods = KEYS.Default_Mods(hotkey)
    if !p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
        return
    endIf

    if false

    ; Global
    elseIf id_option == p_option_g_dialogue_menu_mods
        VARS.key_g_dialogue_menu_mods = mods

    ; NPC
    elseIf id_option == p_option_n_toggle_member_mods
        VARS.key_n_toggle_member_mods = mods
    elseIf id_option == p_option_n_toggle_move_mods
        VARS.key_n_toggle_move_mods = mods
    elseIf id_option == p_option_n_move_farther_mods
        VARS.key_n_move_farther_mods = mods
    elseIf id_option == p_option_n_move_nearer_mods
        VARS.key_n_move_nearer_mods = mods
    elseIf id_option == p_option_n_move_rotate_right_mods
        VARS.key_n_move_rotate_right_mods = mods
    elseIf id_option == p_option_n_move_rotate_left_mods
        VARS.key_n_move_rotate_left_mods = mods
    elseIf id_option == p_option_n_has_base_mods
        VARS.key_n_has_base_mods = mods
    elseIf id_option == p_option_n_count_base_mods
        VARS.key_n_count_base_mods = mods
    elseIf id_option == p_option_n_has_head_mods
        VARS.key_n_has_head_mods = mods
    elseIf id_option == p_option_n_count_heads_mods
        VARS.key_n_count_heads_mods = mods

    ; Member
    elseIf id_option == p_option_m_toggle_clone_mods
        VARS.key_m_toggle_clone_mods = mods
    elseIf id_option == p_option_m_toggle_settler_mods
        VARS.key_m_toggle_settler_mods = mods
    elseIf id_option == p_option_m_toggle_thrall_mods
        VARS.key_m_toggle_thrall_mods = mods
    elseIf id_option == p_option_m_toggle_immobile_mods
        VARS.key_m_toggle_immobile_mods = mods
    elseIf id_option == p_option_m_toggle_paralyzed_mods
        VARS.key_m_toggle_paralyzed_mods = mods
    elseIf id_option == p_option_m_toggle_follower_mods
        VARS.key_m_toggle_follower_mods = mods

    ; Follower
    elseIf id_option == p_option_f_toggle_sneak_mods
        VARS.key_f_toggle_sneak_mods = mods
    elseIf id_option == p_option_f_toggle_saddler_mods
        VARS.key_f_toggle_saddler_mods = mods

    ; Members
    elseIf id_option == p_option_ms_toggle_display_mods
        VARS.key_ms_toggle_display_mods = mods
    elseIf id_option == p_option_ms_display_previous_mods
        VARS.key_ms_display_previous_mods = mods
    elseIf id_option == p_option_ms_display_next_mods
        VARS.key_ms_display_next_mods = mods

    ; Followers
    elseIf id_option == p_option_fs_summon_all_mods
        VARS.key_fs_summon_all_mods = mods
    elseIf id_option == p_option_fs_summon_mobile_mods
        VARS.key_fs_summon_mobile_mods = mods
    elseIf id_option == p_option_fs_summon_immobile_mods
        VARS.key_fs_summon_immobile_mods = mods
    elseIf id_option == p_option_fs_settle_mods
        VARS.key_fs_settle_mods = mods
    elseIf id_option == p_option_fs_unsettle_mods
        VARS.key_fs_unsettle_mods = mods
    elseIf id_option == p_option_fs_immobilize_mods
        VARS.key_fs_immobilize_mods = mods
    elseIf id_option == p_option_fs_mobilize_mods
        VARS.key_fs_mobilize_mods = mods
    elseIf id_option == p_option_fs_sneak_mods
        VARS.key_fs_sneak_mods = mods
    elseIf id_option == p_option_fs_unsneak_mods
        VARS.key_fs_unsneak_mods = mods
    elseIf id_option == p_option_fs_saddle_mods
        VARS.key_fs_saddle_mods = mods
    elseIf id_option == p_option_fs_unsaddle_mods
        VARS.key_fs_unsaddle_mods = mods
    elseIf id_option == p_option_fs_resurrect_mods
        VARS.key_fs_resurrect_mods = mods

    else
        return

    endIf

    MCM.SetTextOptionValue(id_option, KEYS.Current_Mods_To_String(hotkey), false)
    KEYS.Update_Keys()
endFunction

function p_Set_Default_Hotkeys()
    ; this is supposed to default everythign
endFunction
