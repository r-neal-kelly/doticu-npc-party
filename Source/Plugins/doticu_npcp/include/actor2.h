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
    // need to examine this is up to standards of the new method.
    void Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit);

    bool Has_Outfit2(Actor *actor,
                     TESForm *linchpin,
                     TESObjectREFR *vanilla,
                     TESObjectREFR *custom
    );
    bool Has_Outfit2_Partition(Actor *actor,
                               TESForm *linchpin,
                               TESObjectREFR *outfit2_partition
    );
    void Set_Outfit2(Actor *actor,
                     TESForm *linchpin, // an item that when present, stops the engine from adding unwanted items to actor
                     TESObjectREFR *vanilla, // a cache of pre-calculated vanilla outfit items (can be null)
                     TESObjectREFR *custom, // custom items which are additional to vanilla
                     TESObjectREFR *trash, // where non-matching items are put specifically for deletion, i.e. previous outfit items
                     TESObjectREFR *transfer // where non-matching items are put for transfer elsewhere, i.e. items from the world
    );
    void Set_Outfit2_Dead(Actor *actor,
                          TESForm *linchpin,
                          TESObjectREFR *vanilla,
                          TESObjectREFR *custom,
                          TESObjectREFR *trash,
                          TESObjectREFR *transfer
    );
    void Copy_Outfit2_Partition(Actor *actor,
                                TESForm *linchpin,
                                TESObjectREFR *outfit2_partition
    );

    // need to examine this is up to standards of the new method.
    void Cache_Worn(Actor *actor,
                    TESForm *linchpin,
                    TESObjectREFR *cache_out
    );

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    bool Has_Outfit2(StaticFunctionTag *,
                     Actor *actor,
                     TESForm *linchpin,
                     TESObjectREFR *vanilla,
                     TESObjectREFR *custom
    );
    void Set_Outfit2(StaticFunctionTag *,
                     Actor *actor,
                     TESForm *linchpin,
                     TESObjectREFR *vanilla,
                     TESObjectREFR *custom,
                     TESObjectREFR *trash,
                     TESObjectREFR *transfer
    );
    void Set_Outfit2_Dead(StaticFunctionTag *,
                          Actor *actor,
                          TESForm *linchpin,
                          TESObjectREFR *vanilla,
                          TESObjectREFR *custom,
                          TESObjectREFR *trash,
                          TESObjectREFR *transfer
    );

    void Cache_Worn(StaticFunctionTag *,
                    Actor *actor,
                    TESForm *linchpin,
                    TESObjectREFR *cache_out
    );

    bool Register(VMClassRegistry *registry);

}}}
