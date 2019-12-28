Scriptname doticu_npcp_keys extends Quest

; Private Constants
doticu_npcp_vars        p_VARS      = none
doticu_npcp_funcs       p_FUNCS     = none
doticu_npcp_members     p_MEMBERS   = none
doticu_npcp_commands    p_COMMANDS  = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_VARS = DATA.VARS
    p_FUNCS = DATA.MODS.FUNCS
    p_MEMBERS = DATA.MODS.MEMBERS
    p_COMMANDS = DATA.MODS.CONTROL.COMMANDS
endFunction

function f_Initialize()
endFunction

function f_Register()
    Update_Keys()
    RegisterForModEvent("doticu_npcp_load_mod", "On_Load_Mod")
endFunction

; Public Methods
function Update_Keys()
    UnregisterForAllKeys()

    if p_VARS.key_open_mcm > -1
        RegisterForKey(p_VARS.key_open_mcm)
    endIf
    if p_VARS.key_resurrect > -1
        RegisterForKey(p_VARS.key_resurrect)
    endIf
    if p_VARS.key_member > -1
        RegisterForKey(p_VARS.key_member)
    endIf
    if p_VARS.key_unmember > -1
        RegisterForKey(p_VARS.key_unmember)
    endIf
    if p_VARS.key_pack > -1
        RegisterForKey(p_VARS.key_pack)
    endIf
    if p_VARS.key_outfit > -1
        RegisterForKey(p_VARS.key_outfit)
    endIf
    if p_VARS.key_settle > -1
        RegisterForKey(p_VARS.key_settle)
    endIf
    if p_VARS.key_unsettle > -1
        RegisterForKey(p_VARS.key_unsettle)
    endIf
    if p_VARS.key_immobilize > -1
        RegisterForKey(p_VARS.key_immobilize)
    endIf
    if p_VARS.key_mobilize > -1
        RegisterForKey(p_VARS.key_mobilize)
    endIf
    if p_VARS.key_follow > -1
        RegisterForKey(p_VARS.key_follow)
    endIf
    if p_VARS.key_unfollow > -1
        RegisterForKey(p_VARS.key_unfollow)
    endIf
    if p_VARS.key_sneak > -1
        RegisterForKey(p_VARS.key_sneak)
    endIf
    if p_VARS.key_unsneak > -1
        RegisterForKey(p_VARS.key_unsneak)
    endIf
    if p_VARS.key_toggle_member > -1
        RegisterForKey(p_VARS.key_toggle_member)
    endIf
    if p_VARS.key_toggle_settler > -1
        RegisterForKey(p_VARS.key_toggle_settler)
    endIf
    if p_VARS.key_toggle_immobile > -1
        RegisterForKey(p_VARS.key_toggle_immobile)
    endIf
    if p_VARS.key_toggle_enthrall > -1
        RegisterForKey(p_VARS.key_toggle_enthrall)
    endIf
    if p_VARS.key_toggle_follower > -1
        RegisterForKey(p_VARS.key_toggle_follower)
    endIf
    if p_VARS.key_toggle_sneak > -1
        RegisterForKey(p_VARS.key_toggle_sneak)
    endIf
    if p_VARS.key_cycle_style > -1
        RegisterForKey(p_VARS.key_cycle_style)
    endIf
endFunction

; Events
event On_Load_Mod()
endEvent

event OnKeyDown(int code_key)
    Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor

    if code_key == p_VARS.key_open_mcm
        p_FUNCS.Open_MCM()
    elseIf code_key == p_VARS.key_resurrect
        p_COMMANDS.Resurrect(ref_actor, true)
    elseIf code_key == p_VARS.key_member
        p_COMMANDS.Member(ref_actor)
    elseIf code_key == p_VARS.key_unmember
        p_COMMANDS.Unmember(ref_actor)
    elseIf code_key == p_VARS.key_pack
        p_COMMANDS.Pack(ref_actor, true)
    elseIf code_key == p_VARS.key_outfit; this needs to be expanded to a cycle
        p_COMMANDS.Outfit(ref_actor, "member", true)
    elseIf code_key == p_VARS.key_settle
        p_COMMANDS.Settle(ref_actor, true)
    elseIf code_key == p_VARS.key_unsettle
        p_COMMANDS.Unsettle(ref_actor, true)
    elseIf code_key == p_VARS.key_immobilize
        p_COMMANDS.Immobilize(ref_actor, true)
    elseIf code_key == p_VARS.key_mobilize
        p_COMMANDS.Mobilize(ref_actor, true)
    elseIf code_key == p_VARS.key_follow
        p_COMMANDS.Follow(ref_actor, true)
    elseIf code_key == p_VARS.key_unfollow
        p_COMMANDS.Unfollow(ref_actor, true)
    elseIf code_key == p_VARS.key_sneak
        p_COMMANDS.Sneak(ref_actor, true)
    elseIf code_key == p_VARS.key_unsneak
        p_COMMANDS.Unsneak(ref_actor, true)
    elseIf code_key == p_VARS.key_toggle_member
        p_COMMANDS.Toggle_Member(ref_actor)
    elseIf code_key == p_VARS.key_toggle_settler
        p_COMMANDS.Toggle_Settler(ref_actor)
    elseIf code_key == p_VARS.key_toggle_immobile
        p_COMMANDS.Toggle_Immobile(ref_actor)
    elseIf code_key == p_VARS.key_toggle_enthrall
        p_COMMANDS.Toggle_Thrall(ref_actor)
    elseIf code_key == p_VARS.key_toggle_follower
        p_COMMANDS.Toggle_Follower(ref_actor)
    elseIf code_key == p_VARS.key_toggle_sneak
        p_COMMANDS.Toggle_Sneak(ref_actor)
    elseIf code_key == p_VARS.key_cycle_style
        p_COMMANDS.Cycle_Style(ref_actor)
    endIf
endEvent
