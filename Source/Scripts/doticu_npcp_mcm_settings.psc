;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_settings extends Quest

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

int                 p_option_force_clone_unique         =    -1
int                 p_option_force_clone_generic        =    -1
int                 p_option_force_unclone_unique       =    -1
int                 p_option_force_unclone_generic      =    -1
int                 p_option_auto_style                 =    -1
int                 p_option_auto_vitality              =    -1
int                 p_option_auto_resurrect             =    -1

int                 p_option_auto_outfit                =    -1
int                 p_option_fill_outfits               =    -1

int                 p_option_key_fs_summon_all          =    -1
int                 p_option_key_fs_summon_mobile       =    -1
int                 p_option_key_fs_summon_immobile     =    -1
int                 p_option_key_fs_settle              =    -1
int                 p_option_key_fs_unsettle            =    -1
int                 p_option_key_fs_immobilize          =    -1
int                 p_option_key_fs_mobilize            =    -1
int                 p_option_key_fs_sneak               =    -1
int                 p_option_key_fs_unsneak             =    -1
int                 p_option_key_fs_resurrect           =    -1

int                 p_option_key_ms_display_toggle      =    -1
int                 p_option_slider_ms_display          =    -1
int                 p_option_key_ms_display_previous    =    -1
int                 p_option_key_ms_display_next        =    -1

int                 p_option_key_move_toggle            =    -1
int                 p_option_key_move_farther           =    -1
int                 p_option_key_move_nearer            =    -1
int                 p_option_key_move_rotate_right      =    -1
int                 p_option_key_move_rotate_left       =    -1

