/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace doticu_npcp { namespace Member {

    TESObjectREFR *Get_Pack(BGSBaseAlias *member);

}}

namespace doticu_npcp { namespace Member { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
