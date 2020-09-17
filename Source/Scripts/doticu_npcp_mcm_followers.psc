;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_followers extends Quest

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
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

; Private Constants
int property            p_HEADERS_PER_PAGE              =     2 autoReadOnly hidden

int property            p_COMMANDS_IN_MENU              =    11 autoReadOnly hidden
int property            p_COMMAND_ALL_SUMMON_ALL        =     0 autoReadOnly hidden
int property            p_COMMAND_ALL_SUMMON_MOBILE     =     1 autoReadOnly hidden
int property            p_COMMAND_ALL_SUMMON_IMMOBILE   =     2 autoReadOnly hidden
int property            p_COMMAND_ALL_IMMOBILIZE        =     3 autoReadOnly hidden
int property            p_COMMAND_ALL_MOBILIZE          =     4 autoReadOnly hidden
int property            p_COMMAND_ALL_SNEAK             =     5 autoReadOnly hidden
int property            p_COMMAND_ALL_UNSNEAK           =     6 autoReadOnly hidden
int property            p_COMMAND_ALL_SETTLE            =     7 autoReadOnly hidden
int property            p_COMMAND_ALL_UNSETTLE          =     8 autoReadOnly hidden
int property            p_COMMAND_ALL_UNFOLLOW          =     9 autoReadOnly hidden
int property            p_COMMAND_ALL_UNMEMBER          =    10 autoReadOnly hidden

int property            p_COMMANDS_PER_FOLLOWER         =     5 autoReadOnly hidden; count must include the name header
int property            p_COMMAND_ONE_NAME              =     0 autoReadOnly hidden
int property            p_COMMAND_ONE_SUMMON            =     1 autoReadOnly hidden
int property            p_COMMAND_ONE_PACK              =     2 autoReadOnly hidden
int property            p_COMMAND_ONE_IMMOBILIZE        =     3 autoReadOnly hidden
int property            p_COMMAND_ONE_MORE              =     4 autoReadOnly hidden

; Private Variables
bool                    p_is_created                = false
int                     p_code_view                 =     0

Alias[]                 p_arr_aliases               =  none
doticu_npcp_member      p_ref_member                =  none

bool                    p_do_prev_follower          = false
bool                    p_do_next_follower          = false

int                     p_options_offset            =    -1
int                     p_option_menu               =    -1

; Friend Methods
function f_Create()
    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Review_Followers()
    p_code_view = doticu_npcp_codes.VIEW_FOLLOWERS()
    p_ref_member = none
endFunction

bool function f_Is_Valid_Member(doticu_npcp_member ref_member)
    if !ref_member || !ref_member.Is_Filled() || !ref_member.Is_Follower()
        return false
    else
        return true
    endIf
endFunction

function f_Build_Page()
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        if f_Is_Valid_Member(p_ref_member)
            return p_Goto_Followers_Member(p_ref_member, true)
        else
            f_Review_Followers()
        endIf
    endIf

    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    int count_followers = FOLLOWERS.Count_Filled()
    int max_followers = 16;FOLLOWERS.Max()
    if count_followers == 0
        MCM.SetTitleText("Followers: 0/" + max_followers)
        MCM.AddHeaderOption(" No Followers ")
        return
    endIf

    MCM.SetTitleText("Followers: " + count_followers + "/" + max_followers)

    p_option_menu = MCM.AddMenuOption("Command All ", "...")
    MCM.AddEmptyOption()
    p_options_offset = p_option_menu

    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

    int idx = 0
    int cursor = p_HEADERS_PER_PAGE
    p_arr_aliases = FOLLOWERS.Get_Followers()
    while idx < p_arr_aliases.length
        doticu_npcp_follower ref_follower = p_arr_aliases[idx] as doticu_npcp_follower

        MCM.SetCursorPosition(cursor)

        MCM.AddHeaderOption(ref_follower.Name() + " ")
        MCM.AddTextOption("   Summon", "")
        MCM.AddTextOption("   Pack", "")
        if ref_follower.Is_Immobile()
            MCM.AddTextOption("   Mobilize", "")
        else
            MCM.AddTextOption("   Immobilize", "")
        endIf
        MCM.AddTextOption("   More", "...")

        if cursor % 2 == 0
            cursor += 1
        else
            cursor = cursor - 1 + p_COMMANDS_PER_FOLLOWER * 2
        endIf

        idx += 1
    endWhile
