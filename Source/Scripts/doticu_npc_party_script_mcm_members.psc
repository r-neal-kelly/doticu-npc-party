Scriptname doticu_npc_party_script_mcm_members extends Quest

; Private Constants
doticu_npc_party_script_consts  p_CONSTS                = none
doticu_npc_party_script_vars    p_VARS                  = none
doticu_npc_party_script_funcs   p_FUNCS                 = none
doticu_npc_party_script_members p_MEMBERS               = none
doticu_npc_Party_script_mcm     p_MCM                   = none

int                             p_VIEW_MEMBERS          =    0
int                             p_VIEW_MEMBER           =    1

int                             p_HEADERS_PER_PAGE      =    4
int                             p_MEMBERS_PER_PAGE      =   20

int                             p_COMMANDS_PER_MEMBER   =    4
int                             p_IDX_SUMMON            =    0
int                             p_IDX_FOLLOW            =    1
int                             p_IDX_IMMOBILIZE        =    2
int                             p_IDX_MORE              =    3

; Private Variables
int                             p_curr_view             =    0
int                             p_curr_page             =    0
int                             p_count_pages           =   -1
Alias[]                         p_arr_aliases           = none
doticu_npc_party_script_member  p_ref_member            = none
int                             p_idx_member            =   -1
int                             p_options_offset        =   -1

int                             p_option_rename         =   -1
int                             p_option_back           =   -1
int                             p_option_prev           =   -1
int                             p_option_next           =   -1

int                             p_option_access         =   -1; will this action work when npc is unloaded? I don't think so
int                             p_option_clone          =   -1
int                             p_option_unclone        =   -1
int                             p_option_unmember       =   -1

