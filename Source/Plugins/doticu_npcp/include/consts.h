/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Consts {

    using namespace Papyrus;

    String_t Class_Name();
    Class_Info_t* Class_Info();
    Consts_t* Self();
    Object_t* Object();
    Variable_t* Variable(String_t variable_name);

    // Skyrim.esm
    Faction_t* No_Bard_Singer_Autostart_Faction();
    Faction_t* Current_Follower_Faction();
    Faction_t* Potential_Follower_Faction();
    Faction_t* WI_No_Body_Cleanup_Faction();

    Static_t* Marker_X_Static();

    // Dawnguard.esm
    Faction_t* DLC1_Thrall_Faction();
    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction();
    
    // doticu_npc_party.esp
    Faction_t* Member_Faction();
    Faction_t* Horse_Faction();

    Formlist_t* Settler_Markers_Formlist();

    Misc_t* Member_Token();
    Misc_t* Generic_Token();
    Misc_t* Clone_Token();
    Misc_t* Immobile_Token();
    Misc_t* Settler_Token();
    Misc_t* Thrall_Token();
    Misc_t* Paralyzed_Token();
    Misc_t* Mannequin_Token();
    Misc_t* Display_Token();
    Misc_t* Default_Style_Token();
    Misc_t* Warrior_Style_Token();
    Misc_t* Mage_Style_Token();
    Misc_t* Archer_Style_Token();
    Misc_t* Coward_Style_Token();
    Misc_t* Mortal_Vitality_Token();
    Misc_t* Protected_Vitality_Token();
    Misc_t* Essential_Vitality_Token();
    Misc_t* Invulnerable_Vitality_Token();
    Misc_t* Sneak_Follower_Token();

    Quest_t* Static_Data_Quest();
    Quest_t* Dynamic_Data_Quest();
    Quest_t* Members_Quest();
    Quest_t* Followers_Quest();
    Quest_t* Control_Quest();

    Reference_t* Storage_Marker();

    Weapon_t* Blank_Weapon();

    void Log_Variables(Consts_t* self);
    void Log_Defaults(Consts_t* self);
    void Log_Properties(Consts_t* self);

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Registry_t* registry);

}}}
