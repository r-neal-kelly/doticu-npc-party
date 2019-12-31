Scriptname doticu_npcp_consts extends Quest

; Private Constants
Actor                       p_ACTOR_PLAYER                          = none
Cell                        p_CELL_STORAGE                          = none
ObjectReference             p_MARKER_STORAGE                        = none
ObjectReference             p_MARKER_CLONER                         = none
MiscObject                  p_TOKEN_MEMBER                          = none
MiscObject                  p_TOKEN_SETTLER                         = none
MiscObject                  p_TOKEN_FOLLOWER                        = none
MiscObject                  p_TOKEN_FOLLOWER_SNEAK                  = none
MiscObject                  p_TOKEN_IMMOBILE                        = none
MiscObject                  p_TOKEN_CLONE                           = none
MiscObject                  p_TOKEN_BANISHED                        = none
MiscObject                  p_TOKEN_GENERIC                         = none
MiscObject                  p_TOKEN_THRALL                          = none
MiscObject                  p_TOKEN_GREETER                         = none
MiscObject                  p_TOKEN_PARALYZED                       = none
MiscObject                  p_TOKEN_STYLE_DEFAULT                   = none
MiscObject                  p_TOKEN_STYLE_WARRIOR                   = none
MiscObject                  p_TOKEN_STYLE_MAGE                      = none
MiscObject                  p_TOKEN_STYLE_ARCHER                    = none
MiscObject                  p_TOKEN_VITALITY_MORTAL                 = none
MiscObject                  p_TOKEN_VITALITY_PROTECTED              = none
MiscObject                  p_TOKEN_VITALITY_ESSENTIAL              = none
MiscObject                  p_TOKEN_VITALITY_INVULNERABLE           = none
MiscObject                  p_MISC_QUEUE                            = none
GlobalVariable              p_GLOBAL_PLAYER_FOLLOWER_COUNT          = none
GlobalVariable              p_GLOBAL_FORCE_CLONE_UNIQUE             = none
GlobalVariable              p_GLOBAL_FORCE_CLONE_GENERIC            = none
GlobalVariable              p_GLOBAL_FORCE_UNCLONE_UNIQUE           = none
GlobalVariable              p_GLOBAL_FORCE_UNCLONE_GENERIC          = none
FormList                    p_FORMLIST_MARKERS_SETTLER              = none
FormList                    p_FORMLIST_OUTFITS                      = none
Faction                     p_FACTION_MEMBER                        = none
Faction                     p_FACTION_DLC1_THRALL                   = none
Faction                     p_FACTION_DLC1_VAMPIRE_FEED_NO_CRIME    = none
Perk                        p_PERK_VAMPIRE_FEED                     = none
Perk                        p_PERK_KISS_THRALL                      = none
Perk                        p_PERK_KILL_ESSENTIAL                   = none
Perk                        p_PERK_RESURRECT_MEMBER                 = none
PlayerVampireQuestScript    p_SCRIPT_PLAYER_VAMPIRE_QUEST           = none
Keyword                     p_KEYWORD_VAMPIRE                       = none
Container                   p_CONTAINER_EMPTY                       = none
Container                   p_CONTAINER_TEMP                        = none
Container                   p_CONTAINER_OUTFIT                      = none
Outfit                      p_OUTFIT_EMPTY                          = none
Outfit                      p_OUTFIT_TEMPLATE                       = none
Weapon                      p_WEAPON_BLANK                          = none

; Public Constants
int property VERSION_MAJOR
    int function Get()
        return 0; set manually upon each release
    endFunction
endProperty

int property VERSION_MINOR
    int function Get()
        return 1; set manually upon each release
    endFunction
endProperty

int property VERSION_PATCH
    int function Get()
        return 3; set manually upon each release
    endFunction
endProperty

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

Cell property CELL_STORAGE
    Cell function Get()
        return p_CELL_STORAGE
    endFunction
    function Set(Cell val)
        if p_CELL_STORAGE == none
            p_CELL_STORAGE = val
        endIf
    endFunction
endProperty

ObjectReference property MARKER_STORAGE
    ObjectReference function Get()
        return p_MARKER_STORAGE
    endFunction
    function Set(ObjectReference val)
        if p_MARKER_STORAGE == none
            p_MARKER_STORAGE = val
        endIf
    endFunction
endProperty

