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
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
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

; Public Constants
bool property DO_UPDATE hidden
    bool function Get()
        return MCM.DO_UPDATE
    endFunction
endProperty
bool property DONT_UPDATE hidden
    bool function Get()
        return MCM.DONT_UPDATE
    endFunction
endProperty
int property FLAG_ENABLE hidden
    int function Get()
        return MCM.FLAG_ENABLE
    endFunction
endProperty
int property FLAG_DISABLE hidden
    int function Get()
        return MCM.FLAG_DISABLE
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
int                 p_option_clone_outfit               =    -1
int                 p_option_auto_style                 =    -1
int                 p_option_auto_vitality              =    -1
int                 p_option_auto_resurrect             =    -1
int                 p_option_slider_max_members         =    -1

int                 p_option_auto_outfit                =    -1
int                 p_option_fill_outfits               =    -1
int                 p_option_auto_immobile_outfit       =    -1
int                 p_option_slider_percent_body        =    -1
int                 p_option_slider_percent_feet        =    -1
int                 p_option_slider_percent_hands       =    -1
int                 p_option_slider_percent_head        =    -1

int                 p_option_sort_members               =    -1
int                 p_option_sort_followers             =    -1

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

int                 p_option_key_n_has_base             =    -1
int                 p_option_key_n_count_base           =    -1

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
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_DEFAULT)
    elseIf VARS.auto_style == CODES.IS_WARRIOR
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_WARRIOR)
    elseIf VARS.auto_style == CODES.IS_MAGE
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_MAGE)
    elseIf VARS.auto_style == CODES.IS_ARCHER
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_ARCHER)
    elseIf VARS.auto_style == CODES.IS_COWARD
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_COWARD)
    endIf
    if VARS.auto_vitality == CODES.IS_MORTAL
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_MORTAL)
    elseIf VARS.auto_vitality == CODES.IS_PROTECTED
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_PROTECTED)
    elseIf VARS.auto_vitality == CODES.IS_ESSENTIAL
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_ESSENTIAL)
    elseIf VARS.auto_vitality == CODES.IS_INVULNERABLE
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_INVULNERABLE)
    endIf
    p_option_auto_resurrect = MCM.AddToggleOption(" Auto Resurrect Followers ", VARS.auto_resurrect)
    p_option_slider_max_members = MCM.AddSliderOption(" Max Members ", VARS.max_members, " {0} ")
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Cloning ")
    MCM.AddEmptyOption()
    p_option_force_clone_unique = MCM.AddToggleOption(" Force Clone Unique NPCs ", VARS.force_clone_unique)
    p_option_force_unclone_unique = MCM.AddToggleOption(" Force Unclone Unique NPCs ", VARS.force_unclone_unique)
    p_option_force_clone_generic = MCM.AddToggleOption(" Force Clone Generic NPCs ", VARS.force_clone_generic)
    p_option_force_unclone_generic = MCM.AddToggleOption(" Force Unclone Generic NPCs ", VARS.force_unclone_generic)
    if VARS.clone_outfit == CODES.OUTFIT_BASE
        p_option_clone_outfit = MCM.AddTextOption(" New Clone Outfit ", CONSTS.STR_MCM_BASE)
    elseIf VARS.clone_outfit == CODES.OUTFIT_REFERENCE
        p_option_clone_outfit = MCM.AddTextOption(" New Clone Outfit ", CONSTS.STR_MCM_REFERENCE)
    endIf
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Outfitting ")
    MCM.AddEmptyOption()
    p_option_auto_outfit = MCM.AddToggleOption(" Auto Change Outfits ", VARS.auto_outfit)
    if VARS.auto_outfit
        p_option_auto_immobile_outfit = MCM.AddToggleOption(" Use Auto Immobile ", VARS.auto_immobile_outfit, FLAG_ENABLE)
    else
        p_option_auto_immobile_outfit = MCM.AddToggleOption(" Use Auto Immobile ", VARS.auto_immobile_outfit, FLAG_DISABLE)
    endIf
    p_option_fill_outfits = MCM.AddToggleOption(" Auto Fill Outfits ", VARS.fill_outfits)
    MCM.AddEmptyOption()
    if VARS.fill_outfits
        p_option_slider_percent_body = MCM.AddSliderOption(" Fill Body Chance ", VARS.percent_body, " {0}% ")
        p_option_slider_percent_feet = MCM.AddSliderOption(" Fill Feet Chance ", VARS.percent_feet, " {0}% ")
        p_option_slider_percent_hands = MCM.AddSliderOption(" Fill Hands Chance ", VARS.percent_hands, " {0}% ")
        p_option_slider_percent_head = MCM.AddSliderOption(" Fill Head Chance ", VARS.percent_head, " {0}% ")
    endIf
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Sorting ")
    MCM.AddEmptyOption()
    p_option_sort_members = MCM.AddTextOption(" Members Algorithm ", VARS.str_sort_members)
    p_option_sort_followers = MCM.AddTextOption(" Followers Algorithm ", VARS.str_sort_followers)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Displaying ")
    MCM.AddEmptyOption()
    p_option_key_ms_display_toggle = MCM.AddKeymapOption(" Toggle Display ", VARS.key_ms_display_toggle, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_slider_ms_display = MCM.AddSliderOption(" Members per Cycle ", VARS.num_display, " {0} ")
    p_option_key_ms_display_previous = MCM.AddKeymapOption(" Previous Members ", VARS.key_ms_display_previous, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_ms_display_next = MCM.AddKeymapOption(" Next Members ", VARS.key_ms_display_next, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Moving ")
    MCM.AddEmptyOption()
    p_option_key_move_toggle = MCM.AddKeymapOption(" Toggle Move ", VARS.key_move_toggle, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    p_option_key_move_nearer = MCM.AddKeymapOption(" Move Nearer ", VARS.key_move_nearer, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_move_farther = MCM.AddKeymapOption(" Move Farther ", VARS.key_move_farther, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_move_rotate_left = MCM.AddKeymapOption(" Rotate Clockwise ", VARS.key_move_rotate_left, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_move_rotate_right = MCM.AddKeymapOption(" Rotate Counter-Clockwise ", VARS.key_move_rotate_right, MCM.OPTION_FLAG_WITH_UNMAP)
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

    MCM.AddHeaderOption(" One NPC ")
    MCM.AddEmptyOption()
    p_option_key_n_has_base = MCM.AddKeymapOption(" Has Base ", VARS.key_n_has_base, MCM.OPTION_FLAG_WITH_UNMAP)
    p_option_key_n_count_base = MCM.AddKeymapOption(" Count Base ", VARS.key_n_count_base, MCM.OPTION_FLAG_WITH_UNMAP)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
endFunction

function f_On_Option_Select(int id_option)
    if false

    ; General
    elseIf id_option == p_option_auto_style
        if VARS.auto_style == CODES.IS_DEFAULT
            VARS.auto_style = CODES.IS_WARRIOR
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_WARRIOR)
        elseIf VARS.auto_style == CODES.IS_WARRIOR
            VARS.auto_style = CODES.IS_MAGE
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_MAGE)
        elseIf VARS.auto_style == CODES.IS_MAGE
            VARS.auto_style = CODES.IS_ARCHER
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_ARCHER)
        elseIf VARS.auto_style == CODES.IS_ARCHER
            VARS.auto_style = CODES.IS_COWARD
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_COWARD)
        elseIf VARS.auto_style == CODES.IS_COWARD
            VARS.auto_style = CODES.IS_DEFAULT
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_DEFAULT)
        endIf
    elseIf id_option == p_option_auto_vitality
        if VARS.auto_vitality == CODES.IS_MORTAL
            VARS.auto_vitality = CODES.IS_PROTECTED
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_PROTECTED)
        elseIf VARS.auto_vitality == CODES.IS_PROTECTED
            VARS.auto_vitality = CODES.IS_ESSENTIAL
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_ESSENTIAL)
        elseIf VARS.auto_vitality == CODES.IS_ESSENTIAL
            VARS.auto_vitality = CODES.IS_INVULNERABLE
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_INVULNERABLE)
        elseIf VARS.auto_vitality == CODES.IS_INVULNERABLE
            VARS.auto_vitality = CODES.IS_MORTAL
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_MORTAL)
        endIf
    elseIf id_option == p_option_auto_resurrect
        VARS.auto_resurrect = !VARS.auto_resurrect
        MCM.SetToggleOptionValue(p_option_auto_resurrect, VARS.auto_resurrect)

    ; Cloning
    elseIf id_option == p_option_force_clone_unique
        VARS.force_clone_unique = !VARS.force_clone_unique
        MCM.SetToggleOptionValue(p_option_force_clone_unique, VARS.force_clone_unique)
    elseIf id_option == p_option_force_clone_generic
        VARS.force_clone_generic = !VARS.force_clone_generic
        MCM.SetToggleOptionValue(p_option_force_clone_generic, VARS.force_clone_generic)
    elseIf id_option == p_option_force_unclone_unique
        VARS.force_unclone_unique = !VARS.force_unclone_unique
        MCM.SetToggleOptionValue(p_option_force_unclone_unique, VARS.force_unclone_unique)
    elseIf id_option == p_option_force_unclone_generic
        VARS.force_unclone_generic = !VARS.force_unclone_generic
        MCM.SetToggleOptionValue(p_option_force_unclone_generic, VARS.force_unclone_generic)
    elseIf id_option == p_option_clone_outfit
        if VARS.clone_outfit == CODES.OUTFIT_BASE
            VARS.clone_outfit = CODES.OUTFIT_REFERENCE
            MCM.SetTextOptionValue(p_option_clone_outfit, CONSTS.STR_MCM_REFERENCE)
        elseIf VARS.clone_outfit == CODES.OUTFIT_REFERENCE
            VARS.clone_outfit = CODES.OUTFIT_BASE
            MCM.SetTextOptionValue(p_option_clone_outfit, CONSTS.STR_MCM_BASE)
        endIf

    ; Outfitting
    elseIf id_option == p_option_auto_outfit
        VARS.auto_outfit = !VARS.auto_outfit
        MCM.SetToggleOptionValue(p_option_auto_outfit, VARS.auto_outfit)
        if VARS.auto_outfit
            MCM.SetOptionFlags(p_option_auto_immobile_outfit, FLAG_ENABLE, DO_UPDATE)
        else
            MCM.SetOptionFlags(p_option_auto_immobile_outfit, FLAG_DISABLE, DO_UPDATE)
        endIf
    elseIf id_option == p_option_auto_immobile_outfit
        VARS.auto_immobile_outfit = !VARS.auto_immobile_outfit
        MCM.SetToggleOptionValue(p_option_auto_immobile_outfit, VARS.auto_immobile_outfit)
    elseIf id_option == p_option_fill_outfits
        VARS.fill_outfits = !VARS.fill_outfits
        MCM.SetToggleOptionValue(p_option_fill_outfits, VARS.fill_outfits)
        if VARS.fill_outfits
            MCM.f_Enable(p_option_slider_percent_body, DONT_UPDATE)
            MCM.f_Enable(p_option_slider_percent_feet, DONT_UPDATE)
            MCM.f_Enable(p_option_slider_percent_hands, DONT_UPDATE)
            MCM.f_Enable(p_option_slider_percent_head, DO_UPDATE)
        else
            MCM.f_Disable(p_option_slider_percent_body, DONT_UPDATE)
            MCM.f_Disable(p_option_slider_percent_feet, DONT_UPDATE)
            MCM.f_Disable(p_option_slider_percent_hands, DONT_UPDATE)
            MCM.f_Disable(p_option_slider_percent_head, DO_UPDATE)
        endIf

    ; Sorting
    elseIf id_option == p_option_sort_members
        if false

        elseIf VARS.str_sort_members == "NAME"
            VARS.str_sort_members = "NAME_CASELESS"
        elseIf VARS.str_sort_members == "NAME_CASELESS"
            VARS.str_sort_members = "RATING_NAME"
        elseIf VARS.str_sort_members == "RATING_NAME"
            VARS.str_sort_members = "RATING_NAME_CASELESS"
        elseIf VARS.str_sort_members == "RATING_NAME_CASELESS"
            VARS.str_sort_members = "NAME"
        else
            VARS.str_sort_members = "NAME"

        endIf
        MCM.SetTextOptionValue(p_option_sort_members, VARS.str_sort_members)
    elseIf id_option == p_option_sort_followers
        if false

        elseIf VARS.str_sort_followers == "NAME"
            VARS.str_sort_followers = "NAME_CASELESS"
        elseIf VARS.str_sort_followers == "NAME_CASELESS"
            VARS.str_sort_followers = "NAME"
        else
            VARS.str_sort_followers = "NAME"

        endIf
        MCM.SetTextOptionValue(p_option_sort_followers, VARS.str_sort_followers)
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if false

    elseIf id_option == p_option_slider_max_members
        MCM.SetSliderDialogStartValue(VARS.max_members as float)
        MCM.SetSliderDialogDefaultValue(MEMBERS.Get_Real_Max() as float)
        MCM.SetSliderDialogRange(MEMBERS.Get_Count() as float, MEMBERS.Get_Real_Max() as float)
        MCM.SetSliderDialogInterval(1.0)

    elseIf id_option == p_option_slider_percent_body
        MCM.SetSliderDialogStartValue(VARS.percent_body as float)
        MCM.SetSliderDialogDefaultValue(CONSTS.DEFAULT_PERCENT_BODY as float)
        MCM.SetSliderDialogRange(0 as float, 100 as float)
        MCM.SetSliderDialogInterval(1.0)
    elseIf id_option == p_option_slider_percent_feet
        MCM.SetSliderDialogStartValue(VARS.percent_feet as float)
        MCM.SetSliderDialogDefaultValue(CONSTS.DEFAULT_PERCENT_FEET as float)
        MCM.SetSliderDialogRange(0 as float, 100 as float)
        MCM.SetSliderDialogInterval(1.0)
    elseIf id_option == p_option_slider_percent_hands
        MCM.SetSliderDialogStartValue(VARS.percent_hands as float)
        MCM.SetSliderDialogDefaultValue(CONSTS.DEFAULT_PERCENT_HANDS as float)
        MCM.SetSliderDialogRange(0 as float, 100 as float)
        MCM.SetSliderDialogInterval(1.0)
    elseIf id_option == p_option_slider_percent_head
        MCM.SetSliderDialogStartValue(VARS.percent_head as float)
        MCM.SetSliderDialogDefaultValue(CONSTS.DEFAULT_PERCENT_HEAD as float)
        MCM.SetSliderDialogRange(0 as float, 100 as float)
        MCM.SetSliderDialogInterval(1.0)

    elseIf id_option == p_option_slider_ms_display
        MCM.SetSliderDialogStartValue(VARS.num_display as float)
        MCM.SetSliderDialogDefaultValue(CONSTS.DEFAULT_DISPLAY as float)
        MCM.SetSliderDialogRange(CONSTS.MIN_DISPLAY as float, CONSTS.MAX_DISPLAY as float)
        MCM.SetSliderDialogInterval(1.0)

    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if false

    elseIf id_option == p_option_slider_max_members
        VARS.max_members = float_value as int
        MCM.SetSliderOptionValue(id_option, VARS.max_members, " {0} ", DO_UPDATE)

    elseIf id_option == p_option_slider_percent_body
        VARS.percent_body = float_value as int
        MCM.SetSliderOptionValue(id_option, VARS.percent_body, " {0}% ", DO_UPDATE)
    elseIf id_option == p_option_slider_percent_feet
        VARS.percent_feet = float_value as int
        MCM.SetSliderOptionValue(id_option, VARS.percent_feet, " {0}% ", DO_UPDATE)
    elseIf id_option == p_option_slider_percent_hands
        VARS.percent_hands = float_value as int
        MCM.SetSliderOptionValue(id_option, VARS.percent_hands, " {0}% ", DO_UPDATE)
    elseIf id_option == p_option_slider_percent_head
        VARS.percent_head = float_value as int
        MCM.SetSliderOptionValue(id_option, VARS.percent_head, " {0}% ", DO_UPDATE)

    elseIf id_option == p_option_slider_ms_display
        VARS.num_display = float_value as int
        MCM.SetSliderOptionValue(id_option, VARS.num_display, " {0} ", DO_UPDATE)

    endIf
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
    elseIf id_option == p_option_key_n_has_base
        VARS.key_n_has_base = code_key
    elseIf id_option == p_option_key_n_count_base
        VARS.key_n_count_base = code_key

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

    ; Followers
    elseIf id_option == p_option_key_fs_summon_all
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SUMMON_ALL, CONSTS.KEY_DEF_FS_SUMMON_ALL)
            VARS.key_fs_summon_all = CONSTS.KEY_DEF_FS_SUMMON_ALL
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_ALL, false)
        endIf
    elseIf id_option == p_option_key_fs_summon_mobile
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SUMMON_MOBILE, CONSTS.KEY_DEF_FS_SUMMON_MOBILE)
            VARS.key_fs_summon_mobile = CONSTS.KEY_DEF_FS_SUMMON_MOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_MOBILE, false)
        endIf
    elseIf id_option == p_option_key_fs_summon_immobile
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SUMMON_IMMOBILE, CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE)
            VARS.key_fs_summon_immobile = CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE, false)
        endIf
    elseIf id_option == p_option_key_fs_settle
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SETTLE, CONSTS.KEY_DEF_FS_SETTLE)
            VARS.key_fs_settle = CONSTS.KEY_DEF_FS_SETTLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SETTLE, false)
        endIf
    elseIf id_option == p_option_key_fs_unsettle
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_UNSETTLE, CONSTS.KEY_DEF_FS_UNSETTLE)
            VARS.key_fs_unsettle = CONSTS.KEY_DEF_FS_UNSETTLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_UNSETTLE, false)
        endIf
    elseIf id_option == p_option_key_fs_immobilize
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_IMMOBILIZE, CONSTS.KEY_DEF_FS_IMMOBILIZE)
            VARS.key_fs_immobilize = CONSTS.KEY_DEF_FS_IMMOBILIZE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_IMMOBILIZE, false)
        endIf
    elseIf id_option == p_option_key_fs_mobilize
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_MOBILIZE, CONSTS.KEY_DEF_FS_MOBILIZE)
            VARS.key_fs_mobilize = CONSTS.KEY_DEF_FS_MOBILIZE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_MOBILIZE, false)
        endIf
    elseIf id_option == p_option_key_fs_sneak
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_SNEAK, CONSTS.KEY_DEF_FS_SNEAK)
            VARS.key_fs_sneak = CONSTS.KEY_DEF_FS_SNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_SNEAK, false)
        endIf
    elseIf id_option == p_option_key_fs_unsneak
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_UNSNEAK, CONSTS.KEY_DEF_FS_UNSNEAK)
            VARS.key_fs_unsneak = CONSTS.KEY_DEF_FS_UNSNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_UNSNEAK, false)
        endIf
    elseIf id_option == p_option_key_fs_resurrect
        if p_Can_Set_Key(CONSTS.STR_KEY_FS_RESURRECT, CONSTS.KEY_DEF_FS_RESURRECT)
            VARS.key_fs_resurrect = CONSTS.KEY_DEF_FS_RESURRECT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_FS_RESURRECT, false)
        endIf

    ; Members Display
    elseIf id_option == p_option_key_ms_display_toggle
        if p_Can_Set_Key(CONSTS.STR_KEY_MS_DISPLAY_TOGGLE, CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE)
            VARS.key_ms_display_toggle = CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE, false)
        endIf
    elseIf id_option == p_option_key_ms_display_previous
        if p_Can_Set_Key(CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS, CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS)
            VARS.key_ms_display_previous = CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS, false)
        endIf
    elseIf id_option == p_option_key_ms_display_next
        if p_Can_Set_Key(CONSTS.STR_KEY_MS_DISPLAY_NEXT, CONSTS.KEY_DEF_MS_DISPLAY_NEXT)
            VARS.key_ms_display_next = CONSTS.KEY_DEF_MS_DISPLAY_NEXT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MS_DISPLAY_NEXT, false)
        endIf
    
    ; Actors Move
    elseIf id_option == p_option_key_move_toggle
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_TOGGLE, CONSTS.KEY_DEF_MOVE_TOGGLE)
            VARS.key_move_toggle = CONSTS.KEY_DEF_MOVE_TOGGLE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_TOGGLE, false)
        endIf
    elseIf id_option == p_option_key_move_farther
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_FARTHER, CONSTS.KEY_DEF_MOVE_FARTHER)
            VARS.key_move_farther = CONSTS.KEY_DEF_MOVE_FARTHER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_FARTHER, false)
        endIf
    elseIf id_option == p_option_key_move_nearer
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_NEARER, CONSTS.KEY_DEF_MOVE_NEARER)
            VARS.key_move_nearer = CONSTS.KEY_DEF_MOVE_NEARER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_NEARER, false)
        endIf
    elseIf id_option == p_option_key_move_rotate_right
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_ROTATE_RIGHT, CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT)
            VARS.key_move_rotate_right = CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT, false)
        endIf
    elseIf id_option == p_option_key_move_rotate_left
        if p_Can_Set_Key(CONSTS.STR_KEY_MOVE_ROTATE_LEFT, CONSTS.KEY_DEF_MOVE_ROTATE_LEFT)
            VARS.key_move_rotate_left = CONSTS.KEY_DEF_MOVE_ROTATE_LEFT
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_MOVE_ROTATE_LEFT, false)
        endIf
    
    ; Member/Follower Toggles
    elseIf id_option == p_option_key_m_toggle_member
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_MEMBER, CONSTS.KEY_DEF_M_TOGGLE_MEMBER)
            VARS.key_m_toggle_member = CONSTS.KEY_DEF_M_TOGGLE_MEMBER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_MEMBER, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_clone
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_CLONE, CONSTS.KEY_DEF_M_TOGGLE_CLONE)
            VARS.key_m_toggle_clone = CONSTS.KEY_DEF_M_TOGGLE_CLONE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_CLONE, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_settler
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_SETTLER, CONSTS.KEY_DEF_M_TOGGLE_SETTLER)
            VARS.key_m_toggle_settler = CONSTS.KEY_DEF_M_TOGGLE_SETTLER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_SETTLER, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_thrall
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_THRALL, CONSTS.KEY_DEF_M_TOGGLE_THRALL)
            VARS.key_m_toggle_thrall = CONSTS.KEY_DEF_M_TOGGLE_THRALL
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_THRALL, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_immobile
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_IMMOBILE, CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE)
            VARS.key_m_toggle_immobile = CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_paralyzed
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_PARALYZED, CONSTS.KEY_DEF_M_TOGGLE_PARALYZED)
            VARS.key_m_toggle_paralyzed = CONSTS.KEY_DEF_M_TOGGLE_PARALYZED
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_PARALYZED, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_follower
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_FOLLOWER, CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER)
            VARS.key_m_toggle_follower = CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER, false)
        endIf
    elseIf id_option == p_option_key_m_toggle_sneak
        if p_Can_Set_Key(CONSTS.STR_KEY_M_TOGGLE_SNEAK, CONSTS.KEY_DEF_M_TOGGLE_SNEAK)
            VARS.key_m_toggle_sneak = CONSTS.KEY_DEF_M_TOGGLE_SNEAK
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_M_TOGGLE_SNEAK, false)
        endIf

    ; One NPC
    elseIf id_option == p_option_key_n_has_base
        if p_Can_Set_Key(CONSTS.STR_KEY_N_HAS_BASE, CONSTS.KEY_DEF_N_HAS_BASE)
            VARS.key_n_has_base = CONSTS.KEY_DEF_N_HAS_BASE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_N_HAS_BASE, false)
        endIf
    elseIf id_option == p_option_key_n_count_base
        if p_Can_Set_Key(CONSTS.STR_KEY_N_COUNT_BASE, CONSTS.KEY_DEF_N_COUNT_BASE)
            VARS.key_n_count_base = CONSTS.KEY_DEF_N_COUNT_BASE
            MCM.SetKeymapOptionValue(id_option, CONSTS.KEY_DEF_N_COUNT_BASE, false)
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
        elseIf VARS.auto_style == CODES.IS_COWARD
            MCM.SetInfoText("When an npc becomes a member, they will fight as a coward.")
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
    elseIf id_option == p_option_slider_max_members
        MCM.SetInfoText("A limiter for the amount of members you can have.")

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
    elseIf id_option == p_option_clone_outfit
        if VARS.clone_outfit == CODES.OUTFIT_BASE
            MCM.SetInfoText("A clone will receive the base outfit of the original npc.")
        elseIf VARS.clone_outfit == CODES.OUTFIT_REFERENCE
            MCM.SetInfoText("A clone will receive the current outfit of the original npc.")
        endIf

    ; Outfitting
    elseIf id_option == p_option_auto_outfit
        if VARS.auto_outfit
            MCM.SetInfoText("Members will automatically dress for each activity.")
        else
            MCM.SetInfoText("Members will not automatically dress for each activity.")
        endIf
    elseIf id_option == p_option_auto_immobile_outfit
        if VARS.auto_immobile_outfit
            MCM.SetInfoText("When auto outfitting, members will equip their immobile outfit when applicable.")
        else
            MCM.SetInfoText("When auto outfitting, members will never equip their immobile outfit even when applicable.")
        endIf
    elseIf id_option == p_option_fill_outfits
        if VARS.fill_outfits
            MCM.SetInfoText("Members will automatically receive items for each outfit.")
        else
            MCM.SetInfoText("Members will not automatically receive items for each outfit, and will be naked until you equip them.")
        endIf
    elseIf id_option == p_option_slider_percent_body
        MCM.SetInfoText("The chance that outfits will get items that fit on the body.")
    elseIf id_option == p_option_slider_percent_feet
        MCM.SetInfoText("The chance that outfits will get items that fit on the feet.")
    elseIf id_option == p_option_slider_percent_hands
        MCM.SetInfoText("The chance that outfits will get items that fit on the hands.")
    elseIf id_option == p_option_slider_percent_head
        MCM.SetInfoText("The chance that outfits will get items that fit on the head.")

    ; Sorting
    elseIf id_option == p_option_sort_members
        MCM.SetInfoText("The algorithm that is used to sort members. CASELESS ignores capitals.")
    elseIf id_option == p_option_sort_followers
        MCM.SetInfoText("The algorithm that is used to sort followers. CASELESS ignores capitals.")

    ; Displaying
    elseIf id_option == p_option_key_ms_display_toggle
        MCM.SetInfoText("Toggles a member display.")
    elseIf id_option == p_option_slider_ms_display
        MCM.SetInfoText("The number of members which will be summoned at a time during a display.")
    elseIf id_option == p_option_key_ms_display_previous
        MCM.SetInfoText("Will loop through the previous members on display.")
    elseIf id_option == p_option_key_ms_display_next
        MCM.SetInfoText("Will loop through the next members on display.")

    ; Moving
    elseIf id_option == p_option_key_move_toggle
        MCM.SetInfoText("Toggles the act of moving an npc.")
    elseIf id_option == p_option_key_move_farther
        MCM.SetInfoText("While moving an npc, this will make them go farther away from you.")
    elseIf id_option == p_option_key_move_nearer
        MCM.SetInfoText("While moving an npc, this will make them come closer to you.")
    elseIf id_option == p_option_key_move_rotate_left
        MCM.SetInfoText("While moving an npc, this will make them turn clockwise.")
    elseIf id_option == p_option_key_move_rotate_right
        MCM.SetInfoText("While moving an npc, this will make them turn counter-clockwise.")
    
    ; All Followers
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
    
    ; One Follower/Member
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
        MCM.SetInfoText("Causes an npc to follow or unfollow. The npc will become a member if they are not already.")
    elseIf id_option == p_option_key_m_toggle_sneak
        MCM.SetInfoText("Causes an npc to sneak or unsneak. The npc will become a member and a follower if they are not already.")

    ; One NPC
    elseIf id_option == p_option_key_n_has_base
        MCM.SetInfoText("Shows whether or not you have a member with the same base as this npc.")
    elseIf id_option == p_option_key_n_count_base
        MCM.SetInfoText("Shows how many members you have with the same base as this npc.")

    endIf
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

    ; Followers
    elseIf id_option == p_option_key_fs_summon_all
        return CONSTS.STR_KEY_FS_SUMMON_ALL
    elseIf id_option == p_option_key_fs_summon_mobile
        return CONSTS.STR_KEY_FS_SUMMON_MOBILE
    elseIf id_option == p_option_key_fs_summon_immobile
        return CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
    elseIf id_option == p_option_key_fs_settle
        return CONSTS.STR_KEY_FS_SETTLE
    elseIf id_option == p_option_key_fs_unsettle
        return CONSTS.STR_KEY_FS_UNSETTLE
    elseIf id_option == p_option_key_fs_immobilize
        return CONSTS.STR_KEY_FS_IMMOBILIZE
    elseIf id_option == p_option_key_fs_mobilize
        return CONSTS.STR_KEY_FS_MOBILIZE
    elseIf id_option == p_option_key_fs_sneak
        return CONSTS.STR_KEY_FS_SNEAK
    elseIf id_option == p_option_key_fs_unsneak
        return CONSTS.STR_KEY_FS_UNSNEAK
    elseIf id_option == p_option_key_fs_resurrect
        return CONSTS.STR_KEY_FS_RESURRECT

    ; Members Display
    elseIf id_option == p_option_key_ms_display_toggle
        return CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
    elseIf id_option == p_option_key_ms_display_previous
        return CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS
    elseIf id_option == p_option_key_ms_display_next
        return CONSTS.STR_KEY_MS_DISPLAY_NEXT
    
    ; Actors Move
    elseIf id_option == p_option_key_move_toggle
        return CONSTS.STR_KEY_MOVE_TOGGLE
    elseIf id_option == p_option_key_move_farther
        return CONSTS.STR_KEY_MOVE_FARTHER
    elseIf id_option == p_option_key_move_nearer
        return CONSTS.STR_KEY_MOVE_NEARER
    elseIf id_option == p_option_key_move_rotate_right
        return CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
    elseIf id_option == p_option_key_move_rotate_left
        return CONSTS.STR_KEY_MOVE_ROTATE_LEFT
    
    ; Member/Follower Toggles
    elseIf id_option == p_option_key_m_toggle_member
        return CONSTS.STR_KEY_M_TOGGLE_MEMBER
    elseIf id_option == p_option_key_m_toggle_clone
        return CONSTS.STR_KEY_M_TOGGLE_CLONE
    elseIf id_option == p_option_key_m_toggle_settler
        return CONSTS.STR_KEY_M_TOGGLE_SETTLER
    elseIf id_option == p_option_key_m_toggle_thrall
        return CONSTS.STR_KEY_M_TOGGLE_THRALL
    elseIf id_option == p_option_key_m_toggle_immobile
        return CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
    elseIf id_option == p_option_key_m_toggle_paralyzed
        return CONSTS.STR_KEY_M_TOGGLE_PARALYZED
    elseIf id_option == p_option_key_m_toggle_follower
        return CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
    elseIf id_option == p_option_key_m_toggle_sneak
        return CONSTS.STR_KEY_M_TOGGLE_SNEAK

    ; One NPC
    elseIf id_option == p_option_key_n_has_base
        return CONSTS.STR_KEY_N_HAS_BASE
    elseIf id_option == p_option_key_n_count_base
        return CONSTS.STR_KEY_N_COUNT_BASE

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
