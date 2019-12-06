Scriptname doticu_npc_party_script_control extends Quest

; Private Constants
doticu_npc_party_script_codes       p_CODES     = none
doticu_npc_party_script_actor       p_ACTOR2    = none
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

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CODES = DATA.CODES
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_DIALOGUE = (self as Quest) as doticu_npc_party_script_dialogue
    p_KEYS = (self as Quest) as doticu_npc_party_script_keys
    p_MCM = (self as Quest) as doticu_npc_party_script_mcm

    p_DIALOGUE.f_Initialize(DATA)
    p_KEYS.f_Initialize(DATA)
endFunction

; Private Methods
int function p_Notify_On_Member(int int_code, string str_name = "NPC")
    if int_code > -1
        Debug.Notification("Added " + str_name + " as a member of your party.")
        return p_CODES.SUCCESS
    endIf

    if int_code == p_CODES.NO_ACTOR
        Debug.Notification("Invalid target. Cannot add " + str_name + " as a member of your party.")
    elseIf int_code == p_CODES.IS_DUPLICATE
        Debug.Notification(str_name + " is already a member of your party.")
    elseIf int_code == p_CODES.OUT_OF_SPACE
        Debug.Notification("Members are maxed out. Cannot add " + str_name + " as a member of your party.")
    elseIf int_code == p_CODES.NO_RESURRECT
        Debug.Notification("Failed to resurrect. Cannot add " + str_name + " as a member of your party.")
    else
        Debug.Notification("Unknown error. Cannot add " + str_name + " as a member of your party.")
    endIf

    return p_CODES.FAILURE
endFunction

int function p_Notify_On_Unmember(int int_code, string str_name = "NPC")
    if int_code > -1
        Debug.Notification("Removed " + str_name + " from being a member of your party.")
        return p_CODES.SUCCESS
    endIf

    if int_code == p_CODES.NO_ACTOR
        Debug.Notification("Invalid target. Cannot remove " + str_name + " from being a member of your party.")
    elseIf int_code == p_CODES.NO_MEMBER
        Debug.Notification("Not a member. Cannot remove " + str_name + " from being a member of your party.")
    else
        Debug.Notification("Unknown error. Cannot remove " + str_name + " from being a member of your party.")
    endIf

    return p_CODES.FAILURE
endFunction

int function p_Notify_On_Follow(int int_code, string str_name = "NPC")
    if int_code > -1
        Debug.Notification("Added " + str_name + " as a follower in your party.")
        return p_CODES.SUCCESS
    endIf

    if int_code == p_CODES.NO_ACTOR
        Debug.Notification("Invalid target. Cannot add " + str_name + " as a follower in your party.")
    elseIf int_code == p_CODES.IS_DUPLICATE
        Debug.Notification(str_name + " is already a follower in your party.")
    elseIf int_code == p_CODES.OUT_OF_SPACE
        Debug.Notification("Followers are maxed out. Cannot add " + str_name + " as a follower in your party.")
    else
        Debug.Notification("Unknown error. Cannot add " + str_name + " as a follower in your party.")
    endIf

    return p_CODES.FAILURE
endFunction

int function p_Notify_On_Unfollow(int int_code, string str_name = "NPC")
    if int_code > -1
        Debug.Notification("Removed " + str_name + " from being a follower in your party.")
        return p_CODES.SUCCESS
    endIf

    if int_code == p_CODES.NO_ACTOR
        Debug.Notification("Invalid target. Cannot remove " + str_name + " from being a follower in your party.")
    elseIf int_code == p_CODES.NO_FOLLOWER
        Debug.Notification("Not a follower. Cannot remove " + str_name + " from being a follower in your party.")
    else
        Debug.Notification("Unknown error. Cannot remove " + str_name + " from being a follower in your party.")
    endIf

    return p_CODES.FAILURE
endFunction

int function p_Notify_On(int int_code, string str_success = "Success.")
    if int_code > -1
        Debug.Notification(str_success)
        return p_CODES.SUCCESS
    endIf

    if int_code == p_CODES.IS_DUPLICATE
        Debug.Notification("ERROR: Is a duplicate")
    elseIf int_code == p_CODES.OUT_OF_SPACE
        Debug.Notification("ERROR: Out of space")
    elseIf int_code == p_CODES.NO_ACTOR
        Debug.Notification("ERROR: Not an actor")
    elseIf int_code == p_CODES.NO_MEMBER
        Debug.Notification("ERROR: Not a member")
    elseIf int_code == p_CODES.NO_SETTLER
        Debug.Notification("ERROR: Not a settler")
    elseIf int_code == p_CODES.NO_IMMOBILE
        Debug.Notification("ERROR: Not an immobile")
    elseIf int_code == p_CODES.NO_FOLLOWER
        Debug.Notification("ERROR: Not a follower")
    elseIf int_code == p_CODES.EXISTS
        Debug.Notification("ERROR: Already exists")
    else
        Debug.Notification("ERROR: Unknown")
    endIf

    return p_CODES.FAILURE
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

