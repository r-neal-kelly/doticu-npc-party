/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Outfit {

    void Add_Item(Outfit_t* outfit, Form_t* form);
    void Remove_Item(Outfit_t* outfit, Form_t* form);

}}

namespace doticu_npcp { namespace Outfit { namespace Exports {

    void Add_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);
    void Remove_Item(StaticFunctionTag *, BGSOutfit *outfit, TESForm *form_item);

    bool Register(VMClassRegistry *registry);

}}}
