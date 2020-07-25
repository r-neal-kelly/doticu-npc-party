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
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
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

int                 p_option_slider_ms_display          =    -1

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
    if VARS.auto_style == doticu_npcp_codes.STYLE_DEFAULT()
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_DEFAULT)
    elseIf VARS.auto_style == doticu_npcp_codes.STYLE_WARRIOR()
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_WARRIOR)
    elseIf VARS.auto_style == doticu_npcp_codes.STYLE_MAGE()
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_MAGE)
    elseIf VARS.auto_style == doticu_npcp_codes.STYLE_ARCHER()
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_ARCHER)
    elseIf VARS.auto_style == doticu_npcp_codes.STYLE_COWARD()
        p_option_auto_style = MCM.AddTextOption(" New Member Style ", CONSTS.STR_MCM_COWARD)
    endIf
    if VARS.auto_vitality == doticu_npcp_codes.VITALITY_MORTAL()
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_MORTAL)
    elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_PROTECTED()
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_PROTECTED)
    elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_ESSENTIAL)
    elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
        p_option_auto_vitality = MCM.AddTextOption(" New Member Vitality ", CONSTS.STR_MCM_INVULNERABLE)
    endIf
    p_option_slider_max_members = MCM.AddSliderOption(" Max Members ", VARS.max_members, " {0} ")
    p_option_slider_ms_display = MCM.AddSliderOption(" Members per Display Cycle ", VARS.num_display, " {0} ")
    p_option_auto_resurrect = MCM.AddToggleOption(" Auto Resurrect Followers ", VARS.auto_resurrect)
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()
    MCM.AddEmptyOption()

    MCM.AddHeaderOption(" Cloning ")
    MCM.AddEmptyOption()
    p_option_force_clone_unique = MCM.AddToggleOption(" Force Clone Unique NPCs ", VARS.force_clone_unique)
    p_option_force_unclone_unique = MCM.AddToggleOption(" Force Unclone Unique NPCs ", VARS.force_unclone_unique)
    p_option_force_clone_generic = MCM.AddToggleOption(" Force Clone Generic NPCs ", VARS.force_clone_generic)
    p_option_force_unclone_generic = MCM.AddToggleOption(" Force Unclone Generic NPCs ", VARS.force_unclone_generic)
    if VARS.clone_outfit == doticu_npcp_codes.OUTFIT_BASE()
        p_option_clone_outfit = MCM.AddTextOption(" New Clone Outfit ", CONSTS.STR_MCM_BASE)
    elseIf VARS.clone_outfit == doticu_npcp_codes.OUTFIT_REFERENCE()
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
endFunction

function f_On_Option_Select(int id_option)
    if false

    ; General
    elseIf id_option == p_option_auto_style
        if VARS.auto_style == doticu_npcp_codes.STYLE_DEFAULT()
            VARS.auto_style = doticu_npcp_codes.STYLE_WARRIOR()
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_WARRIOR)
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_WARRIOR()
            VARS.auto_style = doticu_npcp_codes.STYLE_MAGE()
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_MAGE)
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_MAGE()
            VARS.auto_style = doticu_npcp_codes.STYLE_ARCHER()
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_ARCHER)
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_ARCHER()
            VARS.auto_style = doticu_npcp_codes.STYLE_COWARD()
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_COWARD)
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_COWARD()
            VARS.auto_style = doticu_npcp_codes.STYLE_DEFAULT()
            MCM.SetTextOptionValue(p_option_auto_style, CONSTS.STR_MCM_DEFAULT)
        endIf
    elseIf id_option == p_option_auto_vitality
        if VARS.auto_vitality == doticu_npcp_codes.VITALITY_MORTAL()
            VARS.auto_vitality = doticu_npcp_codes.VITALITY_PROTECTED()
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_PROTECTED)
        elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_PROTECTED()
            VARS.auto_vitality = doticu_npcp_codes.VITALITY_ESSENTIAL()
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_ESSENTIAL)
        elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
            VARS.auto_vitality = doticu_npcp_codes.VITALITY_INVULNERABLE()
            MCM.SetTextOptionValue(p_option_auto_vitality, CONSTS.STR_MCM_INVULNERABLE)
        elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
            VARS.auto_vitality = doticu_npcp_codes.VITALITY_MORTAL()
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
        if VARS.clone_outfit == doticu_npcp_codes.OUTFIT_BASE()
            VARS.clone_outfit = doticu_npcp_codes.OUTFIT_REFERENCE()
            MCM.SetTextOptionValue(p_option_clone_outfit, CONSTS.STR_MCM_REFERENCE)
        elseIf VARS.clone_outfit == doticu_npcp_codes.OUTFIT_REFERENCE()
            VARS.clone_outfit = doticu_npcp_codes.OUTFIT_BASE()
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
        MCM.SetSliderDialogDefaultValue(MEMBERS.Get_Max() as float)
        MCM.SetSliderDialogRange(MEMBERS.Get_Count() as float, MEMBERS.Get_Max() as float)
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

function f_On_Option_Highlight(int id_option)
    if false

    ; General
    elseIf id_option == p_option_auto_style
        if VARS.auto_style == doticu_npcp_codes.STYLE_DEFAULT()
            MCM.SetInfoText("When an npc becomes a member, they will fight how they wish.")
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_WARRIOR()
            MCM.SetInfoText("When an npc becomes a member, they will fight as a warrior.")
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_MAGE()
            MCM.SetInfoText("When an npc becomes a member, they will fight as a mage.")
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_ARCHER()
            MCM.SetInfoText("When an npc becomes a member, they will fight as an archer.")
        elseIf VARS.auto_style == doticu_npcp_codes.STYLE_COWARD()
            MCM.SetInfoText("When an npc becomes a member, they will fight as a coward.")
        endIf
    elseIf id_option == p_option_auto_vitality
        if VARS.auto_vitality == doticu_npcp_codes.VITALITY_MORTAL()
            MCM.SetInfoText("When an npc becomes a member, they will be mortal.")
        elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_PROTECTED()
            MCM.SetInfoText("When an npc becomes a member, they will be protected and only you can kill them.")
        elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
            MCM.SetInfoText("When an npc becomes a member, they will be essential and will recover when they bleedout.")
        elseIf VARS.auto_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
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
        if VARS.clone_outfit == doticu_npcp_codes.OUTFIT_BASE()
            MCM.SetInfoText("A clone will receive the base outfit of the original npc.")
        elseIf VARS.clone_outfit == doticu_npcp_codes.OUTFIT_REFERENCE()
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
    elseIf id_option == p_option_slider_ms_display
        MCM.SetInfoText("The number of members which will be summoned at a time during a display.")

    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Default(int id_option)
endFunction
