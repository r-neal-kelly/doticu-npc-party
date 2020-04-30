;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_filter extends Quest

; Modules
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return p_DATA.MODS.CONTROL.MCM
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA                      =    none

; Private Variables
bool                p_is_created                =   false
int                 p_code_view                 =       0
int                 p_int_arg_flags             =       0
string[]            p_arr_race_names            =    none
string[]            p_arr_initial_letters       =    none
string              p_str_view_filter           =      ""

int                 p_option_filter             =      -1

string              p_str_arg_sex               =      ""
string              p_str_view_sex              = " Any "
int                 p_option_sex                =      -1

string              p_str_arg_race              =      ""
string              p_str_view_race             = " Any "
int                 p_option_race               =      -1

string              p_str_arg_initial_letter    =      ""
string              p_str_view_initial_letter   = " Any "
int                 p_option_initial_letter     =      -1

string              p_str_arg_search            =      ""
int                 p_option_search             =      -1

int                 p_int_alive_dead            =       0
int                 p_option_is_alive           =      -1
int                 p_option_is_dead            =      -1

int                 p_int_original_clone        =       0
int                 p_option_is_original        =      -1
int                 p_option_is_clone           =      -1

int                 p_int_follower              =       0
int                 p_option_is_follower        =      -1
int                 p_option_isnt_follower      =      -1

int                 p_int_settler               =       0
int                 p_option_is_settler         =      -1
int                 p_option_isnt_settler       =      -1

int                 p_int_immobile              =       0
int                 p_option_is_immobile        =      -1
int                 p_option_isnt_immobile      =      -1

int                 p_int_thrall                =       0
int                 p_option_is_thrall          =      -1
int                 p_option_isnt_thrall        =      -1

int                 p_int_paralyzed             =       0
int                 p_option_is_paralyzed       =      -1
int                 p_option_isnt_paralyzed     =      -1

int                 p_int_mannequin             =       0
int                 p_option_is_mannequin       =      -1
int                 p_option_isnt_mannequin     =      -1

int                 p_int_reanimated            =       0
int                 p_option_is_reanimated      =      -1
int                 p_option_isnt_reanimated    =      -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_code_view = 0
endFunction

function f_Destroy()
    p_code_view = 0
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Review_Filter()
    p_code_view = CODES.VIEW_FILTER
endFunction

string function f_Get_Filter_String()
    return p_str_view_filter
endFunction

function f_Build_Page()
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return p_Goto_Filter_Members()
    endIf

    MCM.SetTitleText(" Filter ")

    p_option_filter = MCM.AddTextOption(" Run Filter ", "")
    MCM.AddEmptyOption()
    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")

    p_option_sex = MCM.AddMenuOption(" Sex ", p_str_view_sex)
    p_option_race = MCM.AddMenuOption(" Race ", p_str_view_race)
    if p_str_arg_search == ""
        p_option_initial_letter = MCM.AddMenuOption(" Initial Letter ", p_str_view_initial_letter, MCM.FLAG_ENABLE)
    else
        p_option_initial_letter = MCM.AddMenuOption(" Initial Letter ", p_str_view_initial_letter, MCM.FLAG_DISABLE)
    endIf
    p_option_search = MCM.AddInputOption(" Search ", p_str_arg_search)

    p_option_is_alive = MCM.AddToggleOption(" Is Alive ", p_int_alive_dead == 1)
    p_option_is_dead = MCM.AddToggleOption(" Is Dead ", p_int_alive_dead == -1)

    p_option_is_original = MCM.AddToggleOption(" Is Original ", p_int_original_clone == 1)
    p_option_is_clone = MCM.AddToggleOption(" Is Clone ", p_int_original_clone == -1)

    p_option_is_follower = MCM.AddToggleOption(" Is Follower ", p_int_follower == 1)
    p_option_isnt_follower = MCM.AddToggleOption(" Isnt Follower ", p_int_follower == -1)

    p_option_is_settler = MCM.AddToggleOption(" Is Settler ", p_int_settler == 1)
    p_option_isnt_settler = MCM.AddToggleOption(" Isnt Settler ", p_int_settler == -1)

    p_option_is_immobile = MCM.AddToggleOption(" Is Immobile ", p_int_immobile == 1)
    p_option_isnt_immobile = MCM.AddToggleOption(" Isnt Immobile ", p_int_immobile == -1)

    p_option_is_thrall = MCM.AddToggleOption(" Is Thrall ", p_int_thrall == 1)
    p_option_isnt_thrall = MCM.AddToggleOption(" Isnt Thrall ", p_int_thrall == -1)

    p_option_is_paralyzed = MCM.AddToggleOption(" Is Paralyzed ", p_int_paralyzed == 1)
    p_option_isnt_paralyzed = MCM.AddToggleOption(" Isnt Paralyzed ", p_int_paralyzed == -1)

    p_option_is_mannequin = MCM.AddToggleOption(" Is Mannequin ", p_int_mannequin == 1)
    p_option_isnt_mannequin = MCM.AddToggleOption(" Isnt Mannequin ", p_int_mannequin == -1)

    p_option_is_reanimated= MCM.AddToggleOption(" Is Reanimated ", p_int_reanimated == 1)
    p_option_isnt_reanimated = MCM.AddToggleOption(" Isnt Reanimated ", p_int_reanimated == -1)

