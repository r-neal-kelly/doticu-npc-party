; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_vars extends Quest

int                 p_version_major                 = -1
int                 p_version_minor                 = -1
int                 p_version_patch                 = -1

int                 p_max_members                   = -1
int                 p_num_display                   = -1
string              p_auto_style                    = ""
string              p_auto_vitality                 = ""
string              p_str_sort_members              = ""

bool                p_auto_resurrect                = false
bool                p_auto_sojourn                  = false
String              p_str_sort_followers            = ""

bool                p_auto_outfit                   = false
bool                p_auto_immobile_outfit          = false
bool                p_fill_outfits                  = false
string              p_clone_outfit                  = ""

int     property    key_g_dialogue_menu             = -1    auto hidden

int     property    key_n_toggle_member             = -1    auto hidden
int     property    key_n_toggle_move               = -1    auto hidden
int     property    key_n_move_nearer               = -1    auto hidden
int     property    key_n_move_farther              = -1    auto hidden
int     property    key_n_move_rotate_left          = -1    auto hidden
int     property    key_n_move_rotate_right         = -1    auto hidden
int     property    key_n_has_base                  = -1    auto hidden
int     property    key_n_count_base                = -1    auto hidden
int     property    key_n_has_head                  = -1    auto hidden
int     property    key_n_count_heads               = -1    auto hidden

int     property    key_m_toggle_clone              = -1    auto hidden
int     property    key_m_toggle_settler            = -1    auto hidden
int     property    key_m_toggle_thrall             = -1    auto hidden
int     property    key_m_toggle_immobile           = -1    auto hidden
int     property    key_m_toggle_paralyzed          = -1    auto hidden
int     property    key_m_toggle_follower           = -1    auto hidden

int     property    key_f_toggle_sneak              = -1    auto hidden
int     property    key_f_toggle_saddler            = -1    auto hidden

int     property    key_ms_toggle_display           = -1    auto hidden
int     property    key_ms_display_previous         = -1    auto hidden
int     property    key_ms_display_next             = -1    auto hidden

int     property    key_fs_summon_all               = -1    auto hidden
int     property    key_fs_summon_mobile            = -1    auto hidden
int     property    key_fs_summon_immobile          = -1    auto hidden
int     property    key_fs_settle                   = -1    auto hidden
int     property    key_fs_unsettle                 = -1    auto hidden
int     property    key_fs_mobilize                 = -1    auto hidden
int     property    key_fs_immobilize               = -1    auto hidden
int     property    key_fs_sneak                    = -1    auto hidden
int     property    key_fs_unsneak                  = -1    auto hidden
int     property    key_fs_saddle                   = -1    auto hidden
int     property    key_fs_unsaddle                 = -1    auto hidden
int     property    key_fs_resurrect                = -1    auto hidden

int[]   property    key_g_dialogue_menu_mods        = none  auto hidden

int[]   property    key_n_toggle_member_mods        = none  auto hidden
int[]   property    key_n_toggle_move_mods          = none  auto hidden
int[]   property    key_n_move_nearer_mods          = none  auto hidden
int[]   property    key_n_move_farther_mods         = none  auto hidden
int[]   property    key_n_move_rotate_left_mods     = none  auto hidden
int[]   property    key_n_move_rotate_right_mods    = none  auto hidden
int[]   property    key_n_has_base_mods             = none  auto hidden
int[]   property    key_n_count_base_mods           = none  auto hidden
int[]   property    key_n_has_head_mods             = none  auto hidden
int[]   property    key_n_count_heads_mods          = none  auto hidden

int[]   property    key_m_toggle_clone_mods         = none  auto hidden
int[]   property    key_m_toggle_settler_mods       = none  auto hidden
int[]   property    key_m_toggle_thrall_mods        = none  auto hidden
int[]   property    key_m_toggle_immobile_mods      = none  auto hidden
int[]   property    key_m_toggle_paralyzed_mods     = none  auto hidden
int[]   property    key_m_toggle_follower_mods      = none  auto hidden

int[]   property    key_f_toggle_sneak_mods         = none  auto hidden
int[]   property    key_f_toggle_saddler_mods       = none  auto hidden

int[]   property    key_ms_toggle_display_mods      = none  auto hidden
int[]   property    key_ms_display_previous_mods    = none  auto hidden
int[]   property    key_ms_display_next_mods        = none  auto hidden

int[]   property    key_fs_summon_all_mods          = none  auto hidden
int[]   property    key_fs_summon_mobile_mods       = none  auto hidden
int[]   property    key_fs_summon_immobile_mods     = none  auto hidden
int[]   property    key_fs_settle_mods              = none  auto hidden
int[]   property    key_fs_unsettle_mods            = none  auto hidden
int[]   property    key_fs_mobilize_mods            = none  auto hidden
int[]   property    key_fs_immobilize_mods          = none  auto hidden
int[]   property    key_fs_sneak_mods               = none  auto hidden
int[]   property    key_fs_unsneak_mods             = none  auto hidden
int[]   property    key_fs_saddle_mods              = none  auto hidden
int[]   property    key_fs_unsaddle_mods            = none  auto hidden
int[]   property    key_fs_resurrect_mods           = none  auto hidden