int                 p_option_key_m_toggle_member        =    -1
int                 p_option_key_m_toggle_clone         =    -1
int                 p_option_key_m_toggle_settler       =    -1
int                 p_option_key_m_toggle_thrall        =    -1
int                 p_option_key_m_toggle_immobile      =    -1
int                 p_option_key_m_toggle_paralyzed     =    -1
int                 p_option_key_m_toggle_follower      =    -1
int                 p_option_key_m_toggle_sneak         =    -1

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

    MCM.SetTitleText(" Settings ")

    MCM.AddHeaderOption(" General ")
    MCM.AddEmptyOption()
    if VARS.auto_style == CODES.IS_DEFAULT
        p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_DEFAULT); maybe default instead of auto?
    elseIf VARS.auto_style == CODES.IS_WARRIOR
        p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_WARRIOR)
    elseIf VARS.auto_style == CODES.IS_MAGE
        p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_MAGE)
    elseIf VARS.auto_style == CODES.IS_ARCHER
        p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_ARCHER)
    endIf
    if VARS.auto_vitality == CODES.IS_MORTAL
        p_option_auto_vitality = MCM.AddTextOption("Auto Vitality", CONSTS.STR_MCM_MORTAL); maybe default instead of auto?
    elseIf VARS.auto_vitality == CODES.IS_PROTECTED
        p_option_auto_vitality = MCM.AddTextOption("Auto Vitality", CONSTS.STR_MCM_PROTECTED)
    elseIf VARS.auto_vitality == CODES.IS_ESSENTIAL
        p_option_auto_vitality = MCM.AddTextOption("Auto Vitality", CONSTS.STR_MCM_ESSENTIAL)
    elseIf VARS.auto_vitality == CODES.IS_INVULNERABLE
        p_option_auto_vitality = MCM.AddTextOption("Auto Vitality", CONSTS.STR_MCM_INVULNERABLE)
    endIf
    p_option_auto_resurrect = MCM.AddToggleOption("Auto Resurrect Followers", VARS.auto_resurrect)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Cloning ")
    MCM.AddEmptyOption()
    p_option_force_clone_unique = MCM.AddToggleOption("Force Clone Unique NPCs", VARS.force_clone_unique)
    p_option_force_unclone_unique = MCM.AddToggleOption("Force Unclone Unique NPCs", VARS.force_unclone_unique)
    p_option_force_clone_generic = MCM.AddToggleOption("Force Clone Generic NPCs", VARS.force_clone_generic)
    p_option_force_unclone_generic = MCM.AddToggleOption("Force Unclone Generic NPCs", VARS.force_unclone_generic)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Outfitting ")
    MCM.AddEmptyOption()
    p_option_auto_outfit = MCM.AddToggleOption("Auto Outfit", VARS.auto_outfit)
    p_option_fill_outfits = MCM.AddTOggleOption("Fill Outfits", VARS.fill_outfits)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Displaying ")
    MCM.AddEmptyOption()
    p_option_key_ms_display_toggle = MCM.AddKeymapOption(" Toggle Display ", VARS.key_ms_display_toggle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_slider_ms_display = MCM.AddSliderOption(" Number per Cycle ", VARS.num_display, " {0} ")
    p_option_key_ms_display_previous = MCM.AddKeymapOption(" Previous Display ", VARS.key_ms_display_previous, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_ms_display_next = MCM.AddKeymapOption(" Next Display ", VARS.key_ms_display_next, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Moving ")
    MCM.AddEmptyOption()
    p_option_key_move_toggle = MCM.AddKeymapOption(" Toggle Move ", VARS.key_move_toggle, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    p_option_key_move_nearer = MCM.AddKeymapOption(" Move Nearer ", VARS.key_move_nearer, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_move_farther = MCM.AddKeymapOption(" Move Farther ", VARS.key_move_farther, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_move_rotate_left = MCM.AddKeymapOption(" Rotate Left ", VARS.key_move_rotate_left, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_move_rotate_right = MCM.AddKeymapOption(" Rotate Right ", VARS.key_move_rotate_right, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" All Followers ")
    MCM.AddEmptyOption()
    p_option_key_fs_summon_all = MCM.AddKeymapOption(" Summon All ", VARS.key_fs_summon_all, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_summon_mobile = MCM.AddKeymapOption(" Summon Mobile ", VARS.key_fs_summon_mobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_summon_immobile = MCM.AddKeymapOption(" Summon Immobile ", VARS.key_fs_summon_immobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_settle = MCM.AddKeymapOption(" Settle ", VARS.key_fs_settle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_unsettle = MCM.AddKeymapOption(" Unsettle ", VARS.key_fs_unsettle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_immobilize = MCM.AddKeymapOption(" Immobilize ", VARS.key_fs_immobilize, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_mobilize = MCM.AddKeymapOption(" Mobilize ", VARS.key_fs_mobilize, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_sneak = MCM.AddKeymapOption(" Sneak ", VARS.key_fs_sneak, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_unsneak = MCM.AddKeymapOption(" Unsneak ", VARS.key_fs_unsneak, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_fs_resurrect = MCM.AddKeymapOption(" Resurrect ", VARS.key_fs_resurrect, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" One Follower/Member ")
    MCM.AddEmptyOption()
    p_option_key_m_toggle_member = MCM.AddKeymapOption(" Toggle Member ", VARS.key_m_toggle_member, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_m_toggle_clone = MCM.AddKeymapOption(" Toggle Clone ", VARS.key_m_toggle_clone, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_m_toggle_settler = MCM.AddKeymapOption(" Toggle Settler ", VARS.key_m_toggle_settler, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_m_toggle_thrall = MCM.AddKeymapOption(" Toggle Thrall ", VARS.key_m_toggle_thrall, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_m_toggle_immobile = MCM.AddKeymapOption(" Toggle Immobile ", VARS.key_m_toggle_immobile, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_m_toggle_paralyzed = MCM.AddKeymapOption(" Toggle Paralyzed ", VARS.key_m_toggle_paralyzed, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_m_toggle_follower = MCM.AddKeymapOption(" Toggle Follower ", VARS.key_m_toggle_follower, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_m_toggle_sneak = MCM.AddKeymapOption(" Toggle Sneak ", VARS.key_m_toggle_sneak, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
endFunction

function f_On_Option_Select(int id_option)
    bool do_update = false
    bool dont_update = true

    if false

    ; General
    elseIf id_option == p_option_auto_style
        if VARS.auto_style == CODES.IS_DEFAULT
            VARS.auto_style = CODES.IS_WARRIOR
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_WARRIOR, do_update)
        elseIf VARS.auto_style == CODES.IS_WARRIOR
            VARS.auto_style = CODES.IS_MAGE
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_MAGE, do_update)
        elseIf VARS.auto_style == CODES.IS_MAGE
            VARS.auto_style = CODES.IS_ARCHER
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_ARCHER, do_update)
        elseIf VARS.auto_style == CODES.IS_ARCHER
            VARS.auto_style = CODES.IS_DEFAULT
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_DEFAULT, do_update)
        endIf
    elseIf id_option == p_option_auto_vitality
        if VARS.auto_vitality == CODES.IS_MORTAL
            VARS.auto_vitality = CODES.IS_PROTECTED
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_PROTECTED, do_update)
        elseIf VARS.auto_vitality == CODES.IS_PROTECTED
            VARS.auto_vitality = CODES.IS_ESSENTIAL
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_ESSENTIAL, do_update)
        elseIf VARS.auto_vitality == CODES.IS_ESSENTIAL
            VARS.auto_vitality = CODES.IS_INVULNERABLE
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_INVULNERABLE, do_update)
        elseIf VARS.auto_vitality == CODES.IS_INVULNERABLE
            VARS.auto_vitality = CODES.IS_MORTAL
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_MORTAL, do_update)
        endIf
    elseIf id_option == p_option_auto_resurrect
        VARS.auto_resurrect = !VARS.auto_resurrect
        MCM.SetToggleOptionValue(p_option_auto_resurrect, VARS.auto_resurrect, do_update)

    ; Cloning
    elseIf id_option == p_option_force_clone_unique
        VARS.force_clone_unique = !VARS.force_clone_unique
        MCM.SetToggleOptionValue(p_option_force_clone_unique, VARS.force_clone_unique, do_update)
    elseIf id_option == p_option_force_clone_generic
        VARS.force_clone_generic = !VARS.force_clone_generic
        MCM.SetToggleOptionValue(p_option_force_clone_generic, VARS.force_clone_generic, do_update)
    elseIf id_option == p_option_force_unclone_unique
        VARS.force_unclone_unique = !VARS.force_unclone_unique
        MCM.SetToggleOptionValue(p_option_force_unclone_unique, VARS.force_unclone_unique, do_update)
    elseIf id_option == p_option_force_unclone_generic
        VARS.force_unclone_generic = !VARS.force_unclone_generic
        MCM.SetToggleOptionValue(p_option_force_unclone_generic, VARS.force_unclone_generic, do_update)

    ; Outfitting
    elseIf id_option == p_option_auto_outfit
        VARS.auto_outfit = !VARS.auto_outfit
        MCM.SetToggleOptionValue(p_option_auto_outfit, VARS.auto_outfit, do_update)
    elseIf id_option == p_option_fill_outfits
        VARS.fill_outfits = !VARS.fill_outfits
        MCM.SetToggleOptionValue(p_option_fill_outfits, VARS.fill_outfits, do_update)

    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if id_option == p_option_slider_ms_display
        MCM.SetSliderDialogStartValue(VARS.num_display as float)
        MCM.SetSliderDialogDefaultValue(CONSTS.DEFAULT_DISPLAY as float)
        MCM.SetSliderDialogRange(CONSTS.MIN_DISPLAY as float, CONSTS.MAX_DISPLAY as float)
        MCM.SetSliderDialogInterval(1.0)
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if id_option == p_option_slider_ms_display
        VARS.num_display = float_value as int
        MCM.SetSliderOptionValue(id_option, VARS.num_display, " {0} ", false)
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    string str_conflict_message

    if code_key > -1 && str_conflict_control
        str_conflict_message = "This conflicts with '" + str_conflict_control + "'"
        if str_conflict_mod
            str_conflict_message += " in the mod '" + str_conflict_mod + "'"
        else
            str_conflict_message += " in vanilla Skyrim"
        endIf
        if !MCM.ShowMessage(str_conflict_message, true)
            return
        endIf
    endIf

    ; we need to check that in our mod, a key isn't set to multiple commands...except if the modifier is different...

    if false

    ; Followers
    elseIf id_option == p_option_key_fs_summon_all
        VARS.key_fs_summon_all = code_key
    elseIf id_option == p_option_key_fs_summon_mobile
        VARS.key_fs_summon_mobile = code_key
    elseIf id_option == p_option_key_fs_summon_immobile
        VARS.key_fs_summon_immobile = code_key
    elseIf id_option == p_option_key_fs_settle
        VARS.key_fs_settle = code_key
    elseIf id_option == p_option_key_fs_unsettle
        VARS.key_fs_unsettle = code_key
    elseIf id_option == p_option_key_fs_immobilize
        VARS.key_fs_immobilize = code_key
    elseIf id_option == p_option_key_fs_mobilize
        VARS.key_fs_mobilize = code_key
    elseIf id_option == p_option_key_fs_sneak
        VARS.key_fs_sneak = code_key
    elseIf id_option == p_option_key_fs_unsneak
        VARS.key_fs_unsneak = code_key
    elseIf id_option == p_option_key_fs_resurrect
        VARS.key_fs_resurrect = code_key

    ; Members Display
    elseIf id_option == p_option_key_ms_display_toggle
        VARS.key_ms_display_toggle = code_key
    elseIf id_option == p_option_key_ms_display_previous
        VARS.key_ms_display_previous = code_key
    elseIf id_option == p_option_key_ms_display_next
        VARS.key_ms_display_next = code_key
    
    ; Actors Move
    elseIf id_option == p_option_key_move_toggle
        VARS.key_move_toggle = code_key
    elseIf id_option == p_option_key_move_farther
        VARS.key_move_farther = code_key
    elseIf id_option == p_option_key_move_nearer
        VARS.key_move_nearer = code_key
    elseIf id_option == p_option_key_move_rotate_right
        VARS.key_move_rotate_right = code_key
    elseIf id_option == p_option_key_move_rotate_left
        VARS.key_move_rotate_left = code_key
    
    ; Member/Follower Toggles
    elseIf id_option == p_option_key_m_toggle_member
        VARS.key_m_toggle_member = code_key
    elseIf id_option == p_option_key_m_toggle_clone
        VARS.key_m_toggle_clone = code_key
    elseIf id_option == p_option_key_m_toggle_settler
        VARS.key_m_toggle_settler = code_key
    elseIf id_option == p_option_key_m_toggle_thrall
        VARS.key_m_toggle_thrall = code_key
    elseIf id_option == p_option_key_m_toggle_immobile
        VARS.key_m_toggle_immobile = code_key
    elseIf id_option == p_option_key_m_toggle_paralyzed
        VARS.key_m_toggle_paralyzed = code_key
    elseIf id_option == p_option_key_m_toggle_follower
        VARS.key_m_toggle_follower = code_key
    elseIf id_option == p_option_key_m_toggle_sneak
        VARS.key_m_toggle_sneak = code_key

    else
        return

    endIf

    KEYS.Update_Keys()

    MCM.SetKeymapOptionValue(id_option, code_key, false)
endFunction

function f_On_Option_Default(int id_option)
    if false

    ; need to deal with the case that the var is already the constant. just quit silently.

    ; Followers
    elseIf id_option == p_option_key_fs_summon_all
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_SUMMON_ALL)
            VARS.key_fs_summon_all = CONSTS.KEY_DEF_FS_SUMMON_ALL
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_ALL, false)
        endIf
    elseIf id_option == p_option_key_fs_summon_mobile
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_SUMMON_MOBILE)
            VARS.key_fs_summon_mobile = CONSTS.KEY_DEF_FS_SUMMON_MOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_MOBILE, false)
        endIf
    elseIf id_option == p_option_key_fs_summon_immobile
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE)
            VARS.key_fs_summon_immobile = CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE, false)
        endIf
    elseIf id_option == p_option_key_fs_settle
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_SETTLE)
            VARS.key_fs_settle = CONSTS.KEY_DEF_FS_SETTLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SETTLE, false)
        endIf
    elseIf id_option == p_option_key_fs_unsettle
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_UNSETTLE)
            VARS.key_fs_unsettle = CONSTS.KEY_DEF_FS_UNSETTLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_UNSETTLE, false)
        endIf
    elseIf id_option == p_option_key_fs_immobilize
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_IMMOBILIZE)
            VARS.key_fs_immobilize = CONSTS.KEY_DEF_FS_IMMOBILIZE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_IMMOBILIZE, false)
        endIf
    elseIf id_option == p_option_key_fs_mobilize
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_MOBILIZE)
            VARS.key_fs_mobilize = CONSTS.KEY_DEF_FS_MOBILIZE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_MOBILIZE, false)
        endIf
    elseIf id_option == p_option_key_fs_sneak
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_SNEAK)
            VARS.key_fs_sneak = CONSTS.KEY_DEF_FS_SNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SNEAK, false)
        endIf
    elseIf id_option == p_option_key_fs_unsneak
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_UNSNEAK)
            VARS.key_fs_unsneak = CONSTS.KEY_DEF_FS_UNSNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_UNSNEAK, false)
        endIf
    elseIf id_option == p_option_key_fs_resurrect
        if p_Can_Set_Key(CONSTS.KEY_DEF_FS_RESURRECT)
            VARS.key_fs_resurrect = CONSTS.KEY_DEF_FS_RESURRECT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_RESURRECT, false)
        endIf

    ; Members Display
    elseIf id_option == p_option_key_ms_display_toggle
        if p_Can_Set_Key(CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE)
            VARS.key_ms_display_toggle = CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE, false)
        endIf
    elseIf id_option == p_option_key_ms_display_previous
        if p_Can_Set_Key(CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS)
            VARS.key_ms_display_previous = CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS, false)
        endIf
    elseIf id_option == p_option_key_ms_display_next
        if p_Can_Set_Key(CONSTS.KEY_DEF_MS_DISPLAY_NEXT)
            VARS.key_ms_display_next = CONSTS.KEY_DEF_MS_DISPLAY_NEXT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_NEXT, false)
        endIf
    
    ; Actors Move
    elseIf id_option == p_option_key_move_toggle
        if p_Can_Set_Key(CONSTS.KEY_DEF_MOVE_TOGGLE)
            VARS.key_move_toggle = CONSTS.KEY_DEF_MOVE_TOGGLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_TOGGLE, false)
        endIf
    elseIf id_option == p_option_key_move_farther
        if p_Can_Set_Key(CONSTS.KEY_DEF_MOVE_FARTHER)
            VARS.key_move_farther = CONSTS.KEY_DEF_MOVE_FARTHER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_FARTHER, false)
        endIf
    elseIf id_option == p_option_key_move_nearer
        if p_Can_Set_Key(CONSTS.KEY_DEF_MOVE_NEARER)
            VARS.key_move_nearer = CONSTS.KEY_DEF_MOVE_NEARER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_NEARER, false)
        endIf
    elseIf id_option == p_option_key_move_rotate_right
        if p_Can_Set_Key(CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT)
            VARS.key_move_rotate_right = CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT, false)
        endIf
    elseIf id_option == p_option_key_move_rotate_left
        if p_Can_Set_Key(CONSTS.KEY_DEF_MOVE_ROTATE_LEFT)
            VARS.key_move_rotate_left = CONSTS.KEY_DEF_MOVE_ROTATE_LEFT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_ROTATE_LEFT, false)
        endIf
    
    ; Member/Follower Toggles
    elseIf id_option == p_option_key_m_toggle_member
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_MEMBER)
            VARS.key_m_toggle_member = CONSTS.KEY_DEF_M_TOGGLE_MEMBER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_MEMBER, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_clone
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_CLONE)
            VARS.key_m_toggle_clone = CONSTS.KEY_DEF_M_TOGGLE_CLONE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_CLONE, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_settler
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_SETTLER)
            VARS.key_m_toggle_settler = CONSTS.KEY_DEF_M_TOGGLE_SETTLER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_SETTLER, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_thrall
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_THRALL)
            VARS.key_m_toggle_thrall = CONSTS.KEY_DEF_M_TOGGLE_THRALL
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_THRALL, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_immobile
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE)
            VARS.key_m_toggle_immobile = CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_paralyzed
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_PARALYZED)
            VARS.key_m_toggle_paralyzed = CONSTS.KEY_DEF_M_TOGGLE_PARALYZED
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_PARALYZED, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_follower
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER)
            VARS.key_m_toggle_follower = CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_sneak
        if p_Can_Set_Key(CONSTS.KEY_DEF_M_TOGGLE_SNEAK)
            VARS.key_m_toggle_sneak = CONSTS.KEY_DEF_M_TOGGLE_SNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_SNEAK, false)
        endIf

    endIf

    KEYS.Update_Keys()
