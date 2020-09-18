; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_control extends Quest

; Modules
doticu_npcp_commands property COMMANDS
    doticu_npcp_commands function Get()
        return (self as Quest) as doticu_npcp_commands
    endFunction
endProperty
doticu_npcp_keys property KEYS
    doticu_npcp_keys function Get()
        return (self as Quest) as doticu_npcp_keys
    endFunction
endProperty
doticu_npcp_mcm property MCM
    doticu_npcp_mcm function Get()
        return (self as Quest) as doticu_npcp_mcm
    endFunction
endProperty

; Friend Methods
function f_Create()
    MCM.f_Create()
endFunction

function f_Register()
    KEYS.Register()
endFunction
