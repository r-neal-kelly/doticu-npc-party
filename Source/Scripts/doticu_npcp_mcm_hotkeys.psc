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
doticu_npcp_data    p_DATA                          =  none

; Private Variables
bool                p_is_created                    = false

int                 p_option_g_modifier             =    -1
int                 p_option_g_dialogue_menu        =    -1

int                 p_option_fs_modifier            =    -1
int                 p_option_fs_summon_all          =    -1
int                 p_option_fs_summon_mobile       =    -1
int                 p_option_fs_summon_immobile     =    -1
int                 p_option_fs_settle              =    -1
int                 p_option_fs_unsettle            =    -1
int                 p_option_fs_immobilize          =    -1
int                 p_option_fs_mobilize            =    -1
int                 p_option_fs_sneak               =    -1
int                 p_option_fs_unsneak             =    -1
int                 p_option_fs_resurrect           =    -1

int                 p_option_ms_modifier            =    -1
int                 p_option_ms_display_toggle      =    -1
int                 p_option_ms_display_previous    =    -1
int                 p_option_ms_display_next        =    -1

int                 p_option_m_modifier             =    -1
int                 p_option_m_toggle_member        =    -1
int                 p_option_m_toggle_clone         =    -1
int                 p_option_m_toggle_settler       =    -1
int                 p_option_m_toggle_thrall        =    -1
int                 p_option_m_toggle_immobile      =    -1
int                 p_option_m_toggle_paralyzed     =    -1
int                 p_option_m_toggle_follower      =    -1
int                 p_option_m_toggle_sneak         =    -1

