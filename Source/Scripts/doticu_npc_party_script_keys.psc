Scriptname doticu_npc_party_script_keys extends Quest

; Private Constants
doticu_npc_party_script_vars    p_VARS      = none
doticu_npc_party_script_members p_MEMBERS   = none
doticu_npc_party_script_control p_CONTROL   = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_VARS = DATA.VARS
    p_MEMBERS = DATA.MODS.MEMBERS
    p_CONTROL = DATA.MODS.CONTROL

    Update_Keys()
endFunction

; Public Methods
function Update_Keys()
    UnregisterForAllKeys()

    if p_VARS.key_member > -1
        RegisterForKey(p_VARS.key_member)
    endIf
    if p_VARS.key_unmember > -1
        RegisterForKey(p_VARS.key_unmember)
    endIf
    if p_VARS.key_access > -1
        RegisterForKey(p_VARS.key_access)
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
    if p_VARS.key_toggle_follower > -1
        RegisterForKey(p_VARS.key_toggle_follower)
    endIf
    if p_VARS.key_toggle_sneak > -1
        RegisterForKey(p_VARS.key_toggle_sneak)
    endIf
endFunction

; Events
event OnKeyDown(int code_key)
    Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor

    if code_key == p_VARS.key_member
        p_CONTROL.Member(ref_actor)
    elseIf code_key == p_VARS.key_unmember
        p_CONTROL.Unmember(ref_actor)
    elseIf code_key == p_VARS.key_access
        p_CONTROL.Access(ref_actor, true)
    elseIf code_key == p_VARS.key_settle
        p_CONTROL.Settle(ref_actor, true)
    elseIf code_key == p_VARS.key_unsettle
        p_CONTROL.Unsettle(ref_actor, true)
    elseIf code_key == p_VARS.key_immobilize
        p_CONTROL.Immobilize(ref_actor, true)
    elseIf code_key == p_VARS.key_mobilize
        p_CONTROL.Mobilize(ref_actor, true)
    elseIf code_key == p_VARS.key_follow
        p_CONTROL.Follow(ref_actor, true)
    elseIf code_key == p_VARS.key_unfollow
        p_CONTROL.Unfollow(ref_actor, true)
    elseIf code_key == p_VARS.key_sneak
        p_CONTROL.Sneak(ref_actor, true)
    elseIf code_key == p_VARS.key_unsneak
        p_CONTROL.Unsneak(ref_actor, true)
    elseIf code_key == p_VARS.key_toggle_member
        p_CONTROL.Toggle_Member(ref_actor)
    elseIf code_key == p_VARS.key_toggle_settler
        p_CONTROL.Toggle_Settler(ref_actor)
    elseIf code_key == p_VARS.key_toggle_immobile
        p_CONTROL.Toggle_Immobile(ref_actor)
    elseIf code_key == p_VARS.key_toggle_follower
        p_CONTROL.Toggle_Follower(ref_actor)
    elseIf code_key == p_VARS.key_toggle_sneak
        p_CONTROL.Toggle_Sneak(ref_actor)
    endIf
endEvent
