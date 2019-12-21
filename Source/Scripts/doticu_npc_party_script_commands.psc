Scriptname doticu_npc_party_script_commands extends Quest

; Private Constants
doticu_npc_party_script_consts      p_CONSTS    = none
doticu_npc_party_script_codes       p_CODES     = none
doticu_npc_party_script_vars        p_VARS      = none
doticu_npc_party_script_logs        p_LOGS      = none
doticu_npc_party_script_actor       p_ACTOR2    = none
doticu_npc_party_script_members     p_MEMBERS   = none
doticu_npc_party_script_followers   p_FOLLOWERS = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_LOGS = DATA.MODS.FUNCS.LOGS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
endFunction

; Private Methods
function p_Notify_On_Member(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " is now a member.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become a member.")
    elseIf code_return == p_CODES.HAS_MEMBER
        p_LOGS.Create_Note(str_name + " is already a member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a member.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be a member.")
    endIf
endFunction

function p_Notify_On_Unmember(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " is no longer a member.")
    elseIf code_return == p_CODES.HASNT_MEMBER
        p_LOGS.Create_Note(str_name + " was already not a member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't be unmembered.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be unmembered.")
    endIf
endFunction

function p_Notify_On_Clone(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note("A clone of " + str_name + " is now a member.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for a clone of " + str_name + " to be a member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, can't be cloned, and can't become a member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("A clone of this can't be made a member.")
    else
        p_LOGS.Create_Error("It's unknown why a clone of" + str_name + " can't be a member.")
    endIf
endFunction

function p_Notify_On_Unclone(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " is no longer a member and was uncloned.")
    elseIf code_return == p_CODES.HASNT_MEMBER
        p_LOGS.Create_Note(str_name + " was already not a member and can't be uncloned.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't be unmembered or uncloned.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be unmembered and uncloned.")
    endIf
endFunction

function p_Notify_On_Access(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " has been accessed.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to be accessed as a new member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be accessed as a new member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a member and be accessed.")
    elseIf code_return == p_CODES.ISNT_MEMBER || code_return == p_CODES.HASNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be accessed.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be accessed.")
    endIf
endFunction

function p_Notify_On_Outfit(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " has been outfitted.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to be outfitted as a new member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be outfitted as a new member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a member and be outfitted.")
    elseIf code_return == p_CODES.ISNT_MEMBER || code_return == p_CODES.HASNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be outfitted.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be outfitted.")
    endIf
endFunction

function p_Notify_On_Resurrect(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " has been resurrected.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to be a resurrected new member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be resurrected, and so can't be a new member.")
    elseIf code_return == p_CODES.IS_ALIVE
        p_LOGS.Create_Note(str_name + " is already alive.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a resurrected new member.")
    elseIf code_return == p_CODES.ISNT_MEMBER || code_return == p_CODES.HASNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be resurrected.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be resurrected.")
    endIf
endFunction

function p_Notify_On_Settle(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will settle here.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a settled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be a settled member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a settled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't settle here.")
    elseIf code_return == p_CODES.IS_SETTLER
        p_LOGS.Create_Note(str_name + " is already settled elsewhere.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't settle here.")
    endIf
endFunction

function p_Notify_On_Unsettle(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will no longer be a settler.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become an unsettled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be an unsettled member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become an unsettled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't unsettle.")
    elseIf code_return == p_CODES.ISNT_SETTLER
        p_LOGS.Create_Note(str_name + " isn't settled.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't unsettle.")
    endIf
endFunction

function p_Notify_On_Resettle(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will resettle here.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a resettled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become a resettled member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a resettled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't resettle.")
    elseIf code_return == p_CODES.ISNT_SETTLER
        p_LOGS.Create_Note(str_name + " isn't a settler, and so can't resettle.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't resettle.")
    endIf
endFunction

function p_Notify_On_Immobilize(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will stop moving.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become an immobile member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be immobilized.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become an immobile member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be immobilized.")
    elseIf code_return == p_CODES.IS_IMMOBILE
        p_LOGS.Create_Note(str_name + " is already immobile.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be immobilized.")
    endIf
endFunction

function p_Notify_On_Mobilize(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will start moving.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a mobile member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be mobilized.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a mobile member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be mobilized.")
    elseIf code_return == p_CODES.ISNT_IMMOBILE
        p_LOGS.Create_Note(str_name + " is already mobile.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be mobilized.")
    endIf
endFunction

function p_Notify_On_Enthrall(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " is now enthralled.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become an enthralled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be enthralled.")
    elseIf code_return == p_CODES.ISNT_VAMPIRE
        p_LOGS.Create_Note("Only a vampire can enthrall a member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become an enthralled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be enthralled.")
    elseIf code_return == p_CODES.IS_IMMOBILE
        p_LOGS.Create_Note(str_name + " is already enthralled.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be enthralled.")
    endIf
endFunction

function p_Notify_On_Unthrall(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " is no longer enthralled.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become an unthralled member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't be unthralled.")
    elseIf code_return == p_CODES.ISNT_VAMPIRE
        p_LOGS.Create_Note("Only a vampire can unthrall a member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become an unthralled member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be unthralled.")
    elseIf code_return == p_CODES.ISNT_IMMOBILE
        p_LOGS.Create_Note(str_name + " is already unthralled.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be unthralled.")
    endIf
endFunction

function p_Notify_On_Style(int code_return, string str_name, string str_style)
    if str_style == "default"
        str_style = "a default member"
    elseIf str_style == "archer"
        str_style = "an " + str_style
    else
        str_style = "a " + str_style
    endIf

    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " now fights as " + str_style + ".")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become " + str_style + ".")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become " + str_style + ".")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become " + str_style + ".")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be " + str_style + ".")
    elseIf code_return == p_CODES.IS_DEFAULT
        p_LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == p_CODES.IS_WARRIOR
        p_LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == p_CODES.IS_MAGE
        p_LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == p_CODES.IS_ARCHER
        p_LOGS.Create_Note(str_name + " is already " + str_style + ".")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be " + str_style + ".")
    endIf
endFunction

function p_Notify_On_Vitalize(int code_return, string str_name, string str_vitality)
    if str_vitality == "essential" || str_vitality == "invulnerable"
        str_vitality = "an " + str_vitality + " member"
    else
        str_vitality = "a " + str_vitality + " member"
    endIf

    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " is now " + str_vitality + ".")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become " + str_vitality + ".")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become " + str_vitality + ".")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become " + str_vitality + ".")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't be " + str_vitality + ".")
    elseIf code_return == p_CODES.IS_DEFAULT
        p_LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == p_CODES.IS_WARRIOR
        p_LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == p_CODES.IS_MAGE
        p_LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == p_CODES.IS_ARCHER
        p_LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't be " + str_vitality + ".")
    endIf
endFunction

function p_Notify_On_Follow(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will start following.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a member or a follower.")
    elseIf code_return == p_CODES.HASNT_SPACE_FOLLOWER
        p_LOGS.Create_Note("No room for " + str_name + " to become a follower.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become a follower.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a member or a follower.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't start following.")
    elseIf code_return == p_CODES.IS_FOLLOWER
        p_LOGS.Create_Note(str_name + " is already following.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't start following.")
    endIf
endFunction

function p_Notify_On_Unfollow(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will stop following.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a non-following member.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become a non-following member.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a member or a non-following member.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't stop following.")
    elseIf code_return == p_CODES.ISNT_FOLLOWER
        p_LOGS.Create_Note(str_name + " wasn't following.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't stop following.")
    endIf
endFunction

function p_Notify_On_Sneak(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will start sneaking.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a member or a sneaking follower.")
    elseIf code_return == p_CODES.HASNT_SPACE_FOLLOWER
        p_LOGS.Create_Note("No room for " + str_name + " to become a sneaking follower.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become a sneaking follower.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a member or a sneaking follower.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't start sneaking.")
    elseIf code_return == p_CODES.ISNT_FOLLOWER
        p_LOGS.Create_Note(str_name + " isn't a follower, and so can't start sneaking.")
    elseIf code_return == p_CODES.IS_SNEAK
        p_LOGS.Create_Note(str_name + " is already sneaking.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't start sneaking.")
    endIf
endFunction

function p_Notify_On_Unsneak(int code_return, string str_name)
    if code_return == p_CODES.SUCCESS
        p_LOGS.Create_Note(str_name + " will stop sneaking.")
    elseIf code_return == p_CODES.HASNT_SPACE_MEMBER
        p_LOGS.Create_Note("No room for " + str_name + " to become a member or an unsneaking follower.")
    elseIf code_return == p_CODES.HASNT_SPACE_FOLLOWER
        p_LOGS.Create_Note("No room for " + str_name + " to become an unsneaking follower.")
    elseIf code_return == p_CODES.CANT_RESURRECT
        p_LOGS.Create_Note(str_name + " can't be revived, and so can't become an unsneaking follower.")
    elseIf code_return == p_CODES.ISNT_ACTOR
        p_LOGS.Create_Note("That can't become a member or an unsneaking follower.")
    elseIf code_return == p_CODES.ISNT_MEMBER
        p_LOGS.Create_Note(str_name + " isn't a member, and so can't stop sneaking.")
    elseIf code_return == p_CODES.ISNT_FOLLOWER
        p_LOGS.Create_Note(str_name + " isn't a follower, and so can't stop sneaking.")
    elseIf code_return == p_CODES.ISNT_SNEAK
        p_LOGS.Create_Note(str_name + " wasn't sneaking.")
    else
        p_LOGS.Create_Error("It's unknown why " + str_name + " can't stop sneaking.")
    endIf
endFunction

; Public Methods
function Member(Actor ref_actor)
    if p_MEMBERS.Should_Clone_Actor(ref_actor)
        Clone(ref_actor)
        return
    endIf

    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    p_Notify_On_Member(p_MEMBERS.Create_Member(ref_actor), str_name)
endFunction

function Unmember(Actor ref_actor)
    if p_MEMBERS.Should_Unclone_Member(p_MEMBERS.Get_Member(ref_actor))
        Unclone(ref_actor)
        return
    endIf

    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    p_Notify_On_Unmember(p_MEMBERS.Destroy_Member(ref_actor), str_name)
endFunction

function Clone(Actor ref_actor)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if p_ACTOR2.Is_Generic(ref_actor)
        p_LOGS.Create_Note("Please wait, cloning may take a while.", false)
    endIf

    p_Notify_On_Clone(p_MEMBERS.Create_Member(ref_actor, true), str_name)
endFunction

function Unclone(Actor ref_actor)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    p_Notify_On_Unclone(p_MEMBERS.Destroy_Member(ref_actor, true), str_name)
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

function Outfit(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    
    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Outfit(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Outfit(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Outfit(ref_member.Outfit(), str_name)
endFunction

function Resurrect(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    
    if do_create && !p_Members.Has_Member(ref_actor)
        p_Notify_On_Resurrect(p_MEMBERS.Create_Member(ref_actor), str_name)
        return
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Resurrect(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Resurrect(ref_member.Resurrect(), str_name)
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

function Enthrall(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Enthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Enthrall(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Enthrall(ref_member.Enthrall(), str_name)
endFunction

function Unthrall(Actor ref_actor, bool do_create)
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unthrall(p_CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Unthrall(ref_member.Unthrall(), str_name)
endFunction

function Style(Actor ref_actor, string str_style, bool do_create); may want int code_style instead
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    if str_style != "warrior" && str_style != "mage" && str_style != "archer"
        str_style = "default"
    endIf

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Style(code_return, str_name, str_style)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Style(p_CODES.HASNT_MEMBER, str_name, str_style)
        return
    endIf

    if str_style == "warrior"
        p_Notify_On_Style(ref_member.Style_Warrior(), str_name, str_style)
    elseIf str_style == "mage"
        p_Notify_On_Style(ref_member.Style_Mage(), str_name, str_style)
    elseIf str_style == "archer"
        p_Notify_On_Style(ref_member.Style_Archer(), str_name, str_style)
    else
        p_Notify_On_Style(ref_member.Style_Default(), str_name, str_style)
    endIf
endFunction

function Vitalize(Actor ref_actor, string str_vitality, bool do_create); may want int code_vitality instead
    int code_return
    string str_name = p_ACTOR2.Get_Name(ref_actor)
    if str_vitality != "protected" && str_vitality != "essential" && str_vitality != "invulnerable"
        str_vitality = "mortal"
    endIf

    if do_create && !p_Members.Has_Member(ref_actor)
        code_return = p_MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Vitalize(code_return, str_name, str_vitality)
            return
        endIf
    endIf

    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Vitalize(p_CODES.HASNT_MEMBER, str_name, str_vitality)
        return
    endIf

    if str_vitality == "mortal"
        p_Notify_On_Vitalize(ref_member.Vitalize_Mortal(), str_name, str_vitality)
    elseIf str_vitality == "protected"
        p_Notify_On_Vitalize(ref_member.Vitalize_Protected(), str_name, str_vitality)
    elseIf str_vitality == "essential"
        p_Notify_On_Vitalize(ref_member.Vitalize_Essential(), str_name, str_vitality)
    elseIf str_vitality == "invulnerable"
        p_Notify_On_Vitalize(ref_member.Vitalize_Invulnerable(), str_name, str_vitality)
    endIf
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

function Unsneak(Actor ref_actor, bool do_create)
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

function Toggle_Thrall(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Thrall()
        Unthrall(ref_actor, true)
    else
        Enthrall(ref_actor, true)
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

function Cycle_Style(Actor ref_actor)
    doticu_npc_party_script_member ref_member = p_MEMBERS.Get_Member(ref_actor)
    if !ref_member
        Style(ref_actor, "default", true)
    elseIf ref_member.Is_Styled_Default()
        Style(ref_actor, "warrior", false)
    elseIf ref_member.Is_Styled_Warrior()
        Style(ref_actor, "mage", false)
    elseIf ref_member.Is_Styled_Mage()
        Style(ref_actor, "archer", false)
    elseIf ref_member.Is_Styled_Archer()
        Style(ref_actor, "default", false)
    endIf
endFunction
