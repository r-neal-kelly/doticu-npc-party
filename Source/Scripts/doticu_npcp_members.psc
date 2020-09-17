; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_members extends Quest

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return doticu_npcp.Vars()
    endFunction
endProperty

; Public Constants
int property MIN_DISPLAY                    =     1 autoReadOnly hidden
int property MAX_DISPLAY                    =     8 autoReadOnly hidden
int property DEFAULT_DISPLAY                =     5 autoReadOnly hidden

int property DEFAULT_PERCENT_BODY           =   100 autoReadOnly hidden
int property DEFAULT_PERCENT_FEET           =    90 autoReadOnly hidden
int property DEFAULT_PERCENT_HANDS          =    90 autoReadOnly hidden
int property DEFAULT_PERCENT_HEAD           =    50 autoReadOnly hidden

; Private Variables
bool                    p_has_display       = false
int                     p_idx_display       =     0
ObjectReference         p_marker_display    =  none

; Native Methods
Alias function From_Actor(Actor ref_actor)    native
int function Max()                          native
int function Count_Filled()                 native

function f_Register()
    int filled_count = Count_Filled()
    if VARS.max_members < filled_count
        VARS.max_members = filled_count
    endIf
endFunction

; Public Methods
doticu_npcp_member function Get_Member(Actor ref_actor)
    return From_Actor(ref_actor) as doticu_npcp_member
endFunction
