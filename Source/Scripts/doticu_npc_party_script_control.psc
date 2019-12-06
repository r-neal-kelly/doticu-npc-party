Scriptname doticu_npc_party_script_control extends Quest

; Private Constants
doticu_npc_party_script_codes       p_CODES     = none
doticu_npc_party_script_members     p_MEMBERS   = none
doticu_npc_party_script_followers   p_FOLLOWERS = none
doticu_npc_party_script_dialogue    p_DIALOGUE  = none
doticu_npc_party_script_keys        p_KEYS      = none
doticu_npc_party_script_mcm         p_MCM       = none

; Public Constants
doticu_npc_party_script_dialogue property DIALOGUE
    doticu_npc_party_script_dialogue function Get()
        return p_DIALOGUE
    endFunction
endProperty

doticu_npc_party_script_keys property KEYS
    doticu_npc_party_script_keys function Get()
        return p_KEYS
    endFunction
endProperty

doticu_npc_party_script_mcm property MCM
    doticu_npc_party_script_mcm function Get()
        return p_MCM
    endFunction
endProperty

; Private Methods
function p_Notify_Member(int code)
    if code == p_CODES.NO_ACTOR
        Debug.Notification("Not an npc. Cannot add to party.")
    elseIf code == p_CODES.IS_DUPLICATE
        Debug.Notification("Already has npc. Cannot add to party.")
    elseIf code == p_CODES.OUT_OF_SPACE
        Debug.Notification("Party is full. Cannot add npc.")
    elseIf code == p_CODES.NO_RESURRECT
        Debug.Notification("Failed to resurrect npc. Cannot add to party.")
    elseIf code == p_CODES.FATAL_ERROR
        Debug.Notification("Fatal error. Cannot add to party.")
    elseIf code < 0
        Debug.Notification("Unknown error. Cannot add to party.")
    else
        Debug.Notification("Added npc to party.")
    endIf
endFunction

function p_Notify_Unmember(int code)
    if code == p_CODES.NO_ACTOR
        Debug.Notification("Not an npc. Cannot remove from party.")
    elseIf code == p_CODES.NO_MEMBER
        Debug.Notification("Not a member. Cannot remove from party.")
    elseIf code == p_CODES.FATAL_ERROR
        Debug.Notification("Fatal error. Cannot add to party.")
    elseIf code < 0
        Debug.Notification("Unknown error. Cannot remove npc.")
    else
        Debug.Notification("Removed npc from party.")
    endIf
endFunction

function p_Notify_Follow(int code)
    if code == p_CODES.NO_ACTOR
        Debug.Notification("Not an npc. Cannot add to followers.")
    elseIf code == p_CODES.IS_DUPLICATE
        Debug.Notification("Is already a follower.")
    elseIf code == p_CODES.OUT_OF_SPACE
        Debug.Notification("Cannot add any more followers.")
    elseIf code == p_CODES.FATAL_ERROR
        Debug.Notification("Fatal error. Cannot add to followers.")
    elseIf code < 0
        Debug.Notification("Unknown error. Cannot add to followers.")
    else
        Debug.Notification("Added member to followers.")
    endIf
endFunction

function p_Notify_Unfollow(int code)
    if code == p_CODES.NO_ACTOR
        Debug.Notification("Not an npc. Cannot remove from followers.")
    elseIf code == p_CODES.NO_MEMBER
        Debug.Notification("Not a follower. Cannot remove from followers.")
    elseIf code == p_CODES.FATAL_ERROR
        Debug.Notification("Fatal error. Cannot add to followers.")
    elseIf code < 0
        Debug.Notification("Unknown error. Cannot remove follower.")
    else
        Debug.Notification("Removed member from followers.")
    endIf
endFunction

function p_Notify(int code)
    ; these should never be seen
    if code == p_CODES.IS_DUPLICATE
        Debug.Notification("ERROR: Is a duplicate")
    elseIf code == p_CODES.OUT_OF_SPACE
        Debug.Notification("ERROR: Out of space")
    elseIf code == p_CODES.NO_ACTOR
        Debug.Notification("ERROR: Not an actor")
    elseIf code == p_CODES.NO_MEMBER
        Debug.Notification("ERROR: Not a member")
    elseIf code == p_CODES.NO_SETTLER
        Debug.Notification("ERROR: Not a settler")
    elseIf code == p_CODES.NO_IMMOBILE
        Debug.Notification("ERROR: Not an immobile")
    elseIf code == p_CODES.NO_FOLLOWER
        Debug.Notification("ERROR: Not a follower")
    elseIf code == p_CODES.EXISTS
        Debug.Notification("ERROR: Already exists")
    elseIf code < 0
        Debug.Notification("ERROR: Unknown")
    endIf
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CODES = DATA.CODES
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_DIALOGUE = (self as Quest) as doticu_npc_party_script_dialogue
    p_KEYS = (self as Quest) as doticu_npc_party_script_keys
    p_MCM = (self as Quest) as doticu_npc_party_script_mcm

    p_DIALOGUE.f_Initialize(DATA)
    p_KEYS.f_Initialize(DATA)
