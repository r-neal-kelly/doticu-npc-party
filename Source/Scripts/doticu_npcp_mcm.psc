;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm extends SKI_ConfigBase

; Modules
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
doticu_npcp_mcm_followers property MCM_FOLLOWERS
    doticu_npcp_mcm_followers function Get()
        return (self as Quest) as doticu_npcp_mcm_followers
    endFunction
endProperty
doticu_npcp_mcm_members property MCM_MEMBERS
    doticu_npcp_mcm_members function Get()
        return (self as Quest) as doticu_npcp_mcm_members
    endFunction
endProperty
doticu_npcp_mcm_member property MCM_MEMBER
    doticu_npcp_mcm_member function Get()
        return (self as Quest) as doticu_npcp_mcm_member
    endFunction
endProperty
doticu_npcp_mcm_filter property MCM_FILTER
    doticu_npcp_mcm_filter function Get()
        return (self as Quest) as doticu_npcp_mcm_filter
    endFunction
endProperty
doticu_npcp_mcm_mannequins property MCM_MANNEQUINS
    doticu_npcp_mcm_mannequins function Get()
        return (self as Quest) as doticu_npcp_mcm_mannequins
    endFunction
endProperty
doticu_npcp_mcm_chests property MCM_CHESTS
    doticu_npcp_mcm_chests function Get()
        return (self as Quest) as doticu_npcp_mcm_chests
    endFunction
endProperty
doticu_npcp_mcm_settings property MCM_SETTINGS
    doticu_npcp_mcm_settings function Get()
        return (self as Quest) as doticu_npcp_mcm_settings
    endFunction
endProperty
doticu_npcp_mcm_hotkeys property MCM_HOTKEYS
    doticu_npcp_mcm_hotkeys function Get()
        return (self as Quest) as doticu_npcp_mcm_hotkeys
    endFunction
endProperty
doticu_npcp_mcm_log property MCM_LOG
    doticu_npcp_mcm_log function Get()
        return (self as Quest) as doticu_npcp_mcm_log
    endFunction
endProperty

; Public Constants
string property STR_HEALTH                  = "Health"                      autoReadOnly hidden
string property STR_MAGICKA                 = "Magicka"                     autoReadOnly hidden
string property STR_STAMINA                 = "Stamina"                     autoReadOnly hidden
string property STR_ONE_HANDED              = "OneHanded"                   autoReadOnly hidden
string property STR_TWO_HANDED              = "TwoHanded"                   autoReadOnly hidden
string property STR_BLOCK                   = "Block"                       autoReadOnly hidden
string property STR_HEAVY_ARMOR             = "HeavyArmor"                  autoReadOnly hidden
string property STR_LIGHT_ARMOR             = "LightArmor"                  autoReadOnly hidden
string property STR_SMITHING                = "Smithing"                    autoReadOnly hidden
string property STR_DESTRUCTION             = "Destruction"                 autoReadOnly hidden
string property STR_RESTORATION             = "Restoration"                 autoReadOnly hidden
string property STR_CONJURATION             = "Conjuration"                 autoReadOnly hidden
string property STR_ALTERATION              = "Alteration"                  autoReadOnly hidden
string property STR_ILLUSION                = "Illusion"                    autoReadOnly hidden
string property STR_ENCHANTING              = "Enchanting"                  autoReadOnly hidden
string property STR_MARKSMAN                = "Marksman"                    autoReadOnly hidden
string property STR_SNEAK                   = "Sneak"                       autoReadOnly hidden
string property STR_ALCHEMY                 = "Alchemy"                     autoReadOnly hidden
string property STR_LOCKPICKING             = "Lockpicking"                 autoReadOnly hidden
string property STR_PICKPOCKET              = "Pickpocket"                  autoReadOnly hidden
string property STR_SPEECHCRAFT             = "Speechcraft"                 autoReadOnly hidden

