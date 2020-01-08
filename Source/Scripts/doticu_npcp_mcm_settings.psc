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

int                 p_option_key_ms_display_start       =    -1
int                 p_option_key_ms_display_stop        =    -1
int                 p_option_key_ms_display_previous    =    -1
int                 p_option_key_ms_display_next        =    -1
int                 p_option_key_ms_toggle_display      =    -1

int                 p_option_key_m_toggle_paralyzed     =    -1

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

function f_Build_Page()
endFunction

function f_On_Option_Select(int id_option)
endFunction

function f_On_Option_Menu_Open(int id_option)
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Highlight(int id_option)
endFunction

; Private States
auto state p_STATE_SETTINGS
    function f_Build_Page()
        MCM.SetCursorPosition(0)
        MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

        MCM.SetTitleText(" Settings ")

        MCM.AddHeaderOption(" Cloning ")
        MCM.AddEmptyOption()
        p_option_force_clone_unique = MCM.AddToggleOption("Force Clone Unique NPCs", VARS.force_clone_unique)
        p_option_force_unclone_unique = MCM.AddToggleOption("Force Unclone Unique NPCs", VARS.force_unclone_unique)
        p_option_force_clone_generic = MCM.AddToggleOption("Force Clone Generic NPCs", VARS.force_clone_generic)
        p_option_force_unclone_generic = MCM.AddToggleOption("Force Unclone Generic NPCs", VARS.force_unclone_generic)
        MCM.AddEmptyOption()
        MCM.AddEmptyOption()

        MCM.AddHeaderOption(" Automatics "); eventually 'General'
        MCM.AddEmptyOption()
        if VARS.auto_style == CODES.IS_DEFAULT
            p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_DEFAULT); should be default instead of auto
        elseIf VARS.auto_style == CODES.IS_WARRIOR
            p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_WARRIOR)
        elseIf VARS.auto_style == CODES.IS_MAGE
            p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_MAGE)
        elseIf VARS.auto_style == CODES.IS_ARCHER
            p_option_auto_style = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_ARCHER)
        endIf
        if VARS.auto_vitality == CODES.IS_MORTAL
            p_option_auto_vitality = MCM.AddTextOption("Auto Vitality", CONSTS.STR_MCM_MORTAL); should be default instead of auto
        elseIf VARS.auto_vitality == CODES.IS_PROTECTED
            p_option_auto_vitality = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_PROTECTED)
        elseIf VARS.auto_vitality == CODES.IS_ESSENTIAL
            p_option_auto_vitality = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_ESSENTIAL)
        elseIf VARS.auto_vitality == CODES.IS_INVULNERABLE
            p_option_auto_vitality = MCM.AddTextOption("Auto Style", CONSTS.STR_MCM_INVULNERABLE)
        endIf
        p_option_auto_resurrect = MCM.AddToggleOption("Auto Resurrect Followers", VARS.auto_resurrect)
        p_option_auto_outfit = MCM.AddToggleOption("Auto Outfit", VARS.auto_outfit)
        MCM.AddEmptyOption()
        MCM.AddEmptyOption()

        MCM.AddHeaderOption(" Hotkeys for All Followers ")
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

        MCM.AddHeaderOption(" Hotkeys for All Members ")
        MCM.AddEmptyOption()
        p_option_key_ms_display_start = MCM.AddKeymapOption(" Start Display ", VARS.key_ms_display_start, MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_ms_display_stop = MCM.AddKeymapOption(" Stop Display ", VARS.key_ms_display_stop, MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_ms_display_previous = MCM.AddKeymapOption(" Previous Display ", VARS.key_ms_display_previous, MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_ms_display_next = MCM.AddKeymapOption(" Next Display ", VARS.key_ms_display_next, MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_ms_toggle_display = MCM.AddKeymapOption(" Toggle Display ", VARS.key_ms_toggle_display, MCM.OPTION_FLAG_WITH_UNMAP)
        MCM.AddEmptyOption()

        MCM.AddHeaderOption(" Hotkeys for One Follower/Member ")
        MCM.AddEmptyOption()
        p_option_key_m_toggle_paralyzed = MCM.AddKeymapOption(" Toggle Paralyzed ", VARS.key_toggle_paralyzed, MCM.OPTION_FLAG_WITH_UNMAP)
        MCM.AddEmptyOption()
        MCM.AddEmptyOption()
        MCM.AddEmptyOption()
    endFunction

    function f_On_Option_Select(int id_option)
        bool do_update = false
        bool dont_update = true

        if id_option == p_option_force_clone_unique
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
        elseIf id_option == p_option_auto_outfit
            VARS.auto_outfit = !VARS.auto_outfit
            MCM.SetToggleOptionValue(p_option_auto_outfit, VARS.auto_outfit, do_update)
        endIf

        MCM.SetInfoText("Testing, can you see this?")
        ;f_On_Option_Highlight(id_option); doesn't seem to work.
    endFunction

    function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
        bool do_update = false
        bool dont_update = true
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

        if id_option == p_option_key_fs_summon_all
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

        elseIf id_option == p_option_key_ms_display_start
            VARS.key_ms_display_start = code_key
        elseIf id_option == p_option_key_ms_display_stop
            VARS.key_ms_display_stop = code_key
        elseIf id_option == p_option_key_ms_display_previous
            VARS.key_ms_display_previous = code_key
        elseIf id_option == p_option_key_ms_display_next
            VARS.key_ms_display_next = code_key
        elseIf id_option == p_option_key_ms_toggle_display
            VARS.key_ms_toggle_display = code_key
        
        elseIf id_option == p_option_key_m_toggle_paralyzed
            VARS.key_toggle_paralyzed = code_key
        endIf

        KEYS.Update_Keys()
        MCM.SetKeymapOptionValue(id_option, code_key, do_update)
        f_On_Option_Highlight(id_option)
    endFunction

    function f_On_Option_Highlight(int id_option)
        ; Cloning
        if id_option == p_option_force_clone_unique
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
        
        ; Automatics
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
        elseIf id_option == p_option_auto_outfit
            if VARS.auto_outfit
                MCM.SetInfoText("Members will automatically dress for each activity.")
            else
                MCM.SetInfoText("Members will not automatically dress for each activity.")
            endIf
        
        ; Hotkeys
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

        elseIf id_option == p_option_key_ms_display_start
            MCM.SetInfoText("Will start a display of members.")
        elseIf id_option == p_option_key_ms_display_stop
            MCM.SetInfoText("Will stop a display of members.")
        elseIf id_option == p_option_key_ms_display_previous
            MCM.SetInfoText("Will rotate members backward on display.")
        elseIf id_option == p_option_key_ms_display_next
            MCM.SetInfoText("Will rotate members forward on the display.")
        elseIf id_option == p_option_key_ms_toggle_display
            MCM.SetInfoText("Toggles a member display.")

        elseIf id_option == p_option_key_m_toggle_paralyzed
            MCM.SetInfoText("Causes a member to become paralyzed.")
        endIf
    endFunction
endState
