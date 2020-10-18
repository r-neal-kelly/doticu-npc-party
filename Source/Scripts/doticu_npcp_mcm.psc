; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm extends SKI_ConfigBase

string p_current_page = ""

event OnConfigOpen()
    ModName = " NPC Party "
    
    Pages = Utility.CreateStringArray(9, "")
    Pages[0] = " Followers "
    Pages[1] = " Members "
    Pages[2] = " Settlers "
    Pages[3] = " Mannequins "
    Pages[4] = " Filter "
    Pages[5] = " Chests "
    Pages[6] = " Settings "
    Pages[7] = " Hotkeys "
    Pages[8] = " Logs "
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
