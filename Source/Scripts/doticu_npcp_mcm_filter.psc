;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_filter extends Quest

; Modules
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
string              p_str_view_filter           =      ""

int                 p_option_filter             =      -1

string              p_str_arg_sex               =      ""
string              p_str_view_sex              = " Any "
int                 p_option_sex                =      -1

string              p_str_arg_race              =      ""
string              p_str_view_race             = " Any "
int                 p_option_race               =      -1

string              p_str_arg_search            =      ""
int                 p_option_search             =      -1

int                 p_int_arg_style             =       0
string              p_str_view_style            = " Any "
int                 p_option_style              =      -1

int                 p_int_arg_vitality          =       0
string              p_str_view_vitality         = " Any "
int                 p_option_vitality           =      -1

int                 p_int_arg_outfit2           =       0
string              p_str_view_outfit2          = " Any "
int                 p_option_outfit2            =      -1

int                 p_int_arg_rating            =      -1
string              p_str_view_rating           = " Any "
int                 p_option_rating             =      -1

int                 p_int_alive_dead            =       0
int                 p_option_is_alive           =      -1
int                 p_option_is_dead            =      -1

int                 p_int_original_clone        =       0
int                 p_option_is_original        =      -1
int                 p_option_is_clone           =      -1

int                 p_int_unique_generic        =       0
int                 p_option_is_unique          =      -1
int                 p_option_is_generic         =      -1

int                 p_int_mobile_immobile       =       0
int                 p_option_is_mobile          =      -1
int                 p_option_is_immobile        =      -1

int                 p_int_settler               =       0
int                 p_option_is_settler         =      -1
int                 p_option_isnt_settler       =      -1

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

int                 p_int_follower              =       0
int                 p_option_is_follower        =      -1
int                 p_option_isnt_follower      =      -1

int                 p_int_sneak                 =       0
int                 p_option_is_sneak           =      -1
int                 p_option_isnt_sneak         =      -1

int                 p_int_saddler               =       0
int                 p_option_is_saddler         =      -1
int                 p_option_isnt_saddler       =      -1

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
    p_code_view = doticu_npcp_codes.VIEW_FILTER()
endFunction

string function f_Get_Filter_String()
    return p_str_view_filter
endFunction

