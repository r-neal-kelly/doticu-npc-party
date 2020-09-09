;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

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
bool                    p_is_created        = false
bool                    p_has_display       = false
int                     p_idx_display       =     0
ObjectReference         p_marker_display    =  none

; Native Methods
Alias function p_From_Actor(Actor ref_actor)    native

bool function Has_Actor(Actor ref_actor)    native
bool function Has_Base(Actor ref_actor)     native
bool function Has_Head(Actor ref_actor)     native

int function Max()                          native
int function Count_Filled()                 native
int function Count_Base(Actor ref_actor)    native
int function Count_Heads(Actor ref_actor)   native

Alias[] function Sort_Filled(int begin = 0, int end = -1) native

string[] function Race_Names() native

function Enforce_Loaded(bool do_resurrect = false) native

; Friend Methods
function f_Create()
    p_is_created = true
    p_has_display = false
    p_idx_display = -1
    p_marker_display = none
endFunction

function f_Destroy()
    p_marker_display = none
    p_idx_display = -1
    p_has_display = false
    p_is_created = false
endFunction

function f_Register()
    int filled_count = Count_Filled()
    if VARS.max_members < filled_count
        VARS.max_members = filled_count
    endIf
endFunction

; Public Methods
doticu_npcp_member function Get_Member(Actor ref_actor)
    return p_From_Actor(ref_actor) as doticu_npcp_member
endFunction
