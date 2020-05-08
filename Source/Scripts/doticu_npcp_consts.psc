;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_consts extends Quest

; Private Constants
Actor                       p_ACTOR_PLAYER                          = none
Cell                        p_CELL_STORAGE                          = none
Static                      p_STATIC_MARKER_X                       = none
ObjectReference             p_MARKER_STORAGE                        = none
ObjectReference             p_MARKER_CLONER                         = none
ObjectReference             p_MARKER_CELL                           = none
ObjectReference             p_MARKER_EXPO_ANTECHAMBER               = none
ObjectReference             p_MARKER_GOTO_SAFE                      = none
Spell                       p_ABILITY_CELL                          = none
Spell                       p_ABILITY_SNEAK                         = none
MiscObject                  p_TOKEN_MEMBER                          = none
MiscObject                  p_TOKEN_SETTLER                         = none
MiscObject                  p_TOKEN_FOLLOWER                        = none
MiscObject                  p_TOKEN_FOLLOWER_SNEAK                  = none
MiscObject                  p_TOKEN_IMMOBILE                        = none
MiscObject                  p_TOKEN_CLONE                           = none
MiscObject                  p_TOKEN_BANISHED                        = none
MiscObject                  p_TOKEN_DISPLAY                         = none
MiscObject                  p_TOKEN_MOVEE                           = none
MiscObject                  p_TOKEN_GENERIC                         = none
MiscObject                  p_TOKEN_THRALL                          = none
MiscObject                  p_TOKEN_GREETER                         = none
MiscObject                  p_TOKEN_PARALYZED                       = none
MiscObject                  p_TOKEN_MANNEQUIN                       = none
MiscObject                  p_TOKEN_STYLE_DEFAULT                   = none
MiscObject                  p_TOKEN_STYLE_WARRIOR                   = none
MiscObject                  p_TOKEN_STYLE_MAGE                      = none
MiscObject                  p_TOKEN_STYLE_ARCHER                    = none
MiscObject                  p_TOKEN_STYLE_COWARD                    = none
MiscObject                  p_TOKEN_REANIMATED                      = none
MiscObject                  p_TOKEN_VITALITY_MORTAL                 = none
MiscObject                  p_TOKEN_VITALITY_PROTECTED              = none
MiscObject                  p_TOKEN_VITALITY_ESSENTIAL              = none
MiscObject                  p_TOKEN_VITALITY_INVULNERABLE           = none
MiscObject                  p_MISC_QUEUE                            = none
MiscObject                  p_MISC_TASKLIST                         = none
MiscObject                  p_MISC_VECTOR_FORM                      = none
GlobalVariable              p_GLOBAL_PLAYER_FOLLOWER_COUNT          = none
GlobalVariable              p_GLOBAL_FORCE_CLONE_UNIQUE             = none
GlobalVariable              p_GLOBAL_FORCE_CLONE_GENERIC            = none
GlobalVariable              p_GLOBAL_FORCE_UNCLONE_UNIQUE           = none
GlobalVariable              p_GLOBAL_FORCE_UNCLONE_GENERIC          = none
GlobalVariable              p_GLOBAL_IS_INSTALLED                   = none
GlobalVariable              p_GLOBAL_PERCENT_NO_BODY                = none
GlobalVariable              p_GLOBAL_PERCENT_NO_FEET                = none
GlobalVariable              p_GLOBAL_PERCENT_NO_HANDS               = none
GlobalVariable              p_GLOBAL_PERCENT_NO_HEAD                = none
FormList                    p_FORMLIST_MARKERS_SETTLER              = none
FormList                    p_FORMLIST_MARKERS_EXPO_CELL            = none
Faction                     p_FACTION_MEMBER                        = none
Faction                     p_FACTION_DLC1_THRALL                   = none
Faction                     p_FACTION_DLC1_VAMPIRE_FEED_NO_CRIME    = none
Faction                     p_FACTION_WI_NO_BODY_CLEANUP            = none
Faction                     p_FACTION_CURRENT_FOLLOWER              = none
Faction                     p_FACTION_POTENTIAL_FOLLOWER            = none
Faction                     p_FACTION_BARD_SINGER_NO_AUTOSTART      = none
Perk                        p_PERK_VAMPIRE_FEED                     = none
Perk                        p_PERK_KISS_THRALL                      = none
Perk                        p_PERK_RESURRECT                        = none
Perk                        p_PERK_REANIMATE                        = none
Perk                        p_PERK_UNPARALYZE                       = none
PlayerVampireQuestScript    p_SCRIPT_PLAYER_VAMPIRE_QUEST           = none
Keyword                     p_KEYWORD_VAMPIRE                       = none
Container                   p_CONTAINER_EMPTY                       = none
Container                   p_CONTAINER_TEMP                        = none
Container                   p_CONTAINER_OUTFIT                      = none
Container                   p_CONTAINER_OUTFIT_SETTLER              = none
Container                   p_CONTAINER_OUTFIT_THRALL               = none
Container                   p_CONTAINER_OUTFIT_IMMOBILE             = none
Container                   p_CONTAINER_OUTFIT_FOLLOWER             = none
Outfit                      p_OUTFIT_EMPTY                          = none
Outfit                      p_OUTFIT_TEMP                           = none
Quest                       p_QUEST_BARD_SONGS                      = none
VoiceType                   p_VOICE_FEMALE_COWARD                   = none
Weapon                      p_WEAPON_BLANK                          = none
Armor                       p_ARMOR_BLANK                           = none
Key                         p_KEY_LOCK                              = none
Quest                       p_QUEST_DIALOGUE_REANIMATED             = none
Quest                       p_QUEST_DIALOGUE_THRALL                 = none
EffectShader                p_SHADER_REANIMATE_FX                   = none
Location                    p_LOCATION_EXPO                         = none

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

