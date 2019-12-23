Scriptname doticu_npcp_mods extends Quest

; Private Constants
doticu_npcp_resets      p_RESETS    = none
doticu_npcp_data        p_DATA      = none
doticu_npcp_funcs       p_FUNCS     = none
doticu_npcp_members     p_MEMBERS   = none
doticu_npcp_followers   p_FOLLOWERS = none
doticu_npcp_control     p_CONTROL   = none
doticu_npcp_main        p_MAIN      = none

; Public Constants
doticu_npcp_resets property RESETS
    doticu_npcp_resets function Get()
        return p_RESETS
    endFunction
    function Set(doticu_npcp_resets val)
        if p_RESETS == none
            p_RESETS = val
        endIf
    endFunction
endProperty

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

doticu_npcp_funcs property FUNCS
    doticu_npcp_funcs function Get()
        return p_FUNCS
    endFunction
    function Set(doticu_npcp_funcs val)
        if p_FUNCS == none
            p_FUNCS = val
        endIf
    endFunction
endProperty

doticu_npcp_members property MEMBERS
    doticu_npcp_members function Get()
        return p_MEMBERS
    endFunction
    function Set(doticu_npcp_members val)
        if p_MEMBERS == none
            p_MEMBERS = val
        endIf
    endFunction
endProperty

doticu_npcp_followers property FOLLOWERS
    doticu_npcp_followers function Get()
        return p_FOLLOWERS
    endFunction
    function Set(doticu_npcp_followers val)
        if p_FOLLOWERS == none
            p_FOLLOWERS = val
        endIf
    endFunction
endProperty

doticu_npcp_control property CONTROL
    doticu_npcp_control function Get()
        return p_CONTROL
    endFunction
    function Set(doticu_npcp_control val)
        if p_CONTROL == none
            p_CONTROL = val
        endIf
    endFunction
endProperty

doticu_npcp_main property MAIN
    doticu_npcp_main function Get()
        return p_MAIN
    endFunction
    function Set(doticu_npcp_main val)
        if p_MAIN == none
            p_MAIN = val
        endIf
    endFunction
endProperty
