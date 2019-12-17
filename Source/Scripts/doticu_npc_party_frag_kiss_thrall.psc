;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname doticu_npc_party_frag_kiss_thrall Extends Perk Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akTargetRef, Actor akActor)
;BEGIN CODE
DATA.MODS.CONTROL.PLAYER.Kiss_Thrall(akTargetRef as Actor)
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

; Private Constants
doticu_npc_party_script_data p_DATA = none

; Public Constants
doticu_npc_party_script_data property DATA
    doticu_npc_party_script_data function Get()
        return p_DATA
    endFunction
    function Set(doticu_npc_party_script_data val)
        if p_DATA == none
            p_DATA = val
        endIf
    endFunction
endProperty