string property STR_MCM_SUMMON              = " Summon "                    autoReadOnly hidden
string property STR_MCM_GOTO                = " Goto "                      autoReadOnly hidden
string property STR_MCM_PACK                = " Pack "                      autoReadOnly hidden
string property STR_MCM_OUTFIT              = " Outfit "                    autoReadOnly hidden
string property STR_MCM_STYLE               = " Style "                     autoReadOnly hidden
string property STR_MCM_VITALIZE            = " Vitalize "                  autoReadOnly hidden
string property STR_MCM_RATING              = " Rating "                    autoReadOnly hidden
string property STR_MCM_VITALITY            = " Vitality "                  autoReadOnly hidden
string property STR_MCM_CURRENT             = " Current "                   autoReadOnly hidden
string property STR_MCM_MEMBER              = " Member "                    autoReadOnly hidden
string property STR_MCM_SETTLER             = " Settler "                   autoReadOnly hidden
string property STR_MCM_THRALL              = " Thrall "                    autoReadOnly hidden
string property STR_MCM_IMMOBILE            = " Immobile "                  autoReadOnly hidden
string property STR_MCM_FOLLOWER            = " Follower "                  autoReadOnly hidden
string property STR_MCM_VANILLA             = " Vanilla "                   autoReadOnly hidden
string property STR_MCM_SETTLE              = " Settle "                    autoReadOnly hidden
string property STR_MCM_RESETTLE            = " Resettle "                  autoReadOnly hidden
string property STR_MCM_UNSETTLE            = " Unsettle "                  autoReadOnly hidden
string property STR_MCM_IMMOBILIZE          = " Immobilize "                autoReadOnly hidden
string property STR_MCM_MOBILIZE            = " Mobilize "                  autoReadOnly hidden
string property STR_MCM_PARALYZE            = " Paralyze "                  autoReadOnly hidden
string property STR_MCM_UNPARALYZE          = " Unparalyze "                autoReadOnly hidden
string property STR_MCM_FOLLOW              = " Follow "                    autoReadOnly hidden
string property STR_MCM_UNFOLLOW            = " Unfollow "                  autoReadOnly hidden
string property STR_MCM_UNSNEAK             = " Unsneak "                   autoReadOnly hidden
string property STR_MCM_RESURRECT           = " Resurrect "                 autoReadOnly hidden
string property STR_MCM_DEFAULT             = " Default "                   autoReadOnly hidden
string property STR_MCM_WARRIOR             = " Warrior "                   autoReadOnly hidden
string property STR_MCM_MAGE                = " Mage "                      autoReadOnly hidden
string property STR_MCM_ARCHER              = " Archer "                    autoReadOnly hidden
string property STR_MCM_COWARD              = " Coward "                    autoReadOnly hidden
string property STR_MCM_MORTAL              = " Mortal "                    autoReadOnly hidden
string property STR_MCM_PROTECTED           = " Protected "                 autoReadOnly hidden
string property STR_MCM_ESSENTIAL           = " Essential "                 autoReadOnly hidden
string property STR_MCM_INVULNERABLE        = " Invulnerable "              autoReadOnly hidden
string property STR_MCM_CLONE               = " Clone "                     autoReadOnly hidden
string property STR_MCM_UNCLONE             = " Unclone "                   autoReadOnly hidden
string property STR_MCM_UNMEMBER            = " Unmember "                  autoReadOnly hidden
string property STR_MCM_BASE                = " Base "                      autoReadOnly hidden
string property STR_MCM_REFERENCE           = " Reference "                 autoReadOnly hidden
string property STR_MCM_RACE                = " Race "                      autoReadOnly hidden

