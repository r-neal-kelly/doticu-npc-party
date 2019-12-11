Scriptname doticu_npc_party_script_mcm extends SKI_ConfigBase

; Private Constants
doticu_npc_party_script_actor       p_ACTOR2                        = none
doticu_npc_party_script_members     p_MEMBERS                       = none
doticu_npc_party_script_followers   p_FOLLOWERS                     = none

int                                 p_FOLLOWERS_HEADERS_PAGE        =    4
int                                 p_FOLLOWERS_COMMANDS_PAGE       =   10
int                                 p_FOLLOWERS_COMMANDS_FOLLOWER   =    4; includes the name
int                                 p_FOLLOWERS_ALL_SUMMON          =    0
int                                 p_FOLLOWERS_ALL_SUMMON_MOBILE   =    1
int                                 p_FOLLOWERS_ALL_SUMMON_IMMOBILE =    2
int                                 p_FOLLOWERS_ALL_IMMOBILIZE      =    3
int                                 p_FOLLOWERS_ALL_MOBILIZE        =    4
int                                 p_FOLLOWERS_ALL_SNEAK           =    5
int                                 p_FOLLOWERS_ALL_UNSNEAK         =    6
int                                 p_FOLLOWERS_ALL_SETTLE          =    7
int                                 p_FOLLOWERS_ALL_UNSETTLE        =    8
int                                 p_FOLLOWERS_ALL_UNMEMBER        =    9
int                                 p_FOLLOWERS_SUMMON              =    1; 0 == the name
int                                 p_FOLLOWERS_IMMOBILIZE          =    2
int                                 p_FOLLOWERS_MORE                =    3

int                                 p_FOLLOWER_HEADERS_PAGE         =    4

int                                 p_MEMBERS_HEADERS_PAGE          =    4
int                                 p_MEMBERS_MEMBERS_PAGE          =   20
int                                 p_MEMBERS_COMMANDS_MEMBER       =    3
int                                 p_MEMBERS_SUMMON                =    0
int                                 p_MEMBERS_IMMOBILIZE            =    1
int                                 p_MEMBERS_FOLLOW                =    2
int                                 p_MEMBERS_UNMEMBER              =    3

int                                 p_MEMBER_HEADERS_PAGE           =    4

; Private Variables
Alias[]                             p_followers_arr_aliases         = none
int                                 p_followers_options_offset      =   -1
int                                 p_followers_option_menu         =   -1

doticu_npc_party_script_follower    p_follower_ref_follower         = none
int                                 p_follower_idx_follower         =   -1
int                                 p_follower_option_back          =   -1
int                                 p_follower_option_prev          =   -1
int                                 p_follower_option_next          =   -1
int                                 p_follower_option_access        =   -1
int                                 p_follower_option_rename        =   -1
int                                 p_follower_option_unfollow      =   -1

Alias[]                             p_members_arr_aliases           = none
int                                 p_members_curr_page             =    0
int                                 p_members_pages                 =   -1
int                                 p_members_options_offset        =   -1
int                                 p_members_option_prev           =   -1
int                                 p_members_option_next           =   -1

doticu_npc_party_script_member      p_member_ref_member             = none
int                                 p_member_idx_member             =   -1
int                                 p_member_option_rename          =   -1
int                                 p_member_option_access          =   -1
int                                 p_member_option_unfollow        =   -1

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
endFunction

; Private Methods
function p_Build_Page()
endFunction

int function p_Get_Idx_Entity(int id_option)
endFunction

int function p_Get_Idx_Command(int id_option)
endFunction

doticu_npc_party_script_member function p_Get_Member(int id_option)
endFunction

doticu_npc_party_script_follower function p_Get_Follower(int id_option)
endFunction