int                 p_option_n_modifier             =    -1
int                 p_option_n_move_toggle          =    -1
int                 p_option_n_move_farther         =    -1
int                 p_option_n_move_nearer          =    -1
int                 p_option_n_move_rotate_right    =    -1
int                 p_option_n_move_rotate_left     =    -1
int                 p_option_n_has_base             =    -1
int                 p_option_n_count_base           =    -1
int                 p_option_n_has_head             =    -1
int                 p_option_n_count_heads          =    -1

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

    MCM.AddHeaderOption(" General ")
    MCM.AddEmptyOption()
    p_option_g_modifier = MCM.AddKeymapOption(" - Modifier - ", VARS.key_g_modifier, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_g_dialogue_menu = MCM.AddKeymapOption(" Open General Menu ", VARS.key_g_dialogue_menu, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" All Followers ")
    MCM.AddEmptyOption()
    p_option_fs_modifier = MCM.AddKeymapOption(" - Modifier - ", VARS.key_fs_modifier, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_summon_all = MCM.AddKeymapOption(" Summon All ", VARS.key_fs_summon_all, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_summon_mobile = MCM.AddKeymapOption(" Summon Mobile ", VARS.key_fs_summon_mobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_summon_immobile = MCM.AddKeymapOption(" Summon Immobile ", VARS.key_fs_summon_immobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_settle = MCM.AddKeymapOption(" Settle ", VARS.key_fs_settle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_unsettle = MCM.AddKeymapOption(" Unsettle ", VARS.key_fs_unsettle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_immobilize = MCM.AddKeymapOption(" Immobilize ", VARS.key_fs_immobilize, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_mobilize = MCM.AddKeymapOption(" Mobilize ", VARS.key_fs_mobilize, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_sneak = MCM.AddKeymapOption(" Sneak ", VARS.key_fs_sneak, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_unsneak = MCM.AddKeymapOption(" Unsneak ", VARS.key_fs_unsneak, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_fs_resurrect = MCM.AddKeymapOption(" Resurrect ", VARS.key_fs_resurrect, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" All Members ")
    MCM.AddEmptyOption()
    p_option_ms_modifier = MCM.AddKeymapOption(" - Modifier - ", VARS.key_ms_modifier, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_ms_display_toggle = MCM.AddKeymapOption(" Toggle Display ", VARS.key_ms_display_toggle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_ms_display_previous = MCM.AddKeymapOption(" Display Previous ", VARS.key_ms_display_previous, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_ms_display_next = MCM.AddKeymapOption(" Display Next ", VARS.key_ms_display_next, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" One Member/Follower ")
    MCM.AddEmptyOption()
    p_option_m_modifier = MCM.AddKeymapOption(" - Modifier - ", VARS.key_m_modifier, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_member = MCM.AddKeymapOption(" Toggle Member ", VARS.key_m_toggle_member, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_clone = MCM.AddKeymapOption(" Toggle Clone ", VARS.key_m_toggle_clone, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_settler = MCM.AddKeymapOption(" Toggle Settler ", VARS.key_m_toggle_settler, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_thrall = MCM.AddKeymapOption(" Toggle Thrall ", VARS.key_m_toggle_thrall, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_immobile = MCM.AddKeymapOption(" Toggle Immobile ", VARS.key_m_toggle_immobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_paralyzed = MCM.AddKeymapOption(" Toggle Paralyzed ", VARS.key_m_toggle_paralyzed, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_follower = MCM.AddKeymapOption(" Toggle Follower ", VARS.key_m_toggle_follower, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_m_toggle_sneak = MCM.AddKeymapOption(" Toggle Sneak ", VARS.key_m_toggle_sneak, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" One NPC ")
    MCM.AddEmptyOption()
    p_option_n_modifier = MCM.AddKeymapOption(" - Modifier - ", VARS.key_n_modifier, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_toggle = MCM.AddKeymapOption(" Toggle Move ", VARS.key_move_toggle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_nearer = MCM.AddKeymapOption(" Move Nearer ", VARS.key_move_nearer, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_farther = MCM.AddKeymapOption(" Move Farther ", VARS.key_move_farther, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_rotate_left = MCM.AddKeymapOption(" Move Clockwise ", VARS.key_move_rotate_left, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_move_rotate_right = MCM.AddKeymapOption(" Move Counter-Clockwise ", VARS.key_move_rotate_right, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_has_base = MCM.AddKeymapOption(" Has Base ", VARS.key_n_has_base, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_count_base = MCM.AddKeymapOption(" Count Base ", VARS.key_n_count_base, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_has_head = MCM.AddKeymapOption(" Has Head ", VARS.key_n_has_head, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_n_count_heads = MCM.AddKeymapOption(" Count Heads ", VARS.key_n_count_heads, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    ; not safe to do anything with a false control
    string str_control = p_Get_Control(id_option)
    if !str_control
        return
    endIf

    ; this avoids false positive conflicts
    if KEYS.Get_Key(str_control) == code_key
        return
    endIf

    ; we ask the user to deal with the conflict
    if code_key > -1 && str_conflict_control
        string str_conflict_message = "This conflicts with '" + str_conflict_control + "'"
        if str_conflict_mod
            str_conflict_message += " in the mod '" + str_conflict_mod + "'."
        else
            str_conflict_message += " in vanilla Skyrim."
        endIf
        str_conflict_message += " Set key anyway?"
        if !MCM.ShowMessage(str_conflict_message, true)
            return
        endIf
    endIf

    if false

    ; General
    elseIf id_option == p_option_g_modifier
        VARS.key_g_modifier = code_key
    elseIf id_option == p_option_g_dialogue_menu
        VARS.key_g_dialogue_menu = code_key

    ; All Followers
    elseIf id_option == p_option_fs_modifier
        VARS.key_fs_modifier = code_key
    elseIf id_option == p_option_fs_summon_all
        VARS.key_fs_summon_all = code_key
    elseIf id_option == p_option_fs_summon_mobile
        VARS.key_fs_summon_mobile = code_key
    elseIf id_option == p_option_fs_summon_immobile
        VARS.key_fs_summon_immobile = code_key
    elseIf id_option == p_option_fs_settle
        VARS.key_fs_settle = code_key
    elseIf id_option == p_option_fs_unsettle
        VARS.key_fs_unsettle = code_key
    elseIf id_option == p_option_fs_immobilize
        VARS.key_fs_immobilize = code_key
    elseIf id_option == p_option_fs_mobilize
        VARS.key_fs_mobilize = code_key
    elseIf id_option == p_option_fs_sneak
        VARS.key_fs_sneak = code_key
    elseIf id_option == p_option_fs_unsneak
        VARS.key_fs_unsneak = code_key
    elseIf id_option == p_option_fs_resurrect
        VARS.key_fs_resurrect = code_key

    ; All Members
    elseIf id_option == p_option_ms_modifier
        VARS.key_ms_modifier = code_key
    elseIf id_option == p_option_ms_display_toggle
        VARS.key_ms_display_toggle = code_key
    elseIf id_option == p_option_ms_display_previous
        VARS.key_ms_display_previous = code_key
    elseIf id_option == p_option_ms_display_next
        VARS.key_ms_display_next = code_key
    
    ; One Member/Follower
    elseIf id_option == p_option_m_modifier
        VARS.key_m_modifier = code_key
    elseIf id_option == p_option_m_toggle_member
        VARS.key_m_toggle_member = code_key
    elseIf id_option == p_option_m_toggle_clone
        VARS.key_m_toggle_clone = code_key
    elseIf id_option == p_option_m_toggle_settler
        VARS.key_m_toggle_settler = code_key
    elseIf id_option == p_option_m_toggle_thrall
        VARS.key_m_toggle_thrall = code_key
    elseIf id_option == p_option_m_toggle_immobile
        VARS.key_m_toggle_immobile = code_key
    elseIf id_option == p_option_m_toggle_paralyzed
        VARS.key_m_toggle_paralyzed = code_key
    elseIf id_option == p_option_m_toggle_follower
        VARS.key_m_toggle_follower = code_key
    elseIf id_option == p_option_m_toggle_sneak
        VARS.key_m_toggle_sneak = code_key

    ; One NPC
    elseIf id_option == p_option_n_modifier
        VARS.key_n_modifier = code_key
    elseIf id_option == p_option_n_move_toggle
        VARS.key_move_toggle = code_key
    elseIf id_option == p_option_n_move_farther
        VARS.key_move_farther = code_key
    elseIf id_option == p_option_n_move_nearer
        VARS.key_move_nearer = code_key
    elseIf id_option == p_option_n_move_rotate_right
        VARS.key_move_rotate_right = code_key
    elseIf id_option == p_option_n_move_rotate_left
        VARS.key_move_rotate_left = code_key
    elseIf id_option == p_option_n_has_base
        VARS.key_n_has_base = code_key
    elseIf id_option == p_option_n_count_base
        VARS.key_n_count_base = code_key
    elseIf id_option == p_option_n_has_head
        VARS.key_n_has_head = code_key
    elseIf id_option == p_option_n_count_heads
        VARS.key_n_count_heads = code_key

    else
        return

    endIf

    KEYS.Update_Keys()

    MCM.SetKeymapOptionValue(id_option, code_key, false)
endFunction

function f_On_Option_Default(int id_option)
    ; not safe to do anything with a false control
    string str_control = p_Get_Control(id_option)
    if !str_control
        return
    endIf
    
    if false

    ; General
    elseIf id_option == p_option_g_modifier
        if p_Can_Set_Key(CONSTS.STR_KEY_G_MODIFIER, CONSTS.KEY_DEF_G_MODIFIER)
            VARS.key_g_modifier = CONSTS.KEY_DEF_G_MODIFIER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_G_MODIFIER, false)
        endIf
    elseIf id_option == p_option_g_dialogue_menu
        if p_Can_Set_Key(CONSTS.STR_KEY_G_DIALOGUE_MENU, CONSTS.KEY_DEF_G_DIALOGUE_MENU)
            VARS.key_g_dialogue_menu = CONSTS.KEY_DEF_G_DIALOGUE_MENU
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_G_DIALOGUE_MENU, false)
        endIf

    ; All Followers
    elseIf id_option == p_option_fs_modifier
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_MODIFIER, CONSTS.KEY_DEF_FS_MODIFIER)
            VARS.key_fs_modifier = CONSTS.KEY_DEF_FS_MODIFIER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_MODIFIER, false)
        endIf
    elseIf id_option == p_option_fs_summon_all
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SUMMON_ALL, CONSTS.KEY_DEF_FS_SUMMON_ALL)
            VARS.key_fs_summon_all = CONSTS.KEY_DEF_FS_SUMMON_ALL
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_ALL, false)
        endIf
    elseIf id_option == p_option_fs_summon_mobile
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SUMMON_MOBILE, CONSTS.KEY_DEF_FS_SUMMON_MOBILE)
            VARS.key_fs_summon_mobile = CONSTS.KEY_DEF_FS_SUMMON_MOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_MOBILE, false)
        endIf
    elseIf id_option == p_option_fs_summon_immobile
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SUMMON_IMMOBILE, CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE)
            VARS.key_fs_summon_immobile = CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE, false)
        endIf
    elseIf id_option == p_option_fs_settle
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SETTLE, CONSTS.KEY_DEF_FS_SETTLE)
            VARS.key_fs_settle = CONSTS.KEY_DEF_FS_SETTLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SETTLE, false)
        endIf
    elseIf id_option == p_option_fs_unsettle
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_UNSETTLE, CONSTS.KEY_DEF_FS_UNSETTLE)
            VARS.key_fs_unsettle = CONSTS.KEY_DEF_FS_UNSETTLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_UNSETTLE, false)
        endIf
    elseIf id_option == p_option_fs_immobilize
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_IMMOBILIZE, CONSTS.KEY_DEF_FS_IMMOBILIZE)
            VARS.key_fs_immobilize = CONSTS.KEY_DEF_FS_IMMOBILIZE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_IMMOBILIZE, false)
        endIf
    elseIf id_option == p_option_fs_mobilize
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_MOBILIZE, CONSTS.KEY_DEF_FS_MOBILIZE)
            VARS.key_fs_mobilize = CONSTS.KEY_DEF_FS_MOBILIZE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_MOBILIZE, false)
        endIf
    elseIf id_option == p_option_fs_sneak
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SNEAK, CONSTS.KEY_DEF_FS_SNEAK)
            VARS.key_fs_sneak = CONSTS.KEY_DEF_FS_SNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SNEAK, false)
        endIf
    elseIf id_option == p_option_fs_unsneak
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_UNSNEAK, CONSTS.KEY_DEF_FS_UNSNEAK)
            VARS.key_fs_unsneak = CONSTS.KEY_DEF_FS_UNSNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_UNSNEAK, false)
        endIf
    elseIf id_option == p_option_fs_resurrect
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_RESURRECT, CONSTS.KEY_DEF_FS_RESURRECT)
            VARS.key_fs_resurrect = CONSTS.KEY_DEF_FS_RESURRECT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_RESURRECT, false)
        endIf

    ; All Members
    elseIf id_option == p_option_ms_modifier
        if p_Can_Set_Key(CONSTS.STR_KEY_MS_MODIFIER, CONSTS.KEY_DEF_MS_MODIFIER)
            VARS.key_ms_modifier = CONSTS.KEY_DEF_MS_MODIFIER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_MODIFIER, false)
        endIf
    elseIf id_option == p_option_ms_display_toggle
        if p_Can_Set_Key(CONSTS.STR_KEY_MS_DISPLAY_TOGGLE, CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE)
            VARS.key_ms_display_toggle = CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE, false)
        endIf
    elseIf id_option == p_option_ms_display_previous
        if p_Can_Set_Key(CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS, CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS)
            VARS.key_ms_display_previous = CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS, false)
        endIf
    elseIf id_option == p_option_ms_display_next
        if p_Can_Set_Key(CONSTS.STR_KEY_MS_DISPLAY_NEXT, CONSTS.KEY_DEF_MS_DISPLAY_NEXT)
            VARS.key_ms_display_next = CONSTS.KEY_DEF_MS_DISPLAY_NEXT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_NEXT, false)
        endIf
    
    ; One Member/Follower
    elseIf id_option == p_option_m_modifier
        if p_Can_Set_Key(CONSTS.STR_KEY_M_MODIFIER, CONSTS.KEY_DEF_M_MODIFIER)
            VARS.key_m_modifier = CONSTS.KEY_DEF_M_MODIFIER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_MODIFIER, false)
        endIf
    elseIf id_option == p_option_m_toggle_member
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_MEMBER, CONSTS.KEY_DEF_M_TOGGLE_MEMBER)
            VARS.key_m_toggle_member = CONSTS.KEY_DEF_M_TOGGLE_MEMBER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_MEMBER, false)
        endIf
    elseIf id_option == p_option_m_toggle_clone
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_CLONE, CONSTS.KEY_DEF_M_TOGGLE_CLONE)
            VARS.key_m_toggle_clone = CONSTS.KEY_DEF_M_TOGGLE_CLONE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_CLONE, false)
        endIf
    elseIf id_option == p_option_m_toggle_settler
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_SETTLER, CONSTS.KEY_DEF_M_TOGGLE_SETTLER)
            VARS.key_m_toggle_settler = CONSTS.KEY_DEF_M_TOGGLE_SETTLER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_SETTLER, false)
        endIf
    elseIf id_option == p_option_m_toggle_thrall
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_THRALL, CONSTS.KEY_DEF_M_TOGGLE_THRALL)
            VARS.key_m_toggle_thrall = CONSTS.KEY_DEF_M_TOGGLE_THRALL
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_THRALL, false)
        endIf
    elseIf id_option == p_option_m_toggle_immobile
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_IMMOBILE, CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE)
            VARS.key_m_toggle_immobile = CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE, false)
        endIf
    elseIf id_option == p_option_m_toggle_paralyzed
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_PARALYZED, CONSTS.KEY_DEF_M_TOGGLE_PARALYZED)
            VARS.key_m_toggle_paralyzed = CONSTS.KEY_DEF_M_TOGGLE_PARALYZED
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_PARALYZED, false)
        endIf
    elseIf id_option == p_option_m_toggle_follower
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_FOLLOWER, CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER)
            VARS.key_m_toggle_follower = CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER, false)
        endIf
    elseIf id_option == p_option_m_toggle_sneak
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_SNEAK, CONSTS.KEY_DEF_M_TOGGLE_SNEAK)
            VARS.key_m_toggle_sneak = CONSTS.KEY_DEF_M_TOGGLE_SNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_SNEAK, false)
        endIf

    ; One NPC
    elseIf id_option == p_option_n_modifier
        if p_Can_Set_Key(CONSTS.STR_KEY_N_MODIFIER, CONSTS.KEY_DEF_N_MODIFIER)
            VARS.key_n_modifier = CONSTS.KEY_DEF_N_MODIFIER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_N_MODIFIER, false)
        endIf
    elseIf id_option == p_option_n_move_toggle
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_TOGGLE, CONSTS.KEY_DEF_MOVE_TOGGLE)
            VARS.key_move_toggle = CONSTS.KEY_DEF_MOVE_TOGGLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_TOGGLE, false)
        endIf
    elseIf id_option == p_option_n_move_farther
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_FARTHER, CONSTS.KEY_DEF_MOVE_FARTHER)
            VARS.key_move_farther = CONSTS.KEY_DEF_MOVE_FARTHER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_FARTHER, false)
        endIf
    elseIf id_option == p_option_n_move_nearer
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_NEARER, CONSTS.KEY_DEF_MOVE_NEARER)
            VARS.key_move_nearer = CONSTS.KEY_DEF_MOVE_NEARER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_NEARER, false)
        endIf
    elseIf id_option == p_option_n_move_rotate_right
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_ROTATE_RIGHT, CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT)
            VARS.key_move_rotate_right = CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT, false)
        endIf
    elseIf id_option == p_option_n_move_rotate_left
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_ROTATE_LEFT, CONSTS.KEY_DEF_MOVE_ROTATE_LEFT)
            VARS.key_move_rotate_left = CONSTS.KEY_DEF_MOVE_ROTATE_LEFT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_ROTATE_LEFT, false)
        endIf
    elseIf id_option == p_option_n_has_base
        if p_Can_Set_Key(CONSTS.STR_KEY_N_HAS_BASE, CONSTS.KEY_DEF_N_HAS_BASE)
            VARS.key_n_has_base = CONSTS.KEY_DEF_N_HAS_BASE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_N_HAS_BASE, false)
        endIf
    elseIf id_option == p_option_n_count_base
        if p_Can_Set_Key(CONSTS.STR_KEY_N_COUNT_BASE, CONSTS.KEY_DEF_N_COUNT_BASE)
            VARS.key_n_count_base = CONSTS.KEY_DEF_N_COUNT_BASE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_N_COUNT_BASE, false)
        endIf
    elseIf id_option == p_option_n_has_head
        if p_Can_Set_Key(CONSTS.STR_KEY_N_HAS_HEAD, CONSTS.KEY_DEF_N_HAS_HEAD)
            VARS.key_n_has_head = CONSTS.KEY_DEF_N_HAS_HEAD
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_N_HAS_HEAD, false)
        endIf
    elseIf id_option == p_option_n_count_heads
        if p_Can_Set_Key(CONSTS.STR_KEY_N_COUNT_HEADS, CONSTS.KEY_DEF_N_COUNT_HEADS)
            VARS.key_n_count_heads = CONSTS.KEY_DEF_N_COUNT_HEADS
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_N_COUNT_HEADS, false)
        endIf

    endIf

    KEYS.Update_Keys()