endFunction

function f_On_Option_Select(int id_option)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Select(id_option)
    endIf

    if false

    ; Filter
    elseIf id_option == p_option_filter
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_code_view = CODES.VIEW_FILTER_MEMBERS
        return MCM.ForcePageReset()

    ; Alive/Dead
    elseIf id_option == p_option_is_alive
        if p_int_alive_dead == 1
            p_int_alive_dead = 0
        else
            p_int_alive_dead = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_alive, p_int_alive_dead == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_is_dead, p_int_alive_dead == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_is_dead
        if p_int_alive_dead == -1
            p_int_alive_dead = 0
        else
            p_int_alive_dead = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_alive, p_int_alive_dead == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_is_dead, p_int_alive_dead == -1, MCM.DO_UPDATE)

    ; Original/Clone
    elseIf id_option == p_option_is_original
        if p_int_original_clone == 1
            p_int_original_clone = 0
        else
            p_int_original_clone = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_original, p_int_original_clone == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_is_clone, p_int_original_clone == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_is_clone
        if p_int_original_clone == -1
            p_int_original_clone = 0
        else
            p_int_original_clone = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_original, p_int_original_clone == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_is_clone, p_int_original_clone == -1, MCM.DO_UPDATE)

    ; Follower
    elseIf id_option == p_option_is_follower
        if p_int_follower == 1
            p_int_follower = 0
        else
            p_int_follower = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_follower, p_int_follower == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_follower, p_int_follower == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_isnt_follower
        if p_int_follower == -1
            p_int_follower = 0
        else
            p_int_follower = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_follower, p_int_follower == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_follower, p_int_follower == -1, MCM.DO_UPDATE)

    ; Settler
    elseIf id_option == p_option_is_settler
        if p_int_settler == 1
            p_int_settler = 0
        else
            p_int_settler = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_settler, p_int_settler == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_settler, p_int_settler == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_isnt_settler
        if p_int_settler == -1
            p_int_settler = 0
        else
            p_int_settler = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_settler, p_int_settler == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_settler, p_int_settler == -1, MCM.DO_UPDATE)

    ; Immobile
    elseIf id_option == p_option_is_immobile
        if p_int_immobile == 1
            p_int_immobile = 0
        else
            p_int_immobile = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_immobile, p_int_immobile == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_immobile, p_int_immobile == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_isnt_immobile
        if p_int_immobile == -1
            p_int_immobile = 0
        else
            p_int_immobile = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_immobile, p_int_immobile == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_immobile, p_int_immobile == -1, MCM.DO_UPDATE)

    ; Thrall
    elseIf id_option == p_option_is_thrall
        if p_int_thrall == 1
            p_int_thrall = 0
        else
            p_int_thrall = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_thrall, p_int_thrall == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_thrall, p_int_thrall == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_isnt_thrall
        if p_int_thrall == -1
            p_int_thrall = 0
        else
            p_int_thrall = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_thrall, p_int_thrall == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_thrall, p_int_thrall == -1, MCM.DO_UPDATE)

    ; Paralyzed
    elseIf id_option == p_option_is_paralyzed
        if p_int_paralyzed == 1
            p_int_paralyzed = 0
        else
            p_int_paralyzed = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_paralyzed, p_int_paralyzed == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_paralyzed, p_int_paralyzed == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_isnt_paralyzed
        if p_int_paralyzed == -1
            p_int_paralyzed = 0
        else
            p_int_paralyzed = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_paralyzed, p_int_paralyzed == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_paralyzed, p_int_paralyzed == -1, MCM.DO_UPDATE)

    ; Mannequin
    elseIf id_option == p_option_is_mannequin
        if p_int_mannequin == 1
            p_int_mannequin = 0
        else
            p_int_mannequin = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_mannequin, p_int_mannequin == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_mannequin, p_int_mannequin == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_isnt_mannequin
        if p_int_mannequin == -1
            p_int_mannequin = 0
        else
            p_int_mannequin = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_mannequin, p_int_mannequin == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_mannequin, p_int_mannequin == -1, MCM.DO_UPDATE)

    ; Reanimated
    elseIf id_option == p_option_is_reanimated
        if p_int_reanimated == 1
            p_int_reanimated = 0
        else
            p_int_reanimated = 1
        endIf
        MCM.SetToggleOptionValue(p_option_is_reanimated, p_int_reanimated == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_reanimated, p_int_reanimated == -1, MCM.DO_UPDATE)
    elseIf id_option == p_option_isnt_reanimated
        if p_int_reanimated == -1
            p_int_reanimated = 0
        else
            p_int_reanimated = -1
        endIf
        MCM.SetToggleOptionValue(p_option_is_reanimated, p_int_reanimated == 1, MCM.DONT_UPDATE)
        MCM.SetToggleOptionValue(p_option_isnt_reanimated, p_int_reanimated == -1, MCM.DO_UPDATE)

    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Menu_Open(id_option)
    endIf

    if false

    elseIf id_option == p_option_sex
        string[] arr_options = Utility.CreateStringArray(4, "")

        arr_options[0] = " Any "
        arr_options[1] = " Male "
        arr_options[2] = " Female "
        arr_options[3] = " None "

        MCM.SetMenuDialogOptions(arr_options)
        MCM.SetMenuDialogDefaultIndex(0)

    elseIf id_option == p_option_race
        p_arr_race_names = doticu_npcp.Aliases_Get_Race_Names(MEMBERS.Get_Members())

        int num_race_names
        if p_arr_race_names[0] == ""
            num_race_names = 0
        else
            num_race_names = p_arr_race_names.length
        endIf

        string[] arr_options = Utility.CreateStringArray(num_race_names + 1, "")
        arr_options[0] = " Any "

        int idx_race_names = 0
        while idx_race_names < num_race_names
            arr_options[idx_race_names + 1] = p_arr_race_names[idx_race_names]
            idx_race_names += 1
        endWhile

        MCM.SetMenuDialogOptions(arr_options)
        MCM.SetMenuDialogDefaultIndex(0)

    elseIf id_option == p_option_initial_letter
        p_arr_initial_letters = doticu_npcp.Aliases_Get_Initial_Letters(MEMBERS.Get_Members())

        int num_letters
        if p_arr_initial_letters[0] == ""
            num_letters = 0
        else
            num_letters = p_arr_initial_letters.length
        endIf

        string[] arr_options = Utility.CreateStringArray(num_letters + 1, "")
        arr_options[0] = " Any "

        int idx_letters = 0
        while idx_letters < num_letters
            arr_options[idx_letters + 1] = p_arr_initial_letters[idx_letters]
            idx_letters += 1
        endWhile

        MCM.SetMenuDialogOptions(arr_options)
        MCM.SetMenuDialogDefaultIndex(0)

    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf

    if false

    elseIf id_option == p_option_sex
        if idx_option < 0

        elseIf idx_option == 0
            p_str_arg_sex = ""
            p_str_view_sex = " Any "
        elseIf idx_option == 1
            p_str_arg_sex = "Male"
            p_str_view_sex = " Male "
        elseIf idx_option == 2
            p_str_arg_sex = "Female"
            p_str_view_sex = " Female "
        elseIf idx_option == 3
            p_str_arg_sex = "None"
            p_str_view_sex = " None "

        endIf
        MCM.SetMenuOptionValue(id_option, p_str_view_sex, MCM.DO_UPDATE)

    elseIf id_option == p_option_race
        if idx_option < 0

        elseIf idx_option == 0
            p_str_arg_race = ""
            p_str_view_race = " Any "
        else
            p_str_arg_race = p_arr_race_names[idx_option - 1]
            p_str_view_race = p_str_arg_race

        endIf
        MCM.SetMenuOptionValue(id_option, p_str_view_race, MCM.DO_UPDATE)

    elseIf id_option == p_option_initial_letter
        if idx_option < 0

        elseIf idx_option == 0
            p_str_arg_initial_letter = ""
            p_str_view_initial_letter = " Any "
        else
            p_str_arg_initial_letter = p_arr_initial_letters[idx_option - 1]
            p_str_view_initial_letter = p_str_arg_initial_letter

        endIf
        MCM.SetMenuOptionValue(id_option, p_str_view_initial_letter, MCM.DO_UPDATE)

    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Input_Accept(id_option, str_input)
    endIf

    if false

    elseIf id_option == p_option_search
        if str_input == ""
            MCM.f_Enable(p_option_initial_letter, MCM.DONT_UPDATE)
        else
            MCM.f_Disable(p_option_initial_letter, MCM.DONT_UPDATE)
        endIf
        p_str_arg_search = str_input
        MCM.SetInputOptionValue(p_option_search, p_str_arg_search, MCM.DO_UPDATE)

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Highlight(id_option)
    endIf

    if false
    
    elseIf id_option == p_option_filter
        MCM.SetInfoText("Execute the filter with all currently selected options.")
    elseIf id_option == p_option_sex
        MCM.SetInfoText("Find members with this sex.")
    elseIf id_option == p_option_race
        MCM.SetInfoText("Find members with this race.")
    elseIf id_option == p_option_initial_letter
        MCM.SetInfoText("Find members whose name starts with this letter.")
    elseIf id_option == p_option_search
        MCM.SetInfoText("Find members whose name contains this input. (If just one character, it only looks at the start of the name.)")
    elseIf id_option == p_option_is_alive
        MCM.SetInfoText("Find members who are alive.")
    elseIf id_option == p_option_is_dead
        MCM.SetInfoText("Find members who are dead.")
    elseIf id_option == p_option_is_original
        MCM.SetInfoText("Find members who are original, as opposed to clones.")
    elseIf id_option == p_option_is_clone
        MCM.SetInfoText("Find members who are clones, as opposed to originals.")
    elseIf id_option == p_option_is_follower
        MCM.SetInfoText("Find members who are followers.")
    elseIf id_option == p_option_isnt_follower
        MCM.SetInfoText("Find members who are not followers.")
    elseIf id_option == p_option_is_settler
        MCM.SetInfoText("Find members who are settlers.")
    elseIf id_option == p_option_isnt_settler
        MCM.SetInfoText("Find members who are not settlers.")
    elseIf id_option == p_option_is_immobile
        MCM.SetInfoText("Find members who are immobile.")
    elseIf id_option == p_option_isnt_immobile
        MCM.SetInfoText("Find members who are not immobile.")
    elseIf id_option == p_option_is_thrall
        MCM.SetInfoText("Find members who are thralls.")
    elseIf id_option == p_option_isnt_thrall
        MCM.SetInfoText("Find members who are not thralls.")
    elseIf id_option == p_option_is_paralyzed
        MCM.SetInfoText("Find members who are paralyzed.")
    elseIf id_option == p_option_isnt_paralyzed
        MCM.SetInfoText("Find members who are not paralyzed.")
    elseIf id_option == p_option_is_mannequin
        MCM.SetInfoText("Find members who are mannequins.")
    elseIf id_option == p_option_isnt_mannequin
        MCM.SetInfoText("Find members who are not mannequins.")
    elseIf id_option == p_option_is_reanimated
        MCM.SetInfoText("Find members who are reanimated.")
    elseIf id_option == p_option_isnt_reanimated
        MCM.SetInfoText("Find members who are not reanimated.")

    endIf
