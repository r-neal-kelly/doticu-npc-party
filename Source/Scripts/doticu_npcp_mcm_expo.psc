;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_expo extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return p_DATA.MODS.FUNCS.MANNEQUINS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return p_DATA.MODS.CONTROL.MCM
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA  =  none

; Private Variables
bool                p_is_created                = false

int                 p_curr_column               =     1
int                 p_curr_row                  =     1
Alias[]             p_curr_members              =  none

int                 p_option_name               =    -1
int                 p_option_goto               =    -1
int                 p_option_north              =    -1
int                 p_option_south              =    -1
int                 p_option_west               =    -1
int                 p_option_east               =    -1

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

function f_Unregister()
endFunction

function f_Build_Page()
    p_curr_members = MANNEQUINS.Get_Mannequins(p_curr_column, p_curr_row)

    MCM.SetTitleText("Expo: C " + p_curr_column + ", R " + p_curr_row)

    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    p_option_name = MCM.AddInputOption(MANNEQUINS.Get_Cell_Name(p_curr_column, p_curr_row), " Detail ")
    p_option_goto = MCM.AddTextOption("                              Teleport", "")

    if p_curr_row < MANNEQUINS.MAX_ROWS
        p_option_north = MCM.AddTextOption("                              N", "")
    else
        p_option_north = MCM.AddTextOption("                              N", "", MCM.FLAG_DISABLE)
    endIf
    if p_curr_column < MANNEQUINS.MAX_COLUMNS
        p_option_east = MCM.AddTextOption("                              E", "")
    else
        p_option_east = MCM.AddTextOption("                              E", "", MCM.FLAG_DISABLE)
    endIf
    if p_curr_row > 1
        p_option_south = MCM.AddTextOption("                              S", "")
    else
        p_option_south = MCM.AddTextOption("                              S", "", MCM.FLAG_DISABLE)
    endIf
    if p_curr_column > 1
        p_option_west = MCM.AddTextOption("                              W", "")
    else
        p_option_west = MCM.AddTextOption("                              W", "", MCM.FLAG_DISABLE)
    endIf

    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")

    MCM.SetCursorPosition(8)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
    p_Fill_Member_Half(8)
    
    MCM.SetCursorPosition(9)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
    p_Fill_Member_Half(16)
endFunction

function f_On_Option_Select(int id_option)
    if false

    elseIf id_option == p_option_goto
        MANNEQUINS.Move_Player_To(p_curr_column, p_curr_row)
    elseIf id_option == p_option_north
        p_curr_row += 1
        MCM.ForcePageReset()
    elseIf id_option == p_option_south
        p_curr_row -= 1
        MCM.ForcePageReset()
    elseIf id_option == p_option_west
        p_curr_column -= 1
        MCM.ForcePageReset()
    elseIf id_option == p_option_east
        p_curr_column += 1
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
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
    if false

    elseIf id_option == p_option_name
        MANNEQUINS.Set_Cell_Name(p_curr_column, p_curr_row, str_input)
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Default(int id_option)
endFunction

; Private Methods
function p_Fill_Member_Half(int idx_to_ex)
    int idx_from = idx_to_ex - 8
    doticu_npcp_member ref_member

    while idx_to_ex > idx_from
        idx_to_ex -= 1
        ref_member = p_curr_members[idx_to_ex] as doticu_npcp_member
        if ref_member
            MCM.AddTextOption(ref_member.Get_Name(), "")
        else
            MCM.AddTextOption("EMPTY ", "", MCM.FLAG_DISABLE)
        endIf
    endWhile
endFunction
