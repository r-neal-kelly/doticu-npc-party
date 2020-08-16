;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_npcs extends Quest

; Private Variable
doticu_npcp_vector_form p_vec_bases         =  none; the real base of a npc, our key
doticu_npcp_vector_form p_vec_vec_origs     =  none; vecs of original members
doticu_npcp_vector_form p_vec_vec_clones    =  none; vecs of cloned npcs, members or not
doticu_npcp_vector_form p_vec_outfits_def   =  none; default vanilla outfits

; Native Methods
function f_Initialize() native
function f_Uninitialize() native

function Remove_Original(Actor original) native
function Remove_Clone(Actor clone) native
