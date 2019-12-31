Scriptname doticu_npcp_mcm_settings extends Quest

; Private Constants
doticu_npcp_consts  p_CONSTS                        = none
doticu_npcp_codes   p_CODES                         = none
doticu_npcp_vars    p_VARS                          = none
doticu_npcp_keys    p_KEYS                          = none
doticu_npcp_mcm     p_MCM                           = none

; Private Variables
int                 p_option_force_clone_unique     =   -1
int                 p_option_force_clone_generic    =   -1
int                 p_option_force_unclone_unique   =   -1
int                 p_option_force_unclone_generic  =   -1
int                 p_option_auto_style             =   -1
int                 p_option_auto_vitality          =   -1
int                 p_option_auto_resurrect         =   -1
int                 p_option_auto_outfit            =   -1
int                 p_option_key_fs_summon_all      =   -1
int                 p_option_key_fs_summon_mobile   =   -1
int                 p_option_key_fs_summon_immobile =   -1
int                 p_option_key_fs_settle          =   -1
int                 p_option_key_fs_unsettle        =   -1
int                 p_option_key_fs_immobilize      =   -1
int                 p_option_key_fs_mobilize        =   -1
int                 p_option_key_fs_sneak           =   -1
int                 p_option_key_fs_unsneak         =   -1
int                 p_option_key_fs_resurrect       =   -1

int                 p_option_key_m_toggle_paralyzed =   -1

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_KEYS = DATA.MODS.CONTROL.KEYS
    p_MCM = DATA.MODS.CONTROL.MCM
endFunction

