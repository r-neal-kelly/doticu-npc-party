Scriptname doticu_npc_party_script_consts extends Quest

; Private Constants
Actor           p_ACTOR_PLAYER                          = none
MiscObject      p_TOKEN_MEMBER                          = none
MiscObject      p_TOKEN_SETTLER                         = none
MiscObject      p_TOKEN_FOLLOWER                        = none
MiscObject      p_TOKEN_FOLLOWER_SNEAK                  = none
MiscObject      p_TOKEN_IMMOBILE                        = none
MiscObject      p_TOKEN_CLONE                           = none
MiscObject      p_TOKEN_BANISHED                        = none
MiscObject      p_TOKEN_GENERIC                         = none
MiscObject      p_TOKEN_THRALL                          = none
MiscObject      p_TOKEN_GREETER                         = none
MiscObject      p_TOKEN_COMBAT_DEFAULT                  = none
MiscObject      p_TOKEN_COMBAT_WARRIOR                  = none
MiscObject      p_TOKEN_COMBAT_MAGE                     = none
MiscObject      p_TOKEN_COMBAT_ARCHER                   = none
GlobalVariable  p_GLOBAL_PLAYER_FOLLOWER_COUNT          = none
GlobalVariable  p_GLOBAL_FORCE_CLONE_UNIQUE             = none
GlobalVariable  p_GLOBAL_FORCE_CLONE_GENERIC            = none
GlobalVariable  p_GLOBAL_FORCE_UNCLONE_UNIQUE           = none
GlobalVariable  p_GLOBAL_FORCE_UNCLONE_GENERIC          = none
FormList        p_FORMLIST_MARKERS_SETTLER              = none
Faction         p_FACTION_DLC1_THRALL                   = none
Faction         p_FACTION_DLC1_VAMPIRE_FEED_NO_CRIME    = none

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

MiscObject property TOKEN_THRALL
    MiscObject function Get()
        return p_TOKEN_THRALL
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_THRALL == none
            p_TOKEN_THRALL = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_GREETER
    MiscObject function Get()
        return p_TOKEN_GREETER
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_GREETER == none
            p_TOKEN_GREETER = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_COMBAT_DEFAULT
    MiscObject function Get()
        return p_TOKEN_COMBAT_DEFAULT
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_COMBAT_DEFAULT == none
            p_TOKEN_COMBAT_DEFAULT = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_COMBAT_WARRIOR
    MiscObject function Get()
        return p_TOKEN_COMBAT_WARRIOR
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_COMBAT_WARRIOR == none
            p_TOKEN_COMBAT_WARRIOR = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_COMBAT_MAGE
    MiscObject function Get()
        return p_TOKEN_COMBAT_MAGE
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_COMBAT_MAGE == none
            p_TOKEN_COMBAT_MAGE = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_COMBAT_ARCHER
    MiscObject function Get()
        return p_TOKEN_COMBAT_ARCHER
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_COMBAT_ARCHER == none
            p_TOKEN_COMBAT_ARCHER = val
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

GlobalVariable property GLOBAL_FORCE_CLONE_UNIQUE
    GlobalVariable function Get()
        return p_GLOBAL_FORCE_CLONE_UNIQUE
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_FORCE_CLONE_UNIQUE == none
            p_GLOBAL_FORCE_CLONE_UNIQUE = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_FORCE_CLONE_GENERIC
    GlobalVariable function Get()
        return p_GLOBAL_FORCE_CLONE_GENERIC
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_FORCE_CLONE_GENERIC == none
            p_GLOBAL_FORCE_CLONE_GENERIC = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_FORCE_UNCLONE_UNIQUE
    GlobalVariable function Get()
        return p_GLOBAL_FORCE_UNCLONE_UNIQUE
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_FORCE_UNCLONE_UNIQUE == none
            p_GLOBAL_FORCE_UNCLONE_UNIQUE = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_FORCE_UNCLONE_GENERIC
    GlobalVariable function Get()
        return p_GLOBAL_FORCE_UNCLONE_GENERIC
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_FORCE_UNCLONE_GENERIC == none
            p_GLOBAL_FORCE_UNCLONE_GENERIC = val
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

Faction property FACTION_DLC1_THRALL
    Faction function Get()
        return p_FACTION_DLC1_THRALL
    endFunction
    function Set(Faction val)
        if p_FACTION_DLC1_THRALL == none
            p_FACTION_DLC1_THRALL = val
        endIf
    endFunction
endProperty

Faction property FACTION_DLC1_VAMPIRE_FEED_NO_CRIME
    Faction function Get()
        return p_FACTION_DLC1_VAMPIRE_FEED_NO_CRIME
    endFunction
    function Set(Faction val)
        if p_FACTION_DLC1_VAMPIRE_FEED_NO_CRIME == none
            p_FACTION_DLC1_VAMPIRE_FEED_NO_CRIME = val
        endIf
    endFunction
endProperty

string property STR_HEALTH      = "Health"      autoReadOnly hidden
string property STR_MAGICKA     = "Magicka"     autoReadOnly hidden
string property STR_STAMINA     = "Stamina"     autoReadOnly hidden
string property STR_ONE_HANDED  = "OneHanded"   autoReadOnly hidden
string property STR_TWO_HANDED  = "TwoHanded"   autoReadOnly hidden
string property STR_BLOCK       = "Block"       autoReadOnly hidden
string property STR_HEAVY_ARMOR = "HeavyArmor"  autoReadOnly hidden
string property STR_LIGHT_ARMOR = "LightArmor"  autoReadOnly hidden
string property STR_SMITHING    = "Smithing"    autoReadOnly hidden
string property STR_DESTRUCTION = "Destruction" autoReadOnly hidden
string property STR_RESTORATION = "Restoration" autoReadOnly hidden
string property STR_CONJURATION = "Conjuration" autoReadOnly hidden
string property STR_ALTERATION  = "Alteration"  autoReadOnly hidden
string property STR_ILLUSION    = "Illusion"    autoReadOnly hidden
string property STR_ENCHANTING  = "Enchanting"  autoReadOnly hidden
string property STR_MARKSMAN    = "Marksman"    autoReadOnly hidden
string property STR_SNEAK       = "Sneak"       autoReadOnly hidden
string property STR_ALCHEMY     = "Alchemy"     autoReadOnly hidden
string property STR_LOCKPICKING = "Lockpicking" autoReadOnly hidden
string property STR_PICKPOCKET  = "Pickpocket"  autoReadOnly hidden
string property STR_SPEECHCRAFT = "Speechcraft" autoReadOnly hidden
