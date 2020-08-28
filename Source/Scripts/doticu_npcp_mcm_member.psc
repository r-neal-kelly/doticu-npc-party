;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_member extends Quest

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return doticu_npcp.Control().COMMANDS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return doticu_npcp.Control().MCM
    endFunction
endProperty

; Public Constants
bool property DO_UPDATE hidden
    bool function Get()
        return MCM.DO_UPDATE
    endFunction
endProperty

; Private Variables
bool                p_is_created                = false
int                 p_code_view                 =     0

doticu_npcp_member  p_ref_member                =  none

int                 p_option_rename             =    -1
int                 p_option_back               =    -1
int                 p_option_prev               =    -1
int                 p_option_next               =    -1

int                 p_option_summon             =    -1
int                 p_option_goto               =    -1
int                 p_option_pack               =    -1
int                 p_option_stash              =    -1
int                 p_option_outfit             =    -1
int                 p_option_settle             =    -1
int                 p_option_resettle           =    -1
int                 p_option_unsettle           =    -1
int                 p_option_enthrall           =    -1
int                 p_option_unthrall           =    -1
int                 p_option_immobilize         =    -1
int                 p_option_mobilize           =    -1
int                 p_option_paralyze           =    -1
int                 p_option_unparalyze         =    -1
int                 p_option_follow             =    -1
int                 p_option_unfollow           =    -1
int                 p_option_sneak              =    -1
int                 p_option_unsneak            =    -1
int                 p_option_rating             =    -1
int                 p_option_style              =    -1
int                 p_option_vitalize           =    -1
int                 p_option_resurrect          =    -1
int                 p_option_clone              =    -1
int                 p_option_unclone            =    -1
int                 p_option_unmember           =    -1

int                 p_option_health             =    -1
int                 p_option_magicka            =    -1
int                 p_option_stamina            =    -1
int                 p_option_skill_one_handed   =    -1
int                 p_option_skill_two_handed   =    -1
int                 p_option_skill_block        =    -1
int                 p_option_skill_heavy_armor  =    -1
int                 p_option_skill_light_armor  =    -1
int                 p_option_skill_smithing     =    -1
int                 p_option_skill_destruction  =    -1
int                 p_option_skill_restoration  =    -1
int                 p_option_skill_conjuration  =    -1
int                 p_option_skill_alteration   =    -1
int                 p_option_skill_illusion     =    -1
int                 p_option_skill_enchanting   =    -1
int                 p_option_skill_marksman     =    -1
int                 p_option_skill_sneak        =    -1
int                 p_option_skill_alchemy      =    -1
int                 p_option_skill_lockpicking  =    -1
int                 p_option_skill_pickpocket   =    -1
int                 p_option_skill_speechcraft  =    -1
int                 p_option_race               =    -1

; Native Methods
function f_Build_Page() native
function p_Build_Commands() native
function p_Update_Commands() native
function p_Build_Statistics() native
function p_Update_Statistics() native

function f_On_Option_Select         (int option) native

; Friend Methods
function f_Create()
    p_is_created = true
    p_code_view = 0
    p_ref_member = none
endFunction

function f_Destroy()
    p_ref_member = none
    p_code_view = 0
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Enable(int id_option, bool bool_update)
    return MCM.f_Enable(id_option, bool_update)
endFunction

function f_Disable(int id_option, bool bool_update)
    return MCM.f_Disable(id_option, bool_update)
endFunction

function f_View_Followers_Member(doticu_npcp_member ref_member)
    p_code_view = doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()

    p_ref_member = ref_member
endFunction

function f_View_Mannequins_Member(doticu_npcp_member ref_member)
    p_code_view = doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()

    p_ref_member = ref_member
endFunction

