;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_followers extends Quest

; Native Methods
Alias function p_From_Actor(Actor ref_actor) native
Alias function p_From_Horse_Actor(Actor ref_actor) native

int function Count_Filled() native
Alias[] function Sort_Filled(int begin, int end) native

int function Retreat() native
int function Unretreat() native
int function Catch_Up() native

; Public Methods
doticu_npcp_follower function Get_Follower(Actor ref_actor)
    return p_From_Actor(ref_actor) as doticu_npcp_follower
endFunction

Alias[] function Get_Followers(int begin = 0, int end = -1)
    return Sort_Filled(begin, end)
endFunction

doticu_npcp_follower function From_Horse_Actor(Actor ref_actor)
    return p_From_Horse_Actor(ref_actor) as doticu_npcp_follower
endFunction
