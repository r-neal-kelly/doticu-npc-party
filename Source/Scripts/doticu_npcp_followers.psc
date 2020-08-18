;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_followers extends Quest

; Native Methods
Alias function p_From_Actor(Actor ref_actor) native
Alias function p_From_Horse_Actor(Actor ref_actor) native

bool function Are_In_Combat() native

int function Max() native
int function Count_Filled() native
int function Count_Unfilled() native
int function Count_Mobile() native
int function Count_Immobile() native
int function Count_Settlers() native
int function Count_Non_Settlers() native
int function Count_Sneaks() native
int function Count_Non_Sneaks() native
int function Count_Saddlers() native
int function Count_Non_Saddlers() native
int function Count_Retreaters() native
int function Count_Non_Retreaters() native

Alias[] function Sort_Filled(int begin, int end) native

int function Enforce() native
int function Resurrect() native
int function Mobilize() native
int function Immobilize() native
int function Settle() native
int function Resettle() native
int function Unsettle() native
int function Enthrall() native
int function Unthrall() native
int function Paralyze() native
int function Unparalyze() native
int function Sneak() native
int function Unsneak() native
int function Saddle() native
int function Unsaddle() native
int function Retreat() native
int function Unretreat() native
int function Unfollow() native
int function Unmember() native

int function Summon_Filled(float radius = 140.0, float degree = 0.0, float interval = 19.0) native
int function Summon_Mobile(float radius = 140.0, float degree = 0.0, float interval = 19.0) native
int function Summon_Immobile(float radius = 140.0, float degree = 0.0, float interval = 19.0) native

int function Catch_Up() native
int function Stash() native

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
