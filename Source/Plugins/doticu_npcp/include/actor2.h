/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameReferences.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"

#include "papyrus.h"
#include "object_ref.h"

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

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    void Set_Outfit2(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *vanilla, TESObjectREFR *custom, TESObjectREFR *transfer);

    void Cache_Worn(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out);
    void Cache_Inventory(StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *worn_out, TESObjectREFR *pack_out);
    void Cache_Static_Inventory(VMClassRegistry* registry, UInt32 id_stack, StaticFunctionTag *, Actor *actor, TESForm *linchpin, TESObjectREFR *cache_out);

    bool Register(VMClassRegistry *registry);

}}}