endFunction

function f_On_Option_Highlight(int id_option)
    if false

    ; General
    elseIf id_option == p_option_auto_style
        if VARS.auto_style == CODES.IS_DEFAULT
            MCM.SetInfoText("When an npc becomes a member, they will fight how they wish.")
        elseIf VARS.auto_style == CODES.IS_WARRIOR
            MCM.SetInfoText("When an npc becomes a member, they will fight as a warrior.")
        elseIf VARS.auto_style == CODES.IS_MAGE
            MCM.SetInfoText("When an npc becomes a member, they will fight as a mage.")
        elseIf VARS.auto_style == CODES.IS_ARCHER
            MCM.SetInfoText("When an npc becomes a member, they will fight as an archer.")
        endIf
    elseIf id_option == p_option_auto_vitality
        if VARS.auto_vitality == CODES.IS_MORTAL
            MCM.SetInfoText("When an npc becomes a member, they will be mortal.")
        elseIf VARS.auto_vitality == CODES.IS_PROTECTED
            MCM.SetInfoText("When an npc becomes a member, they will be protected and only you can kill them.")
        elseIf VARS.auto_vitality == CODES.IS_ESSENTIAL
            MCM.SetInfoText("When an npc becomes a member, they will be essential and will recover when they bleedout.")
        elseIf VARS.auto_vitality == CODES.IS_INVULNERABLE
            MCM.SetInfoText("When an npc becomes a member, they will be invulnerable and cannot be hurt.")
        endIf
    elseIf id_option == p_option_auto_resurrect
        if VARS.auto_resurrect
            MCM.SetInfoText("Followers will automatically resurrect after each battle.")
        else
            MCM.SetInfoText("Followers will not automatically resurrect after each battle.")
        endIf

    ; Cloning
    elseIf id_option == p_option_force_clone_unique
        if VARS.force_clone_unique
            MCM.SetInfoText("Only a clone of a unique npc can become a member, and not the unique npc.")
        else
            MCM.SetInfoText("Allows a unique npc to become a member as well as its clone.")
        endIf
    elseIf id_option == p_option_force_clone_generic
        if VARS.force_clone_generic
            MCM.SetInfoText("Only a clone of a generic npc can become a member, and not the generic npc.")
        else
            MCM.SetInfoText("Allows a generic npc to become a member as well as its clone.")
        endIf
    elseIf id_option == p_option_force_unclone_unique
        if VARS.force_unclone_unique
            MCM.SetInfoText("Forces a clone of a unique npc to be uncloned instead of unmembered.")
        else
            MCM.SetInfoText("Allows a clone of a unique npc to be unmembered or uncloned.")
        endIf
    elseIf id_option == p_option_force_unclone_generic
        if VARS.force_unclone_generic
            MCM.SetInfoText("Forces a clone of a generic npc to be uncloned instead of unmembered.")
        else
            MCM.SetInfoText("Allows a clone of a generic npc to be unmembered or uncloned.")
        endIf

    ; Outfitting
    elseIf id_option == p_option_auto_outfit
        if VARS.auto_outfit
            MCM.SetInfoText("Members will automatically dress for each activity.")
        else
            MCM.SetInfoText("Members will not automatically dress for each activity.")
        endIf
    elseIf id_option == p_option_fill_outfits
        if VARS.fill_outfits
            MCM.SetInfoText("Members will automatically receive items for each outfit.")
        else
            MCM.SetInfoText("Members will not automatically receive items for each outfit, and will be naked until you equip them.")
        endIf
    
    ; Followers Hotkeys
    elseIf id_option == p_option_key_fs_summon_all
        MCM.SetInfoText("Summons all followers before you.")
    elseIf id_option == p_option_key_fs_summon_mobile
        MCM.SetInfoText("Summons only mobilized followers before you.")
    elseIf id_option == p_option_key_fs_summon_immobile
        MCM.SetInfoText("Summons only immobilized followers before you.")
    elseIf id_option == p_option_key_fs_settle
        MCM.SetInfoText("Causes all followers to settle or resettle where they are currently standing.")
    elseIf id_option == p_option_key_fs_unsettle
        MCM.SetInfoText("Causes all followers to no longer be settlers.")
    elseIf id_option == p_option_key_fs_immobilize
        MCM.SetInfoText("Causes all followers to become immobile.")
    elseIf id_option == p_option_key_fs_mobilize
        MCM.SetInfoText("Causes all followers to become mobile.")
    elseIf id_option == p_option_key_fs_sneak
        MCM.SetInfoText("Causes all followers to start sneaking.")
    elseIf id_option == p_option_key_fs_unsneak
        MCM.SetInfoText("Causes all followers to stop sneaking.")
    elseIf id_option == p_option_key_fs_resurrect
        MCM.SetInfoText("Causes all dead followers to resurrect.")

    ; Display Hotkeys
    elseIf id_option == p_option_key_ms_display_toggle
        MCM.SetInfoText("Toggles a member display.")
    elseIf id_option == p_option_key_ms_display_previous
        MCM.SetInfoText("Will rotate members backward on display.")
    elseIf id_option == p_option_key_ms_display_next
        MCM.SetInfoText("Will rotate members forward on the display.")

    ; Move Hotkeys
    elseIf id_option == p_option_key_move_toggle
        MCM.SetInfoText("Toggles the act of moving an npc.")
    elseIf id_option == p_option_key_move_farther
        MCM.SetInfoText("While moving an npc, this will make them go farther away from you.")
    elseIf id_option == p_option_key_move_nearer
        MCM.SetInfoText("While moving an npc, this will make them come closer to you.")
    elseIf id_option == p_option_key_move_rotate_right
        MCM.SetInfoText("While moving an npc, this will make them turn counter-clockwise.")
    elseIf id_option == p_option_key_move_rotate_left
        MCM.SetInfoText("While moving an npc, this will make them turn clockwise.")
    
    ; Member/Follower Toggle Hotkeys
    elseIf id_option == p_option_key_m_toggle_member
        MCM.SetInfoText("Causes an npc to be membered or unmembered.")
    elseIf id_option == p_option_key_m_toggle_clone
        MCM.SetInfoText("Causes an npc to be cloned or uncloned. The npc will become a member if they are not already.")
    elseIf id_option == p_option_key_m_toggle_settler
        MCM.SetInfoText("Causes an npc to be settled or unsettled. The npc will become a member if they are not already.")
    elseIf id_option == p_option_key_m_toggle_thrall
        MCM.SetInfoText("Causes an npc to be enthralled or unthralled. The npc will become a member if they are not already.")
    elseIf id_option == p_option_key_m_toggle_immobile
        MCM.SetInfoText("Causes an npc to be immobile or mobile. The npc will become a member if they are not already.")
    elseIf id_option == p_option_key_m_toggle_paralyzed
        MCM.SetInfoText("Causes an npc to be paralyzed or unparalyzed. The npc will become a member if they are not already.")
    elseIf id_option == p_option_key_m_toggle_follower
        MCM.SetInfoText("Causes an npc to follower or unfollow. The npc will become a member if they are not already.")
    elseIf id_option == p_option_key_m_toggle_sneak
        MCM.SetInfoText("Causes an npc to sneak or unsneak. The npc will become a member and a follower if they are not already.")

    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

; Private Methods
bool function p_Can_Set_Key(int code_key)
    string str_control = MCM.GetCustomControl(code_key)

    if !str_control
        return true
    endIf

    return MCM.ShowMessage("This conflicts with '" + str_control + "'. Set key anyway?", true)
endFunction

function p_Set_Default_Keys()
endFunction
