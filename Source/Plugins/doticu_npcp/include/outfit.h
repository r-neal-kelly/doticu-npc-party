/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Outfit {



}}

namespace doticu_npcp { namespace Outfit { namespace Exports {

    void Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);
    void Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);

    bool Register(VMClassRegistry *registry);

}}}