; Private States
state p_STATE_FOLLOWERS
    function p_Build_Page()
        if p_follower_ref_follower && p_follower_ref_follower.Exists()
            GotoState("p_STATE_FOLLOWER")
            p_Build_Page()
            return
        endIf

        SetCursorPosition(0)
        SetCursorFillMode(LEFT_TO_RIGHT)

        int count_followers = p_FOLLOWERS.Get_Count()
        int max_followers = p_FOLLOWERS.Get_Max()
        if count_followers == 0
            AddHeaderOption("0/" + max_followers as string + " Followers")
            return
        endIf

        p_followers_options_offset = AddHeaderOption(count_followers as string + "/" + max_followers as string + " Followers")
        p_followers_option_menu = AddMenuOption(" Command All ", "...")
        AddEmptyOption()
        AddEmptyOption()

        SetCursorFillMode(TOP_TO_BOTTOM)

        int idx = 0
        int cursor = p_FOLLOWERS_HEADERS_PAGE
        p_followers_arr_aliases = p_FOLLOWERS.Get_Aliases_Sorted()
        while idx < p_followers_arr_aliases.length
            doticu_npc_party_script_follower ref_follower = p_followers_arr_aliases[idx] as doticu_npc_party_script_follower

            SetCursorPosition(cursor)

            AddHeaderOption(ref_follower.Get_Name())
            AddTextOption("   Summon", "")
            if ref_follower.Is_Immobile()
                AddTextOption("   Mobilize", "")
            else
                AddTextOption("   Immobilize", "")
            endIf
            AddTextOption("   More", "...")

            if cursor % 2 == 0
                cursor += 1
            else
                cursor = cursor - 1 + p_FOLLOWERS_COMMANDS_FOLLOWER * 2
            endIf

            idx += 1
        endWhile
    endFunction

    doticu_npc_party_script_follower function p_Get_Follower(int id_option)
        int idx_follower = p_Get_Idx_Entity(id_option)
        return p_followers_arr_aliases[idx_follower] as doticu_npc_party_script_follower
    endFunction

    int function p_Get_Idx_Entity(int id_option)
        int id_option_norm = id_option - p_followers_options_offset - p_FOLLOWERS_HEADERS_PAGE
        int idx_entity = Math.Floor(id_option_norm / (p_FOLLOWERS_COMMANDS_FOLLOWER * 2)) * 2
        if id_option_norm % 2 == 1
            idx_entity += 1
        endIf
        return idx_entity
    endFunction

    int function p_Get_Idx_Command(int id_option)
        int id_option_norm = id_option - p_followers_options_offset - p_FOLLOWERS_HEADERS_PAGE
        int idx_entity = p_Get_Idx_Entity(id_option)
        return Math.Floor(id_option_norm / 2) - Math.Floor(idx_entity / 2) * p_FOLLOWERS_COMMANDS_FOLLOWER
    endFunction

    event OnOptionSelect(int id_option)
        doticu_npc_party_script_follower ref_follower = p_Get_Follower(id_option)
        int idx_entity = p_Get_Idx_Entity(id_option)
        int idx_command = p_Get_Idx_Command(id_option)

        if idx_command == p_FOLLOWERS_SUMMON
            ref_follower.Summon_Ahead()
        elseIf idx_command == p_FOLLOWERS_IMMOBILIZE
            if ref_follower.Is_Immobile()
                ref_follower.Mobilize()
            else
                ref_follower.Immobilize()
            endIf
            ForcePageReset()
        elseIf idx_command == p_FOLLOWERS_MORE
            p_follower_ref_follower = ref_follower
            p_follower_idx_follower = idx_entity
            ForcePageReset()
        endIf
    endEvent

    event OnOptionMenuOpen(int id_option)
        if id_option == p_followers_option_menu
            doticu_npc_party_script_follower ref_follower = p_Get_Follower(id_option)
            string[] arr_options = Utility.CreateStringArray(p_FOLLOWERS_COMMANDS_PAGE, "")

            arr_options[p_FOLLOWERS_ALL_SUMMON] = " Summon "
            arr_options[p_FOLLOWERS_ALL_SUMMON_MOBILE] = " Summon Mobile "
            arr_options[p_FOLLOWERS_ALL_SUMMON_IMMOBILE] = " Summon Immobile "
            arr_options[p_FOLLOWERS_ALL_IMMOBILIZE] = " Immobilize "
            arr_options[p_FOLLOWERS_ALL_MOBILIZE] = " Mobilize "
            arr_options[p_FOLLOWERS_ALL_SNEAK] = " Sneak "
            arr_options[p_FOLLOWERS_ALL_UNSNEAK] = " Unsneak "
            arr_options[p_FOLLOWERS_ALL_SETTLE] = " Settle "
            arr_options[p_FOLLOWERS_ALL_UNSETTLE] = " Unsettle "
            arr_options[p_FOLLOWERS_ALL_UNMEMBER] = " Unmember "

            SetMenuDialogOptions(arr_options)
        endIf
    endEvent

    event OnOptionMenuAccept(int id_option, int idx_option)
        if id_option == p_followers_option_menu
            doticu_npc_party_script_follower ref_follower = p_Get_Follower(id_option)

            if idx_option == p_FOLLOWERS_ALL_SUMMON
                p_FOLLOWERS.Summon()
            elseIf idx_option == p_FOLLOWERS_ALL_SUMMON_MOBILE
                p_FOLLOWERS.Summon_Mobile()
            elseIf idx_option == p_FOLLOWERS_ALL_SUMMON_IMMOBILE
                p_FOLLOWERS.Summon_Immobile()
            elseIf idx_option == p_FOLLOWERS_ALL_IMMOBILIZE
                p_FOLLOWERS.Immobilize()
            elseIf idx_option == p_FOLLOWERS_ALL_MOBILIZE
                p_FOLLOWERS.Mobilize()
            elseIf idx_option == p_FOLLOWERS_ALL_SNEAK
                p_FOLLOWERS.Sneak()
            elseIf idx_option == p_FOLLOWERS_ALL_UNSNEAK
                p_FOLLOWERS.Unsneak()
            elseIf idx_option == p_FOLLOWERS_ALL_SETTLE
                p_FOLLOWERS.Settle()
            elseIf idx_option == p_FOLLOWERS_ALL_UNSETTLE
                p_FOLLOWERS.Unsettle()
            elseIf idx_option == p_FOLLOWERS_ALL_UNMEMBER
                p_FOLLOWERS.Unmember(); maybe too dangerous?
            endIf
        endIf
    endEvent

    event OnOptionHighlight(int id_option)
        if id_option == p_followers_option_menu
            SetInfoText("Command all followers.")
        else

        endIf
    endEvent
