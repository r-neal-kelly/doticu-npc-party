; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_commands extends Quest

; NPC
function Unmember(Actor ref_actor) native
function Clone(Actor ref_actor) native
function Unclone(Actor ref_actor) native
function Toggle_Move(Actor ref_actor) native

; Member
function Summon(Actor ref_actor) native
function Goto(Actor ref_actor) native
function Open_Pack(Actor ref_actor) native
function Resurrect(Actor ref_actor) native
function Mobilize(Actor ref_actor) native
function Immobilize(Actor ref_actor) native
function Settle(Actor ref_actor) native
function Resettle(Actor ref_actor) native
function Unsettle(Actor ref_actor) native
function Paralyze(Actor ref_actor) native
function Unparalyze(Actor ref_actor) native
function Follow(Actor ref_actor) native
function Unfollow(Actor ref_actor) native
function Stylize_Default(Actor ref_actor) native
function Stylize_Warrior(Actor ref_actor) native
function Stylize_Mage(Actor ref_actor) native
function Stylize_Archer(Actor ref_actor) native
function Stylize_Coward(Actor ref_actor) native
function Vitalize_Mortal(Actor ref_actor) native
function Vitalize_Protected(Actor ref_actor) native
function Vitalize_Essential(Actor ref_actor) native
function Vitalize_Invulnerable(Actor ref_actor) native
function Change_Member_Outfit2(Actor ref_actor) native
function Change_Immobile_Outfit2(Actor ref_actor) native
function Change_Settler_Outfit2(Actor ref_actor) native
function Change_Thrall_Outfit2(Actor ref_actor) native
function Change_Follower_Outfit2(Actor ref_actor) native
function Change_Vanilla_Outfit2(Actor ref_actor) native
function Change_Default_Outfit2(Actor ref_actor) native
function Change_Current_Outfit2(Actor ref_actor) native
function Toggle_Expoee(int expoee_id, ObjectReference marker) native
function Toggle_Reanimated(Actor ref_actor) native

; Follower
function Sneak(Actor ref_actor) native
function Unsneak(Actor ref_actor) native

; Followers
function Followers_Summon_All() native
function Followers_Summon_Mobile() native
function Followers_Summon_Immobile() native
function Followers_Stash() native
function Followers_Mobilize() native
function Followers_Immobilize() native
function Followers_Settle() native
function Followers_Unsettle() native
function Followers_Sneak() native
function Followers_Unsneak() native
function Followers_Saddle() native
function Followers_Unsaddle() native
function Followers_Unfollow() native
function Followers_Unmember() native