function f_On_Option_Menu_Open(int id_option)
    if false

    elseIf id_option == p_option_outfit
        if ACTORS.Is_Vampire(doticu_npcp_consts.Player_Actor())
            string[] arr_options = Utility.CreateStringArray(8, "")

            arr_options[0] = MCM.STR_MCM_CURRENT
            arr_options[1] = MCM.STR_MCM_MEMBER
            arr_options[2] = MCM.STR_MCM_SETTLER
            arr_options[3] = MCM.STR_MCM_THRALL
            arr_options[4] = MCM.STR_MCM_FOLLOWER
            arr_options[5] = MCM.STR_MCM_IMMOBILE
            arr_options[6] = MCM.STR_MCM_VANILLA
            arr_options[7] = MCM.STR_MCM_DEFAULT

            MCM.SetMenuDialogOptions(arr_options)
        else
            string[] arr_options = Utility.CreateStringArray(7, "")

            arr_options[0] = MCM.STR_MCM_CURRENT
            arr_options[1] = MCM.STR_MCM_MEMBER
            arr_options[2] = MCM.STR_MCM_SETTLER
            arr_options[3] = MCM.STR_MCM_FOLLOWER
            arr_options[4] = MCM.STR_MCM_IMMOBILE
            arr_options[5] = MCM.STR_MCM_VANILLA
            arr_options[6] = MCM.STR_MCM_DEFAULT

            MCM.SetMenuDialogOptions(arr_options)
        endIf
    
    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if !p_ref_member
        return
    endIf

    Actor ref_actor = p_ref_member.Actor()

    if id_option == p_option_outfit
        if ACTORS.Is_Vampire(doticu_npcp_consts.Player_Actor())
            if idx_option == 0
                FUNCS.Close_Menus()
                COMMANDS.Change_Current_Outfit2(ref_actor)
            elseIf idx_option == 1
                FUNCS.Close_Menus()
                COMMANDS.Change_Member_Outfit2(ref_actor)
            elseIf idx_option == 2
                FUNCS.Close_Menus()
                COMMANDS.Change_Settler_Outfit2(ref_actor)
            elseIf idx_option == 3
                FUNCS.Close_Menus()
                COMMANDS.Change_Thrall_Outfit2(ref_actor)
            elseIf idx_option == 4
                FUNCS.Close_Menus()
                COMMANDS.Change_Follower_Outfit2(ref_actor)
            elseIf idx_option == 5
                FUNCS.Close_Menus()
                COMMANDS.Change_Immobile_Outfit2(ref_actor)
            elseIf idx_option == 6
                FUNCS.Close_Menus()
                COMMANDS.Change_Vanilla_Outfit2(ref_actor)
            elseIf idx_option == 7
                FUNCS.Close_Menus()
                COMMANDS.Change_Default_Outfit2(ref_actor)
            endIf
        else
            if idx_option == 0
                FUNCS.Close_Menus()
                COMMANDS.Change_Current_Outfit2(ref_actor)
            elseIf idx_option == 1
                FUNCS.Close_Menus()
                COMMANDS.Change_Member_Outfit2(ref_actor)
            elseIf idx_option == 2
                FUNCS.Close_Menus()
                COMMANDS.Change_Settler_Outfit2(ref_actor)
            elseIf idx_option == 3
                FUNCS.Close_Menus()
                COMMANDS.Change_Follower_Outfit2(ref_actor)
            elseIf idx_option == 4
                FUNCS.Close_Menus()
                COMMANDS.Change_Immobile_Outfit2(ref_actor)
            elseIf idx_option == 5
                FUNCS.Close_Menus()
                COMMANDS.Change_Vanilla_Outfit2(ref_actor)
            elseIf idx_option == 6
                FUNCS.Close_Menus()
                COMMANDS.Change_Default_Outfit2(ref_actor)
            endIf
        endIf
    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if !p_ref_member
        return
    endIf

    if id_option == p_option_rename
        if str_input != ""
            p_ref_member.Rename(str_input)
            MCM.Reset_Page()
        endIf
    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if !p_ref_member
        return
    endIf
    
    string str_name = p_ref_member.Name()

    if false

    elseIf id_option == p_option_rename
        MCM.SetInfoText("Rename this member.")
    elseIf id_option == p_option_back
        MCM.SetInfoText("Go back to Members")
    elseIf id_option == p_option_prev
        MCM.SetInfoText("Go to the Previous Member")
    elseIf id_option == p_option_next
        MCM.SetInfoText("Go to the Next Member")

    elseIf id_option == p_option_summon
        MCM.SetInfoText("Summon this member to you.")
    elseIf id_option == p_option_goto
        MCM.SetInfoText("Goto this member.")
    elseIf id_option == p_option_pack
        MCM.SetInfoText("Pack items in this member's inventory.")
    elseIf id_option == p_option_stash
        MCM.SetInfoText("Stash all of the items in the member's pack, into community chests.")
    elseIf id_option == p_option_outfit
        MCM.SetInfoText("Choose what this npc will wear in one of their outfits.")

    elseIf id_option == p_option_settle
        MCM.SetInfoText("Settle " + str_name)
    elseIf id_option == p_option_resettle
        MCM.SetInfoText("Resettle " + str_name)
    elseIf id_option == p_option_unsettle
        MCM.SetInfoText("Unsettle " + str_name)

    elseIf id_option == p_option_immobilize
        MCM.SetInfoText("Immobilize " + str_name)
    elseIf id_option == p_option_mobilize
        MCM.SetInfoText("Mobilize " + str_name)

    elseIf id_option == p_option_paralyze
        MCM.SetInfoText("Paralyze " + str_name)
    elseIf id_option == p_option_unparalyze
        MCM.SetInfoText("Unparalyze " + str_name)

    elseIf id_option == p_option_follow
        MCM.SetInfoText("Have " + str_name + " follow you.")
    elseIf id_option == p_option_unfollow
        MCM.SetInfoText("Have " + str_name + " stop following you.")
    
    elseIf id_option == p_option_sneak
        MCM.SetInfoText("Have " + str_name + " sneak.")
    elseIf id_option == p_option_unsneak
        MCM.SetInfoText("Have " + str_name + " stop sneaking.")

    elseIf id_option == p_option_resurrect
        MCM.SetInfoText("Resurrect this dead member.")

    elseIf id_option == p_option_rating
        MCM.SetInfoText("Rate this member. Causes them to sort higher, and can be used in the filter.")
    elseIf id_option == p_option_style
        MCM.SetInfoText("Change the fighting style of this member.")
    elseIf id_option == p_option_vitalize
        MCM.SetInfoText("Change how this member lives or dies.")

    elseIf id_option == p_option_clone
        MCM.SetInfoText("Clone this member.")
    elseIf id_option == p_option_unclone
        MCM.SetInfoText("Unclone and unmember this member.")
    elseIf id_option == p_option_unmember
        MCM.SetInfoText("Unmember this member.")

    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Default(int id_option)
endFunction