Static property STATIC_MARKER_X
    Static function Get()
        return p_STATIC_MARKER_X
    endFunction
    function Set(Static val)
        if p_STATIC_MARKER_X == none
            p_STATIC_MARKER_X = val
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

ObjectReference property MARKER_CELL
    ObjectReference function Get()
        return p_MARKER_CELL
    endFunction
    function Set(ObjectReference val)
        if p_MARKER_CELL == none
            p_MARKER_CELL = val
        endIf
    endFunction
endProperty

ObjectReference property MARKER_EXPO_ANTECHAMBER
    ObjectReference function Get()
        return p_MARKER_EXPO_ANTECHAMBER
    endFunction
    function Set(ObjectReference val)
        if p_MARKER_EXPO_ANTECHAMBER == none
            p_MARKER_EXPO_ANTECHAMBER = val
        endIf
    endFunction
endProperty

ObjectReference property MARKER_GOTO_SAFE
    ObjectReference function Get()
        return p_MARKER_GOTO_SAFE
    endFunction
    function Set(ObjectReference val)
        if p_MARKER_GOTO_SAFE == none
            p_MARKER_GOTO_SAFE = val
        endIf
    endFunction
endProperty

Spell property ABILITY_CELL
    Spell function Get()
        return p_ABILITY_CELL
    endFunction
    function Set(Spell val)
        if p_ABILITY_CELL == none
            p_ABILITY_CELL = val
        endIf
    endFunction
endProperty

Spell property ABILITY_SNEAK
    Spell function Get()
        return p_ABILITY_SNEAK
    endFunction
    function Set(Spell val)
        if p_ABILITY_SNEAK == none
            p_ABILITY_SNEAK = val
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

MiscObject property TOKEN_DISPLAY
    MiscObject function Get()
        return p_TOKEN_DISPLAY
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_DISPLAY == none
            p_TOKEN_DISPLAY = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_MOVEE
    MiscObject function Get()
        return p_TOKEN_MOVEE
    endFunction
    function set(MiscObject val)
        if p_TOKEN_MOVEE == none
            p_TOKEN_MOVEE = val
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

