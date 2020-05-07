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

    bool Is_Worn(Actor *ref_actor, TESForm *ref_form);

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    void Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit);
    bool Has_Changed_Outfit(StaticFunctionTag *, Actor *ref_actor, TESObjectREFR *ref_outfit, TESObjectREFR *ref_outfit2, TESForm *ref_linchpin);
    void Refresh_Outfit(StaticFunctionTag *, Actor *ref_actor, TESObjectREFR *ref_outfit, TESObjectREFR *ref_outfit2, TESForm *ref_linchpin);

    bool Register(VMClassRegistry *registry);

}}}
