Scriptname doticu_npcp_mcm_settings extends Quest

; Private Constants
doticu_npcp_codes   p_CODES                         = none
doticu_npcp_vars    p_VARS                          = none
doticu_npcp_mcm     p_MCM                           = none

; Private Variables
int                 p_option_force_clone_unique     =   -1
int                 p_option_force_clone_generic    =   -1
int                 p_option_force_unclone_unique   =   -1
int                 p_option_force_unclone_generic  =   -1
int                 p_option_auto_style             =   -1
int                 p_option_auto_vitality          =   -1
int                 p_option_auto_resurrect         =   -1

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_MCM = DATA.MODS.CONTROL.MCM
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

function f_On_Option_Highlight(int id_option)
endFunction

; Private States
auto state p_STATE_SETTINGS
    function f_Build_Page()
        p_MCM.SetCursorPosition(0)
        p_MCM.SetCursorFillMode(p_MCM.LEFT_TO_RIGHT)

        p_MCM.SetTitleText(" Settings ")

        p_MCM.AddHeaderOption(" General ")
        p_MCM.AddEmptyOption()
        p_option_force_clone_unique = p_MCM.AddToggleOption("Force Clone Unique NPCs", p_VARS.force_clone_unique)
        p_option_force_unclone_unique = p_MCM.AddToggleOption("Force Unclone Unique NPCs", p_VARS.force_unclone_unique)
        p_option_force_clone_generic = p_MCM.AddToggleOption("Force Clone Generic NPCs", p_VARS.force_clone_generic)
        p_option_force_unclone_generic = p_MCM.AddToggleOption("Force Unclone Generic NPCs", p_VARS.force_unclone_generic)
        if p_VARS.auto_style == p_CODES.IS_DEFAULT
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", " Default ")
        elseIf p_VARS.auto_style == p_CODES.IS_WARRIOR
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", " Warrior ")
        elseIf p_VARS.auto_style == p_CODES.IS_MAGE
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", " Mage ")
        elseIf p_VARS.auto_style == p_CODES.IS_ARCHER
            p_option_auto_style = p_MCM.AddTextOption("Auto Style", " Archer ")
        endIf
        if p_VARS.auto_vitality == p_CODES.IS_MORTAL
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Vitality", " Mortal ")
        elseIf p_VARS.auto_vitality == p_CODES.IS_PROTECTED
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Style", " Protected ")
        elseIf p_VARS.auto_vitality == p_CODES.IS_ESSENTIAL
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Style", " Essential ")
        elseIf p_VARS.auto_vitality == p_CODES.IS_INVULNERABLE
            p_option_auto_vitality = p_MCM.AddTextOption("Auto Style", " Invulnerable ")
        endIf
        p_option_auto_resurrect = p_MCM.AddToggleOption("Auto Resurrect Followers", p_VARS.auto_resurrect)
        p_MCM.AddEmptyOption()

        p_MCM.AddEmptyOption()
        p_MCM.AddEmptyOption()

        p_MCM.AddHeaderOption(" Hotkeys ")
        p_MCM.AddEmptyOption()
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_force_clone_unique
            p_VARS.force_clone_unique = !p_VARS.force_clone_unique
        elseIf id_option == p_option_force_clone_generic
            p_VARS.force_clone_generic = !p_VARS.force_clone_generic
        elseIf id_option == p_option_force_unclone_unique
            p_VARS.force_unclone_unique = !p_VARS.force_unclone_unique
        elseIf id_option == p_option_force_unclone_generic
            p_VARS.force_unclone_generic = !p_VARS.force_unclone_generic
        elseIf id_option == p_option_auto_style
            if p_VARS.auto_style == p_CODES.IS_DEFAULT
                p_VARS.auto_style = p_CODES.IS_WARRIOR
            elseIf p_VARS.auto_style == p_CODES.IS_WARRIOR
                p_VARS.auto_style = p_CODES.IS_MAGE
            elseIf p_VARS.auto_style == p_CODES.IS_MAGE
                p_VARS.auto_style = p_CODES.IS_ARCHER
            elseIf p_VARS.auto_style == p_CODES.IS_ARCHER
                p_VARS.auto_style = p_CODES.IS_DEFAULT
            endIf
        elseIf id_option == p_option_auto_vitality
            if p_VARS.auto_vitality == p_CODES.IS_MORTAL
                p_VARS.auto_vitality = p_CODES.IS_PROTECTED
            elseIf p_VARS.auto_vitality == p_CODES.IS_PROTECTED
                p_VARS.auto_vitality = p_CODES.IS_ESSENTIAL
            elseIf p_VARS.auto_vitality == p_CODES.IS_ESSENTIAL
                p_VARS.auto_vitality = p_CODES.IS_INVULNERABLE
            elseIf p_VARS.auto_vitality == p_CODES.IS_INVULNERABLE
                p_VARS.auto_vitality = p_CODES.IS_MORTAL
            endIf
        elseIf id_option == p_option_auto_resurrect
            p_VARS.auto_resurrect = !p_VARS.auto_resurrect
        endIf
        p_MCM.ForcePageReset()
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_force_clone_unique
            if p_VARS.force_clone_unique
                p_MCM.SetInfoText("Forces a clone to become a member instead of its original unique npc.")
            else
                p_MCM.SetInfoText("Allows a unique npc to become a member instead of its clone.")
            endIf
        elseIf id_option == p_option_force_clone_generic
            if p_VARS.force_clone_generic
                p_MCM.SetInfoText("Forces a clone to become a member instead of its original generic npc.")
            else
                p_MCM.SetInfoText("Allows a generic npc to become a member instead of its clone.")
            endIf
        elseIf id_option == p_option_force_unclone_unique
            if p_VARS.force_unclone_unique
                p_MCM.SetInfoText("Forces a clone of a unique npc to be destroyed when unmembered.")
            else
                p_MCM.SetInfoText("Allows a clone of a unique npc to still exist when unmembered.")
            endIf
        elseIf id_option == p_option_force_unclone_generic
            if p_VARS.force_unclone_generic
                p_MCM.SetInfoText("Forces a clone of a generic npc to be destroyed when unmembered.")
            else
                p_MCM.SetInfoText("Allows a clone of a generic npc to still exist when unmembered.")
            endIf
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
        endIf
    endFunction
endState
