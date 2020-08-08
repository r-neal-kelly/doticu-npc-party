;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_outfit extends ObjectReference

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return doticu_npcp.Funcs().LOGS
    endFunction
endProperty

; Private Constants
int property p_MAX_ITEMS hidden
    int function Get()
        return 16; might be able to increase this, now that we have moved outfitting to c++
    endFunction
endProperty

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
    FUNCS.Wait_Out_Of_Menu(0.1)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if self.GetNumItems() >= p_MAX_ITEMS
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Can only have so many items in an outfit.")
    elseIf !form_item || p_code_create != doticu_npcp_codes.OUTFIT2_DEFAULT() && !form_item.IsPlayable()
        ; now we let unplayables into default outfit's self container
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Cannot add that item to an outfit.")
    endIf
endEvent
