; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_member extends ReferenceAlias

Actor                   p_ref_actor                         =  none
ObjectReference         p_container_pack                    =  none
ObjectReference         p_marker_mannequin                  =  none
ObjectReference         p_marker_display                    =  none
ObjectReference         p_marker_undisplay                  =  none
Outfit                  p_outfit_vanilla                    =  none
Outfit                  p_outfit_default                    =  none
doticu_npcp_outfit      p_outfit2_member                    =  none
doticu_npcp_outfit      p_outfit2_immobile                  =  none
doticu_npcp_outfit      p_outfit2_settler                   =  none
doticu_npcp_outfit      p_outfit2_thrall                    =  none
doticu_npcp_outfit      p_outfit2_follower                  =  none
doticu_npcp_outfit      p_outfit2_vanilla                   =  none
doticu_npcp_outfit      p_outfit2_default                   =  none
doticu_npcp_outfit      p_outfit2_current                   =  none
doticu_npcp_outfit      p_outfit2_auto_backup               =  none

bool                    p_is_locked                         = false
bool                    p_is_clone                          = false
bool                    p_is_immobile                       = false
bool                    p_is_thrall                         = false
bool                    p_is_paralyzed                      = false
bool                    p_is_mannequin                      = false
bool                    p_is_display                        = false
bool                    p_is_reanimated                     = false

int                     p_code_style                        =     0
int                     p_code_vitality                     =     0
int                     p_code_outfit2                      =     0
int                     p_int_rating                        =     0

string                  p_str_name                          =    ""

Faction                 p_prev_faction_crime                =  none
bool                    p_prev_faction_no_body_cleanup      = false

float                   p_prev_aggression                   =   0.0; these four may be unneeded
float                   p_prev_confidence                   =   0.0
float                   p_prev_assistance                   =   0.0
float                   p_prev_morality                     =   0.0

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

bool                    p_prev_faction_potential_follower   = false; to be deleted
Faction[]               p_prev_factions                     =  none; to be deleted
bool                    p_is_settler                        = false; to be deleted

event OnDeath(Actor killer) native
event OnActivate(ObjectReference activator) native
event OnCombatStateChanged(Actor target, int combat_code) native
event OnHit(ObjectReference attacker, Form tool, Projectile projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked) native
event OnItemAdded(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_source) native
event OnItemRemoved(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_destination) native
