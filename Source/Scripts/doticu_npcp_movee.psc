; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_movee extends ReferenceAlias

Actor       p_ref_actor             =  none

bool        p_is_created            = false
bool        p_is_locked             = false
bool        p_is_airborne           = false
bool        p_do_distance_farther   = false
bool        p_do_distance_nearer    = false
bool        p_do_rotate_right       = false
bool        p_do_rotate_left        = false

float       p_distance              =   0.0
float       p_rotation              =   0.0

function Register() native
function Unregister() native
event OnKeyDown(int key_code) native
event OnKeyUp(int key_code, float time_held) native
