;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_outfit extends ObjectReference

; Private Variables
int             p_code_create   =     0; doticu_npcp_codes.OUTFIT2_...
ObjectReference p_cache_base    =  none

; Friend Methods
function f_Destroy()
    doticu_npcp.Object_Ref_Categorize(self)

    if p_cache_base
        p_cache_base.Disable()
        p_cache_base.Delete()
    endIf
endFunction

; Private Methods
function p_Open()
    self.Activate(doticu_npcp_consts.Player_Actor())
    doticu_npcp.Funcs().Wait_Out_Of_Menu(0.1)
endFunction
