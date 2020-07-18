;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_member extends Quest

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
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
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
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
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
doticu_npcp_data    p_DATA                      =  none

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

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

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
    p_code_view = CODES.VIEW_MEMBERS_MEMBER

    p_ref_member = ref_member
endFunction

function f_View_Filter_Members_Member(doticu_npcp_member ref_member)
    p_code_view = CODES.VIEW_FILTER_MEMBERS_MEMBER

    p_ref_member = ref_member
endFunction

function f_View_Followers_Member(doticu_npcp_member ref_member)
    p_code_view = CODES.VIEW_FOLLOWERS_MEMBER

    p_ref_member = ref_member
endFunction

function f_View_Mannequins_Member(doticu_npcp_member ref_member)
    p_code_view = CODES.VIEW_MANNEQUINS_MEMBER

    p_ref_member = ref_member
endFunction

function f_Build_Page()
    if !p_ref_member
        return
    endIf
    
    string str_name = p_ref_member.Name()

    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    if p_code_view == CODES.VIEW_MEMBERS_MEMBER
        MCM.SetTitleText("Member: " + str_name)
    elseIf p_code_view == CODES.VIEW_FOLLOWERS_MEMBER
        MCM.SetTitleText("Follower: " + str_name)
    elseIf p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        MCM.SetTitleText("Filtered Member: " + str_name)
    elseIf p_code_view == CODES.VIEW_MANNEQUINS_MEMBER
        MCM.SetTitleText("Mannequin: " + str_name)
    endIf

    p_option_rename = MCM.AddInputOption(str_name + " ", " Rename ")
    p_option_back = MCM.AddTextOption("                            Go Back", "")

    if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        if MEMBERS.Get_Count() > 1
            p_option_prev = MCM.AddTextOption("                      Previous Member", "")
            p_option_next = MCM.AddTextOption("                        Next Member", "")
        else
            p_option_prev = MCM.AddTextOption("                      Previous Member", "", FLAG_DISABLE)
            p_option_next = MCM.AddTextOption("                        Next Member", "", FLAG_DISABLE)
        endIf
    elseIf p_code_view == CODES.VIEW_FOLLOWERS_MEMBER
        if FOLLOWERS.Count_Filled() > 1
            p_option_prev = MCM.AddTextOption("                      Previous Follower", "")
            p_option_next = MCM.AddTextOption("                        Next Follower", "")
        else
            p_option_prev = MCM.AddTextOption("                      Previous Follower", "", FLAG_DISABLE)
            p_option_next = MCM.AddTextOption("                        Next Follower", "", FLAG_DISABLE)
        endIf
    endIf

    MCM.SetCursorPosition(4)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
    MCM.AddHeaderOption("Commands: ")
    p_Build_Commands()

    MCM.SetCursorPosition(5)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
    MCM.AddHeaderOption("Statistics: ")
    p_Build_Statistics()
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
        if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
            MCM.MCM_MEMBERS.f_Request_Prev_Member()
            MCM.ForcePageReset()
        elseIf p_code_view == CODES.VIEW_FOLLOWERS_MEMBER
            MCM.MCM_FOLLOWERS.f_Request_Prev_Member()
            MCM.ForcePageReset()
        endIf
    elseIf id_option == p_option_next
        f_Disable(id_option, DO_UPDATE)
        if p_code_view == CODES.VIEW_MEMBERS_MEMBER || p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
            MCM.MCM_MEMBERS.f_Request_Next_Member()
            MCM.ForcePageReset()
        elseIf p_code_view == CODES.VIEW_FOLLOWERS_MEMBER
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
        if p_code_view == CODES.VIEW_FOLLOWERS_MEMBER
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
        int int_rating = p_ref_member.Get_Rating()
        if false

        elseIf int_rating == 0
            p_ref_member.Set_Rating(1)
            p_Update_Commands()
        elseIf int_rating == 1
            p_ref_member.Set_Rating(2)
            p_Update_Commands()
        elseIf int_rating == 2
            p_ref_member.Set_Rating(3)
            p_Update_Commands()
        elseIf int_rating == 3
            p_ref_member.Set_Rating(4)
            p_Update_Commands()
        elseIf int_rating == 4
            p_ref_member.Set_Rating(5)
            p_Update_Commands()
        elseIf int_rating == 5
            p_ref_member.Set_Rating(0)
            p_Update_Commands()

        endIf

    elseIf id_option == p_option_style
        int code_style = p_ref_member.Style()
        if code_style == CODES.IS_DEFAULT
            COMMANDS.Stylize_Warrior(ref_actor, false)
            p_Update_Commands()
        elseIf code_style == CODES.IS_WARRIOR
            COMMANDS.Stylize_Mage(ref_actor, false)
            p_Update_Commands()
        elseIf code_style == CODES.IS_MAGE
            COMMANDS.Stylize_Archer(ref_actor, false)
            p_Update_Commands()
        elseIf code_style == CODES.IS_ARCHER
            COMMANDS.Stylize_Coward(ref_actor, false)
            p_Update_Commands()
        elseIf code_style == CODES.IS_COWARD
            COMMANDS.Stylize_Default(ref_actor, false)
            p_Update_Commands()
        endIf

    elseIf id_option == p_option_vitalize
        int code_vitality = p_ref_member.Vitality()
        if code_vitality == CODES.IS_MORTAL
            COMMANDS.Vitalize_Protected(ref_actor, false)
            p_Update_Commands()
        elseIf code_vitality == CODES.IS_PROTECTED
            COMMANDS.Vitalize_Essential(ref_actor, false)
            p_Update_Commands()
        elseIf code_vitality == CODES.IS_ESSENTIAL
            COMMANDS.Vitalize_Invulnerable(ref_actor, false)
            p_Update_Commands()
        elseIf code_vitality == CODES.IS_INVULNERABLE
            COMMANDS.Vitalize_Mortal(ref_actor, false)
            p_Update_Commands()
        endIf
    
    elseIf id_option == p_option_resurrect
        f_Disable(p_option_resurrect, DO_UPDATE)
        COMMANDS.Resurrect_Sync(ref_actor, false)
        p_Update_Commands()
        p_Update_Statistics()

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
        if ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
            string[] arr_options = Utility.CreateStringArray(8, "")

            arr_options[0] = CONSTS.STR_MCM_CURRENT
            arr_options[1] = CONSTS.STR_MCM_MEMBER
            arr_options[2] = CONSTS.STR_MCM_SETTLER
            arr_options[3] = CONSTS.STR_MCM_THRALL
            arr_options[4] = CONSTS.STR_MCM_FOLLOWER
            arr_options[5] = CONSTS.STR_MCM_IMMOBILE
            arr_options[6] = CONSTS.STR_MCM_VANILLA
            arr_options[7] = CONSTS.STR_MCM_DEFAULT

            MCM.SetMenuDialogOptions(arr_options)
        else
            string[] arr_options = Utility.CreateStringArray(7, "")

            arr_options[0] = CONSTS.STR_MCM_CURRENT
            arr_options[1] = CONSTS.STR_MCM_MEMBER
            arr_options[2] = CONSTS.STR_MCM_SETTLER
            arr_options[3] = CONSTS.STR_MCM_FOLLOWER
            arr_options[4] = CONSTS.STR_MCM_IMMOBILE
            arr_options[5] = CONSTS.STR_MCM_VANILLA
            arr_options[6] = CONSTS.STR_MCM_DEFAULT

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
        if ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
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
function p_Build_Commands()
    if !p_ref_member
        return
    endIf

    ; unblessedly, we can't just call an update in the PageReset function,
    ; the lib in not capable, so we have to type out logic here too

    p_option_summon = MCM.AddTextOption(CONSTS.STR_MCM_SUMMON, "", FLAG_ENABLE)
    p_option_goto = MCM.AddTextOption(CONSTS.STR_MCM_GOTO, "", FLAG_ENABLE)
    p_option_pack = MCM.AddTextOption(CONSTS.STR_MCM_PACK, "", FLAG_ENABLE)
    p_option_stash = MCM.AddTextOption(" Stash ", "", FLAG_ENABLE)
    p_option_outfit = MCM.AddMenuOption(CONSTS.STR_MCM_OUTFIT, "", FLAG_ENABLE)

    if p_ref_member.Is_Settler()
        p_option_settle = MCM.AddTextOption(CONSTS.STR_MCM_SETTLE, "", FLAG_DISABLE)
        p_option_resettle = MCM.AddTextOption(CONSTS.STR_MCM_RESETTLE, "", FLAG_ENABLE)
        p_option_unsettle = MCM.AddTextOption(CONSTS.STR_MCM_UNSETTLE, "", FLAG_ENABLE)
    else
        p_option_settle = MCM.AddTextOption(CONSTS.STR_MCM_SETTLE, "", FLAG_ENABLE)
        p_option_resettle = MCM.AddTextOption(CONSTS.STR_MCM_RESETTLE, "", FLAG_DISABLE)
        p_option_unsettle = MCM.AddTextOption(CONSTS.STR_MCM_UNSETTLE, "", FLAG_DISABLE)
    endif

    if p_ref_member.Is_Immobile()
        p_option_immobilize = MCM.AddTextOption(CONSTS.STR_MCM_IMMOBILIZE, "", FLAG_DISABLE)
        p_option_mobilize = MCM.AddTextOption(CONSTS.STR_MCM_MOBILIZE, "", FLAG_ENABLE)
    else
        p_option_immobilize = MCM.AddTextOption(CONSTS.STR_MCM_IMMOBILIZE, "", FLAG_ENABLE)
        p_option_mobilize = MCM.AddTextOption(CONSTS.STR_MCM_MOBILIZE, "", FLAG_DISABLE)
    endif

    if p_ref_member.Is_Paralyzed()
        p_option_paralyze = MCM.AddTextOption(CONSTS.STR_MCM_PARALYZE, "", FLAG_DISABLE)
        p_option_unparalyze = MCM.AddTextOption(CONSTS.STR_MCM_UNPARALYZE, "", FLAG_ENABLE)
    else
        p_option_paralyze = MCM.AddTextOption(CONSTS.STR_MCM_PARALYZE, "", FLAG_ENABLE)
        p_option_unparalyze = MCM.AddTextOption(CONSTS.STR_MCM_UNPARALYZE, "", FLAG_DISABLE)
    endif

    if p_ref_member.Is_Follower()
        p_option_follow = MCM.AddTextOption(CONSTS.STR_MCM_FOLLOW, "", FLAG_DISABLE)
        p_option_unfollow = MCM.AddTextOption(CONSTS.STR_MCM_UNFOLLOW, "", FLAG_ENABLE)

        if p_ref_member.Is_Sneak()
            p_option_sneak = MCM.AddTextOption(CONSTS.STR_MCM_SNEAK, "", FLAG_DISABLE)
            p_option_unsneak = MCM.AddTextOption(CONSTS.STR_MCM_UNSNEAK, "", FLAG_ENABLE)
        else
            p_option_sneak = MCM.AddTextOption(CONSTS.STR_MCM_SNEAK, "", FLAG_ENABLE)
            p_option_unsneak = MCM.AddTextOption(CONSTS.STR_MCM_UNSNEAK, "", FLAG_DISABLE)
        endIf
    else
        p_option_follow = MCM.AddTextOption(CONSTS.STR_MCM_FOLLOW, "", FLAG_ENABLE)
        p_option_unfollow = MCM.AddTextOption(CONSTS.STR_MCM_UNFOLLOW, "", FLAG_DISABLE)

        p_option_sneak = MCM.AddTextOption(CONSTS.STR_MCM_SNEAK, "", FLAG_DISABLE)
        p_option_unsneak = MCM.AddTextOption(CONSTS.STR_MCM_UNSNEAK, "", FLAG_DISABLE)
    endif

    p_option_rating = MCM.AddTextOption(CONSTS.STR_MCM_RATING, p_ref_member.Get_Rating_Stars())

    int code_style = p_ref_member.Style()
    if code_style == CODES.IS_DEFAULT
        p_option_style = MCM.AddTextOption(CONSTS.STR_MCM_STYLE, CONSTS.STR_MCM_DEFAULT)
    elseIf code_style == CODES.IS_WARRIOR
        p_option_style = MCM.AddTextOption(CONSTS.STR_MCM_STYLE, CONSTS.STR_MCM_WARRIOR)
    elseIf code_style == CODES.IS_MAGE
        p_option_style = MCM.AddTextOption(CONSTS.STR_MCM_STYLE, CONSTS.STR_MCM_MAGE)
    elseIf code_style == CODES.IS_ARCHER
        p_option_style = MCM.AddTextOption(CONSTS.STR_MCM_STYLE, CONSTS.STR_MCM_ARCHER)
    elseIf code_style == CODES.IS_COWARD
        p_option_style = MCM.AddTextOption(CONSTS.STR_MCM_STYLE, CONSTS.STR_MCM_COWARD)
    endIf

    int code_vitality = p_ref_member.Vitality()
    if code_vitality == CODES.IS_MORTAL
        p_option_vitalize = MCM.AddTextOption(CONSTS.STR_MCM_VITALITY, CONSTS.STR_MCM_MORTAL)
    elseIf code_vitality == CODES.IS_PROTECTED
        p_option_vitalize = MCM.AddTextOption(CONSTS.STR_MCM_VITALITY, CONSTS.STR_MCM_PROTECTED)
    elseIf code_vitality == CODES.IS_ESSENTIAL
        p_option_vitalize = MCM.AddTextOption(CONSTS.STR_MCM_VITALITY, CONSTS.STR_MCM_ESSENTIAL)
    elseIf code_vitality == CODES.IS_INVULNERABLE
        p_option_vitalize = MCM.AddTextOption(CONSTS.STR_MCM_VITALITY, CONSTS.STR_MCM_INVULNERABLE)
    endIf

    if p_ref_member.Is_Dead()
        p_option_resurrect = MCM.AddTextOption(CONSTS.STR_MCM_RESURRECT, "", FLAG_ENABLE)
    else
        p_option_resurrect = MCM.AddTextOption(CONSTS.STR_MCM_RESURRECT, "", FLAG_DISABLE)
    endIf

    p_option_clone = MCM.AddTextOption(CONSTS.STR_MCM_CLONE, "", FLAG_ENABLE)
    if p_ref_member.Is_Clone()
        p_option_unclone = MCM.AddTextOption(CONSTS.STR_MCM_UNCLONE, "", FLAG_ENABLE)
    else
        p_option_unclone = MCM.AddTextOption(CONSTS.STR_MCM_UNCLONE, "", FLAG_DISABLE)
    endIf

    if MEMBERS.Should_Unclone_Member(p_ref_member)
        p_option_unmember = MCM.AddTextOption(CONSTS.STR_MCM_UNMEMBER, "", FLAG_DISABLE)
    else
        p_option_unmember = MCM.AddTextOption(CONSTS.STR_MCM_UNMEMBER, "", FLAG_ENABLE)
    endIf
