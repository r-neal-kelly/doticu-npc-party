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

bool[]              has_civilized_suit_flags        = none
bool[]              has_combatant_suit_flags        = none
bool[]              has_dangerous_suit_flags        = none
bool[]              has_eater_suit_flags            = none
bool[]              has_exterior_suit_flags         = none
bool[]              has_follower_suit_flags         = none
bool[]              has_guard_suit_flags            = none
bool[]              has_home_suit_flags             = none
bool[]              has_immobile_suit_flags         = none
bool[]              has_inn_suit_flags              = none
bool[]              has_interior_suit_flags         = none
bool[]              has_mannequin_suit_flags        = none
bool[]              has_member_suit_flags           = none
bool[]              has_sandboxer_suit_flags        = none
bool[]              has_settlement_suit_flags       = none
bool[]              has_sitter_suit_flags           = none
bool[]              has_sleeper_suit_flags          = none
bool[]              has_thrall_suit_flags           = none

string[]            names                           = none

ObjectReference[]   caches                          = none
CombatStyle[]       combat_styles                   = none
Spell[]             ghost_abilities                 = none
Outfit[]            outfits                         = none
ObjectReference[]   packs                           = none
ObjectReference[]   suitcases                       = none
VoiceType[]         voice_types                     = none

float[]             alphas                          = none
int[]               ratings                         = none
string[]            relations                       = none
string[]            suit_types                      = none
string[]            vitalities                      = none
