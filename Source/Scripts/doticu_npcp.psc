;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp hidden

function Outfit_Add_Item(Outfit outfit_outfit, Form form_item) native global
function Outfit_Remove_Item(Outfit outfit_outfit, Form form_item) native global
Alias[] function Sort_Aliases(Alias[] arr_aliases) native global

string[] function Get_Race_Names(Alias[] arr_aliases) native global
int function Filter_Flag(int int_flags, string str_command, string str_flag) native global
Alias[] function Filter_Aliases(Alias[] arr_aliases, string str_sex, string str_race, int int_flags) native global

Alias[] function Aliases_Slice(Alias[] arr_aliases, int idx_from, int idx_to_ex) native global