endFunction

function f_On_Option_Select(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Select(id_option)
    endIf

    int idx_entity = p_Get_Idx_Entity(id_option)
    if idx_entity < 0 || idx_entity >= p_arr_aliases.length
        return
    endIf
    int idx_command = p_Get_Idx_Command(id_option, idx_entity)

    doticu_npcp_follower ref_follower = p_arr_aliases[idx_entity] as doticu_npcp_follower
    Actor ref_actor = ref_follower.Actor()

    if false

    elseIf idx_command == p_COMMAND_ONE_SUMMON
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        COMMANDS.Summon(ref_actor)
        MCM.f_Enable(id_option, MCM.DO_UPDATE)

    elseIf idx_command == p_COMMAND_ONE_PACK
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        FUNCS.Close_Menus()
        COMMANDS.Open_Pack(ref_actor)

    elseIf idx_command == p_COMMAND_ONE_IMMOBILIZE
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        if ref_follower.Is_Immobile()
            COMMANDS.Mobilize(ref_actor)
        else
            COMMANDS.Immobilize(ref_actor)
        endIf
        MCM.Reset_Page()

    elseIf idx_command == p_COMMAND_ONE_MORE
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        return p_Goto_Followers_Member(ref_follower.Member() as doticu_npcp_member)

    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Menu_Open(id_option)
    endIf

    if id_option == p_option_menu
        string[] arr_options = Utility.CreateStringArray(p_COMMANDS_IN_MENU, "")

        arr_options[p_COMMAND_ALL_SUMMON_ALL] = " Summon All "
        arr_options[p_COMMAND_ALL_SUMMON_MOBILE] = " Summon Mobile "
        arr_options[p_COMMAND_ALL_SUMMON_IMMOBILE] = " Summon Immobile "
        arr_options[p_COMMAND_ALL_IMMOBILIZE] = " Immobilize "
        arr_options[p_COMMAND_ALL_MOBILIZE] = " Mobilize "
        arr_options[p_COMMAND_ALL_SNEAK] = " Sneak "
        arr_options[p_COMMAND_ALL_UNSNEAK] = " Unsneak "
        arr_options[p_COMMAND_ALL_SETTLE] = " Settle "
        arr_options[p_COMMAND_ALL_UNSETTLE] = " Unsettle "
        arr_options[p_COMMAND_ALL_UNFOLLOW] = " Unfollow "
        arr_options[p_COMMAND_ALL_UNMEMBER] = " Unmember "

        MCM.SetMenuDialogOptions(arr_options)
    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Menu_Accept(id_option, idx_option)
    endIf

    if id_option == p_option_menu
        if idx_option == p_COMMAND_ALL_SUMMON_ALL
            COMMANDS.Followers_Summon_All()
        elseIf idx_option == p_COMMAND_ALL_SUMMON_MOBILE
            COMMANDS.Followers_Summon_Mobile()
        elseIf idx_option == p_COMMAND_ALL_SUMMON_IMMOBILE
            COMMANDS.Followers_Summon_Immobile()
        elseIf idx_option == p_COMMAND_ALL_IMMOBILIZE
            COMMANDS.Followers_Immobilize()
        elseIf idx_option == p_COMMAND_ALL_MOBILIZE
            COMMANDS.Followers_Mobilize()
        elseIf idx_option == p_COMMAND_ALL_SNEAK
            COMMANDS.Followers_Sneak()
        elseIf idx_option == p_COMMAND_ALL_UNSNEAK
            COMMANDS.Followers_Unsneak()
        elseIf idx_option == p_COMMAND_ALL_SETTLE
            COMMANDS.Followers_Settle()
        elseIf idx_option == p_COMMAND_ALL_UNSETTLE
            COMMANDS.Followers_Unsettle()
        elseIf idx_option == p_COMMAND_ALL_UNFOLLOW
            COMMANDS.Followers_Unfollow()
        elseIf idx_option == p_COMMAND_ALL_UNMEMBER
            COMMANDS.Followers_Unmember()
        endIf
        MCM.Reset_Page()
    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Highlight(id_option)
    endIf

    if id_option == p_option_menu
        MCM.SetInfoText("Open the menu to command all followers.")
    else
        int idx_entity = p_Get_Idx_Entity(id_option)
        if idx_entity < 0 || idx_entity >= p_arr_aliases.length
            return
        endIf
        int idx_command = p_Get_Idx_Command(id_option, idx_entity)

        doticu_npcp_follower ref_follower = p_arr_aliases[idx_entity] as doticu_npcp_follower
        string name_follower = ref_follower.Name()

        if false

        elseIf idx_command == p_COMMAND_ONE_SUMMON
            MCM.SetInfoText("Summon " + name_follower + " to you.")
        elseIf idx_command == p_COMMAND_ONE_PACK
            MCM.SetInfoText("Open the pack of " + name_follower + ".")
        elseIf idx_command == p_COMMAND_ONE_IMMOBILIZE
            if ref_follower.Is_Immobile()
                MCM.SetInfoText("Mobilize " + name_follower + ".")
            else
                MCM.SetInfoText("Immobilize " + name_follower + ".")
            endIf
        elseIf idx_command == p_COMMAND_ONE_MORE
            MCM.SetInfoText("Open the follower menu of " + name_follower + ".")

        endIf
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Slider_Open(id_option)
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Slider_Accept(id_option, float_value)
    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Input_Accept(id_option, str_input)
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endFunction

function f_On_Option_Default(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        return MCM.MCM_MEMBER.On_Option_Default(id_option)
    endIf
endFunction

; Private Methods
doticu_npcp_member function p_Get_Prev_Member(doticu_npcp_member ref_member)
    if !p_arr_aliases
        return ref_member
    endIf

    int idx_alias = p_arr_aliases.Find(ref_member.Follower())
    if idx_alias > -1
        if idx_alias == 0
            return (p_arr_aliases[p_arr_aliases.length - 1] as doticu_npcp_follower).Member() as doticu_npcp_member
        else
            return (p_arr_aliases[idx_alias - 1] as doticu_npcp_follower).Member() as doticu_npcp_member
        endIf
    else
        return ref_member
    endIf
endFunction

doticu_npcp_member function p_Get_Next_Member(doticu_npcp_member ref_member)
    if !p_arr_aliases
        return ref_member
    endIf
    
    int idx_alias = p_arr_aliases.Find(ref_member.Follower())
    if idx_alias > -1
        if idx_alias == p_arr_aliases.length - 1
            return (p_arr_aliases[0] as doticu_npcp_follower).Member() as doticu_npcp_member
        else
            return (p_arr_aliases[idx_alias + 1] as doticu_npcp_follower).Member() as doticu_npcp_member
        endIf
    else
        return ref_member
    endIf
endFunction

function p_Goto_Followers_Member(doticu_npcp_member ref_member, bool is_building = false)
    if is_building
        if p_do_prev_follower
            ref_member = p_Get_Prev_Member(ref_member)
            p_ref_member = ref_member
            p_do_prev_follower = false
        elseIf p_do_next_follower
            ref_member = p_Get_Next_Member(ref_member)
            p_ref_member = ref_member
            p_do_next_follower = false
        endIf
        MCM.MCM_MEMBER.f_View_Followers_Member(ref_member)
        MCM.MCM_MEMBER.On_Build_Page()
    else
        p_code_view = doticu_npcp_codes.VIEW_FOLLOWERS_MEMBER()
        p_ref_member = ref_member
        MCM.MCM_MEMBER.f_View_Followers_Member(ref_member)
        MCM.Reset_Page()
    endIf
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