MiscObject property TOKEN_MANNEQUIN
    MiscObject function Get()
        return p_TOKEN_MANNEQUIN
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_MANNEQUIN == none
            p_TOKEN_MANNEQUIN = val
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

MiscObject property TOKEN_STYLE_COWARD
    MiscObject function Get()
        return p_TOKEN_STYLE_COWARD
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_STYLE_COWARD == none
            p_TOKEN_STYLE_COWARD = val
        endIf
    endFunction
endProperty

MiscObject property TOKEN_REANIMATED
    MiscObject function Get()
        return p_TOKEN_REANIMATED
    endFunction
    function Set(MiscObject val)
        if p_TOKEN_REANIMATED == none
            p_TOKEN_REANIMATED = val
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

MiscObject property MISC_TASKLIST
    MiscObject function Get()
        return p_MISC_TASKLIST
    endFunction
    function Set(MiscObject val)
        if p_MISC_TASKLIST == none
            p_MISC_TASKLIST = val
        endIf
    endFunction
endProperty

MiscObject property MISC_VECTOR_FORM
    MiscObject function Get()
        return p_MISC_VECTOR_FORM
    endFunction
    function Set(MiscObject val)
        if p_MISC_VECTOR_FORM == none
            p_MISC_VECTOR_FORM = val
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

GlobalVariable property GLOBAL_IS_INSTALLED
    GlobalVariable function Get()
        return p_GLOBAL_IS_INSTALLED
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_IS_INSTALLED == none
            p_GLOBAL_IS_INSTALLED = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_PERCENT_NO_BODY
    GlobalVariable function Get()
        return p_GLOBAL_PERCENT_NO_BODY
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_PERCENT_NO_BODY == none
            p_GLOBAL_PERCENT_NO_BODY = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_PERCENT_NO_FEET
    GlobalVariable function Get()
        return p_GLOBAL_PERCENT_NO_FEET
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_PERCENT_NO_FEET == none
            p_GLOBAL_PERCENT_NO_FEET = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_PERCENT_NO_HANDS
    GlobalVariable function Get()
        return p_GLOBAL_PERCENT_NO_HANDS
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_PERCENT_NO_HANDS == none
            p_GLOBAL_PERCENT_NO_HANDS = val
        endIf
    endFunction
endProperty

GlobalVariable property GLOBAL_PERCENT_NO_HEAD
    GlobalVariable function Get()
        return p_GLOBAL_PERCENT_NO_HEAD
    endFunction
    function Set(GlobalVariable val)
        if p_GLOBAL_PERCENT_NO_HEAD == none
            p_GLOBAL_PERCENT_NO_HEAD = val
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

Formlist property FORMLIST_MARKERS_EXPO_CELL
    Formlist function Get()
        return p_FORMLIST_MARKERS_EXPO_CELL
    endFunction
    function Set(Formlist val)
        if p_FORMLIST_MARKERS_EXPO_CELL == none
            p_FORMLIST_MARKERS_EXPO_CELL = val
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

Faction property FACTION_WI_NO_BODY_CLEANUP
    Faction function Get()
        return p_FACTION_WI_NO_BODY_CLEANUP
    endFunction
    function Set(Faction val)
        if p_FACTION_WI_NO_BODY_CLEANUP == none
            p_FACTION_WI_NO_BODY_CLEANUP = val
        endIf
    endFunction
endProperty

Faction property FACTION_CURRENT_FOLLOWER
    Faction function Get()
        return p_FACTION_CURRENT_FOLLOWER
    endFunction
    function Set(Faction val)
        if p_FACTION_CURRENT_FOLLOWER == none
            p_FACTION_CURRENT_FOLLOWER = val
        endIf
    endFunction
endProperty

Faction property FACTION_POTENTIAL_FOLLOWER
    Faction function Get()
        return p_FACTION_POTENTIAL_FOLLOWER
    endFunction
    function Set(Faction val)
        if p_FACTION_POTENTIAL_FOLLOWER == none
            p_FACTION_POTENTIAL_FOLLOWER = val
        endIf
    endFunction
