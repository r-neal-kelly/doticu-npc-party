Scriptname doticu_npcp_mcm_members extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
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

; Private Constants
doticu_npcp_data    p_DATA                      =  none

int                 p_HEADERS_PER_PAGE          =     4
int                 p_MEMBERS_PER_PAGE          =    20

; Private Variables
bool                p_is_created                = false

int                 p_curr_page                 =     0
int                 p_num_pages                 =    -1
Alias[]             p_arr_aliases               =  none
doticu_npcp_member  p_ref_member                =  none
int                 p_options_offset            =    -1

bool                p_is_settler                = false

int                 p_option_rename             =    -1
int                 p_option_back               =    -1
int                 p_option_prev               =    -1
int                 p_option_next               =    -1

int                 p_option_summon             =    -1
int                 p_option_pack               =    -1
int                 p_option_outfit             =    -1
int                 p_option_resurrect          =    -1
int                 p_option_settle             =    -1
int                 p_option_resettle           =    -1
int                 p_option_unsettle           =    -1
int                 p_option_enthrall           =    -1
int                 p_option_immobilize         =    -1
int                 p_option_mobilize           =    -1
int                 p_option_paralyze           =    -1
int                 p_option_follow             =    -1
int                 p_option_sneak              =    -1
int                 p_option_style              =    -1
int                 p_option_vitalize           =    -1
int                 p_option_clone              =    -1
int                 p_option_unclone            =    -1
int                 p_option_unmember           =    -1

int                 p_option_health             =    -1
int                 p_option_magicka            =    -1
int                 p_option_stamina            =    -1

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

function f_On_Option_Slider_Open(int id_option)
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Highlight(int id_option)
endFunction

; Private Methods
int function p_Get_Idx_Entity(int id_option)
endFunction

int function p_Get_Idx_Command(int id_option, int idx_entity)
endFunction

string function p_Format_Title(string str_members, string str_pages)
    return str_members + "               " + str_pages
endFunction

function p_View_Members()
    p_ref_member = none
    GotoState("p_STATE_MEMBERS")
    MCM.ForcePageReset()
endFunction

function p_View_Member(int idx_member)
    p_ref_member = p_arr_aliases[idx_member] as doticu_npcp_member
    GotoState("p_STATE_MEMBER")
    MCM.ForcePageReset()
endFunction

; Private States
auto state p_STATE_MEMBERS
    function f_Build_Page()
        MCM.SetCursorPosition(0)
        MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

        int count_members = MEMBERS.Get_Count()
        int max_members = MEMBERS.Get_Max()
        string str_count_members
        string str_count_pages
        if count_members == 0
            str_count_members = "Members: 0/" + max_members
            str_count_pages = "Page: 1/1"
            MCM.SetTitleText(p_Format_Title(str_count_members, str_count_pages))
            MCM.AddHeaderOption(" No Members ")
            return
        endIf

        p_num_pages = Math.Ceiling(count_members / (p_MEMBERS_PER_PAGE as float))
        str_count_members = "Members: " + count_members + "/" + max_members
        str_count_pages = "Page: " + (p_curr_page + 1) + "/" + p_num_pages
        MCM.SetTitleText(p_Format_Title(str_count_members, str_count_pages))

        if count_members > p_MEMBERS_PER_PAGE
            p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "")
            p_option_next = MCM.AddTextOption("                       Go to Next Page", "")
        else
            p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "", MCM.OPTION_FLAG_DISABLED)
            p_option_next = MCM.AddTextOption("                       Go to Next Page", "", MCM.OPTION_FLAG_DISABLED)
        endIf
        p_options_offset = p_option_prev

        MCM.AddHeaderOption("")
        MCM.AddHeaderOption("")

        int idx_from = p_MEMBERS_PER_PAGE * p_curr_page
        int idx_to_ex = idx_from + p_MEMBERS_PER_PAGE
        int idx = 0
        p_arr_aliases = MEMBERS.Get_Members(idx_from, idx_to_ex)
        while idx < p_arr_aliases.length
            doticu_npcp_member ref_member = p_arr_aliases[idx] as doticu_npcp_member
            MCM.AddTextOption(ref_member.Get_Name(), "...")
            idx += 1
        endWhile
    endFunction

    int function p_Get_Idx_Entity(int id_option)
        return id_option - p_options_offset - p_HEADERS_PER_PAGE
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_prev
            if p_curr_page == 0
                p_curr_page = p_num_pages - 1
            else
                p_curr_page -= 1
            endIf
            MCM.ForcePageReset()
        elseIf id_option == p_option_next
            if p_curr_page == p_num_pages - 1
                p_curr_page = 0
            else
                p_curr_page += 1
            endIf
            MCM.ForcePageReset()
        else
            p_View_Member(p_Get_Idx_Entity(id_option))
        endIf
    endFunction
    
    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_prev
            MCM.SetInfoText("Go to the Previous Page")
        elseIf id_option == p_option_next
            MCM.SetInfoText("Go to the Next Page")
        else
            int idx_entity = p_Get_Idx_Entity(id_option)
            doticu_npcp_member ref_member = p_arr_aliases[idx_entity] as doticu_npcp_member
            string str_name = ref_member.Get_Name()
            MCM.SetInfoText("Opens the member menu for " + str_name)
            ; this should show more about the member, like race, gender, style, and stats!!!
            ; whether is dead, healthly, etc. quick stats in other words
        endIf
    endFunction
