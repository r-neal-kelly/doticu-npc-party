Scriptname doticu_npc_party_script_mcm_followers extends Quest

; Private Constants
doticu_npc_party_script_funcs       p_FUNCS                     = none
doticu_npc_party_script_followers   p_FOLLOWERS                 = none
doticu_npc_Party_script_mcm         p_MCM                       = none

int                                 p_VIEW_FOLLOWERS            =    0
int                                 p_VIEW_FOLLOWER             =    1

int                                 p_HEADERS_PER_PAGE          =    4

int                                 p_COMMANDS_PER_PAGE         =   11
int                                 p_IDX_ALL_SUMMON            =    0
int                                 p_IDX_ALL_SUMMON_MOBILE     =    1
int                                 p_IDX_ALL_SUMMON_IMMOBILE   =    2
int                                 p_IDX_ALL_IMMOBILIZE        =    3
int                                 p_IDX_ALL_MOBILIZE          =    4
int                                 p_IDX_ALL_SNEAK             =    5
int                                 p_IDX_ALL_UNSNEAK           =    6
int                                 p_IDX_ALL_SETTLE            =    7
int                                 p_IDX_ALL_UNSETTLE          =    8
int                                 p_IDX_ALL_UNFOLLOW          =    9
int                                 p_IDX_ALL_UNMEMBER          =   10

int                                 p_COMMANDS_PER_FOLLOWER     =    4; includes the name
int                                 p_IDX_NAME                  =    0
int                                 p_IDX_SUMMON                =    1
int                                 p_IDX_IMMOBILIZE            =    2
int                                 p_IDX_MORE                  =    3

; Private Variables
int                                 p_curr_view                 =    0
Alias[]                             p_arr_aliases               = none
doticu_npc_party_script_follower    p_ref_follower              = none
int                                 p_idx_follower              =   -1
int                                 p_options_offset            =   -1

int                                 p_option_menu               =   -1
int                                 p_option_back               =   -1
int                                 p_option_prev               =   -1
int                                 p_option_next               =   -1
int                                 p_option_access             =   -1
int                                 p_option_rename             =   -1
int                                 p_option_unfollow           =   -1

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_FUNCS = DATA.MODS.FUNCS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
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

; Private Methods
int function p_Get_Idx_Entity(int id_option)
endFunction

int function p_Get_Idx_Command(int id_option, int idx_entity)
endFunction

