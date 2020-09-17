; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm_filter extends Quest

int                 p_code_view                 =       0

int                 p_option_filter             =      -1

int                 p_option_sex                =      -1
string              p_str_arg_sex               =      ""
string              p_str_view_sex              = " Any "

int                 p_option_race               =      -1
string              p_str_arg_race              =      ""
string              p_str_view_race             = " Any "

int                 p_option_search             =      -1
string              p_str_arg_search            =      ""

int                 p_option_style              =      -1
int                 p_int_arg_style             =       0
string              p_str_view_style            = " Any "

int                 p_option_vitality           =      -1
int                 p_int_arg_vitality          =       0
string              p_str_view_vitality         = " Any "

int                 p_option_outfit2            =      -1
int                 p_int_arg_outfit2           =       0
string              p_str_view_outfit2          = " Any "

int                 p_option_rating             =      -1
int                 p_int_arg_rating            =      -1
string              p_str_view_rating           = " Any "

int                 p_option_relationship       =      -1
int                 p_int_arg_relationship      =      -1
string              p_str_view_relationship     = " Any "

int                 p_option_is_alive           =      -1
int                 p_option_is_dead            =      -1
int                 p_int_alive_dead            =       0

int                 p_option_is_original        =      -1
int                 p_option_is_clone           =      -1
int                 p_int_original_clone        =       0

int                 p_option_is_unique          =      -1
int                 p_option_is_generic         =      -1
int                 p_int_unique_generic        =       0

int                 p_option_is_mobile          =      -1
int                 p_option_is_immobile        =      -1
int                 p_int_mobile_immobile       =       0

int                 p_option_is_settler         =      -1
int                 p_option_isnt_settler       =      -1
int                 p_int_settler               =       0

int                 p_option_is_thrall          =      -1
int                 p_option_isnt_thrall        =      -1
int                 p_int_thrall                =       0

int                 p_option_is_paralyzed       =      -1
int                 p_option_isnt_paralyzed     =      -1
int                 p_int_paralyzed             =       0

int                 p_option_is_mannequin       =      -1
int                 p_option_isnt_mannequin     =      -1
int                 p_int_mannequin             =       0

int                 p_option_is_reanimated      =      -1
int                 p_option_isnt_reanimated    =      -1
int                 p_int_reanimated            =       0

int                 p_option_is_follower        =      -1
int                 p_option_isnt_follower      =      -1
int                 p_int_follower              =       0

int                 p_option_is_sneak           =      -1
int                 p_option_isnt_sneak         =      -1
int                 p_int_sneak                 =       0

int                 p_option_is_saddler         =      -1
int                 p_option_isnt_saddler       =      -1
int                 p_int_saddler               =       0

function On_Build_Page() native
function On_Option_Select(int option) native
function On_Option_Menu_Open(int option) native
function On_Option_Menu_Accept(int option, int idx) native
function On_Option_Slider_Open(int option) native
function On_Option_Slider_Accept(int option, float value) native
function On_Option_Input_Accept(int option, string value) native
function On_Option_Keymap_Change(int option, int key_code, string conflict, string conflicting_mod) native
function On_Option_Default(int option) native
function On_Option_Highlight(int option) native