endProperty

Faction property FACTION_BARD_SINGER_NO_AUTOSTART
    Faction function Get()
        return p_FACTION_BARD_SINGER_NO_AUTOSTART
    endFunction
    function Set(Faction val)
        if p_FACTION_BARD_SINGER_NO_AUTOSTART == none
            p_FACTION_BARD_SINGER_NO_AUTOSTART = val
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

Perk property PERK_RESURRECT
    Perk function Get()
        return p_PERK_RESURRECT
    endFunction
    function Set(Perk val)
        if p_PERK_RESURRECT == none
            p_PERK_RESURRECT = val
        endIf
    endFunction
endProperty

Perk property PERK_REANIMATE
    Perk function Get()
        return p_PERK_REANIMATE
    endFunction
    function Set(Perk val)
        if p_PERK_REANIMATE == none
            p_PERK_REANIMATE = val
        endIf
    endFunction
endProperty

Perk property PERK_UNPARALYZE
    Perk function Get()
        return p_PERK_UNPARALYZE
    endFunction
    function Set(Perk val)
        if p_PERK_UNPARALYZE == none
            p_PERK_UNPARALYZE = val
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

Container property CONTAINER_OUTFIT_SETTLER
    Container function Get()
        return p_CONTAINER_OUTFIT_SETTLER
    endFunction
    function Set(Container val)
        if p_CONTAINER_OUTFIT_SETTLER == none
            p_CONTAINER_OUTFIT_SETTLER = val
        endIf
    endFunction
endProperty

Container property CONTAINER_OUTFIT_THRALL
    Container function Get()
        return p_CONTAINER_OUTFIT_THRALL
    endFunction
    function Set(Container val)
        if p_CONTAINER_OUTFIT_THRALL == none
            p_CONTAINER_OUTFIT_THRALL = val
        endIf
    endFunction
endProperty

Container property CONTAINER_OUTFIT_IMMOBILE
    Container function Get()
        return p_CONTAINER_OUTFIT_IMMOBILE
    endFunction
    function Set(Container val)
        if p_CONTAINER_OUTFIT_IMMOBILE == none
            p_CONTAINER_OUTFIT_IMMOBILE = val
        endIf
    endFunction
endProperty

Container property CONTAINER_OUTFIT_FOLLOWER
    Container function Get()
        return p_CONTAINER_OUTFIT_FOLLOWER
    endFunction
    function Set(Container val)
        if p_CONTAINER_OUTFIT_FOLLOWER == none
            p_CONTAINER_OUTFIT_FOLLOWER = val
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

Outfit property OUTFIT_TEMP
    Outfit function Get()
        return p_OUTFIT_TEMP
    endFunction
    function Set(Outfit val)
        if p_OUTFIT_TEMP == none
            p_OUTFIT_TEMP = val
        endIf
    endFunction
endProperty

Quest property QUEST_BARD_SONGS
    Quest function Get()
        return p_QUEST_BARD_SONGS
    endFunction
    function Set(Quest val)
        if p_QUEST_BARD_SONGS == none
            p_QUEST_BARD_SONGS = val
        endIf
    endFunction
endProperty

Quest property QUEST_DIALOGUE_REANIMATED
    Quest function Get()
        return p_QUEST_DIALOGUE_REANIMATED
    endFunction
    function Set(Quest val)
        if p_QUEST_DIALOGUE_REANIMATED == none
            p_QUEST_DIALOGUE_REANIMATED = val
        endIf
    endFunction
endProperty

Quest property QUEST_DIALOGUE_THRALL
    Quest function Get()
        return p_QUEST_DIALOGUE_THRALL
    endFunction
    function Set(Quest val)
        if p_QUEST_DIALOGUE_THRALL == none
            p_QUEST_DIALOGUE_THRALL = val
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

