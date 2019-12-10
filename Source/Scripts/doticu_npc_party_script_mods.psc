Scriptname doticu_npc_party_script_mods extends Quest

; Private Constants
doticu_npc_party_script_main        p_MAIN      = none
doticu_npc_party_script_data        p_DATA      = none
doticu_npc_party_script_funcs       p_FUNCS     = none
doticu_npc_party_script_members     p_MEMBERS   = none
doticu_npc_party_script_followers   p_FOLLOWERS = none
doticu_npc_party_script_control     p_CONTROL   = none

; Public Constants
doticu_npc_party_script_main property MAIN
    doticu_npc_party_script_main function Get()
        return p_MAIN
    endFunction
    function Set(doticu_npc_party_script_main val)
        if p_MAIN == none
            p_MAIN = val
        endIf
    endFunction
endProperty

doticu_npc_party_script_data property DATA
    doticu_npc_party_script_data function Get()
        return p_DATA
    endFunction
    function Set(doticu_npc_party_script_data val)
        if p_DATA == none
            p_DATA = val
        endIf
    endFunction
endProperty

doticu_npc_party_script_funcs property FUNCS
    doticu_npc_party_script_funcs function Get()
        return p_FUNCS
    endFunction
    function Set(doticu_npc_party_script_funcs val)
        if p_FUNCS == none
            p_FUNCS = val
        endIf
    endFunction
endProperty

doticu_npc_party_script_members property MEMBERS
    doticu_npc_party_script_members function Get()
        return p_MEMBERS
    endFunction
    function Set(doticu_npc_party_script_members val)
        if p_MEMBERS == none
            p_MEMBERS = val
        endIf
    endFunction
endProperty

doticu_npc_party_script_followers property FOLLOWERS
    doticu_npc_party_script_followers function Get()
        return p_FOLLOWERS
    endFunction
    function Set(doticu_npc_party_script_followers val)
        if p_FOLLOWERS == none
            p_FOLLOWERS = val
        endIf
    endFunction
endProperty

doticu_npc_party_script_control property CONTROL
    doticu_npc_party_script_control function Get()
        return p_CONTROL
    endFunction
    function Set(doticu_npc_party_script_control val)
        if p_CONTROL == none
            p_CONTROL = val
        endIf
    endFunction
endProperty