; Private States
auto state p_STATE_FOLLOWERS
    function f_Build_Page()
        if p_curr_view == p_VIEW_FOLLOWER
            GotoState("p_STATE_FOLLOWER")
            f_Build_Page()
            return
        endIf

        p_MCM.SetCursorPosition(0)
        p_MCM.SetCursorFillMode(p_MCM.LEFT_TO_RIGHT)

        int count_followers = p_FOLLOWERS.Get_Count()
        int max_followers = p_FOLLOWERS.Get_Max()
        if count_followers == 0
            p_MCM.AddHeaderOption("0 / " + max_followers as string + " Followers")
            return
        endIf

        p_options_offset = p_MCM.AddHeaderOption(count_followers as string + " / " + max_followers as string + " Followers")
        p_option_menu = p_MCM.AddMenuOption(" Command All ", "...")
        p_MCM.AddEmptyOption()
        p_MCM.AddEmptyOption()

        p_MCM.SetCursorFillMode(p_MCM.TOP_TO_BOTTOM)

        int idx = 0
        int cursor = p_HEADERS_PER_PAGE
        p_arr_aliases = p_FOLLOWERS.Get_Aliases_Sorted()
        while idx < p_arr_aliases.length
            doticu_npc_party_script_follower ref_follower = p_arr_aliases[idx] as doticu_npc_party_script_follower

            p_MCM.SetCursorPosition(cursor)

            p_MCM.AddHeaderOption(ref_follower.Get_Name())
            p_MCM.AddTextOption("   Summon", "")
            if ref_follower.Is_Immobile()
                p_MCM.AddTextOption("   Mobilize", "")
            else
                p_MCM.AddTextOption("   Immobilize", "")
            endIf
            p_MCM.AddTextOption("   More", "...")

            if cursor % 2 == 0
                cursor += 1
            else
                cursor = cursor - 1 + p_COMMANDS_PER_FOLLOWER * 2
            endIf

            idx += 1
        endWhile
    endFunction

    int function p_Get_Idx_Entity(int id_option)
        int id_option_norm = id_option - p_options_offset - p_HEADERS_PER_PAGE
        int idx_entity = Math.Floor(id_option_norm / (p_COMMANDS_PER_FOLLOWER * 2)) * 2
        if id_option_norm % 2 == 1
            idx_entity += 1
        endIf
        return idx_entity
    endFunction

    int function p_Get_Idx_Command(int id_option, int idx_entity)
        int id_option_norm = id_option - p_options_offset - p_HEADERS_PER_PAGE
        return Math.Floor(id_option_norm / 2) - Math.Floor(idx_entity / 2) * p_COMMANDS_PER_FOLLOWER
    endFunction

    function f_On_Option_Select(int id_option)
        int idx_entity = p_Get_Idx_Entity(id_option)
        int idx_command = p_Get_Idx_Command(id_option, idx_entity)
        doticu_npc_party_script_follower ref_follower = p_arr_aliases[idx_entity] as doticu_npc_party_script_follower

        if idx_command == p_IDX_SUMMON
            ref_follower.Summon_Ahead()
        elseIf idx_command == p_IDX_IMMOBILIZE
            if ref_follower.Is_Immobile()
                ref_follower.Mobilize()
            else
                ref_follower.Immobilize()
            endIf
            p_MCM.ForcePageReset()
        elseIf idx_command == p_IDX_MORE
            p_ref_follower = ref_follower
            p_idx_follower = idx_entity
            p_curr_view = p_VIEW_FOLLOWER
            p_MCM.ForcePageReset()
        endIf
    endFunction

    function f_On_Option_Menu_Open(int id_option)
        if id_option == p_option_menu
            string[] arr_options = Utility.CreateStringArray(p_COMMANDS_PER_PAGE, "")

            arr_options[p_IDX_ALL_SUMMON] = " Summon "
            arr_options[p_IDX_ALL_SUMMON_MOBILE] = " Summon Mobile "
            arr_options[p_IDX_ALL_SUMMON_IMMOBILE] = " Summon Immobile "
            arr_options[p_IDX_ALL_IMMOBILIZE] = " Immobilize "
            arr_options[p_IDX_ALL_MOBILIZE] = " Mobilize "
            arr_options[p_IDX_ALL_SNEAK] = " Sneak "
            arr_options[p_IDX_ALL_UNSNEAK] = " Unsneak "
            arr_options[p_IDX_ALL_SETTLE] = " Settle "
            arr_options[p_IDX_ALL_UNSETTLE] = " Unsettle "
            arr_options[p_IDX_ALL_UNFOLLOW] = " Unfollow "
            arr_options[p_IDX_ALL_UNMEMBER] = " Unmember "

            p_MCM.SetMenuDialogOptions(arr_options)
        endIf
    endFunction

    function f_On_Option_Menu_Accept(int id_option, int idx_option)
        if id_option == p_option_menu
            if idx_option == p_IDX_ALL_SUMMON
                p_FOLLOWERS.Summon()
            elseIf idx_option == p_IDX_ALL_SUMMON_MOBILE
                p_FOLLOWERS.Summon_Mobile()
            elseIf idx_option == p_IDX_ALL_SUMMON_IMMOBILE
                p_FOLLOWERS.Summon_Immobile()
            elseIf idx_option == p_IDX_ALL_IMMOBILIZE
                p_FOLLOWERS.Immobilize()
            elseIf idx_option == p_IDX_ALL_MOBILIZE
                p_FOLLOWERS.Mobilize()
            elseIf idx_option == p_IDX_ALL_SNEAK
                p_FOLLOWERS.Sneak()
            elseIf idx_option == p_IDX_ALL_UNSNEAK
                p_FOLLOWERS.Unsneak()
            elseIf idx_option == p_IDX_ALL_SETTLE
                p_FOLLOWERS.Settle()
            elseIf idx_option == p_IDX_ALL_UNSETTLE
                p_FOLLOWERS.Unsettle()
            elseIf idx_option == p_IDX_ALL_UNFOLLOW
                p_FOLLOWERS.Unfollow()
            elseIf idx_option == p_IDX_ALL_UNMEMBER
                p_FOLLOWERS.Unmember()
            endIf
        endIf
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_menu
            p_MCM.SetInfoText("Command all followers.")
        else

        endIf
    endFunction