Armor property ARMOR_BLANK
    Armor function Get()
        return p_ARMOR_BLANK
    endFunction
    function Set(Armor val)
        if p_ARMOR_BLANK == none
            p_ARMOR_BLANK = val
        endIf
    endFunction
endProperty

VoiceType property VOICE_FEMALE_COWARD
    VoiceType function Get()
        return p_VOICE_FEMALE_COWARD
    endFunction
    function Set(VoiceType val)
        if p_VOICE_FEMALE_COWARD == none
            p_VOICE_FEMALE_COWARD = val
        endIf
    endFunction
endProperty

Key property KEY_LOCK
    Key function Get()
        return p_KEY_LOCK
    endFunction
    function Set(Key val)
        if p_KEY_LOCK == none
            p_KEY_LOCK = val
        endIf
    endFunction
endProperty

EffectShader property SHADER_REANIMATE_FX
    EffectShader function Get()
        return p_SHADER_REANIMATE_FX
    endFunction
    function Set(EffectShader val)
        if p_SHADER_REANIMATE_FX == none
            p_SHADER_REANIMATE_FX = val
        endIf
    endFunction
endProperty

Location property LOCATION_EXPO
    Location function Get()
        return p_LOCATION_EXPO
    endFunction
    function Set(Location val)
        if p_LOCATION_EXPO == none
            p_LOCATION_EXPO = val
        endIf
    endFunction
endProperty

int property VERSION_MAJOR                  =     0 autoReadOnly hidden; set manually upon each release
int property VERSION_MINOR                  =     8 autoReadOnly hidden; set manually upon each release
int property VERSION_PATCH                  =     3 autoReadOnly hidden; set manually upon each release

int property MIN_DISPLAY                    =     1 autoReadOnly hidden
int property MAX_DISPLAY                    =     8 autoReadOnly hidden
int property DEFAULT_DISPLAY                =     5 autoReadOnly hidden

int property DEFAULT_PERCENT_BODY           =   100 autoReadOnly hidden
int property DEFAULT_PERCENT_FEET           =    90 autoReadOnly hidden
int property DEFAULT_PERCENT_HANDS          =    90 autoReadOnly hidden
int property DEFAULT_PERCENT_HEAD           =    50 autoReadOnly hidden

int property KEY_DEF_FS_SUMMON_ALL          =    53 autoReadOnly hidden; Forward Slash
int property KEY_DEF_FS_SUMMON_MOBILE       =    51 autoReadOnly hidden; Comma
int property KEY_DEF_FS_SUMMON_IMMOBILE     =    52 autoReadOnly hidden; Period
int property KEY_DEF_FS_SETTLE              =    39 autoReadOnly hidden; Semicolon
int property KEY_DEF_FS_UNSETTLE            =    40 autoReadOnly hidden; Apostrophe
int property KEY_DEF_FS_IMMOBILIZE          =    13 autoReadOnly hidden; Equals
int property KEY_DEF_FS_MOBILIZE            =    12 autoReadOnly hidden; Minus
int property KEY_DEF_FS_SNEAK               =    10 autoReadOnly hidden; 9
int property KEY_DEF_FS_UNSNEAK             =    11 autoReadOnly hidden; 0
int property KEY_DEF_FS_RESURRECT           =    14 autoReadOnly hidden; Backspace

int property KEY_DEF_MS_DISPLAY_TOGGLE      =    43 autoReadOnly hidden; Back Slash
int property KEY_DEF_MS_DISPLAY_PREVIOUS    =    26 autoReadOnly hidden; Left Bracket
int property KEY_DEF_MS_DISPLAY_NEXT        =    27 autoReadOnly hidden; Right Bracket

int property KEY_DEF_MOVE_TOGGLE            =    56 autoReadOnly hidden; Left Alt
int property KEY_DEF_MOVE_FARTHER           =   200 autoReadOnly hidden; Up Arrow
int property KEY_DEF_MOVE_NEARER            =   208 autoReadOnly hidden; Down Arrow
int property KEY_DEF_MOVE_ROTATE_RIGHT      =   205 autoReadOnly hidden; Right Arrow
int property KEY_DEF_MOVE_ROTATE_LEFT       =   203 autoReadOnly hidden; Left Arrow

