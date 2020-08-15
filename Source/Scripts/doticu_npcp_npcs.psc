;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_npcs extends Quest

; Modules
doticu_npcp_vectors property VECTORS hidden
    doticu_npcp_vectors function Get()
        return doticu_npcp.Funcs().VECTORS
    endFunction
endProperty

; Private Variable
bool                    p_is_created        = false

doticu_npcp_vector_form p_vec_bases         =  none; the real base of a npc, our key
doticu_npcp_vector_form p_vec_vec_origs     =  none; vecs of original members
doticu_npcp_vector_form p_vec_vec_clones    =  none; vecs of cloned npcs, members or not
doticu_npcp_vector_form p_vec_outfits_def   =  none; default vanilla outfits

; Native Methods
function Remove_Original(Actor original) native
function Remove_Clone(Actor clone) native

; Friend Methods
function f_Create(int init_max = 8)
    p_is_created = true
    p_vec_bases = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_vec_origs = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_vec_clones = VECTORS.Create_Form_Vector(init_max, none, 1.5)
    p_vec_outfits_def = VECTORS.Create_Form_Vector(init_max, none, 1.5)
endFunction

function f_Destroy()
    VECTORS.Destroy_Form_Vector(p_vec_outfits_def)
    ; need to destroy each vector in vectors of vectors
    VECTORS.Destroy_Form_Vector(p_vec_bases)

    p_vec_outfits_def = none
    p_vec_vec_clones = none
    p_vec_vec_origs = none
    p_vec_bases = none
    p_is_created = false
endFunction
