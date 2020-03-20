/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusArgs.h"
#include "skse64/PapyrusVM.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/GameForms.h"
#include "skse64/GameReferences.h"

static IDebugLog gLog;

namespace doticu_npcp {

    void Outfit_Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);
    void Outfit_Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);
    void Actor_Set_Outfit(Actor *ref_actor, BGSOutfit *outfit, bool is_sleep_outfit);

    bool Register_Functions(VMClassRegistry *registry);

}