int                             p_option_health         =   -1
int                             p_option_magicka        =   -1
int                             p_option_stamina        =   -1

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CONSTS = DATA.CONSTS
    p_VARS = DATA.VARS
    p_FUNCS = DATA.MODS.FUNCS
    p_MEMBERS = DATA.MODS.MEMBERS
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
auto state p_STATE_MEMBERS
    function f_Build_Page()
        if p_curr_view == p_VIEW_MEMBER
            GotoState("p_STATE_MEMBER")
            f_Build_Page()
            return
        endIf

        p_MCM.SetCursorPosition(0)
        p_MCM.SetCursorFillMode(p_MCM.LEFT_TO_RIGHT)

        int count_members = p_MEMBERS.Get_Count()
        int max_members = p_MEMBERS.Get_Max()
        string str_count_members
        string str_count_pages
        if count_members == 0
            str_count_members = "Members: 0/" + max_members
            str_count_pages = "Page: 1/1"
            p_MCM.SetTitleText(str_count_members + ", " + str_count_pages)
            ; should add a no members option(s)
            return
        endIf

        p_count_pages = Math.Ceiling(count_members / (p_MEMBERS_PER_PAGE as float))
        str_count_members = "Members: " + count_members + "/" + max_members
        str_count_pages = "Page: " + (p_curr_page + 1) + "/" + p_count_pages
        p_MCM.SetTitleText(str_count_members + ", " + str_count_pages)

        if count_members > p_MEMBERS_PER_PAGE
            p_option_prev = p_MCM.AddTextOption("                     Go to Previous Page", "")
            p_option_next = p_MCM.AddTextOption("                       Go to Next Page", "")
        else
            p_option_prev = p_MCM.AddTextOption("                     Go to Previous Page", "", p_MCM.OPTION_FLAG_DISABLED)
            p_option_next = p_MCM.AddTextOption("                       Go to Next Page", "", p_MCM.OPTION_FLAG_DISABLED)
        endIf
        p_options_offset = p_option_prev

        p_MCM.AddHeaderOption("")
        p_MCM.AddHeaderOption("")

        int idx_from = p_MEMBERS_PER_PAGE * p_curr_page
        int idx_to_ex = idx_from + p_MEMBERS_PER_PAGE
        int idx = 0
        p_arr_aliases = p_MEMBERS.Get_Aliases_Sorted(idx_from, idx_to_ex)
        while idx < p_arr_aliases.length
            doticu_npc_party_script_member ref_member = p_arr_aliases[idx] as doticu_npc_party_script_member
            p_MCM.AddMenuOption(ref_member.Get_Name(), "...")
            idx += 1
        endWhile
    endFunction

    int function p_Get_Idx_Entity(int id_option)
        return id_option - p_options_offset - p_HEADERS_PER_PAGE
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_prev
            if p_curr_page == 0
                p_curr_page = p_count_pages - 1
            else
                p_curr_page -= 1
            endIf
        elseIf id_option == p_option_next
            if p_curr_page == p_count_pages - 1
                p_curr_page = 0
            else
                p_curr_page += 1
            endIf
        endIf

        p_MCM.ForcePageReset()
    endFunction

    function f_On_Option_Menu_Open(int id_option)
        int idx_entity = p_Get_Idx_Entity(id_option)
        doticu_npc_party_script_member ref_member = p_arr_aliases[idx_entity] as doticu_npc_party_script_member
        string[] arr_options = Utility.CreateStringArray(p_COMMANDS_PER_MEMBER, "")

        arr_options[p_IDX_SUMMON] = " Summon "
        if ref_member.Is_Follower()
            arr_options[p_IDX_FOLLOW] = " Unfollow "
        else
            arr_options[p_IDX_FOLLOW] = " Follow "
        endIf
        if ref_member.Is_Immobile()
            arr_options[p_IDX_IMMOBILIZE] = " Mobilize "
        else
            arr_options[p_IDX_IMMOBILIZE] = " Immobilize "
        endIf
        arr_options[p_IDX_MORE] = " More... "

        p_MCM.SetMenuDialogOptions(arr_options)
    endFunction

    function f_On_Option_Menu_Accept(int id_option, int idx_option)
        int idx_entity = p_Get_Idx_Entity(id_option)
        doticu_npc_party_script_member ref_member = p_arr_aliases[idx_entity] as doticu_npc_party_script_member

        if idx_option == p_IDX_SUMMON
            ref_member.Summon()
        elseIf idx_option == p_IDX_FOLLOW
            if ref_member.Is_Follower()
                ref_member.Unfollow()
            else
                ref_member.Follow()
            endIf
        elseIf idx_option == p_IDX_IMMOBILIZE
            if ref_member.Is_Immobile()
                ref_member.Mobilize()
            else
                ref_member.Immobilize()
            endIf
        elseIf idx_option == p_IDX_MORE
            p_ref_member = ref_member
            p_idx_member = idx_entity
            p_curr_view = p_VIEW_MEMBER
            p_MCM.ForcePageReset()
        endIf
    endFunction
    
    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_prev
            p_MCM.SetInfoText("Go to the Previous Page")
        elseIf id_option == p_option_next
            p_MCM.SetInfoText("Go to the Next Page")
        else
            int idx_entity = p_Get_Idx_Entity(id_option)
            doticu_npc_party_script_member ref_member = p_arr_aliases[idx_entity] as doticu_npc_party_script_member
            string str_name = ref_member.Get_Name()
            p_MCM.SetInfoText("Opens the member menu for " + str_name)
            ; this should show more about the member, like race, gender, style, and stats!!!
            ; whether is dead, healthly, etc.
        endIf
    endFunction
endState

