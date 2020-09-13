; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_member extends ReferenceAlias

; Private Variables
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
bool                    p_is_settler                        = false
bool                    p_is_thrall                         = false
bool                    p_is_paralyzed                      = false
bool                    p_is_mannequin                      = false
bool                    p_is_display                        = false
bool                    p_is_reanimated                     = false
bool                    p_do_skip_on_load                   = false

int                     p_code_style                        =     0
int                     p_code_vitality                     =     0
int                     p_code_outfit2                      =     0
int                     p_int_rating                        =     0

string                  p_str_name                          =    ""

Faction                 p_prev_faction_crime                =  none
bool                    p_prev_faction_potential_follower   = false
bool                    p_prev_faction_no_body_cleanup      = false
float                   p_prev_aggression                   =   0.0
float                   p_prev_confidence                   =   0.0
float                   p_prev_assistance                   =   0.0
float                   p_prev_morality                     =   0.0

Faction[]               p_prev_factions                     =  none; to be deleted in a future update

; Native Methods
Actor function Actor() native
Alias function Follower() native
int function Style() native
int function Vitality() native
int function Rating() native
string function Name() native
string function Rating_Stars() native

bool function Is_Filled() native
bool function Is_Mannequin() native
bool function Isnt_Mannequin() native
bool function Is_Follower() native

int function Mannequinize(ObjectReference marker) native
int function Unmannequinize() native

int function Rate(int rating) native
int function Rename(string name) native

int function Stash() native

event OnLoad() native
event OnDeath(Actor killer) native
event OnActivate(ObjectReference activator) native
event OnCombatStateChanged(Actor target, int combat_code) native
event OnHit(ObjectReference attacker, Form tool, Projectile projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked) native
event OnItemAdded(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_source) native
event OnItemRemoved(Form item_form, int item_count, ObjectReference item_ref, ObjectReference item_destination) native
