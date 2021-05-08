; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_party_follower extends ReferenceAlias

event OnHit(ObjectReference attacker, Form tool, Projectile projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked)
    Debug.Trace("FOLLOWER")
endEvent
