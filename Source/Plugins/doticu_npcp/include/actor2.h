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
    bool Is_AI_Enabled(Actor *actor);
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
}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    void Set_Outfit2(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *vanilla, TESObjectREFR *custom, TESObjectREFR *transfer);

    void Cache_Worn(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out);
    void Cache_Inventory(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *worn_out, TESObjectREFR *pack_out);
    void Cache_Static_Inventory(VMClassRegistry* registry, UInt32 id_stack, StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out);

    bool Register(VMClassRegistry *registry);

}}}
