Scriptname doticu_npcp_topics extends TopicInfo hidden

; Member Topics
function Member(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Member_Sync(ref_object as Actor)
endFunction

function Unmember(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unmember(ref_object as Actor)
endFunction

function Clone(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Clone(ref_object as Actor)
endFunction

function Unclone(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unclone(ref_object as Actor)
endFunction

function Pack(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Pack(ref_object as Actor, false)
endFunction

function Outfit_Member(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Member(ref_object as Actor, false)
endFunction

function Outfit_Settler(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Settler(ref_object as Actor, false)
endFunction

function Outfit_Thrall(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Thrall(ref_object as Actor, false)
endFunction

function Outfit_Follower(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Follower(ref_object as Actor, false)
endFunction

function Outfit_Immobile(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Outfit_Immobile(ref_object as Actor, false)
endFunction

function Enthrall(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Enthrall(ref_object as Actor, false)
endFunction

function Unthrall(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unthrall(ref_object as Actor, false)
endFunction

function Style_Default(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Default(ref_object as Actor, false)
endFunction

function Style_Warrior(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Warrior(ref_object as Actor, false)
endFunction

function Style_Mage(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Mage(ref_object as Actor, false)
endFunction

function Style_Archer(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Style_Archer(ref_object as Actor, false)
endFunction

function Vitality_Mortal(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Mortal(ref_object as Actor, false)
endFunction

function Vitality_Protected(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Protected(ref_object as Actor, false)
endFunction

function Vitality_Essential(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Essential(ref_object as Actor, false)
endFunction

function Vitality_Invulnerable(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Vitalize_Invulnerable(ref_object as Actor, false)
endFunction

; Settler Topics
function Settle(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Settle(ref_object as Actor, false)
endFunction

function Unsettle(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unsettle(ref_object as Actor, false)
endFunction

function Resettle(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Resettle(ref_object as Actor, false)
endFunction

; Immobile Topics
function Immobilize(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Immobilize_Sync(ref_object as Actor, false)
endFunction

function Mobilize(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Mobilize_Sync(ref_object as Actor, false)
endFunction

; Follower Topics
function Follow(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Follow(ref_object as Actor, false)
endFunction

function Unfollow(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unfollow(ref_object as Actor, false)
endFunction

function Sneak(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Sneak(ref_object as Actor, false)
endFunction

function Unsneak(ObjectReference ref_object)
    (GetOwningQuest() as doticu_npcp_commands).Unsneak(ref_object as Actor, false)
endFunction
