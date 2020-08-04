;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_logs extends Quest

string[]            p_NOTES         =  none
string[]            p_ERRORS        =  none

; Private Variables
bool                p_is_created    = false

int                 p_notes_pivot   =     0; will point at latest note
int                 p_notes_used    =     0
int                 p_notes_max     =    64

int                 p_errors_pivot  =     0; will point at latest error
int                 p_errors_used   =     0
int                 p_errors_max    =    64

; Friend Methods
function f_Create()
    p_NOTES = Utility.CreateStringArray(p_notes_max, "")
    p_ERRORS = Utility.CreateStringArray(p_errors_max, "")

    p_is_created = true

    p_notes_pivot = p_NOTES.length - 1
    p_notes_used = 0

    p_errors_pivot = p_ERRORS.length - 1
    p_errors_used = 0
endFunction

function f_Destroy()
    p_notes_pivot = 0
    p_notes_used = 0
    p_notes_max = 64

    p_errors_pivot = 0
    p_errors_used = 0
    p_errors_max = 64

    p_is_created = false

    p_ERRORS = none
    p_NOTES = none
endFunction

function f_Register()
endFunction

; Private Methods
string[] function p_Copy_Array(string[] arr_orig, int orig_pivot, int orig_used)
    string[] arr_copy = Utility.CreateStringArray(orig_used, "")
    int idx_orig = 0
    int idx_copy = 0

    idx_orig = orig_pivot
    while idx_orig >= 0
        if arr_orig[idx_orig] != ""
            arr_copy[idx_copy] = arr_orig[idx_orig]
            idx_copy += 1
        endIf
        idx_orig -= 1
    endWhile

    idx_orig = arr_orig.length - 1
    while idx_orig > orig_pivot
        if arr_orig[idx_orig] != ""
            arr_copy[idx_copy] = arr_orig[idx_orig]
            idx_copy += 1
        endIf
        idx_orig -= 1
    endWhile

    return arr_copy
endFunction

string[] function p_Slice_Array(string[] arr_orig, int orig_pivot, int orig_used, int idx_from = 0, int idx_to_ex = -1)
    if idx_from < 0
        idx_from = 0
    endIf
    if idx_to_ex > orig_used || idx_to_ex < 0
        idx_to_ex = orig_used
    endIf
    int slice_used = idx_to_ex - idx_from
    if slice_used <= 0
        return Utility.CreateStringArray(0, "")
    endIf
    if slice_used == orig_used
        return p_Copy_Array(arr_orig, orig_pivot, orig_used)
    endIf

    string[] arr_all = p_Copy_Array(arr_orig, orig_pivot, orig_used)
    string[] arr_slice = Utility.CreateStringArray(slice_used, "")
    
    int idx_all = idx_from
    int idx_slice = 0
    while idx_all < idx_to_ex
        arr_slice[idx_slice] = arr_all[idx_all]
        idx_all += 1
        idx_slice += 1
    endWhile

    return arr_slice
endFunction

function p_Push_Note(string str_note)
    if str_note == ""
        return
    endIf

    p_notes_pivot += 1
    if p_notes_pivot == p_NOTES.length
        p_notes_pivot = 0
    endIf

    p_NOTES[p_notes_pivot] = str_note

    if p_notes_used < p_NOTES.length
        p_notes_used += 1
    endIf
endFunction

function p_Push_Error(string str_error)
    if str_error == ""
        return
    endIf

    p_errors_pivot += 1
    if p_errors_pivot == p_ERRORS.length
        p_errors_pivot = 0
    endIf

    p_ERRORS[p_errors_pivot] = str_error

    if p_errors_used < p_ERRORS.length
        p_errors_used += 1
    endIf
endFunction

; Public Methods
function Create_Note(string str_note, bool do_log = true)
    Debug.Notification("NPC Party: " + str_note)
    if do_log
        p_Push_Note(str_note)
    endIf
endFunction

function Create_Error(string str_error, bool do_log = true)
    Debug.Notification("NPC Party ERROR: " + str_error)
    if do_log
        p_Push_Error(str_error)
    endIf
endFunction

string[] function Get_Notes(int idx_from = 0, int idx_to_ex = -1)
    return p_Slice_Array(p_NOTES, p_notes_pivot, p_notes_used, idx_from, idx_to_ex)
endFunction

string[] function Get_Errors(int idx_from = 0, int idx_to_ex = -1)
    return p_Slice_Array(p_ERRORS, p_errors_pivot, p_errors_used, idx_from, idx_to_ex)
endFunction

int function Get_Note_Count()
    return p_notes_used
endFunction

int function Get_Error_Count()
    return p_errors_used
endFunction

int function Get_Note_Max()
    return p_notes_max
endFunction

int function Get_Error_Max()
    return p_errors_max
endFunction

function Clear_Notes()
    int idx = 0
    while idx < p_NOTES.length
        p_NOTES[idx] = ""
        idx += 1
    endWhile

    p_notes_pivot = p_NOTES.length - 1
    p_notes_used = 0
endFunction

function Clear_Errors()
    int idx = 0
    while idx < p_ERRORS.length
        p_ERRORS[idx] = ""
        idx += 1
    endWhile

    p_errors_pivot = p_ERRORS.length - 1
    p_errors_used = 0
endFunction

function Print(string str)
    doticu_npcp.Print("NPC Party: " + str)
endFunction

function Notify_Is_Updating()
    Debug.Notification("NPC Party: " + "Currently updating, please wait...")
endFunction
