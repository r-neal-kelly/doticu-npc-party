;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_package_menu extends Package hidden

; Public Methods
function Exit_Begin(Actor ref_actor)
    doticu_npcp.Funcs().ACTORS.Destroy_Menu()
endFunction
