;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_containers extends Quest

; Public Methods
function Open(ObjectReference ref_container)
    ref_container.Activate(doticu_npcp_consts.Player_Actor())
    doticu_npcp.Funcs().Wait(0.1)
endFunction

string function Name(ObjectReference ref_container)
    return ref_container.GetDisplayName()
endFunction

function Rename(ObjectReference ref_container, string str_name)
    ref_container.SetDisplayName(str_name, true)
endFunction
