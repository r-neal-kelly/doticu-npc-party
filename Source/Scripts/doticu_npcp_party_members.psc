; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_party_members extends Quest

int                 limit                           = 0

bool                do_auto_suits                   = false
bool                do_auto_immobile_suit           = false
bool                do_fill_suits                   = false

bool                has_untouchable_invulnerables   = false

string              default_combat_style            = ""
string              default_relation                = ""
string              default_suit_type               = ""
string              default_vitality                = ""

string              member_suit_fill_type           = ""
string              sort_type                       = ""

Actor[]             actors                          = none
ActorBase[]         original_bases                  = none

bool[]              is_banished_flags               = none
bool[]              is_clone_flags                  = none
bool[]              is_immobile_flags               = none
bool[]              is_mannequin_flags              = none
bool[]              is_reanimated_flags             = none
bool[]              is_thrall_flags                 = none

string[]            names                           = none

CombatStyle[]       combat_styles                   = none
Spell[]             ghost_abilities                 = none
ObjectReference[]   packs                           = none
ObjectReference[]   suitcases                       = none
VoiceType[]         voice_types                     = none

float[]             alphas                          = none
int[]               ratings                         = none
string[]            relations                       = none
string[]            suit_types                      = none
string[]            vitalities                      = none