ObjectReference property MARKER_CLONER
    ObjectReference function Get()
        return p_MARKER_CLONER
    endFunction
    function Set(ObjectReference val)
        if p_MARKER_CLONER == none
            p_MARKER_CLONER = val
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

MiscObject property TOKEN_PARALYZED
    MiscObject function Get()
        return p_TOKEN_PARALYZED
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_PARALYZED == none
            p_TOKEN_PARALYZED = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_STYLE_DEFAULT
    MiscObject function Get()
        return p_TOKEN_STYLE_DEFAULT
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_STYLE_DEFAULT == none
            p_TOKEN_STYLE_DEFAULT = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_STYLE_WARRIOR
    MiscObject function Get()
        return p_TOKEN_STYLE_WARRIOR
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_STYLE_WARRIOR == none
            p_TOKEN_STYLE_WARRIOR = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_STYLE_MAGE
    MiscObject function Get()
        return p_TOKEN_STYLE_MAGE
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_STYLE_MAGE == none
            p_TOKEN_STYLE_MAGE = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_STYLE_ARCHER
    MiscObject function Get()
        return p_TOKEN_STYLE_ARCHER
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_STYLE_ARCHER == none
            p_TOKEN_STYLE_ARCHER = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_VITALITY_MORTAL
    MiscObject function Get()
        return p_TOKEN_VITALITY_MORTAL
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_VITALITY_MORTAL == none
            p_TOKEN_VITALITY_MORTAL = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_VITALITY_PROTECTED
    MiscObject function Get()
        return p_TOKEN_VITALITY_PROTECTED
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_VITALITY_PROTECTED == none
            p_TOKEN_VITALITY_PROTECTED = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_VITALITY_ESSENTIAL
    MiscObject function Get()
        return p_TOKEN_VITALITY_ESSENTIAL
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_VITALITY_ESSENTIAL == none
            p_TOKEN_VITALITY_ESSENTIAL = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_VITALITY_INVULNERABLE
    MiscObject function Get()
        return p_TOKEN_VITALITY_INVULNERABLE
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_VITALITY_INVULNERABLE == none
            p_TOKEN_VITALITY_INVULNERABLE = val
        endIf
    endFunction
endProperty

MiscObject property MISC_QUEUE
    MiscObject function Get()
        return p_MISC_QUEUE
    endFunction
    function Set(MiscObject val)
        if p_MISC_QUEUE == none
            p_MISC_QUEUE = val
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

Formlist property FORMLIST_OUTFITS
    Formlist function Get()
        return p_FORMLIST_OUTFITS
    endFunction
    function Set(Formlist val)
        if p_FORMLIST_OUTFITS == none
            p_FORMLIST_OUTFITS = val
        endIf
    endFunction
endProperty

Faction property FACTION_MEMBER
    Faction function Get()
        return p_FACTION_MEMBER
    endFunction
    function Set(Faction val)
        if p_FACTION_MEMBER == none
            p_FACTION_MEMBER = val
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

Perk property PERK_VAMPIRE_FEED
    Perk function Get()
        return p_PERK_VAMPIRE_FEED
    endFunction
    function Set(Perk val)
        if p_PERK_VAMPIRE_FEED == none
            p_PERK_VAMPIRE_FEED = val
        endIf
    endFunction
endProperty

Perk property PERK_KISS_THRALL
    Perk function Get()
        return p_PERK_KISS_THRALL
    endFunction
    function Set(Perk val)
        if p_PERK_KISS_THRALL == none
            p_PERK_KISS_THRALL = val
        endIf
    endFunction
endProperty

Perk property PERK_KILL_ESSENTIAL
    Perk function Get()
        return p_PERK_KILL_ESSENTIAL
    endFunction
    function Set(Perk val)
        if p_PERK_KILL_ESSENTIAL == none
            p_PERK_KILL_ESSENTIAL = val
        endIf
    endFunction
endProperty

Perk property PERK_RESURRECT_MEMBER
    Perk function Get()
        return p_PERK_RESURRECT_MEMBER
    endFunction
    function Set(Perk val)
        if p_PERK_RESURRECT_MEMBER == none
            p_PERK_RESURRECT_MEMBER = val
        endIf
    endFunction
endProperty

