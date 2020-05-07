/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "papyrus.h"

namespace doticu_npcp { namespace Outfit { namespace Exports {

    void Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);
    void Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);

    bool Register(VMClassRegistry *registry);

}}}
