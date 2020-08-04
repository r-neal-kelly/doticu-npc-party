;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_package_menu extends Package hidden

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty

; Private Constants
doticu_npcp_data p_DATA = none

; Public Constants
doticu_npcp_data property DATA
    doticu_npcp_data function Get()
        return p_DATA
    endFunction
    function Set(doticu_npcp_data val)
        if p_DATA == none
            p_DATA = val
        endIf
    endFunction
endProperty

function Exit_Begin(Actor ref_actor)
    FUNCS.ACTORS.Destroy_Menu()
endFunction
