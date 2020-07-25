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
        return 6; must be even
    endFunction
endProperty
int property p_COLUMNS_PER_PAGE hidden
    int function Get()
        return 2
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

int                 p_idx_page                  =     0
int                 p_num_pages                 =    -1

int                 p_curr_column               =     1
int                 p_curr_row                  =     1
Alias[]             p_curr_members              =  none
doticu_npcp_member  p_ref_member                =  none

int                 p_options_offset            =    -1
int                 p_option_enter              =    -1
int                 p_option_exit               =    -1
int                 p_option_prev               =    -1
int                 p_option_next               =    -1
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
    p_code_view = doticu_npcp_codes.VIEW_MANNEQUINS()
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Review_Mannequins()
    p_code_view = doticu_npcp_codes.VIEW_MANNEQUINS_CELL()
endFunction

bool function f_Is_Valid_Member(doticu_npcp_member ref_member)
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
int function p_Get_Idx_Entity(int id_option)
endFunction

int function p_Get_Column(int id_option)
endFunction

int function p_Get_Row(int id_option)
endFunction

function p_Fill_Cell_Column(int idx_to_ex)
endFunction

function p_Goto_Mannequins_Member()
endFunction

; States
auto state STATE_MANNEQUINS
function f_Build_Page()
    p_code_view = doticu_npcp_codes.VIEW_MANNEQUINS()
    p_num_pages = Math.Ceiling(MANNEQUINS.MAX_COLUMNS / p_COLUMNS_PER_PAGE)
    if p_idx_page < 0 || p_idx_page >= p_num_pages
        p_idx_page = 0
    endIf

    ; Title
    string str_mannequins = "Mannequins: " + MANNEQUINS.Get_Expo_Count() + "/" + MANNEQUINS.Get_Max()
    string str_pages = "Page: " + (p_idx_page + 1) + "/" + p_num_pages
    MCM.SetTitleText(str_mannequins + "               " + str_pages)

    ; Header
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)
    MCM.SetCursorPosition(0)

    if MANNEQUINS.Is_Player_In_Expo()
        p_option_enter =    MCM.AddTextOption("                      Enter Antechamber", "", MCM.FLAG_DISABLE)
        p_option_exit =     MCM.AddTextOption("                            Exit Expo", "", MCM.FLAG_ENABLE)
    else
        p_option_enter =    MCM.AddTextOption("                      Enter Antechamber", "", MCM.FLAG_ENABLE)
        p_option_exit =     MCM.AddTextOption("                            Exit Expo", "", MCM.FLAG_DISABLE)
    endIf
    if MANNEQUINS.MAX_COLUMNS > p_COLUMNS_PER_PAGE
        p_option_prev =     MCM.AddTextOption("                     Go to Previous Page", "")
        p_option_next =     MCM.AddTextOption("                       Go to Next Page", "")
    else
        p_option_prev =     MCM.AddTextOption("                     Go to Previous Page", "", MCM.FLAG_DISABLE)
        p_option_next =     MCM.AddTextOption("                       Go to Next Page", "", MCM.FLAG_DISABLE)
    endIf
    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")
    p_options_offset = p_option_enter

    ; Body
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

    int idx_column
    int idx_column_end
    int idx_row
    string str_cell_name

    idx_column = (p_idx_page * p_COLUMNS_PER_PAGE) + 1
    idx_column_end = idx_column + p_COLUMNS_PER_PAGE - 1
    if idx_column_end > MANNEQUINS.MAX_COLUMNS
        idx_column_end = MANNEQUINS.MAX_COLUMNS
    endIf

    while idx_column <= idx_column_end
        if idx_column % 2 == 0; is even
            MCM.SetCursorPosition(p_HEADERS_IN_MANNEQUINS + 1)
        else; is odd
            MCM.SetCursorPosition(p_HEADERS_IN_MANNEQUINS)
        endIf

        idx_row = MANNEQUINS.MAX_ROWS
        while idx_row > 0
            str_cell_name = MANNEQUINS.Get_Cell_Name(idx_column, idx_row)
            if str_cell_name
                MCM.AddTextOption("C " + idx_column + ", R " + idx_row + ": " + str_cell_name, "...")
            else
                MCM.AddTextOption("Column " + idx_column + ", Row " + idx_row, "...")
            endIf

            idx_row -= 1
        endWhile

        MCM.AddHeaderOption("")

        idx_column += 1
    endWhile
endFunction

function f_On_Option_Select(int id_option)
    if false

    elseIf id_option == p_option_enter
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        FUNCS.Close_Menus()
        MANNEQUINS.Move_Player_To_Antechamber()
    elseIf id_option == p_option_exit
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        FUNCS.Close_Menus()
        MANNEQUINS.Remove_Player()

    elseIf id_option == p_option_prev
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        if p_idx_page == 0
            p_idx_page = p_num_pages - 1
        else
            p_idx_page -= 1
        endIf
        MCM.ForcePageReset()
    elseIf id_option == p_option_next
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        if p_idx_page == p_num_pages - 1
            p_idx_page = 0
        else
            p_idx_page += 1
        endIf
        MCM.ForcePageReset()

    else
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_curr_column = p_Get_Column(id_option)
        p_curr_row = p_Get_Row(id_option)
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
        MCM.SetInfoText("Open the menu for Column " + p_Get_Column(id_option) + ", Row " + p_Get_Row(id_option) + ".")

    endIf
endFunction