endState

state p_STATE_FOLLOWER
    function p_Build_Page()
        string str_follower_name = p_follower_ref_follower.Get_Name()

        SetCursorPosition(0)
        SetCursorFillMode(LEFT_TO_RIGHT)

        AddHeaderOption(str_follower_name)
        p_follower_option_back = AddTextOption("                            Go Back", "")
        if p_FOLLOWERS.Get_Count() > 1
            p_follower_option_prev = AddTextOption("                       Previous Follower", "")
            p_follower_option_next = AddTextOption("                         Next Follower", "")
        else
            p_follower_option_prev = AddTextOption("                       Previous Follower", "", OPTION_FLAG_DISABLED)
            p_follower_option_next = AddTextOption("                         Next Follower", "", OPTION_FLAG_DISABLED)
        endIf

        p_follower_option_access = AddTextOption(" Access ", "")
        p_follower_option_rename = AddInputOption(" Rename ", str_follower_name)
        p_follower_option_unfollow = AddTextOption(" Unfollow ", "")
    endFunction

    event OnOptionSelect(int id_option)
        if id_option == p_follower_option_back
            p_follower_ref_follower = none
            p_follower_idx_follower = -1
            ForcePageReset()
        elseIf id_option == p_follower_option_prev
            if p_follower_idx_follower == 0
                p_follower_idx_follower = p_followers_arr_aliases.length - 1
            else
                p_follower_idx_follower -= 1
            endIf
            p_follower_ref_follower = p_followers_arr_aliases[p_follower_idx_follower] as doticu_npc_party_script_follower
            ForcePageReset()
        elseIf id_option == p_follower_option_next
            if p_follower_idx_follower == p_followers_arr_aliases.length - 1
                p_follower_idx_follower = 0
            else
                p_follower_idx_follower += 1
            endIf
            p_follower_ref_follower = p_followers_arr_aliases[p_follower_idx_follower] as doticu_npc_party_script_follower
            ForcePageReset()
        elseIf id_option == p_follower_option_access
            p_follower_ref_follower.Access()
            ; can't we close the menus?
        elseIf id_option == p_follower_option_unfollow
            p_follower_ref_follower.Unfollow()
            p_follower_ref_follower = none
            p_follower_idx_follower = -1
            ForcePageReset()
        endIf
    endEvent

    event OnOptionInputOpen(int id_option)
        ; anything to do here?
    endEvent

    event OnOptionInputAccept(int id_option, string str_input)
        if id_option == p_follower_option_rename
            if str_input != ""
                p_follower_ref_follower.Set_Name(str_input)
                ForcePageReset()
            endIf
        endIf
    endEvent

    event OnOptionHighlight(int id_option)
        if id_option == p_follower_option_back
            SetInfoText("Go back to Followers")
        elseIf id_option == p_follower_option_prev
            SetInfoText("Go to the Previous Follower")
        elseIf id_option == p_follower_option_next
            SetInfoText("Go to the Next Follower")
        elseIf id_option == p_follower_option_access
            SetInfoText("Access this follower's inventory.")
        elseIf id_option == p_follower_option_rename
            SetInfoText("Rename this follower.")
        elseIf id_option == p_follower_option_unfollow
            SetInfoText("Dismiss this follower.")
        endIf
    endEvent
