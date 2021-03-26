; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_main extends Quest

bool    is_initialized  = false

int     major_version   = 0
int     minor_version   = 0
int     patch_version   = 0

function Execute_Package(Package ref_package, Actor ref_actor) native global
function Execute_Perk(Perk ref_perk, ObjectReference ref_target, Actor ref_actor) native global
function Execute_Topic_Info(TopicInfo topic_info, ObjectReference ref) native global