int property KEY_DEF_M_TOGGLE_MEMBER        =    78 autoReadOnly hidden; NUM+
int property KEY_DEF_M_TOGGLE_CLONE         =   156 autoReadOnly hidden; NUM Enter
int property KEY_DEF_M_TOGGLE_SETTLER       =    82 autoReadOnly hidden; NUM0
int property KEY_DEF_M_TOGGLE_THRALL        =    73 autoReadOnly hidden; NUM9
int property KEY_DEF_M_TOGGLE_IMMOBILE      =    83 autoReadOnly hidden; NUM.
int property KEY_DEF_M_TOGGLE_PARALYZED     =   181 autoReadOnly hidden; NUM/
int property KEY_DEF_M_TOGGLE_FOLLOWER      =    55 autoReadOnly hidden; NUM*
int property KEY_DEF_M_TOGGLE_SNEAK         =    74 autoReadOnly hidden; NUM-

int property KEY_DEF_N_HAS_BASE             =    24 autoReadOnly hidden; O
int property KEY_DEF_N_COUNT_BASE           =    24 autoReadOnly hidden; O

string property STR_HEALTH                  = "Health"                      autoReadOnly hidden
string property STR_MAGICKA                 = "Magicka"                     autoReadOnly hidden
string property STR_STAMINA                 = "Stamina"                     autoReadOnly hidden
string property STR_ONE_HANDED              = "OneHanded"                   autoReadOnly hidden
string property STR_TWO_HANDED              = "TwoHanded"                   autoReadOnly hidden
string property STR_BLOCK                   = "Block"                       autoReadOnly hidden
string property STR_HEAVY_ARMOR             = "HeavyArmor"                  autoReadOnly hidden
string property STR_LIGHT_ARMOR             = "LightArmor"                  autoReadOnly hidden
string property STR_SMITHING                = "Smithing"                    autoReadOnly hidden
string property STR_DESTRUCTION             = "Destruction"                 autoReadOnly hidden
string property STR_RESTORATION             = "Restoration"                 autoReadOnly hidden
string property STR_CONJURATION             = "Conjuration"                 autoReadOnly hidden
string property STR_ALTERATION              = "Alteration"                  autoReadOnly hidden
string property STR_ILLUSION                = "Illusion"                    autoReadOnly hidden
string property STR_ENCHANTING              = "Enchanting"                  autoReadOnly hidden
string property STR_MARKSMAN                = "Marksman"                    autoReadOnly hidden
string property STR_SNEAK                   = "Sneak"                       autoReadOnly hidden
string property STR_ALCHEMY                 = "Alchemy"                     autoReadOnly hidden
string property STR_LOCKPICKING             = "Lockpicking"                 autoReadOnly hidden
string property STR_PICKPOCKET              = "Pickpocket"                  autoReadOnly hidden
string property STR_SPEECHCRAFT             = "Speechcraft"                 autoReadOnly hidden

