; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_party_members extends Quest

int                 limit                               = 0

bool                do_auto_suits                       = false
bool                do_auto_immobile_suit               = false
bool                do_fill_suits                       = false

bool                has_untouchable_invulnerables       = false

string              default_combat_style                = ""
string              default_relation                    = ""
string              default_suit_type                   = ""
string              default_vitality                    = ""

string              member_suit_fill_type               = ""
string              sort_type                           = ""

Actor[]             actors                              = none
ActorBase[]         original_bases                      = none

bool[]              flags_is_banished                   = none
bool[]              flags_is_clone                      = none
bool[]              flags_is_immobile                   = none
bool[]              flags_is_mannequin                  = none
bool[]              flags_is_reanimated                 = none
bool[]              flags_is_thrall                     = none

bool[]              flags_allow_unplayables_civilized   = none
bool[]              flags_allow_unplayables_combatant   = none
bool[]              flags_allow_unplayables_dangerous   = none
bool[]              flags_allow_unplayables_eater       = none
bool[]              flags_allow_unplayables_exterior    = none
bool[]              flags_allow_unplayables_follower    = none
bool[]              flags_allow_unplayables_guard       = none
bool[]              flags_allow_unplayables_home        = none
bool[]              flags_allow_unplayables_immobile    = none
bool[]              flags_allow_unplayables_inn         = none
bool[]              flags_allow_unplayables_interior    = none
bool[]              flags_allow_unplayables_mannequin   = none
bool[]              flags_allow_unplayables_member      = none
bool[]              flags_allow_unplayables_sandboxer   = none
bool[]              flags_allow_unplayables_settlement  = none
bool[]              flags_allow_unplayables_sitter      = none
bool[]              flags_allow_unplayables_sleeper     = none
bool[]              flags_allow_unplayables_thrall      = none

bool[]              flags_has_suit_civilized            = none
bool[]              flags_has_suit_combatant            = none
bool[]              flags_has_suit_dangerous            = none
bool[]              flags_has_suit_eater                = none
bool[]              flags_has_suit_exterior             = none
bool[]              flags_has_suit_follower             = none
bool[]              flags_has_suit_guard                = none
bool[]              flags_has_suit_home                 = none
bool[]              flags_has_suit_immobile             = none
bool[]              flags_has_suit_inn                  = none
bool[]              flags_has_suit_interior             = none
bool[]              flags_has_suit_mannequin            = none
bool[]              flags_has_suit_member               = none
bool[]              flags_has_suit_sandboxer            = none
bool[]              flags_has_suit_settlement           = none
bool[]              flags_has_suit_sitter               = none
bool[]              flags_has_suit_sleeper              = none
bool[]              flags_has_suit_thrall               = none

string[]            names                               = none

ObjectReference[]   caches                              = none
CombatStyle[]       combat_styles                       = none
Spell[]             ghost_abilities                     = none
Outfit[]            outfits                             = none
ObjectReference[]   packs                               = none
ObjectReference[]   suitcases                           = none
VoiceType[]         voice_types                         = none

float[]             alphas                              = none
int[]               ratings                             = none
string[]            relations                           = none
string[]            suit_types                          = none
string[]            vitalities                          = none
