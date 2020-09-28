; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm extends SKI_ConfigBase

string p_current_page = ""

event OnConfigOpen()
    ModName = " NPC Party "
    
    Pages = Utility.CreateStringArray(8, "")
    Pages[0] = " Followers "
    Pages[1] = " Members "
    Pages[2] = " Mannequins "
    Pages[3] = " Filter "
    Pages[4] = " Chests "
    Pages[5] = " Settings "
    Pages[6] = " Hotkeys "
    Pages[7] = " Logs "
endEvent

event OnPageReset(String current_page) native
event OnOptionSelect(int option) native
event OnOptionMenuOpen(int option) native
event OnOptionMenuAccept(int option, int idx) native
event OnOptionSliderOpen(int option) native
event OnOptionSliderAccept(int option, float value) native
event OnOptionInputAccept(int option, string value) native
event OnOptionKeymapChange(int option, int key_code, string conflict, string conflicting_mod) native
event OnOptionDefault(int option) native
event OnOptionHighlight(int option) native
