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
function p_Notify_On_Member(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " is now a member.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't become a member.")
    elseIf code_return == p_CODES.HAS_MEMBER
        Debug.Notification("NPC Party: " + str_name + " is already a member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a member.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't be a member.")
    endIf
endFunction

int function p_Notify_On_Unmember(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " is no longer a member.")
    elseIf code_return == p_CODES.HASNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " was already not a member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't be unmembered.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't be unmembered.")
    endIf
endFunction

function p_Notify_On_Access(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " has been accessed.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to be accessed as a new member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't be accessed as a new member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a member and be accessed.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't be accessed.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't be accessed.")
    endIf
endFunction

function p_Notify_On_Settle(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will settle here.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a settled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't be a settled member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a settled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't settle here.")
    elseIf code_return == p_CODES.IS_SETTLER
        Debug.Notification("NPC Party: " + str_name + " is already settled elsewhere.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't settle here.")
    endIf
endFunction

function p_Notify_On_Unsettle(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will no longer be a settler.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become an unsettled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't be an unsettled member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become an unsettled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't unsettle.")
    elseIf code_return == p_CODES.ISNT_SETTLER
        Debug.Notification("NPC Party: " + str_name + " isn't settled.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't unsettle.")
    endIf
endFunction

function p_Notify_On_Resettle(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will settle here.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a resettled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't become a settled member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a settled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't resettle.")
    elseIf code_return == p_CODES.ISNT_SETTLER
        Debug.Notification("NPC Party: " + str_name + " isn't a settler, and so can't resettle.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't resettle.")
    endIf
endFunction

function p_Notify_On_Immobilize(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will stop moving.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become an immobile member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't be immobilized.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become an immobile member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't be immobilized.")
    elseIf code_return == p_CODES.IS_IMMOBILE
        Debug.Notification("NPC Party: " + str_name + " is already immobile.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't be immobilized.")
    endIf
endFunction

function p_Notify_On_Mobilize(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will start moving.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a mobile member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't be mobilized.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a mobile member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't be mobilized.")
    elseIf code_return == p_CODES.ISNT_IMMOBILE
        Debug.Notification("NPC Party: " + str_name + " is already mobile.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't be mobilized.")
    endIf
endFunction

function p_Notify_On_Follow(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will start following.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a member or a follower.")
    elseIf code_return == p_CODES.HASNT_SPACE_FOLLOWER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a follower.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't become a follower.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a member or a follower.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't start following.")
    elseIf code_return == p_CODES.IS_FOLLOWER
        Debug.Notification("NPC Party: " + str_name + " is already following.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't start following.")
    endIf
endFunction

function p_Notify_On_Unfollow(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will stop following.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a non-following member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't become a non-following member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a member or a non-following member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't stop following.")
    elseIf code_return == p_CODES.ISNT_FOLLOWER
        Debug.Notification("NPC Party: " + str_name + " wasn't following.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't stop following.")
    endIf
endFunction

function p_Notify_On_Sneak(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will start sneaking.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a member or a sneaking follower.")
    elseIf code_return == p_CODES.HASNT_SPACE_FOLLOWER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a sneaking follower.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't become a sneaking follower.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a member or a sneaking follower.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't start sneaking.")
    elseIf code_return == p_CODES.ISNT_FOLLOWER
        Debug.Notification("NPC Party: " + str_name + " isn't a follower, and so can't start sneaking.")
    elseIf code_return == p_CODES.IS_SNEAK
        Debug.Notification("NPC Party: " + str_name + " is already sneaking.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't start sneaking.")
    endIf
endFunction

function p_Notify_On_Unsneak(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        Debug.Notification("NPC Party: " + str_name + " will stop sneaking.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        Debug.Notification("NPC Party: No room for " + str_name + " to become a member or an unsneaking follower.")
    elseIf code_return == p_CODES.HASNT_SPACE_FOLLOWER
        Debug.Notification("NPC Party: No room for " + str_name + " to become an unsneaking follower.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        Debug.Notification("NPC Party: " + str_name + " can't be revived, and so can't become an unsneaking follower.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        Debug.Notification("NPC Party: That can't become a member or an unsneaking follower.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        Debug.Notification("NPC Party: " + str_name + " isn't a member, and so can't stop sneaking.")
    elseIf code_return == p_CODES.ISNT_FOLLOWER
        Debug.Notification("NPC Party: " + str_name + " isn't a follower, and so can't stop sneaking.")
    elseIf code_return == p_CODES.ISNT_SNEAK
        Debug.Notification("NPC Party: " + str_name + " wasn't sneaking.")
    else
        Debug.Notification("NPC Party: It's unknown why " + str_name + " can't stop sneaking.")
    endIf
endFunction

; Public Methods
function Member(Actor ref_actor)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    p_Notify_On_Member(p_MEMBERS.Create_Member(ref_actor), str_name)
endFunction

int function Unmember(Actor ref_actor)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    p_Notify_On_Unmember(p_MEMBERS.Destroy_Member(ref_actor), p_ACTOR2.Get_Name(ref_actor))
endFunction

function Access(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    
    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Access(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Access(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Access(ref_member.Access(), str_name)
endFunction

function Settle(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Settle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Settle(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Settle(ref_member.Settle(), str_name)
endFunction

function Unsettle(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unsettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unsettle(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Unsettle(ref_member.Unsettle(), str_name)
endFunction

function Resettle(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Resettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Resettle(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if do_create && !ref_member.Is_Settler()
        code_return = ref_member.Settle()
        if code_return < 0
            p_Notify_On_Resettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_settler ref_settler = ref_member.Get_Settler()
    if !ref_settler
        p_Notify_On_Resettle(p_CODES.HASNT_SETTLER, str_name)
        return
    endIf

    p_Notify_On_Resettle(ref_settler.Resettle(), str_name)
endFunction

function Immobilize(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Immobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Immobilize(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Immobilize(ref_member.Immobilize(), str_name)
endFunction

function Mobilize(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Mobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Mobilize(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Mobilize(ref_member.Mobilize(), str_name)
endFunction

function Follow(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Follow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Follow(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Follow(ref_member.Follow(), str_name)
endFunction

function Unfollow(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unfollow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unfollow(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Unfollow(ref_member.Unfollow(), str_name)
endFunction

function Sneak(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Sneak(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if do_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return < 0
            p_Notify_On_Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_follower ref_follower = p_FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        p_Notify_On_Sneak(p_CODES.HASNT_FOLLOWER, str_name)
        return
    endIf

    p_Notify_On_Sneak(ref_follower.Sneak(), str_name)
endFunction

function Unsneak(Actor ref_actor, bool do_create); not sure if I want the "un" funcs to create anything...
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unsneak(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if do_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return < 0
            p_Notify_On_Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_follower ref_follower = p_FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        p_Notify_On_Unsneak(p_CODES.HASNT_FOLLOWER, str_name)
        return
    endIf

    p_Notify_On_Unsneak(ref_follower.Unsneak(), str_name)
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
        Unsettle(ref_actor, true)
    else
        Settle(ref_actor, true)
    endIf
endFunction

function Toggle_Immobile(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Immobile()
        Mobilize(ref_actor, true)
    else
        Immobilize(ref_actor, true)
    endIf
endFunction

function Toggle_Follower(Actor ref_actor)
    doticu_npc_party_script_follower ref_follower = p_FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower
        Unfollow(ref_actor, true)
    else
        Follow(ref_actor, true)
    endIf
endFunction

function Toggle_Sneak(Actor ref_actor)
    doticu_npc_party_script_follower ref_follower = p_FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower && ref_follower.Is_Sneak()
        Unsneak(ref_actor, true)
    else
        Sneak(ref_actor, true)
    endIf
endFunction
