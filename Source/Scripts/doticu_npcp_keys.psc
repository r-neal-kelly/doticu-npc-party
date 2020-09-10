; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_keys extends Quest

string p_pressed_hotkey = ""

function Register() native
function Unregister() native
int function Default_Value(string key) native
int function Current_Value(string key) native
int[] function Default_Mods(string key) native
int[] function Current_Mods(string key) native
function Change_Current_Mods(string key, int mod_1, int mod_2, int mod_3) native
string function Default_Mods_To_String(string key) native
string function Current_Mods_To_String(string key) native
string function Conflicting_Hotkey(string key, int value, int mod_1, int mod_2, int mod_3) native
string function Pressed_Hotkey(int value) native
event OnKeyDown(int key_code) native
event OnKeyUp(int key_code, float time_held) native
