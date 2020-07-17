/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "offsets.h"
#include "types.h"

namespace doticu_npcp { namespace Actor2 {

    const char *Get_Base_Name(Actor *actor);
    const char *Get_Ref_Name(Actor *actor);
    const char *Get_Name(Actor *actor);

    BGSOutfit *Get_Outfit(Actor *ref_actor, bool get_sleep_outfit);
    void Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit);

    void Set_Outfit2(Actor *actor, TESForm *linchpin, TESObjectREFR *vanilla, TESObjectREFR *custom, TESObjectREFR *transfer);
    void Copy_Outfit2_Partition(Actor *actor, TESForm *linchpin, TESObjectREFR *outfit2_partition);

    void Cache_Worn(Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out);
    void Cache_Inventory(Actor *actor, TESForm *linchpin, TESObjectREFR *worn_out, TESObjectREFR *pack_out);
    void Cache_Static_Inventory(VMClassRegistry* registry, UInt32 id_stack, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out);

    bool Has_Same_Head(Actor *actor_a, Actor *actor_b);

    bool Is_Alive(Actor *actor);
    bool Is_Dead(Actor *actor);
    bool Is_Loaded(Actor_t *actor);
    bool Is_Unloaded(Actor_t* actor);
    bool Is_Unique(Actor_t* actor);
    bool Is_Generic(Actor_t* actor);
    bool Is_Aliased_In_Quest(Actor *actor, TESQuest *quest);

    void Move_To_Orbit(Actor *obj, TESObjectREFR *target, float radius, float angle_degree);

    Actor_Value_Owner_t* Actor_Value_Owner(Actor_t* actor);
    float Get_Actor_Value(Actor *actor, const char *name);
    float Get_Base_Actor_Value(Actor *actor, const char *name);
    float Get_Max_Actor_Value(Actor *actor, const char *name);
    void Set_Actor_Value(Actor *actor, const char *name, float value);
    void Reset_Actor_Value(Actor *actor, const char *name);
    void Log_Actor_Values(Actor *actor);

    Actor_t* Get_Mount(Actor_t* mounter);
    Actor_t* Get_Mounted_Actor(Actor_t* horse);
    bool Is_On_Mount(Actor_t* actor);

    Int_t Sex(Actor_t* actor);
    String_t Race(Actor_t* actor);

    void Evaluate_Package(Actor_t* actor, bool unk_01 = false, bool unk_02 = false);
    void Update_3D_Model(Actor_t* actor);
    void Fully_Update_3D_Model(Actor_t* actor);
    
    XFactions_t* XFactions(Actor_t* actor, bool do_create = false);
    BFaction_Ranks_t* BFaction_Ranks(Actor_t* actor);
    XFaction_Ranks_t* XFaction_Ranks(Actor_t* actor, bool do_create = false);
    
    Bool_t Has_Faction(Actor_t* actor, Faction_t* faction);
    Bool_t Has_Faction_Rank(Actor_t* actor, Faction_t* faction, Int_t rank);
    void Add_Faction(Actor_t* actor, Faction_t* faction, Int_t rank = 0);
    void Remove_Faction(Actor_t* actor, Faction_t* faction);
    void Add_Crime_Faction(Actor_t* actor, Faction_t* crime_faction);
    void Remove_Crime_Faction(Actor_t* actor);
    void Log_Factions(Actor_t* actor);

    void Follow_Player(Actor_t* actor, Bool_t allow_favors = true);
    void Unfollow_Player(Actor_t* actor);
    void Talks_To_Player(Actor_t* actor, Bool_t can_talk);
    Bool_t Can_Talk_To_Player(Actor_t* actor);
    Bool_t Cant_Talk_To_Player(Actor_t* actor);
    Bool_t Race_Can_Talk_To_Player(Actor_t* actor);
    Bool_t Race_Cant_Talk_To_Player(Actor_t* actor);

    Bool_t Is_AI_Enabled(Actor_t* actor);
    void Enable_AI(Actor_t* actor);
    void Disable_AI(Actor_t* actor);
    
    Bool_t Is_Ghost(Actor_t* actor);
    void Ghostify(Actor_t* actor);
    void Unghostify(Actor_t* actor);

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
