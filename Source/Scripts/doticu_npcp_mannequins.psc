; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mannequins extends Quest

Alias[]         p_arr_mannequins    =  none
string[]        p_arr_cell_names    =  none
ObjectReference p_marker_teleport   =  none

function f_Initialize() native
function f_Unintialize() native

; these will all be deleted
int property SLOTS = 1024 autoReadOnly
int property CELLS = 64 autoReadOnly
int property SLOTS_PER_CELL = 16 autoReadOnly
int property ROWS = 8 autoReadOnly
int property COLUMNS = 8 autoReadOnly
int property SLOTS_PER_COLUMN = 128 autoReadOnly

string function Get_Cell_Name(int column, int row) native
function Set_Cell_Name(int column, int row, string name) native

int function Count_Expoees() native
Alias[] function Expoees(int column, int row) native
function Enforce_Expoee(int expoee_id, ObjectReference marker) native

bool function Is_Player_In_Expo() native

function Move_Player_To_Cell(int column, int row) native
function Move_Player_To_Antechamber() native
function Remove_Player() native
