; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_members extends Quest

Actor[]             actors              = none
ActorBase[]         original_bases      = none

bool[]              is_banished_flags   = none
bool[]              is_clone_flags      = none
bool[]              is_immobile_flags   = none
bool[]              is_mannequin_flags  = none
bool[]              is_paralyzed_flags  = none
bool[]              is_reanimated_flags = none
bool[]              is_thrall_flags     = none

string[]            names               = none
ObjectReference[]   packs               = none
VoiceType[]         voice_types         = none

Outfit[]            default_outfits     = none
Outfit[]            vanilla_outfits     = none

ObjectReference[]   backup_suits        = none
ObjectReference[]   current_suits       = none
ObjectReference[]   default_suits       = none
ObjectReference[]   follower_suits      = none
ObjectReference[]   immobile_suits      = none
ObjectReference[]   member_suits        = none
ObjectReference[]   settler_suits       = none
ObjectReference[]   thrall_suits        = none
ObjectReference[]   vanilla_suits       = none

int[]               ratings             = none
int[]               relations           = none
string[]            styles              = none
string[]            vitalities          = none

; this stuff should be moved to Displays_t
bool                p_has_display       = false
int                 p_idx_display       =     0
ObjectReference     p_marker_display    =  none
