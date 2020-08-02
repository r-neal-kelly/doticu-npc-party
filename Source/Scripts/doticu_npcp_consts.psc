;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_consts extends Quest

;/
    We actually want to remove the need of most of these in due time.
/;

; Skyrim Actors
Actor function Player_Actor() native global

; Skyrim Effect Shaders
EffectShader function Reanimate_Effect_Shader() native global

; Skyrim Factions
Faction function No_Bard_Singer_Autostart_Faction() native global

; Skyrim Keywords
Keyword function Vampire_Keyword() native global

; Skyrim Perks
Perk function Vampire_Feed_Perk() native global

; Skyrim Quests
Quest function Bard_Songs_Quest() native global
Quest function Follower_Dialogue_Quest() native global
Quest function Player_Vampire_Quest() native global

; Skyrim Reference Markers
ObjectReference function Safe_Goto_Marker() native global

; Skyrim Statics
Static function X_Marker_Static() native global

; Dawnguard Factions
Faction function DLC1_Thrall_Faction() native global

; NPCP Actor Bases
ActorBase function Menu_Actor_Base() native global

; NPCP Armors
Armor function Blank_Armor() native global

; NPCP Containers
Container function Empty_Container() native global
Container function Outfit_Container() native global
Container function Immobile_Outfit_Container() native global
Container function Settler_Outfit_Container() native global
Container function Thrall_Outfit_Container() native global
Container function Follower_Outfit_Container() native global

; NPCP Formlists
Formlist function Is_Saddler_Sitting_Globals_Formlist() native global
Formlist function Expo_Cell_Markers_Formlist() native global

; NPCP Globals
GlobalVariable function Is_Installed_Global() native global
GlobalVariable function Force_Clone_Uniques_Global() native global
GlobalVariable function Force_Clone_Generics_Global() native global
GlobalVariable function Force_Unclone_Uniques_Global() native global
GlobalVariable function Force_Unclone_Generics_Global() native global
GlobalVariable function No_Body_Percent_Global() native global
GlobalVariable function No_Feet_Percent_Global() native global
GlobalVariable function No_Hands_Percent_Global() native global
GlobalVariable function No_Head_Percent_Global() native global

; NPCP Leveled Actors
LeveledActor function Horse_Leveled_Actor() native global

; NPCP Locations
Location function Expo_Location() native global

; NPCP Magic Effects
MagicEffect function Retreat_Magic_Effect() native global

; NPCP Misc Tokens
MiscObject function Greeter_Token() native global
MiscObject function Movee_Token() native global
MiscObject function Reanimated_Token() native global
MiscObject function Follower_Token() native global
MiscObject function Saddler_Token() native global
MiscObject function Retreater_Token() native global

; NPCP Miscs
MiscObject function Tasklist() native global
MiscObject function Form_Vector() native global

; NPCP Perks
Perk function Kiss_Thrall_Perk() native global
Perk function Reanimate_Perk() native global
Perk function Resurrect_Perk() native global
Perk function Unparalyze_Perk() native global

; NPCP Quests
Quest function Thrall_Dialogue_Quest() native global
Quest function Reanimated_Dialogue_Quest() native global

; NPCP Reference Categories
ObjectReference function Input_Category() native global
ObjectReference function Swords_Category() native global
ObjectReference function Greatswords_Category() native global
ObjectReference function Waraxes_Category() native global
ObjectReference function Battleaxes_Category() native global
ObjectReference function Maces_Category() native global
ObjectReference function Warhammers_Category() native global
ObjectReference function Daggers_Category() native global
ObjectReference function Staves_Category() native global
ObjectReference function Bows_Category() native global
ObjectReference function Ammo_Category() native global
ObjectReference function Weapons_Category() native global
ObjectReference function Light_Armor_Category() native global
ObjectReference function Heavy_Armor_Category() native global
ObjectReference function Shields_Category() native global
ObjectReference function Jewelry_Category() native global
ObjectReference function Clothes_Category() native global
ObjectReference function Potions_Category() native global
ObjectReference function Poisons_Category() native global
ObjectReference function Ingredients_Category() native global
ObjectReference function Food_Category() native global
ObjectReference function Soulgems_Category() native global
ObjectReference function Scrolls_Category() native global
ObjectReference function Metals_Category() native global
ObjectReference function Leather_Category() native global
ObjectReference function Gems_Category() native global
ObjectReference function Clutter_Category() native global
ObjectReference function Keys_Category() native global
ObjectReference function Misc_Category() native global
ObjectReference function Spell_Tomes_Category() native global
ObjectReference function Recipes_Category() native global
ObjectReference function A_Books_Category() native global
ObjectReference function B_Books_Category() native global
ObjectReference function C_Books_Category() native global
ObjectReference function D_Books_Category() native global
ObjectReference function E_Books_Category() native global
ObjectReference function F_Books_Category() native global
ObjectReference function G_Books_Category() native global
ObjectReference function H_Books_Category() native global
ObjectReference function I_Books_Category() native global
ObjectReference function J_Books_Category() native global
ObjectReference function K_Books_Category() native global
ObjectReference function L_Books_Category() native global
ObjectReference function M_Books_Category() native global
ObjectReference function N_Books_Category() native global
ObjectReference function O_Books_Category() native global
ObjectReference function P_Books_Category() native global
ObjectReference function Q_Books_Category() native global
ObjectReference function R_Books_Category() native global
ObjectReference function S_Books_Category() native global
ObjectReference function T_Books_Category() native global
ObjectReference function U_Books_Category() native global
ObjectReference function V_Books_Category() native global
ObjectReference function W_Books_Category() native global
ObjectReference function X_Books_Category() native global
ObjectReference function Y_Books_Category() native global
ObjectReference function Z_Books_Category() native global
ObjectReference function Books_Category() native global