int function p_Get_Column(int id_option)
    int id_option_norm = id_option - p_options_offset - p_HEADERS_IN_MANNEQUINS
    ; Page 0
    ; 0 == 1, 1 == 2
    ; 2 == 1, 3 == 2
    ; 4 == 1, 5 == 2
    ; ...
    ; Page 1
    ; 0 == 3, 1 == 4
    ; 2 == 3, 3 == 4
    ; 4 == 3, 5 == 4
    ; ...
    if id_option_norm % 2 == 0; is even
        return (p_idx_page * p_COLUMNS_PER_PAGE) + 1
    else; is odd
        return (p_idx_page * p_COLUMNS_PER_PAGE) + 2
    endIf
endFunction

int function p_Get_Row(int id_option)
    int id_option_norm = id_option - p_options_offset - p_HEADERS_IN_MANNEQUINS
    ; 0 == 8, 1 == 8
    ; 2 == 7, 3 == 7
    ; 4 == 6, 5 == 6
    ; ...
    return 8 - Math.Floor(id_option_norm / 2)
endFunction
endState

state STATE_MANNEQUINS_CELL
bool function f_Is_Valid_Member(doticu_npcp_member ref_member)
    if !ref_member || !ref_member.Exists() || !ref_member.Is_Mannequin() || p_curr_members.Find(ref_member) < 0
        return false
    else
        return true
    endIf
endFunction

function f_Build_Page()
    p_curr_members = MANNEQUINS.Get_Mannequins(p_curr_column, p_curr_row)

    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        if f_Is_Valid_Member(p_ref_member)
            return p_Goto_Mannequins_Member()
        else
            f_Review_Mannequins()
        endIf
    endIf

    p_code_view = doticu_npcp_codes.VIEW_MANNEQUINS_CELL()
    
    ; Title
    MCM.SetTitleText("Mannequins: C " + p_curr_column + ", R " + p_curr_row)
    
    ; Header
    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)
    
    p_option_name = MCM.AddInputOption(MANNEQUINS.Get_Cell_Name(p_curr_column, p_curr_row), " Detail ")
    p_option_back =     MCM.AddTextOption("                              Go Back", "")
    p_option_enter =    MCM.AddTextOption("                              Enter Cell", "")
    if MANNEQUINS.Is_Player_In_Expo()
        p_option_exit = MCM.AddTextOption("                              Exit Expo", "", MCM.FLAG_ENABLE)
    else
        p_option_exit = MCM.AddTextOption("                              Exit Expo", "", MCM.FLAG_DISABLE)
    endIf
    MCM.AddHeaderOption("")
    MCM.AddHeaderOption("")
    p_options_offset = p_option_name
    
    ; Body
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
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Select(id_option)
    endIf

    if false

    elseIf id_option == p_option_back
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        GotoState("STATE_MANNEQUINS")
        MCM.ForcePageReset()
    elseIf id_option == p_option_enter
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        FUNCS.Close_Menus()
        MANNEQUINS.Move_Player_To_Cell(p_curr_column, p_curr_row)
    elseIf id_option == p_option_exit
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        FUNCS.Close_Menus()
        MANNEQUINS.Remove_Player()
    elseIf id_option == p_option_north_1 || id_option == p_option_north_2
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_curr_row += 1
        MCM.ForcePageReset()
    elseIf id_option == p_option_south_1 || id_option == p_option_south_2
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_curr_row -= 1
        MCM.ForcePageReset()
    elseIf id_option == p_option_west
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_curr_column -= 1
        MCM.ForcePageReset()
    elseIf id_option == p_option_east
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_curr_column += 1
        MCM.ForcePageReset()
    else
        MCM.f_Disable(id_option, MCM.DO_UPDATE)
        p_code_view = doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        p_ref_member = p_curr_members[p_Get_Idx_Entity(id_option)] as doticu_npcp_member
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Input_Accept(id_option, str_input)
    endIf

    if false

    elseIf id_option == p_option_name
        MANNEQUINS.Set_Cell_Name(p_curr_column, p_curr_row, str_input)
        MCM.ForcePageReset()

    endIf
endFunction

function f_On_Option_Highlight(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Highlight(id_option)
    endIf

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
        doticu_npcp_member ref_member = p_curr_members[p_Get_Idx_Entity(id_option)] as doticu_npcp_member
        if ref_member
            MCM.SetInfoText("Open the mannequin menu for " + ref_member.Name() + ".\n" + MCM.MCM_MEMBERS.Get_Info_String(ref_member))
        endIf

    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Menu_Open(id_option)
    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Slider_Open(id_option)
    endIf
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endFunction

function f_On_Option_Default(int id_option)
    if p_code_view == doticu_npcp_codes.VIEW_MANNEQUINS_MEMBER()
        return MCM.MCM_MEMBER.f_On_Option_Default(id_option)
    endIf
endFunction

int function p_Get_Idx_Entity(int id_option)
    int id_option_norm = id_option - p_options_offset - p_HEADERS_IN_MANNEQUINS_CELL
    ; 0 == 7, 1 == 15
    ; 2 == 6, 3 == 14
    ; 4 == 5, 5 == 13
    ; ...
    int idx_entity = 8 - (Math.Floor(id_option_norm / 2) + 1)
    if id_option_norm % 2 == 1
        idx_entity += 8
    endIf
    return idx_entity
endFunction

function p_Fill_Cell_Column(int idx_to_ex)
    int idx_from = idx_to_ex - 8
    doticu_npcp_member ref_member

    while idx_to_ex > idx_from
        idx_to_ex -= 1
        ref_member = p_curr_members[idx_to_ex] as doticu_npcp_member
        if ref_member
            MCM.AddTextOption(ref_member.Name(), "")
        else
            MCM.AddTextOption("EMPTY ", "", MCM.FLAG_DISABLE)
        endIf
    endWhile
endFunction

function p_Goto_Mannequins_Member()
    MCM.MCM_MEMBER.f_View_Mannequins_Member(p_ref_member)
    MCM.MCM_MEMBER.f_Build_Page()
endFunction
endState
