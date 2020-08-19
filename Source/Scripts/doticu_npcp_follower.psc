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

bool    function Is_Filled()        native
bool    function Is_Unfilled()      native
bool    function Is_Mobile()        native
bool    function Is_Immobile()      native
bool    function Is_Sneak()         native
bool    function Isnt_Sneak()       native
bool    function Is_Saddler()       native
bool    function Isnt_Saddler()     native
bool    function Is_Retreater()     native
bool    function Isnt_Retreater()   native

int     function Sneak()            native
int     function Unsneak()          native
int     function Saddle()           native
int     function Unsaddle()         native
int     function Retreat()          native
int     function Unretreat()        native