string property STR_MCM_HEALTH              = " Health "                    autoReadOnly hidden
string property STR_MCM_MAGICKA             = " Magicka "                   autoReadOnly hidden
string property STR_MCM_STAMINA             = " Stamina "                   autoReadOnly hidden
string property STR_MCM_ONE_HANDED          = " One Handed "                autoReadOnly hidden
string property STR_MCM_TWO_HANDED          = " Two Handed "                autoReadOnly hidden
string property STR_MCM_BLOCK               = " Block "                     autoReadOnly hidden
string property STR_MCM_HEAVY_ARMOR         = " Heavy Armor "               autoReadOnly hidden
string property STR_MCM_LIGHT_ARMOR         = " Light Armor "               autoReadOnly hidden
string property STR_MCM_SMITHING            = " Smithing "                  autoReadOnly hidden
string property STR_MCM_DESTRUCTION         = " Destruction "               autoReadOnly hidden
string property STR_MCM_RESTORATION         = " Restoration "               autoReadOnly hidden
string property STR_MCM_CONJURATION         = " Conjuration "               autoReadOnly hidden
string property STR_MCM_ALTERATION          = " Alteration "                autoReadOnly hidden
string property STR_MCM_ILLUSION            = " Illusion "                  autoReadOnly hidden
string property STR_MCM_ENCHANTING          = " Enchanting "                autoReadOnly hidden
string property STR_MCM_MARKSMAN            = " Marksman "                  autoReadOnly hidden
string property STR_MCM_SNEAK               = " Sneak "                     autoReadOnly hidden
string property STR_MCM_ALCHEMY             = " Alchemy "                   autoReadOnly hidden
string property STR_MCM_LOCKPICKING         = " Lockpicking "               autoReadOnly hidden
string property STR_MCM_PICKPOCKET          = " Pickpocket "                autoReadOnly hidden
string property STR_MCM_SPEECHCRAFT         = " Speechcraft "               autoReadOnly hidden

string property PAGE_FOLLOWERS              = " Followers "                 autoReadOnly hidden
string property PAGE_MEMBERS                = " Members "                   autoReadOnly hidden
string property PAGE_MANNEQUINS             = " Mannequins "                autoReadOnly hidden
string property PAGE_CHESTS                 = " Chests "                    autoReadOnly hidden
string property PAGE_FILTER                 = " Filter "                    autoReadOnly hidden
string property PAGE_SETTINGS               = " Settings "                  autoReadOnly hidden
string property PAGE_HOTKEYS                = " Hotkeys "                   autoReadOnly hidden
string property PAGE_LOG                    = " Log "                       autoReadOnly hidden

bool property DO_UPDATE     = false autoReadOnly hidden
bool property DONT_UPDATE   = true  autoReadOnly hidden

int property FLAG_ENABLE hidden
    int function Get()
        return OPTION_FLAG_NONE
    endFunction
endProperty
int property FLAG_DISABLE hidden
    int function Get()
        return OPTION_FLAG_DISABLED
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA              =  none

; Private Variables
bool                p_is_created        = false
bool                p_is_custom_page    = false
string              p_str_def_page      =    ""
string              p_str_curr_page     =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_is_custom_page = false
    p_str_def_page = PAGE_SETTINGS; or a help page? or global stats page?
    p_str_curr_page = p_str_def_page

    MCM_FOLLOWERS.f_Create(DATA)
    MCM_MEMBERS.f_Create(DATA)
    MCM_MEMBER.f_Create(DATA)
    MCM_FILTER.f_Create(DATA)
    MCM_MANNEQUINS.f_Create(DATA)
    MCM_CHESTS.f_Create(DATA)
    MCM_SETTINGS.f_Create(DATA)
    MCM_HOTKEYS.f_Create(DATA)
    MCM_LOG.f_Create(DATA)
endFunction

function f_Destroy()
    MCM_LOG.f_Destroy()
    MCM_HOTKEYS.f_Destroy()
    MCM_SETTINGS.f_Destroy()
    MCM_CHESTS.f_Destroy()
    MCM_MANNEQUINS.f_Destroy()
    MCM_FILTER.f_Destroy()
    MCM_MEMBER.f_Destroy()
    MCM_MEMBERS.f_Destroy()
    MCM_FOLLOWERS.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    MCM_FOLLOWERS.f_Register()
    MCM_MEMBERS.f_Register()
    MCM_MEMBER.f_Register()
    MCM_FILTER.f_Register()
    MCM_MANNEQUINS.f_Register()
    MCM_CHESTS.f_Register()
    MCM_SETTINGS.f_Register()
    MCM_HOTKEYS.f_Register()
    MCM_LOG.f_Register()
endFunction

