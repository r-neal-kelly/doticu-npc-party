; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_consts hidden

; We actually want to remove the need of most of these in due time.

; Skyrim Actors
Actor function Player_Actor() native global

; Skyrim Keywords
Keyword function Vampire_Keyword() native global

; Skyrim Perks
Perk function Vampire_Feed_Perk() native global

; Skyrim Quests
Quest function Bard_Songs_Quest() native global
Quest function Player_Vampire_Quest() native global

; Dawnguard Factions
Faction function DLC1_Thrall_Faction() native global

; NPCP Actor Bases
ActorBase function Menu_Actor_Base() native global

; NPCP Globals
GlobalVariable function Is_Installed_Global() native global
GlobalVariable function Allow_Dialogue_For_All_Global() native global
GlobalVariable function Allow_Chatter_Global() native global
GlobalVariable function Force_Clone_Uniques_Global() native global
GlobalVariable function Force_Clone_Generics_Global() native global
GlobalVariable function Force_Unclone_Uniques_Global() native global
GlobalVariable function Force_Unclone_Generics_Global() native global
GlobalVariable function No_Body_Percent_Global() native global
GlobalVariable function No_Feet_Percent_Global() native global
GlobalVariable function No_Hands_Percent_Global() native global
GlobalVariable function No_Head_Percent_Global() native global

; NPCP Ints
int function NPCP_Major() native global
int function NPCP_Minor() native global
int function NPCP_Patch() native global

; NPCP Misc Tokens
MiscObject function Greeter_Token() native global

; NPCP Perks
Perk function Kiss_Thrall_Perk() native global
Perk function Reanimate_Perk() native global
Perk function Resurrect_Perk() native global
Perk function Unparalyze_Perk() native global

; NPCP Quests
Quest function Main_Quest() native global
Quest function Vars_Quest() native global
Quest function Funcs_Quest() native global
Quest function Members_Quest() native global
Quest function Followers_Quest() native global
Quest function Control_Quest() native global