PlayerVampireQuestScript property SCRIPT_PLAYER_VAMPIRE_QUEST
    PlayerVampireQuestScript function Get()
        return p_SCRIPT_PLAYER_VAMPIRE_QUEST
    endFunction
    function Set(PlayerVampireQuestScript val)
        if p_SCRIPT_PLAYER_VAMPIRE_QUEST == none
            p_SCRIPT_PLAYER_VAMPIRE_QUEST = val
        endIf
    endFunction
endProperty

Keyword property KEYWORD_VAMPIRE
    Keyword function Get()
        return p_KEYWORD_VAMPIRE
    endFunction
    function Set(Keyword val)
        if p_KEYWORD_VAMPIRE == none
            p_KEYWORD_VAMPIRE = val
        endIf
    endFunction
endProperty

Container property CONTAINER_EMPTY
    Container function Get()
        return p_CONTAINER_EMPTY
    endFunction
    function Set(Container val)
        if p_CONTAINER_EMPTY == none
            p_CONTAINER_EMPTY = val
        endIf
    endFunction
endProperty

Container property CONTAINER_TEMP
    Container function Get()
        return p_CONTAINER_TEMP
    endFunction
    function Set(Container val)
        if p_CONTAINER_TEMP == none
            p_CONTAINER_TEMP = val
        endIf
    endFunction
endProperty

Container property CONTAINER_OUTFIT
    Container function Get()
        return p_CONTAINER_OUTFIT
    endFunction
    function Set(Container val)
        if p_CONTAINER_OUTFIT == none
            p_CONTAINER_OUTFIT = val
        endIf
    endFunction
endProperty

Outfit property OUTFIT_EMPTY
    Outfit function Get()
        return p_OUTFIT_EMPTY
    endFunction
    function Set(Outfit val)
        if p_OUTFIT_EMPTY == none
            p_OUTFIT_EMPTY = val
        endIf
    endFunction
endProperty

Weapon property WEAPON_BLANK
    Weapon function Get()
        return p_WEAPON_BLANK
    endFunction
    function Set(Weapon val)
        if p_WEAPON_BLANK == none
            p_WEAPON_BLANK = val
        endIf
    endFunction
endProperty

string property STR_HEALTH              = "Health"          autoReadOnly hidden
string property STR_MAGICKA             = "Magicka"         autoReadOnly hidden
string property STR_STAMINA             = "Stamina"         autoReadOnly hidden
string property STR_ONE_HANDED          = "OneHanded"       autoReadOnly hidden
string property STR_TWO_HANDED          = "TwoHanded"       autoReadOnly hidden
string property STR_BLOCK               = "Block"           autoReadOnly hidden
string property STR_HEAVY_ARMOR         = "HeavyArmor"      autoReadOnly hidden
string property STR_LIGHT_ARMOR         = "LightArmor"      autoReadOnly hidden
string property STR_SMITHING            = "Smithing"        autoReadOnly hidden
string property STR_DESTRUCTION         = "Destruction"     autoReadOnly hidden
string property STR_RESTORATION         = "Restoration"     autoReadOnly hidden
string property STR_CONJURATION         = "Conjuration"     autoReadOnly hidden
string property STR_ALTERATION          = "Alteration"      autoReadOnly hidden
string property STR_ILLUSION            = "Illusion"        autoReadOnly hidden
string property STR_ENCHANTING          = "Enchanting"      autoReadOnly hidden
string property STR_MARKSMAN            = "Marksman"        autoReadOnly hidden
string property STR_SNEAK               = "Sneak"           autoReadOnly hidden
string property STR_ALCHEMY             = "Alchemy"         autoReadOnly hidden
string property STR_LOCKPICKING         = "Lockpicking"     autoReadOnly hidden
string property STR_PICKPOCKET          = "Pickpocket"      autoReadOnly hidden
string property STR_SPEECHCRAFT         = "Speechcraft"     autoReadOnly hidden

string property STR_MCM_DEFAULT         = " Default "       autoReadOnly hidden
String property STR_MCM_WARRIOR         = " Warrior "       autoReadOnly hidden
String property STR_MCM_MAGE            = " Mage "          autoReadOnly hidden
String property STR_MCM_ARCHER          = " Archer "        autoReadOnly hidden
string property STR_MCM_MORTAL          = " Mortal "        autoReadOnly hidden
String property STR_MCM_PROTECTED       = " Protected "     autoReadOnly hidden
String property STR_MCM_ESSENTIAL       = " Essential "     autoReadOnly hidden
String property STR_MCM_INVULNERABLE    = " Invulnerable "  autoReadOnly hidden