; NPCP Reference Markers
ObjectReference function Cell_Marker() native global
ObjectReference function Expo_Antechamber_Marker() native global
ObjectReference function Storage_Marker() native global

; NPCP Spells
Spell function Cell_Ability_Spell() native global
Spell function Retreat_Ability_Spell() native global

; NPCP Weapons
Weapon function Blank_Weapon() native global

; Literals
int property VERSION_MAJOR                  =     0 autoReadOnly hidden; set manually upon each release
int property VERSION_MINOR                  =     9 autoReadOnly hidden; set manually upon each release
int property VERSION_PATCH                  =     2 autoReadOnly hidden; set manually upon each release

int property MIN_DISPLAY                    =     1 autoReadOnly hidden
int property MAX_DISPLAY                    =     8 autoReadOnly hidden
int property DEFAULT_DISPLAY                =     5 autoReadOnly hidden

int property DEFAULT_PERCENT_BODY           =   100 autoReadOnly hidden
int property DEFAULT_PERCENT_FEET           =    90 autoReadOnly hidden
int property DEFAULT_PERCENT_HANDS          =    90 autoReadOnly hidden
int property DEFAULT_PERCENT_HEAD           =    50 autoReadOnly hidden

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

; Keys
string property KEY_G_DIALOGUE_MENU         = "Global: Open Dialogue Menu"  autoReadOnly hidden

string property KEY_N_TOGGLE_MEMBER         = "NPC: Toggle Member"          autoReadOnly hidden
string property KEY_N_TOGGLE_MOVE           = "NPC: Toggle Move"            autoReadOnly hidden
string property KEY_N_MOVE_FARTHER          = "NPC: Move Farther"           autoReadOnly hidden
string property KEY_N_MOVE_NEARER           = "NPC: Move Nearer"            autoReadOnly hidden
string property KEY_N_MOVE_ROTATE_LEFT      = "NPC: Rotate Left"            autoReadOnly hidden
string property KEY_N_MOVE_ROTATE_RIGHT     = "NPC: Rotate Right"           autoReadOnly hidden
string property KEY_N_HAS_BASE              = "NPC: Has Base"               autoReadOnly hidden
string property KEY_N_COUNT_BASE            = "NPC: Count Base"             autoReadOnly hidden
string property KEY_N_HAS_HEAD              = "NPC: Has Head"               autoReadOnly hidden
string property KEY_N_COUNT_HEADS           = "NPC: Count Heads"            autoReadOnly hidden

string property KEY_M_TOGGLE_CLONE          = "Member: Toggle Clone"        autoReadOnly hidden
string property KEY_M_TOGGLE_SETTLER        = "Member: Toggle Settler"      autoReadOnly hidden
string property KEY_M_TOGGLE_THRALL         = "Member: Toggle Thrall"       autoReadOnly hidden
string property KEY_M_TOGGLE_IMMOBILE       = "Member: Toggle Immobile"     autoReadOnly hidden
string property KEY_M_TOGGLE_PARALYZED      = "Member: Toggle Paralyzed"    autoReadOnly hidden
string property KEY_M_TOGGLE_FOLLOWER       = "Member: Toggle Follower"     autoReadOnly hidden

string property KEY_F_TOGGLE_SNEAK          = "Follower: Toggle Sneak"      autoReadOnly hidden
string property KEY_F_TOGGLE_SADDLER        = "Follower: Toggle Saddler"    autoReadOnly hidden

string property KEY_MS_TOGGLE_DISPLAY       = "Members: Toggle Display"     autoReadOnly hidden
string property KEY_MS_DISPLAY_PREVIOUS     = "Members: Display Previous"   autoReadOnly hidden
string property KEY_MS_DISPLAY_NEXT         = "Members: Display Next"       autoReadOnly hidden

string property KEY_FS_SUMMON_ALL           = "Followers: Summon All"       autoReadOnly hidden
string property KEY_FS_SUMMON_MOBILE        = "Followers: Summon Mobile"    autoReadOnly hidden
string property KEY_FS_SUMMON_IMMOBILE      = "Followers: Summon Immobile"  autoReadOnly hidden
string property KEY_FS_SETTLE               = "Followers: Settle"           autoReadOnly hidden
string property KEY_FS_UNSETTLE             = "Followers: Unsettle"         autoReadOnly hidden
string property KEY_FS_MOBILIZE             = "Followers: Mobilize"         autoReadOnly hidden
string property KEY_FS_IMMOBILIZE           = "Followers: Immobilize"       autoReadOnly hidden
string property KEY_FS_SNEAK                = "Followers: Sneak"            autoReadOnly hidden
string property KEY_FS_UNSNEAK              = "Followers: Unsneak"          autoReadOnly hidden
string property KEY_FS_SADDLE               = "Followers: Saddle"           autoReadOnly hidden
string property KEY_FS_UNSADDLE             = "Followers: Unsaddle"         autoReadOnly hidden
string property KEY_FS_RESURRECT            = "Followers: Resurrect"        autoReadOnly hidden
