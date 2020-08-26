; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm_chests extends Quest

int         p_option_input          =    -1

int         p_option_swords         =    -1
int         p_option_greatswords    =    -1
int         p_option_waraxes        =    -1
int         p_option_battleaxes     =    -1
int         p_option_maces          =    -1
int         p_option_warhammers     =    -1
int         p_option_daggers        =    -1
int         p_option_staves         =    -1
int         p_option_bows           =    -1
int         p_option_ammo           =    -1
int         p_option_weapons        =    -1

int         p_option_light_armor    =    -1
int         p_option_heavy_armor    =    -1
int         p_option_shields        =    -1
int         p_option_jewelry        =    -1
int         p_option_clothes        =    -1

int         p_option_potions        =    -1
int         p_option_poisons        =    -1
int         p_option_ingredients    =    -1
int         p_option_food           =    -1

int         p_option_soulgems       =    -1
int         p_option_scrolls        =    -1
int         p_option_metals         =    -1
int         p_option_leather        =    -1
int         p_option_gems           =    -1
int         p_option_clutter        =    -1
int         p_option_keys           =    -1
int         p_option_misc           =    -1

int         p_option_spell_tomes    =    -1
int         p_option_recipes        =    -1
int         p_option_books_a        =    -1
int         p_option_books_b        =    -1
int         p_option_books_c        =    -1
int         p_option_books_d        =    -1
int         p_option_books_e        =    -1
int         p_option_books_f        =    -1
int         p_option_books_g        =    -1
int         p_option_books_h        =    -1
int         p_option_books_i        =    -1
int         p_option_books_j        =    -1
int         p_option_books_k        =    -1
int         p_option_books_l        =    -1
int         p_option_books_m        =    -1
int         p_option_books_n        =    -1
int         p_option_books_o        =    -1
int         p_option_books_p        =    -1
int         p_option_books_q        =    -1
int         p_option_books_r        =    -1
int         p_option_books_s        =    -1
int         p_option_books_t        =    -1
int         p_option_books_u        =    -1
int         p_option_books_v        =    -1
int         p_option_books_w        =    -1
int         p_option_books_x        =    -1
int         p_option_books_y        =    -1
int         p_option_books_z        =    -1
int         p_option_books          =    -1

function f_Build_Page() native

function f_On_Option_Select         (int option) native
function f_On_Option_Menu_Open      (int option) native
function f_On_Option_Menu_Accept    (int option, int idx) native
function f_On_Option_Slider_Open    (int option) native
function f_On_Option_Slider_Accept  (int option, float value) native
function f_On_Option_Input_Accept   (int option, string value) native
function f_On_Option_Keymap_Change  (int option, int key_code, string conflict, string conflicting_mod) native
function f_On_Option_Default        (int option) native
function f_On_Option_Highlight      (int option) native
