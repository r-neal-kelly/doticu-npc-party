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
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return doticu_npcp.Members()
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return doticu_npcp.Followers()
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
int property FLAG_DISABLE hidden
    int function Get()
        return MCM.FLAG_DISABLE
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

function f_View_Members_Member(doticu_npcp_member ref_member)
    p_code_view = doticu_npcp_codes.VIEW_MEMBERS_MEMBER()

    p_ref_member = ref_member
endFunction

function f_View_Filter_Members_Member(doticu_npcp_member ref_member)
    p_code_view = doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()

    p_ref_member = ref_member
endFunction

function f_View_Followers_Member(doticu_npcp_member ref_member)
    p_code_view = doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()

    p_ref_member = ref_member
endFunction

function f_View_Mannequins_Member(doticu_npcp_member ref_member)
    p_code_view = doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()

    p_ref_member = ref_member
endFunction

function f_On_Option_Select(int id_option)
    if !p_ref_member
        return
    endIf

    Actor ref_actor = p_ref_member.Actor()

    if false

    elseIf id_option == p_option_back
        f_Disable(id_option, DO_UPDATE)
        p_Go_Back()
    elseIf id_option == p_option_prev
        f_Disable(id_option, DO_UPDATE)
        if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
            MCM.MCM_MEMBERS.f_Request_Prev_Member()
            MCM.ForcePageReset()
        elseIf p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
            MCM.MCM_FOLLOWERS.f_Request_Prev_Member()
            MCM.ForcePageReset()
        endIf
    elseIf id_option == p_option_next
        f_Disable(id_option, DO_UPDATE)
        if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER() || p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
            MCM.MCM_MEMBERS.f_Request_Next_Member()
            MCM.ForcePageReset()
        elseIf p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
            MCM.MCM_FOLLOWERS.f_Request_Next_Member()
            MCM.ForcePageReset()
        endIf

    elseIf id_option == p_option_summon
        f_Disable(id_option, DO_UPDATE)
        COMMANDS.Summon_Sync(ref_actor)
        p_Update_Commands()
    elseIf id_option == p_option_goto
        f_Disable(id_option, DO_UPDATE)
        FUNCS.Close_Menus()
        COMMANDS.Goto_Sync(ref_actor)
    elseIf id_option == p_option_pack
        f_Disable(id_option, DO_UPDATE)
        FUNCS.Close_Menus()
        COMMANDS.Pack_Sync(ref_actor, false)
    elseIf id_option == p_option_stash
        f_Disable(id_option, DO_UPDATE)
        p_ref_member.Stash()
        p_Update_Commands()

    elseIf id_option == p_option_settle
        f_Disable(p_option_settle, DO_UPDATE)
        COMMANDS.Settle(ref_actor, false)
        p_Update_Commands()
    elseIf id_option == p_option_resettle
        f_Disable(p_option_resettle, DO_UPDATE)
        COMMANDS.Resettle(ref_actor, false)
        p_Update_Commands()
    elseIf id_option == p_option_unsettle
        f_Disable(p_option_unsettle, DO_UPDATE)
        COMMANDS.Unsettle(ref_actor, false)
        p_Update_Commands()

    elseIf id_option == p_option_immobilize
        f_Disable(p_option_immobilize, DO_UPDATE)
        COMMANDS.Immobilize(ref_actor, false)
        p_Update_Commands()
    elseIf id_option == p_option_mobilize
        f_Disable(p_option_mobilize, DO_UPDATE)
        COMMANDS.Mobilize(ref_actor, false)
        p_Update_Commands()

    elseIf id_option == p_option_paralyze
        f_Disable(p_option_paralyze, DO_UPDATE)
        COMMANDS.Paralyze(ref_actor, false)
        p_Update_Commands()
    elseIf id_option == p_option_unparalyze
        f_Disable(p_option_unparalyze, DO_UPDATE)
        COMMANDS.Unparalyze(ref_actor, false)
        p_Update_Commands()

    elseIf id_option == p_option_follow
        f_Disable(p_option_follow, DO_UPDATE)
        COMMANDS.Follow_Sync(ref_actor, false)
        p_Update_Commands()
    elseIf id_option == p_option_unfollow
        f_Disable(p_option_unfollow, DO_UPDATE)
        COMMANDS.Unfollow_Sync(ref_actor, false)
        if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
            p_Go_Back()
        else
            p_Update_Commands()
        endIf

    elseIf id_option == p_option_sneak
        f_Disable(p_option_sneak, DO_UPDATE)
        COMMANDS.Sneak_Sync(ref_actor, false)
        p_Update_Commands()
    elseIf id_option == p_option_unsneak
        f_Disable(p_option_unsneak, DO_UPDATE)
        COMMANDS.Unsneak_Sync(ref_actor, false)
        p_Update_Commands()

    elseIf id_option == p_option_rating
        int int_rating = p_ref_member.Rating()
        if false

        elseIf int_rating == 0
            p_ref_member.Rate(1)
            p_Update_Commands()
        elseIf int_rating == 1
            p_ref_member.Rate(2)
            p_Update_Commands()
        elseIf int_rating == 2
            p_ref_member.Rate(3)
            p_Update_Commands()
        elseIf int_rating == 3
            p_ref_member.Rate(4)
            p_Update_Commands()
        elseIf int_rating == 4
            p_ref_member.Rate(5)
            p_Update_Commands()
        elseIf int_rating == 5
            p_ref_member.Rate(0)
            p_Update_Commands()

        endIf

    elseIf id_option == p_option_style
        int code_style = p_ref_member.Style()
        if code_style == doticu_npcp_codes.STYLE_DEFAULT()
            COMMANDS.Stylize_Warrior(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        elseIf code_style == doticu_npcp_codes.STYLE_WARRIOR()
            COMMANDS.Stylize_Mage(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        elseIf code_style == doticu_npcp_codes.STYLE_MAGE()
            COMMANDS.Stylize_Archer(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        elseIf code_style == doticu_npcp_codes.STYLE_ARCHER()
            COMMANDS.Stylize_Coward(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        elseIf code_style == doticu_npcp_codes.STYLE_COWARD()
            COMMANDS.Stylize_Default(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        endIf

    elseIf id_option == p_option_vitalize
        int code_vitality = p_ref_member.Vitality()
        if code_vitality == doticu_npcp_codes.VITALITY_MORTAL()
            COMMANDS.Vitalize_Protected(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        elseIf code_vitality == doticu_npcp_codes.VITALITY_PROTECTED()
            COMMANDS.Vitalize_Essential(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        elseIf code_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
            COMMANDS.Vitalize_Invulnerable(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        elseIf code_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
            COMMANDS.Vitalize_Mortal(ref_actor, false)
            ;p_Update_Commands()
            ;p_Update_Statistics()
            MCM.ForcePageReset()
        endIf
    
    elseIf id_option == p_option_resurrect
        f_Disable(p_option_resurrect, DO_UPDATE)
        COMMANDS.Resurrect_Sync(ref_actor, false)
        ;p_Update_Commands()
        ;p_Update_Statistics()
        MCM.ForcePageReset()

    elseIf id_option == p_option_clone
        f_Disable(p_option_clone, DO_UPDATE)
        COMMANDS.Clone_Async(ref_actor)
        p_Update_Commands()
    elseIf id_option == p_option_unclone
        f_Disable(p_option_unclone, DO_UPDATE)
        COMMANDS.Unclone_Sync(ref_actor)
        p_Go_Back()
    elseIf id_option == p_option_unmember
        f_Disable(p_option_unmember, DO_UPDATE)
        COMMANDS.Unmember_Sync(ref_actor)
        p_Go_Back()

    endIf
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
                COMMANDS.Outfit_Current_Sync(ref_actor, false)
            elseIf idx_option == 1
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Member_Sync(ref_actor, false)
            elseIf idx_option == 2
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Settler_Sync(ref_actor, false)
            elseIf idx_option == 3
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Thrall_Sync(ref_actor, false)
            elseIf idx_option == 4
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Follower_Sync(ref_actor, false)
            elseIf idx_option == 5
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Immobile_Sync(ref_actor, false)
            elseIf idx_option == 6
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Vanilla_Sync(ref_actor, false)
            elseIf idx_option == 7
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Default_Sync(ref_actor, false)
            endIf
        else
            if idx_option == 0
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Current_Sync(ref_actor, false)
            elseIf idx_option == 1
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Member_Sync(ref_actor, false)
            elseIf idx_option == 2
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Settler_Sync(ref_actor, false)
            elseIf idx_option == 3
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Follower_Sync(ref_actor, false)
            elseIf idx_option == 4
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Immobile_Sync(ref_actor, false)
            elseIf idx_option == 5
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Vanilla_Sync(ref_actor, false)
            elseIf idx_option == 6
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Default_Sync(ref_actor, false)
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
            MCM.ForcePageReset()
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

; Private Methods
function p_Go_Back()
    if p_code_view == doticu_npcp_codes.VIEW_MEMBERS_MEMBER()
        MCM.MCM_MEMBERS.f_Review_Members()
        MCM.ForcePageReset()
    elseIf p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS_MEMBER()
        MCM.MCM_MEMBERS.f_Review_Filter_Members()
        MCM.ForcePageReset()
    elseIf p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        MCM.MCM_FOLLOWERS.f_Review_Followers()
        MCM.ForcePageReset()
    elseIf p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        MCM.MCM_MANNEQUINS.f_Review_Mannequins()
        MCM.ForcePageReset()
    endIf
endFunction