function f_Unregister()
    MCM_LOG.f_Unregister()
    MCM_HOTKEYS.f_Unregister()
    MCM_SETTINGS.f_Unregister()
    MCM_CHESTS.f_Unregister()
    MCM_MANNEQUINS.f_Unregister()
    MCM_FILTER.f_Unregister()
    MCM_MEMBER.f_Unregister()
    MCM_MEMBERS.f_Unregister()
    MCM_FOLLOWERS.f_Unregister()
endFunction

function f_Change_Page(string str_page)
    p_str_curr_page = str_page
    p_is_custom_page = true
    ForcePageReset()
endFunction

string function f_Get_Current_Page()
    return p_str_curr_page
endFunction

function f_Enable(int id_option, bool bool_update)
    SetOptionFlags(id_option, FLAG_ENABLE, bool_update)
endFunction

function f_Disable(int id_option, bool bool_update)
    SetOptionFlags(id_option, FLAG_DISABLE, bool_update)
endFunction

; Events
event OnConfigInit()
    ModName = " NPC Party"
endEvent

event OnConfigOpen()
    VARS.is_mcm_open = true

    Pages = Utility.CreateStringArray(8, "")
    Pages[0] = PAGE_FOLLOWERS
    Pages[1] = PAGE_MEMBERS
    Pages[2] = PAGE_MANNEQUINS
    Pages[3] = PAGE_FILTER
    Pages[4] = PAGE_CHESTS
    Pages[5] = PAGE_SETTINGS
    Pages[6] = PAGE_HOTKEYS
    Pages[7] = PAGE_LOG
endEvent

event OnConfigClose()
    VARS.is_mcm_open = false
endEvent

event OnPageReset(string str_page)
    if str_page == ""
        ; open the last viewed page rather than a blank one
        str_page = p_str_curr_page
    endIf

    if p_is_custom_page
        ; override for programmatic page changes
        str_page = p_str_curr_page
        p_is_custom_page = false
    endIf

    if str_page == PAGE_FOLLOWERS
        p_str_curr_page = str_page
        MCM_FOLLOWERS.f_Build_Page()
    elseIf str_page == PAGE_MEMBERS
        p_str_curr_page = str_page
        MCM_MEMBERS.f_View_Members(p_DATA.MODS.MEMBERS.Get_Members())
        MCM_MEMBERS.f_Build_Page()
    elseIf str_page == PAGE_FILTER
        p_str_curr_page = str_page
        MCM_FILTER.f_Build_Page()
    elseIf str_page == PAGE_MANNEQUINS
        p_str_curr_page = str_page
        MCM_MANNEQUINS.f_Build_Page()
    elseIf str_page == PAGE_CHESTS
        p_str_curr_page = str_page
        MCM_CHESTS.f_Build_Page()
    elseIf str_page == PAGE_SETTINGS
        p_str_curr_page = str_page
        MCM_SETTINGS.f_Build_Page()
    elseIf str_page == PAGE_HOTKEYS
        p_str_curr_page = str_page
        MCM_HOTKEYS.f_Build_Page()
    elseIf str_page == PAGE_LOG
        p_str_curr_page = str_page
        MCM_LOG.f_Build_Page()
    else
        p_str_curr_page = p_str_def_page
        ForcePageReset()
    endIf
endEvent

event OnOptionSelect(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Select(id_option)
    endIf
endEvent

event OnOptionMenuOpen(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Menu_Open(id_option)
    endIf
endEvent

event OnOptionMenuAccept(int id_option, int idx_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endEvent

event OnOptionSliderOpen(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Slider_Open(id_option)
    endIf
endEvent

event OnOptionSliderAccept(int id_option, float float_value)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endEvent

event OnOptionInputAccept(int id_option, string str_input)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endEvent

event OnOptionKeymapChange(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endEvent

event OnOptionDefault(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Default(id_option)
    endIf
endEvent

event OnOptionHighlight(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Highlight(id_option)
    endIf
endEvent

; Update Methods
function u_0_9_1()
    MCM_CHESTS.f_Create(p_DATA)
    MCM_CHESTS.f_Register()
    MCM_HOTKEYS.f_Create(p_DATA)
    MCM_HOTKEYS.f_Register()
endFunction
