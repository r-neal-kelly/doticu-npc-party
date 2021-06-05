; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm extends SKI_ConfigBase

event OnConfigOpen() native
event OnConfigClose() native
event OnPageReset(string page) native
event OnOptionSelect(int option) native
event OnOptionMenuOpen(int option) native
event OnOptionMenuAccept(int option, int index) native
event OnOptionSliderOpen(int option) native
event OnOptionSliderAccept(int option, float value) native
event OnOptionInputAccept(int option, string value) native
event OnOptionKeymapChange(int option, int key, string conflict, string mod) native
event OnOptionDefault(int option) native
event OnOptionHighlight(int option) native