endFunction

function f_On_Option_Highlight(int id_option)
    if false

    ; General
    elseIf id_option == p_option_g_modifier
        MCM.SetInfoText("An optional key that stops general hotkeys from triggering unless it is being pressed.")
    elseIf id_option == p_option_g_dialogue_menu
        MCM.SetInfoText("Opens the general menu, a dialogue tree with which you can select global commands.")

    ; All Followers
    elseIf id_option == p_option_fs_modifier
        MCM.SetInfoText("An optional key that stops multi-follower hotkeys from triggering unless it is being pressed.")
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
    elseIf id_option == p_option_fs_immobilize
        MCM.SetInfoText("Causes all followers to become immobile.")
    elseIf id_option == p_option_fs_mobilize
        MCM.SetInfoText("Causes all followers to become mobile.")
    elseIf id_option == p_option_fs_sneak
        MCM.SetInfoText("Causes all followers to start sneaking.")
    elseIf id_option == p_option_fs_unsneak
        MCM.SetInfoText("Causes all followers to stop sneaking.")
    elseIf id_option == p_option_fs_resurrect
        MCM.SetInfoText("Causes all dead followers to resurrect.")

    ; All Members
    elseIf id_option == p_option_ms_modifier
        MCM.SetInfoText("An optional key that stops multi-member hotkeys from triggering unless it is being pressed.")
    elseIf id_option == p_option_ms_display_toggle
        MCM.SetInfoText("Toggles a member display.")
    elseIf id_option == p_option_ms_display_previous
        MCM.SetInfoText("Will loop through the previous members on display.")
    elseIf id_option == p_option_ms_display_next
        MCM.SetInfoText("Will loop through the next members on display.")
    
    ; One Member/Follower
    elseIf id_option == p_option_m_modifier
        MCM.SetInfoText("An optional key that stops member/follower hotkeys from triggering unless it is being pressed.")
    elseIf id_option == p_option_m_toggle_member
        MCM.SetInfoText("Causes an npc to be membered or unmembered.")
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
    elseIf id_option == p_option_m_toggle_sneak
        MCM.SetInfoText("Causes an npc to sneak or unsneak. The npc will become a member and a follower if they are not already.")

    ; One NPC
    elseIf id_option == p_option_n_modifier
        MCM.SetInfoText("An optional key that stops npc hotkeys from triggering unless it is being pressed.")
    elseIf id_option == p_option_n_move_toggle
        MCM.SetInfoText("Toggles the act of moving an npc.")
    elseIf id_option == p_option_n_move_farther
        MCM.SetInfoText("While moving an npc, this will make them go farther away from you.")
    elseIf id_option == p_option_n_move_nearer
        MCM.SetInfoText("While moving an npc, this will make them come closer to you.")
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

    endIf
