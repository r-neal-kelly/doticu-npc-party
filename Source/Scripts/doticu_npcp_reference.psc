; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_reference extends ObjectReference

function On_Open(ObjectReference ref, ObjectReference ref_activator) native global
event OnOpen(ObjectReference ref_activator)
    On_Open(self as ObjectReference, ref_activator)
endEvent