endFunction

function f_On_Option_Default(int id_option)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Default(id_option)
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Slider_Open(id_option)
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_code_view == CODES.VIEW_FILTER_MEMBERS
        return MCM.MCM_MEMBERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endFunction

; Private Methods
function p_Concat_Filter_String_Param(string str_param)
    if p_str_view_filter == ""
        p_str_view_filter = str_param
    else
        p_str_view_filter += ", " + str_param
    endIf
endFunction

function p_Goto_Filter_Members()
    string str_arg_search = ""
    p_str_view_filter = ""
    p_int_arg_flags = 0

    if p_str_arg_sex
        p_Concat_Filter_String_Param(p_str_view_sex)
    endIf
    if p_str_arg_race
        p_Concat_Filter_String_Param(p_str_view_race)
    endIf
    if p_str_arg_search
        str_arg_search = p_str_arg_search
        p_Concat_Filter_String_Param("'" + p_str_arg_search + "'")
    elseIf p_str_arg_initial_letter
        str_arg_search = p_str_arg_initial_letter
        p_Concat_Filter_String_Param("'" + p_str_arg_initial_letter + "'")
    endIf

    if p_int_alive_dead == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_ALIVE")
        p_Concat_Filter_String_Param("Alive")
    elseIf p_int_alive_dead == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_DEAD")
        p_Concat_Filter_String_Param("Dead")
    endIf

    if p_int_original_clone == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_ORIGINAL")
        p_Concat_Filter_String_Param("Original")
    elseIf p_int_original_clone == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_CLONE")
        p_Concat_Filter_String_Param("Clone")
    endIf

    if p_int_follower == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_FOLLOWER")
        p_Concat_Filter_String_Param("Follower")
    elseIf p_int_follower == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "ISNT_FOLLOWER")
        p_Concat_Filter_String_Param("!Follower")
    endIf

    if p_int_settler == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_SETTLER")
        p_Concat_Filter_String_Param("Settler")
    elseIf p_int_settler == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "ISNT_SETTLER")
        p_Concat_Filter_String_Param("!Settler")
    endIf

    if p_int_immobile == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_IMMOBILE")
        p_Concat_Filter_String_Param("Immobile")
    elseIf p_int_immobile == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "ISNT_IMMOBILE")
        p_Concat_Filter_String_Param("!Immobile")
    endIf

    if p_int_thrall == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_THRALL")
        p_Concat_Filter_String_Param("Thrall")
    elseIf p_int_thrall == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "ISNT_THRALL")
        p_Concat_Filter_String_Param("!Thrall")
    endIf

    if p_int_paralyzed == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_PARALYZED")
        p_Concat_Filter_String_Param("Paralyzed")
    elseIf p_int_paralyzed == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "ISNT_PARALYZED")
        p_Concat_Filter_String_Param("!Paralyzed")
    endIf

    if p_int_mannequin == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_MANNEQUIN")
        p_Concat_Filter_String_Param("Mannequin")
    elseIf p_int_mannequin == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "ISNT_MANNEQUIN")
        p_Concat_Filter_String_Param("!Mannequin")
    endIf

    if p_int_reanimated == 1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "IS_REANIMATED")
        p_Concat_Filter_String_Param("Reanimated")
    elseIf p_int_reanimated == -1
        p_int_arg_flags = doticu_npcp.Aliases_Filter_Flag(p_int_arg_flags, "SET", "ISNT_REANIMATED")
        p_Concat_Filter_String_Param("!Reanimated")
    endIf

    if p_str_view_filter == ""
        p_str_view_filter = " All Members "
    endIf

    Alias[] arr_filter = doticu_npcp.Aliases_Filter(MEMBERS.Get_Members(), p_str_arg_sex, p_str_arg_race, str_arg_search, p_int_arg_flags)

    MCM.MCM_MEMBERS.f_View_Filter_Members(arr_filter)
    MCM.MCM_MEMBERS.f_Build_Page()
endFunction