endFunction

function f_On_Option_Select(int id_option)
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
string function p_Get_Control(int id_option)
    if false

    ; General
    elseIf id_option == p_option_g_modifier
        return CONSTS.STR_KEY_G_MODIFIER
    elseIf id_option == p_option_g_dialogue_menu
        return CONSTS.STR_KEY_G_DIALOGUE_MENU

    ; All Followers
    elseIf id_option == p_option_fs_modifier
        return CONSTS.STR_KEY_FS_MODIFIER
    elseIf id_option == p_option_fs_summon_all
        return CONSTS.STR_KEY_FS_SUMMON_ALL
    elseIf id_option == p_option_fs_summon_mobile
        return CONSTS.STR_KEY_FS_SUMMON_MOBILE
    elseIf id_option == p_option_fs_summon_immobile
        return CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
    elseIf id_option == p_option_fs_settle
        return CONSTS.STR_KEY_FS_SETTLE
    elseIf id_option == p_option_fs_unsettle
        return CONSTS.STR_KEY_FS_UNSETTLE
    elseIf id_option == p_option_fs_immobilize
        return CONSTS.STR_KEY_FS_IMMOBILIZE
    elseIf id_option == p_option_fs_mobilize
        return CONSTS.STR_KEY_FS_MOBILIZE
    elseIf id_option == p_option_fs_sneak
        return CONSTS.STR_KEY_FS_SNEAK
    elseIf id_option == p_option_fs_unsneak
        return CONSTS.STR_KEY_FS_UNSNEAK
    elseIf id_option == p_option_fs_resurrect
        return CONSTS.STR_KEY_FS_RESURRECT

    ; All Members
    elseIf id_option == p_option_ms_modifier
        return CONSTS.STR_KEY_MS_MODIFIER
    elseIf id_option == p_option_ms_display_toggle
        return CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
    elseIf id_option == p_option_ms_display_previous
        return CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS
    elseIf id_option == p_option_ms_display_next
        return CONSTS.STR_KEY_MS_DISPLAY_NEXT
    
    ; One Member/Follower
    elseIf id_option == p_option_m_modifier
        return CONSTS.STR_KEY_M_MODIFIER
    elseIf id_option == p_option_m_toggle_member
        return CONSTS.STR_KEY_M_TOGGLE_MEMBER
    elseIf id_option == p_option_m_toggle_clone
        return CONSTS.STR_KEY_M_TOGGLE_CLONE
    elseIf id_option == p_option_m_toggle_settler
        return CONSTS.STR_KEY_M_TOGGLE_SETTLER
    elseIf id_option == p_option_m_toggle_thrall
        return CONSTS.STR_KEY_M_TOGGLE_THRALL
    elseIf id_option == p_option_m_toggle_immobile
        return CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
    elseIf id_option == p_option_m_toggle_paralyzed
        return CONSTS.STR_KEY_M_TOGGLE_PARALYZED
    elseIf id_option == p_option_m_toggle_follower
        return CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
    elseIf id_option == p_option_m_toggle_sneak
        return CONSTS.STR_KEY_M_TOGGLE_SNEAK

    ; One NPC
    elseIf id_option == p_option_n_modifier
        return CONSTS.STR_KEY_N_MODIFIER
    elseIf id_option == p_option_n_move_toggle
        return CONSTS.STR_KEY_MOVE_TOGGLE
    elseIf id_option == p_option_n_move_farther
        return CONSTS.STR_KEY_MOVE_FARTHER
    elseIf id_option == p_option_n_move_nearer
        return CONSTS.STR_KEY_MOVE_NEARER
    elseIf id_option == p_option_n_move_rotate_right
        return CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
    elseIf id_option == p_option_n_move_rotate_left
        return CONSTS.STR_KEY_MOVE_ROTATE_LEFT
    elseIf id_option == p_option_n_has_base
        return CONSTS.STR_KEY_N_HAS_BASE
    elseIf id_option == p_option_n_count_base
        return CONSTS.STR_KEY_N_COUNT_BASE
    elseIf id_option == p_option_n_has_head
        return CONSTS.STR_KEY_N_HAS_HEAD
    elseIf id_option == p_option_n_count_heads
        return CONSTS.STR_KEY_N_COUNT_HEADS

    else
        return ""

    endIf
endFunction

bool function p_Can_Set_Key(string str_control, int code_key)
    string str_control_conflict = MCM.GetCustomControl(code_key)
    if str_control_conflict && KEYS.Get_Key(str_control) != code_key
        return MCM.ShowMessage("This conflicts with '" + str_control_conflict + "'. Set key anyway?", true)
    else
        return true
    endIf
endFunction

function p_Set_Default_Keys()
endFunction
