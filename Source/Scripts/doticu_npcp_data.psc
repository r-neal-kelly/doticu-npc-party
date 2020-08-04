;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_data extends Quest

; Private Constants
doticu_npcp_mods    p_MODS          =  none; static
doticu_npcp_vars    p_VARS          =  none; dynamic

; Private Variables
bool                p_is_created    = false

; Public Constants
doticu_npcp_mods property MODS
    doticu_npcp_mods function Get()
        return p_MODS
    endFunction
    function Set(doticu_npcp_mods val)
        if p_MODS == none
            p_MODS = val
        endIf
    endFunction
endProperty

doticu_npcp_vars property VARS
    doticu_npcp_vars function Get()
        return p_VARS
    endFunction
    function Set(doticu_npcp_vars val)
        if p_VARS == none
            p_VARS = val
        endIf
    endFunction
endProperty

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction
