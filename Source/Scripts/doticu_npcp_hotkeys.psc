; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_hotkeys extends Quest

int     global_dialogue_menu            = -1

int     actor_toggle_member             = -1
int     actor_toggle_move               = -1
int     actor_move_nearer               = -1
int     actor_move_farther              = -1
int     actor_move_rotate_left          = -1
int     actor_move_rotate_right         = -1
int     actor_has_base                  = -1
int     actor_count_base                = -1
int     actor_has_head                  = -1
int     actor_count_heads               = -1

int     member_toggle_clone             = -1
int     member_toggle_settler           = -1
int     member_toggle_thrall            = -1
int     member_toggle_immobile          = -1
int     member_toggle_paralyzed         = -1
int     member_toggle_follower          = -1

int     follower_toggle_sneak           = -1
int     follower_toggle_saddler         = -1

int     members_toggle_display          = -1
int     members_display_previous        = -1
int     members_display_next            = -1

int     followers_summon_all            = -1
int     followers_summon_mobile         = -1
int     followers_summon_immobile       = -1
int     followers_settle                = -1
int     followers_unsettle              = -1
int     followers_mobilize              = -1
int     followers_immobilize            = -1
int     followers_sneak                 = -1
int     followers_unsneak               = -1
int     followers_saddle                = -1
int     followers_unsaddle              = -1
int     followers_resurrect             = -1

int[]   global_dialogue_menu_mods       = none

int[]   actor_toggle_member_mods        = none
int[]   actor_toggle_move_mods          = none
int[]   actor_move_nearer_mods          = none
int[]   actor_move_farther_mods         = none
int[]   actor_move_rotate_left_mods     = none
int[]   actor_move_rotate_right_mods    = none
int[]   actor_has_base_mods             = none
int[]   actor_count_base_mods           = none
int[]   actor_has_head_mods             = none
int[]   actor_count_heads_mods          = none

int[]   member_toggle_clone_mods        = none
int[]   member_toggle_settler_mods      = none
int[]   member_toggle_thrall_mods       = none
int[]   member_toggle_immobile_mods     = none
int[]   member_toggle_paralyzed_mods    = none
int[]   member_toggle_follower_mods     = none

int[]   follower_toggle_sneak_mods      = none
int[]   follower_toggle_saddler_mods    = none

int[]   members_toggle_display_mods     = none
int[]   members_display_previous_mods   = none
int[]   members_display_next_mods       = none

int[]   followers_summon_all_mods       = none
int[]   followers_summon_mobile_mods    = none
int[]   followers_summon_immobile_mods  = none
int[]   followers_settle_mods           = none
int[]   followers_unsettle_mods         = none
int[]   followers_mobilize_mods         = none
int[]   followers_immobilize_mods       = none
int[]   followers_sneak_mods            = none
int[]   followers_unsneak_mods          = none
int[]   followers_saddle_mods           = none
int[]   followers_unsaddle_mods         = none
int[]   followers_resurrect_mods        = none

event OnKeyDown(int key_code) native
event OnKeyUp(int key_code, float time_held) native
