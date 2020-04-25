;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_topics extends TopicInfo hidden

; need to investigate if this script is always loaded or instanstiated as needed.

; Member Topics
function Member(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Member_Sync(ref_object as Actor)
endFunction

function Unmember(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unmember_Sync(ref_object as Actor)
endFunction

function Clone(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Clone_Sync(ref_object as Actor)
endFunction

function Unclone(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unclone_Sync(ref_object as Actor)
endFunction

function Pack(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Pack_Sync(ref_object as Actor, false)
endFunction

function Outfit_Show(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Show(ref_object as Actor)
endFunction

function Outfit_Current(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Current_Sync(ref_object as Actor, false)
endFunction

function Outfit_Member(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Member_Sync(ref_object as Actor, false)
endFunction

function Outfit_Settler(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Settler_Sync(ref_object as Actor, false)
endFunction

function Outfit_Thrall(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Thrall_Sync(ref_object as Actor, false)
endFunction

function Outfit_Follower(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Follower_Sync(ref_object as Actor, false)
endFunction

function Outfit_Immobile(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Immobile_Sync(ref_object as Actor, false)
endFunction

function Outfit_Vanilla(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Vanilla_Sync(ref_object as Actor, false)
endFunction

function Outfit_Default(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Default_Sync(ref_object as Actor, false)
endFunction

function Enthrall(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Enthrall_Sync(ref_object as Actor, false)
endFunction

function Unthrall(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unthrall_Sync(ref_object as Actor, false)
endFunction

function Style_Show(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Show(ref_object as Actor)
endFunction

function Style_Default(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Default_Sync(ref_object as Actor, false)
endFunction

function Style_Warrior(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Warrior_Sync(ref_object as Actor, false)
endFunction

function Style_Mage(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Mage_Sync(ref_object as Actor, false)
endFunction

function Style_Archer(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Archer_Sync(ref_object as Actor, false)
endFunction

function Style_Coward(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Coward_Sync(ref_object as Actor, false)
endFunction

function Vitality_Show(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitality_Show(ref_object as Actor)
endFunction

function Vitality_Mortal(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Mortal_Sync(ref_object as Actor, false)
endFunction

function Vitality_Protected(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Protected_Sync(ref_object as Actor, false)
endFunction

function Vitality_Essential(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Essential_Sync(ref_object as Actor, false)
endFunction

function Vitality_Invulnerable(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Invulnerable_Sync(ref_object as Actor, false)
endFunction

; Settler Topics
function Settle(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Settle_Sync(ref_object as Actor, false)
endFunction

function Resettle(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Resettle_Sync(ref_object as Actor, false)
endFunction

function Unsettle(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unsettle_Sync(ref_object as Actor, false)
endFunction

; Immobile Topics
function Immobilize(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Immobilize_Sync(ref_object as Actor, false)
endFunction

function Mobilize(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Mobilize_Sync(ref_object as Actor, false)
endFunction

function Paralyze(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Paralyze_Sync(ref_object as Actor, false)
endFunction

; Follower Topics
function Follow(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Follow_Sync(ref_object as Actor, false)
endFunction

function Unfollow(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unfollow_Sync(ref_object as Actor, false)
endFunction

function Sneak(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Sneak_Sync(ref_object as Actor, false)
endFunction

function Unsneak(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unsneak_Sync(ref_object as Actor, false)
endFunction
