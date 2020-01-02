Scriptname doticu_npcp_commands extends Quest

; Modules
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
function p_Notify_On_Member(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " is now a member.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a member.")
    elseIf code_return == CODES.HAS_MEMBER
        LOGS.Create_Note(str_name + " is already a member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a member.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be a member.")
    endIf
endFunction

function p_Notify_On_Unmember(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " is no longer a member.")
    elseIf code_return == CODES.HASNT_MEMBER
        LOGS.Create_Note(str_name + " was already not a member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't be unmembered.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be unmembered.")
    endIf
endFunction

function p_Notify_On_Clone(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("A clone of " + str_name + " is now a member.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for a clone of " + str_name + " to be a member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, can't be cloned, and can't become a member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("A clone of this can't be made a member.")
    else
        LOGS.Create_Error("It's unknown why a clone of" + str_name + " can't be a member.")
    endIf
endFunction

function p_Notify_On_Unclone(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " is no longer a member and was uncloned.")
    elseIf code_return == CODES.HASNT_MEMBER
        LOGS.Create_Note(str_name + " was already not a member and can't be uncloned.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't be unmembered or uncloned.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be unmembered and uncloned.")
    endIf
endFunction

function p_Notify_On_Pack(int code_return, Actor ref_actor, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will carry the pack.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to carry a pack as a new member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't carry a pack as a new member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a member and carry a pack.")
    elseIf code_return == CODES.ISNT_MEMBER || code_return == CODES.HASNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't carry a pack.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't carry the pack.")
    endIf
endFunction

function p_Notify_On_Outfit(int code_return, string str_name, int code_outfit)
    string str_outfit

    if code_outfit == CODES.IS_MEMBER
        str_outfit = "a member"
    elseIf code_outfit == CODES.IS_SETTLER
        str_outfit = "a settler"
    elseIf code_outfit == CODES.IS_THRALL
        str_outfit = "a thrall"
    elseIf code_outfit == CODES.IS_FOLLOWER
        str_outfit = "a follower"
    elseIf code_outfit == CODES.IS_IMMOBILE
        str_outfit = "an immobile"
    endIf

    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " has been outfitted as " + str_outfit + ".")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to be outfitted as " + str_outfit + ".")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't be outfitted as " + str_outfit + ".")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become " + str_outfit + " and be outfitted.")
    elseIf code_return == CODES.ISNT_MEMBER || code_return == CODES.HASNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be outfitted.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be outfitted as " + str_outfit + ".")
    endIf
endFunction

function p_Notify_On_Resurrect(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " has been resurrected.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to be a resurrected new member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be resurrected, and so can't be a new member.")
    elseIf code_return == CODES.IS_ALIVE
        LOGS.Create_Note(str_name + " is already alive.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a resurrected new member.")
    elseIf code_return == CODES.ISNT_MEMBER || code_return == CODES.HASNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be resurrected.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be resurrected.")
    endIf
endFunction

function p_Notify_On_Settle(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will settle here.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a settled member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't be a settled member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a settled member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't settle here.")
    elseIf code_return == CODES.IS_SETTLER
        LOGS.Create_Note(str_name + " is already settled elsewhere.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't settle here.")
    endIf
endFunction

function p_Notify_On_Unsettle(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will no longer be a settler.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become an unsettled member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't be an unsettled member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become an unsettled member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't unsettle.")
    elseIf code_return == CODES.ISNT_SETTLER
        LOGS.Create_Note(str_name + " isn't settled.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't unsettle.")
    endIf
endFunction

function p_Notify_On_Resettle(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will resettle here.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a resettled member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a resettled member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a resettled member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't resettle.")
    elseIf code_return == CODES.ISNT_SETTLER
        LOGS.Create_Note(str_name + " isn't a settler, and so can't resettle.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't resettle.")
    endIf
endFunction

function p_Notify_On_Enthrall(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " is now enthralled.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become an enthralled member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't be enthralled.")
    elseIf code_return == CODES.ISNT_VAMPIRE
        LOGS.Create_Note("Only a vampire can enthrall a member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become an enthralled member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be enthralled.")
    elseIf code_return == CODES.IS_IMMOBILE
        LOGS.Create_Note(str_name + " is already enthralled.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be enthralled.")
    endIf
endFunction

function p_Notify_On_Unthrall(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " is no longer enthralled.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become an unthralled member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't be unthralled.")
    elseIf code_return == CODES.ISNT_VAMPIRE
        LOGS.Create_Note("Only a vampire can unthrall a member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become an unthralled member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be unthralled.")
    elseIf code_return == CODES.ISNT_IMMOBILE
        LOGS.Create_Note(str_name + " is already unthralled.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be unthralled.")
    endIf
endFunction

function p_Notify_On_Immobilize(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will stop moving.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become an immobile member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't be immobilized.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become an immobile member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be immobilized.")
    elseIf code_return == CODES.IS_IMMOBILE
        LOGS.Create_Note(str_name + " is already immobile.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be immobilized.")
    endIf
endFunction

function p_Notify_On_Mobilize(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will start moving.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a mobile member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't be mobilized.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a mobile member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be mobilized.")
    elseIf code_return == CODES.ISNT_IMMOBILE
        LOGS.Create_Note(str_name + " is already mobile.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be mobilized.")
    endIf
endFunction

function p_Notify_On_Paralyze(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will be paralyzed.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become an immobile and paralyzed member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become an immobile and paralyzed member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become an immobile and paralyzed member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be immobile and paralyzed.")
    elseIf code_return == CODES.IS_PARALYZED
        LOGS.Create_Note(str_name + " is already paralyzed.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be immobile and paralyzed.")
    endIf
endFunction

function p_Notify_On_Unparalyze(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will no longer be paralyzed.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become an immobile and unparalyzed member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become an immobile and unparalyzed member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become an immobile and unparalyzed member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be immobile and unparalyzed.")
    elseIf code_return == CODES.ISNT_PARALYZED
        LOGS.Create_Note(str_name + " wasn't paralyzed.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't stop being paralyzed.")
    endIf
endFunction

function p_Notify_On_Style(int code_return, string str_name, int code_style)
    string str_style

    if code_style == CODES.IS_DEFAULT
        str_style = "a default member"
    elseIf code_style == CODES.IS_WARRIOR
        str_style = "a warrior"
    elseIf code_style == CODES.IS_MAGE
        str_style = "a mage"
    elseIf code_style == CODES.IS_ARCHER
        str_style = "an archer"
    endIf

    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " now fights as " + str_style + ".")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become " + str_style + ".")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become " + str_style + ".")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become " + str_style + ".")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be " + str_style + ".")
    elseIf code_return == CODES.IS_DEFAULT
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == CODES.IS_WARRIOR
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == CODES.IS_MAGE
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == CODES.IS_ARCHER
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be " + str_style + ".")
    endIf
endFunction

function p_Notify_On_Vitalize(int code_return, string str_name, int code_vitality)
    string str_vitality

    if code_vitality == CODES.IS_MORTAL
        str_vitality = "a mortal member"
    elseIf code_vitality == CODES.IS_PROTECTED
        str_vitality = "a protected member"
    elseIf code_vitality == CODES.IS_ESSENTIAL
        str_vitality = "an essential member"
    elseIf code_vitality == CODES.IS_INVULNERABLE
        str_vitality = "an invulnerable member"
    endIf

    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " is now " + str_vitality + ".")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become " + str_vitality + ".")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become " + str_vitality + ".")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become " + str_vitality + ".")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't be " + str_vitality + ".")
    elseIf code_return == CODES.IS_DEFAULT
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == CODES.IS_WARRIOR
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == CODES.IS_MAGE
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == CODES.IS_ARCHER
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be " + str_vitality + ".")
    endIf
endFunction

function p_Notify_On_Follow(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will start following.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a member or a follower.")
    elseIf code_return == CODES.HASNT_SPACE_FOLLOWER
        LOGS.Create_Note("No room for " + str_name + " to become a follower.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a follower.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a member or a follower.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't start following.")
    elseIf code_return == CODES.IS_FOLLOWER
        LOGS.Create_Note(str_name + " is already following.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't start following.")
    endIf
endFunction

function p_Notify_On_Unfollow(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will stop following.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a non-following member.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a non-following member.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a member or a non-following member.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't stop following.")
    elseIf code_return == CODES.ISNT_FOLLOWER
        LOGS.Create_Note(str_name + " wasn't following.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't stop following.")
    endIf
endFunction

function p_Notify_On_Sneak(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will start sneaking.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a member or a sneaking follower.")
    elseIf code_return == CODES.HASNT_SPACE_FOLLOWER
        LOGS.Create_Note("No room for " + str_name + " to become a sneaking follower.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a sneaking follower.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a member or a sneaking follower.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't start sneaking.")
    elseIf code_return == CODES.ISNT_FOLLOWER
        LOGS.Create_Note(str_name + " isn't a follower, and so can't start sneaking.")
    elseIf code_return == CODES.IS_SNEAK
        LOGS.Create_Note(str_name + " is already sneaking.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't start sneaking. " + code_return)
    endIf
endFunction

function p_Notify_On_Unsneak(int code_return, string str_name)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note(str_name + " will stop sneaking.")
    elseIf code_return == CODES.HASNT_SPACE_MEMBER
        LOGS.Create_Note("No room for " + str_name + " to become a member or an unsneaking follower.")
    elseIf code_return == CODES.HASNT_SPACE_FOLLOWER
        LOGS.Create_Note("No room for " + str_name + " to become an unsneaking follower.")
    elseIf code_return == CODES.CANT_RESURRECT
        LOGS.Create_Note(str_name + " can't be revived, and so can't become an unsneaking follower.")
    elseIf code_return == CODES.ISNT_ACTOR
        LOGS.Create_Note("That can't become a member or an unsneaking follower.")
    elseIf code_return == CODES.ISNT_MEMBER
        LOGS.Create_Note(str_name + " isn't a member, and so can't stop sneaking.")
    elseIf code_return == CODES.ISNT_FOLLOWER
        LOGS.Create_Note(str_name + " isn't a follower, and so can't stop sneaking.")
    elseIf code_return == CODES.ISNT_SNEAK
        LOGS.Create_Note(str_name + " wasn't sneaking.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't stop sneaking. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Summon_All(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("Summoned all followers.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to summon.")
    else
        LOGS.Create_Error("Could not summon all followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Summon_Mobile(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("Summoned all mobile followers.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to summon.")
    elseIf code_return == CODES.HASNT_MOBILE
        LOGS.Create_Note("No mobile followers to summon.")
    else
        LOGS.Create_Error("Could not summon mobile followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Summon_Immobile(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("Summoned all immobile followers.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to summon.")
    elseIf code_return == CODES.HASNT_IMMOBILE
        LOGS.Create_Note("No immobile followers to summon.")
    else
        LOGS.Create_Error("Could not summon immobile followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Summon_Mobile_Behind(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("Summoned all mobile followers behind you.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to summon.")
    elseIf code_return == CODES.HASNT_MOBILE
        LOGS.Create_Note("No mobile followers to summon.")
    else
        LOGS.Create_Error("Could not summon mobile followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Settle(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers settle where they stand.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to settle.")
    else
        LOGS.Create_Error("Could not settle followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Unsettle(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers have unsettled.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to unsettle.")
    elseIf code_return == CODES.HASNT_SETTLER
        LOGS.Create_Note("No followers are already unsettled.")
    else
        LOGS.Create_Error("Could not unsettle followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Immobilize(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers have been immobilized.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to immobilize.")
    elseIf code_return == CODES.HASNT_MOBILE
        LOGS.Create_Note("All followers are already immobilized.")
    else
        LOGS.Create_Error("Could not immobilize followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Mobilize(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers have been mobilized.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to mobilize.")
    elseIf code_return == CODES.HASNT_IMMOBILE
        LOGS.Create_Note("All followers are already mobilized.")
    else
        LOGS.Create_Error("Could not mobilize followers. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Sneak(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers will sneak.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to sneak.")
    elseIf code_return == CODES.HASNT_UNSNEAK
        LOGS.Create_Note("All followers are already sneaking.")
    else
        LOGS.Create_Error("Could not make followers sneak. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Unsneak(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers will stop sneaking.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to stop sneaking.")
    elseIf code_return == CODES.HASNT_SNEAK
        LOGS.Create_Note("All followers are already not sneaking.")
    else
        LOGS.Create_Error("Could not make followers stop sneaking. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Resurrect(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All dead followers will resurrect.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to resurrect.")
    elseIf code_return == CODES.HASNT_DEAD
        LOGS.Create_Note("All followers are already alive.")
    else
        LOGS.Create_Error("Could not make followers resurrect. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Unfollow(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers will no longer follow.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to unfollow.")
    else
        LOGS.Create_Error("Could not make followers stop following. " + code_return)
    endIf
endFunction

function p_Notify_On_Followers_Unmember(int code_return)
    if code_return == CODES.SUCCESS
        LOGS.Create_Note("All followers are no longer members.")
    elseIf code_return == CODES.HASNT_FOLLOWER
        LOGS.Create_Note("No followers to unmember.")
    else
        LOGS.Create_Error("Could not unmember followers. " + code_return)
    endIf
endFunction

function p_Member(Actor ref_actor)
    if MEMBERS.Should_Clone_Actor(ref_actor)
        p_Clone(ref_actor)
        return
    endIf

    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    p_Notify_On_Member(MEMBERS.Create_Member(ref_actor), str_name)
endFunction

function p_Unmember(Actor ref_actor)
    if MEMBERS.Should_Unclone_Member(MEMBERS.Get_Member(ref_actor))
        p_Unclone(ref_actor)
        return
    endIf

    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    p_Notify_On_Unmember(MEMBERS.Destroy_Member(ref_actor), str_name)
endFunction

function p_Clone(Actor ref_actor)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if ACTORS.Is_Generic(ref_actor)
        LOGS.Create_Note("Please wait, cloning may take a while.", false)
    endIf

    p_Notify_On_Clone(MEMBERS.Create_Member(ref_actor, true), str_name)
endFunction

function p_Unclone(Actor ref_actor)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    p_Notify_On_Unclone(MEMBERS.Destroy_Member(ref_actor, true), str_name)
endFunction

function p_Pack(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Pack(code_return, ref_actor, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Pack(CODES.HASNT_MEMBER, ref_actor, str_name)
        return
    endIf

    p_Notify_On_Pack(ref_member.Pack(), ref_actor, str_name)
endFunction

function p_Outfit(Actor ref_actor, int code_outfit, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if code_outfit != CODES.IS_MEMBER &&\
        code_outfit != CODES.IS_SETTLER &&\
        code_outfit != CODES.IS_THRALL &&\
        code_outfit != CODES.IS_FOLLOWER &&\
        code_outfit != CODES.IS_IMMOBILE
        code_outfit = CODES.IS_MEMBER; eventually VARS.default_outfit
    endIf
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Outfit(code_return, str_name, code_outfit)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Outfit(CODES.HASNT_MEMBER, str_name, code_outfit)
        return
    endIf

    if code_outfit == CODES.IS_MEMBER
        p_Notify_On_Outfit(ref_member.Outfit_Member(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_SETTLER
        p_Notify_On_Outfit(ref_member.Outfit_Settler(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_THRALL
        p_Notify_On_Outfit(ref_member.Outfit_Thrall(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_FOLLOWER
        p_Notify_On_Outfit(ref_member.Outfit_Follower(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_IMMOBILE
        p_Notify_On_Outfit(ref_member.Outfit_Immobile(), str_name, code_outfit)
    endIf
endFunction

function p_Outfit_Member(Actor ref_actor, bool auto_create)
    p_Outfit(ref_actor, CODES.IS_MEMBER, auto_create)
endFunction

function p_Outfit_Settler(Actor ref_actor, bool auto_create)
    p_Outfit(ref_actor, CODES.IS_SETTLER, auto_create)
endFunction

function p_Outfit_Thrall(Actor ref_actor, bool auto_create)
    p_Outfit(ref_actor, CODES.IS_THRALL, auto_create)
endFunction

function p_Outfit_Follower(Actor ref_actor, bool auto_create)
    p_Outfit(ref_actor, CODES.IS_FOLLOWER, auto_create)
endFunction

function p_Outfit_Immobile(Actor ref_actor, bool auto_create)
    p_Outfit(ref_actor, CODES.IS_IMMOBILE, auto_create)
endFunction

function p_Unoutfit(Actor ref_actor, bool auto_create)
    ; can create a toggle between these two
endFunction

function p_Resurrect(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        p_Notify_On_Resurrect(MEMBERS.Create_Member(ref_actor), str_name)
        return
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Resurrect(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Resurrect(ref_member.Resurrect(), str_name)
endFunction

function p_Settle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Settle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Settle(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Settle(ref_member.Settle(), str_name)
endFunction

function p_Unsettle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unsettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unsettle(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Unsettle(ref_member.Unsettle(), str_name)
endFunction

function p_Resettle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Resettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Resettle(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Settler()
        code_return = ref_member.Settle()
        if code_return < 0
            p_Notify_On_Resettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_settler ref_settler = ref_member.Get_Settler()
    if !ref_settler
        p_Notify_On_Resettle(CODES.HASNT_SETTLER, str_name)
        return
    endIf

    p_Notify_On_Resettle(ref_settler.Resettle(), str_name)
endFunction

function p_Enthrall(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Enthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Enthrall(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Enthrall(ref_member.Enthrall(), str_name)
endFunction

function p_Unthrall(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unthrall(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Unthrall(ref_member.Unthrall(), str_name)
endFunction

function p_Immobilize(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Immobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Immobilize(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Immobilize(ref_member.Immobilize(), str_name)
endFunction

function p_Mobilize(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Mobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Mobilize(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Mobilize(ref_member.Mobilize(), str_name)
endFunction

function p_Paralyze(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Paralyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Paralyze(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Immobile()
        code_return = ref_member.Immobilize()
        if code_return < 0
            p_Notify_On_Paralyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_immobile ref_immobile = ref_member.Get_Immobile()
    if !ref_immobile
        p_Notify_On_Paralyze(CODES.ISNT_IMMOBILE, str_name)
        return
    endIf
    
    p_Notify_On_Paralyze(ref_immobile.Paralyze(), str_name)
endFunction

function p_Unparalyze(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unparalyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unparalyze(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Immobile()
        code_return = ref_member.Immobilize()
        if code_return < 0
            p_Notify_On_Unparalyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_immobile ref_immobile = ref_member.Get_Immobile()
    if !ref_immobile
        p_Notify_On_Unparalyze(CODES.ISNT_IMMOBILE, str_name)
        return
    endIf

    p_Notify_On_Unparalyze(ref_immobile.Unparalyze(), str_name)
endFunction

function p_Style(Actor ref_actor, int code_style, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if code_style != CODES.IS_DEFAULT &&\
        code_style != CODES.IS_WARRIOR &&\
        code_style != CODES.IS_MAGE &&\
        code_style != CODES.IS_ARCHER
        code_style = VARS.auto_style; eventually VARS.default_style
    endIf

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Style(code_return, str_name, code_style)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Style(CODES.HASNT_MEMBER, str_name, code_style)
        return
    endIf

    if code_style == CODES.IS_DEFAULT
        p_Notify_On_Style(ref_member.Style_Default(), str_name, code_style)
    elseIf code_style == CODES.IS_WARRIOR
        p_Notify_On_Style(ref_member.Style_Warrior(), str_name, code_style)
    elseIf code_style == CODES.IS_MAGE
        p_Notify_On_Style(ref_member.Style_Mage(), str_name, code_style)
    elseIf code_style == CODES.IS_ARCHER
        p_Notify_On_Style(ref_member.Style_Archer(), str_name, code_style)
    endIf
endFunction

function p_Style_Default(Actor ref_actor, bool auto_create)
    p_Style(ref_actor, CODES.IS_DEFAULT, auto_create)
endFunction

function p_Style_Warrior(Actor ref_actor, bool auto_create)
    p_Style(ref_actor, CODES.IS_WARRIOR, auto_create)
endFunction

function p_Style_Mage(Actor ref_actor, bool auto_create)
    p_Style(ref_actor, CODES.IS_MAGE, auto_create)
endFunction

function p_Style_Archer(Actor ref_actor, bool auto_create)
    p_Style(ref_actor, CODES.IS_ARCHER, auto_create)
endFunction

function p_Vitalize(Actor ref_actor, int code_vitality, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)
    
    if code_vitality != CODES.IS_MORTAL &&\
        code_vitality != CODES.IS_PROTECTED &&\
        code_vitality != CODES.IS_ESSENTIAL &&\
        code_vitality != CODES.IS_INVULNERABLE
        code_vitality = VARS.auto_vitality; eventually VARS.default_vitality
    endIf
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Vitalize(code_return, str_name, code_vitality)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Vitalize(CODES.HASNT_MEMBER, str_name, code_vitality)
        return
    endIf

    if code_vitality == CODES.IS_MORTAL
        p_Notify_On_Vitalize(ref_member.Vitalize_Mortal(), str_name, code_vitality)
    elseIf code_vitality == CODES.IS_PROTECTED
        p_Notify_On_Vitalize(ref_member.Vitalize_Protected(), str_name, code_vitality)
    elseIf code_vitality == CODES.IS_ESSENTIAL
        p_Notify_On_Vitalize(ref_member.Vitalize_Essential(), str_name, code_vitality)
    elseIf code_vitality == CODES.IS_INVULNERABLE
        p_Notify_On_Vitalize(ref_member.Vitalize_Invulnerable(), str_name, code_vitality)
    endIf
endFunction

function p_Vitalize_Mortal(Actor ref_actor, bool auto_create)
    p_Vitalize(ref_actor, CODES.IS_MORTAL, auto_create)
endFunction

function p_Vitalize_Protected(Actor ref_actor, bool auto_create)
    p_Vitalize(ref_actor, CODES.IS_PROTECTED, auto_create)
endFunction

function p_Vitalize_Essential(Actor ref_actor, bool auto_create)
    p_Vitalize(ref_actor, CODES.IS_ESSENTIAL, auto_create)
endFunction

function p_Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    p_Vitalize(ref_actor, CODES.IS_INVULNERABLE, auto_create)
endFunction

function p_Follow(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Follow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Follow(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Follow(ref_member.Follow(), str_name)
endFunction

function p_Unfollow(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unfollow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unfollow(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    p_Notify_On_Unfollow(ref_member.Unfollow(), str_name)
endFunction

function p_Sneak(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Sneak(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return < 0
            p_Notify_On_Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        p_Notify_On_Sneak(CODES.HASNT_FOLLOWER, str_name)
        return
    endIf

    p_Notify_On_Sneak(ref_follower.Sneak(), str_name)
endFunction

function p_Unsneak(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            p_Notify_On_Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Notify_On_Unsneak(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return < 0
            p_Notify_On_Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        p_Notify_On_Unsneak(CODES.HASNT_FOLLOWER, str_name)
        return
    endIf

    p_Notify_On_Unsneak(ref_follower.Unsneak(), str_name)
endFunction

function p_Toggle_Member(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member
        p_Unmember(ref_actor)
    else
        p_Member(ref_actor)
    endIf
endFunction

function p_Toggle_Settler(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Settler()
        p_Unsettle(ref_actor, true)
    else
        p_Settle(ref_actor, true)
    endIf
endFunction

function p_Toggle_Thrall(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Thrall()
        p_Unthrall(ref_actor, true)
    else
        p_Enthrall(ref_actor, true)
    endIf
endFunction

function p_Toggle_Immobile(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Immobile()
        p_Mobilize(ref_actor, true)
    else
        p_Immobilize(ref_actor, true)
    endIf
endFunction

function p_Toggle_Paralyzed(Actor ref_actor)
    doticu_npcp_immobile ref_immobile = MEMBERS.Get_Immobile(ref_actor)
    if ref_immobile && ref_immobile.Is_Paralyzed()
        p_Unparalyze(ref_actor, true)
    else
        p_Paralyze(ref_actor, true)
    endIf
endFunction

function p_Toggle_Follower(Actor ref_actor)
    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower
        p_Unfollow(ref_actor, true)
    else
        p_Follow(ref_actor, true)
    endIf
endFunction

function p_Toggle_Sneak(Actor ref_actor)
    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower && ref_follower.Is_Sneak()
        p_Unsneak(ref_actor, true)
    else
        p_Sneak(ref_actor, true)
    endIf
endFunction

function p_Cycle_Style(Actor ref_actor, bool auto_create)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Style(ref_actor, VARS.auto_style, auto_create)
    elseIf ref_member.Is_Styled_Default()
        p_Style(ref_actor, CODES.IS_WARRIOR, auto_create)
    elseIf ref_member.Is_Styled_Warrior()
        p_Style(ref_actor, CODES.IS_MAGE, auto_create)
    elseIf ref_member.Is_Styled_Mage()
        p_Style(ref_actor, CODES.IS_ARCHER, auto_create)
    elseIf ref_member.Is_Styled_Archer()
        p_Style(ref_actor, CODES.IS_DEFAULT, auto_create)
    endIf
endFunction

function p_Cycle_Vitality(Actor ref_actor, bool auto_create)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        p_Vitalize(ref_actor, VARS.auto_vitality, auto_create)
    elseIf ref_member.Is_Vitalized_Mortal()
        p_Vitalize(ref_actor, CODES.IS_PROTECTED, auto_create)
    elseIf ref_member.Is_Vitalized_Protected()
        p_Vitalize(ref_actor, CODES.IS_ESSENTIAL, auto_create)
    elseIf ref_member.Is_Vitalized_Essential()
        p_Vitalize(ref_actor, CODES.IS_INVULNERABLE, auto_create)
    elseIf ref_member.Is_Vitalized_Invulnerable()
        p_Vitalize(ref_actor, CODES.IS_MORTAL, auto_create)
    endIf
endFunction

function p_Followers_Summon_All()
    p_Notify_On_Followers_Summon_All(FOLLOWERS.Summon_All())
endFunction

function p_Followers_Summon_Mobile()
    p_Notify_On_Followers_Summon_Mobile(FOLLOWERS.Summon_Mobile())
endFunction

function p_Followers_Summon_Immobile()
    p_Notify_On_Followers_Summon_Immobile(FOLLOWERS.Summon_Immobile())
endFunction

function p_Followers_Summon_Mobile_Behind()
    p_Notify_On_Followers_Summon_Mobile_Behind(FOLLOWERS.Summon_Mobile_Behind())
endFunction

function p_Followers_Settle()
    p_Notify_On_Followers_Settle(FOLLOWERS.Settle())
endFunction

function p_Followers_Unsettle()
    p_Notify_On_Followers_Unsettle(FOLLOWERS.Unsettle())
endFunction

function p_Followers_Immobilize()
    p_Notify_On_Followers_Immobilize(FOLLOWERS.Immobilize())
endFunction

function p_Followers_Mobilize()
    p_Notify_On_Followers_Mobilize(FOLLOWERS.Mobilize())
endFunction

function p_Followers_Sneak()
    p_Notify_On_Followers_Sneak(FOLLOWERS.Sneak())
endFunction

function p_Followers_Unsneak()
    p_Notify_On_Followers_Unsneak(FOLLOWERS.Unsneak())
endFunction

function p_Followers_Resurrect()
    p_Notify_On_Followers_Resurrect(FOLLOWERS.Resurrect())
endFunction

function p_Followers_Unfollow()
    p_Notify_On_Followers_Unfollow(FOLLOWERS.Unfollow())
endFunction

function p_Followers_Unmember()
    p_Notify_On_Followers_Unmember(FOLLOWERS.Unmember())
endFunction

function p_Toggle_Followers_Settle()
    if FOLLOWERS.Get_Count_Settler() > 0
        p_Followers_Unsettle()
    else
        p_Followers_Settle()
    endIf
endFunction

function p_Toggle_Followers_Immobilize()
    if FOLLOWERS.Get_Count_Immobile() > 0
        p_Followers_Mobilize()
    else
        p_Followers_Immobilize()
    endIf
endFunction

function p_Toggle_Followers_Sneak()
    if FOLLOWERS.Get_Count_Sneak() > 0
        p_Followers_Unsneak()
    else
        p_Followers_Sneak()
    endIf
endFunction

; Public Methods
function Member(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Member(ref_actor)
    GotoState("")
endFunction

function Unmember(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Unmember(ref_actor)
    GotoState("")
endFunction

function Clone(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Clone(ref_actor)
    GotoState("")
endFunction

function Unclone(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Unclone(ref_actor)
    GotoState("")
endFunction

function Pack(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Pack(ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Member(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Outfit_Member(ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Settler(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Outfit_Settler(ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Thrall(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Outfit_Thrall(ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Follower(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Outfit_Follower(ref_actor, auto_create)
    GotoState("")
endFunction

function Outfit_Immobile(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Outfit_Immobile(ref_actor, auto_create)
    GotoState("")
endFunction

function Unoutfit(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Unoutfit(ref_actor, auto_create)
    GotoState("")
endFunction

function Resurrect(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Resurrect(ref_actor, auto_create)
    GotoState("")
endFunction

function Settle(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Settle(ref_actor, auto_create)
    GotoState("")
endFunction

function Unsettle(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Unsettle(ref_actor, auto_create)
    GotoState("")
endFunction

function Resettle(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Resettle(ref_actor, auto_create)
    GotoState("")
endFunction

function Enthrall(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Enthrall(ref_actor, auto_create)
    GotoState("")
endFunction

function Unthrall(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Unthrall(ref_actor, auto_create)
    GotoState("")
endFunction

function Immobilize(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Immobilize(ref_actor, auto_create)
    GotoState("")
endFunction

function Mobilize(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Mobilize(ref_actor, auto_create)
    GotoState("")
endFunction

function Paralyze(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Paralyze(ref_actor, auto_create)
    GotoState("")
endFunction

function Unparalyze(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Unparalyze(ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Default(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Style_Default(ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Warrior(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Style_Warrior(ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Mage(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Style_Mage(ref_actor, auto_create)
    GotoState("")
endFunction

function Style_Archer(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Style_Archer(ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Mortal(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Vitalize_Mortal(ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Protected(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Vitalize_Protected(ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Essential(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Vitalize_Essential(ref_actor, auto_create)
    GotoState("")
endFunction

function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Vitalize_Invulnerable(ref_actor, auto_create)
    GotoState("")
endFunction

function Follow(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Follow(ref_actor, auto_create)
    GotoState("")
endFunction

function Unfollow(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Unfollow(ref_actor, auto_create)
    GotoState("")
endFunction

function Sneak(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Sneak(ref_actor, auto_create)
    GotoState("")
endFunction

function Unsneak(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Unsneak(ref_actor, auto_create)
    GotoState("")
endFunction

function Toggle_Member(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Toggle_Member(ref_actor)
    GotoState("")
endFunction

function Toggle_Settler(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Toggle_Settler(ref_actor)
    GotoState("")
endFunction

function Toggle_Thrall(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Toggle_Thrall(ref_actor)
    GotoState("")
endFunction

function Toggle_Immobile(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Toggle_Immobile(ref_actor)
    GotoState("")
endFunction

function Toggle_Paralyzed(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Toggle_Paralyzed(ref_actor)
    GotoState("")
endFunction

function Toggle_Follower(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Toggle_Follower(ref_actor)
    GotoState("")
endFunction

function Toggle_Sneak(Actor ref_actor)
    GotoState("p_STATE_BUSY")
    p_Toggle_Sneak(ref_actor)
    GotoState("")
endFunction

function Cycle_Style(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Cycle_Style(ref_actor, auto_create)
    GotoState("")
endFunction

function Cycle_Vitality(Actor ref_actor, bool auto_create)
    GotoState("p_STATE_BUSY")
    p_Cycle_Vitality(ref_actor, auto_create)
    GotoState("")
endFunction

function Followers_Summon_All()
    GotoState("p_STATE_BUSY")
    p_Followers_Summon_All()
    GotoState("")
endFunction

function Followers_Summon_Mobile()
    GotoState("p_STATE_BUSY")
    p_Followers_Summon_Mobile()
    GotoState("")
endFunction

function Followers_Summon_Immobile()
    GotoState("p_STATE_BUSY")
    p_Followers_Summon_Immobile()
    GotoState("")
endFunction

function Followers_Summon_Mobile_Behind()
    GotoState("p_STATE_BUSY")
    p_Followers_Summon_Mobile_Behind()
    GotoState("")
endFunction

function Followers_Settle()
    GotoState("p_STATE_BUSY")
    p_Followers_Settle()
    GotoState("")
endFunction

function Followers_Unsettle()
    GotoState("p_STATE_BUSY")
    p_Followers_Unsettle()
    GotoState("")
endFunction

function Followers_Immobilize()
    GotoState("p_STATE_BUSY")
    p_Followers_Immobilize()
    GotoState("")
endFunction

function Followers_Mobilize()
    GotoState("p_STATE_BUSY")
    p_Followers_Mobilize()
    GotoState("")
endFunction

function Followers_Sneak()
    GotoState("p_STATE_BUSY")
    p_Followers_Sneak()
    GotoState("")
endFunction

function Followers_Unsneak()
    GotoState("p_STATE_BUSY")
    p_Followers_Unsneak()
    GotoState("")
endFunction

function Followers_Resurrect()
    GotoState("p_STATE_BUSY")
    p_Followers_Resurrect()
    GotoState("")
endFunction

function Followers_Unfollow()
    GotoState("p_STATE_BUSY")
    p_Followers_Unfollow()
    GotoState("")
endFunction

function Followers_Unmember()
    GotoState("p_STATE_BUSY")
    p_Followers_Unmember()
    GotoState("")
endFunction

function Toggle_Followers_Settle()
    GotoState("p_STATE_BUSY")
    p_Toggle_Followers_Settle()
    GotoState("")
endFunction

function Toggle_Followers_Immobilize()
    GotoState("p_STATE_BUSY")
    p_Toggle_Followers_Immobilize()
    GotoState("")
endFunction

function Toggle_Followers_Sneak()
    GotoState("p_STATE_BUSY")
    p_Toggle_Followers_Sneak()
    GotoState("")
endFunction

; should have a "Member" and "Follower" summon cycle. Very mush desired, so it's easy to pick them out of all the names.

; "all", "mobile", "immobile", follower cycle, etc, such that they each summon one after another

; States
state p_STATE_BUSY
    function Member(Actor ref_actor)
    endFunction
    function Unmember(Actor ref_actor)
    endFunction
    function Clone(Actor ref_actor)
    endFunction
    function Unclone(Actor ref_actor)
    endFunction
    function Pack(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Member(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Settler(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Thrall(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Follower(Actor ref_actor, bool auto_create)
    endFunction
    function Outfit_Immobile(Actor ref_actor, bool auto_create)
    endFunction
    function Unoutfit(Actor ref_actor, bool auto_create)
    endFunction
    function Resurrect(Actor ref_actor, bool auto_create)
    endFunction
    function Settle(Actor ref_actor, bool auto_create)
    endFunction
    function Unsettle(Actor ref_actor, bool auto_create)
    endFunction
    function Resettle(Actor ref_actor, bool auto_create)
    endFunction
    function Enthrall(Actor ref_actor, bool auto_create)
    endFunction
    function Unthrall(Actor ref_actor, bool auto_create)
    endFunction
    function Immobilize(Actor ref_actor, bool auto_create)
    endFunction
    function Mobilize(Actor ref_actor, bool auto_create)
    endFunction
    function Paralyze(Actor ref_actor, bool auto_create)
    endFunction
    function Unparalyze(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Default(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Warrior(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Mage(Actor ref_actor, bool auto_create)
    endFunction
    function Style_Archer(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Mortal(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Protected(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Essential(Actor ref_actor, bool auto_create)
    endFunction
    function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    endFunction
    function Follow(Actor ref_actor, bool auto_create)
    endFunction
    function Unfollow(Actor ref_actor, bool auto_create)
    endFunction
    function Sneak(Actor ref_actor, bool auto_create)
    endFunction
    function Unsneak(Actor ref_actor, bool auto_create)
    endFunction
    
    function Toggle_Member(Actor ref_actor)
    endFunction
    function Toggle_Settler(Actor ref_actor)
    endFunction
    function Toggle_Thrall(Actor ref_actor)
    endFunction
    function Toggle_Immobile(Actor ref_actor)
    endFunction
    function Toggle_Paralyzed(Actor ref_actor)
    endFunction
    function Toggle_Follower(Actor ref_actor)
    endFunction
    function Toggle_Sneak(Actor ref_actor)
    endFunction
    
    function Cycle_Style(Actor ref_actor, bool auto_create)
    endFunction
    function Cycle_Vitality(Actor ref_actor, bool auto_create)
    endFunction
    
    function Followers_Summon_All()
    endFunction
    function Followers_Summon_Mobile()
    endFunction
    function Followers_Summon_Immobile()
    endFunction
    function Followers_Summon_Mobile_Behind()
    endFunction
    function Followers_Settle()
    endFunction
    function Followers_Unsettle()
    endFunction
    function Followers_Immobilize()
    endFunction
    function Followers_Mobilize()
    endFunction
    function Followers_Sneak()
    endFunction
    function Followers_Unsneak()
    endFunction
    function Followers_Resurrect()
    endFunction
    function Followers_Unfollow()
    endFunction
    function Followers_Unmember()
    endFunction
    
    function Toggle_Followers_Settle()
    endFunction
    function Toggle_Followers_Immobilize()
    endFunction
    function Toggle_Followers_Sneak()
    endFunction
endState
