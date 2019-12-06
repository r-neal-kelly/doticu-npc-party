Scriptname doticu_npc_party_script_consts extends Quest

; Private Constants
Actor           p_ACTOR_PLAYER                  = none
MiscObject      p_TOKEN_MEMBER                  = none
MiscObject      p_TOKEN_SETTLER                 = none
MiscObject      p_TOKEN_FOLLOWER                = none
MiscObject      p_TOKEN_FOLLOWER_SNEAK          = none
MiscObject      p_TOKEN_IMMOBILE                = none
MiscObject      p_TOKEN_CLONE                   = none
MiscObject      p_TOKEN_BANISHED                = none
MiscObject      p_TOKEN_GENERIC                 = none
GlobalVariable  p_GLOBAL_PLAYER_FOLLOWER_COUNT  = none
FormList        p_FORMLIST_MARKERS_SETTLER      = none

; Public Constants
Actor property ACTOR_PLAYER
    Actor function Get()
        return p_ACTOR_PLAYER
    endFunction
    function Set(Actor val)
        if p_ACTOR_PLAYER == none
            p_ACTOR_PLAYER = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_MEMBER
    MiscObject function Get()
        return p_TOKEN_MEMBER
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_MEMBER == none
            p_TOKEN_MEMBER = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_SETTLER
    MiscObject function Get()
        return p_TOKEN_SETTLER
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_SETTLER == none
            p_TOKEN_SETTLER = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_FOLLOWER
    MiscObject function Get()
        return p_TOKEN_FOLLOWER
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_FOLLOWER == none
            p_TOKEN_FOLLOWER = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_FOLLOWER_SNEAK
    MiscObject function Get()
        return p_TOKEN_FOLLOWER_SNEAK
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_FOLLOWER_SNEAK == none
            p_TOKEN_FOLLOWER_SNEAK = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_IMMOBILE
    MiscObject function Get()
        return p_TOKEN_IMMOBILE
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_IMMOBILE == none
            p_TOKEN_IMMOBILE = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_CLONE
    MiscObject function Get()
        return p_TOKEN_CLONE
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_CLONE == none
            p_TOKEN_CLONE = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_BANISHED
    MiscObject function Get()
        return p_TOKEN_BANISHED
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_BANISHED == none
            p_TOKEN_BANISHED = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_GENERIC
    MiscObject function Get()
        return p_TOKEN_GENERIC
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_GENERIC == none
            p_TOKEN_GENERIC = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_PLAYER_FOLLOWER_COUNT
    GlobalVariable function Get()
        return p_GLOBAL_PLAYER_FOLLOWER_COUNT
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_PLAYER_FOLLOWER_COUNT == none
            p_GLOBAL_PLAYER_FOLLOWER_COUNT = val
        endIf
    endFunction
endProperty

Formlist property FORMLIST_MARKERS_SETTLER
    Formlist function Get()
        return p_FORMLIST_MARKERS_SETTLER
    endFunction
    function Set(Formlist val)
        if p_FORMLIST_MARKERS_SETTLER == none
            p_FORMLIST_MARKERS_SETTLER = val
        endIf
    endFunction
endProperty
