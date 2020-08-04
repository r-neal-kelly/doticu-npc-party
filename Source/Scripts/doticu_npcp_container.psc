;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_container extends ObjectReference

; sadly, we cannot delete this until we force a new game, because the engine deletes all member packs upon removal
; the alternative is to transfer each item in each pack to a newly create ObjectReference instance, and delete
; the this and the old instances in a subsequent update.
