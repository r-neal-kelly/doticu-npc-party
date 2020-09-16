; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_topics_menu extends TopicInfo hidden

function Execute(ObjectReference ref)
    doticu_npcp.Execute_Topic_Info(self as TopicInfo, ref)
endFunction

; all the following is to be deleted

function Exit(ObjectReference ___)
    doticu_npcp.Funcs().ACTORS.Destroy_Menu()
endFunction

function Followers_Summon_All(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Summon_All()
endFunction
function Followers_Summon_Mobile(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Summon_Mobile()
endFunction
function Followers_Summon_Immobile(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Summon_Immobile()
endFunction
function Followers_Stash(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Stash()
endFunction
function Followers_Mobilize(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Mobilize()
endFunction
function Followers_Immobilize(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Immobilize()
endFunction
function Followers_Settle(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Settle()
endFunction
function Followers_Unsettle(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Unsettle()
endFunction
function Followers_Sneak(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Sneak()
endFunction
function Followers_Unsneak(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Unsneak()
endFunction
function Followers_Saddle(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Saddle()
endFunction
function Followers_Unsaddle(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Unsaddle()
endFunction
function Followers_Unfollow(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Unfollow()
endFunction
function Followers_Unmember(ObjectReference ___)
    doticu_npcp.Control().COMMANDS.Followers_Unmember()
endFunction
