Scriptname doticu_npc_party_script_dialogue extends Quest

; Private Constants
doticu_npc_party_script_codes   p_CODES     = none
doticu_npc_party_script_members p_MEMBERS   = none

; Private Methods
doticu_npc_party_script_member function p_Get_Member(Actor ref_actor)
    if !ref_actor
        Debug.Notification("ERROR: Not an actor")
        return none
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        Debug.Notification("ERROR: Not a member")
        return none
    endIf

    return ref_member
endFunction

function p_Handle_If_Error(int code_return)
    if code_return == p_CODES.NO_ACTOR
        Debug.Notification("ERROR: Not an actor")
    elseIf code_return == p_CODES.NO_MEMBER
        Debug.Notification("ERROR: Not a member")
    elseIf code_return == p_CODES.NO_SETTLER
        Debug.Notification("ERROR: Not a settler")
    elseIf code_return == p_CODES.NO_IMMOBILE
        Debug.Notification("ERROR: Not an immobile")
    elseIf code_return == p_CODES.EXISTS
        Debug.Notification("ERROR: Could not create")
    elseIf code_return < 0
        Debug.Notification("ERROR: Unknown")
    endIf
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CODES = DATA.CODES
    p_MEMBERS = DATA.MODS.MEMBERS
endFunction

; Public Methods
function Member_Access(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Handle_If_Error(ref_member.Access())
endFunction

function Member_Settle(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Handle_If_Error(ref_member.Settle())
endFunction

function Member_Unsettle(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Handle_If_Error(ref_member.Unsettle())
endFunction

function Member_Immobilize(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Handle_If_Error(ref_member.Immobilize())
endFunction

function Member_Mobilize(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Handle_If_Error(ref_member.Mobilize())
endFunction

function Member_Follow(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Handle_If_Error(ref_member.Follow())
endFunction

function Member_Unfollow(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Handle_If_Error(ref_member.Unfollow())
endFunction
