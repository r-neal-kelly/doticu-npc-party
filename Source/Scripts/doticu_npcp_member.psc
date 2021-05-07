; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_member extends ReferenceAlias

; this shall have no state.

; Mannequins_t
ObjectReference         p_marker_mannequin                  =  none

; Displays_t
ObjectReference         p_marker_display                    =  none
ObjectReference         p_marker_undisplay                  =  none
bool                    p_is_display                        = false; delete? Displays_t will have its own list.

; to be deleted
bool                    p_prev_faction_no_body_cleanup      = false

; we'll try to remove these as much as possible and just use the clock.
;event OnDeath(Actor killer) native
;event OnActivate(ObjectReference activator) native
;event OnCombatStateChanged(Actor target, int combat_code) native
;event OnHit(ObjectReference attacker, Form tool, Projectile projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked) native
;event OnItemAdded(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_source) native
;event OnItemRemoved(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_destination) native
