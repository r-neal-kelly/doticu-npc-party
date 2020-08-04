;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp hidden

; Actor
function Actor_Set_Outfit2(Actor ref_actor, Form linchpin, ObjectReference vanilla, ObjectReference custom, ObjectReference transfer) native global
function Actor_Cache_Worn(Actor ref_actor, Form form_linchpin, ObjectReference ref_cache_out) native global
function Actor_Cache_Inventory(Actor ref_actor, Form form_linchpin, ObjectReference ref_worn_out, ObjectReference ref_pack_out) native global
function Actor_Cache_Static_Inventory(Actor ref_actor, Form form_linchpin, ObjectREference ref_cache_out) native global
function Actor_Reset_Actor_Value(Actor ref_actor, string name) native global
Actor function Actor_Get_Mounted_Actor(Actor ref_horse) native global
function Actor_Log_Factions(Actor ref_actor) native global
function Actor_Resurrect(Actor ref_actor, bool do_reset_inventory) native global

; Cell
bool function Cell_Is_Interior(Cell ref_cell) native global

; Forms
Form[] function Forms_Slice(Form[] arr_forms, int idx_from, int idx_to_ex) native global

; Form
function Form_Log_Flags(Form ref_form) native global

; Game
string[] function Game_Get_Male_Vanilla_Voice_Names() native global
string[] function Game_Get_Female_Vanilla_Voice_Names() native global
VoiceType function Game_Get_Voice_By_Name(string str_name) native global

; Object_Ref
function Object_Ref_Remove_Unwearable(ObjectReference ref_obj, ObjectReference ref_other) native global
function Object_Ref_Categorize(ObjectReference ref_obj) native global
function Object_Ref_Log_XContainer(ObjectReference ref_object) native global
function Object_Ref_Log_XList(ObjectReference ref_object) native global

; Outfit
function Outfit_Add_Item(Outfit outfit_outfit, Form form_item) native global
function Outfit_Remove_Item(Outfit outfit_outfit, Form form_item) native global

; Tests
function Run_Tests() native global

; Utils
function Print(string str) native global
function Log(string str) native global
function Log_Cell(Cell ref_cell) native global
int[] function New_Int_Array(int size = 0, int fill = 0) native global