function f_Build_Page()
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return p_Goto_Filter_Members()
    endIf

    MCM.SetTitleText(" Filter ")

    p_option_filter = MCM.AddTextOption(" Run Filter ", "")
    p_option_search = MCM.AddInputOption(" Search ", p_str_arg_search)
    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")

    p_option_sex = MCM.AddMenuOption(" Sex ", p_str_view_sex)
    p_option_race = MCM.AddMenuOption(" Race ", p_str_view_race)

    p_option_style = MCM.AddMenuOption(" Style ", p_str_view_style)
    p_option_vitality = MCM.AddMenuOption(" Vitality ", p_str_view_vitality)

    p_option_outfit2 = MCM.AddMenuOption(" Outfit ", p_str_view_outfit2)
    p_option_rating = MCM.AddMenuOption(" Rating ", p_str_view_rating)
    
    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")
    
    p_option_is_alive = MCM.AddToggleOption(" Is Alive ", p_int_alive_dead == 1)
    p_option_is_dead = MCM.AddToggleOption(" Is Dead ", p_int_alive_dead == -1)

    p_option_is_original = MCM.AddToggleOption(" Is Original ", p_int_original_clone == 1)
    p_option_is_clone = MCM.AddToggleOption(" Is Clone ", p_int_original_clone == -1)

    p_option_is_unique = MCM.AddToggleOption(" Is Unique ", p_int_unique_generic == 1)
    p_option_is_generic = MCM.AddToggleOption(" Is Generic ", p_int_unique_generic == -1)

    p_option_is_mobile = MCM.AddToggleOption(" Is Mobile ", p_int_mobile_immobile == 1)
    p_option_is_immobile = MCM.AddToggleOption(" Is Immobile ", p_int_mobile_immobile == -1)

    p_option_is_settler = MCM.AddToggleOption(" Is Settler ", p_int_settler == 1)
    p_option_isnt_settler = MCM.AddToggleOption(" Isnt Settler ", p_int_settler == -1)

    p_option_is_thrall = MCM.AddToggleOption(" Is Thrall ", p_int_thrall == 1)
    p_option_isnt_thrall = MCM.AddToggleOption(" Isnt Thrall ", p_int_thrall == -1)

    p_option_is_paralyzed = MCM.AddToggleOption(" Is Paralyzed ", p_int_paralyzed == 1)
    p_option_isnt_paralyzed = MCM.AddToggleOption(" Isnt Paralyzed ", p_int_paralyzed == -1)

    p_option_is_mannequin = MCM.AddToggleOption(" Is Mannequin ", p_int_mannequin == 1)
    p_option_isnt_mannequin = MCM.AddToggleOption(" Isnt Mannequin ", p_int_mannequin == -1)

    p_option_is_reanimated= MCM.AddToggleOption(" Is Reanimated ", p_int_reanimated == 1)
    p_option_isnt_reanimated = MCM.AddToggleOption(" Isnt Reanimated ", p_int_reanimated == -1)

    p_option_is_follower = MCM.AddToggleOption(" Is Follower ", p_int_follower == 1)
    p_option_isnt_follower = MCM.AddToggleOption(" Isnt Follower ", p_int_follower == -1)

    p_option_is_sneak = MCM.AddToggleOption(" Is Sneak ", p_int_sneak == 1)
    p_option_isnt_sneak = MCM.AddToggleOption(" Isnt Sneak ", p_int_sneak == -1)

    p_option_is_saddler = MCM.AddToggleOption(" Is Saddler ", p_int_saddler == 1)
    p_option_isnt_saddler = MCM.AddToggleOption(" Isnt Saddler ", p_int_saddler == -1)

endFunction

