Scriptname doticu_npcp_mcm_log extends Quest

; Private Constants
doticu_npcp_logs    p_LOGS                  = none
doticu_npcp_mcm     p_MCM                   = none

int                 p_HEADERS_PER_PAGE      =    4
int                 p_STRINGS_PER_PAGE      =   20

; Private Variables
string[]            p_arr_notes             = none
string[]            p_arr_errors            = none
int                 p_pages_count           =   -1
int                 p_pages_curr            =    0

int                 p_options_offset        =   -1
int                 p_option_prev           =   -1
int                 p_option_next           =   -1
int                 p_option_clear_notes    =   -1
int                 p_option_clear_errors   =   -1

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_LOGS = DATA.MODS.FUNCS.LOGS
    p_MCM = DATA.MODS.CONTROL.MCM
endFunction

function f_Initialize()
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

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

function f_On_Option_Highlight(int id_option)
endFunction

; Private Methods
int function p_Get_Idx_Entity(int id_option)
endFunction

; Update Methods
function u_0_1_0()
endFunction

; Private States
auto state p_STATE_LOGS
    function f_Build_Page()
        int notes_count = p_LOGS.Get_Note_Count()
        int errors_count = p_LOGS.Get_Error_Count()
        int notes_max = p_LOGS.Get_Note_Max()
        int errors_max = p_LOGS.Get_Error_Max()
        string str_notes = "Notes: " + notes_count + "/" + notes_max
        string str_errors = "Errors: " + errors_count + "/" + errors_max

        if notes_count == 0 && errors_count == 0
            p_MCM.SetTitleText(str_notes + "         " + "Page 1/1" + "         " + str_errors)
            return
        endIf

        if notes_count > errors_count
            p_pages_count = Math.Ceiling(notes_count / (p_STRINGS_PER_PAGE as float))
        else
            p_pages_count = Math.Ceiling(errors_count / (p_STRINGS_PER_PAGE as float))
        endIf
        
        string str_pages = "Pages: " + (p_pages_curr + 1) + "/" + p_pages_count

        p_MCM.SetTitleText(str_notes + "         " + str_pages + "         " + str_errors)

        p_MCM.SetCursorPosition(0)
        p_MCM.SetCursorFillMode(p_MCM.LEFT_TO_RIGHT)

        if notes_count > p_STRINGS_PER_PAGE || errors_count > p_STRINGS_PER_PAGE
            p_option_prev = p_MCM.AddTextOption("                     Go to Previous Page", "")
            p_option_next = p_MCM.AddTextOption("                       Go to Next Page", "")
        else
            p_option_prev = p_MCM.AddTextOption("                     Go to Previous Page", "", p_MCM.OPTION_FLAG_DISABLED)
            p_option_next = p_MCM.AddTextOption("                       Go to Next Page", "", p_MCM.OPTION_FLAG_DISABLED)
        endIf
        p_options_offset = p_option_prev

        int notes_idx_from = p_STRINGS_PER_PAGE * p_pages_curr
        int notes_idx_to_ex = notes_idx_from + p_STRINGS_PER_PAGE
        p_arr_notes = p_LOGS.Get_Notes(notes_idx_from, notes_idx_to_ex)

        p_MCM.SetCursorPosition(2)
        p_MCM.SetCursorFillMode(p_MCM.TOP_TO_BOTTOM)

        p_MCM.AddHeaderOption("Notes ")

        int idx_notes = 0
        while idx_notes < p_arr_notes.length
            p_MCM.AddTextOption(p_arr_notes[idx_notes], "")
            idx_notes += 1
        endWhile

        if notes_count > 0
            p_MCM.AddHeaderOption("")
            p_option_clear_notes    =  p_MCM.AddTextOption("                        Clear Notes", "")
        endIf

        int errors_idx_from = p_STRINGS_PER_PAGE * p_pages_curr
        int errors_idx_to_ex = errors_idx_from + p_STRINGS_PER_PAGE
        int errors_slice_idx = 0
        p_arr_errors = p_LOGS.Get_Errors(errors_idx_from, errors_idx_to_ex)

        p_MCM.SetCursorPosition(3)
        p_MCM.SetCursorFillMode(p_MCM.TOP_TO_BOTTOM)

        p_MCM.AddHeaderOption("Errors ")

        int idx_errors = 0
        while idx_errors < p_arr_errors.length
            p_MCM.AddTextOption(p_arr_errors[idx_errors], "")
            idx_errors += 1
        endWhile

        if errors_count > 0
            p_MCM.AddHeaderOption("")
            p_option_clear_errors = p_MCM.AddTextOption("                         Clear Errors", "")
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
            p_LOGS.Clear_Notes()
        elseIf id_option == p_option_clear_errors
            p_LOGS.Clear_Errors()
        endIf
        p_MCM.ForcePageReset()
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_prev
            p_MCM.SetInfoText("Go to the Previous Page")
        elseIf id_option == p_option_next
            p_MCM.SetInfoText("Go to the Next Page")
        elseIf id_option == p_option_clear_notes
            p_MCM.SetInfoText("Clear All Notes")
        elseIf id_option == p_option_clear_errors
            p_MCM.SetInfoText("Clear All Errors")
        else
            int idx_entity = p_Get_Idx_Entity(id_option)
            if id_option % 2 == 0
                p_MCM.SetInfoText(p_arr_notes[idx_entity])
            else
                p_MCM.SetInfoText(p_arr_errors[idx_entity])
            endIf
        endIf
    endFunction
endState
