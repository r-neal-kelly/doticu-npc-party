;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_mannequins extends Quest

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

int property p_HEADERS_IN_MANNEQUINS hidden
    int function Get()
        return 4; must be even
    endFunction
endProperty
int property p_OPTIONS_PER_COLUMN hidden
    int function Get()
        return MANNEQUINS.MAX_ROWS + 1; includes the header for each column
    endFunction
endProperty
int property p_HEADERS_IN_MANNEQUINS_CELL hidden
    int function Get()
        return 6
    endFunction
endProperty

; Private Variables
bool                p_is_created                = false
int                 p_code_view                 =    -1

int                 p_curr_column               =     1
int                 p_curr_row                  =     1
Alias[]             p_curr_members              =  none

int                 p_options_offset            =    -1
int                 p_option_enter              =    -1
int                 p_option_exit               =    -1
int                 p_option_name               =    -1
int                 p_option_back               =    -1
int                 p_option_north_1            =    -1
int                 p_option_north_2            =    -1
int                 p_option_west               =    -1
int                 p_option_east               =    -1
int                 p_option_south_1            =    -1
int                 p_option_south_2            =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_code_view = CODES.VIEW_MANNEQUINS
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Build_Page()
endFunction

function f_On_Option_Select(int id_option)
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
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Default(int id_option)
endFunction

; Private Methods
int function p_Get_Cursor_Column(int idx_column)
endFunction

int function p_Get_Idx_Entity(int id_option)
endFunction

int function p_Get_Idx_Command(int id_option, int idx_entity)
endFunction

function p_Fill_Cell_Column(int idx_to_ex)
endFunction

; States
auto state STATE_MANNEQUINS
function f_Build_Page()
    p_code_view = CODES.VIEW_MANNEQUINS

    MCM.SetTitleText(" Mannequins ")

    ; Header
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)
    MCM.SetCursorPosition(0)

    if MANNEQUINS.Is_Player_In_Expo()
        p_option_enter =    MCM.AddTextOption("                              Enter", "", MCM.FLAG_DISABLE)
        p_option_exit =     MCM.AddTextOption("                              Exit", "", MCM.FLAG_ENABLE)
    else
        p_option_enter =    MCM.AddTextOption("                              Enter", "", MCM.FLAG_ENABLE)
        p_option_exit =     MCM.AddTextOption("                              Exit", "", MCM.FLAG_DISABLE)
    endIf
    p_options_offset = p_option_enter
    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")

    ; Body
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

    int idx_column
    int idx_row
    string str_cell_coords
    string str_cell_name

    idx_column = 0
    while idx_column < MANNEQUINS.MAX_COLUMNS
        MCM.SetCursorPosition(p_Get_Cursor_Column(idx_column))

        idx_row = 0
        while idx_row < MANNEQUINS.MAX_ROWS
            str_cell_name = MANNEQUINS.Get_Cell_Name(idx_column + 1, idx_row + 1)
            if str_cell_name
                str_cell_coords = "C " + (idx_column + 1) + ", R " + (idx_row + 1)
                MCM.AddTextOption(str_cell_coords + ": " + str_cell_name, "...")
            else
                str_cell_coords = "Column " + (idx_column + 1) + ", Row " + (idx_row + 1)
                MCM.AddTextOption(str_cell_coords, "...")
            endIf

            idx_row += 1
        endWhile

        MCM.AddHeaderOption("")

        idx_column += 1
    endWhile
endFunction

function f_On_Option_Select(int id_option)
    if false

    elseIf id_option == p_option_enter
        FUNCS.Close_Menus()
        MANNEQUINS.Move_Player_To_Antechamber()
    elseIf id_option == p_option_exit
        FUNCS.Close_Menus()
        MANNEQUINS.Remove_Player()
    else
        int idx_entity = p_Get_Idx_Entity(id_option)
        int idx_command = p_Get_Idx_Command(id_option, idx_entity)
        p_curr_column = idx_entity + 1
        p_curr_row = idx_command + 1
        GotoState("STATE_MANNEQUINS_CELL")
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if false

    elseIf id_option == p_option_enter
        MCM.SetInfoText("Teleport to the Expo Antechamber.")
    elseIf id_option == p_option_exit
        MCM.SetInfoText("Teleport back to Tamriel.")
    else
        int idx_entity = p_Get_Idx_Entity(id_option)
        int idx_command = p_Get_Idx_Command(id_option, idx_entity)
        MCM.SetInfoText("Open the menu for Column " + (idx_entity + 1) + ", Row " + (idx_command + 1) + ".")

    endIf
endFunction

int function p_Get_Cursor_Column(int idx_column)
    if idx_column % 2 == 0; is even
        return p_OPTIONS_PER_COLUMN * idx_column + p_HEADERS_IN_MANNEQUINS
    else; is odd
        return p_OPTIONS_PER_COLUMN * (idx_column - 1) + 1 + p_HEADERS_IN_MANNEQUINS
    endIf
endFunction

int function p_Get_Idx_Entity(int id_option)
    int id_option_norm = id_option - p_options_offset - p_HEADERS_IN_MANNEQUINS
    int idx_entity = Math.Floor(id_option_norm / (p_OPTIONS_PER_COLUMN * 2)) * 2
    if id_option_norm % 2 == 1
        idx_entity += 1
    endIf
    return idx_entity
