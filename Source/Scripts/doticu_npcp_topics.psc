; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_topics extends TopicInfo hidden

; NPC
function Member(ObjectReference ref) native
function Unmember(ObjectReference ref) native
function Clone(ObjectReference ref) native
function Unclone(ObjectReference ref) native

; Member
function Pack(ObjectReference ref) native
function Stash(ObjectReference ref) native
function Mobilize(ObjectReference ref) native
function Immobilize(ObjectReference ref) native
function Settle(ObjectReference ref) native
function Resettle(ObjectReference ref) native
function Unsettle(ObjectReference ref) native
function Enthrall(ObjectReference ref) native
function Unthrall(ObjectReference ref) native
function Paralyze(ObjectReference ref) native
function Deanimate(ObjectReference ref) native
function Follow(ObjectReference ref) native
function Unfollow(ObjectReference ref) native
function Stylize_Default(ObjectReference ref) native
function Stylize_Warrior(ObjectReference ref) native
function Stylize_Mage(ObjectReference ref) native
function Stylize_Archer(ObjectReference ref) native
function Stylize_Coward(ObjectReference ref) native
function Vitality_Mortal(ObjectReference ref) native
function Vitality_Protected(ObjectReference ref) native
function Vitality_Essential(ObjectReference ref) native
function Vitality_Invulnerable(ObjectReference ref) native
function Outfit_Member(ObjectReference ref) native
function Outfit_Immobile(ObjectReference ref) native
function Outfit_Settler(ObjectReference ref) native
function Outfit_Thrall(ObjectReference ref) native
function Outfit_Follower(ObjectReference ref) native
function Outfit_Vanilla(ObjectReference ref) native
function Outfit_Default(ObjectReference ref) native
function Outfit_Current(ObjectReference ref) native
function Style_Show(ObjectReference ref) native
function Vitality_Show(ObjectReference ref) native
function Outfit_Show(ObjectReference ref) native

function Direct_Begin(ObjectReference ref_object)
    (ref_object as Actor).SetDoingFavor(true)
endFunction
function Direct_End(ObjectReference ref_object)
    (ref_object as Actor).SetDoingFavor(false)
endFunction

; Follower
function Sneak(ObjectReference ref) native
function Unsneak(ObjectReference ref) native
function Saddle(ObjectReference ref) native
function Unsaddle(ObjectReference ref) native
function Retreat(ObjectReference ref) native
function Unretreat(ObjectReference ref) native


