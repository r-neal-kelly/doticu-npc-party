;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp hidden

; aliases
Alias[] function Aliases_Slice(Alias[] arr_aliases, int idx_from, int idx_to_ex) native global
Alias[] function Aliases_Sort(Alias[] arr_aliases, string str_algorithm = "") native global
Alias[] function Aliases_Filter(Alias[] arr_aliases, string str_sex, string str_race, int int_flags) native global
int function Aliases_Filter_Flag(int int_flags, string str_command, string str_flag) native global
string[] function Aliases_Get_Race_Names(Alias[] arr_aliases) native global
int[] function Aliases_Update_Free(int[] arr_free, int size_new) native global

; forms
Form[] function Forms_Slice(Form[] arr_forms, int idx_from, int idx_to_ex) native global

; outfit
function Outfit_Add_Item(Outfit outfit_outfit, Form form_item) native global
function Outfit_Remove_Item(Outfit outfit_outfit, Form form_item) native global

; utils
function Print(string str) native global
