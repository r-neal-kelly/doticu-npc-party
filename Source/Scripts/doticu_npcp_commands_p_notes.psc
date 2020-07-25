;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_commands_p_notes extends Quest

; Modules
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA              =  none

; Private Variables
bool                p_is_created        = false

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

; Public Methods
function Member(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " is now a member.")
    elseIf code_return == doticu_npcp_codes.CANT_CLONE()
        LOGS.Create_Note(str_name + " could not be cloned. Try to manually member them.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a member.")
    elseIf code_return == doticu_npcp_codes.HAS_MEMBER()
        LOGS.Create_Note(str_name + " is already a member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member.")
    elseIf code_return == doticu_npcp_codes.CHILD()
        LOGS.Create_Note("A child cannot become a member.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be a member: " + code_return)
    endIf
endFunction

function Unmember(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " is no longer a member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " was already not a member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't be unmembered.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be unmembered: " + code_return)
    endIf
endFunction

function Clone(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("A clone of " + str_name + " is now a member.")
    elseIf code_return == doticu_npcp_codes.CANT_CLONE()
        LOGS.Create_Note(str_name + " could not be cloned.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for a clone of " + str_name + " to be a member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, can't be cloned, and can't become a member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("A clone of this can't be made a member.")
    elseIf code_return == doticu_npcp_codes.CHILD()
        LOGS.Create_Note("A child cannot be cloned.")
    else
        LOGS.Create_Error("It's unknown why a clone of " + str_name + " can't be a member: " + code_return)
    endIf
endFunction

function Unclone(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " is no longer a member and was uncloned.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't be unmembered or uncloned.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " was already not a member and can't be uncloned.")
    elseIf code_return == doticu_npcp_codes.ISNT_CLONE()
        LOGS.Create_Note(str_name + " is not a clone.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be unmembered and uncloned: " + code_return)
    endIf
endFunction

function Pack(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will carry the pack.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to carry a pack as a new member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't carry a pack as a new member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member and carry a pack.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't carry a pack.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't carry the pack: " + code_return)
    endIf
endFunction

function Stash(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has stashed away the contents of their pack.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That is not an actor, and cannot stash anything.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member and cannot stash their pack.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't stash their pack: " + code_return)
    endIf
endFunction

function Outfit(int code_return, string str_name, int code_outfit2)
    string str_outfit

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_MEMBER()
        str_outfit = "a member"
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_SETTLER()
        str_outfit = "a settler"
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_THRALL()
        str_outfit = "a thrall"
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_FOLLOWER()
        str_outfit = "a follower"
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_IMMOBILE()
        str_outfit = "an immobile"
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_VANILLA()
        str_outfit = "a vanilla npc"
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_DEFAULT()
        str_outfit = "a default npc"
    endIf

    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has been outfitted as " + str_outfit + ".")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to be outfitted as " + str_outfit + ".")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't be outfitted as " + str_outfit + ".")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become " + str_outfit + " and be outfitted.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be outfitted.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be outfitted as " + str_outfit + ": " + code_return)
    endIf
endFunction

function Resurrect(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has been resurrected.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to be a resurrected new member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be resurrected, and so can't be a new member.")
    elseIf code_return == doticu_npcp_codes.IS_ALIVE()
        LOGS.Create_Note(str_name + " is already alive.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a resurrected new member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be resurrected.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be resurrected: " + code_return)
    endIf
endFunction

function Reanimate(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has been reanimated.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to be a reanimated member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be reanimated, and so can't be a new member.")
    elseIf code_return == doticu_npcp_codes.IS_ALIVE()
        LOGS.Create_Note(str_name + " is alive and can't be reanimated.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a reanimated member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be reanimated.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be reanimated: " + code_return)
    endIf
endFunction

function Mannequinize(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has been turned into a mannequin.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to be a mannequin.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be resurrected, and so can't be a mannequin.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a mannequin.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be a mannequin.")
    elseIf code_return == doticu_npcp_codes.IS_MANNEQUIN()
        LOGS.Create_Note(str_name + " is already a mannequin.")
    elseIf code_return == doticu_npcp_codes.HASNT_MARKER()
        LOGS.Create_Note(str_name + " doesn't have a valid mannequin marker.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be mannequinized: " + code_return)
    endIf
endFunction

function Unmannequinize(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " is no longer a mannequin.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That isn't an npc.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MANNEQUIN()
        LOGS.Create_Note(str_name + " isn't a mannequin.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be unmannequinized: " + code_return)
    endIf
endFunction

function Settle(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will settle here.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a settled member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't be a settled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a settled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't settle here.")
    elseIf code_return == doticu_npcp_codes.IS_SETTLER()
        LOGS.Create_Note(str_name + " is already settled elsewhere.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't settle here: " + code_return)
    endIf
endFunction

function Unsettle(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will no longer be a settler.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become an unsettled member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't be an unsettled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become an unsettled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't unsettle.")
    elseIf code_return == doticu_npcp_codes.ISNT_SETTLER()
        LOGS.Create_Note(str_name + " isn't settled.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't unsettle: " + code_return)
    endIf
endFunction

function Resettle(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will resettle here.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a resettled member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a resettled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a resettled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't resettle.")
    elseIf code_return == doticu_npcp_codes.ISNT_SETTLER()
        LOGS.Create_Note(str_name + " isn't a settler, and so can't resettle.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't resettle: " + code_return)
    endIf
endFunction

function Enthrall(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " is now enthralled.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become an enthralled member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't be enthralled.")
    elseIf code_return == doticu_npcp_codes.NON_VAMPIRE()
        LOGS.Create_Note("Only a vampire can enthrall a member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become an enthralled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be enthralled.")
    elseIf code_return == doticu_npcp_codes.IS_IMMOBILE()
        LOGS.Create_Note(str_name + " is already enthralled.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be enthralled: " + code_return)
    endIf
endFunction

function Unthrall(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " is no longer enthralled.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become an unthralled member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't be unthralled.")
    elseIf code_return == doticu_npcp_codes.NON_VAMPIRE()
        LOGS.Create_Note("Only a vampire can unthrall a member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become an unthralled member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be unthralled.")
    elseIf code_return == doticu_npcp_codes.ISNT_IMMOBILE()
        LOGS.Create_Note(str_name + " is already unthralled.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be unthralled: " + code_return)
    endIf
endFunction

function Immobilize(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will stop moving.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become an immobile member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't be immobilized.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become an immobile member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be immobilized.")
    elseIf code_return == doticu_npcp_codes.IS_IMMOBILE()
        LOGS.Create_Note(str_name + " is already immobile.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be immobilized: " + code_return)
    endIf
endFunction

function Mobilize(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will start moving.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a mobile member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't be mobilized.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a mobile member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be mobilized.")
    elseIf code_return == doticu_npcp_codes.ISNT_IMMOBILE()
        LOGS.Create_Note(str_name + " is already mobile.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be mobilized: " + code_return)
    endIf
endFunction

function Paralyze(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will be paralyzed.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become an immobile and paralyzed member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become an immobile and paralyzed member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become an immobile and paralyzed member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be immobile and paralyzed.")
    elseIf code_return == doticu_npcp_codes.IS_PARALYZED()
        LOGS.Create_Note(str_name + " is already paralyzed.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be immobile and paralyzed: " + code_return)
    endIf
endFunction

function Unparalyze(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will no longer be paralyzed.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become an immobile and unparalyzed member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become an immobile and unparalyzed member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become an immobile and unparalyzed member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be immobile and unparalyzed.")
    elseIf code_return == doticu_npcp_codes.ISNT_PARALYZED()
        LOGS.Create_Note(str_name + " wasn't paralyzed.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't stop being paralyzed: " + code_return)
    endIf
endFunction

function Stylize(int code_return, string str_name, int code_style)
    string str_style
    if code_style == doticu_npcp_codes.STYLE_DEFAULT()
        str_style = "a default member"
    elseIf code_style == doticu_npcp_codes.STYLE_WARRIOR()
        str_style = "a warrior"
    elseIf code_style == doticu_npcp_codes.STYLE_MAGE()
        str_style = "a mage"
    elseIf code_style == doticu_npcp_codes.STYLE_ARCHER()
        str_style = "an archer"
    elseIf code_style == doticu_npcp_codes.STYLE_COWARD()
        str_style = "a coward"
    endIf

    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " now fights as " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.ISNT_STYLE()
        LOGS.Create_Note("That isn't a member style.")
    elseIf code_return == doticu_npcp_codes.IS_DEFAULT()
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.IS_WARRIOR()
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.IS_MAGE()
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.IS_ARCHER()
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    elseIf code_return == doticu_npcp_codes.IS_COWARD()
        LOGS.Create_Note(str_name + " is already " + str_style + ".")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be " + str_style + ": " + code_return)
    endIf
endFunction

function Vitalize(int code_return, string str_name, int code_vitality)
    string str_vitality

    if code_vitality == doticu_npcp_codes.VITALITY_MORTAL()
        str_vitality = "a mortal member"
    elseIf code_vitality == doticu_npcp_codes.VITALITY_PROTECTED()
        str_vitality = "a protected member"
    elseIf code_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
        str_vitality = "an essential member"
    elseIf code_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
        str_vitality = "an invulnerable member"
    endIf

    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " is now " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.IS_MORTAL()
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.IS_PROTECTED()
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.IS_ESSENTIAL()
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    elseIf code_return == doticu_npcp_codes.IS_INVULNERABLE()
        LOGS.Create_Note(str_name + " is already " + str_vitality + ".")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't be " + str_vitality + ": " + code_return)
    endIf
endFunction

function Follow(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will start following.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a member or a follower.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_FOLLOWER()
        LOGS.Create_Note("No room for " + str_name + " to become a follower.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member or a follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't start following.")
    elseIf code_return == doticu_npcp_codes.IS_FOLLOWER()
        LOGS.Create_Note(str_name + " is already following.")
    elseIf code_return == doticu_npcp_codes.IS_MANNEQUIN()
        LOGS.Create_Note(str_name + " is a mannequin and cannot follow.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't start following: " + code_return)
    endIf
endFunction

function Unfollow(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will stop following.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a non-following member.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a non-following member.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member or a non-following member.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't stop following.")
    elseIf code_return == doticu_npcp_codes.ISNT_FOLLOWER() || code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note(str_name + " wasn't following.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't stop following: " + code_return)
    endIf
endFunction

function Sneak(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will start sneaking.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a member or a sneaking follower.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_FOLLOWER()
        LOGS.Create_Note("No room for " + str_name + " to become a sneaking follower.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a sneaking follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member or a sneaking follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't start sneaking.")
    elseIf code_return == doticu_npcp_codes.ISNT_FOLLOWER()
        LOGS.Create_Note(str_name + " isn't a follower, and so can't start sneaking.")
    elseIf code_return == doticu_npcp_codes.IS_SNEAK()
        LOGS.Create_Note(str_name + " is already sneaking.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't start sneaking: " + code_return)
    endIf
endFunction

function Unsneak(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " will stop sneaking.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a member or an unsneaking follower.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_FOLLOWER()
        LOGS.Create_Note("No room for " + str_name + " to become an unsneaking follower.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become an unsneaking follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member or an unsneaking follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't stop sneaking.")
    elseIf code_return == doticu_npcp_codes.ISNT_FOLLOWER()
        LOGS.Create_Note(str_name + " isn't a follower, and so can't stop sneaking.")
    elseIf code_return == doticu_npcp_codes.ISNT_SNEAK()
        LOGS.Create_Note(str_name + " wasn't sneaking.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't stop sneaking: " + code_return)
    endIf
endFunction

function Saddle(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has saddled up.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a member or a saddled follower.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_FOLLOWER()
        LOGS.Create_Note("No room for " + str_name + " to become a saddled follower.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become a saddled follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member or a saddled follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't saddle up.")
    elseIf code_return == doticu_npcp_codes.ISNT_FOLLOWER()
        LOGS.Create_Note(str_name + " isn't a follower, and so can't saddle up.")
    elseIf code_return == doticu_npcp_codes.IS_SADDLER()
        LOGS.Create_Note(str_name + " is already saddled up.")
    elseIf code_return == doticu_npcp_codes.INTERIOR()
        LOGS.Create_Note(str_name + " cannot saddle up in an interior space.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't saddle up: " + code_return)
    endIf
endFunction

function Unsaddle(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has unsaddled.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_MEMBER()
        LOGS.Create_Note("No room for " + str_name + " to become a member or an unsaddled follower.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_FOLLOWER()
        LOGS.Create_Note("No room for " + str_name + " to become an unsaddled follower.")
    elseIf code_return == doticu_npcp_codes.CANT_RESURRECT()
        LOGS.Create_Note(str_name + " can't be revived, and so can't become an unsaddled follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("That can't become a member or an unsaddled follower.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't unsaddle.")
    elseIf code_return == doticu_npcp_codes.ISNT_FOLLOWER()
        LOGS.Create_Note(str_name + " isn't a follower, and so can't unsaddle.")
    elseIf code_return == doticu_npcp_codes.ISNT_SADDLER()
        LOGS.Create_Note(str_name + " wasn't saddled.")
    else
        LOGS.Create_Error("It's unknown why " + str_name + " can't unsaddle: " + code_return)
    endIf
endFunction

function Summon(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note(str_name + " has been summoned.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("Can only summon actors.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be summoned.")
    elseIf code_return == doticu_npcp_codes.IS_MANNEQUIN()
        LOGS.Create_Note(str_name + " is a mannequin, and so wasn't summoned.")
    else
        LOGS.Create_Note("It is unknown why " + str_name + " can not be summoned: " + code_return)
    endIf
endFunction

function Goto(int code_return, string str_name)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("You have gone to " + str_name)
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("Can only go to actors.")
    elseIf code_return == doticu_npcp_codes.ISNT_MEMBER() || code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note(str_name + " isn't a member, and so can't be gone to.")
    else
        LOGS.Create_Note("It is unknown why " + str_name + " can not be gone to: " + code_return)
    endIf
endFunction

function Move(int code_return, string str_name)
    if code_return == doticu_npcp_codes.STARTED()
        LOGS.Create_Note("Moving " + str_name + ".")
    elseIf code_return == doticu_npcp_codes.STOPPED()
        LOGS.Create_Note("Stopped moving npc.")
    elseIf code_return == doticu_npcp_codes.ISNT_ACTOR()
        LOGS.Create_Note("Can only move actors.")
    elseIf code_return == doticu_npcp_codes.IS_MANNEQUIN()
        LOGS.Create_Note("Can't move mannequins.")
    elseIf code_return == doticu_npcp_codes.IS_DISPLAY()
        LOGS.Create_Note("Can't move displays.")
    endIf
endFunction

function Members_Display_Start(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("Display mode has been started.")
    elseIf code_return == doticu_npcp_codes.HAS_DISPLAY()
        LOGS.Create_Note("Display has already been started.")
    elseIf code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note("No members to display. Check your filter.")
    else
        LOGS.Create_Error("Could not start a display: " + code_return)
    endIf
endFunction

function Members_Display_Stop(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("Display has now been stopped.")
    elseIf code_return == doticu_npcp_codes.HASNT_DISPLAY()
        LOGS.Create_Note("Display has already stopped.")
    else
        LOGS.Create_Error("Could not stop display: " + code_return)
    endIf
endFunction

function Members_Display_Next(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("Displaying next members.")
    elseIf code_return == doticu_npcp_codes.HASNT_DISPLAY()
        LOGS.Create_Note("You need to start up a display first.")
    elseIf code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note("No remaining members to display. Stopping.")
    else
        LOGS.Create_Error("Could not display the next members: " + code_return)
    endIf
endFunction

function Members_Display_Previous(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("Displaying previous members.")
    elseIf code_return == doticu_npcp_codes.HASNT_DISPLAY()
        LOGS.Create_Note("You need to start up a display first.")
    elseIf code_return == doticu_npcp_codes.HASNT_MEMBER()
        LOGS.Create_Note("No remaining members to display. Stopping.")
    else
        LOGS.Create_Error("Could not display the previous members: " + code_return)
    endIf
endFunction

function Followers_Summon_All(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("Summoned all followers.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to summon.")
    else
        LOGS.Create_Error("Could not summon all followers: " + code_return)
    endIf
endFunction

function Followers_Summon_Mobile(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("Summoned all mobile followers.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to summon.")
    elseIf code_return == doticu_npcp_codes.HASNT_MOBILE()
        LOGS.Create_Note("No mobile followers to summon.")
    else
        LOGS.Create_Error("Could not summon mobile followers: " + code_return)
    endIf
endFunction

function Followers_Summon_Immobile(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("Summoned all immobile followers.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to summon.")
    elseIf code_return == doticu_npcp_codes.HASNT_IMMOBILE()
        LOGS.Create_Note("No immobile followers to summon.")
    else
        LOGS.Create_Error("Could not summon immobile followers: " + code_return)
    endIf
endFunction

function Followers_Settle(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers settle where they stand.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to settle.")
    else
        LOGS.Create_Error("Could not settle followers: " + code_return)
    endIf
endFunction

function Followers_Unsettle(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers have unsettled.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to unsettle.")
    elseIf code_return == doticu_npcp_codes.HASNT_SETTLER()
        LOGS.Create_Note("No followers are already unsettled.")
    else
        LOGS.Create_Error("Could not unsettle followers: " + code_return)
    endIf
endFunction

function Followers_Immobilize(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers have been immobilized.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to immobilize.")
    elseIf code_return == doticu_npcp_codes.HASNT_MOBILE()
        LOGS.Create_Note("All followers are already immobilized.")
    else
        LOGS.Create_Error("Could not immobilize followers: " + code_return)
    endIf
endFunction

function Followers_Mobilize(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers have been mobilized.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to mobilize.")
    elseIf code_return == doticu_npcp_codes.HASNT_IMMOBILE()
        LOGS.Create_Note("All followers are already mobilized.")
    else
        LOGS.Create_Error("Could not mobilize followers: " + code_return)
    endIf
endFunction

function Followers_Sneak(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers will sneak.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to sneak.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_SNEAK()
        LOGS.Create_Note("All followers are already sneaking.")
    else
        LOGS.Create_Error("Could not make followers sneak: " + code_return)
    endIf
endFunction

function Followers_Unsneak(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers will stop sneaking.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to stop sneaking.")
    elseIf code_return == doticu_npcp_codes.HASNT_SNEAK()
        LOGS.Create_Note("All followers are already not sneaking.")
    else
        LOGS.Create_Error("Could not make followers stop sneaking: " + code_return)
    endIf
endFunction

function Followers_Saddle(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers will saddle up.")
    elseIf code_return == doticu_npcp_codes.INTERIOR()
        LOGS.Create_Note("Followers cannot saddle up in an interior space.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to saddle up.")
    elseIf code_return == doticu_npcp_codes.HASNT_NON_SADDLER()
        LOGS.Create_Note("All followers are already saddled up.")
    else
        LOGS.Create_Error("Could not make followers saddle up: " + code_return)
    endIf
endFunction

function Followers_Unsaddle(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers will unsaddle.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to unsaddle.")
    elseIf code_return == doticu_npcp_codes.HASNT_SADDLER()
        LOGS.Create_Note("All followers are already unsaddled.")
    else
        LOGS.Create_Error("Could not make followers unsaddle: " + code_return)
    endIf
endFunction

function Followers_Stash(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers have stashed their packs away.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to stash packs.")
    else
        LOGS.Create_Error("Followers could not stash their packs: " + code_return)
    endIf
endFunction

function Followers_Resurrect(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All dead followers will resurrect.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to resurrect.")
    elseIf code_return == doticu_npcp_codes.HASNT_DEAD()
        LOGS.Create_Note("All followers are already alive.")
    else
        LOGS.Create_Error("Could not make followers resurrect: " + code_return)
    endIf
endFunction

function Followers_Unfollow(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers will no longer follow.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to unfollow.")
    else
        LOGS.Create_Error("Could not make followers stop following: " + code_return)
    endIf
endFunction

function Followers_Unmember(int code_return)
    if code_return == doticu_npcp_codes.SUCCESS()
        LOGS.Create_Note("All followers are no longer members.")
    elseIf code_return == doticu_npcp_codes.HASNT_FOLLOWER()
        LOGS.Create_Note("No followers to unmember.")
    else
        LOGS.Create_Error("Could not unmember followers: " + code_return)
    endIf
endFunction
