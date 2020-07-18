;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mannequins extends Quest

; Info
;/
    Formlist Structure:
    ------------    ------------
    |  23  31  |    |  55  63  |
    |  22  30  |    |  54  62  |
    |  21  29  |    |  53  61  |
    |  20  28  |    |  52  60  |
    |          |    |          |
    |  19  27  |    |  51  59  |
    |  18  26  |    |  50  58  |
    |  17  25  |    |  49  57  |
    |  16  24  |    |  48  56  |
    |c1        |    |c2        |
    |  r2      |    |  r2      |
    ------------    ------------
    ------------    ------------
    |   7  15  |    |  39  47  |
    |   6  14  |    |  38  46  |
    |   5  13  |    |  37  45  |
    |   4  12  |    |  36  44  |
    |          |    |          |
    |   3  11  |    |  35  43  |
    |   2  10  |    |  34  42  |
    |   1   9  |    |  33  41  |
    |   0   8  |    |  32  40  |
    |c1        |    |c2        |
    |  r1      |    |  r1      |
    ------------    ------------
    * Pattern actually extends to 8 rows instead of 2.
    * Columns can be added in the future, but not rows.
/;

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
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
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
doticu_npcp_keys property KEYS hidden
    doticu_npcp_keys function Get()
        return p_DATA.MODS.CONTROL.KEYS
    endFunction
endProperty

; Private Constants
doticu_npcp_data p_DATA =  none

int property p_MAX_MANNEQUINS_PER_CELL hidden
    int function Get()
        return 16
    endFunction
endProperty
int property p_MAX_MANNEQUINS_PER_COLUMN hidden
    int function Get()
        return 128
    endFunction
endProperty
int property p_MAX_CELLS hidden
    int function Get()
        return 64
    endFunction
endProperty

; Public Constants
int property MAX_MANNEQUINS hidden
    int function Get()
        return 1024
    endFunction
endProperty
int property MAX_COLUMNS hidden
    int function Get()
        return 8
    endFunction
endProperty
int property MAX_ROWS hidden
    int function Get()
        return 8
    endFunction
endProperty

; Private Variables
bool                    p_is_created        = false
Alias[]                 p_arr_mannequins    =  none
String[]                p_arr_cell_names    =  none
ObjectReference         p_marker_teleport   =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_arr_mannequins = Utility.CreateAliasArray(MAX_MANNEQUINS, none)
    p_arr_cell_names = Utility.CreateStringArray(p_MAX_CELLS, "")
    p_marker_teleport = none
endFunction

function f_Destroy()
    p_arr_mannequins = new Alias[1]
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Try_Set_Teleport(doticu_npcp_member ref_member)
    if Is_Member_In_Expo(ref_member)
        p_Try_Set_Teleport()
    endIf
endFunction

; Private Methods
function p_Try_Set_Teleport()
    if !Is_Player_In_Expo()
        p_Try_Unset_Teleport()
        p_marker_teleport = CONSTS.ACTOR_PLAYER.PlaceAtMe(CONSTS.STATIC_MARKER_X, 1, false, false)
    endIf
endFunction

function p_Try_Unset_Teleport()
    if p_marker_teleport
        p_marker_teleport.Disable()
        p_marker_teleport.Delete()
        p_marker_teleport = none
    endIf
endFunction

; Public Methods
function Expo(int id_expoee, ObjectReference ref_marker, bool auto_create)
    if id_expoee < 0 || id_expoee >= MAX_MANNEQUINS
        return LOGS.Create_Note("Invalid Expo ID.")
    endIf

    if !ref_marker
        return LOGS.Create_Note("Invalid Expo marker.")
    endIf

    doticu_npcp_member ref_member = p_arr_mannequins[id_expoee] as doticu_npcp_member
    if ref_member && ref_member.Is_Mannequin()
        return LOGS.Create_Note("Expo ID already in use.")
    endIf

    Actor ref_actor = Game.FindClosestActorFromRef(ref_marker, 48)
    if !ref_actor || ref_actor == CONSTS.ACTOR_PLAYER
        LOGS.Create_Note("Move NPC onto pedestal.")
        if !KEYS.Is_Active(VARS.key_n_toggle_move)
            LOGS.Create_Note("(You can set a hotkey for 'Toggle Move' in Settings.)")
        endIf
        return
    endIf

    ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        if auto_create
            int code_return = MEMBERS.Create_Member(ref_actor)
            if code_return < 0
                LOGS.Create_Note("Could not create Expo Member.")
            endIf
        else
            return LOGS.Create_Note("Not a Member to Expo.")
        endIf
    endIf

    p_arr_mannequins[id_expoee] = ref_member

    ref_member.Mannequinize(ref_marker)

    return LOGS.Create_Note(ref_member.Name() + " will now be a mannequin.")
endFunction

function Unexpo(int id_expoee)
    if id_expoee < 0 || id_expoee >= MAX_MANNEQUINS
        return LOGS.Create_Note("Invalid Expo ID.")
    endIf

    doticu_npcp_member ref_member = p_arr_mannequins[id_expoee] as doticu_npcp_member
    if !ref_member || ref_member.Isnt_Mannequin()
        p_arr_mannequins[id_expoee] = none
        return LOGS.Create_Note("No mannequin on pedestal.")
    endIf

    p_arr_mannequins[id_expoee] = none

    ref_member.Unmannequinize()

    return LOGS.Create_Note(ref_member.Name() + " will no longer be a mannequin.")