string property STR_MCM_SUMMON              = " Summon "                    autoReadOnly hidden
string property STR_MCM_GOTO                = " Goto "                      autoReadOnly hidden
string property STR_MCM_PACK                = " Pack "                      autoReadOnly hidden
string property STR_MCM_OUTFIT              = " Outfit "                    autoReadOnly hidden
string property STR_MCM_STYLE               = " Style "                     autoReadOnly hidden
string property STR_MCM_VITALIZE            = " Vitalize "                  autoReadOnly hidden
string property STR_MCM_RATING              = " Rating "                    autoReadOnly hidden
string property STR_MCM_VITALITY            = " Vitality "                  autoReadOnly hidden
string property STR_MCM_CURRENT             = " Current "                   autoReadOnly hidden
string property STR_MCM_MEMBER              = " Member "                    autoReadOnly hidden
string property STR_MCM_SETTLER             = " Settler "                   autoReadOnly hidden
string property STR_MCM_THRALL              = " Thrall "                    autoReadOnly hidden
string property STR_MCM_IMMOBILE            = " Immobile "                  autoReadOnly hidden
string property STR_MCM_FOLLOWER            = " Follower "                  autoReadOnly hidden
string property STR_MCM_VANILLA             = " Vanilla "                   autoReadOnly hidden
string property STR_MCM_SETTLE              = " Settle "                    autoReadOnly hidden
string property STR_MCM_RESETTLE            = " Resettle "                  autoReadOnly hidden
string property STR_MCM_UNSETTLE            = " Unsettle "                  autoReadOnly hidden
string property STR_MCM_IMMOBILIZE          = " Immobilize "                autoReadOnly hidden
string property STR_MCM_MOBILIZE            = " Mobilize "                  autoReadOnly hidden
string property STR_MCM_PARALYZE            = " Paralyze "                  autoReadOnly hidden
string property STR_MCM_UNPARALYZE          = " Unparalyze "                autoReadOnly hidden
string property STR_MCM_FOLLOW              = " Follow "                    autoReadOnly hidden
string property STR_MCM_UNFOLLOW            = " Unfollow "                  autoReadOnly hidden
string property STR_MCM_UNSNEAK             = " Unsneak "                   autoReadOnly hidden
string property STR_MCM_RELEVEL             = " Relevel "                   autoReadOnly hidden
string property STR_MCM_RESURRECT           = " Resurrect "                 autoReadOnly hidden
string property STR_MCM_DEFAULT             = " Default "                   autoReadOnly hidden
string property STR_MCM_WARRIOR             = " Warrior "                   autoReadOnly hidden
string property STR_MCM_MAGE                = " Mage "                      autoReadOnly hidden
string property STR_MCM_ARCHER              = " Archer "                    autoReadOnly hidden
string property STR_MCM_COWARD              = " Coward "                    autoReadOnly hidden
string property STR_MCM_MORTAL              = " Mortal "                    autoReadOnly hidden
string property STR_MCM_PROTECTED           = " Protected "                 autoReadOnly hidden
string property STR_MCM_ESSENTIAL           = " Essential "                 autoReadOnly hidden
string property STR_MCM_INVULNERABLE        = " Invulnerable "              autoReadOnly hidden
string property STR_MCM_CLONE               = " Clone "                     autoReadOnly hidden
string property STR_MCM_UNCLONE             = " Unclone "                   autoReadOnly hidden
string property STR_MCM_UNMEMBER            = " Unmember "                  autoReadOnly hidden
string property STR_MCM_BASE                = " Base "                      autoReadOnly hidden
string property STR_MCM_REFERENCE           = " Reference "                 autoReadOnly hidden
string property STR_MCM_RACE                = " Race "                      autoReadOnly hidden

string property STR_MCM_HEALTH              = " Health "                    autoReadOnly hidden
string property STR_MCM_MAGICKA             = " Magicka "                   autoReadOnly hidden
string property STR_MCM_STAMINA             = " Stamina "                   autoReadOnly hidden
string property STR_MCM_ONE_HANDED          = " One Handed "                autoReadOnly hidden
string property STR_MCM_TWO_HANDED          = " Two Handed "                autoReadOnly hidden
string property STR_MCM_BLOCK               = " Block "                     autoReadOnly hidden
string property STR_MCM_HEAVY_ARMOR         = " Heavy Armor "               autoReadOnly hidden
string property STR_MCM_LIGHT_ARMOR         = " Light Armor "               autoReadOnly hidden
string property STR_MCM_SMITHING            = " Smithing "                  autoReadOnly hidden
string property STR_MCM_DESTRUCTION         = " Destruction "               autoReadOnly hidden
string property STR_MCM_RESTORATION         = " Restoration "               autoReadOnly hidden
string property STR_MCM_CONJURATION         = " Conjuration "               autoReadOnly hidden
string property STR_MCM_ALTERATION          = " Alteration "                autoReadOnly hidden
string property STR_MCM_ILLUSION            = " Illusion "                  autoReadOnly hidden
string property STR_MCM_ENCHANTING          = " Enchanting "                autoReadOnly hidden
string property STR_MCM_MARKSMAN            = " Marksman "                  autoReadOnly hidden
string property STR_MCM_SNEAK               = " Sneak "                     autoReadOnly hidden
string property STR_MCM_ALCHEMY             = " Alchemy "                   autoReadOnly hidden
string property STR_MCM_LOCKPICKING         = " Lockpicking "               autoReadOnly hidden
string property STR_MCM_PICKPOCKET          = " Pickpocket "                autoReadOnly hidden
string property STR_MCM_SPEECHCRAFT         = " Speechcraft "               autoReadOnly hidden

