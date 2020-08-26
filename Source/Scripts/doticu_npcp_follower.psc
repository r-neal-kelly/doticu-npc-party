; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_follower extends ReferenceAlias

Actor               p_ref_actor                 =  none
doticu_npcp_member  p_ref_member                =  none
doticu_npcp_horse   p_ref_horse                 =  none

bool                p_is_sneak                  = false
bool                p_is_saddler                = false
bool                p_is_retreater              = false

int                 p_prev_relationship_rank    =     0
float               p_prev_waiting_for_player   =   0.0
float               p_prev_speed_mult           =   0.0
bool                p_prev_faction_bard_no_auto = false

int     function ID()               native
Actor   function Actor()            native
Alias   function Member()           native
string  function Name()             native

bool    function Is_Immobile()      native

int     function Retreat()          native
int     function Unretreat()        native
