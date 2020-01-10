Scriptname doticu_npcp_mcm_log extends Quest

; Modules
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return p_DATA.MODS.CONTROL.MCM
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA                  =  none

int                 p_HEADERS_PER_PAGE      =     4
int                 p_STRINGS_PER_PAGE      =     8

; Private Variables
bool                p_is_created            = false

string[]            p_arr_notes             =  none
string[]            p_arr_errors            =  none
int                 p_pages_count           =    -1
int                 p_pages_curr            =     0

int                 p_options_offset        =    -1
int                 p_option_prev           =    -1
int                 p_option_next           =    -1
int                 p_option_clear_notes    =    -1
int                 p_option_clear_errors   =    -1

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

; Private States
auto state p_STATE_LOGS
    function f_Build_Page()
        int notes_count = LOGS.Get_Note_Count()
        int errors_count = LOGS.Get_Error_Count()
        int notes_max = LOGS.Get_Note_Max()
        int errors_max = LOGS.Get_Error_Max()
        string str_notes = "Notes: " + notes_count + "/" + notes_max
        string str_errors = "Errors: " + errors_count + "/" + errors_max

        if notes_count == 0 && errors_count == 0
            MCM.SetTitleText(str_notes + "         " + "Page 1/1" + "         " + str_errors)
            return
        endIf

        if notes_count > errors_count
            p_pages_count = Math.Ceiling(notes_count / (p_STRINGS_PER_PAGE as float))
        else
            p_pages_count = Math.Ceiling(errors_count / (p_STRINGS_PER_PAGE as float))
        endIf
        
        string str_pages = "Pages: " + (p_pages_curr + 1) + "/" + p_pages_count

        MCM.SetTitleText(str_notes + "         " + str_pages + "         " + str_errors)

        MCM.SetCursorPosition(0)
        MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

        if notes_count > p_STRINGS_PER_PAGE || errors_count > p_STRINGS_PER_PAGE
            p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "")
            p_option_next = MCM.AddTextOption("                       Go to Next Page", "")
        else
            p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "", MCM.OPTION_FLAG_DISABLED)
            p_option_next = MCM.AddTextOption("                       Go to Next Page", "", MCM.OPTION_FLAG_DISABLED)
        endIf
        p_options_offset = p_option_prev

        int notes_idx_from = p_STRINGS_PER_PAGE * p_pages_curr
        int notes_idx_to_ex = notes_idx_from + p_STRINGS_PER_PAGE
        p_arr_notes = LOGS.Get_Notes(notes_idx_from, notes_idx_to_ex)

        MCM.SetCursorPosition(2)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
        MCM.AddHeaderOption("Notes ")

        int idx_notes = 0
        while idx_notes < p_arr_notes.length
            MCM.AddTextOption(p_arr_notes[idx_notes], "")
            idx_notes += 1
        endWhile

        MCM.SetCursorPosition(4 + p_STRINGS_PER_PAGE * 2)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
        MCM.AddHeaderOption("")
        if notes_count > 0
            p_option_clear_notes = MCM.AddTextOption("                        Clear Notes", "")
        else
            p_option_clear_notes = MCM.AddTextOption("                        Clear Notes", "", MCM.OPTION_FLAG_DISABLED)
        endIf

        int errors_idx_from = p_STRINGS_PER_PAGE * p_pages_curr
        int errors_idx_to_ex = errors_idx_from + p_STRINGS_PER_PAGE
        p_arr_errors = LOGS.Get_Errors(errors_idx_from, errors_idx_to_ex)

        MCM.SetCursorPosition(3)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

        MCM.AddHeaderOption("Errors ")

        int idx_errors = 0
        while idx_errors < p_arr_errors.length
            MCM.AddTextOption(p_arr_errors[idx_errors], "")
            idx_errors += 1
        endWhile

        MCM.SetCursorPosition(5 + p_STRINGS_PER_PAGE * 2)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
        MCM.AddHeaderOption("")
        if errors_count > 0
            p_option_clear_errors = MCM.AddTextOption("                         Clear Errors", "")
        else
            p_option_clear_errors = MCM.AddTextOption("                         Clear Errors", "", MCM.OPTION_FLAG_DISABLED)
        endIf
    endFunction

    int function p_Get_Idx_Entity(int id_option)
        return Math.Floor((id_option - p_options_offset - p_HEADERS_PER_PAGE) / 2)
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_prev
            if p_pages_curr == 0
                p_pages_curr = p_pages_count - 1
            else
                p_pages_curr -= 1
            endIf
        elseIf id_option == p_option_next
            if p_pages_curr == p_pages_count - 1
                p_pages_curr = 0
            else
                p_pages_curr += 1
            endIf
        elseIf id_option == p_option_clear_notes
            LOGS.Clear_Notes()
        elseIf id_option == p_option_clear_errors
            LOGS.Clear_Errors()
        endIf
        MCM.ForcePageReset()
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_prev
            MCM.SetInfoText("Go to the Previous Page")
        elseIf id_option == p_option_next
            MCM.SetInfoText("Go to the Next Page")
        elseIf id_option == p_option_clear_notes
            MCM.SetInfoText("Clear All Notes")
        elseIf id_option == p_option_clear_errors
            MCM.SetInfoText("Clear All Errors")
        else
            int idx_entity = p_Get_Idx_Entity(id_option)
            if id_option % 2 == 0 && p_arr_notes.length > 0
                MCM.SetInfoText(p_arr_notes[idx_entity])
            elseIf p_arr_errors.length > 0
                MCM.SetInfoText(p_arr_errors[idx_entity])
            endIf
        endIf
    endFunction
endState
