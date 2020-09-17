; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_followers extends Quest

; Native Methods
Alias function From_Actor(Actor ref_actor) native
int function Level() native
int function Unlevel() native

doticu_npcp_follower function Get_Follower(Actor ref_actor)
    return From_Actor(ref_actor) as doticu_npcp_follower
endFunction