endFunction

function p_Update_Commands()
    if !p_ref_member
        return
    endIf

    f_Enable(p_option_summon, DONT_UPDATE)
    f_Enable(p_option_goto, DONT_UPDATE)
    f_Enable(p_option_pack, DONT_UPDATE)
    f_Enable(p_option_stash, DONT_UPDATE)
    f_Enable(p_option_outfit, DONT_UPDATE)

    if p_ref_member.Is_Settler()
        f_Disable(p_option_settle, DONT_UPDATE)
        f_Enable(p_option_resettle, DONT_UPDATE)
        f_Enable(p_option_unsettle, DONT_UPDATE)
    else
        f_Enable(p_option_settle, DONT_UPDATE)
        f_Disable(p_option_resettle, DONT_UPDATE)
        f_Disable(p_option_unsettle, DONT_UPDATE)
    endif

    if p_ref_member.Is_Immobile()
        f_Disable(p_option_immobilize, DONT_UPDATE)
        f_Enable(p_option_mobilize, DONT_UPDATE)
    else
        f_Enable(p_option_immobilize, DONT_UPDATE)
        f_Disable(p_option_mobilize, DONT_UPDATE)
    endif

    if p_ref_member.Is_Paralyzed()
        f_Disable(p_option_paralyze, DONT_UPDATE)
        f_Enable(p_option_unparalyze, DONT_UPDATE)
    else
        f_Enable(p_option_paralyze, DONT_UPDATE)
        f_Disable(p_option_unparalyze, DONT_UPDATE)
    endif

    if p_ref_member.Is_Follower()
        f_Disable(p_option_follow, DONT_UPDATE)
        f_Enable(p_option_unfollow, DONT_UPDATE)

        if p_ref_member.Is_Sneak()
            f_Disable(p_option_sneak, DONT_UPDATE)
            f_Enable(p_option_unsneak, DONT_UPDATE)
        else
            f_Enable(p_option_sneak, DONT_UPDATE)
            f_Disable(p_option_unsneak, DONT_UPDATE)
        endIf
    else
        f_Enable(p_option_follow, DONT_UPDATE)
        f_Disable(p_option_unfollow, DONT_UPDATE)

        f_Disable(p_option_sneak, DONT_UPDATE)
        f_Disable(p_option_unsneak, DONT_UPDATE)
    endif

    MCM.SetTextOptionValue(p_option_rating, p_ref_member.Get_Rating_Stars(), DONT_UPDATE)

    int code_style = p_ref_member.Style()
    if code_style == CODES.IS_DEFAULT
        MCM.SetTextOptionValue(p_option_style, CONSTS.STR_MCM_DEFAULT, DONT_UPDATE)
    elseIf code_style == CODES.IS_WARRIOR
        MCM.SetTextOptionValue(p_option_style, CONSTS.STR_MCM_WARRIOR, DONT_UPDATE)
    elseIf code_style == CODES.IS_MAGE
        MCM.SetTextOptionValue(p_option_style, CONSTS.STR_MCM_MAGE, DONT_UPDATE)
    elseIf code_style == CODES.IS_ARCHER
        MCM.SetTextOptionValue(p_option_style, CONSTS.STR_MCM_ARCHER, DONT_UPDATE)
    elseIf code_style == CODES.IS_COWARD
        MCM.SetTextOptionValue(p_option_style, CONSTS.STR_MCM_COWARD, DONT_UPDATE)
    endIf

    int code_vitality = p_ref_member.Vitality()
    if code_vitality == CODES.IS_MORTAL
        MCM.SetTextOptionValue(p_option_vitalize, CONSTS.STR_MCM_MORTAL, DONT_UPDATE)
    elseIf code_vitality == CODES.IS_PROTECTED
        MCM.SetTextOptionValue(p_option_vitalize, CONSTS.STR_MCM_PROTECTED, DONT_UPDATE)
    elseIf code_vitality == CODES.IS_ESSENTIAL
        MCM.SetTextOptionValue(p_option_vitalize, CONSTS.STR_MCM_ESSENTIAL, DONT_UPDATE)
    elseIf code_vitality == CODES.IS_INVULNERABLE
        MCM.SetTextOptionValue(p_option_vitalize, CONSTS.STR_MCM_INVULNERABLE, DONT_UPDATE)
    endIf

    if p_ref_member.Is_Dead()
        f_Enable(p_option_resurrect, DONT_UPDATE)
    else
        f_Disable(p_option_resurrect, DONT_UPDATE)
    endIf

    f_Enable(p_option_clone, DONT_UPDATE)
    if p_ref_member.Is_Clone()
        f_Enable(p_option_unclone, DONT_UPDATE)
    else
        f_Disable(p_option_unclone, DONT_UPDATE)
    endIf

    if MEMBERS.Should_Unclone_Member(p_ref_member)
        f_Disable(p_option_unmember, DONT_UPDATE)
    else
        f_Enable(p_option_unmember, DONT_UPDATE)
    endIf

    f_Enable(p_option_rename, DO_UPDATE)