state p_STATE_MEMBER
    function f_Build_Page()
        if !p_ref_member || !p_ref_member.Exists()
            p_curr_view = p_VIEW_MEMBERS
        endIf
        if p_curr_view == p_VIEW_MEMBERS
            GotoState("p_STATE_MEMBERS")
            f_Build_Page()
            return
        endIf

        string str_member_name = p_ref_member.Get_Name()

        p_MCM.SetCursorPosition(0)
        p_MCM.SetCursorFillMode(p_MCM.LEFT_TO_RIGHT)

        p_MCM.SetTitleText("Member: " + str_member_name)

        p_option_rename = p_MCM.AddInputOption(str_member_name + " ", " Rename ")
        p_option_back = p_MCM.AddTextOption("                            Go Back", "")
        if p_MEMBERS.Get_Count() > 1
            p_option_prev = p_MCM.AddTextOption("                      Previous Member", "")
            p_option_next = p_MCM.AddTextOption("                        Next Member", "")
        else
            p_option_prev = p_MCM.AddTextOption("                      Previous Member", "", p_MCM.OPTION_FLAG_DISABLED)
            p_option_next = p_MCM.AddTextOption("                        Next Member", "", p_MCM.OPTION_FLAG_DISABLED)
        endIf

        p_MCM.SetCursorPosition(4)
        p_MCM.SetCursorFillMode(p_MCM.TOP_TO_BOTTOM)

        p_MCM.AddHeaderOption("Commands: ")
        p_option_access = p_MCM.AddTextOption(" Access ", "")
        p_option_clone  = p_MCM.AddTextOption(" Clone ", "")
        if p_ref_member.Is_Clone()
            p_option_unclone  = p_MCM.AddTextOption(" Unclone ", "")
        else
            p_option_unclone  = p_MCM.AddTextOption(" Unclone ", "", p_MCM.OPTION_FLAG_DISABLED)
        endIf
        if !p_MEMBERS.Should_Unclone_Member(p_ref_member)
            p_option_unmember = p_MCM.AddTextOption(" Unmember ", "")
        else
            p_option_unmember = p_MCM.AddTextOption(" Unmember ", "", p_MCM.OPTION_FLAG_DISABLED)
        endIf

        p_MCM.SetCursorPosition(5)
        p_MCM.SetCursorFillMode(p_MCM.TOP_TO_BOTTOM)

        Actor ref_actor = p_ref_member.Get_Actor()
        p_MCM.AddHeaderOption("Statistics: ")
        p_option_health = p_MCM.AddTextOption(" Health: ", ref_actor.GetActorValue(p_CONSTS.STR_HEALTH) as int)
        p_option_magicka = p_MCM.AddTextOption(" Magicka: ", ref_actor.GetActorValue(p_CONSTS.STR_MAGICKA) as int)
        p_option_stamina = p_MCM.AddTextOption(" Stamina: ", ref_actor.GetActorValue(p_CONSTS.STR_STAMINA) as int)
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_back
            p_ref_member = none
            p_idx_member = -1
            p_curr_view = p_VIEW_MEMBERS
            p_MCM.ForcePageReset()
        elseIf id_option == p_option_prev
            if p_idx_member == 0
                p_idx_member = p_arr_aliases.length - 1
            else
                p_idx_member -= 1
            endIf
            p_ref_member = p_arr_aliases[p_idx_member] as doticu_npc_party_script_member
            p_MCM.ForcePageReset()
        elseIf id_option == p_option_next
            if p_idx_member == p_arr_aliases.length - 1
                p_idx_member = 0
            else
                p_idx_member += 1
            endIf
            p_ref_member = p_arr_aliases[p_idx_member] as doticu_npc_party_script_member
            p_MCM.ForcePageReset()
        elseIf id_option == p_option_access
            p_FUNCS.Close_Menus()
            p_ref_member.Access()
        elseIf id_option == p_option_clone
            p_ref_member.Clone()
        elseIf id_option == p_option_unclone
            p_ref_member.Unclone()
            p_ref_member = none
            p_idx_member = -1
            p_curr_view = p_VIEW_MEMBERS
            p_MCM.ForcePageReset()
        elseIf id_option == p_option_unmember
            p_ref_member.Unmember()
            p_ref_member = none
            p_idx_member = -1
            p_curr_view = p_VIEW_MEMBERS
            p_MCM.ForcePageReset()
        endIf
    endFunction

    function f_On_Option_Input_Accept(int id_option, string str_input)
        if id_option == p_option_rename
            if str_input != ""
                p_ref_member.Set_Name(str_input)
                p_MCM.ForcePageReset()
            endIf
        endIf
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_back
            p_MCM.SetInfoText("Go back to Members")
        elseIf id_option == p_option_prev
            p_MCM.SetInfoText("Go to the Previous Member")
        elseIf id_option == p_option_next
            p_MCM.SetInfoText("Go to the Next Member")
        elseIf id_option == p_option_access
            p_MCM.SetInfoText("Access this member's inventory.")
        elseIf id_option == p_option_rename
            p_MCM.SetInfoText("Rename this member.")
        elseIf id_option == p_option_clone
            p_MCM.SetInfoText("Clone this member.")
        elseIf id_option == p_option_unclone
            p_MCM.SetInfoText("Unclone and unmember this member.")
        elseIf id_option == p_option_unmember
            p_MCM.SetInfoText("Unmember this member.")
        endIf
    endFunction
endState