function f_On_Option_Select(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.MCM_MEMBERS.f_On_Option_Select(id_option)
    endIf

    if false

    ; Filter
    elseIf id_option == p_option_filter
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_code_view = doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.ForcePageReset()

    ; Alive/Dead
    elseIf id_option == p_option_is_alive
        p_int_alive_dead = p_Toggle_Between(p_int_alive_dead, 1, 0)
        p_Update_Alive_Dead()
    elseIf id_option == p_option_is_dead
        p_int_alive_dead = p_Toggle_Between(p_int_alive_dead, -1, 0)
        p_Update_Alive_Dead()

    ; Original/Clone
    elseIf id_option == p_option_is_original
        p_int_original_clone = p_Toggle_Between(p_int_original_clone, 1, 0)
        p_Update_Original_Clone()
    elseIf id_option == p_option_is_clone
        p_int_original_clone = p_Toggle_Between(p_int_original_clone, -1, 0)
        p_Update_Original_Clone()

    ; Unique/Generic
    elseIf id_option == p_option_is_unique
        p_int_unique_generic = p_Toggle_Between(p_int_unique_generic, 1, 0)
        p_Update_Unique_Generic()
    elseIf id_option == p_option_is_generic
        p_int_unique_generic = p_Toggle_Between(p_int_unique_generic, -1, 0)
        p_Update_Unique_Generic()

    ; Mobile/Immobile
    elseIf id_option == p_option_is_mobile
        p_int_mobile_immobile = p_Toggle_Between(p_int_mobile_immobile, 1, 0)
        p_Update_Mobile_Immobile()
    elseIf id_option == p_option_is_immobile
        p_int_mobile_immobile = p_Toggle_Between(p_int_mobile_immobile, -1, 0)
        p_Update_Mobile_Immobile()

    ; Settler
    elseIf id_option == p_option_is_settler
        p_int_settler = p_Toggle_Between(p_int_settler, 1, 0)
        p_Update_Settler()
    elseIf id_option == p_option_isnt_settler
        p_int_settler = p_Toggle_Between(p_int_settler, -1, 0)
        p_Update_Settler()

    ; Thrall
    elseIf id_option == p_option_is_thrall
        p_int_thrall = p_Toggle_Between(p_int_thrall, 1, 0)
        p_Update_Thrall()
    elseIf id_option == p_option_isnt_thrall
        p_int_thrall = p_Toggle_Between(p_int_thrall, -1, 0)
        p_Update_Thrall()

    ; Paralyzed
    elseIf id_option == p_option_is_paralyzed
        p_int_paralyzed = p_Toggle_Between(p_int_paralyzed, 1, 0)
        p_Update_Paralyzed()
    elseIf id_option == p_option_isnt_paralyzed
        p_int_paralyzed = p_Toggle_Between(p_int_paralyzed, -1, 0)
        p_Update_Paralyzed()

    ; Mannequin
    elseIf id_option == p_option_is_mannequin
        p_int_mannequin = p_Toggle_Between(p_int_mannequin, 1, 0)
        p_Update_Mannequin()
    elseIf id_option == p_option_isnt_mannequin
        p_int_mannequin = p_Toggle_Between(p_int_mannequin, -1, 0)
        p_Update_Mannequin()

    ; Reanimated
    elseIf id_option == p_option_is_reanimated
        p_int_reanimated = p_Toggle_Between(p_int_reanimated, 1, 0)
        p_Update_Reanimated()
    elseIf id_option == p_option_isnt_reanimated
        p_int_reanimated = p_Toggle_Between(p_int_reanimated, -1, 0)
        p_Update_Reanimated()

    ; Follower
    elseIf id_option == p_option_is_follower
        p_int_follower = p_Toggle_Between(p_int_follower, 1, 0)
        p_Update_Follower()
    elseIf id_option == p_option_isnt_follower
        p_int_follower = p_Toggle_Between(p_int_follower, -1, 0)
        p_Update_Follower()

    ; Sneak
    elseIf id_option == p_option_is_sneak
        p_int_sneak = p_Toggle_Between(p_int_sneak, 1, 0)
        p_Update_Sneak()
    elseIf id_option == p_option_isnt_sneak
        p_int_sneak = p_Toggle_Between(p_int_sneak, -1, 0)
        p_Update_Sneak()

    ; Saddler
    elseIf id_option == p_option_is_saddler
        p_int_saddler = p_Toggle_Between(p_int_saddler, 1, 0)
        p_Update_Saddler()
    elseIf id_option == p_option_isnt_saddler
        p_int_saddler = p_Toggle_Between(p_int_saddler, -1, 0)
        p_Update_Saddler()

    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
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
        p_arr_race_names = MEMBERS.Race_Names()

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

    elseIf id_option == p_option_style
        string[] arr_options = Utility.CreateStringArray(6, "")

        arr_options[0] = " Any "
        arr_options[1] = " Default "
        arr_options[2] = " Warrior "
        arr_options[3] = " Mage "
        arr_options[4] = " Archer "
        arr_options[5] = " Coward "

        MCM.SetMenuDialogOptions(arr_options)
        MCM.SetMenuDialogDefaultIndex(0)
    
    elseIf id_option == p_option_vitality
        string[] arr_options = Utility.CreateStringArray(5, "")

        arr_options[0] = " Any "
        arr_options[1] = " Mortal "
        arr_options[2] = " Protected "
        arr_options[3] = " Essential "
        arr_options[4] = " Invulnerable "

        MCM.SetMenuDialogOptions(arr_options)
        MCM.SetMenuDialogDefaultIndex(0)

    elseIf id_option == p_option_outfit2
        string[] arr_options = Utility.CreateStringArray(8, "")

        arr_options[0] = " Any "
        arr_options[1] = " Member "
        arr_options[2] = " Settler "
        arr_options[3] = " Thrall "
        arr_options[4] = " Immobile "
        arr_options[5] = " Follower "
        arr_options[6] = " Vanilla "
        arr_options[7] = " Default "

        MCM.SetMenuDialogOptions(arr_options)
        MCM.SetMenuDialogDefaultIndex(0)

    elseIf id_option == p_option_rating
        string[] arr_options = Utility.CreateStringArray(7, "")

        arr_options[0] = " Any "
        arr_options[1] = " - "
        arr_options[2] = " * "
        arr_options[3] = " ** "
        arr_options[4] = " *** "
        arr_options[5] = " **** "
        arr_options[6] = " ***** "

        MCM.SetMenuDialogOptions(arr_options)
        MCM.SetMenuDialogDefaultIndex(0)

    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
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

    elseIf id_option == p_option_style
        if idx_option < 0

        elseIf idx_option == 0
            p_int_arg_style = 0
            p_str_view_style = " Any "
        elseIf idx_option == 1
            p_int_arg_style = doticu_npcp_codes.STYLE_DEFAULT()
            p_str_view_style = " Default "
        elseIf idx_option == 2
            p_int_arg_style = doticu_npcp_codes.STYLE_WARRIOR()
            p_str_view_style = " Warrior "
        elseIf idx_option == 3
            p_int_arg_style = doticu_npcp_codes.STYLE_MAGE()
            p_str_view_style = " Mage "
        elseIf idx_option == 4
            p_int_arg_style = doticu_npcp_codes.STYLE_ARCHER()
            p_str_view_style = " Archer "
        elseIf idx_option == 5
            p_int_arg_style = doticu_npcp_codes.STYLE_COWARD()
            p_str_view_style = " Coward "

        endIf
        MCM.SetMenuOptionValue(id_option, p_str_view_style, MCM.DO_UPDATE)

    elseIf id_option == p_option_vitality
        if idx_option < 0

        elseIf idx_option == 0
            p_int_arg_vitality = 0
            p_str_view_vitality = " Any "
        elseIf idx_option == 1
            p_int_arg_vitality = doticu_npcp_codes.VITALITY_MORTAL()
            p_str_view_vitality = " Mortal "
        elseIf idx_option == 2
            p_int_arg_vitality = doticu_npcp_codes.VITALITY_PROTECTED()
            p_str_view_vitality = " Protected "
        elseIf idx_option == 3
            p_int_arg_vitality = doticu_npcp_codes.VITALITY_ESSENTIAL()
            p_str_view_vitality = " Essential "
        elseIf idx_option == 4
            p_int_arg_vitality = doticu_npcp_codes.VITALITY_INVULNERABLE()
            p_str_view_vitality = " Invulnerable "

        endIf
        MCM.SetMenuOptionValue(id_option, p_str_view_vitality, MCM.DO_UPDATE)

    elseIf id_option == p_option_outfit2
        if idx_option < 0

        elseIf idx_option == 0
            p_int_arg_outfit2 = 0
            p_str_view_outfit2 = " Any "
        elseIf idx_option == 1
            p_int_arg_outfit2 = doticu_npcp_codes.OUTFIT2_MEMBER()
            p_str_view_outfit2 = " Member "
        elseIf idx_option == 2
            p_int_arg_outfit2 = doticu_npcp_codes.OUTFIT2_SETTLER()
            p_str_view_outfit2 = " Settler "
        elseIf idx_option == 3
            p_int_arg_outfit2 = doticu_npcp_codes.OUTFIT2_THRALL()
            p_str_view_outfit2 = " Thrall "
        elseIf idx_option == 4
            p_int_arg_outfit2 = doticu_npcp_codes.OUTFIT2_IMMOBILE()
            p_str_view_outfit2 = " Immobile "
        elseIf idx_option == 5
            p_int_arg_outfit2 = doticu_npcp_codes.OUTFIT2_FOLLOWER()
            p_str_view_outfit2 = " Follower "
        elseIf idx_option == 6
            p_int_arg_outfit2 = doticu_npcp_codes.OUTFIT2_VANILLA()
            p_str_view_outfit2 = " Vanilla "
        elseIf idx_option == 7
            p_int_arg_outfit2 = doticu_npcp_codes.OUTFIT2_DEFAULT()
            p_str_view_outfit2 = " Default "

        endIf
        MCM.SetMenuOptionValue(id_option, p_str_view_outfit2, MCM.DO_UPDATE)

    elseIf id_option == p_option_rating
        if idx_option < 0

        elseIf idx_option == 0
            p_int_arg_rating = -1
            p_str_view_rating = " Any "
        elseIf idx_option == 1
            p_int_arg_rating = 0
            p_str_view_rating = " - "
        elseIf idx_option == 2
            p_int_arg_rating = 1
            p_str_view_rating = " * "
        elseIf idx_option == 3
            p_int_arg_rating = 2
            p_str_view_rating = " ** "
        elseIf idx_option == 4
            p_int_arg_rating = 3
            p_str_view_rating = " *** "
        elseIf idx_option == 5
            p_int_arg_rating = 4
            p_str_view_rating = " **** "
        elseIf idx_option == 6
            p_int_arg_rating = 5
            p_str_view_rating = " ***** "

        endIf
        MCM.SetMenuOptionValue(id_option, p_str_view_rating, MCM.DO_UPDATE)

    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.MCM_MEMBERS.f_On_Option_Input_Accept(id_option, str_input)
    endIf

    if false

    elseIf id_option == p_option_search
        p_str_arg_search = str_input
        MCM.SetInputOptionValue(p_option_search, p_str_arg_search, MCM.DO_UPDATE)

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.MCM_MEMBERS.f_On_Option_Highlight(id_option)
    endIf

    if false
    
    elseIf id_option == p_option_filter
        MCM.SetInfoText("Execute the filter with all currently selected options.")
    elseIf id_option == p_option_sex
        MCM.SetInfoText("Find members with this sex.")
    elseIf id_option == p_option_race
        MCM.SetInfoText("Find members with this race.")
    elseIf id_option == p_option_style
        MCM.SetInfoText("Find members with this style.")
    elseIf id_option == p_option_vitality
        MCM.SetInfoText("Find members with this vitality.")
    elseIf id_option == p_option_outfit2
        MCM.SetInfoText("Find members wearing this outfit.")
    elseIf id_option == p_option_rating
        MCM.SetInfoText("Find members with this rating.")
    elseIf id_option == p_option_search
        MCM.SetInfoText("Find members whose name contains this input. (If just one character, it only looks at the start of the name.)")
    elseIf id_option == p_option_is_alive
        MCM.SetInfoText("Find members who are alive.")
    elseIf id_option == p_option_is_dead
        MCM.SetInfoText("Find members who are dead.")
    elseIf id_option == p_option_is_original
        MCM.SetInfoText("Find members who are originals, as opposed to clones.")
    elseIf id_option == p_option_is_clone
        MCM.SetInfoText("Find members who are clones, as opposed to originals.")
    elseIf id_option == p_option_is_unique
        MCM.SetInfoText("Find members who are unique.")
    elseIf id_option == p_option_is_generic
        MCM.SetInfoText("Find members who are generic.")
    elseIf id_option == p_option_is_mobile
        MCM.SetInfoText("Find members who are mobile.")
    elseIf id_option == p_option_is_immobile
        MCM.SetInfoText("Find members who are immobile.")
    elseIf id_option == p_option_is_settler
        MCM.SetInfoText("Find members who are settlers.")
    elseIf id_option == p_option_isnt_settler
        MCM.SetInfoText("Find members who are not settlers.")
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
    elseIf id_option == p_option_is_follower
        MCM.SetInfoText("Find members who are followers.")
    elseIf id_option == p_option_isnt_follower
        MCM.SetInfoText("Find members who are not followers.")
    elseIf id_option == p_option_is_sneak
        MCM.SetInfoText("Find members who are sneaking followers.")
    elseIf id_option == p_option_isnt_sneak
        MCM.SetInfoText("Find members who are not sneaking followers.")
    elseIf id_option == p_option_is_saddler
        MCM.SetInfoText("Find members who are horse riding followers.")
    elseIf id_option == p_option_isnt_saddler
        MCM.SetInfoText("Find members who are not horse riding followers.")

    endIf
endFunction

function f_On_Option_Default(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.MCM_MEMBERS.f_On_Option_Default(id_option)
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.MCM_MEMBERS.f_On_Option_Slider_Open(id_option)
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.MCM_MEMBERS.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_code_view == doticu_npcp_codes.VIEW_FILTER_MEMBERS()
        return MCM.MCM_MEMBERS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endFunction

; Private Methods
int function p_Toggle_Between(int subject, int a, int b)
    if subject == a
        return b
    else
        return a
    endIf
endFunction

function p_Update_Alive_Dead()
    MCM.SetToggleOptionValue(p_option_is_alive, p_int_alive_dead == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_is_dead, p_int_alive_dead == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Original_Clone()
    MCM.SetToggleOptionValue(p_option_is_original, p_int_original_clone == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_is_clone, p_int_original_clone == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Unique_Generic()
    MCM.SetToggleOptionValue(p_option_is_unique, p_int_unique_generic == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_is_generic, p_int_unique_generic == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Mobile_Immobile()
    MCM.SetToggleOptionValue(p_option_is_mobile, p_int_mobile_immobile == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_is_immobile, p_int_mobile_immobile == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Settler()
    MCM.SetToggleOptionValue(p_option_is_settler, p_int_settler == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_settler, p_int_settler == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Thrall()
    MCM.SetToggleOptionValue(p_option_is_thrall, p_int_thrall == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_thrall, p_int_thrall == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Paralyzed()
    MCM.SetToggleOptionValue(p_option_is_paralyzed, p_int_paralyzed == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_paralyzed, p_int_paralyzed == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Mannequin()
    MCM.SetToggleOptionValue(p_option_is_mannequin, p_int_mannequin == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_mannequin, p_int_mannequin == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Reanimated()
    MCM.SetToggleOptionValue(p_option_is_reanimated, p_int_reanimated == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_reanimated, p_int_reanimated == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Follower()
    MCM.SetToggleOptionValue(p_option_is_follower, p_int_follower == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_follower, p_int_follower == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Sneak()
    MCM.SetToggleOptionValue(p_option_is_sneak, p_int_sneak == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_sneak, p_int_sneak == -1, MCM.DO_UPDATE)
endFunction

function p_Update_Saddler()
    MCM.SetToggleOptionValue(p_option_is_saddler, p_int_saddler == 1, MCM.DONT_UPDATE)
    MCM.SetToggleOptionValue(p_option_isnt_saddler, p_int_saddler == -1, MCM.DO_UPDATE)
endFunction

function p_Concat_Filter_String_Param(string str_param)
    if p_str_view_filter == ""
        p_str_view_filter = str_param
    else
        p_str_view_filter += ", " + str_param
    endIf
endFunction

function p_Goto_Filter_Members()
    p_str_view_filter = ""
    p_int_arg_flags = 0

    if p_str_arg_sex
        p_Concat_Filter_String_Param(p_str_view_sex)
    endIf
    if p_str_arg_race
        p_Concat_Filter_String_Param(p_str_view_race)
    endIf
    if p_int_arg_style < 0
        p_Concat_Filter_String_Param(p_str_view_style)
    endIf
    if p_int_arg_vitality < 0
        p_Concat_Filter_String_Param(p_str_view_vitality)
    endIf
    if p_int_arg_outfit2 < 0
        p_Concat_Filter_String_Param(p_str_view_outfit2 + " Outfit")
    endIf
    if p_int_arg_rating > -1
        p_Concat_Filter_String_Param(p_str_view_rating)
    endIf
    if p_str_arg_search
        p_Concat_Filter_String_Param("'" + p_str_arg_search + "'")
    endIf

    if p_int_alive_dead == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_ALIVE")
        p_Concat_Filter_String_Param("Alive")
    elseIf p_int_alive_dead == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_DEAD")
        p_Concat_Filter_String_Param("Dead")
    endIf

    if p_int_original_clone == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_ORIGINAL")
        p_Concat_Filter_String_Param("Original")
    elseIf p_int_original_clone == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_CLONE")
        p_Concat_Filter_String_Param("Clone")
    endIf

    if p_int_unique_generic == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_UNIQUE")
        p_Concat_Filter_String_Param("Unique")
    elseIf p_int_unique_generic == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_GENERIC")
        p_Concat_Filter_String_Param("Generic")
    endIf

    if p_int_mobile_immobile == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_MOBILE")
        p_Concat_Filter_String_Param("Mobile")
    elseIf p_int_mobile_immobile == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_IMMOBILE")
        p_Concat_Filter_String_Param("Immobile")
    endIf

    if p_int_settler == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_SETTLER")
        p_Concat_Filter_String_Param("Settler")
    elseIf p_int_settler == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_SETTLER")
        p_Concat_Filter_String_Param("!Settler")
    endIf

    if p_int_thrall == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_THRALL")
        p_Concat_Filter_String_Param("Thrall")
    elseIf p_int_thrall == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_THRALL")
        p_Concat_Filter_String_Param("!Thrall")
    endIf

    if p_int_paralyzed == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_PARALYZED")
        p_Concat_Filter_String_Param("Paralyzed")
    elseIf p_int_paralyzed == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_PARALYZED")
        p_Concat_Filter_String_Param("!Paralyzed")
    endIf

    if p_int_mannequin == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_MANNEQUIN")
        p_Concat_Filter_String_Param("Mannequin")
    elseIf p_int_mannequin == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_MANNEQUIN")
        p_Concat_Filter_String_Param("!Mannequin")
    endIf

    if p_int_reanimated == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_REANIMATED")
        p_Concat_Filter_String_Param("Reanimated")
    elseIf p_int_reanimated == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_REANIMATED")
        p_Concat_Filter_String_Param("!Reanimated")
    endIf

    if p_int_follower == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_FOLLOWER")
        p_Concat_Filter_String_Param("Follower")
    elseIf p_int_follower == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_FOLLOWER")
        p_Concat_Filter_String_Param("!Follower")
    endIf

    if p_int_sneak == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_SNEAK")
        p_Concat_Filter_String_Param("Sneak")
    elseIf p_int_sneak == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_SNEAK")
        p_Concat_Filter_String_Param("!Sneak")
    endIf

    if p_int_saddler == 1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "IS_SADDLER")
        p_Concat_Filter_String_Param("Saddler")
    elseIf p_int_saddler == -1
        p_int_arg_flags = MEMBERS.Add_Filter_Flag_1(p_int_arg_flags, "ISNT_SADDLER")
        p_Concat_Filter_String_Param("!Saddler")
    endIf

    if p_str_view_filter == ""
        p_str_view_filter = " All Members "
    endIf

    Alias[] arr_filter = MEMBERS.Filter( \
        MEMBERS.Filter_Strings(p_str_arg_sex, p_str_arg_race, p_str_arg_search), \
        MEMBERS.Filter_Ints(p_int_arg_style, p_int_arg_vitality, p_int_arg_outfit2, p_int_arg_rating), \
        p_int_arg_flags, 0 \
    )

    MCM.MCM_MEMBERS.f_View_Filter_Members(arr_filter)
    MCM.MCM_MEMBERS.f_Build_Page()
endFunction