endFunction

function p_Build_Statistics()
    if !p_ref_member
        return
    endIf

    Actor ref_actor = p_ref_member.Actor()

    p_option_health             = MCM.AddTextOption(CONSTS.STR_MCM_HEALTH,      ref_actor.GetActorValue(CONSTS.STR_HEALTH)      as int)
    p_option_magicka            = MCM.AddTextOption(CONSTS.STR_MCM_MAGICKA,     ref_actor.GetActorValue(CONSTS.STR_MAGICKA)     as int)
    p_option_stamina            = MCM.AddTextOption(CONSTS.STR_MCM_STAMINA,     ref_actor.GetActorValue(CONSTS.STR_STAMINA)     as int)

    p_option_skill_one_handed   = MCM.AddTextOption(CONSTS.STR_MCM_ONE_HANDED,  ref_actor.GetActorValue(CONSTS.STR_ONE_HANDED)  as int)
    p_option_skill_two_handed   = MCM.AddTextOption(CONSTS.STR_MCM_TWO_HANDED,  ref_actor.GetActorValue(CONSTS.STR_TWO_HANDED)  as int)
    p_option_skill_block        = MCM.AddTextOption(CONSTS.STR_MCM_BLOCK,       ref_actor.GetActorValue(CONSTS.STR_BLOCK)       as int)
    p_option_skill_heavy_armor  = MCM.AddTextOption(CONSTS.STR_MCM_HEAVY_ARMOR, ref_actor.GetActorValue(CONSTS.STR_HEAVY_ARMOR) as int)
    p_option_skill_light_armor  = MCM.AddTextOption(CONSTS.STR_MCM_LIGHT_ARMOR, ref_actor.GetActorValue(CONSTS.STR_LIGHT_ARMOR) as int)
    p_option_skill_smithing     = MCM.AddTextOption(CONSTS.STR_MCM_SMITHING,    ref_actor.GetActorValue(CONSTS.STR_SMITHING)    as int)

    p_option_skill_destruction  = MCM.AddTextOption(CONSTS.STR_MCM_DESTRUCTION, ref_actor.GetActorValue(CONSTS.STR_DESTRUCTION) as int)
    p_option_skill_restoration  = MCM.AddTextOption(CONSTS.STR_MCM_RESTORATION, ref_actor.GetActorValue(CONSTS.STR_RESTORATION) as int)
    p_option_skill_conjuration  = MCM.AddTextOption(CONSTS.STR_MCM_CONJURATION, ref_actor.GetActorValue(CONSTS.STR_CONJURATION) as int)
    p_option_skill_alteration   = MCM.AddTextOption(CONSTS.STR_MCM_ALTERATION,  ref_actor.GetActorValue(CONSTS.STR_ALTERATION)  as int)
    p_option_skill_illusion     = MCM.AddTextOption(CONSTS.STR_MCM_ILLUSION,    ref_actor.GetActorValue(CONSTS.STR_ILLUSION)    as int)
    p_option_skill_enchanting   = MCM.AddTextOption(CONSTS.STR_MCM_ENCHANTING,  ref_actor.GetActorValue(CONSTS.STR_ENCHANTING)  as int)

    p_option_skill_marksman     = MCM.AddTextOption(CONSTS.STR_MCM_MARKSMAN,    ref_actor.GetActorValue(CONSTS.STR_MARKSMAN)    as int)
    p_option_skill_sneak        = MCM.AddTextOption(CONSTS.STR_MCM_SNEAK,       ref_actor.GetActorValue(CONSTS.STR_SNEAK)       as int)
    p_option_skill_alchemy      = MCM.AddTextOption(CONSTS.STR_MCM_ALCHEMY,     ref_actor.GetActorValue(CONSTS.STR_ALCHEMY)     as int)
    p_option_skill_lockpicking  = MCM.AddTextOption(CONSTS.STR_MCM_LOCKPICKING, ref_actor.GetActorValue(CONSTS.STR_LOCKPICKING) as int)
    p_option_skill_pickpocket   = MCM.AddTextOption(CONSTS.STR_MCM_PICKPOCKET,  ref_actor.GetActorValue(CONSTS.STR_PICKPOCKET)  as int)
    p_option_skill_speechcraft  = MCM.AddTextOption(CONSTS.STR_MCM_SPEECHCRAFT, ref_actor.GetActorValue(CONSTS.STR_SPEECHCRAFT) as int)

    p_option_race               = MCM.AddTextOption(CONSTS.STR_MCM_RACE,        ref_actor.GetRace().GetName())