int function Member(Actor ref_actor)
    return p_Notify_On_Member(p_MEMBERS.Create_Member(ref_actor), p_ACTOR2.Get_Name(ref_actor))
endFunction

int function Unmember(Actor ref_actor)
    return p_Notify_On_Unmember(p_MEMBERS.Destroy_Member(ref_actor), p_ACTOR2.Get_Name(ref_actor))
endFunction

int function Access(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not access " + str_name + "."
    string str_success = "Accessed " + str_name + "."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if p_Notify_On(ref_member.Access(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Settle(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not settle " + str_name + "."
    string str_success = "Settled " + str_name + "."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if ref_member.Is_Settler()
        return Resettle(ref_actor, do_create)
    endIf

    if p_Notify_On(ref_member.Settle(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unsettle(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not unsettle " + str_name + "."
    string str_success = "Unsettled " + str_name + "."
    string str_nothing = str_name + " was already unsettled."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if !ref_member.Is_Settler()
        Debug.Notification(str_nothing)
        return p_CODES.SUCCESS
    endIf

    if p_Notify_On(ref_member.Unsettle(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Resettle(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not resettle " + str_name + "."
    string str_success = "Resettled " + str_name + "."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if do_create && !ref_member.Is_Settler() && Settle(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_settler ref_settler = Get_Settler(ref_actor)
    if !ref_settler
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if p_Notify_On(ref_settler.Resettle(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Immobilize(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not immobilize " + str_name + "."
    string str_success = "Immobilized " + str_name + "."
    string str_nothing = str_name + " was already immobilized."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if ref_member.Is_Immobile()
        Debug.Notification(str_nothing)
        return p_CODES.SUCCESS
    endIF

    if p_Notify_On(ref_member.Immobilize(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Mobilize(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not mobilize " + str_name + "."
    string str_success = "Mobilized " + str_name + "."
    string str_nothing = str_name + " was already mobilized."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if !ref_member.Is_Immobile()
        Debug.Notification(str_nothing)
        return p_CODES.SUCCESS
    endIf

    if p_Notify_On(ref_member.Mobilize(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Follow(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not make " + str_name + " a follower."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_Notify_On_Follow(ref_member.Follow(), str_name)
endFunction

int function Unfollow(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not remove " + str_name + " from being a follower."

    if do_create && !p_Members.Has_Member(ref_actor) && Member(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_member ref_member = Get_Member(ref_actor)
    if !ref_member
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_Notify_On_Unfollow(ref_member.Unfollow(), str_name)
endFunction

int function Sneak(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not make " + str_name + " a sneak follower."
    string str_success = "Made " + str_name + " a sneak follower."
    string str_nothing = str_name + " was already a sneak follower."

    if do_create && !p_Followers.Has_Follower(ref_actor) && Follow(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_follower ref_follower = Get_Follower(ref_actor)
    if !ref_follower
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if ref_follower.Is_Sneak()
        Debug.Notification(str_nothing)
        return p_CODES.SUCCESS
    endIF

    if p_Notify_On(ref_follower.Sneak(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unsneak(Actor ref_actor, bool do_create = true)
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    string str_failure = "Could not stop " + str_name + " from being a sneak follower."
    string str_success = "Stopped " + str_name + " from being a sneak follower."
    string str_nothing = str_name + " was already not a sneak follower."

    if do_create && !p_Followers.Has_Follower(ref_actor) && Follow(ref_actor) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    doticu_npc_party_script_follower ref_follower = Get_Follower(ref_actor)
    if !ref_follower
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    if !ref_follower.Is_Sneak()
        Debug.Notification(str_nothing)
        return p_CODES.SUCCESS
    endIf

    if p_Notify_On(ref_follower.Unsneak(), str_success) == p_CODES.FAILURE
        Debug.Notification(str_failure)
        return p_CODES.FAILURE
    endIf

    return p_CODES.SUCCESS
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
    if ref_follower && ref_follower.Is_Sneak()
        Unsneak(ref_actor)
    elseIf ref_follower
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
