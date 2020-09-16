; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp hidden

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

function Execute_Package(Package ref_package, Actor ref_actor) native global
function Execute_Perk(Perk ref_perk, ObjectReference ref_target, Actor ref_actor) native global
function Execute_Topic_Info(TopicInfo topic_info, ObjectReference ref) native global

; the following shall eventually be removed
function Print(string str) native global
int[] function New_Int_Array(int size = 0, int fill = 0) native global
