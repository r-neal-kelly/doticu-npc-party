;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_vector_form extends ObjectReference

; Private Variables
Form[]              p_arr_forms             =  none
int                 p_num_forms             =     0
Form                p_item_fill             =  none
float               p_grow_rate             =   0.0

; Friend Methods
function f_Create(int init_max = 0, Form item_fill = none, float grow_rate = 1.5)
    if grow_rate < 1.0
        ; will only grow by 1 idx at a time
        grow_rate = 1.0
    endIf

    p_arr_forms = Utility.CreateFormArray(init_max, item_fill)
    p_num_forms = 0
    p_item_fill = item_fill
    p_grow_rate = grow_rate
endFunction

function f_Destroy()
    p_grow_rate = 0.0
    p_item_fill = none
    p_num_forms = 0
    p_arr_forms = Utility.CreateFormArray(1, none); p_arr_forms = none throws!
endFunction