endFunction

; Public Methods
doticu_npc_party_script_member function Get_Member(Actor ref_actor)
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

doticu_npc_party_script_settler function Get_Settler(Actor ref_actor)
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return none
    endIf

    doticu_npc_party_script_settler ref_settler = ref_member.Get_Settler()
    if !ref_settler
        Debug.Notification("ERROR: Not a settler")
        return none
    endIf

    return ref_settler
endFunction

doticu_npc_party_script_immobile function Get_Immobile(Actor ref_actor)
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return none
    endIf

    doticu_npc_party_script_immobile ref_immobile = ref_member.Get_Immobile()
    if !ref_immobile
        Debug.Notification("ERROR: Not an immobile")
        return none
    endIf

    return ref_immobile
endFunction

doticu_npc_party_script_follower function Get_Follower(Actor ref_actor)
    if !ref_actor
        Debug.Notification("ERROR: Not an actor")
        return none
    endIf

    doticu_npc_party_script_follower ref_follower = p_FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        Debug.Notification("ERROR: Not a follower")
        return none
    endIf

    return ref_follower
endFunction

; Public Methods
function Member(Actor ref_actor)
    p_Notify_Member(p_MEMBERS.Create_Member(ref_actor))
endFunction

function Unmember(Actor ref_actor)
    p_Notify_Unmember(p_MEMBERS.Destroy_Member(ref_actor))
endFunction

function Access(Actor ref_actor)
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Notify(ref_member.Access())
endFunction

function Settle(Actor ref_actor)
    if !p_MEMBERS.Has_Member(ref_actor)
        Member(ref_actor)
    endIf
    if !p_MEMBERS.Has_Member(ref_actor)
        return
    endIf
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Notify(ref_member.Settle())
    Debug.Notification("Settled member.")
endFunction

function Unsettle(Actor ref_actor)
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Notify(ref_member.Unsettle())
    Debug.Notification("Unsettled member.")
endFunction

function Resettle(Actor ref_actor)
    doticu_npc_party_script_settler ref_settler = Get_Settler(ref_actor)
    if !ref_settler
        return
    endIf
    p_Notify(ref_settler.Resettle())
    Debug.Notification("Resettled member.")
endFunction

function Immobilize(Actor ref_actor)
    if !p_MEMBERS.Has_Member(ref_actor)
        Member(ref_actor)
    endIf
    if !p_MEMBERS.Has_Member(ref_actor)
        return
    endIf
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Notify(ref_member.Immobilize())
    Debug.Notification("Immobilized member.")
endFunction

function Mobilize(Actor ref_actor)
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Notify(ref_member.Mobilize())
    Debug.Notification("Mobilized member.")
endFunction

function Follow(Actor ref_actor)
    if !p_MEMBERS.Has_Member(ref_actor)
        Member(ref_actor)
    endIf
    if !p_MEMBERS.Has_Member(ref_actor)
        return
    endIf
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Notify_Follow(ref_member.Follow())
endFunction

function Unfollow(Actor ref_actor)
    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        return
    endIf
    p_Notify_Unfollow(ref_member.Unfollow())
endFunction

function Sneak(Actor ref_actor)
    if !p_FOLLOWERS.Has_Follower(ref_actor)
        Follow(ref_actor)
    endIf
    if !p_FOLLOWERS.Has_Follower(ref_actor)
        return
    endIf
    doticu_npc_party_script_follower ref_follower = Get_Follower(ref_actor)
    if !ref_follower
        return
    endIf
    p_Notify(ref_follower.Sneak())
    Debug.Notification("The follower will now sneak.")
endFunction

function Unsneak(Actor ref_actor)
    doticu_npc_party_script_follower ref_follower = Get_Follower(ref_actor)
    if !ref_follower
        return
    endIf
    p_Notify(ref_follower.Unsneak())
    Debug.Notification("The follower will no longer sneak.")
endFunction

function Toggle_Member(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if ref_member
        Unmember(ref_actor)
    else
        Member(ref_actor)
    endIf
endFunction

function Toggle_Settler(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Settler()
        Unsettle(ref_actor)
    else
        Settle(ref_actor)
    endIf
endFunction

function Toggle_Immobile(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Immobile()
        Mobilize(ref_actor)
    else
        Immobilize(ref_actor)
    endIf
endFunction

function Toggle_Follower(Actor ref_actor)
    doticu_npc_party_script_follower ref_follower = p_FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower
        Unfollow(ref_actor)
    else
        Follow(ref_actor)
    endIf
endFunction

function Toggle_Sneak(Actor ref_actor)
    doticu_npc_party_script_follower ref_follower = p_FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower && ref_follower.Is_Sneak()
        Unsneak(ref_actor)
    else
        Sneak(ref_actor)
    endIf
endFunction
