Scriptname doticu_npc_party_script_main extends Quest

; Private Constants
doticu_npc_party_script_data p_DATA = none

; Public Constants
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

; Friend Methods
function f_Register()
    DATA.f_Register()
    DATA.MODS.FUNCS.f_Register()
    DATA.MODS.MEMBERS.f_Register()
    DATA.MODS.FOLLOWERS.f_Register()
    DATA.MODS.CONTROL.f_Register()

    RegisterForModEvent("doticu_npc_party_player_load_game", "On_Player_Load_Game")
endFunction

; Private Methods
function p_Initialize()
    DATA.f_Initialize()
    DATA.MODS.FUNCS.f_Initialize(DATA)
    DATA.MODS.MEMBERS.f_Initialize(DATA)
    DATA.MODS.FOLLOWERS.f_Initialize(DATA)
    DATA.MODS.CONTROL.f_Initialize(DATA)

    f_Register()

    DATA.MODS.FUNCS.LOGS.Create_Note("Thank you for installing!")
endFunction

; Events
event OnInit()
    Utility.Wait(3)
    p_Initialize()
endEvent

event On_Player_Load_Game()
endEvent