endFunction

int function p_Get_Idx_Command(int id_option, int idx_entity)
    int id_option_norm = id_option - p_options_offset - p_HEADERS_IN_MANNEQUINS
    return Math.Floor(id_option_norm / 2) - Math.Floor(idx_entity / 2) * p_OPTIONS_PER_COLUMN
endFunction
endState

state STATE_MANNEQUINS_CELL
function f_Build_Page()
    p_code_view = CODES.VIEW_MANNEQUINS_CELL
    p_curr_members = MANNEQUINS.Get_Mannequins(p_curr_column, p_curr_row)
    
    MCM.SetTitleText("Mannequins in Expo: C " + p_curr_column + ", R " + p_curr_row)
    
    ; Header
    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)
    
    p_option_name = MCM.AddInputOption(MANNEQUINS.Get_Cell_Name(p_curr_column, p_curr_row), " Detail ")
    p_option_back =     MCM.AddTextOption("                              Go Back", "")
    p_option_enter =    MCM.AddTextOption("                              Enter", "")
    if MANNEQUINS.Is_Player_In_Expo()
        p_option_exit = MCM.AddTextOption("                              Exit", "", MCM.FLAG_ENABLE)
    else
        p_option_exit = MCM.AddTextOption("                              Exit", "", MCM.FLAG_DISABLE)
    endIf
    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")
    
    ; Body
    ; we need to make each member clickable and send them to doticu_npcp_mcm_member
    MCM.SetCursorPosition(p_HEADERS_IN_MANNEQUINS_CELL)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
    p_Fill_Cell_Column(8)
        
    MCM.SetCursorPosition(p_HEADERS_IN_MANNEQUINS_CELL + 1)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
    p_Fill_Cell_Column(16)

    ; Footer
    MCM.SetCursorPosition(p_HEADERS_IN_MANNEQUINS_CELL + MANNEQUINS.MAX_ROWS * 2)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")

    if p_curr_row < MANNEQUINS.MAX_ROWS
        p_option_north_1 =  MCM.AddTextOption("                              North", "")
        p_option_north_2 =  MCM.AddTextOption("                              North", "")
    else
        p_option_north_1 =  MCM.AddTextOption("                              North", "", MCM.FLAG_DISABLE)
        p_option_north_2 =  MCM.AddTextOption("                              North", "", MCM.FLAG_DISABLE)
    endIf
    if p_curr_column > 1
        p_option_west =     MCM.AddTextOption("                              West", "")
    else
        p_option_west =     MCM.AddTextOption("                              West", "", MCM.FLAG_DISABLE)
    endIf
    if p_curr_column < MANNEQUINS.MAX_COLUMNS
        p_option_east =     MCM.AddTextOption("                              East", "")
    else
        p_option_east =     MCM.AddTextOption("                              East", "", MCM.FLAG_DISABLE)
    endIf
    if p_curr_row > 1
        p_option_south_1 =  MCM.AddTextOption("                              South", "")
        p_option_south_2 =  MCM.AddTextOption("                              South", "")
    else
        p_option_south_1 =  MCM.AddTextOption("                              South", "", MCM.FLAG_DISABLE)
        p_option_south_2 =  MCM.AddTextOption("                              South", "", MCM.FLAG_DISABLE)
    endIf
endFunction

function f_On_Option_Select(int id_option)
    if false

    elseIf id_option == p_option_back
        GotoState("STATE_MANNEQUINS")
        MCM.ForcePageReset()
    elseIf id_option == p_option_enter
        FUNCS.Close_Menus()
        MANNEQUINS.Move_Player(p_curr_column, p_curr_row)
    elseIf id_option == p_option_exit
        FUNCS.Close_Menus()
        MANNEQUINS.Remove_Player()
    elseIf id_option == p_option_north_1 || id_option == p_option_north_2
        p_curr_row += 1
        MCM.ForcePageReset()
    elseIf id_option == p_option_south_1 || id_option == p_option_south_2
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

function f_On_Option_Input_Accept(int id_option, string str_input)
    if false

    elseIf id_option == p_option_name
        MANNEQUINS.Set_Cell_Name(p_curr_column, p_curr_row, str_input)
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if false

    elseIf id_option == p_option_back
        MCM.SetInfoText("Go back to main Mannequins menu.")
    elseIf id_option == p_option_enter
        MCM.SetInfoText("Teleport to Expo C " + p_curr_column + ", R" + p_curr_row + ".")
    elseIf id_option == p_option_exit
        MCM.SetInfoText("Teleport back to Tamriel.")
    elseIf id_option == p_option_north_1 || id_option == p_option_north_2
        MCM.SetInfoText("Move the menu NORTH one cell, in relation to the position of this cell.")
    elseIf id_option == p_option_south_1 || id_option == p_option_south_2
        MCM.SetInfoText("Move the menu SOUTH one cell, in relation to the position of this cell.")
    elseIf id_option == p_option_west
        MCM.SetInfoText("Move the menu WEST one cell, in relation to the position of this cell.")
    elseIf id_option == p_option_east
        MCM.SetInfoText("Move the menu EAST one cell, in relation to the position of this cell.")
    else
        MCM.SetInfoText("")

    endIf
endFunction

function p_Fill_Cell_Column(int idx_to_ex)
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
endState