endFunction

function p_Update_Statistics()
    if !p_ref_member
        return
    endIf

    Actor ref_actor = p_ref_member.Actor()

    MCM.SetTextOptionValue(p_option_health,             ref_actor.GetActorValue(CONSTS.STR_HEALTH)      as int,  true)
    MCM.SetTextOptionValue(p_option_magicka,            ref_actor.GetActorValue(CONSTS.STR_MAGICKA)     as int,  true)
    MCM.SetTextOptionValue(p_option_stamina,            ref_actor.GetActorValue(CONSTS.STR_STAMINA)     as int,  true)

    MCM.SetTextOptionValue(p_option_skill_one_handed,   ref_actor.GetActorValue(CONSTS.STR_ONE_HANDED)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_two_handed,   ref_actor.GetActorValue(CONSTS.STR_TWO_HANDED)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_block,        ref_actor.GetActorValue(CONSTS.STR_BLOCK)       as int,  true)
    MCM.SetTextOptionValue(p_option_skill_heavy_armor,  ref_actor.GetActorValue(CONSTS.STR_HEAVY_ARMOR) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_light_armor,  ref_actor.GetActorValue(CONSTS.STR_LIGHT_ARMOR) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_smithing,     ref_actor.GetActorValue(CONSTS.STR_SMITHING)    as int,  true)

    MCM.SetTextOptionValue(p_option_skill_destruction,  ref_actor.GetActorValue(CONSTS.STR_DESTRUCTION) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_restoration,  ref_actor.GetActorValue(CONSTS.STR_RESTORATION) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_conjuration,  ref_actor.GetActorValue(CONSTS.STR_CONJURATION) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_alteration,   ref_actor.GetActorValue(CONSTS.STR_ALTERATION)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_illusion,     ref_actor.GetActorValue(CONSTS.STR_ILLUSION)    as int,  true)
    MCM.SetTextOptionValue(p_option_skill_enchanting,   ref_actor.GetActorValue(CONSTS.STR_ENCHANTING)  as int,  true)

    MCM.SetTextOptionValue(p_option_skill_marksman,     ref_actor.GetActorValue(CONSTS.STR_MARKSMAN)    as int,  true)
    MCM.SetTextOptionValue(p_option_skill_sneak,        ref_actor.GetActorValue(CONSTS.STR_SNEAK)       as int,  true)
    MCM.SetTextOptionValue(p_option_skill_alchemy,      ref_actor.GetActorValue(CONSTS.STR_ALCHEMY)     as int,  true)
    MCM.SetTextOptionValue(p_option_skill_lockpicking,  ref_actor.GetActorValue(CONSTS.STR_LOCKPICKING) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_pickpocket,   ref_actor.GetActorValue(CONSTS.STR_PICKPOCKET)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_speechcraft,  ref_actor.GetActorValue(CONSTS.STR_SPEECHCRAFT) as int,  true)

    MCM.SetTextOptionValue(p_option_race,               ref_actor.GetRace().GetName()                         , false)
endFunction

function p_Go_Back()
    if p_code_view == CODES.VIEW_MEMBERS_MEMBER
        MCM.MCM_MEMBERS.f_Review_Members()
        MCM.ForcePageReset()
    elseIf p_code_view == CODES.VIEW_FILTER_MEMBERS_MEMBER
        MCM.MCM_MEMBERS.f_Review_Filter_Members()
        MCM.ForcePageReset()
    elseIf p_code_view == CODES.VIEW_FOLLOWERS_MEMBER
        MCM.MCM_FOLLOWERS.f_Review_Followers()
        MCM.ForcePageReset()
    elseIf p_code_view == CODES.VIEW_MANNEQUINS_MEMBER
        MCM.MCM_MANNEQUINS.f_Review_Mannequins()
        MCM.ForcePageReset()
    endIf
endFunction
