;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp hidden

; Actor
bool function Actor_Has_Changed_Outfit(Actor ref_actor, ObjectReference ref_outfit, ObjectReference ref_outfit2, Form linchpin) native global
function Actor_Refresh_Outfit(Actor ref_actor, ObjectReference ref_outfit, ObjectReference ref_outfit2, Form linchpin) native global

; Aliases
Alias[] function Aliases_Slice(Alias[] arr_aliases, int idx_from, int idx_to_ex) native global
Alias[] function Aliases_Sort(Alias[] arr_aliases, string str_algorithm = "") native global

Alias[] function Aliases_Filter(Alias[] arr_aliases, string[] arr_strings, int[] arr_ints) native global
string[] function Aliases_Filter_Strings(string str_sex = "", string str_race = "", string str_search = "") global
    string[] arr_strings = new string[3]
    arr_strings[0] = str_sex
    arr_strings[1] = str_race
    arr_strings[2] = str_search
    return arr_strings
endFunction
int[] function Aliases_Filter_Ints(int int_style = 0, int int_vitality = 0, int int_rating = -1, int int_flags = 0) global
    int[] arr_ints = new int[4]
    arr_ints[0] = int_style
    arr_ints[1] = int_vitality
    arr_ints[2] = int_rating
    arr_ints[3] = int_flags
    return arr_ints
endFunction
int function Aliases_Filter_Flag(int int_flags, string str_command, string str_flag) native global

string[] function Aliases_Get_Race_Names(Alias[] arr_aliases) native global

; Forms
Form[] function Forms_Slice(Form[] arr_forms, int idx_from, int idx_to_ex) native global

; Object_Ref
function Object_Ref_Log_Items(ObjectReference ref_object) native global

; Outfit
function Outfit_Add_Item(Outfit outfit_outfit, Form form_item) native global
function Outfit_Remove_Item(Outfit outfit_outfit, Form form_item) native global

; Quest
Alias[] function Quest_Get_Used_Aliases(Quest ref_quest) native global
int[] function Quest_Get_Free_Alias_IDs(Quest ref_quest) native global
int function Quest_Count_Used_Aliases(Quest ref_quest) native global
int function Quest_Count_Free_Aliases(Quest ref_quest) native global
int function Quest_Count_Mannequins(Quest ref_quest) native global

; Utils
function Print(string str) native global
function Log(string str) native global
