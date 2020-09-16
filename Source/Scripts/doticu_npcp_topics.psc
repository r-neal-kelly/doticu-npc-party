; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_topics extends TopicInfo hidden

; all the following is to be deleted, see topics_menu Execute

; NPC
function Member(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Member(ref as Actor)
endFunction
function Unmember(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unmember(ref as Actor)
endFunction
function Clone(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Clone(ref as Actor)
endFunction
function Unclone(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unclone(ref as Actor)
endFunction

; Member
function Pack(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Open_Pack(ref as Actor)
endFunction
function Stash(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Stash(ref as Actor)
endFunction
function Mobilize(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Mobilize(ref as Actor)
endFunction
function Immobilize(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Immobilize(ref as Actor)
endFunction
function Settle(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Settle(ref as Actor)
endFunction
function Resettle(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Resettle(ref as Actor)
endFunction
function Unsettle(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unsettle(ref as Actor)
endFunction
function Enthrall(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Enthrall(ref as Actor)
endFunction
function Unthrall(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unthrall(ref as Actor)
endFunction
function Paralyze(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Paralyze(ref as Actor)
endFunction
function Deanimate(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Deanimate(ref as Actor)
endFunction
function Follow(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Follow(ref as Actor)
endFunction
function Unfollow(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unfollow(ref as Actor)
endFunction
function Stylize_Default(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Stylize_Default(ref as Actor)
endFunction
function Stylize_Warrior(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Stylize_Warrior(ref as Actor)
endFunction
function Stylize_Mage(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Stylize_Mage(ref as Actor)
endFunction
function Stylize_Archer(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Stylize_Archer(ref as Actor)
endFunction
function Stylize_Coward(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Stylize_Coward(ref as Actor)
endFunction
function Vitality_Mortal(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Mortal(ref as Actor)
endFunction
function Vitality_Protected(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Protected(ref as Actor)
endFunction
function Vitality_Essential(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Essential(ref as Actor)
endFunction
function Vitality_Invulnerable(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Invulnerable(ref as Actor)
endFunction
function Outfit_Member(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Member_Outfit2(ref as Actor)
endFunction
function Outfit_Immobile(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Immobile_Outfit2(ref as Actor)
endFunction
function Outfit_Settler(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Settler_Outfit2(ref as Actor)
endFunction
function Outfit_Thrall(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Thrall_Outfit2(ref as Actor)
endFunction
function Outfit_Follower(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Follower_Outfit2(ref as Actor)
endFunction
function Outfit_Vanilla(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Vanilla_Outfit2(ref as Actor)
endFunction
function Outfit_Default(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Default_Outfit2(ref as Actor)
endFunction
function Outfit_Current(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Change_Current_Outfit2(ref as Actor)
endFunction
function Style_Show(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Show_Style(ref as Actor)
endFunction
function Vitality_Show(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Show_Vitality(ref as Actor)
endFunction
function Outfit_Show(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Show_Outfit2(ref as Actor)
endFunction

function Direct_Begin(ObjectReference ref)
    (ref as Actor).SetDoingFavor(true)
endFunction
function Direct_End(ObjectReference ref)
    (ref as Actor).SetDoingFavor(false)
endFunction

; Follower
function Sneak(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Sneak(ref as Actor)
endFunction
function Unsneak(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unsneak(ref as Actor)
endFunction
function Saddle(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Saddle(ref as Actor)
endFunction
function Unsaddle(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unsaddle(ref as Actor)
endFunction
function Retreat(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Retreat(ref as Actor)
endFunction
function Unretreat(ObjectReference ref)
    (GetOwningQuest() as doticu_npcp_commands).Unretreat(ref as Actor)
endFunction