endState

state p_STATE_MEMBERS
    function p_Build_Page()
        if p_member_ref_member && p_member_ref_member.Exists()
            GotoState("p_STATE_MEMBER")
            p_Build_Page()
            return
        endIf

        SetCursorPosition(0)
        SetCursorFillMode(LEFT_TO_RIGHT)

        int count_members = p_MEMBERS.Get_Count()
        int max_members = p_MEMBERS.Get_Max()
        string str_count_members
        string str_count_pages
        if count_members == 0
            str_count_members = "0/" + max_members as string + " Members"
            str_count_pages = "Page 1 of 1"
            AddHeaderOption(str_count_members + ", " + str_count_pages)
            return
        endIf

        p_members_pages = Math.Ceiling(count_members / (p_MEMBERS_MEMBERS_PAGE as float))
        str_count_members = count_members as string + "/" + max_members as string + " Members"
        str_count_pages = "Page " + (p_members_curr_page + 1) as string + " of " + p_members_pages as string
        p_members_options_offset = AddHeaderOption(str_count_members + ", " + str_count_pages)
        AddEmptyOption()

        if count_members > p_MEMBERS_MEMBERS_PAGE
            p_members_option_prev = AddTextOption("                     Go to Previous Page", "")
            p_members_option_next = AddTextOption("                       Go to Next Page", "")
        else
            p_members_option_prev = AddTextOption("                     Go to Previous Page", "", OPTION_FLAG_DISABLED)
            p_members_option_next = AddTextOption("                       Go to Next Page", "", OPTION_FLAG_DISABLED)
        endIf

        int idx_from = p_MEMBERS_MEMBERS_PAGE * p_members_curr_page
        int idx_to_ex = idx_from + p_MEMBERS_MEMBERS_PAGE
        int idx = 0
        p_members_arr_aliases = p_MEMBERS.Get_Aliases_Sorted(idx_from, idx_to_ex)
        while idx < p_members_arr_aliases.length
            doticu_npc_party_script_member ref_member = p_members_arr_aliases[idx] as doticu_npc_party_script_member
            AddMenuOption(ref_member.Get_Name(), "...")
            idx += 1
        endWhile
    endFunction

    doticu_npc_party_script_member function p_Get_Member(int id_option)
        int idx_aliases = id_option - p_members_options_offset - p_MEMBERS_HEADERS_PAGE
        return p_members_arr_aliases[idx_aliases] as doticu_npc_party_script_member
    endFunction

    event OnOptionSelect(int id_option)
        if id_option == p_members_option_prev
            if p_members_curr_page == 0
                p_members_curr_page = p_members_pages - 1
            else
                p_members_curr_page -= 1
            endIf
        elseIf id_option == p_members_option_next
            if p_members_curr_page == p_members_pages - 1
                p_members_curr_page = 0
            else
                p_members_curr_page += 1
            endIf
        endIf

        ForcePageReset()
    endEvent

    event OnOptionMenuOpen(int id_option)
        doticu_npc_party_script_member ref_member = p_Get_Member(id_option)
        string[] arr_options = Utility.CreateStringArray(p_MEMBERS_COMMANDS_MEMBER, "")

        arr_options[p_MEMBERS_SUMMON] = " Summon "
        if ref_member.Is_Immobile()
            arr_options[p_MEMBERS_IMMOBILIZE] = " Mobilize "
        else
            arr_options[p_MEMBERS_IMMOBILIZE] = " Immobilize "
        endIf
        if ref_member.Is_Follower()
            arr_options[p_MEMBERS_FOLLOW] = " Follow "
        else
            arr_options[p_MEMBERS_FOLLOW] = " Unfollow "
        endIf
        arr_options[p_MEMBERS_UNMEMBER] = " Unmember "

        SetMenuDialogOptions(arr_options)
    endEvent

    event OnOptionMenuAccept(int id_option, int idx_option)
        doticu_npc_party_script_member ref_member = p_Get_Member(id_option)

        if idx_option == p_MEMBERS_SUMMON
            ref_member.Summon()
        elseIf idx_option == p_MEMBERS_IMMOBILIZE
            if ref_member.Is_Immobile()
                ref_member.Mobilize()
            else
                ref_member.Immobilize()
            endIf
        elseIf idx_option == p_MEMBERS_UNMEMBER
            p_MEMBERS.Destroy_Member(ref_member.Get_Actor())
            ForcePageReset()
        endIf
    endEvent
    
    event OnOptionHighlight(int id_option)
        if id_option == p_members_option_prev
            SetInfoText("Go to the Previous Page")
        elseIf id_option == p_members_option_next
            SetInfoText("Go to the Next Page")
        else
            doticu_npc_party_script_member ref_member = p_Get_Member(id_option)
            string str_name = ref_member.Get_Name()
            SetInfoText("Opens the member menu for " + str_name)
            ; this should show more about the member, like race, gender, style, and stats!!!
            ; whether is dead, healthly, etc.
        endIf
    endEvent
