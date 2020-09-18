; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_members extends Quest

bool                p_has_display       = false
int                 p_idx_display       =     0
ObjectReference     p_marker_display    =  none

Alias function From_Actor(Actor ref_actor) native

doticu_npcp_member function Get_Member(Actor ref_actor)
    return From_Actor(ref_actor) as doticu_npcp_member
endFunction
