; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_party_member extends ReferenceAlias

; this shall have no state.

; Mannequins_t
ObjectReference         p_marker_mannequin                  =  none

; Displays_t
ObjectReference         p_marker_display                    =  none
ObjectReference         p_marker_undisplay                  =  none
bool                    p_is_display                        = false; delete? Displays_t will have its own list.

; to be deleted
bool                    p_prev_faction_no_body_cleanup      = false; still need to add this to Add_Member
