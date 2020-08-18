;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_follower extends ReferenceAlias

; Modules
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty
doticu_npcp_player property PLAYER hidden
    doticu_npcp_player function Get()
        return doticu_npcp.Funcs().ACTORS.PLAYER
    endFunction
endProperty

; Private Variables
Actor                   p_ref_actor                 =  none
doticu_npcp_member      p_ref_member                =  none
doticu_npcp_horse       p_ref_horse                 =  none

bool                    p_is_sneak                  = false
bool                    p_is_saddler                = false
bool                    p_is_retreater              = false

int                     p_prev_relationship_rank    =    -1
float                   p_prev_waiting_for_player   =  -1.0
float                   p_prev_speed_mult           =  -1.0
bool                    p_prev_faction_bard_no_auto = false

; Native Methods
Actor function Actor() native
int function ID() native

string function Name() native

bool function Is_Filled() native
bool function Is_Unfilled() native

int function Sneak() native
int function Unsneak() native
int function Saddle() native
int function Unsaddle() native
int function Retreat() native
int function Unretreat() native

function p_Rename(string new_name) native

; Friend Methods
function f_Register()
    RegisterForModEvent("doticu_npcp_cell_change", "On_Cell_Change")
endFunction

function f_Unregister()
    UnregisterForAllModEvents()
endFunction

; Public Methods
function Enforce()
    p_ref_member.Enforce()
endFunction

bool function Exists()
    return Is_Filled()
endFunction

doticu_npcp_member function Get_Member()
    if !Exists() || !p_ref_member.Exists()
        return none
    else
        return p_ref_member
    endIf
endFunction

int function Rename(string str_name)

    int code_return = p_ref_member.Rename(str_name)
    if code_return != doticu_npcp_codes.SUCCESS()
        return code_return
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Unfollow()
    return p_ref_member.Unfollow()
endFunction

int function Pack(int code_exec)
    return p_ref_member.Pack(code_exec)
endFunction

int function Stash()
    return p_ref_member.Stash()
endFunction

int function Settle()
    if Is_Settler()
        return p_ref_member.Resettle()
    else
        return p_ref_member.Settle()
    endIf
endFunction

int function Unsettle()
    return p_ref_member.Unsettle()
endFunction

int function Immobilize()
    return p_ref_member.Immobilize()
endFunction

int function Mobilize()
    return p_ref_member.Mobilize()
endFunction

int function Unmember()
    return p_ref_member.Unmember()
endFunction

int function Unclone()
    return p_ref_member.Unclone()
endFunction

bool function Is_Sneak()
    return Exists() && p_is_sneak
endFunction

bool function Is_Unsneak()
    return Exists() && !p_is_sneak
endFunction

bool function Is_Saddler()
    return Exists() && p_is_saddler
endFunction

bool function Isnt_Saddler()
    return Exists() && !p_is_saddler
endFunction

bool function Is_Retreater()
    return Exists() && p_is_retreater
endFunction

bool function Isnt_Retreater()
    return Exists() && !p_is_retreater
endFunction

bool function Is_Settler()
    return Exists() && p_ref_member.Is_Settler()
endFunction

bool function Is_Immobile()
    return Exists() && p_ref_member.Is_Immobile()
endFunction

bool function Is_Mobile()
    return Exists() && p_ref_member.Is_Mobile()
endFunction

bool function Is_Paralyzed()
    return Exists() && p_ref_member.Is_Paralyzed()
endFunction

bool function Is_Mannequin()
    return Exists() && p_ref_member.Is_Mannequin()
endFunction

bool function Is_In_Combat()
    return Exists() && p_ref_member.Is_In_Combat()
endFunction

bool function Is_Alive()
    return Exists() && ACTORS.Is_Alive(p_ref_actor)
endFunction

bool function Is_Dead()
    return Exists() && ACTORS.Is_Dead(p_ref_actor)
endFunction

function Summon(int distance = 60, int angle = 0)
    p_ref_member.Summon(distance, angle)
endFunction

function Resurrect()
    p_ref_member.Resurrect()
endFunction

; Events
event OnCombatStateChanged(Actor ref_target, int code_combat)
    if code_combat == doticu_npcp_codes.COMBAT_NO()
        
    elseIf code_combat == doticu_npcp_codes.COMBAT_YES()
        ACTORS.PLAYER.f_Begin_Combat()
    elseIf code_combat == doticu_npcp_codes.COMBAT_SEARCHING()

    endIf
endEvent

event On_Cell_Change(Form cell_new, Form cell_old)
    if Exists()
        Enforce()
    endIf
endEvent

event On_Followers_Enforce(Form form_tasklist)
    if Exists()
        Enforce()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Resurrect(Form form_tasklist)
    if Exists() && Is_Dead()
        Resurrect()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Sneak(Form form_tasklist)
    if Exists() && Is_Unsneak()
        Sneak()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unsneak(Form form_tasklist)
    if Exists() && Is_Sneak()
        Unsneak()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Saddle(Form form_tasklist)
    if Exists() && Isnt_Saddler()
        Saddle()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unsaddle(Form form_tasklist)
    if Exists() && Is_Saddler()
        Unsaddle()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Retreat(Form form_tasklist)
    if Exists() && Isnt_Retreater()
        Retreat()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unretreat(Form form_tasklist)
    if Exists() && Is_Retreater()
        Unretreat()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unfollow(Form form_tasklist)
    if Exists()
        Unfollow()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unmember(Form form_tasklist)
    if Exists()
        Unmember()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent
