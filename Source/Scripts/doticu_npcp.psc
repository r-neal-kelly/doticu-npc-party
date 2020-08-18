;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp hidden

; Modules
doticu_npcp_main function Main() global
    return doticu_npcp_consts.Main_Quest() as doticu_npcp_main
endFunction
doticu_npcp_vars function Vars() global
    return doticu_npcp_consts.Vars_Quest() as doticu_npcp_vars
endFunction
doticu_npcp_funcs function Funcs() global
    return doticu_npcp_consts.Funcs_Quest() as doticu_npcp_funcs
endFunction
doticu_npcp_members function Members() global
    return doticu_npcp_consts.Members_Quest() as doticu_npcp_members
endFunction
doticu_npcp_followers function Followers() global
    return doticu_npcp_consts.Followers_Quest() as doticu_npcp_followers
endFunction
doticu_npcp_control function Control() global
    return doticu_npcp_consts.Control_Quest() as doticu_npcp_control
endFunction

; most of the following shall eventually be moved into existing types or remove completely

; Actor
Actor function Actor_Get_Mounted_Actor(Actor ref_horse) native global

; Object_Ref
function Object_Ref_Categorize(ObjectReference ref_obj) native global
function Object_Ref_Log_XContainer(ObjectReference ref_object) native global
function Object_Ref_Log_XList(ObjectReference ref_object) native global

; Tests
function Run_Tests() native global

; Utils
function Print(string str) native global
function Log(string str) native global
int[] function New_Int_Array(int size = 0, int fill = 0) native global
