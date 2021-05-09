; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_party_members extends Quest

int                 limit                           = 0

int                 fill_suit_aura_probability      = 0
int                 fill_suit_body_probability      = 0
int                 fill_suit_feet_probability      = 0
int                 fill_suit_finger_probability    = 0
int                 fill_suit_forearm_probability   = 0
int                 fill_suit_forehead_probability  = 0
int                 fill_suit_hands_probability     = 0
int                 fill_suit_head_probability      = 0
int                 fill_suit_neck_probability      = 0

bool                do_change_suits_automatically   = false
bool                do_fill_suits_automatically     = false
bool                do_fill_suits_strictly          = false
bool                do_unfill_suits_to_pack         = false

bool                has_untouchable_invulnerables   = false

string              default_combat_style            = ""
string              default_relation                = ""
string              default_suit_type               = ""
string              default_vitality                = ""

string              member_suit_fill_type           = ""
string              sort_type                       = ""

Actor[]             actors                          = none
ActorBase[]         original_bases                  = none

bool[]              flags_is_banished               = none
bool[]              flags_is_clone                  = none
bool[]              flags_is_immobile               = none
bool[]              flags_is_mannequin              = none
bool[]              flags_is_reanimated             = none
bool[]              flags_is_sneak                  = none
bool[]              flags_is_thrall                 = none

bool[]              flags_has_suit_archer           = none
bool[]              flags_has_suit_civilized        = none
bool[]              flags_has_suit_combatant        = none
bool[]              flags_has_suit_coward           = none
bool[]              flags_has_suit_dangerous        = none
bool[]              flags_has_suit_eater            = none
bool[]              flags_has_suit_exterior         = none
bool[]              flags_has_suit_follower         = none
bool[]              flags_has_suit_guard            = none
bool[]              flags_has_suit_home             = none
bool[]              flags_has_suit_immobile         = none
bool[]              flags_has_suit_inn              = none
bool[]              flags_has_suit_interior         = none
bool[]              flags_has_suit_mage             = none
bool[]              flags_has_suit_mannequin        = none
bool[]              flags_has_suit_member           = none
bool[]              flags_has_suit_sandboxer        = none
bool[]              flags_has_suit_settlement       = none
bool[]              flags_has_suit_sitter           = none
bool[]              flags_has_suit_sleeper          = none
bool[]              flags_has_suit_thrall           = none
bool[]              flags_has_suit_warrior          = none

bool[]              flags_only_playables_archer     = none
bool[]              flags_only_playables_civilized  = none
bool[]              flags_only_playables_combatant  = none
bool[]              flags_only_playables_coward     = none
bool[]              flags_only_playables_dangerous  = none
bool[]              flags_only_playables_eater      = none
bool[]              flags_only_playables_exterior   = none
bool[]              flags_only_playables_follower   = none
bool[]              flags_only_playables_guard      = none
bool[]              flags_only_playables_home       = none
bool[]              flags_only_playables_immobile   = none
bool[]              flags_only_playables_inn        = none
bool[]              flags_only_playables_interior   = none
bool[]              flags_only_playables_mage       = none
bool[]              flags_only_playables_mannequin  = none
bool[]              flags_only_playables_member     = none
bool[]              flags_only_playables_sandboxer  = none
bool[]              flags_only_playables_settlement = none
bool[]              flags_only_playables_sitter     = none
bool[]              flags_only_playables_sleeper    = none
bool[]              flags_only_playables_thrall     = none
bool[]              flags_only_playables_warrior    = none

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