function f_Initialize()
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
        p_MCM.SetCursorPosition(0)
        p_MCM.SetCursorFillMode(p_MCM.LEFT_TO_RIGHT)

        p_MCM.SetTitleText(" Settings ")

        p_MCM.AddHeaderOption(" Cloning ")
        p_MCM.AddEmptyOption()
        p_option_force_clone_unique = p_MCM.AddToggleOption("Force Clone Unique NPCs", p_VARS.force_clone_unique)
        p_option_force_unclone_unique = p_MCM.AddToggleOption("Force Unclone Unique NPCs", p_VARS.force_unclone_unique)
        p_option_force_clone_generic = p_MCM.AddToggleOption("Force Clone Generic NPCs", p_VARS.force_clone_generic)
        p_option_force_unclone_generic = p_MCM.AddToggleOption("Force Unclone Generic NPCs", p_VARS.force_unclone_generic)
        p_MCM.AddEmptyOption()
        p_MCM.AddEmptyOption()

        p_MCM.AddHeaderOption(" Automatics "); eventually 'General'
        p_MCM.AddEmptyOption()
        if p_VARS.auto_style == p_CODES.IS_DEFAULT
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", p_CONSTS.STR_MCM_DEFAULT); should be default instead of auto
        elseIf p_VARS.auto_style == p_CODES.IS_WARRIOR
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", p_CONSTS.STR_MCM_WARRIOR)
        elseIf p_VARS.auto_style == p_CODES.IS_MAGE
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", p_CONSTS.STR_MCM_MAGE)
        elseIf p_VARS.auto_style == p_CODES.IS_ARCHER
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", p_CONSTS.STR_MCM_ARCHER)
        endIf
        if p_VARS.auto_vitality == p_CODES.IS_MORTAL
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Vitality", p_CONSTS.STR_MCM_MORTAL); should be default instead of auto
        elseIf p_VARS.auto_vitality == p_CODES.IS_PROTECTED
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Style", p_CONSTS.STR_MCM_PROTECTED)
        elseIf p_VARS.auto_vitality == p_CODES.IS_ESSENTIAL
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Style", p_CONSTS.STR_MCM_ESSENTIAL)
        elseIf p_VARS.auto_vitality == p_CODES.IS_INVULNERABLE
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Style", p_CONSTS.STR_MCM_INVULNERABLE)
        endIf
        p_option_auto_resurrect = p_MCM.AddToggleOption("Auto Resurrect Followers", p_VARS.auto_resurrect)
        p_option_auto_outfit = p_MCM.AddToggleOption("Auto Outfit", p_VARS.auto_outfit)
        p_MCM.AddEmptyOption()
        p_MCM.AddEmptyOption()

        p_MCM.AddHeaderOption(" Hotkeys for All Followers ")
        p_MCM.AddEmptyOption()
        p_option_key_fs_summon_all = p_MCM.AddKeymapOption(" Followers: Summon All ", p_VARS.key_fs_summon_all, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_summon_mobile = p_MCM.AddKeymapOption(" Followers: Summon Mobile ", p_VARS.key_fs_summon_mobile, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_summon_immobile = p_MCM.AddKeymapOption(" Followers: Summon Immobile ", p_VARS.key_fs_summon_immobile, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_settle = p_MCM.AddKeymapOption(" Followers: Settle ", p_VARS.key_fs_settle, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_unsettle = p_MCM.AddKeymapOption(" Followers: Unsettle ", p_VARS.key_fs_unsettle, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_immobilize = p_MCM.AddKeymapOption(" Followers: Immobilize ", p_VARS.key_fs_immobilize, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_mobilize = p_MCM.AddKeymapOption(" Followers: Mobilize ", p_VARS.key_fs_mobilize, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_sneak = p_MCM.AddKeymapOption(" Followers: Sneak ", p_VARS.key_fs_sneak, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_unsneak = p_MCM.AddKeymapOption(" Followers: Unsneak ", p_VARS.key_fs_unsneak, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_option_key_fs_resurrect = p_MCM.AddKeymapOption(" Followers: Resurrect ", p_VARS.key_fs_resurrect, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_MCM.AddEmptyOption()
        p_MCM.AddEmptyOption()

        p_MCM.AddHeaderOption(" Hotkeys for One Follower/Member ")
        p_MCM.AddEmptyOption()
        p_option_key_m_toggle_paralyzed = p_MCM.AddKeymapOption(" Member: Toggle Paralyzed ", p_VARS.key_toggle_paralyzed, p_MCM.OPTION_FLAG_WITH_UNMAP)
        p_MCM.AddEmptyOption()
        p_MCM.AddEmptyOption()
        p_MCM.AddEmptyOption()
    endFunction

    function f_On_Option_Select(int id_option)
        bool do_update = false
        bool dont_update = true

        if id_option == p_option_force_clone_unique
            p_VARS.force_clone_unique = !p_VARS.force_clone_unique
            p_MCM.SetToggleOptionValue(p_option_force_clone_unique, p_VARS.force_clone_unique, do_update)
        elseIf id_option == p_option_force_clone_generic
            p_VARS.force_clone_generic = !p_VARS.force_clone_generic
            p_MCM.SetToggleOptionValue(p_option_force_clone_generic, p_VARS.force_clone_generic, do_update)
        elseIf id_option == p_option_force_unclone_unique
            p_VARS.force_unclone_unique = !p_VARS.force_unclone_unique
            p_MCM.SetToggleOptionValue(p_option_force_unclone_unique, p_VARS.force_unclone_unique, do_update)
        elseIf id_option == p_option_force_unclone_generic
            p_VARS.force_unclone_generic = !p_VARS.force_unclone_generic
            p_MCM.SetToggleOptionValue(p_option_force_unclone_generic, p_VARS.force_unclone_generic, do_update)
        
        elseIf id_option == p_option_auto_style
            if p_VARS.auto_style == p_CODES.IS_DEFAULT
                p_VARS.auto_style = p_CODES.IS_WARRIOR
                p_MCM.SetTextOptionValue(p_option_auto_style, p_CONSTS.STR_MCM_WARRIOR, do_update)
            elseIf p_VARS.auto_style == p_CODES.IS_WARRIOR
                p_VARS.auto_style = p_CODES.IS_MAGE
                p_MCM.SetTextOptionValue(p_option_auto_style, p_CONSTS.STR_MCM_MAGE, do_update)
            elseIf p_VARS.auto_style == p_CODES.IS_MAGE
                p_VARS.auto_style = p_CODES.IS_ARCHER
                p_MCM.SetTextOptionValue(p_option_auto_style, p_CONSTS.STR_MCM_ARCHER, do_update)
            elseIf p_VARS.auto_style == p_CODES.IS_ARCHER
                p_VARS.auto_style = p_CODES.IS_DEFAULT
                p_MCM.SetTextOptionValue(p_option_auto_style, p_CONSTS.STR_MCM_DEFAULT, do_update)
            endIf
        elseIf id_option == p_option_auto_vitality
            if p_VARS.auto_vitality == p_CODES.IS_MORTAL
                p_VARS.auto_vitality = p_CODES.IS_PROTECTED
                p_MCM.SetTextOptionValue(p_option_auto_vitality, p_CONSTS.STR_MCM_PROTECTED, do_update)
            elseIf p_VARS.auto_vitality == p_CODES.IS_PROTECTED
                p_VARS.auto_vitality = p_CODES.IS_ESSENTIAL
                p_MCM.SetTextOptionValue(p_option_auto_vitality, p_CONSTS.STR_MCM_ESSENTIAL, do_update)
            elseIf p_VARS.auto_vitality == p_CODES.IS_ESSENTIAL
                p_VARS.auto_vitality = p_CODES.IS_INVULNERABLE
                p_MCM.SetTextOptionValue(p_option_auto_vitality, p_CONSTS.STR_MCM_INVULNERABLE, do_update)
            elseIf p_VARS.auto_vitality == p_CODES.IS_INVULNERABLE
                p_VARS.auto_vitality = p_CODES.IS_MORTAL
                p_MCM.SetTextOptionValue(p_option_auto_vitality, p_CONSTS.STR_MCM_MORTAL, do_update)
            endIf
        elseIf id_option == p_option_auto_resurrect
            p_VARS.auto_resurrect = !p_VARS.auto_resurrect
            p_MCM.SetToggleOptionValue(p_option_auto_resurrect, p_VARS.auto_resurrect, do_update)
        elseIf id_option == p_option_auto_outfit
            p_VARS.auto_outfit = !p_VARS.auto_outfit
            p_MCM.SetToggleOptionValue(p_option_auto_outfit, p_VARS.auto_outfit, do_update)
        endIf

        p_MCM.SetInfoText("Testing, can you see this?")
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
            if !p_MCM.ShowMessage(str_conflict_message, true)
                return
            endIf
        endIf

        ; we need to check that in our mod, a key isn't set to multiple commands...except if the modifier is different...

        if id_option == p_option_key_fs_summon_all
            p_VARS.key_fs_summon_all = code_key
        elseIf id_option == p_option_key_fs_summon_mobile
            p_VARS.key_fs_summon_mobile = code_key
        elseIf id_option == p_option_key_fs_summon_immobile
            p_VARS.key_fs_summon_immobile = code_key
        elseIf id_option == p_option_key_fs_settle
            p_VARS.key_fs_settle = code_key
        elseIf id_option == p_option_key_fs_unsettle
            p_VARS.key_fs_unsettle = code_key
        elseIf id_option == p_option_key_fs_immobilize
            p_VARS.key_fs_immobilize = code_key
        elseIf id_option == p_option_key_fs_mobilize
            p_VARS.key_fs_mobilize = code_key
        elseIf id_option == p_option_key_fs_sneak
            p_VARS.key_fs_sneak = code_key
        elseIf id_option == p_option_key_fs_unsneak
            p_VARS.key_fs_unsneak = code_key
        elseIf id_option == p_option_key_fs_resurrect
            p_VARS.key_fs_resurrect = code_key
        
        elseIf id_option == p_option_key_m_toggle_paralyzed
            p_VARS.key_toggle_paralyzed = code_key
        endIf

        p_KEYS.Update_Keys()
        p_MCM.SetKeymapOptionValue(id_option, code_key, do_update)
        f_On_Option_Highlight(id_option)
    endFunction

    function f_On_Option_Highlight(int id_option)
        ; Cloning
        if id_option == p_option_force_clone_unique
            if p_VARS.force_clone_unique
                p_MCM.SetInfoText("Only a clone of a unique npc can become a member, and not the unique npc.")
            else
                p_MCM.SetInfoText("Allows a unique npc to become a member as well as its clone.")
            endIf
        elseIf id_option == p_option_force_clone_generic
            if p_VARS.force_clone_generic
                p_MCM.SetInfoText("Only a clone of a generic npc can become a member, and not the generic npc.")
            else
                p_MCM.SetInfoText("Allows a generic npc to become a member as well as its clone.")
            endIf
        elseIf id_option == p_option_force_unclone_unique
            if p_VARS.force_unclone_unique
                p_MCM.SetInfoText("Forces a clone of a unique npc to be uncloned instead of unmembered.")
            else
                p_MCM.SetInfoText("Allows a clone of a unique npc to be unmembered or uncloned.")
            endIf
        elseIf id_option == p_option_force_unclone_generic
            if p_VARS.force_unclone_generic
                p_MCM.SetInfoText("Forces a clone of a generic npc to be uncloned instead of unmembered.")
            else
                p_MCM.SetInfoText("Allows a clone of a generic npc to be unmembered or uncloned.")
            endIf
        
        ; Automatics
        elseIf id_option == p_option_auto_style
            if p_VARS.auto_style == p_CODES.IS_DEFAULT
                p_MCM.SetInfoText("When an npc becomes a member, they will fight how they wish.")
            elseIf p_VARS.auto_style == p_CODES.IS_WARRIOR
                p_MCM.SetInfoText("When an npc becomes a member, they will fight as a warrior.")
            elseIf p_VARS.auto_style == p_CODES.IS_MAGE
                p_MCM.SetInfoText("When an npc becomes a member, they will fight as a mage.")
            elseIf p_VARS.auto_style == p_CODES.IS_ARCHER
                p_MCM.SetInfoText("When an npc becomes a member, they will fight as an archer.")
            endIf
        elseIf id_option == p_option_auto_vitality
            if p_VARS.auto_vitality == p_CODES.IS_MORTAL
                p_MCM.SetInfoText("When an npc becomes a member, they will be mortal.")
            elseIf p_VARS.auto_vitality == p_CODES.IS_PROTECTED
                p_MCM.SetInfoText("When an npc becomes a member, they will be protected and only you can kill them.")
            elseIf p_VARS.auto_vitality == p_CODES.IS_ESSENTIAL
                p_MCM.SetInfoText("When an npc becomes a member, they will be essential and will recover when they bleedout.")
            elseIf p_VARS.auto_vitality == p_CODES.IS_INVULNERABLE
                p_MCM.SetInfoText("When an npc becomes a member, they will be invulnerable and cannot be hurt.")
            endIf
        elseIf id_option == p_option_auto_resurrect
            if p_VARS.auto_resurrect
                p_MCM.SetInfoText("Followers will automatically resurrect after each battle.")
            else
                p_MCM.SetInfoText("Followers will not automatically resurrect after each battle.")
            endIf
        elseIf id_option == p_option_auto_outfit
            if p_VARS.auto_outfit
                p_MCM.SetInfoText("Members will automatically dress for each activity.")
            else
                p_MCM.SetInfoText("Members will not automatically dress for each activity.")
            endIf
        
        ; Hotkeys
        elseIf id_option == p_option_key_fs_summon_all
            p_MCM.SetInfoText("Summons all followers before you.")
        elseIf id_option == p_option_key_fs_summon_mobile
            p_MCM.SetInfoText("Summons only mobilized followers before you.")
        elseIf id_option == p_option_key_fs_summon_immobile
            p_MCM.SetInfoText("Summons only immobilized followers before you.")
        elseIf id_option == p_option_key_fs_settle
            p_MCM.SetInfoText("Causes all followers to settle or resettle where they are currently standing.")
        elseIf id_option == p_option_key_fs_unsettle
            p_MCM.SetInfoText("Causes all followers to no longer be settlers.")
        elseIf id_option == p_option_key_fs_immobilize
            p_MCM.SetInfoText("Causes all followers to become immobile.")
        elseIf id_option == p_option_key_fs_mobilize
            p_MCM.SetInfoText("Causes all followers to become mobile.")
        elseIf id_option == p_option_key_fs_sneak
            p_MCM.SetInfoText("Causes all followers to start sneaking.")
        elseIf id_option == p_option_key_fs_unsneak
            p_MCM.SetInfoText("Causes all followers to stop sneaking.")
        elseIf id_option == p_option_key_fs_resurrect
            p_MCM.SetInfoText("Causes all dead followers to resurrect.")
        endIf
    endFunction
endState
