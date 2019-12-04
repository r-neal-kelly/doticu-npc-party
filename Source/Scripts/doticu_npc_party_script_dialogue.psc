Scriptname doticu_npc_party_script_dialogue extends Quest

; Private Constants
doticu_npc_party_script_codes   p_CODES     = none
doticu_npc_party_script_members p_MEMBERS   = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CODES = DATA.CODES
    p_MEMBERS = DATA.MODS.MEMBERS
endFunction

; Public Methods
function Member_Access(Actor ref_actor)
    ;;;;;testing
    Debug.Notification("this is a test")
    ;;;;;

    int code_return

    if !ref_actor
        Debug.Notification("ERROR: Not an actor")
        return
    endIf
    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        Debug.Notification("ERROR: Not a member")
        return
    endIf
    
    code_return = ref_member.Access()
    if code_return == p_CODES.NO_MEMBER
        Debug.Notification("ERROR: Not a member")
        return
    else
    endIf
endFunction