string property STR_KEY_FS_SUMMON_ALL       = "Summon All Followers"        autoReadOnly hidden
string property STR_KEY_FS_SUMMON_MOBILE    = "Summon Mobile Followers"     autoReadOnly hidden
string property STR_KEY_FS_SUMMON_IMMOBILE  = "Summon Immobile Followers"   autoReadOnly hidden
string property STR_KEY_FS_SETTLE           = "Settle Followers"            autoReadOnly hidden
string property STR_KEY_FS_UNSETTLE         = "Unsettle Followers"          autoReadOnly hidden
string property STR_KEY_FS_IMMOBILIZE       = "Immobilize Followers"        autoReadOnly hidden
string property STR_KEY_FS_MOBILIZE         = "Mobilize Followers"          autoReadOnly hidden
string property STR_KEY_FS_SNEAK            = "Sneak Followers"             autoReadOnly hidden
string property STR_KEY_FS_UNSNEAK          = "Unsneak Followers"           autoReadOnly hidden
string property STR_KEY_FS_RESURRECT        = "Resurrect Followers"         autoReadOnly hidden

string property STR_KEY_MS_DISPLAY_TOGGLE   = "Toggle Member Display"       autoReadOnly hidden
string property STR_KEY_MS_DISPLAY_PREVIOUS = "Display Previous Members"    autoReadOnly hidden
string property STR_KEY_MS_DISPLAY_NEXT     = "Display Next Members"        autoReadOnly hidden

string property STR_KEY_MOVE_TOGGLE         = "Toggle Move"                 autoReadOnly hidden
string property STR_KEY_MOVE_FARTHER        = "Move Farther"                autoReadOnly hidden
string property STR_KEY_MOVE_NEARER         = "Move Nearer"                 autoReadOnly hidden
string property STR_KEY_MOVE_ROTATE_RIGHT   = "Rotate Right"                autoReadOnly hidden
string property STR_KEY_MOVE_ROTATE_LEFT    = "Rotate Left"                 autoReadOnly hidden

string property STR_KEY_M_TOGGLE_MEMBER     = "Toggle Member"               autoReadOnly hidden
string property STR_KEY_M_TOGGLE_CLONE      = "Toggle Clone"                autoReadOnly hidden
string property STR_KEY_M_TOGGLE_SETTLER    = "Toggle Settler"              autoReadOnly hidden
string property STR_KEY_M_TOGGLE_THRALL     = "Toggle Thrall"               autoReadOnly hidden
string property STR_KEY_M_TOGGLE_IMMOBILE   = "Toggle Immobile"             autoReadOnly hidden
string property STR_KEY_M_TOGGLE_PARALYZED  = "Toggle Paralyzed"            autoReadOnly hidden
string property STR_KEY_M_TOGGLE_FOLLOWER   = "Toggle Follower"             autoReadOnly hidden
string property STR_KEY_M_TOGGLE_SNEAK      = "Toggle Sneak"                autoReadOnly hidden

string property STR_KEY_N_HAS_BASE          = "Has Base"                    autoReadOnly hidden
string property STR_KEY_N_COUNT_BASE        = "Count Base"                  autoReadOnly hidden
