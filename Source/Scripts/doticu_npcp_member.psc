; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_member extends ReferenceAlias

; this shall have no state.

; Mannequins_t
ObjectReference         p_marker_mannequin                  =  none

; Displays_t
ObjectReference         p_marker_display                    =  none
ObjectReference         p_marker_undisplay                  =  none
bool                    p_is_display                        = false; delete? Displays_t will have its own list.

; Settlers_t
ObjectReference         p_settler_sleeper_marker            =  none
ObjectReference         p_settler_sitter_marker             =  none
ObjectReference         p_settler_eater_marker              =  none
ObjectReference         p_settler_guard_marker              =  none

int                     p_settler_sandboxer_radius          =     0
int                     p_settler_sleeper_radius            =     0
int                     p_settler_sitter_radius             =     0
int                     p_settler_eater_radius              =     0
int                     p_settler_guard_radius              =     0

int                     p_settler_sleeper_time              =     0
int                     p_settler_sitter_time               =     0
int                     p_settler_eater_time                =     0
int                     p_settler_guard_time                =     0

int                     p_settler_sleeper_duration          =     0
int                     p_settler_sitter_duration           =     0
int                     p_settler_eater_duration            =     0
int                     p_settler_guard_duration            =     0

int                     p_settler_sandboxer_movement        =     0
int                     p_settler_sleeper_movement          =     0
int                     p_settler_sitter_movement           =     0
int                     p_settler_eater_movement            =     0
int                     p_settler_guard_movement            =     0

int                     p_settler_sandboxer_wander_distance =     0
int                     p_settler_sleeper_wander_distance   =     0
int                     p_settler_eater_wander_distance     =     0

int                     p_settler_sandboxer_flags           =     0
int                     p_settler_sleeper_flags             =     0
int                     p_settler_sitter_flags              =     0
int                     p_settler_eater_flags               =     0
int                     p_settler_guard_flags               =     0

ObjectReference         p_settler_sleeper_bed               =  none

; to be deleted
bool                    p_prev_faction_no_body_cleanup      = false

; we'll try to remove these as much as possible and just use the clock.
event OnDeath(Actor killer) native
event OnActivate(ObjectReference activator) native
event OnCombatStateChanged(Actor target, int combat_code) native
event OnHit(ObjectReference attacker, Form tool, Projectile projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked) native
event OnItemAdded(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_source) native
event OnItemRemoved(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_destination) native
