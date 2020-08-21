;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_hotkeys extends Quest

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return doticu_npcp.Vars()
    endFunction
endProperty
doticu_npcp_keys property KEYS hidden
    doticu_npcp_keys function Get()
        return doticu_npcp.Control().KEYS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return doticu_npcp.Control().MCM
    endFunction
endProperty

; Private Variables
int                 p_option_set_defaults               =    -1
int                 p_option_unset_all                  =    -1

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

; Native Methods
function f_Build_Page() native
function f_On_Option_Highlight(int option) native
function Change_Hotkey_Value(int option, int value, bool do_render = true) native
function Change_Hotkey_Mods(int option, int mod_1, int mod_2, int mod_3, bool do_render = true) native
function Reset_Hotkeys() native
function Unset_Hotkeys() native
string function Value_Option_To_Hotkey(int value_option) native
string function Mods_Option_To_Hotkey(int mods_option) native

; Friend Methods
function f_On_Option_Keymap_Change(int id_option, int value, string conflicting_hotkey, string conflicting_mod)
    string hotkey = Value_Option_to_Hotkey(id_option)
    if hotkey
        if value != KEYS.Current_Value(hotkey)
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
            if p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
                Change_Hotkey_Value(id_option, value)
                KEYS.Update_Keys()
            endIf
        endIf
    endIf
endFunction

function f_On_Option_Select(int id_option)
    if id_option == p_option_set_defaults
        if MCM.ShowMessage("This will set all NPC Party hotkeys to their defaults. " + \
                           "You will need to confirm any conflicts. Continue?", \
                           true, " Yes ", " No ")
            Reset_Hotkeys()
        endIf
    elseIf id_option == p_option_unset_all
        if MCM.ShowMessage("This will unset all NPC Party hotkeys. Continue?", true, " Yes ", " No ")
            Unset_Hotkeys()
        endIf
    else
        string hotkey = Mods_Option_to_Hotkey(id_option)
        if hotkey
            int value = KEYS.Current_Value(hotkey)
            int[] mods = p_Read_Pressed_Mods(hotkey)
            if mods.length > 0 && p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
                Change_Hotkey_Mods(id_option, mods[0], mods[1], mods[2])
            endIf
        endIf
    endIf
endFunction

function f_On_Option_Default(int id_option)
    if id_option != p_option_set_defaults && id_option != p_option_unset_all
        string hotkey = Value_Option_To_Hotkey(id_option)
        if hotkey
            int value = KEYS.Default_Value(hotkey)
            int[] mods = KEYS.Current_Mods(hotkey)
            if p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
                Change_Hotkey_Value(id_option, value)
                KEYS.Update_Keys()
            endIf
        else
            hotkey = Mods_Option_To_Hotkey(id_option)
            if hotkey
                int value = KEYS.Current_Value(hotkey)
                int[] mods = KEYS.Default_Mods(hotkey)
                if p_Can_Set_Hotkey(hotkey, value, mods[0], mods[1], mods[2])
                    Change_Hotkey_Mods(id_option, mods[0], mods[1], mods[2])
                endIf
            endIf
        endIf
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
int[] function p_Read_Pressed_Mods(string hotkey)
    int[] mods = new int[3]
    mods[0] = -1
    mods[1] = -1
    mods[2] = -1

    if MCM.ShowMessage("Set or Unset mods?", true, " Set ", " Unset ")
        if MCM.ShowMessage("Press and hold up to three keys and click enter. Cancel will leave the mods as they are.", true)
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
            return doticu_npcp.New_Int_Array(0)
        endIf
    else
        if MCM.ShowMessage("Are you sure you want to clear mods?", true)
            return mods
        else
            return doticu_npcp.New_Int_Array(0)
        endIf
    endIf
endFunction

bool function p_Can_Set_Hotkey(string hotkey, int value, int mod_1, int mod_2, int mod_3)
    if value > 0
        string npcp_conflict = KEYS.Conflicting_Hotkey(hotkey, value, mod_1, mod_2, mod_3)
        if npcp_conflict != ""
            return MCM.ShowMessage("This conflicts with '" + npcp_conflict + "'. Set key anyway?", true)
        else
            string mcm_conflict = MCM.GetCustomControl(value)
            if mcm_conflict && KEYS.Current_Value(hotkey) != value
                return MCM.ShowMessage("This conflicts with '" + mcm_conflict + "'. Set key anyway?", true)
            else
                return true
            endIf
        endIf
    else
        return true
    endIf
endFunction