endState

state p_STATE_MEMBER
    ; this will have an individual members's page.
    ; AddInputOption("Rename", "")
    ; AddTextOption("Access", "")
    ; AddTextOption("Unfollow", "")
endState

state p_STATE_FILTER
    function p_Build_Page()
        ; should be able to request an array with filter variables
        ; and maybe should cache it, but it gets complicated at that point
        ; but it's slow without it. there are options, but this will wait
    endFunction
endState

state p_STATE_SETTINGS
    function p_Build_Page()
        ; should have a way to bind all keys
        ; should have toggles for global vars
        ; confer with doticu_npc_party_script_vars
    endFunction
endState

; Events
event OnConfigOpen()
    Pages = Utility.CreateStringArray(4, "")
    Pages[0] = "   Followers"
    Pages[1] = "   Members"
    Pages[2] = "   Filter"
    Pages[3] = "   Settings"
endEvent

event OnPageReset(string str_page)
    if str_page == "   Followers"
        GotoState("p_STATE_FOLLOWERS")
    elseIf str_page == "   Members"
        GotoState("p_STATE_MEMBERS")
    elseIf str_page == "   Filter"
        GotoState("p_STATE_FILTER")
    elseIf str_page == "   Settings"
        GotoState("p_STATE_SETTINGS")
    endIf

    p_Build_Page()
endEvent
