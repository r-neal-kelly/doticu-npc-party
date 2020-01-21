;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_vector_form extends ObjectReference

; Private Constants
doticu_npcp_data    p_DATA                  =  none

; Public Variables
int property num hidden
    int function Get()
        return p_num_forms
    endFunction
endProperty
int property max hidden
    int function Get()
        return p_max_forms
    endFunction
endProperty

; Private Variables
bool                p_is_created            = false
Form[]              p_arr_forms             =  none
int                 p_num_forms             =     0
int                 p_max_forms             =     0
Form                p_item_fill             =  none
float               p_grow_rate             =   0.0

; Friend Methods
function f_Create(doticu_npcp_data DATA, int init_size = 0, Form item_fill = none, float grow_rate = 1.5)
    p_DATA = DATA

    if grow_rate < 1.0
        ; will only grow by 1 idx at a time
        grow_rate = 1.0
    endIf

    p_is_created = true
    p_arr_forms = Utility.CreateFormArray(init_size, item_fill)
    p_num_forms = 0
    p_max_forms = init_size
    p_item_fill = item_fill
    p_grow_rate = grow_rate
endFunction

function f_Destroy()
    p_grow_rate = 0.0
    p_item_fill = none
    p_max_forms = 0
    p_num_forms = 0
    ;p_arr_forms = none; throws!
    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
function p_Grow()
    int max_forms = Math.Ceiling(p_max_forms * p_grow_rate)
    if max_forms <= p_max_forms
        max_forms = p_max_forms + 1
    endIf
    p_max_forms = max_forms

    p_arr_forms = Utility.ResizeFormArray(p_arr_forms, p_max_forms, p_item_fill)
endFunction

; Public Methods
Form[] function Get_Array()
    return PapyrusUtil.SliceFormArray(p_arr_forms, 0, p_num_forms - 1)
endFunction

function Push(Form item)
    if p_num_forms >= p_max_forms
        p_Grow()
    endIf
    p_arr_forms[p_num_forms] = item
    p_num_forms += 1
endFunction

Form function Pop()
    if p_num_forms > 0
        p_num_forms -= 1
        return p_arr_forms[p_num_forms]
    else
        return none
    endIf
endFunction

function Remove_At_Unstable(int idx)
    if idx > -1 && idx < p_num_forms
        p_num_forms -= 1
        p_arr_forms[idx] = p_arr_forms[p_num_forms]
    else
        return none
    endIf
endFunction

Form function At(int idx)
    if idx > -1 && idx < p_num_forms
        return p_arr_forms[idx]
    else
        return none
    endIf
endFunction

Form function Set(int idx, Form item)
    if idx > -1 && idx < p_num_forms
        Form item_old = p_arr_forms[idx]
        p_arr_forms[idx] = item
        return item_old
    else
        return none
    endIf
endFunction

Form function Unset(int idx)
    if idx > -1 && idx < p_num_forms
        Form item_old = p_arr_forms[idx]
        p_arr_forms[idx] = p_item_fill
        return item_old
    else
        return none
    endIf
endFunction

bool function Has(Form item)
    return p_arr_forms.Find(item, 0) > -1
endFunction

int function Find(Form item)
    return p_arr_forms.Find(item, 0)
endFunction

function Fit()
    p_arr_forms = Get_Array()
    p_max_forms = p_num_forms
endFunction