endFunction

bool function Is_ID_Used(int id_expoee)
    if id_expoee < 0 || id_expoee >= MAX_MANNEQUINS
        return false
    endIf

    return p_arr_mannequins[id_expoee] != none
endFunction

bool function Is_ID_Free(int id_expoee)
    if id_expoee < 0 || id_expoee >= MAX_MANNEQUINS
        return false
    endIf

    return p_arr_mannequins[id_expoee] == none
endFunction

function Refresh_Mannequin(int id_expoee, ObjectReference ref_marker)
    if id_expoee < 0 || id_expoee >= MAX_MANNEQUINS
        return
    endIf

    if !ref_marker
        return
    endIf

    doticu_npcp_member ref_member = p_arr_mannequins[id_expoee] as doticu_npcp_member
    if ref_member
        ref_member.Actor().MoveTo(ref_marker)
    endIf
endFunction

Alias[] function Get_Mannequins(int column = 1, int row = 1, int idx_from = 0, int idx_to_ex = -1)
    if column < 1
        column = 1
    endIf
    if column > MAX_COLUMNS
        column = MAX_COLUMNS
    endIf
    column -= 1

    if row < 1
        row = 1
    endIf
    if row > MAX_ROWS
        row = MAX_ROWS
    endIf
    row -= 1

    if idx_from < 0
        idx_from = 0
    endIf
    if idx_to_ex > p_MAX_MANNEQUINS_PER_CELL || idx_to_ex < 0
        idx_to_ex = p_MAX_MANNEQUINS_PER_CELL
    endIf

    int num_mannequins = idx_to_ex - idx_from
    if num_mannequins < 1
        return Utility.CreateAliasArray(0, none)
    endIf

    Alias[] arr_copy = Utility.CreateAliasArray(num_mannequins, none)
    int idx_orig = column * p_MAX_MANNEQUINS_PER_COLUMN + row * p_MAX_MANNEQUINS_PER_CELL + idx_from
    int idx_copy = 0
    while idx_copy < num_mannequins
        arr_copy[idx_copy] = p_arr_mannequins[idx_orig]
        idx_orig += 1
        idx_copy += 1
    endWhile

    return arr_copy
endFunction

string function Get_Cell_Name(int column, int row)
    if column < 1
        column = 1
    endIf
    if column > MAX_COLUMNS
        column = MAX_COLUMNS
    endIf
    column -= 1

    if row < 1
        row = 1
    endIf
    if row > MAX_ROWS
        row = MAX_ROWS
    endIf
    row -= 1

    int idx_cell_names = column * MAX_ROWS + row

    return p_arr_cell_names[idx_cell_names]
endFunction

function Set_Cell_Name(int column, int row, string str_name)
    if column < 1
        column = 1
    endIf
    if column > MAX_COLUMNS
        column = MAX_COLUMNS
    endIf
    column -= 1

    if row < 1
        row = 1
    endIf
    if row > MAX_ROWS
        row = MAX_ROWS
    endIf
    row -= 1

    int idx_cell_names = column * MAX_ROWS + row
    p_arr_cell_names[idx_cell_names] = str_name
endFunction

function Move_Player_To_Cell(int column, int row)
    p_Try_Set_Teleport()

    if column < 1
        column = 1
    endIf
    if column > MAX_COLUMNS
        column = MAX_COLUMNS
    endIf
    column -= 1

    if row < 1
        row = 1
    endIf
    if row > MAX_ROWS
        row = MAX_ROWS
    endIf
    row -= 1

    int idx_cell = column * MAX_ROWS + row
    CONSTS.ACTOR_PLAYER.MoveTo(CONSTS.FORMLIST_MARKERS_EXPO_CELL.GetAt(idx_cell) as ObjectReference)
endFunction

function Remove_Player()
    if Is_Player_In_Expo()
        if p_marker_teleport
            CONSTS.ACTOR_PLAYER.MoveTo(p_marker_teleport)
            p_Try_Unset_Teleport()
        else
            CONSTS.ACTOR_PLAYER.MoveTo(CONSTS.MARKER_GOTO_SAFE)
        endIf
    endIf
endFunction

function Move_Player_To_Antechamber()
    p_Try_Set_Teleport()

    CONSTS.ACTOR_PLAYER.MoveTo(CONSTS.MARKER_EXPO_ANTECHAMBER)
endFunction

bool function Is_Player_In_Expo()
    return CONSTS.ACTOR_PLAYER.IsInLocation(CONSTS.LOCATION_EXPO)
endFunction

bool function Is_Member_In_Expo(doticu_npcp_member ref_member)
    return ref_member && ref_member.Exists() && ref_member.Actor().IsInLocation(CONSTS.LOCATION_EXPO)
endFunction

int function Get_Expo_Count()
    ; this should actually return the number of mannequins in expo, because when we add loose mannequins, they'll conflate
    return MEMBERS.Count_Mannequins(); this will count loose mannequins too, so send c++ the array in this module to count
endFunction

int function Get_Max()
    return MAX_MANNEQUINS
endFunction