endState

state p_STATE_MEMBER
    function f_Build_Page()
        if !p_ref_member || !p_ref_member.Exists()
            p_View_Members()
            return
        endIf

        string str_member_name = p_ref_member.Get_Name()
        p_is_settler = p_ref_member.Is_Settler()

        MCM.SetCursorPosition(0)
        MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

        MCM.SetTitleText("Member: " + str_member_name)

        p_option_rename = MCM.AddInputOption(str_member_name + " ", " Rename ")
        p_option_back = MCM.AddTextOption("                            Go Back", "")
        if MEMBERS.Get_Count() > 1
            p_option_prev = MCM.AddTextOption("                      Previous Member", "")
            p_option_next = MCM.AddTextOption("                        Next Member", "")
        else
            p_option_prev = MCM.AddTextOption("                      Previous Member", "", MCM.OPTION_FLAG_DISABLED)
            p_option_next = MCM.AddTextOption("                        Next Member", "", MCM.OPTION_FLAG_DISABLED)
        endIf
        p_options_offset = p_option_rename

        MCM.SetCursorPosition(4)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

        MCM.AddHeaderOption("Commands: ")

        p_option_summon = MCM.AddTextOption(CONSTS.STR_MCM_SUMMON, "")
        p_option_pack = MCM.AddTextOption(" Pack ", "")
        p_option_outfit = MCM.AddMenuOption(CONSTS.STR_MCM_OUTFIT, "")

        if p_ref_member.Is_Immobile()
            p_option_immobilize = MCM.AddTextOption(CONSTS.STR_MCM_IMMOBILIZE, "", MCM.OPTION_FLAG_DISABLED)
            p_option_mobilize = MCM.AddTextOption(CONSTS.STR_MCM_MOBILIZE, "", MCM.OPTION_FLAG_NONE)
        else
            p_option_immobilize = MCM.AddTextOption(CONSTS.STR_MCM_IMMOBILIZE, "", MCM.OPTION_FLAG_NONE)
            p_option_mobilize = MCM.AddTextOption(CONSTS.STR_MCM_MOBILIZE, "", MCM.OPTION_FLAG_DISABLED)
        endif

        if p_is_settler
            p_option_settle = MCM.AddTextOption(CONSTS.STR_MCM_SETTLE, "", MCM.OPTION_FLAG_DISABLED)
            p_option_resettle = MCM.AddTextOption(CONSTS.STR_MCM_RESETTLE, "", MCM.OPTION_FLAG_NONE)
            p_option_unsettle = MCM.AddTextOption(CONSTS.STR_MCM_UNSETTLE, "", MCM.OPTION_FLAG_NONE)
        else
            p_option_settle = MCM.AddTextOption(CONSTS.STR_MCM_SETTLE, "", MCM.OPTION_FLAG_NONE)
            p_option_resettle = MCM.AddTextOption(CONSTS.STR_MCM_RESETTLE, "", MCM.OPTION_FLAG_DISABLED)
            p_option_unsettle = MCM.AddTextOption(CONSTS.STR_MCM_UNSETTLE, "", MCM.OPTION_FLAG_DISABLED)
        endif

        p_option_clone = MCM.AddTextOption(" Clone ", "")
        if p_ref_member.Is_Clone()
            p_option_unclone = MCM.AddTextOption(" Unclone ", "")
        else
            p_option_unclone = MCM.AddTextOption(" Unclone ", "", MCM.OPTION_FLAG_DISABLED)
        endIf
        if !MEMBERS.Should_Unclone_Member(p_ref_member)
            p_option_unmember = MCM.AddTextOption(" Unmember ", "")
        else
            p_option_unmember = MCM.AddTextOption(" Unmember ", "", MCM.OPTION_FLAG_DISABLED)
        endIf

        MCM.SetCursorPosition(5)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

        Actor ref_actor = p_ref_member.Get_Actor()
        MCM.AddHeaderOption("Statistics: ")
        p_option_health = MCM.AddTextOption(" Health: ", ref_actor.GetActorValue(CONSTS.STR_HEALTH) as int)
        p_option_magicka = MCM.AddTextOption(" Magicka: ", ref_actor.GetActorValue(CONSTS.STR_MAGICKA) as int)
        p_option_stamina = MCM.AddTextOption(" Stamina: ", ref_actor.GetActorValue(CONSTS.STR_STAMINA) as int)
    endFunction

    function f_On_Option_Select(int id_option)
        Actor ref_actor = p_ref_member.Get_Actor()

        if id_option == p_option_back
            p_View_Members()
        elseIf id_option == p_option_prev
            p_ref_member = MEMBERS.Get_Prev_Member(p_ref_member)
            MCM.ForcePageReset()
        elseIf id_option == p_option_next
            p_ref_member = MEMBERS.Get_Next_Member(p_ref_member)
            MCM.ForcePageReset()
        elseIf id_option == p_option_summon
            COMMANDS.Summon_Async(ref_actor)
        elseIf id_option == p_option_pack
            FUNCS.Close_Menus()
            COMMANDS.Pack(ref_actor, false)
        elseIf id_option == p_option_immobilize
            COMMANDS.Immobilize_Sync(ref_actor, false)
            MCM.SetOptionFlags(p_option_immobilize, MCM.OPTION_FLAG_DISABLED, true)
            MCM.SetOptionFlags(p_option_mobilize, MCM.OPTION_FLAG_NONE, false)
        elseIf id_option == p_option_mobilize
            COMMANDS.Mobilize_Sync(ref_actor, false)
            MCM.SetOptionFlags(p_option_immobilize, MCM.OPTION_FLAG_NONE, true)
            MCM.SetOptionFlags(p_option_mobilize, MCM.OPTION_FLAG_DISABLED, false)
        elseIf id_option == p_option_settle
            COMMANDS.Settle_Async(ref_actor, false)
            MCM.SetOptionFlags(p_option_settle, MCM.OPTION_FLAG_DISABLED, true)
            MCM.SetOptionFlags(p_option_resettle, MCM.OPTION_FLAG_NONE, true)
            MCM.SetOptionFlags(p_option_unsettle, MCM.OPTION_FLAG_NONE, false)
            p_is_settler = true
        elseIf id_option == p_option_resettle
            COMMANDS.Resettle_Async(ref_actor, false)
            MCM.SetOptionFlags(p_option_settle, MCM.OPTION_FLAG_DISABLED, true)
            MCM.SetOptionFlags(p_option_resettle, MCM.OPTION_FLAG_NONE, true)
            MCM.SetOptionFlags(p_option_unsettle, MCM.OPTION_FLAG_NONE, false)
            p_is_settler = true
        elseIf id_option == p_option_unsettle
            COMMANDS.Unsettle_Async(ref_actor, false)
            MCM.SetOptionFlags(p_option_settle, MCM.OPTION_FLAG_NONE, true)
            MCM.SetOptionFlags(p_option_resettle, MCM.OPTION_FLAG_DISABLED, true)
            MCM.SetOptionFlags(p_option_unsettle, MCM.OPTION_FLAG_DISABLED, false)
            p_is_settler = false
        elseIf id_option == p_option_clone
            COMMANDS.Clone_Async(ref_actor)
        elseIf id_option == p_option_unclone
            ;p_ref_member.Unclone()
            COMMANDS.Unclone_Sync(ref_actor)
            p_View_Members()
        elseIf id_option == p_option_unmember
            ;p_ref_member.Unmember()
            COMMANDS.Unmember_Sync(ref_actor)
            p_View_Members()
        endIf
    endFunction

    function f_On_Option_Menu_Open(int id_option)
        if id_option == p_option_outfit
            if ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
                string[] arr_options = Utility.CreateStringArray(5, "")

                arr_options[0] = CONSTS.STR_MCM_CURRENT
                arr_options[1] = CONSTS.STR_MCM_MEMBER
                arr_options[2] = CONSTS.STR_MCM_SETTLER
                arr_options[3] = CONSTS.STR_MCM_THRALL
                arr_options[4] = CONSTS.STR_MCM_FOLLOWER
                arr_options[5] = CONSTS.STR_MCM_IMMOBILE

                MCM.SetMenuDialogOptions(arr_options)
            else
                string[] arr_options = Utility.CreateStringArray(4, "")

                arr_options[0] = CONSTS.STR_MCM_CURRENT
                arr_options[1] = CONSTS.STR_MCM_MEMBER
                arr_options[2] = CONSTS.STR_MCM_SETTLER
                arr_options[3] = CONSTS.STR_MCM_FOLLOWER
                arr_options[4] = CONSTS.STR_MCM_IMMOBILE

                MCM.SetMenuDialogOptions(arr_options)
            endIf
        endIf
    endFunction
    
    function f_On_Option_Menu_Accept(int id_option, int idx_option)
        Actor ref_actor = p_ref_member.Get_Actor()

        if id_option == p_option_outfit
            if ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
                if idx_option == 0
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Current(ref_actor, false)
                elseIf idx_option == 1
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Member(ref_actor, false)
                elseIf idx_option == 2
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Settler(ref_actor, false)
                elseIf idx_option == 3
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Thrall(ref_actor, false)
                elseIf idx_option == 4
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Follower(ref_actor, false)
                elseIf idx_option == 5
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Immobile(ref_actor, false)
                endIf
            else
                if idx_option == 0
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Current(ref_actor, false)
                elseIf idx_option == 1
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Member(ref_actor, false)
                elseIf idx_option == 2
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Settler(ref_actor, false)
                elseIf idx_option == 3
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Follower(ref_actor, false)
                elseIf idx_option == 4
                    FUNCS.Close_Menus()
                    COMMANDS.Outfit_Immobile(ref_actor, false)
                endIf
            endIf
        endIf
    endFunction

    function f_On_Option_Input_Accept(int id_option, string str_input)
        if id_option == p_option_rename
            if str_input != ""
                p_ref_member.Set_Name(str_input)
                MCM.ForcePageReset()
            endIf
        endIf
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_back
            MCM.SetInfoText("Go back to Members")
        elseIf id_option == p_option_prev
            MCM.SetInfoText("Go to the Previous Member")
        elseIf id_option == p_option_next
            MCM.SetInfoText("Go to the Next Member")
        elseIf id_option == p_option_pack
            MCM.SetInfoText("Pack items in this member's inventory.")
        elseIf id_option == p_option_outfit
            MCM.SetInfoText("Choose what this npc will wear in one of their outfits.")
        elseIf id_option == p_option_immobilize
            MCM.SetInfoText("Immobilize " + p_ref_member.Get_Name())
        elseIf id_option == p_option_mobilize
            MCM.SetInfoText("Mobilize " + p_ref_member.Get_Name())
        elseIf id_option == p_option_rename
            MCM.SetInfoText("Rename this member.")
        elseIf id_option == p_option_clone
            MCM.SetInfoText("Clone this member.")
        elseIf id_option == p_option_unclone
            MCM.SetInfoText("Unclone and unmember this member.")
        elseIf id_option == p_option_unmember
            MCM.SetInfoText("Unmember this member.")
        endIf
    endFunction
endState
