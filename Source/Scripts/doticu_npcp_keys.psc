Scriptname doticu_npcp_keys extends Quest

; Private Constants
doticu_npcp_vars        p_VARS      = none
doticu_npcp_funcs       p_FUNCS     = none
doticu_npcp_members     p_MEMBERS   = none
doticu_npcp_followers   p_FOLLOWERS = none
doticu_npcp_commands    p_COMMANDS  = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_VARS = DATA.VARS
    p_FUNCS = DATA.MODS.FUNCS
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
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

    if p_VARS.key_fs_summon_all > -1
        RegisterForKey(p_VARS.key_fs_summon_all)
    endIf
    if p_VARS.key_fs_summon_mobile > -1
        RegisterForKey(p_VARS.key_fs_summon_mobile)
    endIf
    if p_VARS.key_fs_summon_immobile > -1
        RegisterForKey(p_VARS.key_fs_summon_immobile)
    endIf
    if p_VARS.key_fs_settle > -1
        RegisterForKey(p_VARS.key_fs_settle)
    endIf
    if p_VARS.key_fs_unsettle > -1
        RegisterForKey(p_VARS.key_fs_unsettle)
    endIf
    if p_VARS.key_fs_immobilize > -1
        RegisterForKey(p_VARS.key_fs_immobilize)
    endIf
    if p_VARS.key_fs_mobilize > -1
        RegisterForKey(p_VARS.key_fs_mobilize)
    endIf
    if p_VARS.key_fs_sneak > -1
        RegisterForKey(p_VARS.key_fs_sneak)
    endIf
    if p_VARS.key_fs_unsneak > -1
        RegisterForKey(p_VARS.key_fs_unsneak)
    endIf
    if p_VARS.key_fs_unfollow > -1
        RegisterForKey(p_VARS.key_fs_unfollow)
    endIf
    if p_VARS.key_fs_unmember > -1
        RegisterForKey(p_VARS.key_fs_unmember)
    endIf
    if p_VARS.key_fs_resurrect > -1
        RegisterForKey(p_VARS.key_fs_resurrect)
    endIf

    if p_VARS.key_resurrect > -1
        RegisterForKey(p_VARS.key_resurrect)
    endIf
    if p_VARS.key_pack > -1
        RegisterForKey(p_VARS.key_pack)
    endIf
    if p_VARS.key_outfit > -1
        RegisterForKey(p_VARS.key_outfit)
    endIf

    if p_VARS.key_toggle_member > -1
        RegisterForKey(p_VARS.key_toggle_member)
    endIf
    if p_VARS.key_toggle_settler > -1
        RegisterForKey(p_VARS.key_toggle_settler)
    endIf
    if p_VARS.key_toggle_enthrall > -1
        RegisterForKey(p_VARS.key_toggle_enthrall)
    endIf
    if p_VARS.key_toggle_immobile > -1
        RegisterForKey(p_VARS.key_toggle_immobile)
    endIf
    if p_VARS.key_toggle_paralyzed > -1
        RegisterForKey(p_VARS.key_toggle_paralyzed)
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
    if p_VARS.key_cycle_vitality > -1
        RegisterForKey(p_VARS.key_cycle_vitality)
    endIf
    if p_VARS.key_cycle_outfit > -1
        RegisterForKey(p_VARS.key_cycle_outfit)
    endIf
endFunction

; Events
event On_Load_Mod()
endEvent

event OnKeyDown(int code_key)
    if Utility.IsInMenuMode()
        return
    endIf
    
    Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor

    ; need to cancel if in menu mode, because we don't want crap to happen when in console or menu!

    ; can add a 'Yell' command to topics, so that all funcs can be used in dialogue

    ; these should be sent to commands for notes!
    if code_key == p_VARS.key_fs_summon_all
        p_COMMANDS.Followers_Summon_All()
    elseIf code_key == p_VARS.key_fs_summon_mobile
        p_COMMANDS.Followers_Summon_Mobile()
    elseIf code_key == p_VARS.key_fs_summon_immobile
        p_COMMANDS.Followers_Summon_Immobile()
    
    elseIf code_key == p_VARS.key_resurrect
        p_COMMANDS.Resurrect(ref_actor, true)
    elseIf code_key == p_VARS.key_pack
        p_COMMANDS.Pack(ref_actor, true)
    elseIf code_key == p_VARS.key_outfit; this needs to be expanded to a cycle
        p_COMMANDS.Outfit(ref_actor, "member", true)
    
    elseIf code_key == p_VARS.key_toggle_member
        p_COMMANDS.Toggle_Member(ref_actor)
    elseIf code_key == p_VARS.key_toggle_settler
        p_COMMANDS.Toggle_Settler(ref_actor)
    elseIf code_key == p_VARS.key_toggle_enthrall
        p_COMMANDS.Toggle_Thrall(ref_actor)
    elseIf code_key == p_VARS.key_toggle_immobile
        p_COMMANDS.Toggle_Immobile(ref_actor)
    elseIf code_key == p_VARS.key_toggle_paralyzed
        p_COMMANDS.Toggle_Paralyzed(ref_actor)
    elseIf code_key == p_VARS.key_toggle_follower
        p_COMMANDS.Toggle_Follower(ref_actor)
    elseIf code_key == p_VARS.key_toggle_sneak
        p_COMMANDS.Toggle_Sneak(ref_actor)
    
    elseIf code_key == p_VARS.key_cycle_style
        p_COMMANDS.Cycle_Style(ref_actor)
    endIf
endEvent