endState

state p_STATE_FOLLOWER
    function f_Build_Page()
        if !p_ref_follower || !p_ref_follower.Exists()
            p_curr_view = p_VIEW_FOLLOWERS
        endIf
        if p_curr_view == p_VIEW_FOLLOWERS
            GotoState("p_STATE_FOLLOWERS")
            f_Build_Page()
            return
        endIf

        string str_follower_name = p_ref_follower.Get_Name()

        p_MCM.SetCursorPosition(0)
        p_MCM.SetCursorFillMode(p_MCM.LEFT_TO_RIGHT)

        p_MCM.AddHeaderOption("Follower: " + str_follower_name)
        p_option_back = p_MCM.AddTextOption("                            Go Back", "")
        if p_FOLLOWERS.Get_Count() > 1
            p_option_prev = p_MCM.AddTextOption("                       Previous Follower", "")
            p_option_next = p_MCM.AddTextOption("                         Next Follower", "")
        else
            p_option_prev = p_MCM.AddTextOption("                       Previous Follower", "", p_MCM.OPTION_FLAG_DISABLED)
            p_option_next = p_MCM.AddTextOption("                         Next Follower", "", p_MCM.OPTION_FLAG_DISABLED)
        endIf

        p_option_access = p_MCM.AddTextOption(" Access ", "")
        p_option_rename = p_MCM.AddInputOption(" Rename ", str_follower_name)
        p_option_unfollow = p_MCM.AddTextOption(" Unfollow ", "")
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_back
            p_ref_follower = none
            p_idx_follower = -1
            p_curr_view = p_VIEW_FOLLOWERS
            p_MCM.ForcePageReset()
        elseIf id_option == p_option_prev
            if p_idx_follower == 0
                p_idx_follower = p_arr_aliases.length - 1
            else
                p_idx_follower -= 1
            endIf
            p_ref_follower = p_arr_aliases[p_idx_follower] as doticu_npc_party_script_follower
            p_MCM.ForcePageReset()
        elseIf id_option == p_option_next
            if p_idx_follower == p_arr_aliases.length - 1
                p_idx_follower = 0
            else
                p_idx_follower += 1
            endIf
            p_ref_follower = p_arr_aliases[p_idx_follower] as doticu_npc_party_script_follower
            p_MCM.ForcePageReset()
        elseIf id_option == p_option_access
            p_FUNCS.Close_Menu()
            p_ref_follower.Access()
        elseIf id_option == p_option_unfollow
            p_ref_follower.Unfollow()
            p_ref_follower = none
            p_idx_follower = -1
            p_curr_view = p_VIEW_FOLLOWERS
            p_MCM.ForcePageReset()
        endIf
    endFunction

    function f_On_Option_Input_Accept(int id_option, string str_input)
        if id_option == p_option_rename
            if str_input != ""
                p_ref_follower.Set_Name(str_input)
                p_MCM.ForcePageReset()
            endIf
        endIf
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_back
            p_MCM.SetInfoText("Go back to Followers")
        elseIf id_option == p_option_prev
            p_MCM.SetInfoText("Go to the Previous Follower")
        elseIf id_option == p_option_next
            p_MCM.SetInfoText("Go to the Next Follower")
        elseIf id_option == p_option_access
            p_MCM.SetInfoText("Access this follower's inventory.")
        elseIf id_option == p_option_rename
            p_MCM.SetInfoText("Rename this follower.")
        elseIf id_option == p_option_unfollow
            p_MCM.SetInfoText("Dismiss this follower.")
        endIf
    endFunction
endState
